#include "../BDT/bininfo.h"

#if defined(BININFO_H)
#include "drawRAAplot.cxx"
#endif
double quadsum(double arg1, double arg2){
	return TMath::Sqrt( arg1*arg1 + arg2*arg2 );
}

void drawRAAplot_sys2()
{
	bool ISPROJSTAT = true;
//  	gStyle->SetErrorX(0.00001);
	gStyle->SetOptStat(kFALSE);
	gStyle->SetOptTitle(kFALSE);
	gStyle->SetEndErrorSize(0);
	TFile* f_sys = TFile::Open(Form("%s/Systematics/total_systematic.root", workdir.Data() ));
	TFile* f_craa = TFile::Open(Form("%s/plots/resultRAA_nS_centrality.root", workdir.Data() ));
	TFile* f_praa = TFile::Open(Form("%s/plots/resultRAA_nS_pt.root", workdir.Data() ));
	TFile* f_syspp = TFile::Open(Form("%s/HIN16023_PP_Systematic.root", hin16023.Data()));
	TFile* f_ypp = TFile::Open(Form("%s/fitresults_upsilon_fixParm1_seed2_DoubleCB_PP_DATA_pt0.0-30.0_y0.0-2.4_muPt4.0.root",hin16023.Data() ));

	TCanvas* c2 = new TCanvas("c2","",1000,700);
	TCanvas* c3 = new TCanvas("c3","",1000,700);
	TCanvas* c4 = new TCanvas("c4","",1000,700);

	TPad *p2_1, *p2_2, *p3_1, *p3_2;
	p2_1 = new TPad("p21", "", 0.00, 0.0,0.83,1);
	p2_1->SetRightMargin(0);
	p2_1->SetBottomMargin(0.12);
	p2_2 = new TPad("p22", "", 0.83, 0.0,1,1);
	p2_2->SetLeftMargin(0);
	p2_2->SetBottomMargin(0.12);
	p3_1 = new TPad("p31", "", 0.00, 0,0.83,1);
	p3_1->SetRightMargin(0);
	p3_2= new TPad("p32", "", 0.83, 0,1,1);
	p3_2->SetLeftMargin(0);
	p2_1->SetTicks();
	p2_2->SetTicks();


	TGraphAsymmErrors* g_y1cent = (TGraphAsymmErrors*) f_craa->Get("RAAcent_1S");

	TH1D* h_y2cent = (TH1D*) f_craa->Get("RAAcent_2S");
	TH1D* h_y3cent = (TH1D*) f_craa->Get("RAAcent_3S");
	TH1D* h_y1int = (TH1D*) f_craa->Get("y1int");
	TH1D* h_y2int = (TH1D*) f_craa->Get("y2int");
	TH1D* h_y3int = (TH1D*) f_craa->Get("y3int");
	TH1D* h_y2pt  = (TH1D*) f_praa->Get("h2pt");
	TH1D* h_y3pt  = (TH1D*) f_praa->Get("h3pt");
	TH1D* h_ppstat = (TH1D*) f_ypp->Get("fitResults");
	TH1D* hp_y2int = (TH1D*) f_syspp->Get("hIntPP_2S");
	TH1D* hp_y3int = (TH1D*) f_syspp->Get("hIntPP_3S"); 
	TH1D* hp_y2pt  = (TH1D*) f_syspp->Get("hptPP_2S"); 
	TH1D* hp_y3pt  = (TH1D*) f_syspp->Get("hptPP_3S"); 

	TH1D* he_y2cent = (TH1D*) f_sys->Get("syst_comp/hsys_tot_c2S");
	TH1D* he_y3cent = (TH1D*) f_sys->Get("syst_comp/hsys_tot_c3S");
	TH1D* he_y2pt =   (TH1D*) f_sys->Get("syst_comp/hsys_tot_p2S");
	TH1D* he_y3pt =   (TH1D*) f_sys->Get("syst_comp/hsys_tot_p3S");

	TGraphAsymmErrors *g_y1int, *g_y2int, *g_y3int, *g_y2pt, *g_y3pt, *ge_y2cent, *ge_y3cent, *ge_y2int, *ge_y3int, *ge_y2pt, *ge_y3pt;
	double markersize = 1.4;

	g_y1int = new TGraphAsymmErrors();

	g_y2int = new TGraphAsymmErrors();
	g_y3int = new TGraphAsymmErrors();
	g_y1int->SetPoint(0, 1, h_y1int->GetBinContent(1));
	g_y2int->SetPoint(0, 2, h_y2int->GetBinContent(2));
	g_y3int->SetPoint(0, 3, h_y3int->GetBinContent(3));
	g_y1int->SetPointEYlow(0, h_y1int->GetBinError(1) );
	g_y1int->SetPointEYhigh(0, h_y1int->GetBinError(1) );
	g_y2int->SetPointEYlow(0, h_y2int->GetBinError(2) );
	g_y2int->SetPointEYhigh(0, h_y2int->GetBinError(2) );
	g_y3int->SetPointEYlow(0, h_y3int->GetBinError(3) );
	g_y3int->SetPointEYhigh(0, h_y3int->GetBinError(3) );


	g_y2pt = new TGraphAsymmErrors();
	g_y3pt = new TGraphAsymmErrors();

	
	g_y2int->SetPointEXlow( 0, 0);
	g_y2int->SetPointEXhigh(0, 0);
	g_y3int->SetPointEXlow( 0, 0);
	g_y3int->SetPointEXhigh(0, 0);
	g_y2pt->SetPoint(0, 2, h_y2pt->GetBinContent(1));
	g_y2pt->SetPoint(0, 2, h_y2pt->GetBinContent(1));
	g_y2pt->SetPoint(1, 6.5, h_y2pt->GetBinContent(2));
	g_y2pt->SetPoint(1, 6.5, h_y2pt->GetBinContent(2));
	g_y2pt->SetPoint(2, 19.5, h_y2pt->GetBinContent(3));
	g_y2pt->SetPoint(2, 19.5, h_y2pt->GetBinContent(3));
	g_y2pt->SetPointEXlow(0, 0);
	g_y2pt->SetPointEXhigh(0, 0);
	g_y2pt->SetPointEXlow( 1, 0);
	g_y2pt->SetPointEXhigh(1, 0);
	g_y2pt->SetPointEXlow( 2, 0);
	g_y2pt->SetPointEXhigh(2, 0);
	g_y2pt->SetPointEYlow (0, h_y2pt->GetBinError(1));
	g_y2pt->SetPointEYhigh(0, h_y2pt->GetBinError(1));
	g_y2pt->SetPointEYlow (1, h_y2pt->GetBinError(2));
	g_y2pt->SetPointEYhigh(1, h_y2pt->GetBinError(2));
	g_y2pt->SetPointEYlow (2, h_y2pt->GetBinError(3));
	g_y2pt->SetPointEYhigh(2, h_y2pt->GetBinError(3));

	g_y3pt->SetPoint(0, 3, h_y3pt->GetBinContent(1));
	g_y3pt->SetPoint(0, 3, h_y3pt->GetBinContent(1));
	g_y3pt->SetPoint(1, 18, h_y3pt->GetBinContent(2));
	g_y3pt->SetPoint(1, 18, h_y3pt->GetBinContent(2));
	g_y3pt->SetPointEXlow( 0, 0);
	g_y3pt->SetPointEXhigh(0, 0);
	g_y3pt->SetPointEXlow( 1, 0);
	g_y3pt->SetPointEXhigh(1, 0);
	g_y3pt->SetPointEYlow (0, h_y3pt->GetBinError(1));
	g_y3pt->SetPointEYhigh(0, h_y3pt->GetBinError(1));
	g_y3pt->SetPointEYlow (1, h_y3pt->GetBinError(2));
	g_y3pt->SetPointEYhigh(1, h_y3pt->GetBinError(2));

	ge_y2cent = new TGraphAsymmErrors();
	ge_y3cent = new TGraphAsymmErrors();
	ge_y2int  = new TGraphAsymmErrors();
	ge_y3int  = new TGraphAsymmErrors();
	ge_y2pt   = new TGraphAsymmErrors();
	ge_y3pt   = new TGraphAsymmErrors();

	TGraphAsymmErrors* tga[6] = {ge_y2cent, ge_y3cent, ge_y2int, ge_y3int, ge_y2pt, ge_y3pt};
	std::vector<int> x;
	std::vector<double> v_err;

	int hnbins = 0;
	int count_h = 0;
	hnbins = h_y2cent->GetNbinsX();
	for(int idx = 0 ;idx < hnbins; idx++){
		if(h_y2cent->GetBinContent(idx+1) !=0) {
			double	cont_x, cont_y;
			cont_x = h_y2cent->GetBinCenter(idx+1);
			cont_y = h_y2cent->GetBinContent(idx+1);
			ge_y2cent->SetPoint(count_h, cont_x, cont_y );
			count_h++;
		}
	}

	hnbins = h_y3cent->GetNbinsX();
	std::cout << "3S cent bins : " << hnbins << std::endl;
	count_h = 0;
	for(int idx = 0 ;idx < hnbins; idx++){
		if(h_y3cent->GetBinContent(idx+1) !=0) {
			ge_y3cent->SetPoint(count_h, h_y3cent->GetBinCenter(idx+1), h_y3cent->GetBinContent(idx+1) );
			count_h++;
		}
	}
	count_h=0;
	hnbins = h_y2pt->GetNbinsX();
	for(int idx = 0 ;idx < hnbins; idx++){
		if(h_y2pt->GetBinContent(idx+1) !=0) {
		  std::cout << "POINT CENTER PT BIN : " << h_y2pt->GetBinCenter(idx+1) << std::endl;
			ge_y2pt->SetPoint(count_h, h_y2pt->GetBinCenter(idx+1), h_y2pt->GetBinContent(idx+1) );
			count_h++;
		}
	}

	hnbins = h_y3pt->GetNbinsX();
	count_h = 0;
	for(int idx = 0 ;idx < hnbins; idx++){
		if(h_y3pt->GetBinContent(idx+1) !=0) {
			ge_y3pt->SetPoint(count_h, h_y3pt->GetBinCenter(idx+1), h_y3pt->GetBinContent(idx+1) );
			count_h++;
		}
	}
	ge_y2int->SetPoint(0, 2, h_y2int->GetBinContent(2));
	ge_y3int->SetPoint(0, 3, h_y3int->GetBinContent(3));

	ge_y2int->SetPointEXhigh(0,0.3);
	ge_y2int->SetPointEXlow(0,0.3);
	ge_y3int->SetPointEXhigh(0,0.3);
	ge_y3int->SetPointEXlow(0,0.3);

	std::vector<ana_bins> ac2  = ana_bm["2c"];
	std::vector<ana_bins> ac3  = ana_bm["3c"];
	std::vector<ana_bins> ap2  = ana_bm["2p"];
	std::vector<ana_bins> ap3  = ana_bm["3p"];
	for(int i = 0; i<9; i++){
	  	double err_frac = he_y2cent->GetBinContent(9-i);
		double taaerr_frac;
		std::pair<double,double> taa = glp::Taa[{ac2[i].centl, ac2[i].centh}];
		taaerr_frac = taa.second/taa.first;
		err_frac = quadsum(err_frac, taaerr_frac);
		double raa = ge_y2cent->GetPointY(i);
		int interval = 7;
		if(i == 1) interval = 3;
		ge_y2cent->SetPointError(i, interval, interval, raa*err_frac, raa*err_frac);
		std::cout <<"RAA: "<< raa << std::endl;
	}
	for(int i = 0; i<3; i++){
	  	double err_frac = he_y3cent->GetBinContent(3-i);
		double raa = ge_y3cent->GetPointY(i);
		double taaerr_frac;
		std::pair<double,double> taa = glp::Taa[{ac2[i].centl, ac2[i].centh}];
		taaerr_frac = taa.second/taa.first;
		err_frac = quadsum(err_frac, taaerr_frac);
		int interval = 7;
		if(i == 0) interval  =3;
		ge_y3cent->SetPointError(i, interval, interval, raa*err_frac, raa*err_frac);
	}
	for(int i = 0; i<1; i++){
	  	double err_frac = he_y2cent->GetBinContent(10);
		double taaerr_frac;
		std::pair<double,double> taa = glp::Taa[{ac2[9].centl, ac2[9].centh}];
		taaerr_frac = taa.second/taa.first;
		err_frac = quadsum(err_frac, taaerr_frac);
		err_frac = quadsum(err_frac, 0.01261);
		err_frac = quadsum(err_frac, 0.02);
		err_frac = quadsum(err_frac, hp_y2int->GetBinContent(1));
		double raa = ge_y2int->GetPointY(i);
		ge_y2int->SetPointError(i, 0.2, 0.2, raa*err_frac, raa*err_frac);
		std::cout <<Form("RAA of integrated 2S: %.3f \\pm %.3f \\pm %.3f", raa,h_y2int->GetBinError(2), raa*err_frac)  << std::endl;
	}
	for(int i = 0; i<1; i++){
	  	double err_frac = he_y3cent->GetBinContent(4);
		double taaerr_frac;
		std::pair<double,double> taa = glp::Taa[{ac3[3].centl, ac3[3].centh}];
		taaerr_frac = taa.second/taa.first;
		err_frac = quadsum(err_frac, taaerr_frac);
		err_frac = quadsum(err_frac, 0.01261);
		err_frac = quadsum(err_frac, 0.02);
		err_frac = quadsum(err_frac, hp_y3int->GetBinContent(1));
		double raa = ge_y3int->GetPointY(i);
		ge_y3int->SetPointError(i, 0.2, 0.2, raa*err_frac, raa*err_frac);
		std::cout <<Form("RAA of integrated 3S: %.3f \\pm %.3f \\pm %.3f", raa,h_y3int->GetBinError(3), raa*err_frac)  << std::endl;
	}
	for(int i = 0; i<3; i++){
	  	double err_frac = he_y2pt->GetBinContent(i+1);
		double pp_err = hp_y2pt->GetBinContent(i+1);;
		err_frac = quadsum(err_frac, pp_err);
		double raa = ge_y2pt->GetPointY(i);
		double bin_center = h_y2pt->GetBinCenter(i+1);
		double bin_width = h_y2pt->GetBinWidth(i+1)/2;
		std::cout << "PT BIN BIN RANGE : " << bin_center - bin_width << ", " << bin_center + bin_width << std::endl;
		ge_y2pt->SetPointError(i,  bin_width, bin_width, raa*err_frac, raa*err_frac);
	}
	for(int i = 0; i<2; i++){
	  	double err_frac = he_y3pt->GetBinContent(i+1);
		double pp_err = hp_y3pt->GetBinContent(i+1);;
		err_frac = quadsum(err_frac, pp_err);
		double raa = ge_y3pt->GetPointY(i);
		double bin_center = h_y3pt->GetBinCenter(i+1);
		double bin_width = h_y3pt->GetBinWidth(i+1)/2;
		ge_y3pt->SetPointError(i,  bin_width, bin_width, raa*err_frac, raa*err_frac);
	}

//	ge_y2cent ->SetFillStyle(1001);
//	ge_y3cent ->SetFillStyle(1001);
//	ge_y2int  ->SetFillStyle(1001);
//	ge_y3int  ->SetFillStyle(1001);
//	ge_y2pt   ->SetFillStyle(1001);
//	ge_y3pt   ->SetFillStyle(1001);

	g_y1int->GetXaxis()->SetLimits(0,4);
	g_y1int->GetXaxis()->SetRangeUser(0,4);
	g_y1int->GetXaxis()->SetTickSize(0);
	g_y1int->GetXaxis()->SetTitle("int.");
	g_y1int->GetXaxis()->SetTitleSize(g_y1int->GetXaxis()->GetTitleSize()*(0.83/0.17));
	g_y1int->GetXaxis()->CenterTitle(true);
	g_y1int->GetXaxis()->SetLabelSize(0);
	g_y1int ->GetYaxis()->SetRangeUser(0,1.2);
	g_y1int  ->SetLineColor(kRed+3);
	g_y1int  ->SetMarkerColor(kRed+3);
	g_y1int  ->SetMarkerStyle(kFullCircle);
	g_y1int  ->SetMarkerSize(markersize);
	g_y2int  ->SetLineColor(kBlue);
	g_y2int  ->SetMarkerColor(kBlue);
	g_y2int  ->SetMarkerStyle(kFullSquare);
	g_y2int  ->SetMarkerSize(markersize);
	g_y3int  ->SetLineColor(kGreen+2);
	g_y3int  ->SetMarkerColor(kGreen+2);
	g_y3int  ->SetMarkerStyle(kFullSquare);
	g_y3int  ->SetMarkerSize(markersize);
	g_y1cent  ->SetMarkerSize(markersize);

	g_y2pt->GetXaxis()->SetLimits(0,30);
	g_y2pt->GetXaxis()->SetRangeUser(0,30);

	g_y1int ->GetYaxis()->SetRangeUser(0,1.3);
	g_y2int ->GetYaxis()->SetRangeUser(0,1.3);
	g_y3int ->GetYaxis()->SetRangeUser(0,1.3);
	g_y2pt ->GetYaxis()->SetRangeUser(0,1.3);
	g_y3pt ->GetYaxis()->SetRangeUser(0,1.3);
	

	ge_y2cent ->GetYaxis()->SetRangeUser(0,1.3);
	ge_y3cent ->GetYaxis()->SetRangeUser(0,1.3);
	ge_y2int  ->GetYaxis()->SetRangeUser(0,1.3);
	ge_y3int  ->GetYaxis()->SetRangeUser(0,1.3);
	ge_y2pt   ->GetYaxis()->SetRangeUser(0,1.3);
	ge_y3pt   ->GetYaxis()->SetRangeUser(0,1.3);
	ge_y2pt   ->GetXaxis()->SetLimits(0,30);
	ge_y3pt   ->GetXaxis()->SetLimits(0,30);
	ge_y2pt   ->GetXaxis()->SetRangeUser(0,30);
	ge_y3pt   ->GetXaxis()->SetRangeUser(0,30);


	g_y2pt   ->SetMarkerColor(kBlue);
	g_y3pt   ->SetLineColor(kGreen+2);
	g_y2pt   ->SetLineColor(kBlue);
	g_y3pt   ->SetMarkerColor(kGreen+2);
	g_y2pt   ->SetMarkerStyle(kFullSquare);
	g_y3pt   ->SetMarkerStyle(kFullSquare);
	g_y2pt   ->SetMarkerSize(markersize);
	g_y3pt   ->SetMarkerSize(markersize);

	ge_y2cent ->SetLineColor(kBlue);
	ge_y3cent ->SetLineColor(kGreen+3);

	ge_y2int  ->SetLineColor(kBlue);
	ge_y3int  ->SetLineColor(kGreen+3);
	ge_y2pt   ->SetLineColor(kBlue);
	ge_y3pt   ->SetLineColor(kGreen+3);
	gStyle->SetEndErrorSize(0);

	ge_y2cent ->SetFillColorAlpha(kAzure-3	 	,0.25);
	ge_y3cent ->SetFillColorAlpha(kTeal+5		,0.25);
	ge_y2int  ->SetFillColorAlpha(kAzure-3		,0.25);
	ge_y3int  ->SetFillColorAlpha(kTeal+5		,0.25);
	ge_y2pt   ->SetFillColorAlpha(kAzure-3		,0.25);
	ge_y3pt   ->SetFillColorAlpha(kTeal+5		,0.25);

	TLegend* leg = new TLegend(0.55, 0.45, 0.85, 0.70);
	leg->AddEntry(g_y1cent, "#Upsilon(1S) PLB 790 (2019) 270", "pl");
	leg->AddEntry(h_y2cent, "#Upsilon(2S)", "pl");
	leg->AddEntry(h_y3cent, "#Upsilon(3S)", "pl");
	//leg->SetTextAlign(31);
	leg->SetTextSize(0.04);
	TLegendEntry *eleg = leg->GetEntry();
	eleg->SetTextSize(eleg->GetTextSize()* 0.6);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.035);
	TLegend* leg2 = new TLegend(0.65, 0.4, 0.85, 0.7);
	leg2->AddEntry(h_y3cent, "#Upsilon(3S)", "pl");
	leg2->SetBorderSize(0);
	leg2->SetTextFont(42);
	leg2->SetTextSize(0.04);


	c2->cd();
	p2_1->Draw();
	p2_2->Draw();
	TLine* lineone = new TLine();
	lineone->SetLineStyle(kDashed);
	lineone->SetLineWidth(1);


	p2_1->cd();

	g_y1cent->SetTitle("");
	h_y2cent->SetMarkerStyle(kFullSquare);
	h_y3cent->SetMarkerStyle(kFullSquare);
	h_y2cent->SetMarkerSize(markersize);
	h_y3cent->SetMarkerSize(markersize);

	h_y2cent->SetStats(0);
	h_y2cent->SetTitle("");
	h_y2cent->Draw("");
	h_y3cent->Draw("same");
	g_y1cent->Draw("PE");

	ge_y2cent->Draw("5");
	ge_y3cent->Draw("5");

	TLatex* tl = new TLatex();
	tl->SetTextSize(0.037);
	tl->SetTextFont(42);
	tl->DrawLatex( 40, 1.15,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 40, 1.06, "|y| < 2.4");
