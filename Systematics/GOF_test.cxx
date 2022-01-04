//Goodness of Fit decision macro, Chebyshev bkg order must be defined prior to this test
#pragma once
//#include "../LLR_CCorder.h"
#include "LLR_bkgPDF.cxx"
#include "../BDT/bininfo.h"
#include "stat.cxx"
struct ana_bins;

bool cmp(const std::pair<double, string> a, const std::pair<double, string> b){
	return a.first <= b.first;
};
bool cmp_rev(const std::pair<double, string> a, const std::pair<double, string> b){
	return a.first >= b.first;
};

std::vector<std::pair<double, string> > Chi2GOF_function(ana_bins ab, string test1, string test2, string test3){
	long ts = _TS;

	int CCO = getNomBkgO(ab);
	string fittype="";
	fittype = (strcmp(ab.bin_attr.c_str(), "c") ==0) ? fittype+"FF" : fittype+"GC";

	string typeCC = Form("CB3:%s:%s", test1.c_str(), fittype.c_str());
	string typeEE = Form("CB3:%s:%s", test2.c_str(), fittype.c_str());
	string typeEX = Form("CB3:%s:%s", test3.c_str(), fittype.c_str());

	string fitCC = GetFit(__FITRESLATEST, false, typeCC, ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	string fitEE = GetFit(__FITRESLATEST, false, typeEE, ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	string fitEX = GetFit(__FITRESLATEST, false, typeEX, ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	
	auto getChi2NDF = [&](string fileN){
		std::cout << fileN.c_str() << std::endl;
		TFile* x = TFile::Open(fileN.c_str());
		if(x == nullptr) return 999.;
		RooWorkspace *ws_res = (RooWorkspace*) x->Get("workspace");
		string name_fitres = (strcmp(fittype.c_str(),"GC")==0) ? "fitresult_model_gc_reducedDS" : "fitresult_model_reducedDS";
		string name_pdf = (strcmp(fittype.c_str(),"GC")==0) ? "model_gc" : "model";
		std::cout << "Fit res name : " << name_fitres.c_str() << ", PDF name : " << name_pdf.c_str() << std::endl;
		RooPlot* plt = ws_res->var("mass")->frame(120); //frame(NmassBin)
		ws_res->data("reducedDS")->plotOn(plt);
		ws_res->pdf(name_pdf.c_str())->setStringAttribute("fitrange", nullptr);
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
		{chi2CC, test1},
		{chi2EE, test2},
		{chi2EX, test3},
	};
	
	return c2vec;

};

std::vector<std::pair<double, string> > Chi2GOF_test(ana_bins ab){
	long ts = _TS;
	int CCO = getNomBkgO(ab);
	string fittype="";
	fittype = (strcmp(ab.bin_attr.c_str(), "c") ==0) ? fittype+"FF" : fittype+"GC";

	string typeCC = Form("CC%d", CCO);
	string typeEE = Form("EE");
	string typeEX = Form("EX");
	return Chi2GOF_function(ab, typeCC, typeEE, typeEX);
};

#define statc std::pair<string, std::pair<double, int> >
#define statw std::pair<statc, double>
std::vector<std::pair<double, string> > AICGOF_function(ana_bins ab, string test1, string test2, string test3, string opt){
	long ts = _TS;
	int CCO = getNomBkgO(ab);
	string test4 = Form("CC%d", CCO+1);
	string fittype="";
	fittype = (strcmp(ab.bin_attr.c_str(), "c") ==0) ? fittype+"FF" : fittype+"GC";

	string type1 = Form("CB3:%s:%s", test1.c_str(), fittype.c_str());
	string type2 = Form("CB3:%s:%s", test2.c_str(), fittype.c_str());
	string type3 = Form("CB3:%s:%s", test3.c_str(), fittype.c_str());
	string type4 = Form("CB3:%s:%s", test4.c_str(), fittype.c_str());

	string fit1 = GetFit(__FITRESLATEST, false, type1, ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	string fit2 = GetFit(__FITRESLATEST, false, type2, ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	string fit3 = GetFit(__FITRESLATEST, false, type3, ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	string fit4 = GetFit(__FITRESLATEST, false, type4, ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	
	auto getAICcomp = [&](string fileN){
		std::cout << fileN.c_str() << std::endl;
		TFile* x = TFile::Open(fileN.c_str());
		if(x == nullptr) return (std::pair<double, int>){999,999};
		string name_fitres = (strcmp(fittype.c_str(),"GC")==0) ? "fitresult_model_gc_reducedDS" : "fitresult_model_reducedDS";
		RooFitResult* fit_res = (RooFitResult*) x->Get(name_fitres.c_str());
		int nFitParam = (fit_res->floatParsFinal()).size();
		double Nll = fit_res->minNll();
		x->Close();
		return std::pair<double, int>{Nll, nFitParam};
	};

	statc stat1 = {test1, getAICcomp(fit1)};
	statc stat2 = {test2, getAICcomp(fit2)};
	statc stat3 = {test3, getAICcomp(fit3)};
	statc stat4 = {test4, getAICcomp(fit4)};
	//# 'notuse' option calls positive likelihood to fail every test, if ChebyShev is off +1 order is also cancelled
	if(opt.find("notuse")!=std::string::npos){
		if(opt.find("1")!=std::string::npos){
			stat1 = {test1, {999,999}};
			if(test1.find("CC") != std::string::npos ) stat4 = {test4, {999,999}};
		}
		if(opt.find("2")!=std::string::npos){
			stat2 = {test2, {999,999}};
			if(test2.find("CC") != std::string::npos ) stat4 = {test4, {999,999}};
		}
		if(opt.find("3")!=std::string::npos){
			stat3 = {test3, {999,999}};
			if(test3.find("CC") != std::string::npos ) stat4 = {test4, {999,999}};
		}

	}
	//AIC test to determine the nominal background PDF, takes 2 steps
	//Step 1) Compare AIC results between ErfExp & Exp, choice of better probability
	//Step 2) AIC test between choice from step 1) with Chebyshev PDF, the Chebysev function order is determined by LR test from 1st to 6th order
	//# step 1. Test ErfExp vs. Exp
	dat AIC_res_step1 = AIC_statistic(
		stat1.second.first, stat1.second.second,
		stat2.second.first, stat2.second.second
	);
	// step 1 results
	////Winner
	statw stat_step1 = (AIC_res_step1[1] > 0.68) ? statw{stat2, AIC_res_step1[1]} : statw{stat1, AIC_res_step1[0]};
	////Looser
	statw stat_step1NOT = (AIC_res_step1[1] <= 0.68 ) ? statw{stat2, AIC_res_step1[1]} : statw{stat1, AIC_res_step1[0]};
//	statw stat_step1 = (AIC_res_step1[0] > AIC_res_step1[1]) ? statw{stat1, AIC_res_step1[0]} : statw{stat2, AIC_res_step1[1]};
//	////Looser
//	statw stat_step1NOT = (AIC_res_step1[0] <= AIC_res_step1[1]) ? statw{stat1, AIC_res_step1[0]} : statw{stat2, AIC_res_step1[1]};
	std::cout << Form("[GOF] AIC test 1. : %.5f & %.5f : %s & %s", stat_step1.second, stat_step1NOT.second, stat_step1.first.first.c_str(), stat_step1NOT.first.first.c_str()) << std::endl;

	//# step 2. Test step 1 vs. ChebyShev ( > 95 % significance ) (Nominal)
	dat AIC_res_step2 = AIC_statistic(
		stat_step1.first.second.first, stat_step1.first.second.second,
		stat3.second.first, stat3.second.second
	);
	// step 2 results
	////Winner
	statw stat_step2 = ( AIC_res_step2[1] < 0.95) ? statw{stat_step1.first, AIC_res_step2[0]} : statw{stat3, AIC_res_step2[1]};
	////Looser
	statw stat_step2NOT = (AIC_res_step2[1] >= 0.95 ) ? statw{stat_step1.first, AIC_res_step2[0]} : statw{stat3, AIC_res_step2[1]};

	//# step 3. Test step 1 looser vs. step 2 winner (Nominal)
	dat AIC_res_step3 = AIC_statistic(
		stat_step1NOT.first.second.first, stat_step1NOT.first.second.second,
		stat_step2.first.second.first, stat_step2.first.second.second
	);
	statw stat_step3NOT =  statw{stat_step1NOT.first, AIC_res_step3[0]} ;

	//# step 4. Test ChebyShev +1 order vs. step2 winner (Nominal)
	dat AIC_res_step4 = AIC_statistic(
		stat4.second.first, stat4.second.second,
		stat_step2.first.second.first, stat_step2.first.second.second
	);
	statw stat_step4NOT = statw{stat4, AIC_res_step4[0]};
	// if nominal is Chebyshev, use first alternative as +1 order, this will be checked in sorting stage
	if( stat_step2.first.first.find("CC") != std::string::npos ) stat_step4NOT = {stat4 , 1.};
	
	std::vector<std::pair< double, string > > gof_alt_vec = {
		{stat_step2NOT.second, stat_step2NOT.first.first},
		{stat_step3NOT.second, stat_step3NOT.first.first},
		{stat_step4NOT.second, stat_step4NOT.first.first},
	};
	// sort alternatives by p-value
	std::sort(gof_alt_vec.begin(), gof_alt_vec.end(), cmp_rev );

	std::vector<std::pair< double, string > > gof_vec = {
		{stat_step2.second, stat_step2.first.first},
		gof_alt_vec[0],
		gof_alt_vec[1],
		gof_alt_vec[2],
	};
	return gof_vec;

};
std::vector<std::pair<double, string> > AICGOF_test(ana_bins ab){
	long ts = _TS;
	int CCO = getNomBkgO(ab);
	string fittype="";
	fittype = (strcmp(ab.bin_attr.c_str(), "c") ==0) ? fittype+"FF" : fittype+"GC";

	string typeCC = Form("CC%d", CCO);
	string typeEE = Form("EE");
	string typeEX = Form("EX");
	return AICGOF_function(ab, typeEE, typeEX, typeCC, ab.bkgopt);
};
