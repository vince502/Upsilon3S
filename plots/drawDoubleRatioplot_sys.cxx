#include "../BDT/bininfo.h"
#include "drawDoubleRatioplot.cxx"

void drawRAAplot_sys2()
{
//  	gStyle->SetErrorX(0.00001);
	gStyle->SetOptStat(kFALSE);
	gStyle->SetOptTitle(kFALSE);
	gStyle->SetEndErrorSize(0);
	TFile* f_sys = TFile::Open(Form("%s/Systematics/total_systematic_DR.root", workdir.Data() ));
//	TFile* f_craa = TFile::Open(Form("%s/plots/resultRAA_nS_centrality.root", workdir.Data() ));
//	TFile* f_praa = TFile::Open(Form("%s/plots/resultRAA_nS_pt.root", workdir.Data() ));

	TCanvas* c2 = new TCanvas("c2","",1000,700);
	TCanvas* c3 = new TCanvas("c3","",1000,700);
//	TCanvas* c4 = new TCanvas("c4","",1000,700);

	TPad *p2_1, *p2_2, *p3_1, *p3_2;
	p2_1 = new TPad("p21", "", 0.00, 0,0.83,1);
	p2_1->SetRightMargin(0);
	p2_2 = new TPad("p22", "", 0.83, 0,1,1);
	p2_2->SetLeftMargin(0);
	p3_1 = new TPad("p31", "", 0.00, 0,0.83,1);
	p3_1->SetRightMargin(0);
	p3_2= new TPad("p32", "", 0.83, 0,1,1);
	p3_2->SetLeftMargin(0);
	p2_1->SetTicks();
	p2_2->SetTicks();


	TGraphAsymmErrors* g_y1cent = (TGraphAsymmErrors*) f_craa->Get("RAAcent_1S");

	std::pair<TH1D*, TH1D*> drpair = getPbPbDR(0,0);
	TH1D* h_y2cent = (TH1D*) drpair.first;
	TH1D* h_y3cent = (TH1D*) drpair.second;
	TH1D* h_y1int = (TH1D*) f_craa->Get("y1int");
	TH1D* h_y2int = (TH1D*) f_craa->Get("y2int");
	TH1D* h_y3int = (TH1D*) f_craa->Get("y3int");
	TH1D* h_y2pt  = (TH1D*) f_praa->Get("h2pt");
	TH1D* h_y3pt  = (TH1D*) f_praa->Get("h3pt");

	TH1D* he_y2cent = (TH1D*) f_sys->Get("hsys_tot_c2S");
	TH1D* he_y3cent = (TH1D*) f_sys->Get("hsys_tot_c3S");
	TH1D* he_y2pt =   (TH1D*) f_sys->Get("hsys_tot_p2S");
	TH1D* he_y3pt =   (TH1D*) f_sys->Get("hsys_tot_p3S");

	TGraphAsymmErrors *g_y1int, *g_y2int, *g_y3int, *g_y2pt, *g_y3pt, *ge_y2cent, *ge_y3cent, *ge_y2int, *ge_y3int, *ge_y2pt, *ge_y3pt;

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
	g_y3int->SetPointEXlow( 1, 0);
	g_y3int->SetPointEXhigh(1, 0);
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
	g_y3pt->SetPoint(1, 12, h_y3pt->GetBinContent(2));
	g_y3pt->SetPoint(1, 12, h_y3pt->GetBinContent(2));
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


	for(int i = 0; i<9; i++){
	  	double err_frac = he_y2cent->GetBinContent(9-i);
		double raa = ge_y2cent->GetPointY(i);
		int interval = 7;
		if(i == 1) interval = 3;
		ge_y2cent->SetPointError(i, interval, interval, raa*err_frac, raa*err_frac);
		std::cout <<"RAA: "<< raa << std::endl;
	}
	for(int i = 0; i<3; i++){
	  	double err_frac = he_y3cent->GetBinContent(3-i);
		double raa = ge_y3cent->GetPointY(i);
		int interval = 7;
		if(i == 0) interval  =3;
		ge_y3cent->SetPointError(i, interval, interval, raa*err_frac, raa*err_frac);
	}
	for(int i = 0; i<1; i++){
	  	double err_frac = he_y2cent->GetBinContent(10);
		double raa = ge_y2int->GetPointY(i);
		ge_y2int->SetPointError(i, 0.2, 0.2, raa*err_frac, raa*err_frac);
	}
	for(int i = 0; i<1; i++){
	  	double err_frac = he_y3cent->GetBinContent(4);
		double raa = ge_y3int->GetPointY(i);
		ge_y3int->SetPointError(i, 0.2, 0.2, raa*err_frac, raa*err_frac);
	}
	for(int i = 0; i<3; i++){
	  	double err_frac = he_y2pt->GetBinContent(i+1);
		double raa = ge_y2pt->GetPointY(i);
		double bin_center = h_y2pt->GetBinCenter(i+1);
		double bin_width = h_y2pt->GetBinWidth(i+1)/2;
		std::cout << "PT BIN BIN RANGE : " << bin_center - bin_width << ", " << bin_center + bin_width << std::endl;
		ge_y2pt->SetPointError(i,  bin_width, bin_width, raa*err_frac, raa*err_frac);
	}
	for(int i = 0; i<2; i++){
	  	double err_frac = he_y3pt->GetBinContent(i+1);
		double raa = ge_y3pt->GetPointY(i);
		double bin_center = h_y3pt->GetBinCenter(i+1);
		double bin_width = h_y3pt->GetBinWidth(i+1)/2;
		ge_y3pt->SetPointError(i,  bin_width, bin_width, raa*err_frac, raa*err_frac);
	}

	ge_y2cent ->SetFillStyle(3001);
	ge_y3cent ->SetFillStyle(3001);
	ge_y2int  ->SetFillStyle(3001);
	ge_y3int  ->SetFillStyle(3001);
	ge_y2pt   ->SetFillStyle(3001);
	ge_y3pt   ->SetFillStyle(3001);

	g_y1int->GetXaxis()->SetLimits(0,4);
	g_y1int->GetXaxis()->SetRangeUser(0,4);
	g_y1int->GetXaxis()->SetTickSize(0);
	g_y1int->GetXaxis()->SetLabelSize(0);
	g_y1int ->GetYaxis()->SetRangeUser(0,1.2);
	g_y1int  ->SetLineColor(kRed+2);
	g_y1int  ->SetMarkerColor(kRed+2);
	g_y1int  ->SetMarkerStyle(kFullCircle);
	g_y1int  ->SetMarkerSize(1);
	g_y2int  ->SetLineColor(kBlue);
	g_y2int  ->SetMarkerColor(kBlue);
	g_y2int  ->SetMarkerStyle(kCircle);
	g_y2int  ->SetMarkerSize(1);
	g_y3int  ->SetLineColor(kGreen+2);
	g_y3int  ->SetMarkerColor(kGreen+2);
	g_y3int  ->SetMarkerStyle(kCircle);
	g_y3int  ->SetMarkerSize(1);

	g_y2pt->GetXaxis()->SetLimits(0,30);
	g_y2pt->GetXaxis()->SetRangeUser(0,30);

	g_y2int ->GetYaxis()->SetRangeUser(0,1.2);
	g_y3int ->GetYaxis()->SetRangeUser(0,1.2);
	g_y2pt ->GetYaxis()->SetRangeUser(0,1.2);
	g_y3pt ->GetYaxis()->SetRangeUser(0,1.2);
	ge_y2cent ->GetYaxis()->SetRangeUser(0,1.2);
	ge_y3cent ->GetYaxis()->SetRangeUser(0,1.2);
	ge_y2int  ->GetYaxis()->SetRangeUser(0,1.2);
	ge_y3int  ->GetYaxis()->SetRangeUser(0,1.2);
	ge_y2pt   ->GetYaxis()->SetRangeUser(0,1.2);
	ge_y3pt   ->GetYaxis()->SetRangeUser(0,1.2);
	ge_y2pt   ->GetXaxis()->SetLimits(0,30);
	ge_y3pt   ->GetXaxis()->SetLimits(0,30);
	ge_y2pt   ->GetXaxis()->SetRangeUser(0,30);
	ge_y3pt   ->GetXaxis()->SetRangeUser(0,30);

	ge_y2cent ->SetFillColor(kBlue);
	ge_y3cent ->SetFillColor(kGreen+3);
	ge_y2int  ->SetFillColor(kBlue);
	ge_y3int  ->SetFillColor(kGreen+3);
	ge_y2pt   ->SetFillColor(kBlue);
	ge_y3pt   ->SetFillColor(kGreen+3);
	g_y2pt   ->SetMarkerColor(kBlue);
	g_y3pt   ->SetMarkerColor(kGreen+3);
	g_y2pt   ->SetMarkerStyle(kFullSquare);
	g_y3pt   ->SetMarkerStyle(kFullSquare);

	ge_y2cent ->SetLineColor(kBlue);
	ge_y3cent ->SetLineColor(kGreen+3);

	ge_y2int  ->SetLineColor(kBlue);
	ge_y3int  ->SetLineColor(kGreen+3);
	ge_y2pt   ->SetLineColor(kBlue);
	ge_y3pt   ->SetLineColor(kGreen+3);
	gStyle->SetEndErrorSize(0);

	TLegend* leg = new TLegend(0.65, 0.4, 0.85, 0.7);
	leg->AddEntry(g_y1cent, "#varUpsilon(1S) HIN-16-023 (Stat. + Syst.", "pl");
	leg->AddEntry(h_y2cent, "#varUpsilon(2S)", "pl");
	leg->AddEntry(h_y3cent, "#varUpsilon(3S)", "pl");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.04);
	TLegend* leg2 = new TLegend(0.65, 0.4, 0.85, 0.7);
	leg2->AddEntry(h_y3cent, "#varUpsilon(3S)", "pl");
	leg2->SetBorderSize(0);
	leg2->SetTextFont(42);
	leg2->SetTextSize(0.04);


	c2->cd();
	p2_1->Draw();
	p2_2->Draw();

	p2_1->cd();
	TLine* lineone = new TLine();
	lineone->SetLineStyle(kDashed);
	lineone->DrawLineNDC(0, 0.5, 1, 0.5);
	g_y1cent->SetTitle("");

	h_y2cent->SetStats(0);
	h_y2cent->SetTitle("");
	h_y2cent->Draw("");
	h_y3cent->Draw("same");
	g_y1cent->Draw("PE");

	ge_y2cent->Draw("2");
	ge_y3cent->Draw("2");

	TLatex* tl = new TLatex();
	tl->SetTextSize(0.04);
	tl->SetTextFont(42);
	tl->SetNDC();
	tl->DrawLatex( 0.2, 0.8,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 0.2, 0.75, "|y| < 2.4");
	tl->DrawLatex( 0.2, 0.7, "p^{#mu}_{T} > 3.5 GeV/c");
	leg->Draw();
	p2_1->Update();
	p2_1->Draw();

	p2_2->cd();
	g_y1int->Draw("APE");
	g_y2int->Draw("PE");
	g_y3int->Draw("PE");
	ge_y2int->Draw("2");
	ge_y3int->Draw("2");
	p2_2->Update();
	p2_2->Draw();
	c2->Modified();
	c2->Update();

	c4->cd();
	ge_y2cent->Draw("a2");