//	tl->DrawLatex( 140, 1.15, "p^{#mu}_{T} > 3.5 GeV/c");
	lineone->DrawLine(0, 1.0, 420, 1.0);
	leg->Draw();

	TBox* b_yerr = new TBox();
	TBox* b_y2err = new TBox();
	TBox* b_y3err = new TBox();
	double glb_err2s = 0;
	double glb_err3s = 0;
	double glb_errMB_PP = 0;
	double pp_stat2s = h_ppstat->GetBinError(2) / h_ppstat->GetBinContent(2);
	double pp_stat3s = h_ppstat->GetBinError(3) / h_ppstat->GetBinContent(3);
	glb_errMB_PP = quadsum(glb_errMB_PP, 0.01261);
	glb_errMB_PP = quadsum(glb_errMB_PP, 0.02);
	glb_err2s = quadsum(glb_err2s, hp_y2int->GetBinContent(1) );
	glb_err3s = quadsum(glb_err3s, hp_y3int->GetBinContent(1) );
	glb_err2s = quadsum(glb_err2s, pp_stat2s );
	glb_err3s = quadsum(glb_err3s, pp_stat3s );

	b_yerr->SetX1(360);
	b_yerr->SetX2(380);
	b_yerr->SetY1(1 - fabs(glb_errMB_PP));
	b_yerr->SetY2(1 + fabs(glb_errMB_PP));
	b_yerr->SetFillColorAlpha(12, 0.8);
	b_yerr->SetLineWidth(1);
	b_y2err->SetX1(380);
	b_y2err->SetX2(400);
	b_y2err->SetY1(1 - fabs(glb_err2s));
	b_y2err->SetY2(1 + fabs(glb_err2s));
	std::cout <<"Global Error 2S " << b_y2err->GetY1() << std::endl;
	b_y2err->SetFillColorAlpha(kAzure-3, 0.8);
	b_y2err->SetLineWidth(1);
