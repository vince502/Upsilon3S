
void analysis_plots_combine_func_w1s_forCS(TFile* hf, TFile* hsys, TFile* hdff, TFile* hdfsys)
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

	// TH1D* hpp_p3s_sys = (TH1D*) ppsys->Get("hptPP_3S_yield");
	// TH1D* hpp_p2s_sys = (TH1D*) ppsys->Get("hptPP_2S_yield");
	// TH1D* hpp_i3s_sys = (TH1D*) ppsys->Get("hIntPP_3S_yield");
	// TH1D* hpp_i2s_sys = (TH1D*) ppsys->Get("hIntPP_2S_yield");

	// TH1D* hpp_p3s_unc = (TH1D*) ppsys->Get("hptPP_3S_yield_total");
	// TH1D* hpp_p2s_unc = (TH1D*) ppsys->Get("hptPP_2S_yield_total");
	// TH1D* hpp_i3s_unc = (TH1D*) ppsys->Get("hIntPP_3S_yield_total");
	// TH1D* hpp_i2s_unc = (TH1D*) ppsys->Get("hIntPP_2S_yield_total");

	vhist.push_back(hp3s);	vhist.push_back(hp3s_sys);	//vhist.push_back(hpp_p3s_sys);
	vhist.push_back(hp2s);	vhist.push_back(hp2s_sys);	//vhist.push_back(hpp_p2s_sys);
	vhist.push_back(hc3s);	vhist.push_back(hc3s_sys);	//vhist.push_back(hpp_i3s_sys);
	vhist.push_back(hc2s);	vhist.push_back(hc2s_sys);	//vhist.push_back(hpp_i2s_sys);


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
		*pg_p2s, *pg_p2s_sys
	);

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
	g_p2s->SetName("g_p2s"); g_p2s_sys->SetName("g_c2s_sys");
	g_c3s->SetName("g_c3s"); g_c3s_sys->SetName("g_p3s_sys");
	g_c2s->SetName("g_c2s"); g_c2s_sys->SetName("g_c2s_sys");
	g_i3s->SetName("g_i3s"); g_i3s_sys->SetName("g_i3s_sys");
	g_i2s->SetName("g_i2s"); g_i2s_sys->SetName("g_i2s_sys");

	TH1D* hp23s = (TH1D*) hdff->Get("rp3S");
	TH1D* hc23s = (TH1D*) hdff->Get("rc3S");

	TH1D* hp23s_sys = (TH1D*) hdfsys->Get("syst_comp/hsys_tot_p3S");
	TH1D* hc23s_sys = (TH1D*) hdfsys->Get("syst_comp/hsys_tot_c3S");

	// TH1D* hpp_p23s_sys = (TH1D*) ppdfsys->Get("hptPP_3Sover2S_ratio");
	// TH1D* hpp_i23s_sys = (TH1D*) ppdfsys->Get("hIntPP_3Sover2S_ratio");

	// TH1D* hpp_p23s_unc = (TH1D*) ppdfsys->Get("hptPP_3S_yield_total");
	// TH1D* hpp_i23s_unc = (TH1D*) ppdfsys->Get("hIntPP_3S_yield_total");

	TGraphAsymmErrors* g_p23s = new TGraphAsymmErrors(); TGraphAsymmErrors* g_p23s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors* g_c23s = new TGraphAsymmErrors(); TGraphAsymmErrors* g_c23s_sys = new TGraphAsymmErrors();
	TGraphAsymmErrors* g_i23s = new TGraphAsymmErrors(); TGraphAsymmErrors* g_i23s_sys = new TGraphAsymmErrors();

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
				//point_x.second=  point_x.second *6;
				point_x.second=  7;
				ref_raa = raahist.GetBinContent( (vab.size()+1) - idx);
				nom_sys = hist.GetBinContent( (vab.size() +1) - idx);
				double tot_sys = quadsum(nom_sys, taa_err);
				point_y = { ref_raa, ref_raa * tot_sys };
			}
			if(ab.bintype == kPt){
				// auto hpt_err = (ab.state == 3) ? hpp_p3s_sys : hpp_p2s_sys;
				point_x = {((double)( ab.pl + ab.ph ))/2., ((double)(ab.ph-ab.pl))/2. };
				ref_raa = raahist.GetBinContent( idx );
				nom_sys = hist.GetBinContent( idx );
				//double pp_err = hpt_err->GetBinContent( idx );
				double tot_sys = nom_sys;
			
				point_y = { ref_raa , ref_raa * tot_sys };
			}
			grap.AddPoint(point_x.first, point_y.first);
			grap.SetPointError(idx-1, point_x.second, point_x.second, point_y.second, point_y.second);
		}
	};
	auto fillsysgraphdr = [&](TH1D& hist, TH1D& raahist, TGraphAsymmErrors& grap, string abt){
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
				//point_x.second=  point_x.second *6;
				point_x.second= 7;
				ref_raa = raahist.GetBinContent( (vab.size()+1) - idx);
				nom_sys = hist.GetBinContent( (vab.size() +1) - idx);
				point_y = { ref_raa, ref_raa * quadsum(nom_sys,0/* taa_err*/) };
			}
			if(ab.bintype == kPt){
				point_x = {((double)( ab.pl + ab.ph ))/2., ((double)(ab.ph-ab.pl))/2. };
				// double pp_sys = hpp_p3s_sys->GetBinContent( idx );  
				ref_raa = raahist.GetBinContent( idx );
				nom_sys = hist.GetBinContent( idx );
				point_y = { ref_raa , ref_raa * quadsum(nom_sys,0/* taa_err*/) };
			}
			grap.AddPoint(point_x.first, point_y.first);
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
	// double int_pp_sys_2s = (hpp_i2s_sys->GetBinContent(1));
	// double int_pp_sys_3s = (hpp_i3s_sys->GetBinContent(1));
	int_sys_2s =  quadsum( mb_unc, int_sys_2s);
	int_sys_3s =  quadsum( mb_unc, int_sys_3s);
	g_i2s_sys->AddPoint(2, val_2s) ;
	g_i2s_sys->SetPointError(0, int_sys_width, int_sys_width, val_2s *int_sys_2s, val_2s * int_sys_2s ) ;
	g_i3s_sys->AddPoint(3, val_3s) ;
	g_i3s_sys->SetPointError(0, int_sys_width, int_sys_width, val_3s *int_sys_3s, val_3s * int_sys_3s ) ;

	g_i23s->AddPoint(2.5, hc23s->GetBinContent(1)) ;
	g_i23s->SetPointError(0, 0,0, hc23s->GetBinError(1), hc23s->GetBinError(1) ) ;
	double int_sys_width_dr = 0.45;
	// double int_pp_sys_dr = hpp_i23s_sys->GetBinContent(1);
	//g_i23s_sys->AddPoint(2.5, hc23s->GetBinContent(1)) ;
	//g_i23s_sys->SetPointError(0, int_sys_width_dr, int_sys_width_dr, hc23s_sys->GetBinContent(1) * hc23s->GetBinContent(1), hc23s_sys->GetBinContent(1) hc23s->GetBinContent(1) ) ;

