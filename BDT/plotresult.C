#include <iostream>
#include <cstdlib>
#include "TROOT.h"
#include "RooFit.h"
#include "RooPlot.h"
#include "bininfo.h"

using namespace RooFoit;


std::vector<std::pair<double, double>> bdtbin5 = {{-1.0, -0.2}, {-0.2, -0.1}, {-0.1, 0.05},{0.05, 0.2}, {0.2, 1.0}};
std::vector<std::pair<double, double>> bdtbin3 = {{-1.0, -0.2}, {-0.2, 0.05}, {0.05, 1.0}};

string workdir = "/home/vince402/Upsilon3S";
string plotdir;

TPad* plotone(long ts,double ylim, int ptlow, int pthigh, int cbinlow, int cbinhigh,float blow,  float bhigh, float vcut, TString MupT = "3p5", string Trig = "S13", TString fittype = "freefit"){
  string fitdir;
  int ylim10 = (int) (ylim*10);

  if( fittype=="freefit") fitdir = "FF";
  else if (fittype=="DatafixtoMC") fitdir = "DFM";
  TFile* file1 = new TFile(Form("%s/Yield/Yield_%ld_%s_pt_%d-%d_rap_-%d-%d_120bin_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", workdir.c_str(), ts, fitdir.c_str(),ptlow, pthigh, ylim10, ylim10, cbinlow, cbinhigh, blow, bhigh, vcut),"read");
//  TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
  TString massDIR = Form("%s/MassDist/BDT/%ld/freefit/%s/%.1f/cent%d-%d/pT%.1f-%.1f/FitResult",workdir.c_str(), ts,Trig.c_str(),ylim,cbinlow, cbinhigh, (double) ptlow, (double) pthigh);
  plotdir = massDIR;
  void * dirpM = gSystem->OpenDirectory(massDIR.Data());
  if(dirpM) gSystem->FreeDirectory(dirpM);
  else{ gSystem->mkdir(massDIR.Data(), kTRUE);}

  RooWorkspace* works1 = (RooWorkspace*) file1->Get("workspace");
  RooFitResult* Result = (RooFitResult*) file1->Get("fitresult_model_reducedDS");

  RooDataSet* dataset = (RooDataSet*) works1->data("reducedDS");
  RooRealVar* vmass = (RooRealVar*) works1->var("mass");

  gStyle->SetOptTitle(0);
  
  RooPlot* plot1 = vmass->frame();
  works1->data("reducedDS")->plotOn(plot1, Name("massPlot"), MarkerSize(0.5), LineWidth(1));
  works1->pdf("model")->plotOn(plot1, Name("modelPlot"), LineWidth(1));

//  RooGenericPdf* cb1 = (RooGenericPdf*) works1->pdf("twoCB1S");
  works1->pdf("model")->plotOn(plot1, Components(RooArgSet(*works1->pdf("twoCB1S")) ), LineWidth(1),LineStyle(1), LineColor(kRed) , MoveToBack());
  works1->pdf("model")->plotOn(plot1, Components(RooArgSet(*works1->pdf("twoCB2S")) ), LineWidth(1),LineStyle(1), LineColor(kRed) , MoveToBack());
  works1->pdf("model")->plotOn(plot1, Components(RooArgSet(*works1->pdf("twoCB3S")) ), LineWidth(1),LineStyle(1), LineColor(kRed) , MoveToBack());
  works1->pdf("model")->plotOn(plot1, Components(RooArgSet(*works1->pdf("bkgErf")) ), LineWidth(1), LineStyle(1), LineColor(kGreen), MoveToBack() );

//  TCanvas* c1 = new TCanvas("c1", "", 1100, 800);
  TPad* c1 = new TPad("c1","", 0,0,1,1);
  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.7, 1.0);
  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.0, 0.7, 0.25);
  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.7, 0.0, 1.0, 1.0);
  c1->cd();
  pad_mass->Draw();
  pad_pull->SetBottomMargin(0);
  pad_pull->Draw();
  pad_leg->Draw();
  pad_mass->cd();
  plot1->Draw();

  pad_pull->cd();
  pad_pull->SetGrid(0,1);
  pad_pull->SetTopMargin(0);
  TLine* line_pull = new TLine(8.,0., 14., 0.);
  line_pull->SetLineColorAlpha(kRed, 0.5);
  RooHist* hpull = plot1->pullHist("massPlot", "modelPlot");
  RooPlot* pullPlot = works1->var("mass")->frame(Title("Pull Distribution"));
  pullPlot->addPlotable(hpull, "P");
  pullPlot->GetYaxis()->SetLabelSize(0.13);
  pullPlot->Draw();
  line_pull->Draw("same");
  RooArgList parList = Result->floatParsFinal();
  Double_t chi2 = 0.;
  Double_t *ypull = hpull->GetY();
  Double_t Npullbin =0;
  for(Int_t ibin = 0; ibin < 120; ibin++){
    if(ypull[ibin] == 0) continue;
    chi2 += TMath::Power(ypull[ibin],2);
    Npullbin++;
  }
  int Nfitpar = parList.getSize();
  int ndf = Npullbin - Nfitpar;
  TLatex* NormChi2tex = new TLatex();
  NormChi2tex->SetNDC();
  NormChi2tex->SetTextSize(0.035);
  NormChi2tex->SetTextFont(42);
  pad_mass->cd();
  NormChi2tex->DrawLatex(0.1, 0.02, Form("#chi^{2}/ndf: %3.f/%d", chi2, ndf));

  pad_leg->cd();
  RooPlot* legPlot = works1->var("mass")->frame(Name("Fit Results"), Title("Fit Results"));
  works1->pdf("model")->paramOn(legPlot, Layout(0, 0.93, 0.97), Parameters(parList));
  legPlot->getAttText()->SetTextAlign(11);
  legPlot->getAttText()->SetTextSize(0.07);

  TPaveText* Ptext = (TPaveText*) legPlot->findObject(Form("%s_paramBox", works1->pdf("model")->GetName())); 
  Ptext->SetY1(0.03);
  Ptext->SetY2(0.93);
  Ptext->Draw();

  c1->Update();
  return c1;
};

