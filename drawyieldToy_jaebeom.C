#include <iostream>
#include "TTree.h"
#include "TH1.h"
#include "TMath.h"
#include "TStyle.h"
//#include "./BDT/bininfo.h"
#include "/home/CMS/Analysis/Upsilon3S_pp2017Ref/Utility/Style_jaebeom.h"
#include "fitter.h"
//#include "Headers/Style_jaebeom_wCMSLumi.h"

using namespace std;

void drawyieldToy_jaebeom(double ptLow=0, double ptHigh=4, int cLow = 0, int cHigh=90, int state=3)
{
  gStyle->SetOptStat(0);
  int nToy = 2000;
  int numbins=300;
  double fcut=2.4;
  double nllcut = 64;

  string fname = Form("%dS_pt_%.0f_%.0f_cent_%d_%d",state,ptLow,ptHigh,cLow,cHigh);
  TFile* fn = new TFile(Form("/home/vince402/shared/Upsilon3S_PostPreApp/Yield_nominal/unblind/fit_data_%s.root",fname.c_str()),"read");
  RooFitResult* fitRes;
  if(!(cLow==0 && cHigh==90)) fitRes = (RooFitResult*) fn->Get("fitresult_model_reducedDS");
  else fitRes = (RooFitResult*) fn->Get("fitresult_model_gc_reducedDS");
  double nll_nom = fitRes->minNll();

  RooWorkspace* ws = (RooWorkspace*) fn->Get("workspace");
  double err_mu_nom = ws->var("Erfmean")->getVal();
  double err_sigma_nom = ws->var("Erfsigma")->getVal();
  double err_lambda_nom = ws->var("Erfp0")->getVal();
  double nbkg_nom = ws->var("nBkg")->getVal();

  TH1D* hyn = (TH1D*) fn->Get("hYield");
  double nom = hyn->GetBinContent(state);
  double n1s_nom = hyn->GetBinContent(1);
  double n2s_nom = hyn->GetBinContent(2);
  double nom_sign = nom/hyn->GetBinError(state);
  
  TH1D* h = new TH1D(Form("h%dS",state),Form(";nSig%dS;",state),200,0,nom*3);
  TH1D* hp = new TH1D("hpull",";Pull;",numbins,-5.,5);


  TH1D* hyield;
  RooWorkspace* ws_final = new RooWorkspace("workspaceF");
  RooRealVar* vBkg = new RooRealVar("vBkg","", 0, 1e+9);
  RooRealVar* vstateyield = new RooRealVar("vstateyield","", 0, 0, 1e+9);
  RooRealVar* v1syield = new RooRealVar("v1syield","", 0, -1e+5, +1e+5);
  RooRealVar* v2syield = new RooRealVar("v2syield","", 0, -1e+5, +1e+5);
  RooRealVar* vErfmean = new RooRealVar("vErfmean","", 0, 0, 10);
  RooRealVar* vErfsigma = new RooRealVar("vErfsigma","", 0, -10, 10);
  RooRealVar* vErfp0 = new RooRealVar("vErfp0","", 0, 0, 9);
  RooRealVar* vPull = new RooRealVar("vPull","", 0, -5, 5);
  RooArgSet* argSet = new RooArgSet();
  argSet->add(*vBkg);
  argSet->add(*vstateyield);
  argSet->add(*v1syield);
  argSet->add(*v2syield);
  argSet->add(*vErfmean);
  argSet->add(*vErfsigma);
  argSet->add(*vErfp0);
  argSet->add(*vPull);
  RooDataSet* ds_prefinal = new RooDataSet("datasetF", "pull data", *argSet);


  for(int i=1; i<=nToy;i++){
	TH1::AddDirectory(kFALSE); 
    TFile* t = TFile::Open(Form("/home/vince402/Upsilon3S/MCTOY/Unblind_ToyDir_%dS_pt_%.0f_%.0f_cent_%d_%d/Toy_%d.root",state,ptLow,ptHigh,cLow,cHigh,i));
    if(!t || t->IsZombie()) {continue;}
    RooWorkspace* ws_ = (RooWorkspace*) t->Get("workspaceO");
    double nbkg = ws_->var("nBkg")->getVal();

    TH1D* hyield = (TH1D*) t->Get("hyield");
    double ns = hyield->GetBinContent(state);
    double n1s = hyield->GetBinContent(1);
    double n2s = hyield->GetBinContent(2);

    if(hyield->GetBinContent(6)>fcut){ t->Close("R"); continue;}
    if(fabs(nll_nom-hyield->GetBinContent(7))>nllcut) {t->Close("R"); continue;}

	vBkg->setVal(nbkg);
	vstateyield->setVal(ns);
	v1syield->setVal(n1s);
	v2syield->setVal(n2s);

    double nserr = hyield->GetBinError(state);
	vstateyield->setError(nserr);
    double ns_sign = ns/nserr;

    double err_mu = ws_->var("Erfmean")->getVal();
    double err_sigma = ws_->var("Erfsigma")->getVal();
    double err_lambda = ws_->var("Erfp0")->getVal();
	vErfmean->setVal(err_mu);
	vErfsigma->setVal(err_sigma);
	vErfp0->setVal(err_lambda);

    double valf = (ns-nom)/nserr; 
	vPull->setVal(valf);
	ds_prefinal->add(*argSet);
    h->Fill(ns);
    hp->Fill(valf);
	t->Close("R");
  }
  RooDataSet* ds_final = (RooDataSet*) ds_prefinal->reduce("vPull", "");
  ws_final->import(*ds_final);
  RooRealVar* pdf_gaus_mean = new RooRealVar("gaus_mean", "", 1,-3,3);
  RooRealVar* pdf_gaus_sigma = new RooRealVar("gaus_sigma", "", 1,0, 2);
  RooGaussian* pdf_gaus = new RooGaussian("gauspdf", "", *vPull, *pdf_gaus_mean, *pdf_gaus_sigma);
  RooRealVar* NormG = new RooRealVar("NormG", "", 400, 0, 3000);
  RooAddPdf* model = new RooAddPdf("model_gaus","Norm* Gaus", RooArgList(*((RooGenericPdf*) pdf_gaus)), RooArgList(*NormG) );
  ws_final->import(*model);

  RooFitResult* fitres = ws_final->pdf("model_gaus")->fitTo(*(ws_final->data("datasetF")), RooFit::Minimizer("Minuit","minimize"), RooFit::Save(), RooFit::Range(-5, 5), RooFit::NumCPU(2));
  TFile* f_out = new TFile(Form("MCTOY/result_%s.root",fname.c_str()), "recreate");
  f_out->cd();
  fitres->Write();
  fitres->Print();
  ws_final->Write();

  TF1 *f1 = new TF1("f1", "gaus", -5, 5);
  hp->Fit("f1","R");
  double mean = f1->GetParameter(1);
  double meanerr = f1->GetParError(1);
  double sigma = f1->GetParameter(2);
  double sigmaerr = f1->GetParError(2);
  double textsize = 0.03;
  double xpos = 0.55;
  double ypos = 0.83;
  double ydiff=0.05;
  TCanvas* c1 = new TCanvas("c1","",700,700);
  c1->cd();
  h->Draw();
  drawGlobText(Form("#varUpsilon(%dS)",state),xpos,ypos,kBlack,textsize);
  drawGlobText(Form("%.0f<p_{T}<%.0f GeV/c",ptLow,ptHigh),xpos,ypos-ydiff,kBlack,textsize);
  drawGlobText(Form("cent. %d-%d%%",cLow,cHigh),xpos,ypos-ydiff*2,kBlack,textsize);
  drawGlobText(Form("#mu = %.3f #pm %.3f",h->GetMean(),h->GetRMS()),xpos,ypos-ydiff*3,kBlack,textsize);
  drawGlobText(Form("nominal #mu = %.3f #pm %.3f",nom,hyn->GetBinError(state)),xpos,ypos-ydiff*4,kBlack,textsize);
  c1->SaveAs(Form("MCTOY/Unblind_ResultToyMC_Yield_%s.pdf",fname.c_str()));
  
  xpos = 0.15;
  ypos = 0.83;
  TCanvas* c2 = new TCanvas("c2","",700,700);
  c2->cd();
  hp->SetMarkerSize(1.0);
  hp->Draw("PE");

  dashedLine(mean,0,mean,f1->Eval(mean),2,2);

  drawGlobText(Form("#varUpsilon(%dS)",state),xpos,ypos,kBlack,textsize);
  drawGlobText(Form("%.0f<p_{T}<%.0f GeV/c",ptLow,ptHigh),xpos,ypos-ydiff,kBlack,textsize);
  drawGlobText(Form("cent. %d-%d%%",cLow,cHigh),xpos,ypos-ydiff*2,kBlack,textsize);
  drawGlobText(Form("#mu = %.3f #pm %.3f",mean,meanerr),xpos,ypos-ydiff*3,kBlack,textsize);
  drawGlobText(Form("#sigma = %.3f #pm %.3f",sigma,sigmaerr),xpos,ypos-ydiff*4,kBlack,textsize);

  cout << "entries : " << hp->GetEntries() << endl;
  cout << "mean - rms : " << hp->GetMean() << ", " << hp->GetRMS() << endl;

  c2->SaveAs(Form("MCTOY/Unblind_ResultToyMC_%s.pdf",fname.c_str()));
  TCanvas* c3 = new TCanvas("c3","", 600,700);
  RooPlot* plt = ws_final->var("vPull")->frame(40);
  ws_final->data("datasetF")->plotOn(plt);
  ws_final->pdf("model_gaus")->plotOn(plt);
  plt->Draw();
  c3->cd();
  f_out->cd();
  plt->Write();
  c3->Write();
  c2->Write();
  c1->Write();
  c2->Write();
  f_out->Close();
}
