
void analysis_plots_combine_func_w1s_theory2_2reg(TFile* hf, TFile* hsys, TFile* ppsys, TFile* hdff, TFile* hdfsys, TFile* ppdfsys)
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
		*pg_p2s, *pg_p2s_sys
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
	g_p2s->SetName("g_p2s"); g_p2s_sys->SetName("g_c2s_sys");
	g_c3s->SetName("g_c3s"); g_c3s_sys->SetName("g_p3s_sys");
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
	int_sys_2s =  quadsum( mb_unc, quadsum( pp_sys, quadsum(pp_lum, quadsum(int_pp_sys_2s, int_sys_2s) ) ) );
	int_sys_3s =  quadsum( mb_unc, quadsum( pp_sys, quadsum(pp_lum, quadsum(int_pp_sys_3s, int_sys_3s) ) ) );
	g_i2s_sys->AddPoint(2, val_2s) ;
	g_i2s_sys->SetPointError(0, int_sys_width, int_sys_width, val_2s *int_sys_2s, val_2s * int_sys_2s ) ;
	g_i3s_sys->AddPoint(3, val_3s) ;
	g_i3s_sys->SetPointError(0, int_sys_width, int_sys_width, val_3s *int_sys_3s, val_3s * int_sys_3s ) ;

	g_i23s->AddPoint(2.5, hc23s->GetBinContent(1)) ;
	g_i23s->SetPointError(0, 0,0, hc23s->GetBinError(1), hc23s->GetBinError(1) ) ;
	double int_sys_width_dr = 0.45;
	double int_pp_sys_dr = hpp_i23s_sys->GetBinContent(1);
	g_i23s_sys->AddPoint(2.5, hc23s->GetBinContent(1)) ;
	g_i23s_sys->SetPointError(0, int_sys_width_dr, int_sys_width_dr, hc23s_sys->GetBinContent(1) * quadsum( int_pp_sys_dr, hc23s->GetBinContent(1)), hc23s_sys->GetBinContent(1) * quadsum( int_pp_sys_dr, hc23s->GetBinContent(1)) ) ;

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
	double glb_2serr = hpp_i2s_unc->GetBinContent(1);
	double glb_3serr = hpp_i3s_unc->GetBinContent(1);
	double glb_errMB_PP = 0;
	glb_errMB_PP =quadsum(0.019, 0.01261);
