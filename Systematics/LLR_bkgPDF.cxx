#include <iostream>
#include "TMath.h"
#include "TROOT.h"
#include "TFile.h"
#include "RooFit.h"
#include "../BDT/yield_eff_signif.cxx"
#include "stat.cxx"

static int signif_formula = 2;

std::pair<double, std::pair<double, double> > LLR_bkgPDF(RooFitResult* res1, RooFitResult* res2);
std::pair<double, std::pair<double, double> >  LLR_bkgPDF(std::string type1, std::string type2, long ts, double pl, double ph, int cl, int ch, double blow, double bhigh, int train_state, int sig_state, double ylim =2.4);
std::pair<double, std::pair<double, double> > LLR_bkgPDF(std::string type1, std::string type2, long ts, double pl, double ph, int cl, int ch, int train_state, int sig_state, double ylim =2.4, double vcut = 0.00);


std::pair<double, std::pair<double, double> > LLR_bkgPDF(RooFitResult* res1, RooFitResult* res2)
{

	const RooArgList res1_parslist = res1->floatParsFinal();
	const RooArgList res2_parslist = res2->floatParsFinal();
	double NLL1 = res1->minNll();
	double NLL2 = res2->minNll();
	std::pair<double, double> nllp = {NLL1, NLL2};

	int res1_len = res1_parslist.size();
	int res2_len = res2_parslist.size();
	double delta_ndf = fabs(res1_len - res2_len);

	double LR = 2*(NLL1 - NLL2);
	return {1 - ROOT::Math::chisquared_cdf(LR, delta_ndf), nllp};
};

std::pair<double, std::pair<double, double> > LLR_bkgPDF(std::string type1, std::string type2, long ts, double pl, double ph, int cl, int ch, double blow, double bhigh, int train_state, int sig_state, int bpl, int bph, double ylim =2.4, double vcut = 0.00){
	std::unique_ptr<binplotter> bnull, btest;
	bnull.reset( new binplotter(type1, ts, ylim, pl, ph, cl, ch, blow, bhigh, bpl, bph, train_state, sig_state, false));
	btest.reset( new binplotter(type2, ts, ylim, pl, ph, cl, ch, blow, bhigh, bpl, bph, train_state, sig_state, false));

	auto fitres_null = bnull->res;
	auto fitres_test = btest->res;

	auto calc_res =  LLR_bkgPDF(fitres_null, fitres_test);

	return calc_res;

};

std::pair<double, std::pair<double, double> > LLR_bkgPDF(std::string type1, std::string type2, long ts, double pl, double ph, int cl, int ch, int train_state, int sig_state, int bpl, int bph, double ylim =2.4, double vcut = 0.00){
	double blow = Get_BDT(ts_alias(ts), train_state, sig_state, bpl, bph, (int) pl, (int) ph, cl, ch, vcut,  ylim, signif_formula);
	double bhigh = 1;
	auto res =  LLR_bkgPDF(type1, type2, ts, pl ,ph ,cl, ch, blow, bhigh, train_state, sig_state, bpl, bph, ylim, vcut);
	return res;
};

std::pair<double, std::pair<double, double> > LLR_bkgPDF(std::string type1, std::string type2, long ts, ana_bins x){
	return LLR_bkgPDF(type1, type2, ts, x.pl, x.ph, x.cl, x.ch, x.train_state, x.state, x.bpl, x.bph, 2.4, 0.00);
}

std::pair<double, std::pair<double, double> > LLR_bkgPDF(std::string type1, std::string type2, long ts, ana_bins x, double bl){
	return LLR_bkgPDF(type1, type2, ts, x.pl, x.ph, x.cl, x.ch, bl, 1., x.train_state, x.state, x.bpl, x.bph, 2.4, 0.00);
}
