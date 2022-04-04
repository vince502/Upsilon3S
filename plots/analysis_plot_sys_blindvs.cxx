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

#if _TS == 20000000016 && __has_include("../LLR_CCorder_20000000016.h")
#   include "../LLR_CCorder_20000000016.h"
#   define getNomBkgO getNomBkgO_20000000016
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

TGraphAsymmErrors analysis_plot_sys_blindvs(TFile* hf, TFile* hsys, TFile* ppsys){
	TH1D* hp3s = (TH1D*) hf->Get("rp3S");
	TH1D* hp2s = (TH1D*) hf->Get("rp2S");
	TH1D* hc3s = (TH1D*) hf->Get("rc3S");
	TH1D* hc2s = (TH1D*) hf->Get("rc2S");

	TH1D* hp3s_sys = (TH1D*) hsys->Get("syst_comp/hsys_tot_p3S");
	TH1D* hp2s_sys = (TH1D*) hsys->Get("syst_comp/hsys_tot_p2S");
	TH1D* hc3s_sys = (TH1D*) hsys->Get("syst_comp/hsys_tot_c3S");
	TH1D* hc2s_sys = (TH1D*) hsys->Get("syst_comp/hsys_tot_c2S");

	TH1D* hpp_p3s_sys = (TH1D*) ppsys->Get("hptPP_3S_yield");
	TH1D* hpp_p2s_sys = (TH1D*) ppsys->Get("hptPP_2S_yield");
	TH1D* hpp_i3s_sys = (TH1D*) ppsys->Get("hIntPP_3S_yield");
	TH1D* hpp_i2s_sys = (TH1D*) ppsys->Get("hIntPP_2S_yield");

	TH1D* hpp_p3s_unc = (TH1D*) ppsys->Get("hptPP_3S_yield_total");
	TH1D* hpp_p2s_unc = (TH1D*) ppsys->Get("hptPP_2S_yield_total");
	TH1D* hpp_i3s_unc = (TH1D*) ppsys->Get("hIntPP_3S_yield_total");
	TH1D* hpp_i2s_unc = (TH1D*) ppsys->Get("hIntPP_2S_yield_total");

	TGraphAsymmErrors g_p3s, g_p3s_sys;
	TGraphAsymmErrors g_p2s, g_p2s_sys;
	TGraphAsymmErrors g_c3s, g_c3s_sys;
	TGraphAsymmErrors g_c2s, g_c2s_sys;
	TGraphAsymmErrors g_i3s, g_i3s_sys;
	TGraphAsymmErrors g_i2s, g_i2s_sys;
	
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
//////LAMBDA, CONSTANTS ////
	auto get_taa_err = [](ana_bins x){
		auto taa = glp::Taa[{x.centl, x.centh}];
		return (double) taa.second/taa.first;
	};
	auto quadsum = [](double arg1, double arg2){ return TMath::Sqrt(arg1 * arg1 + arg2 * arg2); };
	double pp_lum =0;
	double pp_sys =0;
	double mb_unc =0;
////////////////////////////

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
				double tot_sys = quadsum(nom_sys, taa_err);
				point_y = { ref_raa, ref_raa * tot_sys };
			}
			if(ab.bintype == kPt){
				auto hpt_err = (ab.state == 3) ? hpp_p3s_sys : hpp_p2s_sys;
				point_x = {((double)( ab.pl + ab.ph ))/2., ((double)(ab.ph-ab.pl))/2. };
				ref_raa = raahist.GetBinContent( idx );
				nom_sys = hist.GetBinContent( idx );
				double pp_err = hpt_err->GetBinContent( idx );
				double tot_sys = quadsum(nom_sys, pp_err);
			
				point_y = { ref_raa , ref_raa * tot_sys };
			}
			grap.AddPoint(point_x.first, point_y.first);
			grap.SetPointError(idx-1, point_x.second, point_x.second, point_y.second, point_y.second);
		}
	};
/////////////////////////////////INTEGRATED BIN///////////////////////////////////

	g_i2s.AddPoint(2, hc2s->GetBinContent(1)) ;
	g_i2s.SetPointError(0, 0,0, hc2s->GetBinError(1), hc2s->GetBinError(1) ) ;
	g_i3s.AddPoint(3, hc3s->GetBinContent(1)) ;
	g_i3s.SetPointError(0, 0,0, hc3s->GetBinError(1), hc3s->GetBinError(1) ) ;

	double int_sys_width = 0.23;

	double val_2s = hc2s->GetBinContent(1);
	double val_3s = hc3s->GetBinContent(1);
	double int_sys_2s = (hc2s_sys->GetBinContent(1));
	double int_sys_3s = (hc3s_sys->GetBinContent(1));
	double int_pp_sys_2s = (hpp_i2s_sys->GetBinContent(1));
	double int_pp_sys_3s = (hpp_i3s_sys->GetBinContent(1));
	int_sys_2s =  quadsum( mb_unc, quadsum( pp_sys, quadsum(pp_lum, quadsum(int_pp_sys_2s, int_sys_2s) ) ) );
	int_sys_3s =  quadsum( mb_unc, quadsum( pp_sys, quadsum(pp_lum, quadsum(int_pp_sys_3s, int_sys_3s) ) ) );
	g_i2s_sys.AddPoint(2, val_2s) ;
	g_i2s_sys.SetPointError(0, int_sys_width, int_sys_width, val_2s *int_sys_2s, val_2s * int_sys_2s ) ;
	g_i3s_sys.AddPoint(3, val_3s) ;
	g_i3s_sys.SetPointError(0, int_sys_width, int_sys_width, val_3s *int_sys_3s, val_3s * int_sys_3s ) ;

