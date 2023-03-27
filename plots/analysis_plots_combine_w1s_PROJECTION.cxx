////#define _TS 9999999999
////#define _TS 10000000016
////#define _TS 100019111111
//#define _TS 200019111111
//#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
//#   include "../LLR_CCorder_9999999999.h"
//#   define getNomBkgO getNomBkgO_9999999999
//#endif
//
//#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
//#   include "../LLR_CCorder_10000000016.h"
//#   define getNomBkgO getNomBkgO_10000000016
//#endif
//
//#if _TS == 20000000016 && __has_include("../LLR_CCorder_20000000016.h")
//#   include "../LLR_CCorder_20000000016.h"
//#   define getNomBkgO getNomBkgO_20000000016
//#endif
//
//#if _TS == 100019111111 && __has_include("../LLR_CCorder_100019111111.h")
//#   include "../LLR_CCorder_100019111111.h"
//#   define getNomBkgO getNomBkgO_100019111111
//#	define ana_bm ana_bm_comb
//#endif
//
//#if _TS == 200019111111 && __has_include("../LLR_CCorder_200019111111.h")
//#   include "../LLR_CCorder_200019111111.h"
//#   define getNomBkgO getNomBkgO_200019111111
//#	define ana_bm ana_bm_comb_ub
//#endif
//
//#if _TS == 10000000003 && __has_include("../LLR_CCorder_10000000003.h")
//#   include "../LLR_CCorder_10000000003.h"
//#   define getNomBkgO getNomBkgO_10000000003
//#endif
//
////#if _TS != 9999999999
////#	define ana_bm ana_bm_comb
////#endif
//#include "../BDT/bininfo.h"
//#include "../BDT/BDTtraindiff.cxx"
//#include "../glauberparams_PbPb5TeV.h"
//#include "theory/get_theory.cxx"
//#include "Style_HIN-21-007.C"
//
////////LAMBDA, CONSTANTS ////
//	auto get_taa_err = [](ana_bins x){
//		auto taa = glp::Taa[{x.centl, x.centh}];
//		return (double) taa.second/taa.first;
//	};
//	auto quadsum = [](double arg1, double arg2){ return TMath::Sqrt(arg1 * arg1 + arg2 * arg2); };
//	double pp_lum =0;
//	double pp_sys =0;
//	double mb_unc =0;
//////////////////////////////
//void invokePAgraph(
//	TGraphAsymmErrors& pg_c1s,TGraphAsymmErrors& pg_c1s_sys,
//	TGraphAsymmErrors& pg_c2s,TGraphAsymmErrors& pg_c2s_sys,
//	TGraphAsymmErrors& pg_i1s,TGraphAsymmErrors& pg_i1s_sys,
//	TGraphAsymmErrors& pg_i2s,TGraphAsymmErrors& pg_i2s_sys,
//	TGraphAsymmErrors& pg_p1s,TGraphAsymmErrors& pg_p1s_sys,
//	TGraphAsymmErrors& pg_p2s,TGraphAsymmErrors& pg_p2s_sys
//);
//
//void analysis_plots_combine_func(TFile* hf, TFile* hsys, TFile* ppsys, TFile* hdff, TFile* hdfsys, TFile* ppdfsys);
//
//void analysis_plots_combine(){
//	analysis_plots_combine_func(TFile::Open(Form("./result/RAA_%ld.root", _TS)), TFile::Open(Form("../Systematics/data/total_systematics_RAA_%ld.root", _TS) ), TFile::Open("/home/CMS/Analysis/Upsilon3S_pp2017Ref/Results/PP_2017EOY_Systematic.root"), TFile::Open(Form("./result/DR_%ld.root", _TS) ), TFile::Open(Form("../Systematics/data/total_systematics_DR_%ld.root", _TS) ), TFile::Open("/home/CMS/Analysis/Upsilon3S_pp2017Ref/Results/PP_2017EOY_Systematic.root"));
//};

