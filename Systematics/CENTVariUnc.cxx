#pragma once
#include "GOF_test.cxx"
#include "sys_wr_helper.cxx"

#ifndef pp
#define pp std::pair<std::pair<double, string>, std::pair<double, string> >
#endif

pp getCENTVariUnc_2item(ana_bins x){
	int pl, ph, cl, ch, state, bpl, bph;
	pl = x.pl; ph = x.ph; cl = x.cl; ch = x.ch; state = x.state; bpl = x.bpl; bph = x.bph;
	int train_state = x.train_state;
	long ts = _TS;
	long ts_sys_up, ts_sys_do;
	if( ts == 10000000016){
		ts_sys_up = 9999999998;
		ts_sys_do = 9999999997;
	}
	else{
		ts_sys_up = (ts * 10000)+2;
		ts_sys_do = (ts * 10000)+1;
	}
	string fittype = (strcmp(x.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	auto AICres = AICGOF_test(x);
	string bkgNom = AICres[0].second;
	std::string type_nom = Form("CB3:%s:%s",	bkgNom.c_str(), fittype.c_str());

	binplotter *bp_nom, *bp_sys1, *bp_sys2;
	double bl_nom = Get_BDT(ts_alias(ts), x);
	bp_nom  = new binplotter(type_nom, ts       ,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	bp_sys1 = new binplotter(type_nom, ts_sys_up,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	bp_sys2 = new binplotter(type_nom, ts_sys_do,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	RooRealVar raa_nom, raa_sys1, raa_sys2;
	if( !isDR ){
	raa_nom = bp_nom->get_yield(state);
	raa_sys1 = bp_sys1->get_yield(state);
	raa_sys2 = bp_sys2->get_yield(state);
	}
	if( isDR ){
	raa_nom  = bp_nom->return_23s_frac();
	raa_sys1 = bp_sys1->return_23s_frac();
	raa_sys2 = bp_sys2->return_23s_frac();
	}

	double unc_sys1 =  (raa_sys1.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	double unc_sys2 =  (raa_sys2.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	std::cout << "[SigPdfVariUnc] unc_sys1 : " << unc_sys1 << std::endl;
	std::cout << "[SigPdfVariUnc] unc_sys2 : " << unc_sys2 << std::endl;
	return pp { { unc_sys1, "Up" }, { unc_sys2, "Down" } };
};

double getCENTVariUnc(ana_bins x){
	pp res = getCENTVariUnc_2item(x);
	return max(fabs(res.first.first), fabs(res.second.first));
};

void CENTVariUnc(){
	sys_wr_helper(Form("CENT_unc%s_%ld.root", labDR.c_str(), _TS) , getCENTVariUnc);
	sys_wr_helper_2item(Form("CENT_unc%s_2item_%ld.root",labDR.c_str(), _TS), getCENTVariUnc_2item);
}