//////////////////////////////////////////////////////////////////////////////////

	fillgraph(*hc2s, g_c2s, "2c");
	fillgraph(*hc3s, g_c3s, "3c");
	fillgraph(*hp2s, g_p2s, "2p");
	fillgraph(*hp3s, g_p3s, "3p");

	fillsysgraph(*hc2s_sys, *hc2s, g_c2s_sys, "2c");
	fillsysgraph(*hc3s_sys, *hc3s, g_c3s_sys, "3c");
	fillsysgraph(*hp2s_sys, *hp2s, g_p2s_sys, "2p");
	fillsysgraph(*hp3s_sys, *hp3s, g_p3s_sys, "3p");

	TCanvas* c1 = new TCanvas("c1","", 1000,900);
	TCanvas* c2 = new TCanvas("c2","", 1000,900);
	TPad* p1_L = new TPad("p1L", "", 0.00, 0., 0.83,1.);
	TPad* p1_R = new TPad("p1R", "", 0.83, 0., 1., 1.);
	TPad* p2 = new TPad("p2", "", 0., 0., 1., 1.);
	p1_L->SetBottomMargin(0.12);
	p1_R->SetBottomMargin(0.12);
	p2->SetBottomMargin(0.12);
	p1_L->SetTicks();
	p1_R->SetTicks();
	p2->SetTicks();

	double p2scale = ( (0.83 -0.12)/ (1. - 0.83) ) ;

	p1_L->SetRightMargin(0);
	p1_R->SetLeftMargin(0);

	c1->cd();
	p1_L->Draw();
	p1_R->Draw();
	c2->cd();
	p2->Draw();

///////////////////////////////Clone : For combining HIN-16-023///////////////////
	TCanvas* c1a = new TCanvas("c1a","", 1000,900);
	TCanvas* c2a = new TCanvas("c2a","", 1000,900);
	TCanvas* c1b = new TCanvas("c1b","", 1000,900);
	TCanvas* c2b = new TCanvas("c2b","", 1000,900);
	TPad* p1_La = new TPad("p1La", "", 0.00, 0., 0.83,1.);
	TPad* p1_Ra = new TPad("p1Ra", "", 0.83, 0., 1., 1.);
	TPad* p2a = new TPad("p2a", "", 0., 0., 1., 1.);
	p1_La->SetBottomMargin(0.12);
	p1_Ra->SetBottomMargin(0.12);
	p2a->SetBottomMargin(0.12);
	p1_La->SetTicks();
	p1_Ra->SetTicks();
	p2a->SetTicks();

	double p2ascale = ( (0.83 -0.12)/ (1. - 0.83) ) ;

	p1_La->SetRightMargin(0);
	p1_Ra->SetLeftMargin(0);

	c1a->cd();
	p1_La->Draw();
	p1_Ra->Draw();
	c2a->cd();
	p2a->Draw();

/////////////////////////////////GRAPH ATTR///////////////////////////////////
	g_c2s.SetLineColor(kBlue);
	g_p2s.SetLineColor(kBlue);
	g_i2s.SetLineColor(kBlue);
	g_c2s.SetMarkerColor(kBlue+2);
	g_p2s.SetMarkerColor(kBlue+2);
	g_i2s.SetMarkerColor(kBlue+2);

	g_c2s_sys.SetLineColor(kBlue);
	g_p2s_sys.SetLineColor(kBlue);
	g_i2s_sys.SetLineColor(kBlue);
	g_c2s_sys.SetFillColorAlpha(kAzure-3, 0.25);
    g_p2s_sys.SetFillColorAlpha(kAzure-3, 0.25);
    g_i2s_sys.SetFillColorAlpha(kAzure-3, 0.25);

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

	g_c2s.SetMarkerStyle(kFullSquare);
	g_p2s.SetMarkerStyle(kFullSquare);
	g_i2s.SetMarkerStyle(kFullSquare);
	g_c2s.SetMarkerSize(1.4);
	g_p2s.SetMarkerSize(1.4);
	g_i2s.SetMarkerSize(1.4);

	g_c3s.SetMarkerStyle(kFullSquare);
	g_p3s.SetMarkerStyle(kFullSquare);
	g_i3s.SetMarkerStyle(kFullSquare);
	g_c3s.SetMarkerSize(1.4);
	g_p3s.SetMarkerSize(1.4);
	g_i3s.SetMarkerSize(1.4);
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////Global Uncertainties/////////////////////////////

	TBox* b_err = new TBox();
	TBox* b_2serr = new TBox();
	TBox* b_3serr = new TBox();
	TBox* b_pterr = new TBox();
	double glb_2serr = hpp_i2s_unc->GetBinContent(1);
	double glb_3serr = hpp_i3s_unc->GetBinContent(1);
	double glb_errMB_PP = 0;
	glb_errMB_PP =quadsum(0.019, 0.01261);
//	glb_errMB_PP =quadsum(pp_lum, mb_unc);

	double glb_errpt = 0;
	double taaint_err = glp::Taa[{0, 90}].second/ glp::Taa[{0, 90}].first;
	glb_errpt = quadsum( 0.01261, quadsum(taaint_err, 0.019));