void analysis_plots_combine_func_w1s_PROJECTION(TFile* hf, TFile* hsys, TFile* ppsys, TFile* hdff, TFile* hdfsys, TFile* ppdfsys, int sc)
{
	std::vector<TH1D*> vhist = {};
	std::vector<TGraphAsymmErrors*> vgraph= {};

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

	vhist.push_back(hp3s);	vhist.push_back(hp3s_sys);	vhist.push_back(hpp_p3s_sys);
	vhist.push_back(hp2s);	vhist.push_back(hp2s_sys);	vhist.push_back(hpp_p2s_sys);
	vhist.push_back(hc3s);	vhist.push_back(hc3s_sys);	vhist.push_back(hpp_i3s_sys);
	vhist.push_back(hc2s);	vhist.push_back(hc2s_sys);	vhist.push_back(hpp_i2s_sys);


	TGraphAsymmErrors *g_p3s = new TGraphAsymmErrors(); TGraphAsymmErrors *g_p3s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *g_p2s = new TGraphAsymmErrors(); TGraphAsymmErrors *g_p2s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *g_c3s = new TGraphAsymmErrors(); TGraphAsymmErrors *g_c3s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *g_c2s = new TGraphAsymmErrors(); TGraphAsymmErrors *g_c2s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *g_i3s = new TGraphAsymmErrors(); TGraphAsymmErrors *g_i3s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *g_i2s = new TGraphAsymmErrors(); TGraphAsymmErrors *g_i2s_sys = new TGraphAsymmErrors();

	TGraphAsymmErrors *pg_c1s = new TGraphAsymmErrors(); TGraphAsymmErrors *pg_c1s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *pg_c2s = new TGraphAsymmErrors(); TGraphAsymmErrors *pg_c2s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *pg_i1s = new TGraphAsymmErrors(); TGraphAsymmErrors *pg_i1s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *pg_i2s = new TGraphAsymmErrors(); TGraphAsymmErrors *pg_i2s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *pg_p1s = new TGraphAsymmErrors(); TGraphAsymmErrors *pg_p1s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors *pg_p2s = new TGraphAsymmErrors(); TGraphAsymmErrors *pg_p2s_sys = new TGraphAsymmErrors();
	invokePAgraph(
		*pg_c1s, *pg_c1s_sys,
		*pg_c2s, *pg_c2s_sys,
		*pg_i1s, *pg_i1s_sys,
		*pg_i2s, *pg_i2s_sys,
		*pg_p1s, *pg_p1s_sys,
		*pg_p2s, *pg_p2s_sys,
		sc
	);
	std::cout << pg_c1s->GetPointX(1) << std::endl;

	vgraph.push_back(g_p3s); vgraph.push_back(g_p3s_sys);
	vgraph.push_back(g_p2s); vgraph.push_back(g_p2s_sys);
	vgraph.push_back(g_c3s); vgraph.push_back(g_c3s_sys);
	vgraph.push_back(g_c2s); vgraph.push_back(g_c2s_sys);
	vgraph.push_back(g_i3s); vgraph.push_back(g_i3s_sys);
	vgraph.push_back(g_i2s); vgraph.push_back(g_i2s_sys);

	vgraph.push_back(pg_c1s); vgraph.push_back(pg_c1s_sys);
	vgraph.push_back(pg_c2s); vgraph.push_back(pg_c2s_sys);
	vgraph.push_back(pg_i1s); vgraph.push_back(pg_i1s_sys);
	vgraph.push_back(pg_i2s); vgraph.push_back(pg_i2s_sys);
	vgraph.push_back(pg_p1s); vgraph.push_back(pg_p1s_sys);
	vgraph.push_back(pg_p2s); vgraph.push_back(pg_p2s_sys);


	g_p3s->SetName("g_p3s"); g_p3s_sys->SetName("g_p3s_sys");
	g_p2s->SetName("g_p2s"); g_p2s_sys->SetName("g_p2s_sys");
	g_c3s->SetName("g_c3s"); g_c3s_sys->SetName("g_c3s_sys");
	g_c2s->SetName("g_c2s"); g_c2s_sys->SetName("g_c2s_sys");
	g_i3s->SetName("g_i3s"); g_i3s_sys->SetName("g_i3s_sys");
	g_i2s->SetName("g_i2s"); g_i2s_sys->SetName("g_i2s_sys");

	TH1D* hp23s = (TH1D*) hdff->Get("rp3S");
	TH1D* hc23s = (TH1D*) hdff->Get("rc3S");

	TH1D* hp23s_sys = (TH1D*) hdfsys->Get("syst_comp/hsys_tot_p3S");
	TH1D* hc23s_sys = (TH1D*) hdfsys->Get("syst_comp/hsys_tot_c3S");

	TH1D* hpp_p23s_sys = (TH1D*) ppdfsys->Get("hptPP_3Sover2S_ratio");
	TH1D* hpp_i23s_sys = (TH1D*) ppdfsys->Get("hIntPP_3Sover2S_ratio");

	TH1D* hpp_p23s_unc = (TH1D*) ppdfsys->Get("hptPP_3S_yield_total");
	TH1D* hpp_i23s_unc = (TH1D*) ppdfsys->Get("hIntPP_3S_yield_total");

	TGraphAsymmErrors* g_p23s = new TGraphAsymmErrors(); TGraphAsymmErrors* g_p23s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors* g_c23s = new TGraphAsymmErrors(); TGraphAsymmErrors* g_c23s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors* g_i23s = new TGraphAsymmErrors(); TGraphAsymmErrors* g_i23s_sys = new TGraphAsymmErrors();

//////////////////////////NOMINAL VALUE, STATISTICAL ERROR///////////////////////////

	auto fillgraph = [&](TH1D& hist, TGraphAsymmErrors& grap, string abt, int mode){
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
			point_y.second = point_y.second * projectionStat(sc, mode);
			grap.SetPointError(idx-1, point_x.second, point_x.second, point_y.second, point_y.second);
			if(ab.bintype == kPt){
				grap.GetXaxis()->SetLimits(0,30);
			}

		}
	};

/////////////////////////////////SYSTEMATIC ERRORS///////////////////////////////////


	auto fillsysgraph = [&](TH1D& hist, TH1D& raahist, TGraphAsymmErrors& grap, string abt, int mode){
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
			point_y.second = point_y.second * projectionSyst(sc, mode);
			grap.SetPointError(idx-1, point_x.second, point_x.second, point_y.second, point_y.second);
		}
	};
	auto fillsysgraphdr = [&](TH1D& hist, TH1D& raahist, TGraphAsymmErrors& grap, string abt, int mode){
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
			point_y.second = point_y.second * projectionSyst(sc, mode);
			grap.SetPointError(idx-1, point_x.second, point_x.second, point_y.second, point_y.second);
		}
	};