//////////////////////////////////////////////////////////////////////////////////

	fillgraph(*hc2s, *g_c2s, "2c");
	fillgraph(*hc3s, *g_c3s, "3c");
	fillgraph(*hp2s, *g_p2s, "2p");
	fillgraph(*hp3s, *g_p3s, "3p");

	fillsysgraph(*hc2s_sys, *hc2s, *g_c2s_sys, "2c");
	fillsysgraph(*hc3s_sys, *hc3s, *g_c3s_sys, "3c");
	fillsysgraph(*hp2s_sys, *hp2s, *g_p2s_sys, "2p");
	fillsysgraph(*hp3s_sys, *hp3s, *g_p3s_sys, "3p");

	fillgraph(*hc23s, *g_c23s, "3c");
	fillgraph(*hp23s, *g_p23s, "3p");

	fillsysgraphdr(*hc23s_sys, *hc23s, *g_c23s_sys, "3c");
	fillsysgraphdr(*hp23s_sys, *hp23s, *g_p23s_sys, "3p");
	
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
	// double glb_2serr = hpp_i2s_unc->GetBinContent(1);
	// double glb_3serr = hpp_i3s_unc->GetBinContent(1);
	//double glb_23serr = hpp_i23s_unc->GetBinContent(1);
	double glb_errMB_PP = 0;
	glb_errMB_PP =quadsum(0.019, 0.);
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

    // b_2serr->SetX1(380);
    // b_2serr->SetX2(400);
    // b_2serr->SetY1(1 - fabs(glb_2serr));
    // b_2serr->SetY2(1 + fabs(glb_2serr));
    // b_2serr->SetFillColorAlpha(kAzure-3, 0.8);
    // b_2serr->SetLineWidth(1);

    // b_3serr->SetX1(400);
    // b_3serr->SetX2(420);
    // b_3serr->SetY1(1 - glb_3serr);
    // b_3serr->SetY2(1 + glb_3serr);
    // b_3serr->SetFillColorAlpha(kTeal+5, 0.8);
    // b_3serr->SetLineWidth(1);

	b_pterr->SetX1(28);
	b_pterr->SetX2(30);
	b_pterr->SetY1(1 - glb_errpt);
	b_pterr->SetY2(1 + glb_errpt);
	b_pterr->SetFillColorAlpha(12, 0.8);
	b_pterr->SetLineWidth(2);
	b_pterr->SetLineColor(kGray+2);
	dbg();

