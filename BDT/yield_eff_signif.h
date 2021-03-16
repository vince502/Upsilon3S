#ifndef YIELD_EFF_SIGNIF_H
#define YIELD_EFF_SIGNIF_H

#include <iostream>
#include <cstdlib>
#include "TROOT.h"
#include "RooFit.h"
#include "./EffCalc/openEffhist.C"

class binplotter
{
  public:
  	binplotter(long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _blow, double _bhigh);
	~binplotter();
	RooRealVar yield_eff();
	double getsignificance();
	double Eff;
  	
  private:
  	long ts;
	double ylim, blow, bhigh;
	int pl, ph,cl, ch;
	double vcut =0.01;
	TString MupT = "3p5";
	string Trig ="S13";
	TString fittype = "freefit";
};
binplotter::binplotter(long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _blow, double _bhigh){
  ts = _ts; ylim = _ylim;  pl = _pl; ph = _ph; cl = _cl; ch = _ch; blow = _blow; bhigh = _bhigh;
};

binplotter::~binplotter(){ return; };

RooRealVar binplotter::yield_eff(){
  string fitdir;
  int ylim10 = (int) (ylim*10);
  if( fittype=="freefit") fitdir = "FF";
  else if (fittype=="DatafixtoMC") fitdir = "DFM";
  string filename = Form("/home/vince402/Upsilon3S/Yield/Yield_%ld_%s_pt_%d-%d_rap_-%d-%d_120bin_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", ts, fitdir.c_str(),pl,ph, ylim10, ylim10,cl, ch, blow, bhigh, vcut);

  if(TFile::Open(filename.c_str(), "open")==nullptr || TFile::Open(filename.c_str(),"read")->IsZombie()){
    std::cout << "Running Fitter for new Yield" << std::endl;
    string command = Form("root -l -b -q \'../MassYieldFit_BDT.C(\"/home/vince402/Upsilon3S/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT.root\", %d, %d, %.1f, %.1f, \"3p5\", \"S13\", %d, %d, %.3f, %.2f, %.2f , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 0.5, 0.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 4, 7, 0.95, 9, 4.0, 8})\'",ts, pl, ph,-1*ylim,ylim, cl, ch, vcut, blow, bhigh);
    int a = system(command.c_str());
  }
  TFile* file1 = new TFile(filename.c_str(),"read");
  std::cout << filename.c_str() << std::endl;

  RooFitResult * res = (RooFitResult*) file1->Get("fitresult_model_reducedDS");
  RooRealVar* Yield3S;
  RooArgList* paramList = (RooArgList*) &res->floatParsFinal();
  for( auto arg : *paramList) {
    if(strcmp(arg->GetName(),"nSig3S")==0){
      Yield3S = (RooRealVar*) arg;
    }
  }

  std::cout << Yield3S->GetName()<< ": " << Yield3S->getVal() << ", Error: " << Yield3S->getError()<< std::endl;
  double bdteff = openEffhist((float) pl, (float) ph, 0, ylim, cl, ch, false, false, false, kTrigUps, ts, blow, bhigh);  
  Eff=bdteff;
  RooRealVar YoverE("YE","Yield over Eff", (Yield3S->getVal()/bdteff), -100, 100000);
  YoverE.setError(Yield3S->getError()/bdteff);
  return YoverE;
};

double binplotter::getsignificance(){
  string fitdir;
  int ylim10 = (int) (ylim*10);
  if( fittype=="freefit") fitdir = "FF";
  else if (fittype=="DatafixtoMC") fitdir = "DFM";
  TFile* file1 = new TFile(Form("/home/vince402/Upsilon3S/Yield/Yield_%ld_%s_pt_%d-%d_rap_-%d-%d_120bin_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", ts, fitdir.c_str(),pl,ph, ylim10, ylim10,cl, ch, blow, bhigh, vcut),"read");
  
  RooWorkspace* works1 = (RooWorkspace*) file1->Get("workspace");
  RooFitResult* Rsult = (RooFitResult*) file1->Get("fitresult_model_reducedDS");

  RooDataSet* dataset = (RooDataSet*) works1->data("reducedDS");
  RooRealVar* vmass = (RooRealVar*) works1->var("mass");
  vmass->setRange("SigReg", 10, 10.7);
  RooAbsPdf* pdf_sig = (RooAbsPdf*) works1->pdf("twoCB3S");
  RooAbsPdf* pdf_bkg = (RooAbsPdf*) works1->pdf("bkgErf");
  double nSig = works1->var("nSig3S")->getVal();
  double nBkg = works1->var("nBkg")->getVal();

  RooAbsReal* integral_sig = pdf_sig->createIntegral(*vmass, RooFit::NormSet(*vmass), RooFit::Range("SigReg"));
  RooAbsReal* integral_bkg = pdf_bkg->createIntegral(*vmass, RooFit::NormSet(*vmass), RooFit::Range("SigReg"));
  double sig_sum = nSig *((double) integral_sig->getVal());
  double bkg_sum = nBkg *((double) integral_bkg->getVal());
  double significance = sig_sum/TMath::Sqrt(sig_sum+bkg_sum);
  return significance;
};

#endif