//	glb_errMB_PP =quadsum(pp_lum, mb_unc);

	double glb_errpt = 0;
	double taaint_err = glp::Taa[{0, 90}].second/ glp::Taa[{0, 90}].first;
	glb_errpt = quadsum( 0.01261, quadsum(taaint_err, 0.019));

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

	TLegend* leg_cent = new TLegend(0.38, 0.48, 0.7, 0.70);
	leg_cent->AddEntry(pg_c1s, "#kern[-0.00]{ }#Upsilon(1S) (2015 PbPb/pp)", "pe");
	leg_cent->AddEntry((TObject*)0, "", "");
	leg_cent->AddEntry(g_c2s, "#kern[-0.00]{ }#Upsilon(2S)", "pe");
	leg_cent->AddEntry((TObject*)0, "", "");
	leg_cent->AddEntry(g_c3s, "#kern[-0.00]{ }#Upsilon(3S)", "pe");
	leg_cent->SetBorderSize(0);
	leg_cent->SetTextFont(42);
	leg_cent->SetTextSize(0.03);
	leg_cent->SetFillStyle(0);
	leg_cent->SetColumnSeparation(0.4);
	TLegend* leg_cent_box = new TLegend(0.38, 0.48, 0.7, 0.70);
	leg_cent_box->AddEntry(pg_c1s_sys, "#kern[-0.00]{ }#Upsilon(1S) (2015 PbPb/pp)", "f");
	leg_cent_box->AddEntry((TObject*)0, "", "");
	leg_cent_box->AddEntry(g_c2s_sys, "#kern[-0.00]{ }#Upsilon(2S)", "f");
	leg_cent_box->AddEntry((TObject*)0, "", "");
	leg_cent_box->AddEntry(g_c3s_sys, "#kern[-0.00]{ }#Upsilon(3S)", "f");
	leg_cent_box->SetBorderSize(0);
	leg_cent_box->SetTextFont(42);
	leg_cent_box->SetTextSize(0.03);
	leg_cent_box->SetColumnSeparation(0.4);

	TLegend* leg_pt = new TLegend(0.18, 0.47, 0.52, 0.7);
	leg_pt->AddEntry(pg_p1s, "#kern[-0.00]{ }#Upsilon(1S) (2015 PbPb/pp)", "pe");
	leg_pt->AddEntry((TObject*)0, "", "");
	leg_pt->AddEntry(g_p2s, "#kern[-0.00]{ }#Upsilon(2S)", "pe");
	leg_pt->AddEntry((TObject*)0, "", "");
	leg_pt->AddEntry(g_p3s, "#kern[-0.00]{ }#Upsilon(3S)", "pe");
	leg_pt->SetBorderSize(0);
	leg_pt->SetTextFont(42);
	leg_pt->SetTextSize(0.03);
	leg_pt->SetFillStyle(0);
	TLegend* leg_pt_box = new TLegend(0.18, 0.47, 0.52, 0.7);
	leg_pt_box->AddEntry(pg_p1s_sys, "#kern[-0.00]{ }#Upsilon(1S) (2015 PbPb/pp)", "f");
	leg_pt_box->AddEntry((TObject*)0, "", "");
	leg_pt_box->AddEntry(g_p2s_sys, "#kern[-0.00]{ }#Upsilon(2S)", "f");
	leg_pt_box->AddEntry((TObject*)0, "", "");
	leg_pt_box->AddEntry(g_p3s_sys, "#kern[-0.00]{ }#Upsilon(3S)", "f");
	leg_pt_box->SetBorderSize(0);
	leg_pt_box->SetTextFont(42);
	leg_pt_box->SetTextSize(0.03);

	TLegend* leg_cent_theory = new TLegend(0.61, 0.40, 0.90, 0.60);
	leg_cent_theory->SetFillColorAlpha(0,0);
	leg_cent_theory->SetNColumns(2);
	leg_cent_theory->SetColumnSeparation(0.17);
	leg_cent_theory->SetBorderSize(0);
	leg_cent_theory->SetTextFont(42);
	leg_cent_theory->SetTextSize(0.030);

	TLegend* leg_pt_theory = new TLegend(0.54, 0.47, 0.85, 0.7);
	leg_pt_theory->SetNColumns(2);
	leg_pt_theory->SetFillColorAlpha(0,0);

	leg_pt_theory->SetColumnSeparation(0.07);
	leg_pt_theory->SetBorderSize(0);
	leg_pt_theory->SetTextFont(42);
	leg_pt_theory->SetTextSize(0.030);
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
	p1_L->SetLeftMargin(0.13);
	p1_R->SetLeftMargin(0);
	p2->SetLeftMargin(0.12);
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

//	g_c2s->Draw("PE");
	pg_c1s->Draw("PE");
	g_c3s->Draw("PE");
	pg_c1s_sys->Draw("5");
	g_c2s_sys->Draw("5");
	g_c3s_sys->Draw("5");
//    draw_theory_EPPS16(p1_L, leg_cent, kTCent, 2);
//    draw_theory_EPPS16(p1_L, leg_cent, kTCent, 3);
//	leg_cent_theory->AddEntry((TObject*)0, "Total","");
//	leg_cent_theory->AddEntry((TObject*)0, "No recomb.","");
    draw_theory_Transport(p1_L,  leg_cent_theory, kTCent, 1, false, false);
    draw_theory_Transport(p1_L,  leg_cent_theory, kTCent, 1, false, true);
    draw_theory_Transport(p1_L,  leg_cent_theory, kTCent, 2, false, false);
    draw_theory_Transport(p1_L,  leg_cent_theory, kTCent, 2, false, true);
    draw_theory_Transport(p1_L,  leg_cent_theory, kTCent, 3, false, false);
    draw_theory_Transport(p1_L,  leg_cent_theory, kTCent, 3, false, true);
	leg_cent_theory->SetHeader("");
