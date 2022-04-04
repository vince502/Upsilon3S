//#define _TS 9999999999
//#define _TS 10000000016
//#define _TS 100019111111
#define _TS 200019111111
#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#   include "../LLR_CCorder_9999999999.h"
#   define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
#   include "../LLR_CCorder_10000000016.h"
#   define getNomBkgO getNomBkgO_10000000016
#endif

#if _TS == 100019111111 && __has_include("../LLR_CCorder_100019111111.h")
#   include "../LLR_CCorder_100019111111.h"
#   define getNomBkgO getNomBkgO_100019111111
#endif

#if _TS == 200019111111 && __has_include("../LLR_CCorder_200019111111.h")
#   include "../LLR_CCorder_200019111111.h"
#   define getNomBkgO getNomBkgO_200019111111
#endif

#if _TS == 10000000003 && __has_include("../LLR_CCorder_10000000003.h")
#   include "../LLR_CCorder_10000000003.h"
#   define getNomBkgO getNomBkgO_10000000003
#endif

#if _TS != 9999999999
#	define ana_bm ana_bm_comb
#endif
#include "../BDT/bininfo.h"
#include "../BDT/BDTtraindiff.cxx"
#include "../glauberparams_PbPb5TeV.h"

TGraphAsymmErrors analysis_DRplot_sys(TFile* hf, TFile* hsys, TFile* ppsys){
	TH1D* hp3s = (TH1D*) hf->Get("rp3S");
//	TH1D* hp2s = (TH1D*) hf->Get("rp2S");
	TH1D* hc3s = (TH1D*) hf->Get("rc3S");
//	TH1D* hc2s = (TH1D*) hf->Get("rc2S");

	TH1D* hp3s_sys = (TH1D*) hsys->Get("syst_comp/hsys_tot_p3S");
//	TH1D* hp2s_sys = (TH1D*) hsys->Get("syst_comp/hsys_tot_p2S");
	TH1D* hc3s_sys = (TH1D*) hsys->Get("syst_comp/hsys_tot_c3S");
//	TH1D* hc2s_sys = (TH1D*) hsys->Get("syst_comp/hsys_tot_c2S");

	TH1D* hpp_p3s_sys = (TH1D*) ppsys->Get("hptPP_3Sover2S_ratio");
//	TH1D* hpp_p2s_sys = (TH1D*) ppsys->Get("hptPP_2S_yield");
	TH1D* hpp_i3s_sys = (TH1D*) ppsys->Get("hIntPP_3Sover2S_ratio");
//	TH1D* hpp_i2s_sys = (TH1D*) ppsys->Get("hIntPP_2S_yield");

	TH1D* hpp_p3s_unc = (TH1D*) ppsys->Get("hptPP_3S_yield_total");
//	TH1D* hpp_p2s_unc = (TH1D*) ppsys->Get("hptPP_2S_yield_total");
	TH1D* hpp_i3s_unc = (TH1D*) ppsys->Get("hIntPP_3S_yield_total");
//	TH1D* hpp_i2s_unc = (TH1D*) ppsys->Get("hIntPP_2S_yield_total");

	TGraphAsymmErrors g_p3s, g_p3s_sys;
//	TGraphAsymmErrors g_p2s, g_p2s_sys;
	TGraphAsymmErrors g_c3s, g_c3s_sys;
//	TGraphAsymmErrors g_c2s, g_c2s_sys;
	TGraphAsymmErrors g_i3s, g_i3s_sys;
//	TGraphAsymmErrors g_i2s, g_i2s_sys;
	
//////////////////////////NOMINAL VALUE, STATISTICAL ERROR///////////////////////////

	auto fillgraph = [&](TH1D& hist, TGraphAsymmErrors& grap, string abt){
		auto vab = ana_bm[abt.c_str()];
		std::sort(vab.begin(), vab.end(), [](ana_bins &x, ana_bins &y){
			return x.plot_idx < y.plot_idx;}
		);
		for( auto idx : ROOT::TSeqI(1,vab.size()+1,1)){
			auto ab = vab[idx-1];
			std::cout << Form(" idx-1 pl, ph, cl, ch : %d  %d %d %d %d", idx-1, ab.pl, ab.ph, ab.cl, ab.ch) << std::endl;
			if(ab.bintype == kInt){ std::cout << "skipping integrated bin" << std::endl; continue;}
			int plt_idx = ab.plot_idx;
			std::pair<double, double> point_x;
			std::pair<double, double> point_y;
			if(ab.bintype == kCent){
				point_x = glp::Npart[{ab.centl, ab.centh}];
				point_y = {hist.GetBinContent( (vab.size()+1) - idx), hist.GetBinError( (vab.size() +1) - idx)};
			}
			if(ab.bintype == kPt){
				point_x = {((double)( ab.pl + ab.ph ))/2., 0.};//((double)(ab.ph-ab.pl))/2. };
				point_y = {hist.GetBinContent( idx ), hist.GetBinError( idx )};
			}
			grap.AddPoint(point_x.first, point_y.first);
			grap.SetPointError(idx-1, point_x.second, point_x.second, point_y.second, point_y.second);
			if(ab.bintype == kPt){
				grap.GetXaxis()->SetLimits(0,30);
			}

		}
	};

/////////////////////////////////SYSTEMATIC ERRORS///////////////////////////////////

	auto get_taa_err = [](ana_bins x){
		auto taa = glp::Taa[{x.centl, x.centh}];
		return (double) taa.second/taa.first;
	};
	auto quadsum = [](double arg1, double arg2){ return TMath::Sqrt(arg1 * arg1 + arg2 * arg2); };

	auto fillsysgraph = [&](TH1D& hist, TH1D& raahist, TGraphAsymmErrors& grap, string abt){
		auto vab = ana_bm[abt.c_str()];
		std::sort(vab.begin(), vab.end(), [](ana_bins &x, ana_bins &y){
			return x.plot_idx < y.plot_idx;}
		);
		for( auto idx : ROOT::TSeqI(1,vab.size()+1,1)){
			auto ab = vab[idx-1];
			std::cout << Form(" idx-1 pl, ph, cl, ch : %d  %d %d %d %d", idx-1, ab.pl, ab.ph, ab.cl, ab.ch) << std::endl;
			if(ab.bintype == kInt){ std::cout << "skipping integrated bin" << std::endl; continue;}
			int plt_idx = ab.plot_idx;
			std::pair<double, double> point_x;
			std::pair<double, double> point_y;
			double ref_raa;
			auto taa_err = get_taa_err(ab);
			double nom_sys;
			if(ab.bintype == kCent){
				point_x = glp::Npart[{ab.centl, ab.centh}];
				point_x.second=  point_x.second *6;
				ref_raa = raahist.GetBinContent( (vab.size()+1) - idx);
				nom_sys = hist.GetBinContent( (vab.size() +1) - idx);
				point_y = { ref_raa, ref_raa * quadsum(nom_sys,0/* taa_err*/) };
			}
			if(ab.bintype == kPt){
				point_x = {((double)( ab.pl + ab.ph ))/2., ((double)(ab.ph-ab.pl))/2. };
				double pp_sys = hpp_p3s_sys->GetBinContent( idx );  
				ref_raa = raahist.GetBinContent( idx );
				nom_sys = hist.GetBinContent( idx );
				point_y = { ref_raa , ref_raa * quadsum(nom_sys,0/* taa_err*/) };
			}
			grap.AddPoint(point_x.first, point_y.first);
			grap.SetPointError(idx-1, point_x.second, point_x.second, point_y.second, point_y.second);
		}
	};
/////////////////////////////////INTEGRATED BIN///////////////////////////////////

//	g_i2s.AddPoint(2, hc2s->GetBinContent(1)) ;
//	g_i2s.SetPointError(0, 0,0, hc2s->GetBinError(1), hc2s->GetBinError(1) ) ;
	g_i3s.AddPoint(2.5, hc3s->GetBinContent(1)) ;
	g_i3s.SetPointError(0, 0,0, hc3s->GetBinError(1), hc3s->GetBinError(1) ) ;

	double int_sys_width = 0.45;
	double int_pp_sys = hpp_i3s_sys->GetBinContent(1);
//	g_i2s_sys.AddPoint(2, hc2s->GetBinContent(1)) ;
//	g_i2s_sys.SetPointError(0, int_sys_width, int_sys_width, hc2s_sys->GetBinContent(1) *hc2s->GetBinContent(1), hc2s_sys->GetBinContent(1) *hc2s->GetBinContent(1) ) ;
	g_i3s_sys.AddPoint(2.5, hc3s->GetBinContent(1)) ;
	g_i3s_sys.SetPointError(0, int_sys_width, int_sys_width, hc3s_sys->GetBinContent(1) * quadsum( int_pp_sys, hc3s->GetBinContent(1)), hc3s_sys->GetBinContent(1) * quadsum( int_pp_sys, hc3s->GetBinContent(1)) ) ;

//////////////////////////////////////////////////////////////////////////////////

//	fillgraph(*hc2s, g_c2s, "2c");
	fillgraph(*hc3s, g_c3s, "3c");
//	fillgraph(*hp2s, g_p2s, "2p");
	fillgraph(*hp3s, g_p3s, "3p");

//	fillsysgraph(*hc2s_sys, *hc2s, g_c2s_sys, "2c");
	fillsysgraph(*hc3s_sys, *hc3s, g_c3s_sys, "3c");
//	fillsysgraph(*hp2s_sys, *hp2s, g_p2s_sys, "2p");
	fillsysgraph(*hp3s_sys, *hp3s, g_p3s_sys, "3p");

	TCanvas* c1 = new TCanvas("c1","", 1000,900);
	TCanvas* c2 = new TCanvas("c2","", 1000,900);
	TPad* p1_L = new TPad("p1L", "", 0.00, 0., 0.83,1.);
	TPad* p1_R = new TPad("p1R", "", 0.83, 0., 1., 1.);
	TPad* p2 = new TPad("p2", "", 0., 0., 1., 1.);
	p1_L->SetLeftMargin(0.12);
	p2->SetLeftMargin(0.12);
	p1_L->SetBottomMargin(0.12);
	p1_R->SetBottomMargin(0.12);
	p2->SetBottomMargin(0.12);
	p1_L->SetTicks();
	p1_R->SetTicks();
	p2->SetTicks();

	double p2scale = (( 0.83 - 0.12)/ (1. - 0.83) ) ;

	p1_L->SetRightMargin(0);
	p1_R->SetLeftMargin(0);

	c1->cd();
	p1_L->Draw();
	p1_R->Draw();
	c2->cd();
	p2->Draw();

/////////////////////////////////GRAPH ATTR///////////////////////////////////
//	g_c2s.SetLineColor(kBlue);
//	g_p2s.SetLineColor(kBlue);
//	g_i2s.SetLineColor(kBlue);
//	g_c2s.SetMarkerColor(kBlue+2);
//	g_p2s.SetMarkerColor(kBlue+2);
//	g_i2s.SetMarkerColor(kBlue+2);
//
//	g_c2s_sys.SetLineColor(kBlue);
//	g_p2s_sys.SetLineColor(kBlue);
//	g_i2s_sys.SetLineColor(kBlue);
//	g_c2s_sys.SetFillColorAlpha(kAzure-3, 0.25);
//    g_p2s_sys.SetFillColorAlpha(kAzure-3, 0.25);
//    g_i2s_sys.SetFillColorAlpha(kAzure-3, 0.25);

	g_c3s.SetLineColor(kGreen+2);
	g_p3s.SetLineColor(kGreen+2);
	g_i3s.SetLineColor(kGreen+2);
	g_c3s.SetMarkerColor(kGreen+2);
	g_p3s.SetMarkerColor(kGreen+2);
	g_i3s.SetMarkerColor(kGreen+2);

	g_c3s_sys.SetLineColor(kGreen+3);
	g_p3s_sys.SetLineColor(kGreen+3);
	g_i3s_sys.SetLineColor(kGreen+3);
	g_c3s_sys.SetFillColorAlpha(kTeal+5, 0.25);
    g_p3s_sys.SetFillColorAlpha(kTeal+5, 0.25);
    g_i3s_sys.SetFillColorAlpha(kTeal+5, 0.25);

//	g_c2s.SetMarkerStyle(kFullSquare);
//	g_p2s.SetMarkerStyle(kFullSquare);
//	g_i2s.SetMarkerStyle(kFullSquare);
//	g_c2s.SetMarkerSize(1.4);
//	g_p2s.SetMarkerSize(1.4);
//	g_i2s.SetMarkerSize(1.4);

	g_c3s.SetMarkerStyle(kFullSquare);
	g_p3s.SetMarkerStyle(kFullSquare);
	g_i3s.SetMarkerStyle(kFullSquare);
	g_c3s.SetMarkerSize(1.4);
	g_p3s.SetMarkerSize(1.4);
	g_i3s.SetMarkerSize(1.4);
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////Global Uncertainties/////////////////////////////

//	TBox* b_err = new TBox();
//	TBox* b_2serr = new TBox();
	TBox* b_3serr = new TBox();
//	double glb_2serr = 0;label_pos_up
	double glb_3serr = hpp_i3s_unc->GetBinContent(1);
	double glb_errMB_PP = 0;
	double pp_state2s;

///////////////////////////////////////////////////////////////////////////////

//////////////////////////////Auxiliary Drawings///////////////////////////////
	gStyle->SetEndErrorSize(0);

	double yup = 1.6;
	double ydown = 0.0;
	double label_pos_up = yup - 0.2 ;
//	double label_pos_do = yup - 0.6 ;

	TLine* lineone = new TLine();
	lineone->SetLineStyle(kDashed);
	lineone->SetLineWidth(1);

	TLatex* tl = new TLatex();
	tl->SetTextSize(0.037);
	tl->SetTextFont(42);

	TLegend* leg_cent = new TLegend(0.80, 0.5, 0.85, 0.6);
//	leg_cent->AddEntry(&g_c2s, "#Upsilon(2S)", "pl");
	leg_cent->AddEntry(&g_c3s, "#Upsilon(3S)", "pl");
	leg_cent->SetBorderSize(0);
	leg_cent->SetTextFont(42);
	leg_cent->SetTextSize(0.04);

	TLegend* leg_pt = new TLegend(0.65, 0.5, 0.85, 0.6);
//	leg_pt->AddEntry(&g_p2s, "#Upsilon(2S)", "pl");
	leg_pt->AddEntry(&g_p3s, "#Upsilon(3S)", "pl");
	leg_pt->SetBorderSize(0);
	leg_pt->SetTextFont(42);
	leg_pt->SetTextSize(0.04);

///////////////////////////////////////////////////////////////////////////////

	p1_L->cd();
	g_c3s.GetYaxis()->SetRangeUser(ydown, yup);
	g_c3s.GetXaxis()->SetLimits(0, 420);
	g_c3s.GetXaxis()->SetRangeUser(0, 420);
	g_c3s.GetXaxis()->SetTitle("#LT N_{part} #GT");
	g_c3s.GetXaxis()->SetTitleOffset(0.9);
	g_c3s.GetXaxis()->SetTitleSize(0.05);
	g_c3s.GetXaxis()->CenterTitle();
	g_c3s.GetYaxis()->SetTitle("(#Upsilon(3S)/#Upsilon(2S))_{PbPb} / (#Upsilon(3S)/#Upsilon(2S))_{pp}");
	g_c3s.GetYaxis()->SetTitleOffset(1.0);
	g_c3s.GetYaxis()->SetTitleSize(0.05);
	g_c3s.GetYaxis()->CenterTitle();
	g_c3s.Draw("APE");
//	g_c3s.Draw("PE ");
//	g_c2s_sys.Draw("5");
	g_c3s_sys.Draw("5");
	lineone->DrawLine(0, 1, 420, 1);
	lineone->DrawLine(0, 2, 420, 2);
	tl->DrawLatex( 40, label_pos_up +0.05,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 40, label_pos_up -0.15, "|y| < 2.4");
//	leg_cent->Draw();

	b_3serr->SetX1(390);
    b_3serr->SetX2(420);
    b_3serr->SetY1(1 - fabs(glb_3serr));
    b_3serr->SetY2(1 + fabs(glb_3serr));
    b_3serr->SetFillColorAlpha(12, 0.8);
    b_3serr->SetLineWidth(1);
	b_3serr->Draw("L");

	p1_L->Update();
	p1_L->Draw();

	p1_R->cd();
	g_i3s.GetYaxis()->SetRangeUser(ydown, yup);
	g_i3s.GetYaxis()->SetTickLength( g_i3s.GetYaxis()->GetTickLength() * p2scale );
	g_i3s.GetXaxis()->SetRangeUser(1,4);
	g_i3s.GetXaxis()->SetLimits(1,4);
	g_i3s.GetXaxis()->SetTickSize(0);
	g_i3s.GetXaxis()->SetLabelSize(0);
	g_i3s.Draw("APE");
//	g_i2s.Draw("PE");
//	g_i2s_sys.Draw("5");
	g_i3s_sys.Draw("5");
	lineone->DrawLine(1,1,4,1);
	lineone->DrawLine(1,2,4,2);
	tl->SetTextSize(0.037*p2scale);
	tl->SetTextAlign(21);
	tl->DrawLatex( 2.5, 2.05, "Cent.");
	tl->SetTextAlign(23);
	tl->DrawLatex( 2.5, 1.95, "0-90 %");
	p1_R->Update();
	p1_R->Draw();

	c1->Modified();
	c1->Update();

	c2->cd();
	p2->cd();
	g_p3s.GetYaxis()->SetRangeUser(ydown, yup);
	g_p3s.GetXaxis()->SetRangeUser(0, 30);
	g_p3s.GetXaxis()->SetTitle("p_{T} (GeV/c)");
	g_p3s.GetXaxis()->SetTitleOffset(0.9);
	g_p3s.GetXaxis()->SetTitleSize(0.05);
	g_p3s.GetXaxis()->CenterTitle();
	g_p3s.GetYaxis()->SetTitle("(#Upsilon(3S)/#Upsilon(2S))_{PbPb} / (#Upsilon(3S)/#Upsilon(2S))_{pp}");
	g_p3s.GetYaxis()->SetTitleOffset(0.9);
	g_p3s.GetYaxis()->SetTitleSize(0.05);
	g_p3s.GetYaxis()->CenterTitle();
	g_p3s.Draw("APE");
//	g_p2s.Draw("PE");
//	g_p2s_sys.Draw("5");
	g_p3s_sys.Draw("5");
	lineone->DrawLine(0, 1, 30, 1);
	lineone->DrawLine(0, 2, 30, 2);
	tl->SetTextSize(0.037);
	tl->SetTextAlign(11);
	tl->DrawLatex( 2.5, label_pos_up + 0.05,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 12, label_pos_up + 0.05 , "|y| < 2.4");
	tl->DrawLatex( 2.5,label_pos_up - 0.15 , "Cent. 0-90 %");
//	leg_pt->Draw();
	p2->Draw();
	
	c2->Modified();
	c2->Update();

	c1->cd();
	p1_L->cd();
	CMS_lumi_square(p1_L,103, 33);
	c2->cd();
	p2->cd();
	CMS_lumi_square( p2, 103, 33);

	TFile* output = new TFile(Form("resultDR_nS_centrality_withSystematics_%ld_v2.root", _TS), "recreate");
	output->cd();
	c1->SaveAs(Form("../checkout/tscol/DR_centrality_int_%ld_v2.pdf", _TS));
	c2->SaveAs(Form("../checkout/tscol/DR_pt_%ld_v2.pdf", _TS));
	c1->Write();
	c2->Write();
	output->Close();
	
//	c1->SaveAs("RAA_SYST_CENT_PT.pdf");
	return g_p3s;

};


//TGraphAsymmErrors analysis_DRplot_sys(){
//	return analysis_DRplot_sys(TFile::Open(Form("./result/DR_%ld.root", _TS) ), TFile::Open(Form("../Systematics/data/total_systematics_DR_%ld.root", _TS) ), TFile::Open("/home/CMS/Analysis/Upsilon3S_pp2017Ref/Results/PP_2017EOY_Systematic.root") );
//};

TGraphAsymmErrors analysis_DRplot_sys(){
	return analysis_DRplot_sys(TFile::Open(Form("./result/DR_%ld.root", _TS) ), TFile::Open(Form("../Systematics/data/total_systematics_DR_%ld.root", _TS) ), TFile::Open("/home/CMS/Analysis/Upsilon3S_pp2017Ref/Results/PP_2017EOY_Systematic.root") );
};