///////////////////////////////////////////////////////////////////////////////

//////////////////////////////Auxiliary Drawings///////////////////////////////
	gStyle->SetEndErrorSize(0);

	double yup = 1.3;
	double ydown = 0.0;

	TLine* lineone = new TLine();
	lineone->SetLineStyle(kDashed);
	lineone->SetLineWidth(1);

	TLatex* tl = new TLatex();
	tl->SetTextSize(0.037);
	tl->SetTextFont(42);

	TLegend* leg_cent = new TLegend(0.75, 0.4, 0.85, 0.70);
	leg_cent->AddEntry(&g_c2s, "#Upsilon(2S)", "pl");
	leg_cent->AddEntry(&g_c3s, "#Upsilon(3S)", "pl");
	leg_cent->SetBorderSize(0);
	leg_cent->SetTextFont(42);
	leg_cent->SetTextSize(0.04);

	TLegend* leg_pt = new TLegend(0.65, 0.3, 0.85, 0.7);
	leg_pt->AddEntry(&g_p2s, "#Upsilon(2S)", "pl");
	leg_pt->AddEntry(&g_p3s, "#Upsilon(3S)", "pl");
	leg_pt->SetBorderSize(0);
	leg_pt->SetTextFont(42);
	leg_pt->SetTextSize(0.04);

///////////////////////////////////////////////////////////////////////////////

	p1_L->cd();
	g_c2s.GetYaxis()->SetRangeUser(ydown, yup);
	g_c2s.GetXaxis()->SetTitle("#LT N_{part} #GT");
	g_c2s.GetXaxis()->SetTitleOffset(0.9);
	g_c2s.GetXaxis()->SetTitleSize(0.05);
	g_c2s.GetXaxis()->CenterTitle();
	g_c2s.GetYaxis()->SetTitle("R_{AA}");
	g_c2s.GetYaxis()->SetTitleOffset(0.9);
	g_c2s.GetYaxis()->SetTitleSize(0.05);
	g_c2s.GetYaxis()->CenterTitle();
	g_c2s.Draw("APE");
	g_c3s.Draw("PE ");
	g_c2s_sys.Draw("5");
	g_c3s_sys.Draw("5");
	lineone->DrawLine(0, 1, 420, 1);
	tl->DrawLatex( 40, 1.15,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 40, 1.06, "|y| < 2.4");
	leg_cent->Draw();

    b_err->SetX1(360);
    b_err->SetX2(380);
    b_err->SetY1(1 - fabs(glb_errMB_PP));
    b_err->SetY2(1 + fabs(glb_errMB_PP));
    b_err->SetFillColorAlpha(12, 0.8);
    b_err->SetLineWidth(1);
    b_2serr->SetX1(380);
    b_2serr->SetX2(400);
    b_2serr->SetY1(1 - fabs(glb_2serr));
    b_2serr->SetY2(1 + fabs(glb_2serr));
//    std::cout <<"Global Error 2S " << b_y2err->GetY1() << std::endl;
    b_2serr->SetFillColorAlpha(kAzure-3, 0.8);
    b_2serr->SetLineWidth(1);
    b_3serr->SetX1(400);
    b_3serr->SetX2(420);
    b_3serr->SetY1(1 - glb_3serr);
    b_3serr->SetY2(1 + glb_3serr);
    b_3serr->SetFillColorAlpha(kTeal+5, 0.8);
    b_3serr->SetLineWidth(1);
//  b_3serr->SetLineColor();
	b_err->Draw("L");
	b_3serr->Draw("L");
    b_2serr->Draw("L");

	p1_L->Update();
	p1_L->Draw();

	p1_R->cd();
	g_i2s.GetYaxis()->SetRangeUser(ydown, yup);
	g_i2s.GetYaxis()->SetTickLength( g_i2s.GetYaxis()->GetTickLength() * p2scale );
	g_i2s.GetXaxis()->SetRangeUser(1,4);
	g_i2s.GetXaxis()->SetLimits(1,4);
	g_i2s.GetXaxis()->SetTickSize(0);
	g_i2s.GetXaxis()->SetLabelSize(0);
	g_i2s.Draw("APE");
	g_i3s.Draw("PE");
	g_i2s_sys.Draw("5");
	g_i3s_sys.Draw("5");
	lineone->DrawLine(1,1,4,1);
	tl->SetTextSize(0.037* p2scale);
	tl->SetTextAlign(21);
	tl->DrawLatex( 2.5, 1.02, "Cent.");
	tl->DrawLatex( 2.5, 0.94, "0-90 %");
	p1_R->Update();
	p1_R->Draw();