////////////////////Data Serialize to text/////////////////////////////////////////////
	int centup2[] = {90, 70, 60, 50, 40 ,30 ,20, 10, 5};
	int centdo2[] = {70, 60, 50, 40, 30, 20, 10, 5, 0};
	int centup3[] = {90, 70, 50, 30};
	int centdo3[] = {70, 50, 30, 0};

	int ptup2[] = {3, 6, 9, 15, 30};
	int ptdo2[] = {0, 3, 6, 9, 15};
	int ptup3[] = {4, 9, 15, 30};
	int ptdo3[] = {0, 4, 9, 15};
//	auto fillpoints = [&] (ofstream& fs, TGraphAsymmErrors* g, TGraphAsymmErrors* g_sys, string tag, string outputform = "yaml", int mode = 0) {
//		auto xs = g_sys->GetX();
//		auto ys = g->GetY();
//		auto exls = g_sys->GetEXlow();
//		auto exhs = g_sys->GetEXhigh();
//		auto eyls = g->GetEYlow();
//		auto eyhs = g->GetEYhigh();
//		auto exlspart = g->GetEXlow();
//		auto exhspart = g->GetEXhigh();
//
//		auto eyls_sys = g_sys->GetEYlow();
//		auto eyhs_sys = g_sys->GetEYhigh();
//
//
//		unsigned long arrSize = g->GetN();
//		//fs<< tag << std::endl;
//		if( strcmp(outputform.c_str(), "yaml")==0){
//			if(mode == 11){
//				fs << "dependent_variables:" << std::endl;
//				fs << "- header: {name: \'$R_{\\rm AA}$\', units: \'\' }" << std::endl;
//				fs << "  qualifiers:" << std::endl;
//				fs << "  - {name: RE, value: \'Pb Pb --> UPSILON(2,3S) < MU+ MU- > X\'}" << std::endl;
//				fs << "  - {name: SQRT(S_NN), value: 5020 GeV}" << std::endl;
//				fs << "  - {name: \'$|y|$\', value: \'$ < 2.4$\' }" << std::endl;
//				fs << "  - {name: \'$p_{T}$\', value: 0 -- 30, units: GeV }" << std::endl;
//				fs << Form("  - {name: GLOBAL UNC. PP MB, value: \'%.1f %%\'}", 100* fabs(glb_errMB_PP)) << std::endl;
//				fs << Form("  - {name: GLOBAL UNC. PP 2S, value: \'%.1f %%\'}", 100* fabs(glb_2serr) ) << std::endl;
//				fs << Form("  - {name: GLOBAL UNC. PP 3S, value: \'%.1f %%\'}", 100* fabs(glb_3serr) ) << std::endl;
//			}
//			if(mode == 12){
//				fs << "dependent_variables:" << std::endl;
//				fs << "- header: {name: \'$R_{\\rm AA}$\', units: \'\' }" << std::endl;
//				fs << "  qualifiers:" << std::endl;
//				fs << "  - {name: RE, value: \'Pb Pb --> UPSILON(2,3S) < MU+ MU- > X\'}" << std::endl;
//				fs << "  - {name: SQRT(S_NN), value: 5020 GeV}" << std::endl;
//				fs << "  - {name: \'$|y|$\', value: \'$ < 2.4$\' }" << std::endl;
//				fs << "  - {name: \'$p_{T}$\', value: 0 -- 30, units: GeV }" << std::endl;
//				fs << Form("  - {name: GLOBAL UNC. PP MB, value: \'%.1f %%\'}", 100 * fabs(glb_errMB_PP)) << std::endl;
//				fs << Form("  - {name: GLOBAL UNC. PP 2S, value: \'%.1f %%\'}", 100 * fabs(glb_2serr) ) << std::endl;
//				fs << Form("  - {name: GLOBAL UNC. PP 3S, value: \'%.1f %%\'}", 100 * fabs(glb_3serr) ) << std::endl;
//			}
//			if(mode == 13){
//				fs << "dependent_variables:" << std::endl;
//				fs << "- header: {name: \'$R_{\\rm AA}$\', units: \'\'}" << std::endl;
//				fs << "  qualifiers:" << std::endl;
//				fs << "  - {name: RE, value: \'Pb Pb --> UPSILON(2,3S) < MU+ MU- > X\'}" << std::endl;
//				fs << "  - {name: SQRT(S_NN), value: 5020 GeV}" << std::endl;
//				fs << "  - {name: \'$|y|$\', value: \'$ < 2.4$\' }" << std::endl;
//				fs << "  - {name: \'CENTRALITY\', value: 0 -- 90, units: \'%\' }" << std::endl;
//				fs << Form("  - {name: GLOBAL UNC., value: \'%.1f %%\'}",  100 * fabs(glb_errpt)) << std::endl;
//			}
//			if(mode == 21){
//				fs << "dependent_variables:" << std::endl;
//				fs << "- header: {name: \'$DR_{\\rm 23}$\', units: \'\'}" << std::endl;
//				fs << "  qualifiers:" << std::endl;
//				fs << "  - {name: RE, value: \'Pb Pb --> UPSILON(2,3S) < MU+ MU- > X\'}" << std::endl;
//				fs << "  - {name: SQRT(S_NN), value: 5020 GeV}" << std::endl;
//				fs << "  - {name: \'$|y|$\', value: \'$ < 2.4$\' }" << std::endl;
//				fs << "  - {name: \'$p_{T}$\', value: 0 -- 30, units: GeV }" << std::endl;
//				fs << Form("  - {name: GLOBAL UNC., value: \'%.1f %%\'}", 100 * fabs(glb_23serr)) << std::endl;
//			}
//			if(mode == 22){
//				fs << "dependent_variables:" << std::endl;
//				fs << "- header: {name: \'$DR_{\\rm 23}$\', units: \'\'}" << std::endl;
//				fs << "  qualifiers:" << std::endl;
//				fs << "  - {name: RE, value: \'Pb Pb --> UPSILON(2,3S) < MU+ MU- > X\'}" << std::endl;
//				fs << "  - {name: SQRT(S_NN), value: 5020 GeV}" << std::endl;
//				fs << "  - {name: \'$|y|$\', value: \'$ < 1.0$\' }" << std::endl;
//				fs << "  - {name: \'$p_{T}$\', value: 0 -- 30, units: GeV }" << std::endl;
//				fs << Form("  - {name: GLOBAL UNC., value: \'%.1f %%\'}", 100* fabs(glb_23serr)) << std::endl;
//			}
//			if(mode == 23){
//				fs << "dependent_variables:" << std::endl;
//				fs << "- header: {name: \'$DR_{\\rm 23}$\', units: \'\'}" << std::endl;
//				fs << "  qualifiers:" << std::endl;
//				fs << "  - {name: RE, value: \'Pb Pb --> UPSILON(2,3S) < MU+ MU- > X\'}" << std::endl;
//				fs << "  - {name: SQRT(S_NN), value: 5020 GeV}" << std::endl;
//				fs << "  - {name: \'$|y|$\', value: \'$ < 2.4$\' }" << std::endl;
//				fs << "  - {name: \'CENTRALITY\', value: 0 -- 90, units: \'%\' }" << std::endl;
//			}
//			fs << "  values:" << std::endl;
//		}
//		for( int idx = 0; idx < arrSize; idx++ ){
//			if( strcmp(outputform.c_str(), "yaml")== 0){
//				if( mode == 11 || mode == 21 || mode == 13 || mode == 23){
//				fs << 
//					Form("  - value: %.3f\n    errors:\n    - {label: stat, symerror: %.3f}\n    - {label: sys, symerror: %.3f}",ys[idx], eyls[idx], eyls_sys[idx]) <<
//					std::endl;
//				}
//			}
//			if( strcmp(outputform.c_str(), "plain")==0){
//				fs<< 
//					Form("%.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f", xs[idx], exls[idx], exhs[idx], ys[idx], eyls[idx], eyhs[idx], eyls_sys[idx], eyhs_sys[idx]) <<
//					std::endl;
//			}
////			fs << Form("X: %.3f, Y: %.3f, eXlow: %.3f, eXhigh: %.3f, eYlow: %.3f, eYhigh: %.3f", xs[idx], ys[idx], exls[idx], exhs[idx], yxls[idx], yxhs[idx]) << std::endl ;
//		}
//				if( mode == 12 || mode == 22){
//				fs << 
//					Form("  - value: %.3f\n    errors:\n    - {label: stat, symerror: %.3f}\n    - {label: sys, symerror: %.3f}",ys[0], eyls[0], eyls_sys[0]) <<
//					std::endl;
//				}
//
//		if( strcmp(outputform.c_str(), "yaml")==0){
//			if(mode == 11 || mode == 12 || mode ==21 || mode == 22){
//				fs << "- header: {name: \'$\\langle N_{\\rm part} \\rangle$\', units: \'\' }" << std::endl;
//				fs << "  values:" << std::endl;
//			}
//		}
//		for( int idx = 0; idx < arrSize; idx++ ){
//			if( strcmp(outputform.c_str(), "yaml")== 0){
//				if( mode == 11 || mode == 21){
//				fs << 
//					Form("  - value: %.3f\n    errors:\n    - symerror: %.3f", xs[idx], exhspart[idx]) <<
//					std::endl;
//				}
//			}
//		}
//		if( mode == 12 || mode == 22){
//		fs << 
//			Form("  - value: %.3f\n    errors:\n    - symerror: %.3f", 126.0, 0.8) <<
//			std::endl;
//		}
//		fs<< std::endl;
//
//		if( strcmp(outputform.c_str(), "yaml")==0){
//			fs << "independent_variables:" << std::endl;
//			if( mode == 11 ){
//			fs << "- header: {name: Centrality, units: \'\' }" << std::endl;
//			}
//			if( mode == 12 ){
//			fs << "- header: {name: Centrality, units: \'\' }" << std::endl;
//			}
//			if( mode == 13 ){
//			fs << "- header: {name: \'p_{\\rm T}\', units: \'GeV\' }" << std::endl;
//			}
//			if( mode == 21 ){
//			fs << "- header: {name: Centrality, units: \'\' }" << std::endl;
//			}
//			if( mode == 22 ){
//			fs << "- header: {name: Centrality, units: \'\' }" << std::endl;
//			}
//			if( mode == 23 ){
//			fs << "- header: {name: \'p_{\\rm T}\', units: \'GeV\' }" << std::endl;
//			}
//			fs << "  values:" << std::endl;
//		}
//		for( int idx = 0; idx < arrSize; idx++ ){
//			if( strcmp(outputform.c_str(), "yaml")==0){
//			if( mode == 11 ){
//				if( tag.find("2S") != std::string::npos){
//				fs <<  Form("  - {high: %d, low: %d}", centup2[idx], centdo2[idx] ) << std::endl;
//				}
//				if( tag.find("3S") != std::string::npos){
//				fs <<  Form("  - {high: %d, low: %d}", centup3[idx], centdo3[idx] ) << std::endl;
//				}
//			}
//			if( mode == 21 ){
//				fs <<  Form("  - {high: %d, low: %d}", centup3[idx], centdo3[idx] ) << std::endl;
//			}
//			if( mode == 13  ){
//				if( tag.find("2S") != std::string::npos){
//					fs <<  Form("  - {high: %d, low: %d}", ptup2[idx], ptdo2[idx] ) << std::endl;
//				}
//				if( tag.find("3S") != std::string::npos){
//					fs <<  Form("  - {high: %d, low: %d}", ptup3[idx], ptdo3[idx] ) << std::endl;
//				}
//			}
//			if( mode == 23 ){
//				fs <<  Form("  - {high: %d, low: %d}", ptup3[idx], ptdo3[idx] ) << std::endl;
//			}
////					Form("  - value: %.3f\n    errors:\n    - asymerror: {minus: %.3f, plus: %.3f}", xs[idx], exls[idx], exhs[idx]) <<
//			}
//		}
//		if( mode == 12|| mode == 22 ){
//			fs <<  Form("  - {high: %d, low: %d}", 90, 0 ) << std::endl;
//		}
//		fs<< std::endl;
//	};
//	ofstream out;
//	out.open("../hepdata/figure_2,_2S_left.yaml");
//	fillpoints(out, g_c2s, g_c2s_sys, "2S centrality nominal", "yaml", 11);
//	out.close();
//	out.open("../hepdata/figure_2,_3S_left.yaml");
//	fillpoints(out, g_c3s, g_c3s_sys, "3S centrality nominal", "yaml", 11);
//	out.close();
//	out.open("../hepdata/figure_2,_2S_center.yaml");
//	fillpoints(out, g_i2s, g_i2s_sys, "2S integrated nominal", "yaml", 12);
//	out.close();
//	out.open("../hepdata/figure_2,_3S_center.yaml");
//	fillpoints(out, g_i3s, g_i3s_sys, "3S integrated nominal", "yaml", 12);
//	out.close();
//	out.open("../hepdata/figure_2,_2S_right.yaml");
//	fillpoints(out, g_p2s, g_p2s_sys, "2S pt nominal", "yaml", 13);
//	out.close();
//	out.open("../hepdata/figure_2,_3S_right.yaml");
//	fillpoints(out, g_p3s, g_p3s_sys, "3S pt nominal", "yaml", 13);
//	out.close();
//	out.open("../hepdata/figure_3,_left.yaml");
//	fillpoints(out, g_c23s,g_c23s_sys,"3S/2S centrality nominal", "yaml", 21);
//	out.close();
//	out.open("../hepdata/figure_3,_center.yaml");
//	fillpoints(out, g_i23s, g_i23s_sys, "3S/2S integrated nominal", "yaml", 22);
//	out.close();
//	out.open("../hepdata/figure_3,_right.yaml");
//	fillpoints(out, g_p23s,g_p23s_sys,"3S/2S pt nominal", "yaml", 23);
//	out.close();
//
//	out.open("HIN-21-007_points_plain.txt");
//	out << "x, x_low, x_high, y, y_stat_low, y_stat_high, y_syst_low, y_syst_high" << std::endl;
//	fillpoints(out, g_c2s, g_c2s_sys, "2S centrality ", "plain");
//	fillpoints(out, g_c3s, g_c3s_sys, "3S centrality ", "plain");
//	fillpoints(out, g_c23s,g_c23s_sys,"3S/2S centrality ", "plain");
//	fillpoints(out, g_p2s, g_p2s_sys, "2S pt ", "plain");
//	fillpoints(out, g_p3s, g_p3s_sys, "3S pt ", "plain");
//	fillpoints(out, g_p23s,g_p23s_sys,"3S/2S pt ", "plain");
//	fillpoints(out, g_i2s, g_i2s_sys, "2S integrated", "plain");
//	fillpoints(out, g_i3s, g_i3s_sys, "3S integrated", "plain");
//	fillpoints(out, g_i23s, g_i23s_sys, "3S/2S integrated", "plain");
//	out.close();

