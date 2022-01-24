#ifndef YIELD_EFF_SIGNIF_H
#define YIELD_EFF_SIGNIF_H

#include <iostream>
#include <cstdlib>
#include "TROOT.h"
#include "RooFit.h"
#include "./EffCalc/openEffhist.C"
#include "./EffCalc/openEffhist_SYS.C"
#include "./EffCalc/DNDPT/openEffhist_SYSDPT.C"
#include "./EffCalc/DNDPT/openEffhist_SYSDPT_NN.C"
#include "./EffCalc/noDNDPT/openEffhist_SYSNODPT.C"
#include "bininfo.h"


class binplotter
{
  public:
	binplotter();
	binplotter(ana_bins x, int _bdtptMin, int _bdtptMax);
  	binplotter(std::string _type, long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _vcut, double _blow, double _bhigh, int _bdtptMin, int _bdtptMax, int _train_state = 3, int _target_state =3, bool find_bdt = false, bool eff_old = false);
//  	binplotter(std::string _type, long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _blow, double _bhigh, int _bdtptMin, int _bdtptMax, int _train_state = 3,  int _target_state = 3, bool find_bdt = false, bool eff_old = false);
  	binplotter(std::string _type, long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _blow, double _bhigh, int _bdtptMin, int _bdtptMax, int _train_state = 3, int _target_state =3, bool find_bdt = false, bool eff_old = false);
	void init(bool get_bdt= true);
	void set_params(double _vcut);
	void set_params(string _fitfunc);
	void set_params(string _fitfunc, double _vcut);
	void dump();
	~binplotter();
	RooRealVar get_yield(int state =3);
	RooRealVar get_bkg(int state = 3);
	std::pair<double, double> get_eff(int state =3, bool getNum = false);
	std::vector<double> get_eff_NN(int state =3);
	std::pair<double, double> get_eff_sysdpt(int state =3, std::string what = "", bool getNum = false);
	RooRealVar yield_eff();
	RooRealVar get_frac(int state);
	RooRealVar return_23s_frac(bool withEff = false);
	RooRealVar getsignificance();
	RooRealVar* NS;
	RooRealVar* NB;
	bool refit = false;
	RooRealVar yield1S, yield2S, yield3S, frac2S, frac3S;
	std::string type;
	double ylim, blow, bhigh;
	TFile* file1;
	RooFitResult* res = nullptr;
	RooWorkspace* worksp;
  	
  private:
  	long ts;
	int pl, ph,cl, ch, train_state, target_state, bdtptMin, bdtptMax;
	bool eff_old;
	double vcut =0.00;
	TString MupT = "3p5";
	string Trig ="S13";
	std::string fittype = "freefit";
	string filename;
	string fitfunc="";//"_CC3";

};

#endif
