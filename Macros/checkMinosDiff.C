#include "../BDT/bininfo.h"
#include "../script_tools.h"
#include "../plots/measurement.cxx"

#define DEBUG

void checkMinosDiff(){
	long ts1 = 200019111111;
	long ts2 = 2100019111111;
	int pl = 0;
	int ph = 4;

	ana_bins ab1 = ana_bm_comb_ub["3p"][0];
	ana_bins ab2 = ana_bm_comb_ub_ib["3p"][0];
	double bl1 = Get_BDT(ts_alias(ts1), 3, 3, pl, ph, pl, ph, 0, 181);
	double bl2 = Get_BDT(ts_alias(ts2), 3, 3, 0, 30, pl, ph, 0, 181);
	binplotter bp1 = binplotter(ts1, ab1, "CB3:EE:GCMINOS", bl1);
	binplotter bp2 = binplotter(ts2, ab2, "CB3:EE:GCMINOS", bl2);

	auto eff1 = bp1.get_eff(3, 0);
	auto eff2 = bp2.get_eff(3, 0);

#if defined DEBUG
	std::cout << bl1 << " \n" << bl2 << std::endl;
#endif

	string query_file1 = GetFit(11, false, "CB3:EE:GCMINOS",ts1, 3, 3, pl, ph, 0, 181, bl1, 1, pl, ph, 0,"");
	string query_file2 = GetFit(11, false, "CB3:EE:GCMINOS",ts2, 3, 3, pl, ph, 0, 181, bl2, 1, 0, 30, 0,"");
#if defined DEBUG
	std::cout << query_file1.c_str() << " \n" << query_file2.c_str() << std::endl;
#endif

	TFile* f1 = TFile::Open(query_file1.c_str());
	TFile* f2 = TFile::Open(query_file2.c_str());

	auto fitres1 = (RooFitResult*) f1->Get("fitresult_model_gc_reducedDS");
	auto fitres2 = (RooFitResult*) f2->Get("fitresult_model_gc_reducedDS");
	
	auto varres1 = fitres1->floatParsFinal(); 
	auto varres2 = fitres2->floatParsFinal(); 

	int idx1  = varres1.index("nSig3S");
	int idx2  = varres2.index("nSig3S");
	
	RooRealVar* var1 = (RooRealVar*) &varres1[idx1];
	RooRealVar* var2 = (RooRealVar*) &varres2[idx2];
#if defined DEBUG
	var1->Print();
	var2->Print();
#endif
	var1->setVal(var1->getVal() / eff1.first );
	var2->setVal(var2->getVal() / eff2.first );
	var1->setAsymError( var1->getAsymErrorLo() / eff1.first, var1->getAsymErrorHi() / eff1.first );
	var2->setAsymError( var2->getAsymErrorLo() / eff2.first, var2->getAsymErrorHi() / eff2.first );
	std::cout << "Nominal :" << std::endl;
	var1->Print();
	std::cout << Form(", Minos Error : %.4f, %.4f", var1->getAsymErrorLo(), var1->getAsymErrorHi() ) << std::endl;
	std::cout << "New  :" << std::endl;
	var2->Print();
	std::cout << Form(", Minos Error : %.4f, %.4f", var2->getAsymErrorLo(), var2->getAsymErrorHi() ) << std::endl;
};