//	c1->Modified();
//	c1->Update();

	c2->cd();
	p2->cd();
	g_p2s.GetYaxis()->SetRangeUser(ydown, yup);
	g_p2s.GetXaxis()->SetRangeUser(0, 30);
	g_p2s.GetXaxis()->SetTitle("p_{T} (GeV/c)");
	g_p2s.GetXaxis()->SetTitleOffset(0.9);
	g_p2s.GetXaxis()->SetTitleSize(0.05);
	g_p2s.GetXaxis()->CenterTitle();
	g_p2s.GetYaxis()->SetTitle("R_{AA}");
	g_p2s.GetYaxis()->SetTitleOffset(0.9);
	g_p2s.GetYaxis()->SetTitleSize(0.05);
	g_p2s.GetYaxis()->CenterTitle();
	g_p2s.Draw("APE");
	g_p3s.Draw("PE");
	g_p2s_sys.Draw("5");
	g_p3s_sys.Draw("5");
	lineone->DrawLine(0, 1, 30, 1);
	tl->SetTextSize(0.037);
	tl->SetTextAlign(11);
	tl->DrawLatex( 2.5, 1.15,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 11, 1.15, "|y| < 2.4");
	tl->DrawLatex( 2.5,1.06, "Cent. 0-90 %");
	leg_pt->Draw();
	b_pterr->SetX1(0);
	b_pterr->SetX2(2);
	b_pterr->SetY1(1 - glb_errpt);
	b_pterr->SetY2(1 + glb_errpt);
	b_pterr->SetFillColorAlpha(12, 0.8);
	b_pterr->SetLineWidth(1);
	b_pterr->SetLineColor(kBlack);
	b_pterr->Draw("L");

	p2->Draw();
	
	c2->Modified();
	c2->Update();

	c1->cd();
	p1_L->cd();
	CMS_lumi_square(p1_L,103, 33);
	c2->cd();
	p2->cd();
	CMS_lumi_square( p2, 103, 33);

	TFile* output = new TFile(Form("resultRAA_nS_centrality_withSystematics_%ld_v2.root", _TS), "recreate");
	output->cd();
	c1->SaveAs(Form("../checkout/tscol/RAA_centrality_int_%ld_v2.pdf", _TS) );
	c2->SaveAs(Form("../checkout/tscol/RAA_pt_%ld_v2.pdf", _TS) );
	c1->Write();
	c2->Write();
	output->Close();

	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	TGraphAsymmErrors pg_c1s, pg_p1s, pg_c2s, pg_p2s, pg_c3s, pg_p3s;
	TGraphAsymmErrors pg_i1s, pg_i2s, pg_i3s;

	pg_c1s.SetLineColor(kViolet-5);
	pg_p1s.SetLineColor(kViolet-5);
	pg_i1s.SetLineColor(kViolet-5);
	pg_c1s.SetMarkerColor(kViolet+1);
	pg_p1s.SetMarkerColor(kViolet+1);
	pg_i1s.SetMarkerColor(kViolet+1);

	pg_c2s.SetLineColor(kPink-3);
	pg_p2s.SetLineColor(kPink-3);
	pg_i2s.SetLineColor(kPink-3);
	pg_c2s.SetMarkerColor(kPink-2);
	pg_p2s.SetMarkerColor(kPink-2);
	pg_i2s.SetMarkerColor(kPink-2);

	pg_c3s.SetLineColor(kGreen+4);
	pg_p3s.SetLineColor(kGreen+4);
	pg_i3s.SetLineColor(kGreen+4);
	pg_c3s.SetMarkerColor(kGreen+4);
	pg_p3s.SetMarkerColor(kGreen+4);
	pg_i3s.SetMarkerColor(kGreen+4);

	pg_c1s.SetMarkerStyle(kFullCircle);
	pg_p1s.SetMarkerStyle(kFullCircle);
	pg_i1s.SetMarkerStyle(kFullCircle);
	pg_c1s.SetMarkerSize(1.4);
	pg_p1s.SetMarkerSize(1.4);
	pg_i1s.SetMarkerSize(1.4);

	pg_c2s.SetMarkerStyle(kFullCircle);
	pg_p2s.SetMarkerStyle(kFullCircle);
	pg_i2s.SetMarkerStyle(kFullCircle);
	pg_c2s.SetMarkerSize(1.4);
	pg_p2s.SetMarkerSize(1.4);
	pg_i2s.SetMarkerSize(1.4);

	pg_c3s.SetMarkerStyle(kFullCircle);
	pg_p3s.SetMarkerStyle(kFullCircle);
	pg_i3s.SetMarkerStyle(kFullCircle);
	pg_c3s.SetMarkerSize(1.4);
	pg_p3s.SetMarkerSize(1.4);
	pg_i3s.SetMarkerSize(1.4);

	/////////////////////////////////////////////////////////////////
	pg_c1s.SetPoint(0,8.3000002, 0.79200000);
	pg_c1s.SetPoint(1,30.600000, 0.92199999);
	pg_c1s.SetPoint(2, 53.900002, 0.60900003);
	pg_c1s.SetPoint(3, 87.000000, 0.52399999);
	pg_c1s.SetPoint(4, 131.39999, 0.48500001);
	pg_c1s.SetPoint(5, 189.20000, 0.40200001);
	pg_c1s.SetPoint(6, 264.20001, 0.32400000);
	pg_c1s.SetPoint(7, 333.29999, 0.32100001);
	pg_c1s.SetPoint(8, 384.29999, 0.31900001);
	pg_c1s.SetPointError(0, 0, 0, 0.13100000, 0.13100000);
	pg_c1s.SetPointError(1, 0, 0, 0.088000000, 0.088000000);
	pg_c1s.SetPointError(2, 0, 0, 0.052999999, 0.052999999);
	pg_c1s.SetPointError(3, 0, 0, 0.035999998, 0.035999998);
	pg_c1s.SetPointError(4, 0, 0, 0.027000001, 0.027000001);
	pg_c1s.SetPointError(5, 0, 0, 0.039000001, 0.039000001);
	pg_c1s.SetPointError(6, 0, 0, 0.017000001, 0.017000001);
	pg_c1s.SetPointError(7, 0, 0, 0.021000000, 0.021000000);
	pg_c1s.SetPointError(8, 0, 0, 0.018999999, 0.018999999);

	pg_i1s.SetPoint(0, 1, 0.376 );
	pg_i1s.SetPointError(0 ,0, 0,  TMath::Sqrt(0.013*0.013 + 0.035*0.035) );

	pg_p1s.SetPoint(0, 1,	 0.301);
	pg_p1s.SetPoint(1, 3,	 0.362);
	pg_p1s.SetPoint(2, 5,	 0.388);
	pg_p1s.SetPoint(3, 7.5, 0.402);
	pg_p1s.SetPoint(4, 10.5,0.422);
	pg_p1s.SetPoint(5, 21,	 0.425);

	pg_p1s.SetPointError(0, 1.0, 1.0, quadsum(0.027, 0.123), quadsum(0.027, 0.123));
	pg_p1s.SetPointError(1, 1.0, 1.0, quadsum(0.029, 0.035), quadsum(0.029, 0.035));
	pg_p1s.SetPointError(2, 1.0, 1.0, quadsum(0.033, 0.035), quadsum(0.033, 0.035));
	pg_p1s.SetPointError(3, 1.5, 1.5, quadsum(0.028, 0.032), quadsum(0.028, 0.032));
	pg_p1s.SetPointError(4, 1.5, 1.5, quadsum(0.035, 0.045), quadsum(0.035, 0.045));
	pg_p1s.SetPointError(5, 9.0, 9.0, quadsum(0.026, 0.036), quadsum(0.026, 0.036));


	pg_c2s.SetPoint(0, 8.3,	 0.563);
	pg_c2s.SetPoint(1, 30.6,	 0.530);
	pg_c2s.SetPoint(2, 53.9,	 0.21);
	pg_c2s.SetPoint(3, 87.0, 0.229);
	pg_c2s.SetPoint(4, 131.4,0.194);
	pg_c2s.SetPoint(5, 189.2,	 0.154);
	pg_c2s.SetPoint(6, 264.2,	 0.101);
	pg_c2s.SetPoint(7, 333.3,	 0.119);

	pg_i2s.SetPoint(0, 1., 0.117 );
	pg_i2s.SetPointError(0 ,0, 0,  quadsum(0.022, 0.019), quadsum(0.022, 0.019) );

	pg_c2s.SetPointError(0, 0.0, 0.0, quadsum(0.319, 0.136), quadsum(0.319, 0.154));
	pg_c2s.SetPointError(1, 0.0, 0.0, quadsum(0.170, 0.128), quadsum(0.170, 0.131));
	pg_c2s.SetPointError(2, 0.0, 0.0, quadsum(0.106, 0.037), quadsum(0.106, 0.038));
	pg_c2s.SetPointError(3, 0.0, 0.0, quadsum(0.077, 0.023), quadsum(0.077, 0.023));
	pg_c2s.SetPointError(4, 0.0, 0.0, quadsum(0.060, 0.019), quadsum(0.060, 0.019));
	pg_c2s.SetPointError(5, 0.0, 0.0, quadsum(0.092, 0.032), quadsum(0.092, 0.032));
	pg_c2s.SetPointError(6, 0.0, 0.0, quadsum(0.042, 0.031), quadsum(0.042, 0.031));
	pg_c2s.SetPointError(7, 0.0, 0.0, quadsum(0.051, 0.009), quadsum(0.051, 0.009));

	pg_p2s.SetPoint(0, 2,	 0.085);
	pg_p2s.SetPoint(1, 6.5,	 0.129);
	pg_p2s.SetPoint(2, 19.5, 0.126);

	pg_p2s.SetPointError(0, 2.0, 2.0, quadsum(0.039, 0.095), quadsum(0.039, 0.095));
	pg_p2s.SetPointError(1, 2.5, 2.5, quadsum(0.038, 0.031), quadsum(0.038, 0.031));
	pg_p2s.SetPointError(2, 10.5, 10.5, quadsum(0.032, 0.016), quadsum(0.032, 0.016));

	////////////// CL 68 % ////////////
	TBox* box_c3s_0 = new TBox(46.8-5, 0, 46.8+5, 0.188);
	TBox* box_c3s_1 = new TBox(270.7-5, 0, 270.5+5, 0.040);
	pg_c3s.SetPoint(0, 46.8,	 0.188);
	pg_c3s.SetPoint(1, 270.7,	 0.040);

	TBox* box_i3s_0 = new TBox(2.5-0.25, 0, 2.5+0.25, 0.059);
	pg_i3s.SetPoint(0, 1., 0.059 );

	TBox* box_p3s_0 = new TBox(3-0.5, 0, 3+0.5, 0.092);
	TBox* box_p3s_1 = new TBox(18-0.5, 0, 18+0.5, 0.052);
	pg_p3s.SetPoint(0, 3,	 0.092);
	pg_p3s.SetPoint(1, 18,	 0.052);

	pg_p3s.SetPointError(0, 1.50, 1.50, 0,0);
	pg_p3s.SetPointError(1, 9.00, 9.00, 0,0);
	box_c3s_0->SetFillColorAlpha(kOrange+6, 0.8);
	box_c3s_1->SetFillColorAlpha(kOrange+6, 0.8);
	box_i3s_0->SetFillColorAlpha(kOrange+6, 0.8);
	box_p3s_0->SetFillColorAlpha(kOrange+6, 0.8);
	box_p3s_1->SetFillColorAlpha(kOrange+6, 0.8);
	box_c3s_0->SetLineWidth(1);
	box_c3s_1->SetLineWidth(1);
	box_i3s_0->SetLineWidth(1);
	box_p3s_0->SetLineWidth(1);
	box_p3s_1->SetLineWidth(1);

	////////////// CL 95 % ////////////
	TArrow* arr_c3s_0 = new TArrow(46.8,0.258,46.8, 0, 0.015, "|->");
	TArrow* arr_c3s_1 = new TArrow(270.7 ,0.077,270.7, 0, 0.015, "|->");
	TLine* line_c3s_0 = new TLine(46.8-3,0.258, 46.8+3, 0.258);
	TLine* line_c3s_1 = new TLine(270.7-3,0.077, 270.7+3, 0.077);
	pg_c3s.SetPoint(2, 46.8,	 0.258);
	pg_c3s.SetPoint(3, 270.7,	 0.077);

	TArrow* arr_i3s_0 = new TArrow(2.5,0.096,2.5, 0, 0.015, "|->");
	TLine* line_i3s_0 = new TLine(2.5-0.2,0.096, 2.5+0.2, 0.096);
	pg_i3s.SetPoint(2, 1., 0.096 );

	TArrow* arr_p3s_0 = new TArrow(3,0.155,3, 0.0, 0.015, "|->");
	TArrow* arr_p3s_1 = new TArrow(18,0.095,18, 0, 0.015, "|->");
	TLine* line_p3s_0 = new TLine(3-0.33,0.155, 3+0.33, 0.155);
	TLine* line_p3s_1 = new TLine(18-0.33,0.095, 18+0.33, 0.095);
	pg_p3s.SetPoint(2, 3,	 0.155);
	pg_p3s.SetPoint(3, 18,	 0.095);

	pg_p3s.SetPointError(2, 1.50, 1.50, 0,0);
	pg_p3s.SetPointError(3, 9.00, 9.00, 0,0);

