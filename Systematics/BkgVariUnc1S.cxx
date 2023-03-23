//#include "../plots/drawRAAplot_v2.cxx"
#include "GOF_test.cxx"
#include "sys_wr_helper.cxx"

#ifndef pp
#define pp std::pair<std::pair<double, string>, std:;pair<double, string> >
#endif

pp getBkgVariUnc1S_2item(ana_bins x){
	int pl, ph, cl, ch, state, bpl, bph;
	pl = x.pl; ph = x.ph; cl = x.cl; ch = x.ch; state = x.state; bpl = x.bpl; bph = x.bph;
	int train_state = x.train_state;
	string fittype = (strcmp(x.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	long ts = _TS;
	auto AICres = AICGOF_test(x);
	string bkgtype_nom = AICres[0].second;
	string bkgtype_sys1 = AICres[1].second;
	string bkgtype_sys2 = AICres[2].second;
//	string bkgtype_sys2 = (bkgtype_nom.find("CC") != std::string::npos) ? 
//	bkgtype_nom.substr(0,2) + Form("%d",stoi(bkgtype_nom.substr(2,1) )+1 ) : (bkgtype_sys1.find("CC") != std::string::npos) ?
//	bkgtype_sys1.substr(0,2) + Form("%d",stoi(bkgtype_sys1.substr(2,1) )+1 ) : AICres[2].second;

	std::string type_nom = 	Form("CB3:%s:%s",	bkgtype_nom.c_str(),  fittype.c_str());
	std::string type_sys1  =Form("CB3:%s:%s",	bkgtype_sys1.c_str(),  fittype.c_str());
	std::string type_sys2 = Form("CB3:%s:%s",	bkgtype_sys2.c_str(),  fittype.c_str());

	binplotter *bp_nom, *bp_sys1, *bp_sys2;
	double bl_nom = Get_BDT(ts, train_state, state, bpl, bph, pl, ph, cl, ch);
	bp_nom  = new binplotter(type_nom , ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	bp_sys1 = new binplotter(type_sys1, ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	bp_sys2 = new binplotter(type_sys2, ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	RooRealVar raa_nom, raa_sys1, raa_sys2;
	if( !isDR ){
	raa_nom = bp_nom->get_yield(1);
	raa_sys1 = bp_sys1->get_yield(1);
	raa_sys2 = bp_sys2->get_yield(1);
//	double eff_nom = bp_nom->get_eff(state).first;
//	double eff_sys1 = bp_sys1->get_eff(state).first;
//	double eff_sys2 = bp_sys2->get_eff(state).first;
//	raa_nom.setVal(raa_nom.getVal()/eff_nom);
//	raa_sys1.setVal(raa_sys1.getVal()/eff_sys1);
//	raa_sys2.setVal(raa_sys2.getVal()/eff_sys2);
	}
	if( isDR ){
//	raa_nom  = bp_nom->return_23s_frac();
//	raa_sys1 = bp_sys1->return_23s_frac();
//	raa_sys2 = bp_sys2->return_23s_frac();
	}

	double unc_sys1 =  (raa_sys1.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	double unc_sys2 =  (raa_sys2.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	if( bkgtype_sys2.find("CC") != std::string::npos ) unc_sys2 = 0 ;
	return (pp) { {unc_sys1, bkgtype_sys1}, {unc_sys2, bkgtype_sys2} };
};
double getBkgVariUnc1S(ana_bins x){
	pp res = getBkgVariUnc1S_2item(x);
	return max(fabs(res.first.first), fabs(res.second.first));
};

void BkgVariUnc1S(){
	sys_wr_helper_2item(Form("bkgPDF_unc%s1S_2item.root", labDR.c_str()), getBkgVariUnc1S_2item);
	sys_wr_helper(Form("bkgPDF_unc%s1S.root", labDR.c_str()), getBkgVariUnc1S);
}
