#include "../plots/drawRAAplot.cxx"

std::string findtype(int pl, int ph, int cl, int ch){
	std::string fittype = "";
	if( cl ==0 && ch == 181) fittype = "GC";
	else fittype = "FF";
	return fittype;
};

double getSysPdfVariUnc(int pl, int ph, int cl, int ch, int state){
	long ts = 9999999999;
	std::string type_nom = Form("CB3:CC%d:%s",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str());
	std::string type_sys = Form("CB2G:CC%d:%s",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str());

	RooRealVar raa_nom, raa_sys, raa_sys2;
	raa_nom = getDoubleRatioValue({cl, ch}, {(double) pl, (double) ph},type_nom, -2, state, 2, ts);
	raa_sys = getDoubleRatioValue({cl, ch}, {(double) pl, (double) ph},type_sys, -2, state, 2, ts);

	double unc_sys =  (raa_sys.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	return unc_sys;
};
double getSysPdfVariUnc(ana_bins k){
	double unc_sys = getSysPdfVariUnc(k.pl, k.ph, k.cl, k.ch, k.state);
	return unc_sys;
};

void SigPdfVariUnc(){
	TFile* output = new TFile("sigPDF_unc.root","recreate");
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
		rc2s->SetBinContent(counter, getSysPdfVariUnc(item));
		counter++;
	}
	counter =1;
	for( auto item : vc3){
		rc3s->SetBinContent(counter, getSysPdfVariUnc(item));
		counter++;
	}
	counter =1;

	for( auto item : vp2){
		rp2s->SetBinContent(counter, getSysPdfVariUnc(item));
		counter++;
	}
	counter =1;
	
	for( auto item : vp3){
		rp3s->SetBinContent(counter, getSysPdfVariUnc(item));
		counter++;
	}
	output->cd();
	rc2s->Write();
	rc3s->Write();
	rp2s->Write();
	rp3s->Write();
	output->Close();
}