//	ge_y3cent->Draw("2");
	c4->Update();
	c4->Draw();
	c4->Modified();


	c3->cd();
	tl->SetTextSize(0.04);
	tl->SetTextFont(42);
	tl->SetNDC();
//	gStyle->SetErrorX(0.);
	
	TLegend* legx = new TLegend(0.65, 0.4, 0.85, 0.7);
	lineone->SetLineStyle(kDashed);
	lineone->DrawLineNDC(0,0.5,1,0.5);
	legx->AddEntry(h_y2pt, "#varUpsilon(2S)", "pl");
	legx->AddEntry(h_y3pt, "#varUpsilon(3S)", "pl");
	legx->SetBorderSize(0);
	legx->SetTextFont(42);
	legx->SetTextSize(0.04);

	
	gStyle->SetEndErrorSize(0);
	g_y2pt->Draw("APE");
	g_y3pt->Draw("PE");
	ge_y3pt->Draw("2");
	ge_y2pt->Draw("2");

	legx->Draw();
	tl->DrawLatex( 0.2, 0.8,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 0.2, 0.75, "|y| < 2.4");
	tl->DrawLatex( 0.2, 0.7, "p^{#mu}_{T} > 3.5 GeV/c");

	c3->Modified();
	c3->Update();


	c2->cd();
	p2_1->cd();
	CMS_lumi_square(p2_1, 2, 33);
	c3->cd();
	CMS_lumi_square(c3, 2, 33);

	TFile* output = new TFile("resultRAA_nS_centrality_withSystematics2.root", "recreate");
	output->cd();
	c2->SaveAs("testR.C");
	c2->Write();
	c3->Write();
	c4->Write();
	output->Close();

}
