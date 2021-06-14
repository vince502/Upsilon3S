#ifndef YIELD_EFF_SIGNIF_H
#define YIELD_EFF_SIGNIF_H

#include <iostream>
#include <cstdlib>
#include "TROOT.h"
#include "RooFit.h"
#include "./EffCalc/openEffhist.C"
#include "bininfo.h"
#include "Get_Optimal_BDT.cxx"

class binplotter
{
  public:
	binplotter();
  	binplotter(std::string _type, long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _blow, double _bhigh);
	void init();
	void set_params(double _vcut);
	void set_params(string _fitfunc);
	void set_params(string _fitfunc, double _vcut);
	void dump();
	~binplotter();
	RooRealVar get_yield();
	std::pair<double, double> get_eff();
	RooRealVar yield_eff();
	RooRealVar getsignificance();
	RooRealVar* NS;
	RooRealVar* NB;
	bool refit = false;
	RooRealVar yield1S, yield2S, yield3S;
	std::string type;
	double ylim, blow, bhigh;
  	
  private:
  	long ts;
	int pl, ph,cl, ch;
	double vcut =0.00;
	TString MupT = "3p5";
	string Trig ="S13";
	TString fittype = "freefit";
	string filename;
	string fitfunc="";//"_CC3";

};
binplotter::binplotter(){
};

binplotter::binplotter(std::string _type, long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _blow, double _bhigh){
  type = _type; ts = _ts; ylim = _ylim;  pl = _pl; ph = _ph; cl = _cl; ch = _ch; blow = _blow; bhigh = _bhigh;

  int nbin = 120;
  if (massrng.find(ts) != massrng.end()) { nbin = (int) ((massrng[ts].second - massrng[ts].first)/0.05); } 
  std::cout << "--------------------Calculated nbin : " << nbin << "----------------------"<< std::endl;
  init();
};

binplotter::~binplotter(){ };

void binplotter::init(){
  auto _fitdir = parser_symbol(type, ":");
  fitfunc = _fitdir[1];
  int ylim10 = (int) (ylim*10);
  int nbin = 120;
  std::string fitdir, markDDiter;
  auto info_string_BDT = info_BDT(ts);
  auto info_fit = parser_symbol(type, ":");
  if (massrng.find(ts) != massrng.end()) { nbin = (int) ((massrng[ts].second - massrng[ts].first)/0.05); } 
  else if (info_string_BDT[1] != "nan") {
    auto m_pair =  parser_symbol(info_string_BDT[1],",");
    double m_low = stod( m_pair[0].c_str()) ;
    double m_high = stod( m_pair[1].c_str()) ;
    nbin = (int) ((m_high - m_low)/0.05) ; 
  }
  fitdir = info_fit[2].c_str();
  blow = Get_Optimal_BDT(ts, pl, ph,(double) -1*ylim, ylim, cl, ch, vcut).first;
  
  filename = Form("/home/vince402/Upsilon3S/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", ts, fitdir.c_str(),Form("_%s",fitfunc.c_str()) ,pl,ph, ylim10, ylim10,nbin, cl, ch, blow, bhigh, vcut);
  if(fitdir.find("DD") != std::string::npos){
    filename = filename.substr(0, filename.length() -5) + Form("_DDiter%d.root",fitdir[4]-48); 
  }

};

void binplotter::set_params(double _vcut){
  vcut = _vcut;
  init();
};
void binplotter::set_params(string _fitfunc){
  fitfunc = _fitfunc;
  init();
};

void binplotter::set_params(string _fitfunc, double _vcut){
  fitfunc = _fitfunc;
  vcut = _vcut;
  init();
};

void binplotter::dump(){
  std::cout << Form(" ts %ld ylim %.4f blow %.4f bhigh %.4f pl %d ph %d cl %d ch %d vcut %.4f MupT %s Trig %s fittype %s filename %s fitfunc %s",ts, ylim, blow, bhigh, pl, ph, cl, ch, vcut, MupT.Data(), Trig.c_str(), fittype.Data(), filename.c_str(), fitfunc.c_str()) << std::endl;
};


