#include "../plots/drawRAAplot.cxx"

std::string findtype(int pl, int ph, int cl, int ch){
	std::string fittype = "";
	if( cl ==0 && ch == 181) fittype = "GC";
	else fittype = "FF";
	return fittype;
};

double getDPTVariUnc(int pl, int ph, int cl, int ch, int state){
	double bl = Get_BDT(9999999999, state, pl ,ph ,cl, ch);
	dbg();
	binplotter* bp = new binplotter(Form("CB3:CC%d:%s",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str()), 9999999999, 2.4, pl, ph, cl, ch, bl, 1, state);
	auto v_eff = bp->get_eff_NN(state);
	double ref = v_eff[0];
	double ratio_NU = fabs(v_eff[1]- ref)/ref;
	double ratio_ND = fabs(v_eff[2]- ref)/ref;
	double ratio_UN = fabs(v_eff[3]- ref)/ref;
	double ratio_DN = fabs(v_eff[4]- ref)/ref;
	double dpt_unc = TMath::Sqrt( 0.25*( ratio_UN* ratio_UN +   ratio_ND* ratio_ND + ratio_UN* ratio_UN + ratio_DN* ratio_DN ));

	return dpt_unc;
};
double getDPTVariUnc(ana_bins k){
	double unc_sys = getDPTVariUnc(k.pl, k.ph, k.cl, k.ch, k.state);
	return unc_sys;
};

void DPTUnc(){
	TFile* output = new TFile("effDPTQuad_unc.root","recreate");
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
		rc2s->SetBinContent(counter, getDPTVariUnc(item));
		counter++;
	}
	counter =1;
	for( auto item : vc3){
		rc3s->SetBinContent(counter, getDPTVariUnc(item));
		counter++;
	}
	counter =1;

	for( auto item : vp2){
		rp2s->SetBinContent(counter, getDPTVariUnc(item));
		counter++;
	}
	counter =1;
	
	for( auto item : vp3){
		rp3s->SetBinContent(counter, getDPTVariUnc(item));
		counter++;
	}
	output->cd();
	rc2s->Write();
	rc3s->Write();
	rp2s->Write();
	rp3s->Write();
	output->Close();
}