/////////////////////////////////INTEGRATED BIN///////////////////////////////////

	g_i2s->AddPoint(2, hc2s->GetBinContent(1)) ;
	g_i2s->SetPointError(0, 0,0, hc2s->GetBinError(1), hc2s->GetBinError(1) ) ;
	g_i3s->AddPoint(3, hc3s->GetBinContent(1)) ;
	g_i3s->SetPointError(0, 0,0, hc3s->GetBinError(1), hc3s->GetBinError(1) ) ;

	double int_sys_width = 0.23;

	double val_2s = hc2s->GetBinContent(1);
	double val_3s = hc3s->GetBinContent(1);
	double int_sys_2s = (hc2s_sys->GetBinContent(1));
	double int_sys_3s = (hc3s_sys->GetBinContent(1));
	double int_pp_sys_2s = (hpp_i2s_sys->GetBinContent(1));
	double int_pp_sys_3s = (hpp_i3s_sys->GetBinContent(1));
	int_sys_2s =  quadsum( mb_unc, quadsum( pp_sys, quadsum(pp_lum, quadsum(int_pp_sys_2s, int_sys_2s) ) ) ) * projectionSyst(sc, 2018);
	int_sys_3s =  quadsum( mb_unc, quadsum( pp_sys, quadsum(pp_lum, quadsum(int_pp_sys_3s, int_sys_3s) ) ) ) * projectionSyst(sc, 2018);
	g_i2s_sys->AddPoint(2, val_2s) ;
	g_i2s_sys->SetPointError(0, int_sys_width, int_sys_width, val_2s *int_sys_2s, val_2s * int_sys_2s ) ;
	g_i3s_sys->AddPoint(3, val_3s) ;
	g_i3s_sys->SetPointError(0, int_sys_width, int_sys_width, val_3s *int_sys_3s, val_3s * int_sys_3s ) ;

	g_i23s->AddPoint(2.5, hc23s->GetBinContent(1)) ;
	g_i23s->SetPointError(0, 0,0, hc23s->GetBinError(1), hc23s->GetBinError(1) ) ;
	double int_sys_width_dr = 0.45;
	double int_pp_sys_dr = hpp_i23s_sys->GetBinContent(1);
	g_i23s_sys->AddPoint(2.5, hc23s->GetBinContent(1)) ;
	g_i23s_sys->SetPointError(0, int_sys_width_dr, int_sys_width_dr, hc23s_sys->GetBinContent(1) * quadsum( int_pp_sys_dr, hc23s->GetBinContent(1)) * projectionSyst(sc, 2018), hc23s_sys->GetBinContent(1) * quadsum( int_pp_sys_dr, hc23s->GetBinContent(1)) * projectionSyst(sc, 2018)  ) ;

//////////////////////////////////////////////////////////////////////////////////

	fillgraph(*hc2s, *g_c2s, "2c", 0);
	fillgraph(*hc3s, *g_c3s, "3c", 0);
	fillgraph(*hp2s, *g_p2s, "2p", 0);
	fillgraph(*hp3s, *g_p3s, "3p", 0);

	fillsysgraph(*hc2s_sys, *hc2s, *g_c2s_sys, "2c", 2018);
	fillsysgraph(*hc3s_sys, *hc3s, *g_c3s_sys, "3c", 2018);
	fillsysgraph(*hp2s_sys, *hp2s, *g_p2s_sys, "2p", 2018);
	fillsysgraph(*hp3s_sys, *hp3s, *g_p3s_sys, "3p", 2018);

	fillgraph(*hc23s, *g_c23s, "3c", 2018);
	fillgraph(*hp23s, *g_p23s, "3p", 2018);

	fillsysgraphdr(*hc23s_sys, *hc23s, *g_c23s_sys, "3c", 2018);
	fillsysgraphdr(*hp23s_sys, *hp23s, *g_p23s_sys, "3p", 2018);

	double p2scale = ( (0.83 -0.12)/ (1. - 0.83) ) ;
	kGLBp2scale = p2scale;

	readyPlot(g_c2s, g_c2s_sys, "CA2SCENT");
	readyPlot(g_i2s, g_i2s_sys, "CA2SINT");
	
	readyPlot(g_c3s, g_c3s_sys, "CA3SCENT");
	readyPlot(g_i3s, g_i3s_sys, "CA3SINT");

	readyPlot(g_p2s, g_p2s_sys, "CA2SPT");
	readyPlot(g_p3s, g_p3s_sys, "CA3SPT");

	readyPlot(pg_c2s, pg_c2s_sys, "PA2SCENT");
	readyPlot(pg_i2s, pg_i2s_sys, "PA2SINT");
	
	readyPlot(pg_c1s, pg_c1s_sys, "PA1SCENT");
	readyPlot(pg_i1s, pg_i1s_sys, "PA1SINT");

	readyPlot(pg_p2s, pg_p2s_sys, "PA2SPT");
	readyPlot(pg_p1s, pg_p1s_sys, "PA1SPT");

	readyPlot(g_c23s, g_c23s_sys, "CADRCENT");
	readyPlot(g_i23s, g_i23s_sys, "CADRINT");
	readyPlot(g_p23s, g_p23s_sys, "CADRPT");

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

	dbg();
    b_err->SetX1(360);
    b_err->SetX2(380);
    b_err->SetY1(1 - fabs(glb_errMB_PP));
    b_err->SetY2(1 + fabs(glb_errMB_PP));
    b_err->SetFillColorAlpha(12, 0.0);
    b_err->SetLineWidth(2);
	b_err->SetLineColor(kGray+2);

    b_2serr->SetX1(380);
    b_2serr->SetX2(400);
    b_2serr->SetY1(1 - fabs(glb_2serr));
    b_2serr->SetY2(1 + fabs(glb_2serr));
    b_2serr->SetFillColorAlpha(kAzure-3, 0.8);
    b_2serr->SetLineWidth(1);

    b_3serr->SetX1(400);
    b_3serr->SetX2(420);
    b_3serr->SetY1(1 - glb_3serr);
    b_3serr->SetY2(1 + glb_3serr);
    b_3serr->SetFillColorAlpha(kTeal+5, 0.8);
    b_3serr->SetLineWidth(1);

	b_pterr->SetX1(28);
	b_pterr->SetX2(30);
	b_pterr->SetY1(1 - glb_errpt);
	b_pterr->SetY2(1 + glb_errpt);
	b_pterr->SetFillColorAlpha(12, 0.8);
	b_pterr->SetLineWidth(2);
	b_pterr->SetLineColor(kGray+2);
	dbg();