//	arr_c3s_0->SetLineWidth(1);
//	arr_c3s_1->SetLineWidth(1);
//	arr_i3s_0->SetLineWidth(1);
//	arr_p3s_0->SetLineWidth(1);
//	arr_p3s_0->SetLineWidth(1);
	arr_c3s_0->SetLineColor(kOrange+4);
	arr_c3s_1->SetLineColor(kOrange+4);
	arr_i3s_0->SetLineColor(kOrange+4);
	arr_p3s_0->SetLineColor(kOrange+4);
	arr_p3s_1->SetLineColor(kOrange+4);
	line_c3s_0->SetLineColor(kOrange+4);
	line_c3s_1->SetLineColor(kOrange+4);
	line_i3s_0->SetLineColor(kOrange+4);
	line_p3s_0->SetLineColor(kOrange+4);
	line_p3s_1->SetLineColor(kOrange+4);
	/////////////////////////////////////////////////////////////////
	TLegend* leg_cent2 = new TLegend(0.55, 0.35, 0.83, 0.7);
	TLegend* leg_cent2_2 = new TLegend(0.55, 0.35, 0.83, 0.7);
//	leg_cent2->AddEntry(&pg_c1s, "#Upsilon(1S) PLB 790 (2019) 270", "pl");
	leg_cent2->AddEntry(&pg_c2s, "#Upsilon(2S) PLB 790 (2019) 270", "pl");
	leg_cent2->AddEntry(box_c3s_0, "#splitline{#Upsilon(3S) PLB 790 (2019) 270,}{ 68 % C.L.}", "f");
	leg_cent2->AddEntry(arr_p3s_0, "#splitline{#Upsilon(3S) PLB 790 (2019) 270,}{ 95 % C.L.}", "" );

	leg_cent2_2->AddEntry(&pg_c1s, "#Upsilon(1S) PLB 790 (2019) 270", "pl");
	leg_cent2_2->AddEntry(&pg_c2s, "#Upsilon(2S) PLB 790 (2019) 270", "pl");
	leg_cent2_2->AddEntry(box_c3s_0, "#splitline{#Upsilon(3S) PLB 790 (2019) 270,}{ 68 % C.L.}", "f");
	leg_cent2_2->AddEntry(arr_p3s_0, "#splitline{#Upsilon(3S) PLB 790 (2019) 270,}{ 95 % C.L.}", "" );

	leg_cent2->AddEntry(&g_c2s, "#Upsilon(2S)", "pl");
	leg_cent2->AddEntry(&g_c3s, "#Upsilon(3S)", "pl");
	leg_cent2->SetBorderSize(0);
	leg_cent2->SetTextFont(42);
	leg_cent2->SetTextSize(0.028);

	leg_cent2_2->AddEntry(&g_c2s, "#Upsilon(2S)", "pl");
	leg_cent2_2->AddEntry(&g_c3s, "#Upsilon(3S)", "pl");
	leg_cent2_2->SetBorderSize(0);
	leg_cent2_2->SetTextFont(42);
	leg_cent2_2->SetTextSize(0.027);

	TLegend* leg_pt2 = new TLegend(0.53, 0.30, 0.8, 0.7);
	TLegend* leg_pt2_2 = new TLegend(0.53, 0.4, 0.8, 0.71);