//	b_y2err->SetLineColor(kBlack);


	b_y3err->SetX1(400);
	b_y3err->SetX2(420);
	b_y3err->SetY1(1 - glb_err3s);
	b_y3err->SetY2(1 + glb_err3s);
	b_y3err->SetFillColorAlpha(kTeal+5, 0.8);
	b_y3err->SetLineWidth(1);
//	b_y3err->SetLineColor();
	b_yerr->Draw("L");
	b_y3err->Draw("L");
	b_y2err->Draw("L");

	p2_1->Update();
	p2_1->Draw();

	p2_2->cd();
	g_y1int->GetYaxis()->SetTickSize(g_y1int->GetYaxis()->GetTickLength() * (0.87/0.13));
	g_y1int->GetXaxis()->SetTitle("0-90 %");
	g_y1int->GetXaxis()->CenterTitle(kTRUE);
	g_y1int->GetXaxis()->SetTitleSize(g_y1int->GetXaxis()->GetTitleSize() * (0.87/0.13) );
	g_y1int->Draw("APE");
	g_y2int->Draw("PE");
	g_y3int->Draw("PE");
	ge_y2int->Draw("5");
	ge_y3int->Draw("5");
	lineone->DrawLine(0, 1, 4, 1);
	tl->SetTextSize(0.027*(0.83/0.17));
	tl->SetTextAlign(21);
	tl->DrawLatex( 2, 1.02, "Cent.");
	tl->DrawLatex( 2, 0.94, "0-90 %");


	p2_2->Update();
	p2_2->Draw();
	c2->cd();

	c2->Modified();
	c2->Update();

	c4->cd();
	ge_y2cent->Draw("a5");