RooRealVar binplotter::get_yield(){
  std::cout << "Opening Yield file : " << filename.c_str() << std::endl;
  if(TFile::Open(filename.c_str(), "open")==nullptr || TFile::Open(filename.c_str(),"read")->IsZombie()|| refit){
    std::cout << "Running Fitter for new Yield" << std::endl;
    string command;
    if(strcmp(fitfunc.c_str(),"")==0){ command =Form("root -l -b -q \'../MassYieldFit_BDT.C(\"/home/vince402/Upsilon3S/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT.root\", %d, %d, %.1f, %.1f, \"3p5\", \"S13\", %d, %d, %.3f, %.2f, %.2f , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 0.5, 0.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 4, 7, 0.95, 9, 4.0, 8})\'",ts, pl, ph,-1*ylim,ylim, cl, ch, vcut, blow, bhigh);}
    if(strcmp(fitfunc.c_str(),"_CC3")==0){ command =Form("root -l -b -q \'../MassYieldFit_BDT_CC3.C(\"/home/vince402/Upsilon3S/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT.root\", %d, %d, %.1f, %.1f, \"3p5\", \"S13\", %d, %d, %.3f, %.2f, %.2f , (Double_t[]) {0.13, 1.54, 3.68, 0.56, -0.1, -0.1, 0.0}, (Double_t[]) {0.01, 0.5, 0.5, 0.15, -0.2, -0.2, -0.1}, (Double_t[]) {0.25, 4, 7, 0.95, 0.2,0.2,0.2})\'",ts, pl, ph,-1*ylim,ylim, cl, ch, vcut, blow, bhigh);}
    int a = system(command.c_str());
  }

  TFile* file1 = new TFile(filename.c_str(),"read");
  RooFitResult * res ;
  res = (RooFitResult*) file1->Get("fitresult_model_reducedDS");
  if(res==nullptr)
  {
    res = (RooFitResult*) file1->Get("fitresult_model_gc_reducedDS");
  }
  RooRealVar Yield1S, Yield2S, Yield3S;
  RooArgList* paramList = (RooArgList*) &res->floatParsFinal();
  for( auto arg : *paramList) {
    if(strcmp(arg->GetName(),"nSig1S")==0){
      Yield1S = (RooRealVar)*(RooRealVar*) arg;
    }
    if(strcmp(arg->GetName(),"nSig2S")==0){
      Yield2S = (RooRealVar)*(RooRealVar*) arg;
    }
    if(strcmp(arg->GetName(),"nSig3S")==0){
      Yield3S = (RooRealVar)*(RooRealVar*) arg;
    }
  }
  yield1S = Yield1S;
  yield2S = Yield2S;
  yield3S = Yield3S;
  return Yield3S;

};
std::pair<double, double> binplotter::get_eff(){
  std::pair<double, double> bdteff = openEffhist((float) pl, (float) ph, -1.*(ylim), ylim, cl, ch, true, true, false, kTrigUps, ts, blow, bhigh);  
  return bdteff;
};

RooRealVar binplotter::yield_eff(){
  RooRealVar Yield3S = binplotter::get_yield();
  double bdteff = get_eff().first;
  std::cout << Yield3S.GetName()<< ": " << Yield3S.getVal() << ", Error: " << Yield3S.getError()<< std::endl;
  std::cout << "BDT efficiency of : " << bdteff << std::endl;
  RooRealVar YoverE("YE","Yield over Eff", (Yield3S.getVal()/bdteff), -100, 100000);
  YoverE.setError(Yield3S.getError()/bdteff);
  return YoverE;
};

//RooRealVar binplotter::getsignificance(){
//  string fitdir;
//  TFile* file1 = new TFile(filename.c_str(),"read");
//  
//  RooWorkspace* works1 = (RooWorkspace*) file1->Get("workspace");
//  RooFitResult* Rsult = (RooFitResult*) file1->Get("fitresult_model_reducedDS");
//
//  RooDataSet* dataset = (RooDataSet*) works1->data("reducedDS");
//  RooRealVar* vmass = (RooRealVar*) works1->var("mass");
//  vmass->setRange("SigReg", 10, 10.7);
//  RooAbsPdf* pdf_sig = (RooAbsPdf*) works1->pdf("twoCB3S");
//  RooAbsPdf* pdf_bkg;
//  if(strcmp(fitfunc.c_str(),"")==0)pdf_bkg =(RooAbsPdf*) works1->pdf("bkgErf");
//  if(fitfunc.find("_CC")!=std::string::npos)pdf_bkg =(RooAbsPdf*) works1->pdf("CCBkg");
//  NS = (RooRealVar*) works1->var("nSig3S");
//  NB = (RooRealVar*) works1->var("nBkg");
//  double nSig = works1->var("nSig3S")->getVal();
//  double nBkg = works1->var("nBkg")->getVal();
//  double eSig = works1->var("nSig3S")->getError();
//  double eBkg = works1->var("nBkg")->getError();
//
//  RooAbsReal* integral_sig = pdf_sig->createIntegral(*vmass, RooFit::NormSet(*vmass), RooFit::Range("SigReg"));
//  RooAbsReal* integral_bkg = pdf_bkg->createIntegral(*vmass, RooFit::NormSet(*vmass), RooFit::Range("SigReg"));
//  double sig_sum = nSig *((double) integral_sig->getVal());
//  double sig_err = eSig *((double) integral_sig->getVal());
//  double bkg_sum = nBkg *((double) integral_bkg->getVal());
//  double bkg_err = eBkg *((double) integral_bkg->getVal());
//  double signif = sig_sum/TMath::Sqrt(sig_sum+bkg_sum);
//  double signif_err = (TMath::Power(sig_sum+bkg_sum,-1.5))*(TMath::Sqrt(TMath::Power((0.5*sig_sum+bkg_sum)*sig_err,2)+TMath::Power(0.5*sig_sum*bkg_err,2)));
//  RooRealVar significance("significance","Significance of signal",signif,0,10000);
//  significance.setError(signif_err);
//  return significance;
//};

#endif
