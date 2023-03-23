#include "sys_wr_helper.cxx"
#include "./GOF_test.cxx"

double effratio(ana_bins ab){
	long ts = _TS;
	if( ab.state == 2) return 0;
	TFile* f_pp_corr = TFile::Open("/home/CMS/Analysis/HIN21007/Upsilon3S_pp2017Ref/CrossCheck/corr.root");

	TH1D* h_pp_corr;
	if(ab.bintype != kPt) h_pp_corr = (TH1D*) f_pp_corr->Get("hratio_int"); 
	if(ab.bintype == kPt) h_pp_corr = (TH1D*) f_pp_corr->Get("hratio_pt"); 
	double pp_corr = (ab.bintype ==kPt) ? h_pp_corr->GetBinContent( h_pp_corr->FindBin( (ab.pl+ab.ph)/2 ) ) : h_pp_corr->GetBinContent(1);
	f_pp_corr->Close();

	string fittype = (strcmp(ab.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	string bkgtype = AICGOF_test(ab)[0].second;
	string type = Form("CB3:%s:%s", bkgtype.c_str(), fittype.c_str());
	double bl = Get_BDT(ts_alias(ts), ab);
//	std::cout << "[bl, type]: " <<bl << ", " << type.c_str()  << std::endl;
	auto bp = new binplotter(type, ts, 2.4, ab.pl,  ab.ph, ab.cl, ab.ch, 0., bl, 1, ab.bpl, ab.bph, ab.train_state, ab.state, false, false);
	RooRealVar _yacc_2s = upsi::getacceptance(ab.pl, ab.ph, -2.4,2.4, 3.5, 2);
	RooRealVar _yacc_3s = upsi::getacceptance(ab.pl, ab.ph, -2.4,2.4, 3.5, 3);
	auto _yeff_2s = bp->get_eff(2);
	auto _yeff_3s = bp->get_eff(3);
//	RooRealVar theratio("ratio", "", 0);
	std::cout << Form("[mc ratio]: eff, acc 2,3S : %.4f, %.4f, %.4f, %.4f",_yeff_2s.first, _yacc_2s.getVal(), _yeff_3s.first, _yacc_3s.getVal()) << std::endl;
	double _ratio = (  (_yacc_2s.getVal()) * (_yeff_2s.first) ) / ( (_yacc_3s.getVal()) * (_yeff_3s.first) );
//	double _ratio = (  (_yacc_2s.getVal())  ) / ( (_yacc_3s.getVal()) );
//	theratio.setVal(pp_corr / (1/_ratio) );
	double theratio =(pp_corr / (1/_ratio) ) -1 ;
//	std::cout << "ratio: " << theratio.getVal() << std::endl;
	return theratio;
}

void CorrectionUnc(){
	sys_wr_helper(Form("Correction_unc_DR_%ld.root", _TS), effratio);	
}
