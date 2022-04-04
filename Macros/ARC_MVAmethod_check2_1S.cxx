#include "../BDT/bininfo.h"
#define _TS 1
int getNomBkgO(ana_bins ab){return 0;}
#include "../plots/measurement.cxx"

void ARC_MVAmethod_check2_1S(){
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
			auto res_nom = getRAAValue(true, ab, "CB3:EE:GC", -2, 1, 1, 100019111111, false, false, 1);
			auto res_fitsig = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 1, 111019111111, false, false, 1);
			double bl = -2;
			if(ab.bintype ==kInt) bl = 0.2290;
//			auto res_wider_sblow = getRAAValue(true, ab, "CB3:EE:GC", bl, 1, 0, 100029111111); //original
dbg();
//			auto res_wider_sblow = getRAAValue(true, ab, "CB3:EE:GCnobdtcheck", -1.00000, 1, 0, 20000000000);
			auto res_wider_sblow = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 1, 113019111111, false, false, 1);
			bl = -2;
//			auto res_smpl1 = getRAAValue(true, ab, "CB3:EE:GC", bl, 1, 0, 20000000011); //original
			auto res_smpl1 = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 1, 114019111111, false, false, 1);

			auto res_smpl2 = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 1, 200019111111, false, false, 1);
			auto res_smpl3 = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 1, 112019111111, false, false, 1);
//			ab.state =2;
			auto res_smpl4 = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 1, 110019111111, false, false, 1); //100219111111 Problem

			auto res_smpl5 = getRAAValue(true, ab, "CB3:EE:GC", 0.2620, 1, 1, 210019111111, false, false, 1);
			auto res_smpl6 = getRAAValue(true, ab, "CB3:EE:GC", -0.9990, 1, 1, 100019111111, false, false, 1);
			auto res_smpl7 = getRAAValue(true, ab, "CB3:EE:GC", -0.9990, 1, 1, 111019111111, false, false, 1);
			auto res_smpl8 = getRAAValue(true, ab, "CB3:EE:GC", -0.9990, 1, 1, 113019111111, false, false, 1);
			auto res_smpl9 = getRAAValue(true, ab, "CB3:EE:GC", -0.9990, 1, 1, 114019111111, false, false, 1);
			auto res_smpl10 = getRAAValue(true, ab, "CB3:EE:GC", -0.9990, 1, 1, 200019111111, false, false, 1);
