#include "GOF_test.cxx"
#include "sys_wr_helper.cxx"


double getDPTVariUnc(ana_bins x){
	int pl, ph, cl, ch, state, bpl, bph;
	pl = x.pl; ph = x.ph; cl = x.cl; ch = x.ch; state = x.state; bpl = x.bpl; bph = x.bph;
	int train_state = x.train_state;
	string fittype = (strcmp(x.bin_attr.c_str(), "c") ==0) ? "FF" : "GC";
	long ts = _TS;
	auto AICres = AICGOF_test(x);
	string bkgtype_nom = AICres[0].second;
	string type_nom = Form("CB3:%s:%s", bkgtype_nom.c_str(), fittype.c_str() );
	double bl = Get_BDT(ts_alias(ts), x);

	binplotter* bp = new binplotter(type_nom, ts, 2.4, pl, ph, cl, ch, 0, bl, 1, bpl, bph, train_state, state, false, false);
	auto v_eff = bp->get_eff_NN(state);
	double ref = v_eff[0];
	double ratio_NU = fabs(v_eff[1]- ref)/ref;
	double ratio_ND = fabs(v_eff[2]- ref)/ref;
	double ratio_UN = fabs(v_eff[3]- ref)/ref;
	double ratio_DN = fabs(v_eff[4]- ref)/ref;
	double dpt_unc = TMath::Sqrt( 0.25*( ratio_UN* ratio_UN +   ratio_ND* ratio_ND + ratio_UN* ratio_UN + ratio_DN* ratio_DN ));

	return dpt_unc;
};

void DPTUnc(){
	sys_wr_helper(Form("effDPTQuad_unc_%ld.root",ts_alias(_TS)), getDPTVariUnc);
}

