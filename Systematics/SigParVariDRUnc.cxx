#include "../plots/drawDoubleRatioplot.cxx"

std::string findtype(int pl, int ph, int cl, int ch){
	std::string fittype = "";
	if( cl ==0 && ch == 181) fittype = "GC";
	else fittype = "FF";
	return fittype;
};

double getSigParVariUnc(int pl, int ph, int cl, int ch, int state){
	long ts = 9999999999;
	std::string type_nom = Form("CB3:CC%d:DR%s",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str());
	std::string type_sys = Form("CB3:CC%d:DR%sXMC1P",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str());

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
	RooRealVar raa_nom, raa_sys, raa_sys2;
	raa_nom = getDoubleRatioValue({cl, ch}, {(double) pl, (double) ph},type_nom,{ -2,1}, state, 1, ts);
	raa_sys = getDoubleRatioValue({cl, ch}, {(double) pl, (double) ph},type_sys,{ -2,1}, state, 1, ts);

	double unc_sys =  (raa_sys.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	return unc_sys;
};
double getSigParVariUnc(ana_bins k){
	double unc_sys = getSigParVariUnc(k.pl, k.ph, k.cl, k.ch, k.state);
	return unc_sys;
};

void SigParVariDRUnc(){
	TFile* output = new TFile("sigPAR_DR_unc.root","recreate");
	TH1D *rc2s, *rc3s, *rp2s, *rp3s;
	rc2s = new TH1D("rc2S","",10,0,9); //include int. bin
	rc3s = new TH1D("rc3S","",4,0,3);  //include int. bin
	rp2s = new TH1D("rp2S","",3,1,3);
	rp3s = new TH1D("rp3S","",2,1,2);

	std::vector<ana_bins> vc2, vc3, vp2, vp3;
	vc2 = ana_bm["2c"];
	vc3 = ana_bm["3c"];
	vp2 = ana_bm["2p"];
	vp3 = ana_bm["3p"];

	int counter =1;
	for( auto item : vc2){
		rc2s->SetBinContent(counter, getSigParVariUnc(item));
		counter++;
	}
	counter =1;
	for( auto item : vc3){
		rc3s->SetBinContent(counter, getSigParVariUnc(item));
		counter++;
	}
	counter =1;

	for( auto item : vp2){
		rp2s->SetBinContent(counter, getSigParVariUnc(item));
		counter++;
	}
	counter =1;
	
	for( auto item : vp3){
		rp3s->SetBinContent(counter, getSigParVariUnc(item));
		counter++;
	}
	output->cd();
	rc2s->Write();
	rc3s->Write();
	rp2s->Write();
	rp3s->Write();
	output->Close();
}