//////////////////////////////////////////////////////////////////////////////////

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

	TLegend* leg_cent = new TLegend(0.53, 0.43, 0.70, 0.67);
	leg_cent->AddEntry(pg_c1s, "#kern[-0.00]{ }#Upsilon(1S) (2015 PbPb/pp)", "pe");
	leg_cent->AddEntry((TObject*)0, "", "");
	leg_cent->AddEntry(g_c2s, "#kern[-0.00]{ }#Upsilon(2S)", "pe");
	leg_cent->AddEntry((TObject*)0, "", "");
	leg_cent->AddEntry(g_c3s, "#kern[-0.00]{ }#Upsilon(3S)", "pe");
	leg_cent->SetBorderSize(0);
	leg_cent->SetTextFont(42);
	leg_cent->SetTextSize(0.04);
	leg_cent->SetFillStyle(0);
	leg_cent->SetColumnSeparation(0.4);
	TLegend* leg_cent_box = new TLegend(0.53, 0.43, 0.70, 0.67);
	leg_cent_box->AddEntry(pg_c1s_sys, "#kern[-0.00]{ }#Upsilon(1S) (2015 PbPb/pp)", "f");
	leg_cent_box->AddEntry((TObject*)0, "", "");
	leg_cent_box->AddEntry(g_c2s_sys, "#kern[-0.00]{ }#Upsilon(2S)", "f");
	leg_cent_box->AddEntry((TObject*)0, "", "");
	leg_cent_box->AddEntry(g_c3s_sys, "#kern[-0.00]{ }#Upsilon(3S)", "f");
	leg_cent_box->SetBorderSize(0);
	leg_cent_box->SetTextFont(42);
	leg_cent_box->SetTextSize(0.04);
	leg_cent_box->SetColumnSeparation(0.4);

	TLegend* leg_pt = new TLegend(0.45, 0.48, 0.62, 0.71);
	leg_pt->AddEntry(pg_p1s, "#kern[-0.00]{ }#Upsilon(1S) (2015 PbPb/pp)", "pe");
	leg_pt->AddEntry((TObject*)0, "", "");
	leg_pt->AddEntry(g_p2s, "#kern[-0.00]{ }#Upsilon(2S)", "pe");
	leg_pt->AddEntry((TObject*)0, "", "");
	leg_pt->AddEntry(g_p3s, "#kern[-0.00]{ }#Upsilon(3S)", "pe");
	leg_pt->SetBorderSize(0);
	leg_pt->SetTextFont(42);
	leg_pt->SetTextSize(0.04);
	leg_pt->SetFillStyle(0);
	TLegend* leg_pt_box = new TLegend(0.45, 0.48, 0.62, 0.71);
	leg_pt_box->AddEntry(pg_p1s_sys, "#kern[-0.00]{ }#Upsilon(1S) (2015 PbPb/pp)", "f");
	leg_pt_box->AddEntry((TObject*)0, "", "");
	leg_pt_box->AddEntry(g_p2s_sys, "#kern[-0.00]{ }#Upsilon(2S)", "f");
	leg_pt_box->AddEntry((TObject*)0, "", "");
	leg_pt_box->AddEntry(g_p3s_sys, "#kern[-0.00]{ }#Upsilon(3S)", "f");
	leg_pt_box->SetBorderSize(0);
	leg_pt_box->SetTextFont(42);
	leg_pt_box->SetTextSize(0.04);
