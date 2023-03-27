#include "../upsilonAna.cxx"
#include "../.workdir.h"
#if defined _TS
	#include "../Systematics/GOF_test.cxx"

#include "projectionTable.h"

RooRealVar getRAAValue(std::pair <int, int>);
// Double Ratio Finding Function
//////////////////////////////////////////////////////////////////////////////
//RooRealVar getRAAValue(bool inc_pp_stat, std::pair <int, int> cbpair, std::pair<double, double> ptpair = {0,30},std::string type = "CB3:CC2:GC", double bdtlow_val = -2, int bdtptMin = 0 , int bdtptMax = 30, int train_state = 3, int state =3, int getPre = 0,long ts =9999999999, bool stdvcut = false, bool eff_old = false){
RooRealVar getRAAValue(bool inc_pp_stat, ana_bins ab, std::string type = "CB3:CC2:GC", double custom_bl  = -2, double custom_bh = 1, int getPre = 0,long ts =9999999999, bool stdvcut = false, bool eff_old = false, int ofstate = -1, int sc = 0){
	if(ofstate == -1) ofstate = ab.state;
	int cl, ch, pl, ph, state, train_state, bpl, bph;
	cl = ab.cl; ch = ab.ch;
	pl = ab.pl; ph = ab.ph;
	bpl = ab.bpl; bph = ab.bph;
	state = ab.state; train_state = ab.train_state;
	double val_bdt_nom;
	if(custom_bl < -1 )val_bdt_nom= Get_BDT(ts_alias(ts), ab);
	double bdt_upper =custom_bh;
	std::cout << "[getDRV] val_bdt_nom : " << val_bdt_nom << std::endl;
	
	double ylim = 2.4;
	if(custom_bl >= -1 ) val_bdt_nom = custom_bl;
	
	binplotter* bp ;
	
	double app_cutQVP = (stdvcut) ? 0.01 : 0.0000;
	bp = new binplotter(type,ts, ylim, (double) pl, (double) ph, cl, ch, app_cutQVP, val_bdt_nom, bdt_upper, bpl, bph, train_state, state, false, eff_old);
	
	RooRealVar _y = bp->get_yield(ofstate);
	if(getPre==2) return _y;
	RooRealVar _yacc = upsi::getacceptance(pl,ph, (double) -1*ylim, ylim, 3.5, ofstate);
	auto _yeff_pair = bp->get_eff(ofstate);
	double _yeff = _yeff_pair.first;
	RooRealVar yAA, yPP ;
	yAA = RooRealVar(Form("corrY%dyield",ofstate), Form("corrected %dS yield",ofstate), _y.getVal()/(_yacc.getVal()*_yeff));
	std::cout <<"##Yield "<<state<<"S Corrected y/acc eff: "<< yAA.getVal() << ", Efficiency: " << _yeff << ", Acceptance: " << _yacc.getVal() << std::endl;
	yAA.setError(_y.getError()/(_yacc.getVal()*_yeff ));
	std::cout << "\n\n\n YAA ERROR : " << yAA.getError() << "\n\n" << std::endl;
	if(getPre==1) return yAA;
	TFile* file_pp =TFile::Open(Form("/home/CMS/Analysis/HIN21007/Upsilon3S_pp2017Ref/Results/results_%dS.root",ofstate));
	std::cout << file_pp->GetName() << std::endl;
	
	TH1D *h_cs_pp = (!(pl == 0 && ph == 30)) ? (TH1D*) file_pp->Get("hptData") : (TH1D*) file_pp->Get("hintData");
	
	double cs_pp, cs_err;
	if((pl == 0 && ph == 30 )){
	  cs_pp = h_cs_pp->GetBinContent(1);
	  cs_err = h_cs_pp->GetBinError(1);
	}
	else{
	  cs_pp = h_cs_pp->GetBinContent(ab.plot_idx);
	  cs_err = h_cs_pp->GetBinError(ab.plot_idx);
	}

//  double _Ypp_acc = hApp->GetBinContent(1);
//  double _Ypp_eff = hEpp->GetBinContent(1);
//  std::cout << Form("\n[BIN] pp attrib. %.0f-%.0f GeV/c, %d-%d(/2 %%) -> yield : %.3f $\\pm$ %.3f, acc : %.3f, eff : %.3f", ptpair.first, ptpair.second, cbpair.first, cbpair.second, _Ypp, _Ypp_err, _Ypp_acc, _Ypp_eff) << std::endl;
//  if(!(ptpair.first ==0 && ptpair.second ==30 )){
//    _Ypp_eff = hEpp_pt->GetBinContent(hEpp_pt->FindBin((ptpair.first+ptpair.second)/2));
//  }
//  yPP = RooRealVar(Form("corrY%dyieldPP", state) , Form("corrected %dS yield pp", state), _Ypp/(_Ypp_eff*_Ypp_acc));
//  yPP.setError(_Ypp_err/(_Ypp_eff*_Ypp_acc));
//  Double_t cs_pp = 28*TMath::Power(10,9);
	Double_t Nmb = 11968044281.;
	auto taa =glp::Taa[{ab.centl,ab.centh}];
	double lum_scale = 1 *TMath::Power(10,6);
	double n_scale = 4;
	if( ts == 20000000000 ) n_scale = 1;  
	if( ts == 20000000001 ) n_scale = 1;  
	if( ts == 20000000011 ) n_scale = 1;  
	if( ts == 20000000003 ) n_scale = 1;  
	if( ts == 20000000004 ) n_scale = 1;  
	if( ts_alias(ts) != ts) n_scale = 1;

	std::cout << "\n\n\n[n_scale] : " << n_scale  << "\n\n\n" << std::endl;
	
	Double_t trig_presc = 1.0684;
	Double_t taa_Nmb = 4.8*(ph-pl)*taa.first*Nmb/(trig_presc);
	Double_t step_one = (lum_scale)/(taa_Nmb * cs_pp);
	Double_t step_one_err  = -(cs_err*lum_scale)/(taa_Nmb * cs_pp * cs_pp );
	Double_t step_two = step_one * (90./(ab.centh - ab.centl) );
	Double_t step_two_err = step_one_err * (90./(ab.centh - ab.centl));
	Double_t val_RAA = n_scale*step_two*yAA.getVal();
	Double_t val_RAA_err;
	std::cout << "step 2 err and yAA err : " << n_scale* step_two_err*yAA.getVal() << ", " << n_scale*step_two * yAA.getError()/val_RAA << std::endl;
	if(inc_pp_stat) val_RAA_err = TMath::Sqrt(TMath::Power(n_scale*step_two_err* yAA.getVal(),2) + TMath::Power(TMath::Sqrt(n_scale)*step_two * yAA.getError() * projectionStat(sc, 2018),2)); 
	if(!inc_pp_stat) val_RAA_err = step_two * yAA.getError() * projectionStat(sc, 2018); 
	std::cout << std::endl << std::endl << Form(" taa_Nmb: %.3f, cs_pp : %.9f,  step_one: %.16f, step_two %.16f ", taa_Nmb, cs_pp,  (double) step_one, (double) step_two) << std::endl << std::endl;
	std::cout << std::endl << std::endl << "Projected RAA : " << val_RAA << std::endl << std::endl;
	std::cout << "\n\n\n step 2 err and yAA err : " <<  n_scale* step_two_err*yAA.getVal() << ", " << step_two * yAA.getError() << "\n\n" << std::endl;
	
	RooRealVar val_return = RooRealVar("raa","", val_RAA);
	val_return.setError(val_RAA_err);
	
	return val_return;
};

