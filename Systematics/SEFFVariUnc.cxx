//#include "../plots/drawRAAplot.cxx"
#include "GOF_test.cxx"
#include "sys_wr_helper.cxx"
#include "../BDT/BDTVari_Seff.cxx"

#ifndef pp 
#define pp std::pair<std::pair<double, string>, std::pair<double, string> >
#endif 

pp getSEFFVariUnc_2item(ana_bins x){
	int pl, ph, cl, ch, state, bpl, bph;
	pl = x.pl; ph = x.ph; cl = x.cl; ch = x.ch; state = x.state; bpl = x.bpl; bph = x.bph;
	string fittype = (strcmp(x.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	long ts = _TS;
    int train_state = x.train_state;
	const std::string type_r = "CB3:CC2:DRGC";
	const std::string typenobdt = "CB3:CC4:FF";
	double rapMax = 2.4;
	double rapMin = -2.4;
	double cutQVP = 0.00;
	double blow_ref, ratio;

	///////////////////////////////////////////////////
	std::pair< double, double > res = BDTVari_Seff(ts, x);
	///////////////////////////////////////////////////
	
	string bkgtype = AICGOF_test(x)[0].second;
	std::string type_nom = 	Form("CB3:%s:%s",		 	bkgtype.c_str(),  fittype.c_str());
	std::string type_sys1  =Form("CB3:%s:%sbdtup",		bkgtype.c_str(),  fittype.c_str());
	std::string type_sys2 = Form("CB3:%s:%sbdtdown",	bkgtype.c_str(),  fittype.c_str());
	binplotter *bp_nom, *bp_sys1, *bp_sys2;
	double bl_nom = Get_BDT(ts, x);
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
	raa_nom  = bp_nom->get_frac(state);
	raa_sys1 = bp_sys1->get_frac(state);
	raa_sys2 = bp_sys2->get_frac(state);
	}

	double unc_sys1 =  (raa_sys1.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	double unc_sys2 =  (raa_sys2.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	std::cout <<"RETURN: " << max(fabs(unc_sys1), fabs(unc_sys2)) << std::endl;
	return pp { { unc_sys1, "Up" }, {unc_sys2, "Down" } };
};

double getSEFFVariUnc(ana_bins x){
	pp res = getSEFFVariUnc_2item(x);
	return max(fabs(res.first.first), fabs(res.second.first));
};


void SEFFVariUnc(){
	sys_wr_helper("BDT_Seff_unc.root", getSEFFVariUnc);
	sys_wr_helper_2item("BDT_Seff_unc_2item.root", getSEFFVariUnc_2item);
}

