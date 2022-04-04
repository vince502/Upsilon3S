#include "../BDT/bininfo.h"
#define _TS 1
int getNomBkgO(ana_bins ab){return 0;}
#include "../plots/measurement.cxx"

void ARC_MVAmethod_check(){
	TGraphAsymmErrors* g1 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g2 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g3 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g4 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g5 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g6 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g7 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g8 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g9 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g10 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g11 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g12 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g13 = new TGraphAsymmErrors();
	auto fillgraph = [&](){
		int counter = 0;
//		for ( auto ab : {ana_bm_comb["3c"][0],ana_bm_comb["3c"][1],ana_bm_comb["3p"][0]}){
		for ( auto ab : {ana_bm_comb["3c"][0]}){
			if(ab.bintype !=kCent){
			auto res_nom = getRAAValue(true, ab, "CB3:EE:GC", -2, 1, 0, 100019111111);
			auto res_fitsig = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 0, 113019111111);
			double bl = -2;
			if(ab.bintype ==kInt) bl = 0.2290;
//			auto res_wider_sblow = getRAAValue(true, ab, "CB3:EE:GC", bl, 1, 0, 100029111111); //original
dbg();
			auto res_wider_sblow = getRAAValue(true, ab, "CB3:EE:GCnobdtcheck", -1.00000, 1, 0, 20000000000);
			bl = -2;
//			auto res_smpl1 = getRAAValue(true, ab, "CB3:EE:GC", bl, 1, 0, 20000000011); //original
			auto res_smpl1 = getRAAValue(true, ab, "CB3:EE:GCnobdtcheck", -1.00000, 1, 0, 20000000000, true);

			auto res_smpl2 = getRAAValue(true, ab, "CB3:EE:GC", 0.2290, 1, 0, 20000000000);
			auto res_smpl3 = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 0, 20000000000);
//			ab.state =2;
			auto res_smpl4 = getRAAValue(true, ab, "CB3:EE:GC", 0.2290, 1, 0, 20000000000, false, false, 2);
			auto res_smpl5 = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 0, 20000000000, false, false, 2);
			auto res_smpl6 = getRAAValue(true, ab, "CB3:EE:GCnobdtcheck", -1.00000, 1, 0, 20000000000, true, false, 2);
			auto res_smpl7 = getRAAValue(true, ab, "CB3:EE:GCnobdtcheck", -1.00000, 1, 0, 20000000000, false, false, 2);
//			auto res_smpl1 = getRAAValue(true, ab, "CB3:EE:GCnobdtcheck", 0.4, 1, 0, 20000000000, false);

			g1->AddPoint(0.5 + counter , res_nom.getVal());
			g2->AddPoint(0.65+ counter, res_fitsig.getVal());
			g3->AddPoint(0.8 + counter, res_wider_sblow.getVal());
			g4->AddPoint(0.95 + counter, res_smpl1.getVal());
			g5->AddPoint(1.1 + counter, res_smpl2.getVal());
			g6->AddPoint(1.25 + counter, res_smpl3.getVal());
			g7->AddPoint(1.4 + counter, res_smpl4.getVal());
			g8->AddPoint(1.55 + counter, res_smpl5.getVal());
			g9->AddPoint(1.7 + counter, res_smpl6.getVal());
			g10->AddPoint(1.95 + counter, res_smpl7.getVal());
			g1->SetPointError(counter, 0, 0, res_nom.getError(), res_nom.getError());
			g2->SetPointError(counter, 0, 0, res_fitsig.getError(), res_fitsig.getError());
			g3->SetPointError(counter, 0, 0, res_wider_sblow.getError(), res_wider_sblow.getError());
			g4->SetPointError(counter, 0, 0, res_smpl1.getError(), res_smpl1.getError());
			g5->SetPointError(counter, 0, 0, res_smpl2.getError(), res_smpl2.getError());
			g6->SetPointError(counter, 0, 0, res_smpl3.getError(), res_smpl3.getError());
			g7->SetPointError(counter, 0, 0, res_smpl4.getError(), res_smpl4.getError());
			g8->SetPointError(counter, 0, 0, res_smpl5.getError(), res_smpl5.getError());
			g9->SetPointError(counter, 0, 0, res_smpl6.getError(), res_smpl6.getError());
			g10->SetPointError(counter, 0, 0, res_smpl7.getError(), res_smpl7.getError());
			}
			if(ab.bintype ==kCent){
			auto res_nom = getRAAValue(true, ab, "CB3:EE:FF", -2, 1, 0, 10000000016);
			auto res_fitsig = getRAAValue(true, ab, "CB3:EE:FF", -2, 1, 0, 100019111111);
			auto res_wider_sblow = getRAAValue(true, ab, "CB3:EE:FF", -2, 1, 0, 100029111111);
			g1->AddPoint(0.5 + counter , res_nom.getVal());
			g2->AddPoint(0.65+ counter, res_fitsig.getVal());
			g3->AddPoint(0.8 + counter, res_wider_sblow.getVal());
			g1->SetPointError(counter, 0, 0, res_nom.getError(), res_nom.getError());
			g2->SetPointError(counter, 0, 0, res_fitsig.getError(), res_fitsig.getError());
			g3->SetPointError(counter, 0, 0, res_wider_sblow.getError(), res_wider_sblow.getError());
			}
			counter ++;
		}
	};
	fillgraph();


	
	TCanvas* c1 = new TCanvas("c1","",700, 600);
	c1->cd();

	TLegend* leg = new TLegend(0.55,0.35,0.9,0.75);
	leg->AddEntry(g1, "Nominal cut 0.2290", "pe");
	leg->AddEntry(g2, "Nominal cut 0.2620", "pe");
	leg->AddEntry(g3, "No BDT QQVtxProb > 0.00", "pe");
	leg->AddEntry(g4, "No BDT QQVtxProb > 0.01", "pe");
	leg->AddEntry(g5, "UB Nominal cut 0.2290", "pe");
	leg->AddEntry(g6, "UB Nominal cut 0.2620", "pe");
	leg->AddEntry(g7, "(2S)UB Nominal cut 0.2290", "pe");
	leg->AddEntry(g8, "(2S)UB Nominal cut 0.2620", "pe");
	leg->AddEntry(g9, "(2S)No BDT QQVtxProb > 0.00", "pe");
	leg->AddEntry(g10, "(2S)No BDT QQVtxProb > 0.01", "pe");
	leg->SetBorderSize(0);

	g1->GetXaxis()->SetLimits(0,4.1);
	g1->GetXaxis()->SetRangeUser(0,4.1);
	g1->GetYaxis()->SetLimits(0,.25);
	g1->GetYaxis()->SetRangeUser(0,.25);
	g1->SetMarkerStyle(kFullCircle);
	g2->SetMarkerStyle(kFullCircle);
	g3->SetMarkerStyle(kFullCircle);
	g4->SetMarkerStyle(kFullCircle);
	g5->SetMarkerStyle(kFullCircle);
	g6->SetMarkerStyle(kFullCircle);
	g7->SetMarkerStyle(kFullCircle);
	g8->SetMarkerStyle(kFullCircle);
	g9->SetMarkerStyle(kFullCircle);
	g10->SetMarkerStyle(kFullCircle);
	g1->SetMarkerColor(kBlack);
	g1->SetLineColor(kBlack);

	g2->SetMarkerColor(kRed-2);
	g2->SetLineColor(kRed-2);

	g3->SetMarkerColor(kOrange+8);
	g3->SetLineColor(kOrange+8);

	g4->SetMarkerColor(kTeal-2);
	g4->SetLineColor(kTeal-2);

	g5->SetMarkerColor(kBlue+1);
	g5->SetLineColor(kBlue+1);

	g6->SetMarkerColor(kMagenta-2);
	g6->SetLineColor(kMagenta-2);

	g7->SetMarkerColor(kBlue+1);
	g7->SetLineColor(kBlue+1);

	g8->SetMarkerColor(kMagenta-2);
	g8->SetLineColor(kMagenta-2);

	g9->SetMarkerColor(kOrange+8);
	g9->SetLineColor(kOrange+8);

	g10->SetMarkerColor(kTeal-2);
	g10->SetLineColor(kTeal-2);

	g1->Draw("APE");
	g2->Draw("PE");
	g3->Draw("PE");
	g4->Draw("PE");
	g5->Draw("PE");
	g6->Draw("PE");
	g7->Draw("PE");
	g8->Draw("PE");
	g9->Draw("PE");
	g10->Draw("PE");
	leg->Draw();
}
