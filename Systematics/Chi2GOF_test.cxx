//Goodness of Fit decision macro, Chebyshev bkg order must be defined prior to this test
#pragma once
#include "../LLR_CCorder.h"
#include "../BDT/bininfo.h"

bool cmp(const std::pair<double, string> a, const std::pair<double, string> b){
	return a.first <= b.first;
};

std::vector<std::pair<double, string> > Chi2GOF_test(ana_bins ab){
	long ts = 9999999999;
	int CCO = getNomBkgO(ab);
	string fittype="";
	fittype = (strcmp(ab.bin_attr.c_str(), "c") ==0) ? fittype+"FF" : fittype+"GC";

	string typeCC = Form("CB3:CC%d:%s", CCO, fittype.c_str());
	string typeEE = Form("CB3:EE:%s", fittype.c_str());
	string typeEX = Form("CB3:EX:%s", fittype.c_str());

	string fitCC = GetFit(__FITRESLATEST, false, typeCC, ts, ab.state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	string fitEE = GetFit(__FITRESLATEST, false, typeEE, ts, ab.state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	string fitEX = GetFit(__FITRESLATEST, false, typeEX, ts, ab.state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	
	auto getChi2NDF = [&](string fileN){
		TFile* x = TFile::Open(fileN.c_str());
		if(x == nullptr) return 999.;
		RooWorkspace *ws_res = (RooWorkspace*) x->Get("workspace");
		string name_fitres = (strcmp(fittype.c_str(),"GC")==0) ? "fitresult_model_gc_reducedDS" : "fitresult_model_reducedDS";
		string name_pdf = (strcmp(fittype.c_str(),"GC")==0) ? "model_gc" : "model";
		RooPlot* plt = ws_res->var("mass")->frame(120); //frame(NmassBin)
		ws_res->data("reducedDS")->plotOn(plt);
		ws_res->pdf(name_pdf.c_str())->plotOn(plt);
		RooFitResult* fit_res = (RooFitResult*) x->Get(name_fitres.c_str());
		int nFitParam = (fit_res->floatParsFinal()).size();
		double Chi2NDF = plt->chiSquare(nFitParam);
		x->Close();
		return Chi2NDF;
	};

	double chi2CC = getChi2NDF(fitCC);
	double chi2EE = getChi2NDF(fitEE);
	double chi2EX = getChi2NDF(fitEX);
	std::vector<std::pair< double, string> > c2vec = {
		{chi2CC, Form("CC%d",CCO)},
		{chi2EE, "EE"},
		{chi2EX, "EX"},
	};
	sort(c2vec.begin(), c2vec.end(), cmp);
	return c2vec;

}
