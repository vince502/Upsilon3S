//#include "../plots/drawRAAplot.cxx"
#include "GOF_test.cxx"
#include "sys_wr_helper.cxx"

#ifndef pp 
#define pp std::pair<std::pair<double, string>, std::pair<double, string> >
#endif 

pp getBDTDiffVariUnc_2item(ana_bins x){
	int pl, ph, cl, ch, state, bpl, bph;
	pl = x.pl; ph = x.ph; cl = x.cl; ch = x.ch; state = x.state; bpl = x.bpl; bph = x.bph;
	string fittype = (strcmp(x.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	long ts = _TS;
    int train_state = x.train_state;
	const std::string typenobdt = "CB3:CC4:FF";
	double rapMax = 2.4;
	double rapMin = -2.4;
	double cutQVP = 0.00;
	double blow_ref, ratio;

	///////////////////////////////////////////////////

//	auto bdtud = [=](){
//		double bdt_nom = Get_BDT(ts, x);
//		double lowten = (bdt_nom - (-1.) ) * 0.1;
//		double upten = (1. - bdt_nom) * 0.1;
//		return std::pair<double, double>(bdt_nom - lowten, bdt_nom + upten);
//	};
	///////////////////////////////////////////////////
	
	string bkgtype = AICGOF_test(x)[0].second;
	std::string type_nom = 	Form("CB3:%s:%s",		 	bkgtype.c_str(),  fittype.c_str());
	std::string type_sys1  =Form("CB3:%s:%sbdtup",		bkgtype.c_str(),  fittype.c_str());
	std::string type_sys2 = Form("CB3:%s:%sbdtdown",	bkgtype.c_str(),  fittype.c_str());
	binplotter *bp_nom, *bp_sys1, *bp_sys2;
	double bl_nom = Get_BDT(ts_alias(ts), x);
	//////////////////////////////////////////////////
	auto getdiff = [=](){
		auto sb_ratio = get_eff_acc_v2(type_nom, ts_alias(ts), 2.4, (double) pl, (double) ph, cl, ch, bl_nom, 1.0, bpl, bph, train_state, 1, state, false);
		return Get_BDTTD(ts_alias(ts), x, sb_ratio.getVal());
	};
	auto res = getdiff(); 
	//////////////////////////////////////////////////

	bp_nom  = new binplotter(type_nom , ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	bp_sys1 = new binplotter(type_sys1, ts,  2.4, pl, ph, cl, ch, 0, res.second, 1, bpl, bph, train_state, state, false, false);
	bp_sys2 = new binplotter(type_sys2, ts,  2.4, pl, ph, cl, ch, 0, res.first, 1, bpl, bph, train_state, state, false, false);
	RooRealVar raa_nom, raa_sys1, raa_sys2;
	if( !isDR ){
	raa_nom = bp_nom->get_yield(state);
	raa_sys1 = bp_sys1->get_yield(state);
	raa_sys2 = bp_sys2->get_yield(state);
	double eff_nom = bp_nom->get_eff(state).first;
	double eff_sys1 = bp_sys1->get_eff(state).first;
	double eff_sys2 = bp_sys2->get_eff(state).first;
	raa_nom.setVal(raa_nom.getVal()/eff_nom);
	raa_sys1.setVal(raa_sys1.getVal()/eff_sys1);
	raa_sys2.setVal(raa_sys2.getVal()/eff_sys2);
	}
	if( isDR ){
		if( x.state == 2 ) return pp { { 0, "Up" }, { 0, "Down" } };
		else{
			raa_nom  = bp_nom->return_23s_frac(false);
			raa_sys1 = bp_sys1->return_23s_frac(false);
			raa_sys2 = bp_sys2->return_23s_frac(false);
		}
	}

	double unc_sys1 =  (raa_sys1.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	double unc_sys2 =  (raa_sys2.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	std::cout <<"RETURN: " << max(fabs(unc_sys1), fabs(unc_sys2)) << std::endl;
	return pp { { unc_sys1, "Up" }, {unc_sys2, "Down" } };
};

double getBDTDiffVariUnc(ana_bins x){
	pp res = getBDTDiffVariUnc_2item(x);
	return max(fabs(res.first.first), fabs(res.second.first));
};


void BDTDiffVariUnc(){
	sys_wr_helper(Form("BDT_Diff_unc%s_%ld.root",labDR.c_str(), _TS), getBDTDiffVariUnc);
	sys_wr_helper_2item(Form("BDT_Diff_unc%s_2item_%ld.root",labDR.c_str(), _TS), getBDTDiffVariUnc_2item);
}