///////////////////////////////////////////////////////////////////////////////

//////////////////////////////Auxiliary Drawings///////////////////////////////
	gStyle->SetEndErrorSize(0);

	double yup = 1.3;
	double ydown = 0.0;
	double label_pos_up = DRCENTYUP - 0.2 ;

	TLine* lineone = new TLine();
	lineone->SetLineStyle(kDashed);
	lineone->SetLineWidth(1);

	TLatex* tl = new TLatex();
	tl->SetTextSize(0.042);
	tl->SetTextFont(42);

	TLegend* leg_cent = new TLegend(0.53, 0.4, 0.85, 0.70);
	leg_cent->AddEntry(pg_c1s, "#Upsilon(1S)", "pl");
	leg_cent->AddEntry(g_c2s, "#Upsilon(2S)", "pl");
	leg_cent->AddEntry(g_c3s, "#Upsilon(3S)", "pl");
	leg_cent->SetBorderSize(0);
	leg_cent->SetTextFont(42);
	leg_cent->SetTextSize(0.04);

	TLegend* leg_pt = new TLegend(0.45, 0.4, 0.85, 0.7);
	leg_pt->AddEntry(pg_p1s, "#Upsilon(1S)", "pl");
	leg_pt->AddEntry(g_p2s, "#Upsilon(2S)", "pl");
	leg_pt->AddEntry(g_p3s, "#Upsilon(3S)", "pl");
	leg_pt->SetBorderSize(0);
	leg_pt->SetTextFont(42);
	leg_pt->SetTextSize(0.04);
//////////////////////////////////INITIALIZE CANVASES/////////////////////////////////

	std::map<string, TObject*> towrite;
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
	p1_L->SetRightMargin(0);
	p1_R->SetLeftMargin(0);
	////////READY PADS/////////
	c1->cd();
	p1_L->Draw();
	p1_R->Draw();
	c2->cd();
	p2->Draw();
	////////DRAW GRAPHS AND SO ON////////////
	//CENT CANVAS//
	c1->cd();
	//RAA CENT LEFT//
	p1_L->cd();
	g_c2s->Draw("APE");
	pg_c1s->Draw("PE");
	g_c3s->Draw("PE");
	pg_c1s_sys->Draw("5");
	pg_c1s->SetName("g_c1s");
	pg_c1s_sys->SetName("g_c1s_sys");
	towrite["pg_c1s"] = pg_c1s;
	towrite["pg_c1s_sys"] = pg_c1s_sys;
	g_c2s_sys->Draw("5");
	g_c3s_sys->Draw("5");
	TLine* p1_L_line1 = lineone->DrawLine(0, 1, 420, 1);
	TLatex* p1_L_latex1 = tl->DrawLatex( 40, 1.15,"p_{T} < 30 GeV/c");
	TLatex* p1_L_latex2 = tl->DrawLatex( 40, 1.06, "|y| < 2.4");
	leg_cent->Draw();
	b_err->  Draw("L");
	b_2serr->Draw("L");
	b_3serr->Draw("L");
	towrite["p1_L_box1"] = b_err;
	towrite["p1_L_box2"] = b_2serr;
	towrite["p1_L_box3"] = b_3serr;
	towrite["p1_L_line1"] = p1_L_line1;
	towrite["p1_L_latex1"] = p1_L_latex1;
	towrite["p1_L_latex2"] = p1_L_latex2;
	towrite["leg_cent"] = leg_cent;
	towrite["g_c2s"] = g_c2s;
	towrite["g_c3s"] = g_c3s;
	towrite["g_c3s_sys"] = g_c3s_sys;
	towrite["g_c2s_sys"] = g_c2s_sys;

	p1_L->Update();
	p1_L->Draw();
	towrite["p1_L"] = p1_L;
	//RAA INT RIGHT//
	p1_R->cd();
	g_i2s->GetXaxis()->SetLimits(0,4);
	g_i2s->Draw("APE");
	pg_i1s->Draw("PE");
	g_i3s->Draw("PE");
	pg_i1s_sys->Draw("5");
	g_i2s_sys->Draw("5");
	g_i3s_sys->Draw("5");
	TLine* p1_R_line1 = lineone->DrawLine(0,1,4,1);
	tl->SetTextSize(0.042* p2scale);
	tl->SetTextAlign(21);
	TLatex* p1_R_latex1 = tl->DrawLatex( 2.0, 1.02, "Cent.");
	TLatex* p1_R_latex2 = tl->DrawLatex( 2.0, 0.94, "0-90%");
	pg_i1s_sys->SetName("g_i1s_sys");
	pg_i1s->SetName("g_i1s");
	towrite["g_i1s_sys"] = pg_i1s_sys;
	towrite["g_i2s_sys"] = g_i2s_sys;
	towrite["g_i3s_sys"] = g_i3s_sys;
	towrite["g_i3s"] = g_i3s;
	towrite["g_i2s"] = g_i2s;
	towrite["pg_i1s"] = pg_i1s;
	towrite["p1_R_line1"] = p1_L_line1;
	towrite["p1_R_latex1"] = p1_R_latex1;
	towrite["p1_R_latex2"] = p1_R_latex2;
	p1_R->Update();
	p1_R->Draw();
	towrite["p1_R"] = p1_R;

	//PT CANVAS//
	c2->cd();
	p2->cd();
	g_p2s->Draw("APE");
	pg_p1s->Draw("PE");
	g_p3s->Draw("PE");
	pg_p1s_sys->Draw("5");
	g_p2s_sys->Draw("5");
	g_p3s_sys->Draw("5");
	TLine* p2_line1 = lineone->DrawLine(0, 1, 30, 1);
	tl->SetTextSize(0.042);
	tl->SetTextAlign(11);