//	leg_pt2->AddEntry(&pg_p1s, "#Upsilon(1S) PLB 790 (2019) 270", "pl");
	leg_pt2->AddEntry(&pg_p2s, "#Upsilon(2S) PLB 790 (2019) 270", "pl");
	leg_pt2->AddEntry(box_p3s_0, "#splitline{#Upsilon(3S) PLB 790 (2019) 270,}{ 68 % C.L.}", "f");
	leg_pt2->AddEntry(arr_p3s_0, "#splitline{#Upsilon(3S) PLB 790 (2019) 270,}{ 95 % C.L.}", "" );
	leg_pt2->AddEntry(&g_p2s, "#Upsilon(2S)", "pl");
	leg_pt2->AddEntry(&g_p3s, "#Upsilon(3S)", "pl");
	leg_pt2->SetBorderSize(0);
	leg_pt2->SetTextFont(42);
	leg_pt2->SetTextSize(0.028);

	leg_pt2_2->AddEntry(&pg_p1s, "#Upsilon(1S) PLB 790 (2019) 270", "pl");
	leg_pt2_2->AddEntry(&pg_p2s, "#Upsilon(2S) PLB 790 (2019) 270", "pl");
	leg_pt2_2->AddEntry(box_p3s_0, "#splitline{#Upsilon(3S) PLB 790 (2019) 270,}{ 68 % C.L.}", "f");
	leg_pt2_2->AddEntry(arr_p3s_0, "#splitline{#Upsilon(3S) PLB 790 (2019) 270,}{ 95 % C.L.}", "" );
	leg_pt2_2->AddEntry(&g_p2s, "#Upsilon(2S)", "pl");
	leg_pt2_2->AddEntry(&g_p3s, "#Upsilon(3S)", "pl");
	leg_pt2_2->SetBorderSize(0);
	leg_pt2_2->SetTextFont(42);
	leg_pt2_2->SetTextSize(0.027);
	/////////////////////////////////////////////////////////////////

	p1_La->cd();
	g_c2s.GetYaxis()->SetRangeUser(ydown, yup);
	g_c2s.GetXaxis()->SetTitle("#LT N_{part} #GT");
	g_c2s.GetXaxis()->SetTitleOffset(0.9);
	g_c2s.GetXaxis()->SetTitleSize(0.05);
	g_c2s.GetXaxis()->CenterTitle();
	g_c2s.GetYaxis()->SetTitle("R_{AA}");
	g_c2s.GetYaxis()->SetTitleOffset(0.9);
	g_c2s.GetYaxis()->SetTitleSize(0.05);
	g_c2s.GetYaxis()->CenterTitle();
	g_c2s.Draw("APE");
	g_c3s.Draw("PE ");
