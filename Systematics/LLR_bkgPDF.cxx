#include <iostream>
#include "TMath.h"
#include "TROOT.h"
#include "TFile.h"
#include "RooFit.h"
#include "../BDT/yield_eff_signif.cxx"

static int signif_formula = 2;

double LLR_bkgPDF(RooFitResult* res1, RooFitResult* res2);
double LLR_bkgPDF(std::string type1, std::string type2, long ts, double pl, double ph, int cl, int ch, double blow, double bhigh, double state, double ylim =2.4);
double LLR_bkgPDF(std::string type1, std::string type2, long ts, double pl, double ph, int cl, int ch, double state, double ylim =2.4, double vcut = 0.00);
double LLR_bkgPDF(RooFitResult* res1, RooFitResult* res2)
{

	const RooArgList res1_parslist = res1->floatParsFinal();
	const RooArgList res2_parslist = res2->floatParsFinal();
	double NLL1 = res1->minNll();
	double NLL2 = res2->minNll();

	int res1_len = res1_parslist.size();
	int res2_len = res2_parslist.size();
	double delta_ndf = fabs(res1_len - res2_len);

	double LR = 2*(NLL1 - NLL2);
	return 1 - ROOT::Math::chisquared_cdf(LR, delta_ndf);
};

double LLR_bkgPDF(std::string type1, std::string type2, long ts, double pl, double ph, int cl, int ch, double blow, double bhigh, double state, double ylim =2.4, double vcut = 0.00){
	binplotter bnull, btest;
	bnull = binplotter(type1, ts, ylim, pl, ph, cl, ch, blow, bhigh, state, false);
	btest = binplotter(type2, ts, ylim, pl, ph, cl, ch, blow, bhigh, state, false);

	auto fitres_null = bnull.res;
	auto fitres_test = btest.res;
	return LLR_bkgPDF(fitres_null, fitres_test);

};

double LLR_bkgPDF(std::string type1, std::string type2, long ts, double pl, double ph, int cl, int ch, double state, double ylim =2.4, double vcut = 0.00){
	double blow = Get_BDT(ts, state, (int) pl, (int) ph, cl, ch, vcut,  ylim, signif_formula);
	double bhigh = 1;
	return LLR_bkgPDF(type1, type2, ts, pl ,ph ,cl, ch, blow, bhigh, state, ylim, vcut);
};
