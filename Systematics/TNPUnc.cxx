#include "../BDT/bininfo.h"

std::pair< string, string > get_histnames(ana_bins x){
	double bl = Get_BDT(9999999999, x.state, x.pl, x.ph, x.cl, x.ch);
	double ml, mh;
	if( x.state == 2){ml = 9.3; mh = 10.7;}
	if( x.state == 3){ml = 9.6; mh = 11.0;}
	std::string histNameNOM = Form("BDT_%dS_train%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_fix", x.state, x.state, 9999999999, bl, 1, x.pl, x.ph, -2.4, 2.4, 3.5, ml, mh, x.cl, x.ch, 0, true, true);
	std::string histNameSYS = histNameNOM + "_SYSTNP";
	return std::make_pair<string, string> (histNameNOM, histNameSYS);
};

void TNPUnc(){
	 
	TFile* output = new TFile("effTNP_unc.root","recreate");
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

}

