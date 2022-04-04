#include "../.workdir.h"
#include "../BDT/bininfo.h"
#define _TS 100019111111

TFile* f_hist;

void DrawSignif(ana_bins ab = ana_bm_comb["3c"][0]){
	long ts= _TS;
	
	f_hist = TFile::Open(Form("%s/BDT/Significance_hist/HIST_train%dS_for%dS_bdtpt_%d_%d_%ld_pt_%d-%d_rap_-24-24_cbin_%d-%d_vp_0.0000_S2.root", workdir.Data(), ab.train_state, ab.state, ab.bpl, ab.bph, ts, ab.pl, ab.ph, ab.cl, ab.ch) );
	auto thekeys = f_hist->GetListOfKeys();
	TCanvas* cx = new TCanvas("cx","", 700, 600);	
	cx->SetLeftMargin(0.13);
	auto g1 =  (TGraph*) f_hist->Get(Form("%s/HISTO", thekeys->At(0)->GetName()));
	auto g2 =  (TGraph*) f_hist->Get(Form("%s/TR1_HISTO", thekeys->At(0)->GetName()));
	auto g3 =  (TGraph*) f_hist->Get(Form("%s/TR2_HISTO", thekeys->At(0)->GetName()));
//	auto c1 =  (TCanvas*) f_hist->Get(Form("%s/two_signif", thekeys->At(0)->GetName()));
//	return (TCanvas*) f_hist->Get(Form("%s/two_signif", thekeys->At(0)->GetName()));
	g1->GetXaxis()->SetRangeUser(-0.3, 0.55);
	g1->GetXaxis()->SetTitle("BDT score");
	g1->GetYaxis()->SetRangeUser(0.134-0.03, 0.134+0.02);
	g1->GetYaxis()->SetTitle("Significance (a.u.)");
	g1->Draw("AL");
	g2->Draw("L");
	g3->Draw("L");
	cx->SaveAs(Form("../checkout/tscol/signif_%ld_hist_%dS_pt%d-%d_cent%d-%d.pdf", _TS, ab.state, ab.pl, ab.ph, ab.centl, ab.centh) );
//	c1->SaveAs(Form("signif_hist_%dS_pt%d-%d_cent%d-%d.pdf", ab.state, ab.pl, ab.ph, ab.centl, ab.centh) );
}
//void DrawSignif(ana_bins ab = ana_bm_comb["3c"][0]){
//	long ts= _TS;
//	
//	auto f_hist = TFile::Open(Form("%s/BDT/Significance_hist/HIST_train%dS_for%dS_bdtpt_%d_%d_%ld_pt_%d-%d_rap_-24-24_cbin_%d-%d_vp_0.0000_S2.root", workdir.Data(), ab.train_state, ab.state, ab.bpl, ab.bph, ts, ab.pl, ab.ph, ab.cl, ab.ch) );
//	auto thekeys = f_hist->GetListOfKeys();
//	TCanvas* c1 = (TCanvas*) f_hist->Get(Form("%s/two_signif", thekeys->At(0)->GetName()));
//	c1->SaveAs(Form("signif_hist_%dS_pt%d-%d_cent%d-%d.pdf", ab.state, ab.pl, ab.ph, ab.centl, ab.centh) );
//}
