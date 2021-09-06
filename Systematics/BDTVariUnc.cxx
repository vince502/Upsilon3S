#include "../plots/drawRAAplot.cxx"

std::string findtype(int pl, int ph, int cl, int ch){
	std::string fittype = "";
	if( cl ==0 && ch == 181) fittype = "GC";
	else fittype = "FF";
	return fittype;
};

double getBDTVariUnc(int pl, int ph, int cl, int ch, int state){
	long ts = 9999999999;
	const std::string type_r = "CB3:CC2:DRGC";
	const std::string typenobdt = "CB3:CC4:FF";
	double rapMax = 2.4;
	double rapMin = -2.4;
	double cutQVP = 0.00;
	double blow_ref, ratio;
	if( findtype (pl, ph, cl, ch) != "FF") blow_ref = -0.0;
	else if( findtype (pl, ph, cl, ch) != "GC") blow_ref = -0.1;
	///////////////////////////////////////////////////
	auto prep_bdtval = [&]  (int _step =0 ) mutable {
	    auto sb_ratio = get_eff_acc(type_r, typenobdt, ts, rapMax, pl, ph, cl, ch, blow_ref, 1.0, state, 1, state, true);
	    std::cout << Form("pl, ph, cl, ch, blow_ref, ratio: %d, %d, %d, %d, %.4f, %.6f", pl, ph, cl, ch, blow_ref,  sb_ratio.getVal() ) << std::endl;
	    if( _step == 1) ratio = sb_ratio.getVal() + sb_ratio.getError();
	    if( _step == -1) ratio = sb_ratio.getVal() - sb_ratio.getError();
	    if(_step == 0){ std::cout << "Why fitting Nominal here? " << std::endl;}

	    std::cout << "\n\n\n\nDEBUG : RATIO = "<<ratio<<"\nDEBUG : REF RATIO = "<<sb_ratio.getVal() << ", Error = "<< sb_ratio.getError() << std::endl;
	    std::string systype;
	    if(_step ==  1) systype = "SYSUP";
	    if(_step == -1) systype = "SYSDOWN";
	   auto res_GOB = Get_Optimal_BDT(ts,pl, ph, rapMin, rapMax, cl, ch, cutQVP , ratio, state, "", "S2", systype.c_str());
	   auto res_GOB_ref = Get_Optimal_BDT(ts,pl, ph, rapMin, rapMax, cl, ch, cutQVP , sb_ratio.getVal(), state, "", "S2");
	   double res_blow = res_GOB.first;
	   double res_blow_ref = res_GOB_ref.first;
	   if (res_blow == res_blow_ref){
	       std::cout << "[BDT val Getter] Referencing BDT ratio from Integrated Bin" << std::endl;
	       auto sb_ratio_INT = get_eff_acc(type_r, typenobdt, ts, rapMax, 0, 30, 0, 181, -0.0, 1.0, state, 1, state, true);
	       std::cout << "\n\n\n\n DEBUG REPORT: SB_RATIO_INT="<< sb_ratio_INT.getVal() << ", SB_RATIO="<<sb_ratio.getVal() << "\n\n\n\n";
	       double ratio_INT_ref = sb_ratio_INT.getVal();
	       double ratio_INT = ratio_INT_ref + ((double) _step * sb_ratio.getError() ); 
	       double INT_BDT_ref = Get_Optimal_BDT(ts,0,30, rapMin, rapMax, 0, 181, cutQVP , ratio_INT_ref, state, "", "S2", "").first;

	       double INT_BDT = Get_Optimal_BDT(ts,0,30, rapMin, rapMax, 0, 181, cutQVP , ratio_INT, state, "", "S2", "SYSNON2").first;
	       std::cout << "\n\n\n\n DEBUG REPORT: INT_BDT_ref="<< INT_BDT_ref  << "\n\n\n\n";
	       std::cout << "\n\n\n\n DEBUG REPORT: INT_BDT="<< INT_BDT  << "\n\n\n\n";
	       double bdt_val_ratio = INT_BDT/INT_BDT_ref;
	       std::cout << "\n\n\n\n DEBUG REPORT: BDT_VAL_RATIO="<< bdt_val_ratio  << "\n\n\n\n";
	       res_blow = res_blow_ref* bdt_val_ratio;
	   }
	   std::cout <<"[INFO] " <<res_blow << " is the determined BDT \n\n\n" << std::endl;
	   return res_blow;
	};
	///////////////////////////////////////////////////

	std::string type_nom = Form("CB3:CC%d:%s",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str());
	std::string type_sys  = Form("CB3:CC%d:%sbdtup",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str());
	std::string type_sys2 = Form("CB3:CC%d:%sbdtdown",getNomBkgO(state, pl, ph, cl, ch), findtype(pl, ph, cl, ch).c_str());
	RooRealVar raa_nom, raa_sys, raa_sys2;
	raa_nom = getDoubleRatioValue({cl, ch}, {(double) pl, (double) ph},type_nom, -2, state, 1, ts, false, true);
	std::cout << "CHECK" <<  prep_bdtval(1) << std::endl;
	raa_sys = getDoubleRatioValue({cl, ch}, {(double) pl, (double) ph},type_sys, prep_bdtval(1), state, 1, ts, false, true);
	raa_sys2 = getDoubleRatioValue({cl, ch}, {(double) pl, (double) ph},type_sys2, prep_bdtval(-1), state, 1, ts, false, true);

	double unc_sys =  (raa_sys.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	double unc_sys2 =  (raa_sys.getVal() - raa_nom.getVal())/(raa_nom.getVal());
	return max(fabs(unc_sys), fabs(unc_sys2));
};
double getBDTVariUnc(ana_bins k){
	double unc_sys = getBDTVariUnc(k.pl, k.ph, k.cl, k.ch, k.state);
	return unc_sys;
};

void BDTVariUnc(){
	TFile* output = new TFile("BDT_unc.root","recreate");
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
		rc2s->SetBinContent(counter, getBDTVariUnc(item));
		counter++;
	}
	counter =1;
	for( auto item : vc3){
		rc3s->SetBinContent(counter, getBDTVariUnc(item));
		counter++;
	}
	counter =1;

	for( auto item : vp2){
		rp2s->SetBinContent(counter, getBDTVariUnc(item));
		counter++;
	}
	counter =1;
	
	for( auto item : vp3){
		rp3s->SetBinContent(counter, getBDTVariUnc(item));
		counter++;
	}
	output->cd();
	rc2s->Write();
	rc3s->Write();
	rp2s->Write();
	rp3s->Write();
	output->Close();
}

