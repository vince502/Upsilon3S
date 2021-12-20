#include "../plots/drawRAAplot.cxx"
#include "GOF_test.cxx"
#include "sys_wr_helper.cxx"
bool isDR = false;

double getSigParVariUnc(ana_bins x){
	int pl, ph, cl, ch, state, bpl, bph;
	pl = x.pl; ph = x.ph; cl = x.cl; ch = x.ch; state = x.state; bpl = x.bpl; bph = x.bph;
	int train_state = state;
	long ts = 9999999999;
	string fittype = (strcmp(x.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	string bkgNom = AICGOF_test(x)[0].second;
	std::string type_nom = Form("CB3:%s:%s",		bkgNom.c_str(), fittype.c_str());
	std::string type_sys = Form("CB3:%s:%sXMC1P",	bkgNom.c_str(), fittype.c_str());

	binplotter *bp_nom, *bp_sys1;
	double bl_nom = Get_BDT(ts, x);
	bp_nom  = new binplotter(type_nom, ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	bp_sys1 = new binplotter(type_sys, ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	RooRealVar raa_nom, raa_sys1;
	if( !isDR ){
	raa_nom = bp_nom->get_yield(state);
	raa_sys1 = bp_sys1->get_yield(state);
	}
	if( isDR ){
	raa_nom  = bp_nom->get_frac(state);
	raa_sys1 = bp_sys1->get_frac(state);
	}

	double unc_sys1 =  (raa_sys1.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	return unc_sys1;
};

void SigParVariUnc(){
	sys_wr_helper("sigPAR_unc.root", getSigParVariUnc);
}

