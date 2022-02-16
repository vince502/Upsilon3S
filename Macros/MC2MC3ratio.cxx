#define _TS 10000000016
#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#   include "../LLR_CCorder_9999999999.h"
#   define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
#   include "../LLR_CCorder_10000000016.h"
#   define getNomBkgO getNomBkgO_10000000016
#endif

#if _TS == 10000000003 && __has_include("../LLR_CCorder_10000000003.h")
#   include "../LLR_CCorder_10000000003.h"
#   define getNomBkgO getNomBkgO_10000000003
#endif

#if _TS != 9999999999
#   define ana_bm ana_bm_comb
#endif

#include "plot_wr_helper.cxx"
#include "../Systematics/GOF_test.cxx"

RooRealVar effratio(ana_bins ab, long ts = 10000000016){
	TFile* f_pp_mc = TFile::Open("/home/CMS/Analysis/Upsilon3S_pp2017Ref/CrossCheck/corr.root");
	string fittype = (strcmp(ab.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	string bkgtype = AICGOF_test(ab)[0].second;
	string type = Form("CB3:%s:%s", bkgtype.c_str(), fittype.c_str());
	double bl = Get_BDT(ts, ab);
//	std::cout << "[bl, type]: " <<bl << ", " << type.c_str()  << std::endl;
	auto bp = new binplotter(type, ts, 2.4, ab.pl,  ab.ph, ab.cl, ab.ch, 0., bl, 1, ab.bpl, ab.bph, ab.train_state, ab.state, false, false);
	RooRealVar _yacc_2s = upsi::getacceptance(ab.pl, ab.ph, -2.4,2.4, 3.5, 2);
	RooRealVar _yacc_3s = upsi::getacceptance(ab.pl, ab.ph, -2.4,2.4, 3.5, 3);
	auto _yeff_2s = bp->get_eff(2);
	auto _yeff_3s = bp->get_eff(3);
	RooRealVar theratio("ratio", "", 0);
	std::cout << Form("[mc ratio]: eff, acc 2,3S : %.4f, %.4f, %.4f, %.4f",_yeff_2s.first, _yacc_2s.getVal(), _yeff_3s.first, _yacc_3s.getVal()) << std::endl;
	double _ratio = (  (_yacc_2s.getVal()) * (_yeff_2s.first) ) / ( (_yacc_3s.getVal()) * (_yeff_3s.first) );
//	double _ratio = (  (_yacc_2s.getVal())  ) / ( (_yacc_3s.getVal()) );
	double pp_corr =1;
	if(ab.state == 3){
		if(ab.bintype == kPt) pp_corr = ((TH1D*) f_pp_mc->Get("hratio_pt"))->GetBinContent( ab.plot_idx);
		else pp_corr = ((TH1D*) f_pp_mc->Get("hratio_int"))->GetBinContent(1);
	}
	theratio.setVal(_ratio* pp_corr);
	std::cout << "ratio: " << theratio.getVal() << std::endl;
	f_pp_mc->Close();
	return theratio;
}

void MC2MC3ratio(){
	plot_wr_helper("MCratio_220121.root", effratio, 10000000016);	
	TFile* f_res = TFile::Open("result/MCratio_220121.root");
	TCanvas* c1 = new TCanvas("c1", "", 1600, 700);
	c1->Divide(2,1);
	TH1D* h_c3s, *h_p3s;
	h_c3s = (TH1D*) f_res->Get("rc3S");
	h_p3s = (TH1D*) f_res->Get("rp3S");
	h_c3s->SetStats(0);
	h_p3s->SetStats(0);

	h_c3s->GetXaxis()->SetBinLabel(1,"int.");
	h_c3s->GetXaxis()->SetBinLabel(2,"0-30 %");
	h_c3s->GetXaxis()->SetBinLabel(3,"30-50 %");
	h_c3s->GetXaxis()->SetBinLabel(4,"50-70 %");
	h_c3s->GetXaxis()->SetBinLabel(5,"70-90 %");

	h_p3s->GetXaxis()->SetBinLabel(1,"0-4");
	h_p3s->GetXaxis()->SetBinLabel(2,"4-9");
	h_p3s->GetXaxis()->SetBinLabel(3,"9-15");
	h_p3s->GetXaxis()->SetBinLabel(4,"15-30");


	h_c3s->GetXaxis()->CenterTitle();
	h_p3s->GetXaxis()->CenterTitle();
	h_c3s->GetXaxis()->SetTitle("");
	h_p3s->GetXaxis()->SetTitle("GeV/c^{2}");

	h_c3s->GetYaxis()->SetRangeUser(0.96, 1.04) ;
	h_p3s->GetYaxis()->SetRangeUser(0.96, 1.04) ;

	h_c3s->GetYaxis()->CenterTitle();
	h_p3s->GetYaxis()->CenterTitle();
	h_c3s->GetYaxis()->SetTitle("(#varepsilon #times acc) ratio");
	h_p3s->GetYaxis()->SetTitle("(#varepsilon #times acc) ratio");

	TLine* lineone = new TLine();
	lineone->SetLineColor(kRed);
	lineone->SetLineStyle(kDashed);

	c1->cd(1);
	h_c3s->Draw();
	lineone->DrawLine(0,1,4,1);
	c1->cd(2);
	h_p3s->Draw();
	lineone->DrawLine(1,1,4,1);

//	CMS_lumi_simulation((TPad*) c1->GetPad(1),101, 33);
//	CMS_lumi_simulation((TPad*) c1->GetPad(2),101, 33);

	c1->SaveAs("./Plots/MC23ratio.pdf");
	f_res->Close();


	
}
