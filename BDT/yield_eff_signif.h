#include <iostream>
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
  TFile* file1 = new TFile(Form("../Yield/Yield_%ld_%s_pt_%d-%d_rap_-%d-%d_120bin_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", ts, fitdir.c_str(),pl,ph, ylim10, ylim10,cl, ch, blow, bhigh, vcut),"read");

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
  TFile* file1 = new TFile(Form("../Yield/Yield_%ld_%s_pt_%d-%d_rap_-%d-%d_120bin_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", ts, fitdir.c_str(),pl,ph, ylim10, ylim10,cl, ch, blow, bhigh, vcut),"read");
  
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
