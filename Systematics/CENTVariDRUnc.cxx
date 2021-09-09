#include "../plots/drawDoubleRatioplot.cxx"

std::string findtype(int pl, int ph, int cl, int ch){
	std::string fittype = "";
	if( cl ==0 && ch == 181) fittype = "GC";
	else fittype = "FF";
	return fittype;
};

double getCENTVariUnc(int pl, int ph, int cl, int ch, int state){
	long ts = 9999999999;
	long ts_sys_up   = 9999999998;
	long ts_sys_down = 9999999997;
	std::string type_nom = Form("CB3:CC%d:DR%s",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str());
	std::string type_sys = Form("CB3:CC%d:DR%s",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str());

	RooRealVar raa_nom, raa_sys_up, raa_sys_down;
	double bl = Get_BDT(ts, state, pl, ph, cl, ch);
	raa_nom = getDoubleRatioValue({cl, ch}, {(double) pl, (double) ph},type_nom, {bl,1}, state, 1, ts);
	binplotter *bp_up, *bp_down;
	bp_up   = new binplotter(type_sys, ts_sys_up  , 2.4, (double) pl, (double) ph, cl, ch, bl, 1.,state, false);
	bp_down = new binplotter(type_sys, ts_sys_down, 2.4, (double) pl, (double) ph, cl, ch, bl, 1.,state, false);
	raa_sys_up   = bp_up->get_frac(state);
	raa_sys_down = bp_down->get_frac(state);
	
	double large_sys = ( (fabs(raa_sys_up.getVal() - raa_nom.getVal() ) - fabs(raa_sys_down.getVal() - raa_nom.getVal())) > 0) ? raa_sys_up.getVal() : raa_sys_down.getVal();

	double unc_sys = (large_sys - raa_nom.getVal())/(raa_nom.getVal());
	return unc_sys;
};
double getCENTVariUnc(ana_bins k){
	double unc_sys = getCENTVariUnc(k.pl, k.ph, k.cl, k.ch, k.state);
	return unc_sys;
};

void  CENTVariDRUnc(){
	TFile* output = new TFile("CENT_DR_unc.root","recreate");
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
		rc2s->SetBinContent(counter, getCENTVariUnc(item));
		counter++;
	}
	counter =1;
	for( auto item : vc3){
		rc3s->SetBinContent(counter, getCENTVariUnc(item));
		counter++;
	}
	counter =1;

	for( auto item : vp2){
		rp2s->SetBinContent(counter, getCENTVariUnc(item));
		counter++;
	}
	counter =1;
	
	for( auto item : vp3){
		rp3s->SetBinContent(counter, getCENTVariUnc(item));
		counter++;
	}
	output->cd();
	rc2s->Write();
	rc3s->Write();
	rp2s->Write();
	rp3s->Write();
	output->Close();
}

