#include "../BDT/bininfo.h"
#define _TS 1
int getNomBkgO(ana_bins ab){return 0;}
#include "../plots/measurement.cxx"

void ARC_MVAmethod_check_cent(){
	TGraphAsymmErrors* g1 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g2 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g3 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g4 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g5 = new TGraphAsymmErrors();
	TGraphAsymmErrors* g6 = new TGraphAsymmErrors();
	auto fillgraph = [&](){
		int counter = 0;
//		for ( auto ab : {ana_bm_comb["3c"][0],ana_bm_comb["3c"][1],ana_bm_comb["3p"][0]}){
			TCanvas* c1 = new TCanvas("c1","",850, 600);

		for ( auto abv : {ana_bm_comb["3c"]}){
			for(auto ab : abv){
			double bl = Get_BDT(100019111111, ab);
			if(ab.bintype ==kCent){
			auto res_smpl1 = getRAAValue(true, ab, "CB3:EE:FF", bl, 1, 1, 100019111111);

			auto res_smpl2 = getRAAValue(true, ab, "CB3:EE:FF", bl, 1, 1, 111019111111);
			auto res_smpl3 = getRAAValue(true, ab, "CB3:EE:FF", bl, 1, 1, 113019111111);
//			ab.state =2;
			auto res_smpl4 = getRAAValue(true, ab, "CB3:EE:FF", bl, 1, 1, 114019111111); //100219111111 Problem
			auto res_smpl5 = getRAAValue(true, ab, "CB3:EE:FF", bl, 1, 1, 200019111111); //100219111111 Problem
			double sf = 4;
			double esf = 2;
			g1->AddPoint(0.35 + 1.4* counter, sf* res_smpl1.getVal());
			g2->AddPoint(0.5 + 1.4* counter, sf* res_smpl2.getVal());
			g3->AddPoint(0.75 + 1.4* counter, sf* res_smpl3.getVal());
			g4->AddPoint(0.9 + 1.4* counter, sf* res_smpl4.getVal());
			g5->AddPoint(1.15 + 1.4* counter, res_smpl1.getVal() +res_smpl2.getVal() +res_smpl3.getVal() +res_smpl4.getVal());
			g6->AddPoint(1.3 + 1.4* counter, 1. * res_smpl5.getVal());

			g1->SetPointError(counter, 0, 0, res_smpl1.getError()*esf, esf*res_smpl1.getError());
			g2->SetPointError(counter, 0, 0, res_smpl2.getError()*esf, esf*res_smpl2.getError());
			g3->SetPointError(counter, 0, 0, res_smpl3.getError()*esf, esf*res_smpl3.getError());
			g4->SetPointError(counter, 0, 0, res_smpl4.getError()*esf, esf*res_smpl4.getError());
			auto quad = [](double v1, double v2, double v3, double v4){
				return sqrt(v1* v1 + v2* v2 + v3* v3 + v4* v4);
			};
			g5->SetPointError(counter, 0, 0, 
			quad(res_smpl1.getError()*1 ,res_smpl2.getError()*1 ,res_smpl3.getError()*1 ,res_smpl4.getError()*1),
			quad(res_smpl1.getError()*1 ,res_smpl2.getError()*1 ,res_smpl3.getError()*1 ,1*res_smpl4.getError())
			);
			g6->SetPointError(counter, 0, 0, res_smpl5.getError()*1.0, 1.*res_smpl5.getError());
			counter ++;

			c1->cd();

			g1->SetMarkerStyle(kFullCircle);
			g2->SetMarkerStyle(kFullCircle);
			g3->SetMarkerStyle(kFullCircle);
			g4->SetMarkerStyle(kFullCircle);
			g5->SetMarkerStyle(kFullCircle);
			g6->SetMarkerStyle(kFullCircle);

			g1->SetMarkerColor(kBlack);
			g1->SetLineColor(kBlack);

			g2->SetMarkerColor(kRed-2);
			g2->SetLineColor(kRed-2);

			g3->SetMarkerColor(kOrange+8);
			g3->SetLineColor(kOrange+8);

			g4->SetMarkerColor(kTeal-2);
			g4->SetLineColor(kTeal-2);

			g5->SetMarkerColor(kRed-4);
			g5->SetLineColor(kRed-4);

			g6->SetMarkerColor(kViolet+10);
			g6->SetLineColor(kViolet+10);

			g1->Draw("APE");
			g2->Draw("PE");
			g3->Draw("PE");
			g4->Draw("PE");
			g5->Draw("PE");
			g6->Draw("PE");


			TFile* fout = new TFile(Form("./corryield/corryield_cbin%d-%d_3S.root",ab.cl, ab.ch), "recreate");
			fout->cd();
			g1->SetName("3S_g1");
			g2->SetName("3S_g2");
			g3->SetName("3S_g3");
			g4->SetName("3S_g4");
			g5->SetName("3S_g5");
			g6->SetName("3S_g6");
			g1->Write();
			g2->Write();
			g3->Write();
			g4->Write();
			g5->Write();
			g6->Write();
			fout->Close();
			}
			}
		}
		TLegend* leg = new TLegend(0.55,0.25,0.90,0.75);
		leg->SetHeader("Left to right #rightarrow descending order");
		leg->AddEntry(g1, "nominal, projected blind #1", "pe");
		leg->AddEntry(g2, "nominal, projected blind #2", "pe");
		leg->AddEntry(g3, "nominal, projected blind #3", "pe");
		leg->AddEntry(g4, "nominal, projected blind #4", "pe");
		leg->AddEntry(g5, "nominal, sum of blind(#1~#4)", "pe");
		leg->AddEntry(g6, "nominal, full data", "pe");
		leg->SetBorderSize(0);
		TLine* line_cut = new TLine();
		line_cut->SetLineWidth(2);
		line_cut->SetLineColor(kBlack);
		line_cut->SetLineStyle(2);
//		double ref1, ref2, ref3, ref4;
		double ref[4] = {g6->GetPointY(0),g6->GetPointY(1),g6->GetPointY(2),g6->GetPointY(3)};
		for( auto idx : ROOT::TSeqI(4) ){
			std::cout << ref[idx] << std::endl;
			g1->SetPointY(idx,g1->GetPointY(idx)/ ref[idx]);
			g2->SetPointY(idx,g2->GetPointY(idx)/ ref[idx]);
			g3->SetPointY(idx,g3->GetPointY(idx)/ ref[idx]);
			g4->SetPointY(idx,g4->GetPointY(idx)/ ref[idx]);
			g5->SetPointY(idx,g5->GetPointY(idx)/ ref[idx]);
			g6->SetPointY(idx,g6->GetPointY(idx)/ ref[idx]);

			g1->SetPointEYhigh(idx,g1->GetErrorYhigh(idx)/ ref[idx]);
			g2->SetPointEYhigh(idx,g2->GetErrorYhigh(idx)/ ref[idx]);
			g3->SetPointEYhigh(idx,g3->GetErrorYhigh(idx)/ ref[idx]);
			g4->SetPointEYhigh(idx,g4->GetErrorYhigh(idx)/ ref[idx]);
			g5->SetPointEYhigh(idx,g5->GetErrorYhigh(idx)/ ref[idx]);
			g6->SetPointEYhigh(idx,g6->GetErrorYhigh(idx)/ ref[idx]);

			g1->SetPointEYlow(idx,g1->GetErrorYlow(idx)/ ref[idx]);
			g2->SetPointEYlow(idx,g2->GetErrorYlow(idx)/ ref[idx]);
			g3->SetPointEYlow(idx,g3->GetErrorYlow(idx)/ ref[idx]);
			g4->SetPointEYlow(idx,g4->GetErrorYlow(idx)/ ref[idx]);
			g5->SetPointEYlow(idx,g5->GetErrorYlow(idx)/ ref[idx]);
			g6->SetPointEYlow(idx,g6->GetErrorYlow(idx)/ ref[idx]);
		}

		g1->GetXaxis()->SetLimits(0,11.1);
		g1->GetXaxis()->SetRangeUser(0,11.1);
		g1->GetYaxis()->SetLimits(-1.0,3.0);
		g1->GetYaxis()->SetRangeUser(-1.0,3.0);
		g1->GetYaxis()->SetTitle("Normalized #Upsilon(3S) yield");
		g1->GetYaxis()->CenterTitle();

		TLatex* tl =new TLatex();
		tl->SetTextSize(0.031);
		
		c1->cd();
		g1->Draw("APE");
		g2->Draw("PE");
		g3->Draw("PE");
		g4->Draw("PE");
		g5->Draw("PE");
		g6->Draw("PE");
		line_cut->DrawLine(1.5, -1.0, 1.5, 3.0);
		line_cut->DrawLine(2.9, -1.0, 2.9, 3.0);
		line_cut->DrawLine(4.3, -1.0, 4.3, 3.0);
		tl->DrawLatex(0.35,2.8, "0-30%");
		tl->DrawLatex(1.8, 2.8, "30-50%");
		tl->DrawLatex(3.2, 2.8, "50-70%");
		tl->DrawLatex(4.6, 2.8, "70-90%");

		leg->Draw();
		c1->SaveAs("~/Upsilon3S/checkout/blind_result_check_cent.pdf");
		c1->SaveAs("~/Upsilon3S/checkout/blind_result_check_cent.png");

		TCanvas* c2 = new TCanvas("c2","",850, 600);
		c2->cd();


//		double ref1, ref2, ref3, ref4;
//		double ref[4] = {g1->GetPointY(0),g1->GetPointY(1),g1->GetPointY(2),g1->GetPointY(3)};
		for( auto idx : ROOT::TSeqI(4) ){
			std::cout << ref[idx] << std::endl;
			g1->SetPointEYhigh(idx,fabs(g1->GetErrorYhigh(idx)/ 1.));// g1->GetPointY(idx)) );
			g2->SetPointEYhigh(idx,fabs(g2->GetErrorYhigh(idx)/ 1.));// g2->GetPointY(idx)) );
			g3->SetPointEYhigh(idx,fabs(g3->GetErrorYhigh(idx)/ 1.));// g3->GetPointY(idx)) );
			g4->SetPointEYhigh(idx,fabs(g4->GetErrorYhigh(idx)/ 1.));// g4->GetPointY(idx)) );
			g5->SetPointEYhigh(idx,fabs(g5->GetErrorYhigh(idx)/ 1.));// g5->GetPointY(idx)) );
			g6->SetPointEYhigh(idx,fabs(g6->GetErrorYhigh(idx)/ 1.));// g6->GetPointY(idx)) );

			g1->SetPointEYlow(idx,fabs(g1->GetErrorYlow(idx)/ 1.));// g1->GetPointY(idx)) );
			g2->SetPointEYlow(idx,fabs(g2->GetErrorYlow(idx)/ 1.));// g2->GetPointY(idx)) );
			g3->SetPointEYlow(idx,fabs(g3->GetErrorYlow(idx)/ 1.));// g3->GetPointY(idx)) );
			g4->SetPointEYlow(idx,fabs(g4->GetErrorYlow(idx)/ 1.));// g4->GetPointY(idx)) );
			g5->SetPointEYlow(idx,fabs(g5->GetErrorYlow(idx)/ 1.));// g5->GetPointY(idx)) );
			g6->SetPointEYlow(idx,fabs(g6->GetErrorYlow(idx)/ 1.));// g6->GetPointY(idx)) );

			g1->SetPointY(idx,0);
			g2->SetPointY(idx,0);
			g3->SetPointY(idx,0);
			g4->SetPointY(idx,0);
			g5->SetPointY(idx,0);
			g6->SetPointY(idx,0);


		}
		g1->GetXaxis()->SetLimits(0,11.1);
		g1->GetXaxis()->SetRangeUser(0,11.1);
		g1->GetYaxis()->SetLimits(-1.0,1.0);
		g1->GetYaxis()->SetRangeUser(-1.0,1.0);
		g1->GetYaxis()->SetTitle("Absolute #Upsilon(3S) uncertainty");
		g1->GetYaxis()->CenterTitle();

		g1->Draw("APE");
		g2->Draw("PE");
		g3->Draw("PE");
		g4->Draw("PE");
		g5->Draw("PE");
		g6->Draw("PE");
		line_cut->DrawLine(1.5, -1.0, 1.5, 1.0);
		line_cut->DrawLine(2.9, -1.0, 2.9, 1.0);
		line_cut->DrawLine(4.3, -1.0, 4.3, 1.0);
		tl->DrawLatex(0.35,1.02, "0-30%");
		tl->DrawLatex(1.8 ,0.8, "30-50%");
		tl->DrawLatex(3.2 ,0.8, "50-70%");
		tl->DrawLatex(4.6 ,0.8, "70-90%");

		leg->Draw();
		c2->SaveAs("~/Upsilon3S/checkout/blind_result_check_cent_rel.pdf");
		c2->SaveAs("~/Upsilon3S/checkout/blind_result_check_cent_rel.png");
	};
	fillgraph();

}