RooRealVar getRAAValue(ana_bins ab, long ts, bool ppstat, int sc, int ofstate = -1, int getPre=0){
	string fittype = (strcmp(ab.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	string bkgtype = AICGOF_test(ab)[0].second;
	string type = Form("CB3:%s:%s", bkgtype.c_str() ,fittype.c_str());
	double bl = Get_BDT(ts_alias(ts), ab);
	return getRAAValue(ppstat, ab, type, -2, 1, getPre, ts, false, false, ofstate, sc);
};

RooRealVar getRAAValueS(ana_bins ab, long ts, bool ppstat, int sc){
	return getRAAValue(ab, ts, ppstat, sc,-1,0);
};

//RooRealVar getRAAValue(ana_bins ab,  double bl, long ts, bool ppstat = 0, int ofstate = -1, int getPre=0){
//	string fittype = (strcmp(ab.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
//	string bkgtype = AICGOF_test(ab)[0].second;
//	string type = Form("CB3:%s:%s", bkgtype.c_str() ,fittype.c_str());
//	double bl = Get_BDT(ts_alias(ts), ab);
//	return getRAAValue(ppstat, ab, type, bl, 1, getPre, ts, false, false, ofstate);
//};


RooRealVar getDRValue(bool inc_pp_stat, ana_bins ab, std::string type = "CB3:CC2:GC", double custom_bl  = -2, double custom_bh = 1, int getPre = 0,long ts =9999999999, bool stdvcut = false, bool eff_old = false, int sc = 0){
	if( ab.state == 2) return RooRealVar("notuse","" , 0) ;
	int cl, ch, pl, ph, state, train_state, bpl, bph;
	cl = ab.cl; ch = ab.ch;
	pl = ab.pl; ph = ab.ph;
	bpl = ab.bpl; bph = ab.bph;
	state = ab.state; train_state = ab.train_state;
	double val_bdt_nom = Get_BDT(ts_alias(ts), ab);
	double bdt_upper =custom_bh;
	std::cout << "[getDRV] val_bdt_nom : " << val_bdt_nom << std::endl;
	
	double ylim = 2.4;
	if(custom_bl >= -1 ) val_bdt_nom = custom_bl;
	
	binplotter* bp ;
	
	double app_cutQVP = (stdvcut) ? 0.01 : 0.0000;
	bp = new binplotter(type,ts, ylim, (double) pl, (double) ph, cl, ch, app_cutQVP, val_bdt_nom, bdt_upper, bpl, bph, train_state, state, false, eff_old);
	// Data - 1. Get Yield and error
	RooRealVar yAA2S = bp->get_yield(2);
	RooRealVar yAA3S = bp->get_yield(3);

	// Data - 2. Get Yield covariance Value
	RooFitResult* fitres = bp->res;
	auto fpf = fitres->floatParsFinal();
	int idx_2s = fpf.index("nSig2S");
	int idx_3s = fpf.index("nSig3S");
	TMatrixTSym<double> cov_m = fitres->covarianceMatrix();
	double cov_23s =  cov_m[idx_2s][idx_3s];

	// Data - 3. Get PP Single Ratio;
//	TFile* ppSR = TFile::Open("/home/CMS/Analysis/Upsilon3S_pp2017Ref/Results/results_3S_SR.root");
	TFile* ppSR = TFile::Open("/home/CMS/Analysis/HIN21007/Upsilon3S_pp2017Ref/Results/results_3S_SR_NonCorrected.root");
	bool isptbin = (ab.bintype ==kPt);
	TH1D* pp_data = ( isptbin ) ? (TH1D*) ppSR->Get("hptData") : (TH1D*) ppSR->Get("hintData");
	double pp_val = ( isptbin ) ? pp_data->GetBinContent(ab.plot_idx) : pp_data->GetBinContent(1); 
	double pp_err = ( isptbin ) ? pp_data->GetBinError(ab.plot_idx) : pp_data->GetBinError(1);

	double n_scale = 4;
	if( ts == 20000000000 ) n_scale = 1;  
	if( ts == 20000000001 ) n_scale = 1;  
	if( ts == 20000000011 ) n_scale = 1;  
	if( ts == 20000000003 ) n_scale = 1;  
	if( ts == 20000000004 ) n_scale = 1;  
	if( ts_alias(ts) != ts) n_scale = 1;

	std::cout << Form("[AASR] n_scale : %.1f pt(%d-%d) cent(%d-%d) val +/- err : ",n_scale, ab.pl, ab.ph, ab.centl, ab.centh) << pp_val << " +/- " << pp_err << std::endl;

	// Calc - 1. Numerator : val = Y2S/Y3S
	double AA_val = yAA3S.getVal() / yAA2S.getVal();

	// Calc - 2. Numerator : err = Y2S/Y3S * SQRT( (E2S/Y2S) ^2  + (E3S/Y3S) ^2 - 2* (COV23S/Y2S*Y3S) )
	double AA_err = AA_val * TMath::Sqrt(
		TMath::Power( (yAA2S.getError()/ yAA2S.getVal() ) ,2) 
		+TMath::Power( (yAA3S.getError() / yAA3S.getVal() ) ,2) 
		- 2 * ( cov_23s / ( yAA2S.getVal() * yAA3S.getVal()) ) 
	);
	// Calc - 2-1. Update err for Blind projection
	AA_err = AA_err / TMath::Sqrt(n_scale);
	
	if(getPre==1){
		std::cout << "Getting only the Single Ratio PbPb" << std::endl;
		RooRealVar theDoubleRatio("SR", "", AA_val);
		theDoubleRatio.setError(AA_err);
	
		return theDoubleRatio;
	}
	std::cout << Form("[AASR] pt(%d-%d) cent(%d-%d) val +/- err : ",ab.pl, ab.ph, ab.centl, ab.centh) << AA_val << " +/- " << AA_err << std::endl;
	
	// Calc - 3. DoubleRatio : val = AASR / ppSR
	double DR_val = AA_val / pp_val;

	// Calc - 4. DoubleRatio : err = AASR / ppSR * SQRT( (AA_err / AA_val) ^2 + (pp_err / pp_val) ^2 )
	double DR_err = DR_val * TMath::Sqrt( TMath::Power( (AA_err / AA_val), 2) + TMath::Power( (pp_err / pp_val), 2) )* projectionStat(sc, 2018);

	RooRealVar theDoubleRatio("DR", "", DR_val);
	theDoubleRatio.setError(DR_err);

	std::cout << theDoubleRatio.getVal() << std::endl;

	return theDoubleRatio;
};

RooRealVar getDRValue(ana_bins ab, long ts, bool ppstat, int sc, int getPre = 0){
	string fittype = (strcmp(ab.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	string bkgtype = AICGOF_test(ab)[0].second;
	string type = Form("CB3:%s:%s", bkgtype.c_str() ,fittype.c_str());
	double bl = Get_BDT(ts_alias(ts), ab);
	return getDRValue(ppstat, ab, type, -2, 1, getPre, ts, false, false, sc);
};

RooRealVar getDRValueS(ana_bins ab, long ts, bool ppstat, int sc){
	return getDRValue(ab, ts, ppstat, sc,0);
};

#endif

RooRealVar getRAWValue(bool inc_pp_stat, ana_bins ab, std::string type = "CB3:CC2:GC", double custom_bl  = -2, double custom_bh = 1, int getPre = 0,long ts =9999999999, bool stdvcut = false, bool eff_old = false, int ofstate = -1){
	if(ofstate == -1) ofstate = ab.state;
	int cl, ch, pl, ph, state, train_state, bpl, bph;
	cl = ab.cl; ch = ab.ch;
	pl = ab.pl; ph = ab.ph;
	bpl = ab.bpl; bph = ab.bph;
	state = ab.state; train_state = ab.train_state;

	double val_bdt_nom;
	double bdt_upper =custom_bh;
	double ylim = 2.4;
	double app_cutQVP = (stdvcut) ? 0.01 : 0.0000;
	if(custom_bl < -1 ) val_bdt_nom= Get_BDT(ts_alias(ts), ab);
	if(custom_bl >= -1 ) val_bdt_nom = custom_bl;
	binplotter* bp ;
	bp = new binplotter(type,ts, ylim, (double) pl, (double) ph, cl, ch, app_cutQVP, val_bdt_nom, bdt_upper, bpl, bph, train_state, state, false, eff_old);
	RooRealVar _y = bp->get_yield(ofstate);
	if(getPre==2) return _y;
	RooRealVar _yacc = upsi::getacceptance(pl,ph, (double) -1*ylim, ylim, 3.5, ofstate);
	auto _yeff_pair = bp->get_eff(ofstate);
	double _yeff = _yeff_pair.first;
	RooRealVar yAA, yPP ;
	yAA = RooRealVar(Form("corrY%dyield",ofstate), Form("corrected %dS yield",ofstate), _y.getVal()/(_yacc.getVal()*_yeff));
	std::cout <<"##Yield "<<state<<"S Corrected y/acc eff: "<< yAA.getVal() << ", Efficiency: " << _yeff << ", Acceptance: " << _yacc.getVal() << std::endl;
	yAA.setError(_y.getError()/(_yacc.getVal()*_yeff ));
	std::cout << "\n\n\n YAA ERROR : " << yAA.getError() << "\n\n" << std::endl;
	if(getPre==1) return yAA;
};