//	pg_c1s.Draw("PE ");
	pg_c2s.Draw("PE ");
	g_c2s_sys.Draw("5");
	g_c3s_sys.Draw("5");
	box_c3s_0->Draw("L");
	box_c3s_1->Draw("L");
	arr_c3s_0->Draw();
	arr_c3s_1->Draw();
//	line_c3s_0->Draw();
//	line_c3s_1->Draw();

	lineone->DrawLine(0, 1, 420, 1);
	tl->DrawLatex( 40, 1.15,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 40, 1.06, "|y| < 2.4");
	leg_cent2->Draw();
	
	arr_c3s_0->DrawArrow(228,0.7,228, 0.65, 0.015,"|->");

    b_err->SetX1(360);
    b_err->SetX2(380);
    b_err->SetY1(1 - fabs(glb_errMB_PP));
    b_err->SetY2(1 + fabs(glb_errMB_PP));
    b_err->SetFillColorAlpha(12, 0.8);
    b_err->SetLineWidth(1);
    b_2serr->SetX1(380);
    b_2serr->SetX2(400);
    b_2serr->SetY1(1 - fabs(glb_2serr));
    b_2serr->SetY2(1 + fabs(glb_2serr));
//    std::cout <<"Global Error 2S " << b_y2err->GetY1() << std::endl;
    b_2serr->SetFillColorAlpha(kAzure-3, 0.8);
    b_2serr->SetLineWidth(1);
    b_3serr->SetX1(400);
    b_3serr->SetX2(420);
    b_3serr->SetY1(1 - glb_3serr);
    b_3serr->SetY2(1 + glb_3serr);
    b_3serr->SetFillColorAlpha(kTeal+5, 0.8);
    b_3serr->SetLineWidth(1);
//  b_3serr->SetLineColor();
	b_err->Draw("L");
	b_3serr->Draw("L");
    b_2serr->Draw("L");

	p1_La->Update();
	p1_La->Draw();

	p1_Ra->cd();
	g_i2s.GetYaxis()->SetRangeUser(ydown, yup);
//	g_i2s.GetYaxis()->SetTickLength( g_i2s.GetYaxis()->GetTickLength() * p2scale );
	g_i2s.GetXaxis()->SetRangeUser(0,4);
	g_i2s.GetXaxis()->SetLimits(0,4);
	g_i2s.GetXaxis()->SetTickSize(0);
	g_i2s.GetXaxis()->SetLabelSize(0);
	g_i2s.Draw("APE");
	g_i3s.Draw("PE");
//	pg_i1s.Draw("PE");
	pg_i2s.Draw("PE");
//	pg_i3s.Draw("PE");
	g_i2s_sys.Draw("5");
	g_i3s_sys.Draw("5");
	box_i3s_0->Draw("L");
	arr_i3s_0->Draw();