//	ge_y3cent->Draw("2");
	c4->Update();
	c4->Draw();
	c4->Modified();


	c3->cd();
	tl->SetTextAlign(11);
	tl->SetTextSize(0.04);
	tl->SetTextFont(42);
//	tl->SetNDC();
//	gStyle->SetErrorX(0.);
	
	TLegend* legx = new TLegend(0.65, 0.4, 0.85, 0.7);
	lineone->SetLineStyle(kDashed);
	lineone->DrawLineNDC(0,0.5,1,0.5);
	legx->AddEntry(g_y2pt, "#Upsilon(2S)", "pl");
	legx->AddEntry(g_y3pt, "#Upsilon(3S)", "pl");
	legx->SetBorderSize(0);
	legx->SetTextFont(42);
	legx->SetTextSize(0.04);

	
	gStyle->SetEndErrorSize(0);
	g_y2pt->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	g_y2pt->GetYaxis()->SetTitle("R_{AA}");
	g_y2pt->GetXaxis()->SetTitleSize(0.05);
	g_y2pt->GetYaxis()->SetTitleSize(0.05);
	g_y2pt->GetXaxis()->SetTitleOffset(0.9);
	g_y2pt->GetYaxis()->SetTitleOffset(0.9);
	g_y2pt->GetXaxis()->CenterTitle(true);
	g_y2pt->GetYaxis()->CenterTitle(true);
	g_y2pt->Draw("APE");
	g_y3pt->Draw("PE");
	ge_y3pt->Draw("5");
	ge_y2pt->Draw("5");

	legx->Draw();
	tl->DrawLatex( 2.5, 1.15,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 10, 1.15, "|y| < 2.4");
