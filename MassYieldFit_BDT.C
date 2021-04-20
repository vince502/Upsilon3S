#include <TROOT.h>
#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaveText.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TParameter.h>
#include <TSystem.h>
#include <RooRealVar.h>
#include <RooArgSet.h>
#include <RooDataSet.h>
#include <RooWorkspace.h>
#include <RooPlot.h>
#include <RooHist.h>
#include <RooGaussian.h>
#include <RooCBShape.h>
#include <RooChebychev.h>
#include <RooPolynomial.h>
#include <RooExponential.h>
#include <RooGenericPdf.h>
#include <RooAddPdf.h>
#include <RooFitResult.h>
#include <RooFormulaVar.h>
#include "Headers/Style_Upv2.h"
#include "Headers/Upsilon.h"
#include ".workdir.h"

using namespace std;
using namespace RooFit;

void MassYieldFit_BDT(const string fname = "", const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString MupT = "3p5", const string Trig = "", int cBinLow =0, int cBinHigh = 180, double cutQVP = 0.01, double cutBDTlow=-1, double cutBDThigh = 1. ,Double_t params[/*sigma1S_1, alpha, n , frac, Erfmean, Erfsigma, Erfp0*/]= {},Double_t paramslow[/*sigma1S_1, alpha, n , frac, Erfmean, Erfsigma, Erfp0*/]= {},Double_t paramshigh[/*sigma1S_1, alpha, n , frac, Erfmean, Erfsigma, Erfp0*/]= {}){
  Double_t etaMax= 2.4;
  Double_t etaMin = -2.4;
  string delim = "OniaRooDataset_BDT";
  size_t pos = fname.find(delim)+18;
  string ts = fname.substr(pos,10);

  bool swflag = false;
  if( fname.find("Switch1") != std::string::npos) { swflag = true;}
  
  TString mainDIR = workdir;
  TString massDIR = mainDIR +  Form("/MassDist/BDT/%s/freefit/%s/%.1f/cent%d-%d/pT%.1f-%.1f/FitResult",ts.c_str(), Trig.c_str(), rapMax,cBinLow,cBinHigh,ptMin,ptMax);
  TString massDIRp = mainDIR + Form("/MassDist/BDT/%s/freefit/%s/%.1f/cent%d-%d/pT%.1f-%.1f/FitResult/png", ts.c_str(), Trig.c_str(), rapMax,cBinLow,cBinHigh,ptMin,ptMax);
  TString massDIRl = mainDIR + Form("/MassDist/BDT/%s/freefit/%s/%.1f/cent%d-%d/pT%.1f-%.1f/FitResult/logY", ts.c_str(), Trig.c_str(), rapMax,cBinLow,cBinHigh,ptMin,ptMax);
  TString massDIR2 = mainDIR + Form("/MassDist/BDT/%s/freefit/%s/%.1f/cent%d-%d/pT%.1f-%.1f/WithoutFit", ts.c_str(), Trig.c_str(), rapMax,cBinLow,cBinHigh,ptMin,ptMax);
  void * dirpM = gSystem->OpenDirectory(massDIR.Data());
  if(dirpM) gSystem->FreeDirectory(dirpM);
  else{ gSystem->mkdir(massDIR.Data(), kTRUE); gSystem->mkdir(massDIRl.Data(),kTRUE);}
  void * dirpM2 = gSystem->OpenDirectory(massDIR2.Data());
  if(dirpM2) gSystem->FreeDirectory(dirpM2);
  else gSystem->mkdir(massDIR2.Data(), kTRUE);
  void * dirpMp = gSystem->OpenDirectory(massDIRp.Data());
  if(dirpMp) gSystem->FreeDirectory(dirpMp);
  else gSystem->mkdir(massDIRp.Data(), kTRUE);
  TString yieldDIR = mainDIR + "/Yield";
  void * dirpY = gSystem->OpenDirectory(yieldDIR.Data());
  if(dirpY) gSystem->FreeDirectory(dirpY);
  else gSystem->mkdir(yieldDIR.Data(), kTRUE);

  SetStyle();

  const Double_t RangeLow = 8;
  const Double_t RangeHigh = 14;
  const Int_t Nmassbins = 120;

  TFile* fout;
  fout = new TFile(Form("/home/vince402/Upsilon3S/Yield/Yield_%s_FF_pt_%d-%d_rap_%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_%s%d_%s%.4f-%.4f_%s%.4f.root",ts.c_str(), (int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(),(int) swflag, "BDT",1,"cut",cutBDTlow, cutBDThigh ,"vp",cutQVP), "RECREATE");

  Double_t MupTCut;
  if(MupT == "0") MupTCut = 0;
  else if(MupT == "0p5") MupTCut = 0.5;
  else if(MupT == "1") MupTCut = 1.0;
  else if(MupT == "1p5") MupTCut = 1.5;
  else if(MupT == "2") MupTCut = 2.0;
  else if(MupT == "2p5") MupTCut = 2.5;
  else if(MupT == "3") MupTCut = 3.0;
  else if(MupT == "3p5") MupTCut = 3.5;
  else if(MupT == "4") MupTCut = 4.0;
  else
  {
          cout << "There is no such muon pT cut value" << endl;
          return;
  }

  TFile* fin;
  fin = new TFile(Form("%s",fname.c_str()),"READ");
  RooDataSet* dataset;
  dataset = (RooDataSet*) fin->Get("dataset");

  RooWorkspace* works1 = new RooWorkspace(Form("workspace"));
  works1->import(*dataset);

  RooArgSet* argRD = new RooArgSet(*(works1->var("mass")), *(works1->var("pt")), *(works1->var("y")), *(works1->var("cBin")), *(works1->var("pt1")), *(works1->var("pt2")), *(works1->var("eta1")), *(works1->var("eta2")), *(works1->var("QQVtxProb")));
  argRD->add(*(works1->var("BDT")));
  RooDataSet* initialDS = (RooDataSet*) dataset->reduce(*argRD);
  initialDS->SetName("initialDS");
  
  RooDataSet* reducedDS = (RooDataSet*) initialDS->reduce(RooArgSet(*(works1->var("mass"))), Form("( pt >=%f && pt <=%f) && (y >= %f && y <=%f) && (cBin>=%d && cBin<=%d) &&(pt1 >= %f) && (pt2 >= %f) && (eta1 >= %f && eta1 <= %f) && ( eta2 >= %f && eta2 <= %f) && (BDT>= %f && BDT <%f)&&(QQVtxProb > %f)", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, MupTCut, MupTCut, etaMin, etaMax, etaMin, etaMax, cutBDTlow, cutBDThigh, cutQVP));
  reducedDS->SetName("reducedDS");
  works1->import(*reducedDS);
  works1->var("mass")->setRange(RangeLow, RangeHigh);
  works1->var("mass")->Print();

  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
  TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
  c1->cd();
  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.98, 1.0);
  pad_mass->Draw();
  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.05, 0.98, 0.25);
  pad_pull->SetBottomMargin(0);
  pad_pull->Draw();
  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.65, 0.40, 0.99, 0.92);
  pad_leg->SetBottomMargin(0);
  pad_leg->Draw();

  TH1D* hYield = new TH1D("hYield", "", 3, 0, 3);

  pad_mass->cd();
  RooPlot* massPlot = works1->var("mass")->frame(Nmassbins);
  works1->data("reducedDS")->plotOn(massPlot, Name("massPlot"));

  RooRealVar mean1S("mean1S", "mean of Upsilon 1S", U1S_mass, U1S_mass-0.015, U1S_mass+0.015);
  RooRealVar mean3S("mean3S", "mean of Upsilon 1S", U3S_mass, U3S_mass-0.010, U3S_mass+0.010);
  RooRealVar mratio2("mratio2", "mratio2", U2S_mass/U1S_mass);
  RooRealVar mratio3("mratio3", "mratio3", U3S_mass/U1S_mass);
  RooFormulaVar mean2S("mean2S", "mean1S*mratio2", RooArgSet(mean1S, mratio2));
  //RooFormulaVar mean3S("mean3S", "mean1S*mratio3", RooArgSet(mean1S, mratio3));

  RooRealVar sigma1S_1("sigma1S_1", "sigma1 of 1S", 0.05, paramslow[0], paramshigh[0]);
  RooFormulaVar sigma2S_1("sigma2S_1", "@0*@1", RooArgList(sigma1S_1, mratio2));
  RooFormulaVar sigma3S_1("sigma3S_1", "@0*@1", RooArgList(sigma1S_1, mratio3));

  RooRealVar* x1S = new RooRealVar("x1S", "sigma ratio", 0.35, 0, 1);

  RooFormulaVar sigma1S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_1, *x1S));
  RooFormulaVar sigma2S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_2, mratio2));
  RooFormulaVar sigma3S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_2, mratio3));

  RooRealVar alpha("alpha", "alpha of Crystal ball", 2.0, paramslow[1], paramshigh[1]);
  RooRealVar n("n", "n of Crystal ball", 2.0, paramslow[2], paramshigh[2]);
  RooRealVar* frac = new RooRealVar("frac", "CB fraction", 0.5, paramslow[3], paramshigh[3]);

  RooCBShape* CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *(works1->var("mass")), mean1S, sigma1S_1, alpha, n);
  RooCBShape* CB2S_1 = new RooCBShape("CB2S_1", "2S Crystal ball function1", *(works1->var("mass")), mean2S, sigma2S_1, alpha, n);
  RooCBShape* CB3S_1 = new RooCBShape("CB3S_1", "3S Crystal ball function1", *(works1->var("mass")), mean3S, sigma3S_1, alpha, n);
  RooCBShape* CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *(works1->var("mass")), mean1S, sigma1S_2, alpha, n);
  RooCBShape* CB2S_2 = new RooCBShape("CB2S_2", "2S Crystal ball function2", *(works1->var("mass")), mean2S, sigma2S_2, alpha, n);
  RooCBShape* CB3S_2 = new RooCBShape("CB3S_2", "3S Crystal ball function2", *(works1->var("mass")), mean3S, sigma3S_2, alpha, n);