//	TLatex* p2_latex1 = tl->DrawLatex( 2.5, 1.15,"p_{T} < 30 GeV/c");
	TLatex* p2_latex2 = tl->DrawLatex( 2.5, 1.15, "|y| < 2.4");
	TLatex* p2_latex3 = tl->DrawLatex( 2.5,1.06, "Cent. 0-90%");
	pg_p1s->SetName("g_p1s");
	pg_p1s_sys->SetName("g_p1s_sys");
	towrite["g_p1s"] = pg_p1s;
	towrite["g_p1s_sys"] = pg_p1s_sys;
	towrite["g_p2s"] = g_p2s;
	towrite["g_p3s"] = g_p3s;
	towrite["g_p3s_sys"] = g_p3s_sys;
	towrite["g_p2s_sys"] = g_p2s_sys;
	towrite["p2_line1"] = p2_line1;
//	towrite["p2_latex1"] = p2_latex1;
	towrite["p2_latex2"] = p2_latex2;
	towrite["p2_latex3"] = p2_latex3;
	towrite["leg_pt"] = leg_pt;
	leg_pt->Draw();
	b_pterr->Draw("L");
	towrite["p2_box1"] = b_pterr;

	p2->Draw();
	towrite["p2"] = p2;
	//LUMIFY PADS AND COMBINE PLOTS//
	c1->cd();
	p1_L->cd();
	CMS_lumi_square(p1_L,1030 + sc, 33, 1);
	c2->cd();
	p2->cd();
	CMS_lumi_square( p2, 1030 + sc, 33, 1);
	c1->Update();
	c1->Modified();
	c2->Update();
	c2->Modified();
	towrite["c2"] = c2;
	towrite["c1"] = c1;

	c1->SaveAs(Form("../checkout/tscol/AUX/Projection/RAA_centrality_int_%ld_v3_w1s_Scenario-%d.pdf", _TS, sc) );
	c2->SaveAs(Form("../checkout/tscol/AUX/Projection/RAA_pt_%ld_v3_w1s_Scenario-%d.pdf", _TS, sc) );
	TFile* output = new TFile(Form("result/resultRAA_w1s_%ld_raw_v3_Scenario-%d.root", _TS,sc), "recreate");
	TDirectory *Dir_vanila = output->mkdir("vanila");
	Dir_vanila->cd();
	c1->Write();
	c2->Write();
	for(auto item : towrite){
		item.second->Write();
	}
	output->cd();
	/////////////////////END OF WRITE LOOP 1//////////////////////////////
	
	towrite["p1_L"]->Clear();
	towrite["p1_R"]->Clear();
	towrite["p2"]->Clear();
	towrite["leg_cent"]->Delete();
	towrite["leg_pt"]->Delete();

	leg_cent = new TLegend(0.75, 0.4, 0.85, 0.70);
	leg_cent->AddEntry(g_c2s, "#Upsilon(2S)", "pl");
	leg_cent->AddEntry(g_c3s, "#Upsilon(3S)", "pl");
	leg_cent->SetBorderSize(0);
	leg_cent->SetTextFont(42);
	leg_cent->SetTextSize(0.04);

	leg_pt = new TLegend(0.65, 0.3, 0.85, 0.7);
	leg_pt->AddEntry(g_p2s, "#Upsilon(2S)", "pl");
	leg_pt->AddEntry(g_p3s, "#Upsilon(3S)", "pl");
	leg_pt->SetBorderSize(0);
	leg_pt->SetTextFont(42);
	leg_pt->SetTextSize(0.04);

//	towrite["xcx"] = xcx;
//	towrite["xcx"] = xcx;
//	towrite["xcx"] = xcx;
//	towrite["xcx"] = xcx;
//	towrite["xcx"] = xcx;
//	towrite["xcx"] = xcx;
//	towrite["xcx"] = xcx;

	output->Close();