//	tl->DrawLatex( 10,1.15, "p^{#mu}_{T} > 3.5 GeV/c");
	tl->DrawLatex( 2.5,1.06, "Cent. 0-90 %");

	lineone->DrawLine(0, 1.0, 30, 1.0);
	double glb_errpt = 0;
	double taaint_err = glp::Taa[{0, 90}].second/ glp::Taa[{0, 90}].first;
	glb_errpt = quadsum(glb_errpt, 0.01261);
	glb_errpt = quadsum(glb_errpt, 0.02);
	glb_errpt = quadsum(glb_errpt, taaint_err );
	TBox* b_ynerr = new TBox();
	b_ynerr->SetX1(0);
	b_ynerr->SetX2(2);
	b_ynerr->SetY1(1 - glb_errpt);
	b_ynerr->SetY2(1 + glb_errpt);
	b_ynerr->SetFillColorAlpha(12, 0.8);
	b_ynerr->SetLineWidth(1);
	b_ynerr->SetLineColor(kBlack);
	b_ynerr->Draw("L");


	c3->Modified();
	c3->Update();


	c2->cd();
	p2_1->cd();
	CMS_lumi_square(p2_1, 101, 33);
	c3->cd();
	CMS_lumi_square(c3, 101, 33);

	TFile* output = new TFile("resultRAA_nS_centrality_withSystematics2.root", "recreate");
	output->cd();
	c2->SaveAs("../checkout/RAA_centrality_int.pdf");
	c3->SaveAs("../checkout/RAA_pt.pdf");
	c2->Write();
	c3->Write();
	c4->Write();
	output->Close();

}
