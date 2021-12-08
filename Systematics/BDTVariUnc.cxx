#include "../plots/drawRAAplot.cxx"
#include "Chi2GOF_test.cxx"
#include "sys_wr_helper.cxx"
bool isDR = false;

std::string findtype(int pl, int ph, int cl, int ch){
	std::string fittype = "";
	if( cl ==0 && ch == 181) fittype = "GC";
	else fittype = "FF";
	return fittype;
};

double getBDTVariUnc(ana_bins x){
	int pl, ph, cl, ch, state, bpl, bph;
	pl = x.pl; ph = x.ph; cl = x.cl; ch = x.ch; state = x.state; bpl = x.bpl; bph = x.bph;
	string fittype = (strcmp(x.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	long ts = 9999999999;
    int train_state = state;
	const std::string type_r = "CB3:CC2:DRGC";
	const std::string typenobdt = "CB3:CC4:FF";
	double rapMax = 2.4;
	double rapMin = -2.4;
	double cutQVP = 0.00;
	double blow_ref, ratio;
	///////////////////////////////////////////////////
	auto prep_bdtval = [&] (double blow_ref = -0.3, int _step =0) mutable {
  double cutQVP_noBDT= 0.01;
  std::string fname;

  RooRealVar sb_ratio;
    sb_ratio = get_eff_acc_v2(type_r, ts, rapMax, pl, ph, cl, ch, blow_ref, 1.0, bpl, bph, train_state, 1, state, false);
    double ratio;
    string systype;
    if( _step == 1) {ratio = sb_ratio.getVal() + sb_ratio.getError(); systype = "SYSUP"; }
    if( _step ==-1) {ratio = sb_ratio.getVal() - sb_ratio.getError(); systype = "SYSDOWN"; }
    std::cout << "sb_ratio: " << sb_ratio.getVal() << std::endl;
  auto res_GOB = Get_Optimal_BDT(ts,pl, ph, rapMin, rapMax, cl, ch, cutQVP , ratio, train_state,bpl, bph, "", "S2", systype.c_str());
  auto res_GOB_ref = Get_Optimal_BDT(ts,pl, ph, rapMin, rapMax, cl, ch, cutQVP , sb_ratio.getVal(), train_state,bpl, bph, "", "S2", "SX");
  double res_blow = res_GOB.first;
  double res_blow_ref = res_GOB_ref.first;
  if( res_blow == res_blow_ref ){
       std::cout << "[DBG0831] " <<res_blow << " , " << res_blow_ref<< std::endl;;
       std::cout << "[BDT val Getter] Referencing BDT ratio from Integrated Bin" << std::endl;
       auto sb_ratio_INT = get_eff_acc_v2(type_r, ts, rapMax, 0, 30, 0, 181, blow_ref, 1.0, 0, 30, train_state, 1, state, false);
       double ratio_INT_ref = sb_ratio_INT.getVal();
       double ratio_INT = ratio_INT_ref + ((double) _step * sb_ratio.getError() );
    std::cout << "[DBG0831] " << Form(" INT RATIOS (SB, REF, ratio_INT) %.6f %.6f %.6f" , sb_ratio_INT.getVal(), ratio_INT_ref, ratio_INT) << std::endl;
       double INT_BDT_ref = Get_Optimal_BDT(ts,0, 30, rapMin, rapMax, 0, 181, cutQVP , ratio_INT_ref, train_state, 0, 30, "", "S2", "ST").first;
       double INT_BDT = Get_Optimal_BDT(ts,0, 30, rapMin, rapMax, 0, 181, cutQVP , ratio_INT, train_state, 0, 30 , "", "S2", "SYSNON2").first;
       double bdt_val_ratio = INT_BDT/INT_BDT_ref;
       std::cout << "[DBG0831] BDT_VAL_RATIO: " << bdt_val_ratio << std::endl;
       res_blow = res_blow_ref* bdt_val_ratio;
  }


   std::cout <<"[INFO] " <<res_blow << " is the determined BDT \n\n\n" << std::endl;
   return std::make_pair(res_blow,ratio);

};
//	auto prep_bdtval = [&]  (int _step =0 ) mutable {
//	    auto sb_ratio = get_eff_acc(type_r, typenobdt, ts, rapMax, pl, ph, cl, ch, blow_ref, 1.0, state, 1, state, true);
//	    std::cout << Form("pl, ph, cl, ch, blow_ref, ratio: %d, %d, %d, %d, %.4f, %.6f", pl, ph, cl, ch, blow_ref,  sb_ratio.getVal() ) << std::endl;
//	    if( _step == 1) ratio = sb_ratio.getVal() + sb_ratio.getError();
//	    if( _step == -1) ratio = sb_ratio.getVal() - sb_ratio.getError();
//	    if(_step == 0){ std::cout << "Why fitting Nominal here? " << std::endl;}
//
//	    std::cout << "\n\n\n\nDEBUG : RATIO = "<<ratio<<"\nDEBUG : REF RATIO = "<<sb_ratio.getVal() << ", Error = "<< sb_ratio.getError() << std::endl;
//	    std::string systype;
//	    if(_step ==  1) systype = "SYSUP";
//	    if(_step == -1) systype = "SYSDOWN";
//	   auto res_GOB = Get_Optimal_BDT(ts,pl, ph, rapMin, rapMax, cl, ch, cutQVP , ratio, state, "", "S2", systype.c_str());
//	   auto res_GOB_ref = Get_Optimal_BDT(ts,pl, ph, rapMin, rapMax, cl, ch, cutQVP , sb_ratio.getVal(), state, "", "S2");
//	   double res_blow = res_GOB.first;
//	   double res_blow_ref = res_GOB_ref.first;
//	   if (res_blow == res_blow_ref){
//	       std::cout << "[BDT val Getter] Referencing BDT ratio from Integrated Bin" << std::endl;
//	       auto sb_ratio_INT = get_eff_acc(type_r, typenobdt, ts, rapMax, 0, 30, 0, 181, -0.0, 1.0, state, 1, state, true);
//	       std::cout << "\n\n\n\n DEBUG REPORT: SB_RATIO_INT="<< sb_ratio_INT.getVal() << ", SB_RATIO="<<sb_ratio.getVal() << "\n\n\n\n";
//	       double ratio_INT_ref = sb_ratio_INT.getVal();
//	       double ratio_INT = ratio_INT_ref + ((double) _step * sb_ratio.getError() ); 
//	       double INT_BDT_ref = Get_Optimal_BDT(ts,0,30, rapMin, rapMax, 0, 181, cutQVP , ratio_INT_ref, state, "", "S2", "").first;
//
//	       double INT_BDT = Get_Optimal_BDT(ts,0,30, rapMin, rapMax, 0, 181, cutQVP , ratio_INT, state, "", "S2", "SYSNON2").first;
//	       std::cout << "\n\n\n\n DEBUG REPORT: INT_BDT_ref="<< INT_BDT_ref  << "\n\n\n\n";
//	       std::cout << "\n\n\n\n DEBUG REPORT: INT_BDT="<< INT_BDT  << "\n\n\n\n";
//	       double bdt_val_ratio = INT_BDT/INT_BDT_ref;
//	       std::cout << "\n\n\n\n DEBUG REPORT: BDT_VAL_RATIO="<< bdt_val_ratio  << "\n\n\n\n";
//	       res_blow = res_blow_ref* bdt_val_ratio;
//	   }
//	   std::cout <<"[INFO] " <<res_blow << " is the determined BDT \n\n\n" << std::endl;
//	   return res_blow;
//	};
	///////////////////////////////////////////////////
	
	string bkgtype = Chi2GOF_test(x)[0].second;
	std::string type_nom = 	Form("CB3:%s:%s",		 	bkgtype.c_str(),  fittype.c_str());
	std::string type_sys1  =Form("CB3:%s:%sbdtup",		bkgtype.c_str(),  fittype.c_str());
	std::string type_sys2 = Form("CB3:%s:%sbdtdown",	bkgtype.c_str(),  fittype.c_str());
	binplotter *bp_nom, *bp_sys1, *bp_sys2;
	double bl_nom = Get_BDT(ts, state, bpl, bph, pl, ph, cl, ch);
	bp_nom  = new binplotter(type_nom , ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	dbg(1209);
	bp_sys1 = new binplotter(type_sys1, ts,  2.4, pl, ph, cl, ch, 0, prep_bdtval( 1).first, 1, bpl, bph, train_state, state, false, false);
	dbg(1210);
	bp_sys2 = new binplotter(type_sys2, ts,  2.4, pl, ph, cl, ch, 0, prep_bdtval(-1).first, 1, bpl, bph, train_state, state, false, false);
	dbg(1211);
	RooRealVar raa_nom, raa_sys1, raa_sys2;
	if( !isDR ){
	raa_nom = bp_nom->get_yield(state);
	raa_sys1 = bp_nom->get_yield(state);
	raa_sys2 = bp_nom->get_yield(state);
	}
	if( isDR ){
	raa_nom  = bp_nom->get_frac(state);
	raa_sys1 = bp_nom->get_frac(state);
	raa_sys2 = bp_nom->get_frac(state);
	}

	double unc_sys1 =  (raa_sys1.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	double unc_sys2 =  (raa_sys2.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	return max(fabs(unc_sys1), fabs(unc_sys2));
};

void BDTVariUnc(){
	sys_wr_helper("BDT_unc.root", getBDTVariUnc);
}