//	towrite["p1_L"]->Clear();
//	towrite["p1_R"]->Clear();
//	towrite["p2"]->Clear();
//	towrite["leg_cent"]->Delete();
//	towrite["leg_pt"]->Delete();
//
//	p1_L->SetLeftMargin(0.12);
//	p2->SetLeftMargin(0.12);
//
//	leg_cent = new TLegend(0.21,0.17, 0.66, 0.36);
//	leg_cent->AddEntry(g_c23s, "#Upsilon(3S)", "pl");
//	leg_cent->SetBorderSize(0);
//	leg_cent->SetTextFont(42);
//	leg_cent->SetTextSize(0.032);
//
//	leg_pt = new TLegend(0.47,0.17, 0.78, 0.32);
//	leg_pt->AddEntry(g_p23s, "#Upsilon(3S)", "pl");
//	leg_pt->SetBorderSize(0);
//	leg_pt->SetTextFont(42);
//	leg_pt->SetTextSize(0.032);
//	c1->cd();
//	p1_L->Draw();
//	p1_R->Draw();
//	c2->cd();
//	p2->Draw();
//	////////DRAW GRAPHS AND SO ON////////////
//	//CENT CANVAS//
//	c1->cd();
//	//RAA CENT LEFT//
//	p1_L->cd();
//	g_c23s->Draw("APE");
//	g_c23s_sys->Draw("5");
//	p1_L_line1 = lineone->DrawLine(0, 1, 420, 1);
//	tl->DrawLatex( 40, label_pos_up +0.05,"p_{T} < 30 GeV/c");
//	tl->DrawLatex( 40, label_pos_up -0.15, "|y| < 2.4");
////	leg_cent->Draw();
//	b_3serr->Draw("L");
//
//	p1_L->Update();
//	p1_L->Draw();
//	//RAA INT RIGHT//
//	p1_R->cd();
//	g_i23s->Draw("APE");
//	g_i23s_sys->Draw("5");
//	p1_R_line1 = lineone->DrawLine(1,1,4,1);
//	tl->SetTextSize(0.024* p2scale);
//	tl->SetTextAlign(21);
//	p1_R_latex1 = tl->DrawLatex( 2.5, 1.02, "Cent.");
//	p1_R_latex2 = tl->DrawLatex( 2.5, 0.94, "0-90%");
//	p1_R->Update();
//	p1_R->Draw();
//	towrite["p1_R"] = p1_R;
//
//	//PT CANVAS//
//	c2->cd();
//	p2->cd();
//	g_p23s->Draw("APE");
//	g_p23s_sys->Draw("5");
//	p2_line1 = lineone->DrawLine(0, 1, 30, 1);
//	tl->SetTextSize(0.042);
//	tl->SetTextAlign(11);
//	tl->DrawLatex( 2.5, label_pos_up + 0.05,"p_{T} < 30 GeV/c");
//	tl->DrawLatex( 12, label_pos_up + 0.05 , "|y| < 2.4");
//	tl->DrawLatex( 2.5,label_pos_up - 0.15 , "Cent. 0-90%");
////	leg_pt->Draw();
//	b_pterr->Draw("L");
//
//	p2->Draw();
//	towrite["p2"] = p2;
//	//LUMIFY PADS AND COMBINE PLOTS//
//	c1->cd();
//	p1_L->cd();
//	CMS_lumi_square(p1_L,1030 + sc, 33, 1);
//	c2->cd();
//	p2->cd();
//	CMS_lumi_square( p2, 1030 + sc, 33, 1);
//	c1->Update();
//	c1->Modified();
//	c2->Update();
//	c2->Modified();
//	towrite["c2"] = c2;
//	towrite["c1"] = c1;
//
//	c1->SaveAs(Form("../checkout/tscol/DR_centrality_int_%ld_v3.pdf", _TS) );
//	c2->SaveAs(Form("../checkout/tscol/DR_pt_%ld_v3.pdf", _TS) );
//	output = new TFile(Form("resultDR_%ld_v3.root", _TS), "recreate");
//	dbg();
//	Dir_vanila = output->mkdir("vanila");
//	dbg();
//	Dir_vanila->cd();
//	c1->Write();
//	c2->Write();
//	for(auto item : towrite){
//		item.second->Write();
//	}
	output->cd();
};