//			auto res_smpl6 = getRAAValue(true, ab, "CB3:EE:GCnobdtcheck", -1.00000, 1, 0, 20000000000, true, false, 2);
//			auto res_smpl7 = getRAAValue(true, ab, "CB3:EE:GCnobdtcheck", -1.00000, 1, 0, 20000000000, false, false, 2);
//			auto res_smpl1 = getRAAValue(true, ab, "CB3:EE:GCnobdtcheck", 0.4, 1, 0, 20000000000, false);

			g1->AddPoint(0.2 + counter , 4* res_nom.getVal());
			g2->AddPoint(0.35+ counter, 4* res_fitsig.getVal());
			g3->AddPoint(0.5 + counter, 4* res_wider_sblow.getVal());
			g4->AddPoint(0.65 + counter, 4* res_smpl1.getVal());
			g5->AddPoint(0.8 + counter, 1 * res_smpl2.getVal());//unblind
			g6->AddPoint(1.05 + counter, 4 *res_smpl3.getVal());
			g7->AddPoint(1.2 + counter, 4* res_smpl4.getVal());
			g8->AddPoint(1.35 + counter, 1* res_smpl5.getVal());//unblind
			g9->AddPoint(1.6 + counter, 4* res_smpl6.getVal());
			g10->AddPoint(1.85 + counter, 4* res_smpl7.getVal());
			g11->AddPoint(2.0 + counter, 4* res_smpl8.getVal());
			g12->AddPoint(2.15 + counter, 4* res_smpl9.getVal());
			g13->AddPoint(2.3 + counter, 1* res_smpl10.getVal());//unblind
			g1->SetPointError(counter, 0, 0, res_nom.getError()*2, 2*res_nom.getError());
			g2->SetPointError(counter, 0, 0, res_fitsig.getError()*2, 2*res_fitsig.getError());
			g3->SetPointError(counter, 0, 0, res_wider_sblow.getError()*2, 2*res_wider_sblow.getError());
			g4->SetPointError(counter, 0, 0, res_smpl1.getError()*2, 2*res_smpl1.getError());
			g5->SetPointError(counter, 0, 0, res_smpl2.getError(), res_smpl2.getError());
			g6->SetPointError(counter, 0, 0, res_smpl3.getError()*2, 2*res_smpl3.getError());
			g7->SetPointError(counter, 0, 0, res_smpl4.getError()*2, 2*res_smpl4.getError());
			g8->SetPointError(counter, 0, 0, res_smpl5.getError(), res_smpl5.getError());
			g9->SetPointError(counter, 0, 0, res_smpl6.getError()*2, 2*res_smpl6.getError());
			g10->SetPointError(counter, 0, 0, res_smpl7.getError()*2, 2*res_smpl7.getError());
			g11->SetPointError(counter, 0, 0, res_smpl8.getError()*2, 2*res_smpl8.getError());
			g12->SetPointError(counter, 0, 0, res_smpl9.getError()*2, 2*res_smpl9.getError());
			g13->SetPointError(counter, 0, 0, res_smpl10.getError(), res_smpl10.getError());
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


	
	TCanvas* c1 = new TCanvas("c1","",800, 600);
	c1->cd();

	TLegend* leg = new TLegend(0.5,0.25,0.90,0.75);
	leg->SetHeader("Left to right #rightarrow descending order");
	leg->AddEntry(g1, "nominal train, dataset1 blind", "pe");
	leg->AddEntry(g2, "nominal train, dataset2 blind", "pe");
	leg->AddEntry(g3, "nominal train, dataset3 blind", "pe");
	leg->AddEntry(g4, "nominal train, dataset4 blind", "pe");
	leg->AddEntry(g5, "nominal train, Full data", "pe");
	leg->AddEntry(g6, "alterante train, nominal BDT, dataset1 blind", "pe");
	leg->AddEntry(g7, "alterante train, nominal BDT, dataset2 blind", "pe");
	leg->AddEntry(g8, "alterante train, nominal BDT, Full", "pe");
	leg->AddEntry(g9, "no BDT, dataset1 blind", "pe");
	leg->AddEntry(g10,"no BDT, dataset2 blind", "pe");
	leg->AddEntry(g11,"no BDT, dataset3 blind", "pe");
	leg->AddEntry(g12,"no BDT, dataset4 blind", "pe");
	leg->AddEntry(g13,"no BDT, Full", "pe");
	leg->SetBorderSize(0);

	TLine* line_cut = new TLine();

	g1->GetXaxis()->	SetLimits(0, 5.1);
	g1->GetXaxis()->SetRangeUser( 0, 5.1);
	g1->GetYaxis()->	SetLimits(140000, 180000);
	g1->GetYaxis()->SetRangeUser( 140000, 180000);
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
	g11->SetMarkerStyle(kFullCircle);
	g12->SetMarkerStyle(kFullCircle);
	g13->SetMarkerStyle(kFullCircle);

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

	g6->SetMarkerColor(kBlack);
	g6->SetLineColor(kBlack);

	g7->SetMarkerColor(kRed-2);
	g7->SetLineColor(kRed-2);

	g8->SetMarkerColor(kBlue+1);
	g8->SetLineColor(kBlue+1);

	g9->SetMarkerColor(kBlack);
	g9->SetLineColor(kBlack);

	g10->SetMarkerColor(kRed-2);
	g10->SetLineColor(kRed-2);

	g11->SetMarkerColor(kOrange+8);
	g11->SetLineColor(kOrange+8);

	g12->SetMarkerColor(kTeal-2);
	g12->SetLineColor(kTeal-2);

	g13->SetMarkerColor(kBlue+1);
	g13->SetLineColor(kBlue+1);

	line_cut->SetLineWidth(2);
	line_cut->SetLineColor(kBlack);
	line_cut->SetLineStyle(2);
	g1->Draw("APE");
	g2->Draw("PE");
	g3->Draw("PE");
	g4->Draw("PE");
	g5->Draw("PE");
	line_cut->DrawLine(0.925, -0.1, 0.925, 0.25);
	g6->Draw("PE");
	g7->Draw("PE");
	g8->Draw("PE");
	line_cut->DrawLine(1.475, -0.1, 1.475, 0.25);
	g9->Draw("PE");
	g10->Draw("PE");
	g11->Draw("PE");
	g12->Draw("PE");
	g13->Draw("PE");
	line_cut->DrawLine(2.425, -0.1, 2.425, 0.25);
	leg->Draw();
	std::cout << "YIELD 1: "<< g1->GetPointY(0) << std::endl;
	std::cout << "YIELD 2: "<< g2->GetPointY(0) << std::endl;
	std::cout << "YIELD 3: "<< g3->GetPointY(0) << std::endl;
	std::cout << "YIELD 4: "<< g4->GetPointY(0) << std::endl;
	std::cout << "YIELD 5: "<< g5->GetPointY(0) << std::endl;
	std::cout << "YIELD 6: "<< g6->GetPointY(0) << std::endl;
	std::cout << "YIELD 7: "<< g7->GetPointY(0) << std::endl;
	std::cout << "YIELD 8: "<< g8->GetPointY(0) << std::endl;
	std::cout << "YIELD 9: "<< g9->GetPointY(0) << std::endl;
	std::cout << "YIELD 10: "<< g10->GetPointY(0) << std::endl;
	std::cout << "YIELD 11: "<< g11->GetPointY(0) << std::endl;
	std::cout << "YIELD 12: "<< g12->GetPointY(0) << std::endl;
	std::cout << "YIELD 13: "<< g13->GetPointY(0) << std::endl;
	TFile* fout = new TFile("corryield_1S.root", "recreate");
	fout->cd();
	g1->SetName("1S_g1");
	g2->SetName("1S_g2");
	g3->SetName("1S_g3");
	g4->SetName("1S_g4");
	g5->SetName("1S_g5");
	g6->SetName("1S_g6");
	g7->SetName("1S_g7");
	g8->SetName("1S_g8");
	g9->SetName("1S_g9");
	g10->SetName("1S_g10");
	g11->SetName("1S_g11");
	g12->SetName("1S_g12");
	g13->SetName("1S_g13");
	g1->Write();
	g2->Write();
	g3->Write();
	g4->Write();
	g5->Write();
	g6->Write();
	g7->Write();
	g8->Write();
	g9->Write();
	g10->Write();
	g11->Write();
	g12->Write();
	g13->Write();
	fout->Close();
}