//	leg_cent_theory->SetX1(230);
//	leg_cent_theory->SetX2(230);
//	leg_cent_theory->SetY1(0.43);
//	leg_cent_theory->SetY2(230);
	TLine* p1_L_line1 = lineone->DrawLine(0, 1, 420, 1);
	TLatex* p1_L_latex1 = tl->DrawLatex( 40, 1.15,"#it{p}_{T} < 30 GeV/c");
	TLatex* p1_L_latex2 = tl->DrawLatex( 40, 1.06, "|#it{y}| < 2.4");
	leg_cent_box->Draw();
	leg_cent->Draw();
	leg_cent_theory->Draw();
	TLatex* p1L_legT = new TLatex();
	p1L_legT->SetTextFont(leg_cent_theory->GetTextFont());
	p1L_legT->SetTextSize(leg_cent_theory->GetTextSize());
	p1L_legT->SetTextAlign(11);
	p1L_legT->DrawLatex(240, 0.74, "Total  #lower[-0.8]{#scale[1.2]{#bf{TAMU}}}   No recomb.");
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
	towrite["g_i2s_sys"] = g_i2s_sys;
	towrite["g_i3s_sys"] = g_i3s_sys;
	towrite["g_i3s"] = g_i3s;
	towrite["g_i2s"] = g_i2s;
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

//	g_p2s->Draw("PE");
	pg_p1s->Draw("PE");
	g_p3s->Draw("PE");
	pg_p1s_sys->Draw("5");
	g_p2s_sys->Draw("5");
	g_p3s_sys->Draw("5");
//    draw_theory_EPPS16(p2,leg_pt,  kTPt, 2);
//    draw_theory_EPPS16(p2,leg_pt,  kTPt, 3);
	leg_pt_theory->AddEntry((TObject*)0, "Total","");
	leg_pt_theory->AddEntry((TObject*)0, "No recomb.","");
    draw_theory_Transport(p2, leg_pt_theory, kTPt, 1, false, false);
    draw_theory_Transport(p2, leg_pt_theory, kTPt, 1, false, true);
    draw_theory_Transport(p2, leg_pt_theory, kTPt, 2, false, false);
    draw_theory_Transport(p2, leg_pt_theory, kTPt, 2, false, true);
    draw_theory_Transport(p2, leg_pt_theory, kTPt, 3, false, false);
    draw_theory_Transport(p2, leg_pt_theory, kTPt, 3, false, true);
	TLine* p2_line1 = lineone->DrawLine(0, 1, 30, 1);
	tl->SetTextSize(0.042);
	tl->SetTextAlign(11);
//	TLatex* p2_latex1 = tl->DrawLatex( 2.5, 1.15,"p_{T} < 30 GeV/c");
	TLatex* p2_latex2 = tl->DrawLatex( 2.5, 1.15, "|#it{y}| < 2.4");
	TLatex* p2_latex3 = tl->DrawLatex( 2.5,1.06, "Cent. 0-90%");
	towrite["g_p2s"] = g_p2s;
	towrite["g_p3s"] = g_p3s;
	towrite["g_p3s_sys"] = g_p3s_sys;
	towrite["g_p2s_sys"] = g_p2s_sys;
	towrite["p2_line1"] = p2_line1;
//	towrite["p2_latex1"] = p2_latex1;
	towrite["p2_latex2"] = p2_latex2;
	towrite["p2_latex3"] = p2_latex3;
	towrite["leg_pt"] = leg_pt;
	leg_pt_box->Draw();
	leg_pt->Draw();
	leg_pt_theory->Draw();
	b_pterr->Draw("L");
	towrite["p2_box1"] = b_pterr;

	p2->Draw();
	towrite["p2"] = p2;
	//LUMIFY PADS AND COMBINE PLOTS//
	c1->cd();
	p1_L->cd();
	CMS_lumi_square(p1_L,103, 33, 2);
	c2->cd();
	p2->cd();
	CMS_lumi_square( p2, 103, 33, 2);
	c1->Update();
	c1->Modified();
	c2->Update();
	c2->Modified();
	towrite["c2"] = c2;
	towrite["c1"] = c1;

	c1->SaveAs(Form("../checkout/tscol/RAA_centrality_int_%ld_v3_w1s_theory2_2reg.pdf", _TS) );
	c2->SaveAs(Form("../checkout/tscol/RAA_pt_%ld_v3_w1s_theory2_2reg.pdf", _TS) );

	TFile* output = new TFile(Form("resultRAA_%ld_v3.root", _TS), "recreate");
	TDirectory *Dir_vanila = output->mkdir("vanila_w1s");
	Dir_vanila->cd();
	c1->Write();
	c2->Write();