void plotresult(long ts, double ylim, int ptlow, int pthigh, int cbinlow, int cbinhigh,  float vcut, TString MupT = "3p5", string Trig = "S13", TString fittype = "freefit", int binnum=5){
  std::vector<std::pair<double, double>> bdtbin;
  bdtbin = bdtbinsec[ts][binnum];
  if(bdtbinsec.find[ts] == bdtbinsec.end()){
  bdtbin = (binnum ==5) ? bdtbin5 : ( (binnum ==3) ?  bdtbin3 : bdtbin5);
  }

  TCanvas* c1;
  if(binnum == 5){ c1 = new TCanvas("c1", "", 3000,1800); c1->Divide(3,2);}
  else if (binnum ==3 ) {c1 = new TCanvas("c1", "", 3000, 900); c1->Divide(3,1);}
  c1->cd();
  TPad* p1, p2, p3, p4, p5;
  int count=1;
  for(auto range : bdtbin){
    p1 = plotone(ts, ylim,ptlow, pthigh, cbinlow, cbinhigh, range.first, range.second, vcut, MupT, Trig, fittype);
    TLatex* bdtlabel = new TLatex();
    p1->cd();
    bdtlabel->SetNDC();
    bdtlabel->DrawLatex(0.25,0.8, Form("BDT #in [%.2f, %.2f]",range.first, range.second));
    c1->cd(count);
    p1->Draw();
    count++;
  }
  c1->Update();
  c1->SaveAs(Form("%s/FitResult_BDT_%ld_y%.1f_%dbin_collection_pt%d-%d_cbin%d-%d.pdf",plotdir.c_str(), ts,ylim, binnum, ptlow, pthigh, cbinlow, cbinhigh));
}