//void invokePAgraph(
//	TGraphAsymmErrors& pg_c1s,TGraphAsymmErrors& pg_c1s_sys,
//	TGraphAsymmErrors& pg_c2s,TGraphAsymmErrors& pg_c2s_sys,
//	TGraphAsymmErrors& pg_i1s,TGraphAsymmErrors& pg_i1s_sys,
//	TGraphAsymmErrors& pg_i2s,TGraphAsymmErrors& pg_i2s_sys,
//	TGraphAsymmErrors& pg_p1s,TGraphAsymmErrors& pg_p1s_sys,
//	TGraphAsymmErrors& pg_p2s,TGraphAsymmErrors& pg_p2s_sys
//){
//
/////1S/////////
//	pg_c1s.SetPoint(0,8.3000002, 0.79200000);
//	pg_c1s.SetPoint(1,30.600000, 0.92199999);
//	pg_c1s.SetPoint(2, 53.900002, 0.60900003);
//	pg_c1s.SetPoint(3, 87.000000, 0.52399999);
//	pg_c1s.SetPoint(4, 131.39999, 0.48500001);
//	pg_c1s.SetPoint(5, 189.20000, 0.40200001);
//	pg_c1s.SetPoint(6, 264.20001, 0.32400000);
//	pg_c1s.SetPoint(7, 333.29999, 0.32100001);
//	pg_c1s.SetPoint(8, 384.29999, 0.31900001);
//
//	pg_i1s.SetPoint(0, 1, 0.376 );
//
//	pg_p1s.SetPoint(0, 1,	 0.301);
//	pg_p1s.SetPoint(1, 3,	 0.362);
//	pg_p1s.SetPoint(2, 5,	 0.388);
//	pg_p1s.SetPoint(3, 7.5, 0.402);
//	pg_p1s.SetPoint(4, 10.5,0.422);
//	pg_p1s.SetPoint(5, 21,	 0.425);
//
//	pg_c1s_sys.SetPoint(0,8.3000002, 0.79200000);
//	pg_c1s_sys.SetPoint(1,30.600000, 0.92199999);
//	pg_c1s_sys.SetPoint(2, 53.900002, 0.60900003);
//	pg_c1s_sys.SetPoint(3, 87.000000, 0.52399999);
//	pg_c1s_sys.SetPoint(4, 131.39999, 0.48500001);
//	pg_c1s_sys.SetPoint(5, 189.20000, 0.40200001);
//	pg_c1s_sys.SetPoint(6, 264.20001, 0.32400000);
//	pg_c1s_sys.SetPoint(7, 333.29999, 0.32100001);
//	pg_c1s_sys.SetPoint(8, 384.29999, 0.31900001);
//
//	pg_i1s_sys.SetPoint(0, 1, 0.376 );
//
//	pg_p1s_sys.SetPoint(0, 1,	 0.301);
//	pg_p1s_sys.SetPoint(1, 3,	 0.362);
//	pg_p1s_sys.SetPoint(2, 5,	 0.388);
//	pg_p1s_sys.SetPoint(3, 7.5, 0.402);
//	pg_p1s_sys.SetPoint(4, 10.5,0.422);
//	pg_p1s_sys.SetPoint(5, 21,	 0.425);
//
//	pg_c1s.SetPointError(0, 0, 0, 0.13100000, 0.13100000);
//	pg_c1s.SetPointError(1, 0, 0, 0.088000000, 0.088000000);
//	pg_c1s.SetPointError(2, 0, 0, 0.052999999, 0.052999999);
//	pg_c1s.SetPointError(3, 0, 0, 0.035999998, 0.035999998);
//	pg_c1s.SetPointError(4, 0, 0, 0.027000001, 0.027000001);
//	pg_c1s.SetPointError(5, 0, 0, 0.039000001, 0.039000001);
//	pg_c1s.SetPointError(6, 0, 0, 0.017000001, 0.017000001);
//	pg_c1s.SetPointError(7, 0, 0, 0.021000000, 0.021000000);
//	pg_c1s.SetPointError(8, 0, 0, 0.018999999, 0.018999999);
//
//	pg_i1s.SetPointError(0 ,0, 0,  quadsum(0.013, 0), quadsum(0.013,0) );
//         
//	pg_p1s.SetPointError(0, 1.0, 1.0, quadsum(0.027, 0.000), quadsum(0.027, 0.000));
//	pg_p1s.SetPointError(1, 1.0, 1.0, quadsum(0.029, 0.000), quadsum(0.029, 0.000));
//	pg_p1s.SetPointError(2, 1.0, 1.0, quadsum(0.033, 0.000), quadsum(0.033, 0.000));
//	pg_p1s.SetPointError(3, 1.5, 1.5, quadsum(0.028, 0.000), quadsum(0.028, 0.000));
//	pg_p1s.SetPointError(4, 1.5, 1.5, quadsum(0.035, 0.000), quadsum(0.035, 0.000));
//	pg_p1s.SetPointError(5, 9.0, 9.0, quadsum(0.026, 0.000), quadsum(0.026, 0.000));
//
//
//	pg_c1s_sys.SetPointError(0, 0, 0, 0.13100000, 0.13100000);
//	pg_c1s_sys.SetPointError(1, 0, 0, 0.088000000, 0.088000000);
//	pg_c1s_sys.SetPointError(2, 0, 0, 0.052999999, 0.052999999);
//	pg_c1s_sys.SetPointError(3, 0, 0, 0.035999998, 0.035999998);
//	pg_c1s_sys.SetPointError(4, 0, 0, 0.027000001, 0.027000001);
//	pg_c1s_sys.SetPointError(5, 0, 0, 0.039000001, 0.039000001);
//	pg_c1s_sys.SetPointError(6, 0, 0, 0.017000001, 0.017000001);
//	pg_c1s_sys.SetPointError(7, 0, 0, 0.021000000, 0.021000000);
//	pg_c1s_sys.SetPointError(8, 0, 0, 0.018999999, 0.018999999);
//
//	pg_i1s_sys.SetPointError(0 ,0, 0,  quadsum(0.000, 0.035), quadsum(0.000,0.035) );
//
//	pg_p1s_sys.SetPointError(0, 1.0, 1.0, quadsum(0.000, 0.123), quadsum(0.000, 0.123));
//	pg_p1s_sys.SetPointError(1, 1.0, 1.0, quadsum(0.000, 0.035), quadsum(0.000, 0.035));
//	pg_p1s_sys.SetPointError(2, 1.0, 1.0, quadsum(0.000, 0.035), quadsum(0.000, 0.035));
//	pg_p1s_sys.SetPointError(3, 1.5, 1.5, quadsum(0.000, 0.032), quadsum(0.000, 0.032));
//	pg_p1s_sys.SetPointError(4, 1.5, 1.5, quadsum(0.000, 0.045), quadsum(0.000, 0.045));
//	pg_p1s_sys.SetPointError(5, 9.0, 9.0, quadsum(0.000, 0.036), quadsum(0.000, 0.036));
//
/////2S/////////
//	pg_c2s.SetPoint(0, 8.3,	 0.563);
//	pg_c2s.SetPoint(1, 30.6,	 0.530);
//	pg_c2s.SetPoint(2, 53.9,	 0.21);
//	pg_c2s.SetPoint(3, 87.0, 0.229);
//	pg_c2s.SetPoint(4, 131.4,0.194);
//	pg_c2s.SetPoint(5, 189.2,	 0.154);
//	pg_c2s.SetPoint(6, 264.2,	 0.101);
//	pg_c2s.SetPoint(7, 333.3,	 0.119);
//
//	pg_i2s.SetPoint(0, 1., 0.117 );
//
//	pg_c2s_sys.SetPoint(0, 8.3,	 0.563);
//	pg_c2s_sys.SetPoint(1, 30.6,	 0.530);
//	pg_c2s_sys.SetPoint(2, 53.9,	 0.21);
//	pg_c2s_sys.SetPoint(3, 87.0, 0.229);
//	pg_c2s_sys.SetPoint(4, 131.4,0.194);
//	pg_c2s_sys.SetPoint(5, 189.2,	 0.154);
//	pg_c2s_sys.SetPoint(6, 264.2,	 0.101);
//	pg_c2s_sys.SetPoint(7, 333.3,	 0.119);
//
//	pg_i2s_sys.SetPoint(0, 1., 0.117 );
//
//	pg_c2s.SetPointError(0, 0.0, 0.0, quadsum(0.319, 0.000), quadsum(0.319, 0.000));
//	pg_c2s.SetPointError(1, 0.0, 0.0, quadsum(0.170, 0.000), quadsum(0.170, 0.000));
//	pg_c2s.SetPointError(2, 0.0, 0.0, quadsum(0.106, 0.000), quadsum(0.106, 0.000));
//	pg_c2s.SetPointError(3, 0.0, 0.0, quadsum(0.077, 0.000), quadsum(0.077, 0.000));
//	pg_c2s.SetPointError(4, 0.0, 0.0, quadsum(0.060, 0.000), quadsum(0.060, 0.000));
//	pg_c2s.SetPointError(5, 0.0, 0.0, quadsum(0.092, 0.000), quadsum(0.092, 0.000));
//	pg_c2s.SetPointError(6, 0.0, 0.0, quadsum(0.042, 0.000), quadsum(0.042, 0.000));
//	pg_c2s.SetPointError(7, 0.0, 0.0, quadsum(0.051, 0.000), quadsum(0.051, 0.000));
//
//	pg_i2s.SetPointError(0 ,0, 0,  quadsum(0.022, 0.000), quadsum(0.022, 0.000) );
//
//	pg_p2s.SetPoint(0, 2,	 0.085);
//	pg_p2s.SetPoint(1, 6.5,	 0.129);
//	pg_p2s.SetPoint(2, 19.5, 0.126);
//
//	pg_p2s.SetPointError(0, 2.0, 2.0, quadsum(0.039, 0.000), quadsum(0.039, 0.000));
//	pg_p2s.SetPointError(1, 2.5, 2.5, quadsum(0.038, 0.000), quadsum(0.038, 0.000));
//	pg_p2s.SetPointError(2, 10.5, 10.5, quadsum(0.032, 0.000), quadsum(0.032, 0.000));
//
//
//	pg_c2s_sys.SetPointError(0, 0.0, 0.0, quadsum(0.000, 0.136), quadsum(0.000, 0.154));
//	pg_c2s_sys.SetPointError(1, 0.0, 0.0, quadsum(0.000, 0.128), quadsum(0.000, 0.131));
//	pg_c2s_sys.SetPointError(2, 0.0, 0.0, quadsum(0.000, 0.037), quadsum(0.000, 0.038));
//	pg_c2s_sys.SetPointError(3, 0.0, 0.0, quadsum(0.000, 0.023), quadsum(0.000, 0.023));
//	pg_c2s_sys.SetPointError(4, 0.0, 0.0, quadsum(0.000, 0.019), quadsum(0.000, 0.019));
//	pg_c2s_sys.SetPointError(5, 0.0, 0.0, quadsum(0.000, 0.032), quadsum(0.000, 0.032));
//	pg_c2s_sys.SetPointError(6, 0.0, 0.0, quadsum(0.000, 0.031), quadsum(0.000, 0.031));
//	pg_c2s_sys.SetPointError(7, 0.0, 0.0, quadsum(0.000, 0.009), quadsum(0.000, 0.009));
//
//	pg_i2s_sys.SetPointError(0 ,0, 0,  quadsum(0.000, 0.019), quadsum(0.000, 0.019) );
//
//	pg_p2s_sys.SetPoint(0, 2,	 0.085);
//	pg_p2s_sys.SetPoint(1, 6.5,	 0.129);
//	pg_p2s_sys.SetPoint(2, 19.5, 0.126);
//
//	pg_p2s_sys.SetPointError(0, 2.0, 2.0, quadsum(0.000, 0.095), quadsum(0.000, 0.095));
//	pg_p2s_sys.SetPointError(1, 2.5, 2.5, quadsum(0.000, 0.031), quadsum(0.000, 0.031));
//	pg_p2s_sys.SetPointError(2, 10.5, 10.5, quadsum(0.000, 0.016), quadsum(0.000, 0.016));
//};