//	c1->SaveAs(Form("../checkout/tscol/RAA_centrality_int_%ld_v3_w1s_theory2_2reg_logy.pdf", _TS) );
	c2->cd();
	TPad* p3 = new TPad("p3", "", 0., 0., 1., 1.);
	p3->SetBottomMargin(0.12);
	p3->SetTicks();
	p3->SetLeftMargin(0.12);
	p3->SetLogy(true);
	p3->Draw();
	p3->cd();
	leg_pt_theory->Clear();
	leg_pt_theory->SetNColumns(2);
	leg_pt_theory->SetColumnSeparation(0.07);
	g_p2s->GetYaxis()->SetRangeUser(1e-2, 7e+1);
	g_p2s->GetXaxis()->SetLimits(0, 30);
	g_p2s->GetXaxis()->SetRangeUser(0, 30);
	g_p2s->Draw("APE");

//	g_p2s->Draw("PE");
	pg_p1s->Draw("PE");
	g_p3s->Draw("PE");
	pg_p1s_sys->Draw("5");
	g_p2s_sys->Draw("5");
	g_p3s_sys->Draw("5");
//    draw_theory_EPPS16(p2,leg_pt,  kTPt, 2);
//    draw_theory_EPPS16(p2,leg_pt,  kTPt, 3);
//	leg_pt_theory->AddEntry((TObject*) 0, "Total TAMU","");
//	leg_pt_theory->AddEntry((TObject*) 0, "No recomb.","");
    draw_theory_Transport(p3, leg_pt_theory, kTPt, 1, false, false);
    draw_theory_Transport(p3, leg_pt_theory, kTPt, 1, false, true);
    draw_theory_Transport(p3, leg_pt_theory, kTPt, 2, false, false);
    draw_theory_Transport(p3, leg_pt_theory, kTPt, 2, false, true);
    draw_theory_Transport(p3, leg_pt_theory, kTPt, 3, false, false);
    draw_theory_Transport(p3, leg_pt_theory, kTPt, 3, false, true);
	leg_pt_theory->SetHeader("");
	leg_pt_box->SetY1NDC(0.534);
	leg_pt_box->SetY2NDC(0.652);
	leg_pt->SetY1NDC(0.534);
	leg_pt->SetY2NDC(0.652);
	leg_pt_theory->SetY1NDC(0.53);
	leg_pt_theory->SetY2NDC(0.70);
	p2_line1 = lineone->DrawLine(0, 1, 30, 1);
	tl->SetTextSize(0.042);
	tl->SetTextAlign(13);
//	p2_latex1 = tl->DrawLatex( 2.5, 1.15,"p_{T} < 30 GeV/c");
	p2_latex2 = tl->DrawLatex( 20, 47., "|#it{y}| < 2.4");
	p2_latex3 = tl->DrawLatex( 20, 25, "Cent. 0-90%");
	TLatex* p2_legT = new TLatex();
	p2_legT->SetTextFont(leg_pt_theory->GetTextFont());
	p2_legT->SetTextSize(leg_pt_theory->GetTextSize());
	p2_legT->SetTextAlign(11);
	p2_legT->DrawLatex(leg_pt_theory->GetX1()+1.6, 5, "Total  #lower[-0.8]{#scale[1.2]{#bf{TAMU}}}   No recomb.");
	leg_pt_box->Draw();
	leg_pt->Draw();
	leg_pt_theory->Draw();
	b_pterr->Draw("L");
	CMS_lumi_square( p3, 103, 11, 2, false);
	c2->Update();
	c2->Modified();
	c2->SaveAs(Form("../checkout/tscol/RAA_pt_%ld_v3_w1s_theory2_2reg_logy.pdf", _TS) );
//	for(auto item : towrite){
//		item.second->Write();
//	}
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

};