//////////////////////////////////INITIALIZE CANVASES/////////////////////////////////


	std::map<string, TObject*> towrite;
	TCanvas* c1 = new TCanvas("c1","", 1100,900);
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
	p1_L->SetLeftMargin(0.16);
	p1_R->SetLeftMargin(0);
	p2->SetLeftMargin(0.15);
	p2->SetRightMargin(0.03);
	////////READY PADS/////////
	c1->cd();
	p1_L->Draw();
	p1_R->Draw();
	c2->cd();
	p2->Draw();
	////////DRAW GRAPHS AND SO ON////////////
	//CENT CANVAS//
	c1->cd();
	double Rdo = 3e-5;
	double Rup = 3e-1;
	//RAA CENT LEFT//
	p1_L->cd();
	g_c2s->GetYaxis()->SetRangeUser(Rdo,Rup);
	g_c2s->GetYaxis()->SetTitle("B#times(1#lower[0.2]{#kern[0.2]{#scale[1.5]{#it{/}}}}#it{T}_{#kern[-0.2]{AA}})#times d^{2}#font[122]{N}#lower[0.2]{#kern[0.2]{#scale[1.5]{#it{/}}}}d#it{y}d#it{p}_{T} (nb / GeV/#it{c})");
	g_c2s->GetYaxis()->SetTitleOffset(1.65);
	g_c2s->Draw("APE");
	pg_c1s->Draw("PE");
	g_c3s->Draw("PE");
	pg_c1s_sys->Draw("5");
	g_c2s_sys->Draw("5");
	g_c3s_sys->Draw("5");
	TLine* p1_L_line1 = lineone->DrawLine(0, 1, 420, 1);
	TLatex* p1_L_latex1 = tl->DrawLatex( 40, 1e-1,"#it{p}_{T} < 30 GeV/#it{c}");
	TLatex* p1_L_latex2 = tl->DrawLatex( 40, 5e-2, "|#it{y}| < 2.4");
	leg_cent_box->Draw();
	leg_cent->Draw("same");
	b_err->  Draw("L");

	p1_L->Update();
	p1_L->Draw();
	towrite["p1_L"] = p1_L;
	//RAA INT RIGHT//
	p1_R->cd();
	g_i2s->GetXaxis()->SetLimits(0,4);
	g_i2s->GetYaxis()->SetRangeUser(Rdo,Rup);
	g_i2s->Draw("APE");
	pg_i1s->Draw("PE");
	g_i3s->Draw("PE");
	pg_i1s_sys->Draw("5");
	g_i2s_sys->Draw("5");
	g_i3s_sys->Draw("5");
	TLine* p1_R_line1 = lineone->DrawLine(0,1,4,1);
	tl->SetTextSize(0.042* p2scale);
	tl->SetTextAlign(21);
	TLatex* p1_R_latex1 = tl->DrawLatex( 2.0, 1.05e-1, "Cent.");
	TLatex* p1_R_latex2 = tl->DrawLatex( 2.0, 6.5e-2, "0-90%");
	p1_R->Update();
	p1_R->Draw();

	//PT CANVAS//
	c2->cd();
	p2->cd();
	g_p2s->GetYaxis()->SetRangeUser(Rdo,Rup);
	g_p2s->GetYaxis()->SetTitle("B#times(1#lower[0.2]{#kern[0.2]{#scale[1.5]{#it{/}}}}#it{T}_{#kern[-0.2]{AA}})#times d^{2}#font[122]{N}#lower[0.2]{#kern[0.2]{#scale[1.5]{#it{/}}}}d#it{y}d#it{p}_{T} (nb / GeV/#it{c})");
	g_p2s->GetYaxis()->SetTitleOffset(1.5);
	g_p2s->Draw("APE");
	pg_p1s->Draw("PE");
	g_p3s->Draw("PE");
	pg_p1s_sys->Draw("5");
	g_p2s_sys->Draw("5");
	g_p3s_sys->Draw("5");
	TLine* p2_line1 = lineone->DrawLine(0, 1, 30, 1);
	tl->SetTextSize(0.042);
	tl->SetTextAlign(11);