//	line_i3s_0->Draw();

	lineone->DrawLine(0,1,4,1);
	tl->SetTextSize(0.037* p2scale);
	tl->SetTextAlign(21);
	tl->DrawLatex( 2., 1.02, "Cent.");
	tl->DrawLatex( 2., 0.94, "0-90 %");
	p1_Ra->Update();
	p1_Ra->Draw();

//	c1->Modified();
//	c1->Update();

	c2a->cd();
	p2a->cd();
	g_p2s.GetYaxis()->SetRangeUser(ydown, yup);
	g_p2s.GetXaxis()->SetRangeUser(0, 30);
	g_p2s.GetXaxis()->SetTitle("p_{T} (GeV/c)");
	g_p2s.GetXaxis()->SetTitleOffset(0.9);
	g_p2s.GetXaxis()->SetTitleSize(0.05);
	g_p2s.GetXaxis()->CenterTitle();
	g_p2s.GetYaxis()->SetTitle("R_{AA}");
	g_p2s.GetYaxis()->SetTitleOffset(0.9);
	g_p2s.GetYaxis()->SetTitleSize(0.05);
	g_p2s.GetYaxis()->CenterTitle();
	g_p2s.Draw("APE");
	g_p3s.Draw("PE");
//	pg_p1s.Draw("PE");
	pg_p2s.Draw("PE");
//	pg_p3s.Draw("PE");
	g_p2s_sys.Draw("5");
	g_p3s_sys.Draw("5");
	box_p3s_0->Draw("L");
	box_p3s_1->Draw("L");
	arr_p3s_0->Draw();
	arr_p3s_1->Draw();
//	line_p3s_0->Draw();
//	line_p3s_1->Draw();

	lineone->DrawLine(0, 1, 30, 1);
	tl->SetTextSize(0.037);
	tl->SetTextAlign(11);
	tl->DrawLatex( 2.5, 1.15,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 11, 1.15, "|y| < 2.4");
	tl->DrawLatex( 2.5,1.06, "Cent. 0-90 %");
	leg_pt2->Draw();
	arr_c3s_0->DrawArrow(17.45,0.66,17.45, 0.61, 0.015,"|->");

	b_pterr->SetX1(0);
	b_pterr->SetX2(2);
	b_pterr->SetY1(1 - glb_errpt);
	b_pterr->SetY2(1 + glb_errpt);
	b_pterr->SetFillColorAlpha(12, 0.8);
	b_pterr->SetLineWidth(1);
	b_pterr->SetLineColor(kBlack);
	b_pterr->Draw("L");

	p2a->Draw();
	
	c2a->Modified();
	c2a->Update();

	c1a->cd();
	p1_La->cd();
	CMS_lumi_square(p1_La,103, 33);
	c2a->cd();
	p2a->cd();
	CMS_lumi_square( p2a, 103, 33);
	
	TFile* output2 = new TFile(Form("resultRAA_nS_centrality_withSystematics_v2_HIN16023_%ld.root", _TS), "recreate");
	output2->cd();
	c1a->SaveAs(Form("../checkout/tscol/RAA_centrality_int_v2_HIN16023_%ld.pdf", _TS));
	c2a->SaveAs(Form("../checkout/tscol/RAA_pt_v2_HIN16023_%ld.pdf", _TS));
	c1a->Write();
	c2a->Write();
	leg_cent2->AddEntry(&pg_c1s, "#Upsilon(1S) PLB 790 (2019) 270", "pl");
	leg_pt2->AddEntry(&pg_p1s, "#Upsilon(1S) PLB 790 (2019) 270", "pl");
	arr_c3s_0->Clear();
	arr_c3s_1->Clear();
	c1a->cd();
	p1_La->cd();
	pg_c1s.Draw("PE");
	leg_cent2->Clear();
	leg_cent2_2->Draw();
	arr_c3s_0->DrawArrow(228,0.65,228, 0.60, 0.015,"|->");
	p1_Ra->cd();
	pg_i1s.Draw("PE");
	c2a->cd();
	p2a->cd();
	pg_p1s.Draw("PE");
//	leg_pt2->SetY1(leg_pt2->GetY1() +0.2);
	leg_pt2->Clear();
	leg_pt2_2->Draw();
	arr_c3s_0->DrawArrow(17.45,0.7,17.45, 0.65, 0.015,"|->");
	output2->cd();
	c1a->SaveAs(Form("../checkout/tscol/RAA_centrality_int_v2_HIN16023_w1S_%ld.pdf", _TS));
	c2a->SaveAs(Form("../checkout/tscol/RAA_pt_v2_HIN16023_w1S_%ld.pdf", _TS));

	output2->Close();
//	c1->SaveAs("RAA_SYST_CENT_PT.pdf");
	return g_p2s;

};


//TGraphAsymmErrors analysis_plot_sys(){
//	return analysis_plot_sys(TFile::Open(Form("./result/RAA_%ld.root", _TS)), TFile::Open(Form("../Systematics/data/total_systematics_RAA_%ld.root", _TS) ), TFile::Open("/home/CMS/Analysis/Upsilon3S_pp2017Ref/Results/PP_2017EOY_Systematic.root"));
//};

TGraphAsymmErrors analysis_plot_sys(){
	return analysis_plot_sys(TFile::Open(Form("./result/RAA_%ld.root", _TS)), TFile::Open(Form("../Systematics/data/total_systematics_RAA_%ld.root", _TS) ), TFile::Open("/home/CMS/Analysis/Upsilon3S_pp2017Ref/Results/PP_2017EOY_Systematic.root"));
};
