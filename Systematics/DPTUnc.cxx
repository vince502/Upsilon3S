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
	dbg();
	auto count_eff_nom = bp->get_eff(state, true);
	auto count_eff_down = bp->get_eff_sysdpt(state, "DOWN", true);
	auto count_eff_up = bp->get_eff_sysdpt(state, "UP", true);
	double eff_nom_nom, eff_up_nom, eff_down_nom, eff_nom_up, eff_nom_down;
	eff_nom_nom = count_eff_nom.second/count_eff_nom.first;
	eff_up_nom = count_eff_up.second/count_eff_nom.first;
	eff_down_nom = count_eff_down.second/count_eff_nom.first;
	eff_nom_up = count_eff_nom.second/count_eff_up.first;
	eff_nom_down = count_eff_nom.second/count_eff_down.first;
	std::cout << "[SYSTEMATIC] Efficiency nom, no: " <<Form(" %.4f, %.4f, %.4f, %.4f, %.4f %%",eff_nom_nom, eff_up_nom, eff_down_nom, eff_nom_up, eff_nom_down )<< std::endl; 
	double err_upnom, err_downnom, err_nomup, err_nomdown;
	err_upnom = (eff_up_nom - eff_nom_nom) / eff_nom_nom;
	err_downnom = (eff_down_nom - eff_nom_nom) / eff_nom_nom;
	err_nomup = (eff_nom_up - eff_nom_nom) / eff_nom_nom;
	err_nomdown = (eff_nom_down - eff_nom_nom) / eff_nom_nom;
	double dpt_unc = TMath::Sqrt( err_upnom * err_upnom + err_downnom * err_downnom + err_nomup * err_nomup + err_nomdown * err_nomdown );

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