//  RooGaussian* G1S = new RooGaussian("G1S", "1S Gaussian", *(works1->var("mass")), mean1S, sigma1S_2);
//  RooGaussian* G2S = new RooGaussian("G2S", "2S Gaussian", *(works1->var("mass")), mean2S, sigma2S_2);
//  RooGaussian* G3S = new RooGaussian("G3S", "3S Gaussian", *(works1->var("mass")), mean3S, sigma3S_2);

  RooAddPdf* twoCB1S = new RooAddPdf("twoCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2), RooArgList(*frac));
  RooAddPdf* twoCB2S = new RooAddPdf("twoCB2S", "Sum of 2S Crystal ball", RooArgList(*CB2S_1, *CB2S_2), RooArgList(*frac));
  RooAddPdf* twoCB3S = new RooAddPdf("twoCB3S", "Sum of 3S Crystal ball", RooArgList(*CB3S_1, *CB3S_2), RooArgList(*frac));
//  RooAddPdf* CBG1S = new RooAddPdf("CBG1S", "Sum of 1S Crystal ball Gauss", RooArgList(*CB1S_1, *G1S), RooArgList(*frac));
//  RooAddPdf* CBG2S = new RooAddPdf("CBG2S", "Sum of 2S Crystal ball Gauss", RooArgList(*CB2S_1, *G2S), RooArgList(*frac));
//  RooAddPdf* CBG3S = new RooAddPdf("CBG3S", "Sum of 3S Crystal ball Gauss", RooArgList(*CB3S_1, *G3S), RooArgList(*frac));
  RooRealVar Erfmean("Erfmean", "Mean of Errfunction", 7, paramslow[4], paramshigh[4]);//for 0~40, 4~7 GeV
  RooRealVar Erfsigma("Erfsigma", "Sigma of Errfunction", 1, paramslow[5], paramshigh[5]);//for 0~40, 4~7 GeV
  RooRealVar Erfp0("Erfp0", "1st parameter of Errfunction", 1, paramslow[6], paramshigh[6]);
  RooGenericPdf* bkgErf = new RooGenericPdf("bkgErf", "Error background", "TMath::Exp(-@0/@1)*(TMath::Erf((@0-@2)/(TMath::Sqrt(2)*@3))+1)*0.5", RooArgList(*(works1->var("mass")), Erfp0, Erfmean, Erfsigma));

  RooGenericPdf* Signal1S;
  RooGenericPdf* Signal2S;
  RooGenericPdf* Signal3S;

  Signal1S = (RooGenericPdf*) twoCB1S;
  Signal2S = (RooGenericPdf*) twoCB2S;
  Signal3S = (RooGenericPdf*) twoCB3S;

  RooGenericPdf* Background;
  Background = (RooGenericPdf*) bkgErf;

  sigma1S_1.setVal(params[0]);
  alpha.setVal(params[1]);
  n.setVal(params[2]);
  frac->setVal(params[3]);

  Erfmean.setVal(params[4]);
  Erfsigma.setVal(params[5]);
  Erfp0.setVal(params[6]);

  RooRealVar* nSig1S = new RooRealVar("nSig1S", "# of 1S signal", 400, -1000, 1000000);
  RooRealVar* nSig2S = new RooRealVar("nSig2S", "# of 2S signal", 100, -1000, 300000);
  RooRealVar* nSig3S = new RooRealVar("nSig3S", "# of 3S signal", 30, -10, 90000);
  RooRealVar* nBkg = new RooRealVar("nBkg", "# of background signal", 300, -1000, 10000000);
  RooAddPdf* model = new RooAddPdf("model", "1S+2S+3S+Bkg", RooArgList(*Signal1S, *Signal2S, *Signal3S, *Background), RooArgList(*nSig1S, *nSig2S, *nSig3S, *nBkg));

  works1->import(*model);

  RooFitResult* Result = works1->pdf("model")->fitTo(*reducedDS, Save(), NumCPU(2), Hesse(kTRUE), Range(RangeLow, RangeHigh), Minos(0), SumW2Error(kTRUE), Extended(kTRUE));
  works1->pdf("model")->plotOn(massPlot, Name("modelPlot"));
  works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal1S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal2S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal3S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Background)), LineColor(kBlue), LineStyle(kDashed));
  massPlot->SetTitle("");
  massPlot->SetXTitle("M (GeV/c^2)");
  massPlot->SetYTitle("Counts");
  massPlot->Draw();
  TLatex* lt0 = new TLatex();
  FormLatex(lt0, 12, 0.035);
  lt0->DrawLatex(0.43,0.85, Form("BDT #in [%.2f, %.2f]",cutBDTlow, cutBDThigh));
  lt0->DrawLatex(0.43,0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c",MupTCut));
  lt0->DrawLatex(0.43,0.75, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int) ptMin, (int) ptMax));
  lt0->DrawLatex(0.43,0.70, Form("Centrality %d-%d %%",(int) cBinLow/2, (int) cBinHigh/2));
  lt0->DrawLatex(0.43,0.65, Form("Trigger# : %s", Trig.c_str()));
  Result->Print("v");
  WriteMessage("Fitting is dOnE ! ! !");

  pad_pull->cd();
  pad_pull->SetGrid(0,1);
  TLine* line_pull = new TLine(RangeLow,0.,RangeHigh, 0.);
  line_pull->SetLineColorAlpha(kRed, 0.5);
  line_pull->SetLineWidth(3);
  RooHist* hpull = massPlot->pullHist("massPlot", "modelPlot");
  RooPlot* pullPlot = works1->var("mass")->frame(Title("Pull Distribution"));
  pullPlot->addPlotable(hpull, "P");
  pullPlot->GetYaxis()->SetLabelSize(0.13);
  pullPlot->Draw();
  line_pull->Draw("same");

  Double_t chi2 = 0.;
  Double_t *ypull = hpull->GetY();
  Double_t Npullbin = 0;
  for(Int_t ibin = 0; ibin < Nmassbins; ibin++){
    if(ypull[ibin] ==0) continue;
    chi2 += TMath::Power(ypull[ibin],2);
    Npullbin++;
  }
  Int_t Nfitpar = Result->floatParsFinal().getSize();
  Int_t ndf = Npullbin - Nfitpar;

  TLatex* NormChi2tex = new TLatex();
  FormLatex(NormChi2tex, 42, 0.13);
  NormChi2tex->DrawLatex(0.15, 0.95, Form("#chi^{2}/ndf: %3.f/%d", chi2, ndf));
  WriteMessage("Pull distribution is dOnE !!!");

  pad_leg->cd();
  RooPlot* legPlot = works1->var("mass")->frame(Name("Fit Results"), Title("Fit Results"));
  RooArgList parList = Result->floatParsFinal();
  parList.Print("v");
  works1->pdf("model")->paramOn(legPlot, Layout(0, 0.93, 0.97), Parameters(parList));
  legPlot->getAttText()->SetTextAlign(11);
  legPlot->getAttText()->SetTextSize(0.05);

  TPaveText* Ptext = (TPaveText*) legPlot->findObject(Form("%s_paramBox", works1->pdf("model")->GetName()));
  Ptext->SetY1(0.01);
  Ptext->SetY2(0.95);
  Ptext->Draw();

  
  WriteMessage("Writting result is dOnE !!!");

  Double_t Yield1S = works1->var("nSig1S")->getVal();
  Double_t Yield1SErr = works1->var("nSig1S")->getError();
  Double_t Yield2S = works1->var("nSig2S")->getVal();
  Double_t Yield2SErr = works1->var("nSig2S")->getError();
  Double_t Yield3S = works1->var("nSig3S")->getVal();
  Double_t Yield3SErr = works1->var("nSig3S")->getError();
  Double_t YieldBkg = works1->var("nBkg")->getVal();

  hYield->SetBinContent(1, Yield1S);
  hYield->SetBinError(1, Yield1SErr);
  hYield->SetBinContent(2, Yield2S);
  hYield->SetBinError(2, Yield2SErr);
  hYield->SetBinContent(3, Yield3S);
  hYield->SetBinError(3, Yield3SErr);

  Double_t meanout = works1->var("mean1S")->getVal();
  Double_t sigma1out = works1->var("sigma1S_1")->getVal();
  Double_t sigma2out = (works1->var("x1S")->getVal())*sigma1out;
  Double_t fracout = works1->var("frac")->getVal();
  Double_t sigmaout = TMath::Sqrt(fracout*sigma1out*sigma1out+(1-fracout)*sigma2out*sigma2out);

  TF1* Sgnfc1S;
  TF1* Sgnfc2S;
  TF1* Sgnfc3S;

  Sgnfc1S = works1->pdf("twoCB1S")->asTF(*(works1->var("mass")));
  Sgnfc2S = works1->pdf("twoCB2S")->asTF(*(works1->var("mass")));
  Sgnfc3S = works1->pdf("twoCB3S")->asTF(*(works1->var("mass")));

  TF1* Bkgfc;
  Bkgfc = works1->pdf("bkgErf")->asTF(*(works1->var("mass")));

  Double_t TIntgr1S = Sgnfc1S->Integral(RangeLow, RangeHigh);
  Double_t TIntgr2S = Sgnfc2S->Integral(RangeLow, RangeHigh);
  Double_t TIntgr3S = Sgnfc3S->Integral(RangeLow, RangeHigh);
  Double_t TIntgrBkg = Bkgfc->Integral(RangeLow, RangeHigh);
  Double_t IntgrSig = Sgnfc1S->Integral(meanout-2*sigmaout, meanout+2*sigmaout);
  Double_t IntgrBkg = Bkgfc->Integral(meanout-2*sigmaout, meanout+2*sigmaout);
  Double_t Significance =(Yield1S*IntgrSig/TIntgr1S/TMath::Sqrt(((Yield1S*IntgrSig/TIntgr1S)+(YieldBkg*IntgrBkg/TIntgrBkg))));

  TH1D* hfrac = new TH1D("hfrac", "", 6, 0, 6);
  hfrac->SetBinContent(1, Sgnfc1S->Eval(U1S_mass));
  hfrac->SetBinContent(2, Bkgfc->Eval(U1S_mass));
  hfrac->SetBinContent(3, Sgnfc1S->Integral(9.3, 9.6));
  hfrac->SetBinContent(4, Bkgfc->Integral(9.3, 9.6));
  hfrac->SetBinContent(5, Sgnfc1S->Integral(9.1, 9.8));
  hfrac->SetBinContent(6, Bkgfc->Integral(9.1, 9.8));

  TH1D* hfracdist = new TH1D("hfracdist","",20, 9, 10);
  for(Int_t i =0; i <20; i++){
    hfracdist->SetBinContent(i+1, Sgnfc1S->Eval(9+0.05*i)/(Sgnfc1S->Eval(9+0.05*i)+Bkgfc->Eval(9+0.05*i)));
  }
  FILE* ftxt = 0;
  if(ftxt != NULL){
    fprintf(ftxt, "mean sigma1 sigma2 fraction totsigma totsig totbkg sig bkg nsig nbkg significance \n");
    fprintf(ftxt, "%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f \n", meanout, sigma1out, sigma2out, fracout, sigmaout, TIntgr1S, TIntgrBkg, IntgrSig, IntgrBkg, Yield1S, YieldBkg, Significance);
    fprintf(ftxt, "mean  U1sigma1  fraction  alpha  n  Erfmean  Erfsigma  Erfp0 \n");
    fprintf(ftxt, "%.3f   %.3f   %.3f   %.3f   %.3f   %.3f   %.3f   %.3f \n", Yield1S, Yield2S, Yield3S, YieldBkg, TIntgr1S, TIntgr2S, TIntgr3S, TIntgrBkg);
  }
  

  c1->SaveAs(Form("%s/MassDistribution_pt_%d-%d_rap_%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_%s%d_%s%.4f-%.4f_%s%.4f.pdf",massDIR.Data(), (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag,"BDT",1,"cut",cutBDTlow, cutBDThigh,"vp",cutQVP));
  c1->SaveAs(Form("%s/png/MassDistribution_pt_%d-%d_rap_%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_%s%d_%s%.4f-%.4f_%s%.4f.png",massDIR.Data(), (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag,"BDT",1,"cut",cutBDTlow, cutBDThigh,"vp",cutQVP));
  TCanvas* c1_tmp = (TCanvas*) c1->Clone("ylogc1");
  c1_tmp->SetLogy();
  c1_tmp->Modified();
  c1_tmp->SaveAs(Form("%s/MassDistribution_pt_%d-%d_rap_%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_%s%d_%s%.4f-%.4f_%s%.4f.pdf",massDIRl.Data(), (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag,"BDT",1,"cut",cutBDTlow, cutBDThigh,"vp",cutQVP));
  TH1D* hmass = new TH1D("hmass", ";M (GeV/c^2);Counts", Nmassbins, RangeLow, RangeHigh);
  reducedDS->fillHistogram(hmass, (*works1->var("mass")));
  FormTH1Marker(hmass, 0, 0, 1.4);
  c2->cd();
  hmass->Draw("pe");
  lumiText(0.56, 0.92);
  TLatex* lt1 = new TLatex();
  FormLatex(lt1, 12, 0.04);
  lt1->DrawLatex(0.6, 0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
  lt1->DrawLatex(0.6, 0.75, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int) ptMin, (int) ptMax));

  c2->SaveAs(Form("%s/WithoutFit_pt_%d-%d_rap_%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_%s%d_%s%.4f-%.4f_%s%.4f.pdf",massDIR2.Data(),(int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10),  Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag,"BDT",1,"cut",cutBDTlow, cutBDThigh,"vp",cutQVP));

  fout->cd();
  RooWorkspace* wtmp = new RooWorkspace("workspace");
  wtmp->import(*works1->var("mass")); 
  wtmp->import(*works1->pdf("model")); 
  wtmp->import(*works1->data("reducedDS")); 
  wtmp->Write();
  Result->Write();
  massPlot->Write();
  hYield->Write();
  hmass->Write();
  Sgnfc1S->Write();
  Sgnfc2S->Write();
  Sgnfc3S->Write();
  hfrac->Write();
  hfracdist->Write();

 
}