//	TLatex* p2_latex1 = tl->DrawLatex( 2.5, 1.15,"#it{p}_{T} < 30 GeV/#it{c}");
	TLatex* p2_latex2 = tl->DrawLatex( 2.5, 1e-1, "|#it{y}| < 2.4");
	TLatex* p2_latex3 = tl->DrawLatex( 2.5, 5e-2, "Cent. 0-90%");
	leg_pt_box->Draw();
	leg_pt->Draw("same");
	b_pterr->Draw("L");

	p2->Draw();
	towrite["p2"] = p2;
	//LUMIFY PADS AND COMBINE PLOTS//
	c1->cd();
	p1_L->cd();
	CMS_lumi_square(p1_L,2, 33, -1);
	c2->cd();
	p2->cd();
	CMS_lumi_square( p2, 2, 33, -1);
	p1_L->SetLogy();
	p1_R->SetLogy();
	p2->SetLogy();
	c1->Update();
	c1->Modified();
	c2->Update();
	c2->Modified();

	c1->SaveAs(Form("../checkout/tscol/CS_centrality_int_%ld_v3_w1s.pdf", _TS) );
	c2->SaveAs(Form("../checkout/tscol/CS_pt_%ld_v3_w1s.pdf", _TS) );
	TFile* output = new TFile(Form("resultCS_%ld_v3.root", _TS), "recreate");
	TDirectory *Dir_vanila = output->mkdir("vanila_w1s");
	Dir_vanila->cd();
	c1->Write();
	c2->Write();
	
//	c2->cd();
//	p2->cd();
//	leg_pt->SetY1NDC(0.57);
//	leg_pt->SetY2NDC(0.79);
//	p2_latex2->Delete();
//	p2_latex3->Delete();
//	p2_latex2 = tl->DrawLatex( 2.5, 6, "|#it{y}| < 2.4");
//	p2_latex3 = tl->DrawLatex( 2.5,12, "Cent. 0-90%");
//	leg_pt_box->Draw();
//	leg_pt->Draw();
//	g_p2s->GetYaxis()->SetRangeUser(1e-6, 5e-3);
//	p2->SetLogy(1);
//	// c2->SetLogy(1);
//	c2->Modified();
//	c2->Draw();
//	c2->SaveAs(Form("../checkout/tscol/CS_pt_logy_%ld_v3_w1s.pdf", _TS) );
//	c2->SetLogy(0);
	output->Close();

	output->cd();
};

