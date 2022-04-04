

void blind_vs_full(){
	TFile* fblind_val = new TFile("./result/RAA_100019111111_NOSF.root");
	TFile* fblind_err = new TFile("../Systematics/data/total_systematics_RAA_100019111111.root");
	TFile* ffull_val = new TFile("./result/RAA_200019111111.root");
	TFile* ffull_err = new TFile("../Systematics/data/total_systematics_RAA_200019111111.root");
	TFile* fblind_2s_val = new TFile("./result/RAA_100019111111_only2S.root");
	TFile* ffull_2s_val = new TFile("./result/RAA_200019111111_only2S.root");

	TH1D* h2c_b = (TH1D*) fblind_val->Get("rc2S");
	TH1D* h3c_b = (TH1D*) fblind_val->Get("rc3S");
	TH1D* h2p_b = (TH1D*) fblind_val->Get("rp2S");
	TH1D* h3p_b = (TH1D*) fblind_val->Get("rp3S");

	TH1D* h3c_b_2s = (TH1D*) fblind_2s_val->Get("rc3S");
	TH1D* h3p_b_2s = (TH1D*) fblind_2s_val->Get("rp3S");

	TH1D* h2c_r = (TH1D*) h2c_b->Clone("rc2S_ratio");
	TH1D* h3c_r = (TH1D*) h3c_b->Clone("rc3S_ratio");
	TH1D* h2p_r = (TH1D*) h2p_b->Clone("rp2S_ratio");
	TH1D* h3p_r = (TH1D*) h3p_b->Clone("rp3S_ratio");

	TH1D* h3c_r_2s = (TH1D*) h3c_b_2s->Clone("rc3S_2S_ratio");
	TH1D* h3p_r_2s = (TH1D*) h3p_b_2s->Clone("rp3S_2S_ratio");


	TH1D* e2c_b = (TH1D*) fblind_err->Get("syst_comp/hsys_tot_c2S");
	TH1D* e3c_b = (TH1D*) fblind_err->Get("syst_comp/hsys_tot_c3S");
	TH1D* e2p_b = (TH1D*) fblind_err->Get("syst_comp/hsys_tot_p2S");
	TH1D* e3p_b = (TH1D*) fblind_err->Get("syst_comp/hsys_tot_p3S");

	double xbins = 0;
	std::vector<string> binc2s, binc3s, binp2s, binp3s;
	binc2s = {"int.", "0-5", "5-10", "10-20", "20-30", "30-40", "40-50", "50-60", "60-70", "70-90"};
	binc3s = {"int.", "0-30", "30-50", "50-70", "70-90"};
	binp2s = {"0-3", "3-6", "6-9", "9-15", "15-30"};
	binp3s = {"0-4", "4-9", "9-15", "15-30" };


h2c_b->SetLineColor(kRed);
h3c_b->SetLineColor(kRed);
h2p_b->SetLineColor(kRed);
h3p_b->SetLineColor(kRed);
h3c_b_2s->SetLineColor(kRed);
h3p_b_2s->SetLineColor(kRed);

h2c_b->SetMarkerColor(kRed);
h3c_b->SetMarkerColor(kRed);
h2p_b->SetMarkerColor(kRed);
h3p_b->SetMarkerColor(kRed);
h3c_b_2s->SetMarkerColor(kRed);
h3p_b_2s->SetMarkerColor(kRed);

e2c_b->SetFillColorAlpha(kRed,0.8);
e3c_b->SetFillColorAlpha(kRed,0.8);
e2p_b->SetFillColorAlpha(kRed,0.8);
e3p_b->SetFillColorAlpha(kRed,0.8);

h2c_b->SetStats(0);
h3c_b->SetStats(0);
h2p_b->SetStats(0);
h3p_b->SetStats(0);
h3c_b_2s->SetStats(0);
h3p_b_2s->SetStats(0);

h2c_b->GetXaxis()->SetTitle("Centrality (%)");
h3c_b->GetXaxis()->SetTitle("Centrality (%)");
h3c_b_2s->GetXaxis()->SetTitle("Centrality (%)");
h2p_b->GetXaxis()->SetTitle("pT (GeV/c)");
h3p_b->GetXaxis()->SetTitle("pT (GeV/c)");
h3p_b_2s->GetXaxis()->SetTitle("pT (GeV/c)");

h2c_b->GetYaxis()->SetTitle("R_{AA}");
h3c_b->GetYaxis()->SetTitle("R_{AA}");
h2p_b->GetYaxis()->SetTitle("R_{AA}");
h3p_b->GetYaxis()->SetTitle("R_{AA}");

h2c_r->GetXaxis()->SetTitle("Centrality (%)");
h3c_r->GetXaxis()->SetTitle("Centrality (%)");
h3c_r_2s->GetXaxis()->SetTitle("Centrality (%)");
h2p_r->GetXaxis()->SetTitle("pT (GeV/c)");
h3p_r->GetXaxis()->SetTitle("pT (GeV/c)");
h3p_r_2s->GetXaxis()->SetTitle("pT (GeV/c)");

h2c_r->GetYaxis()->SetTitle("Ratio");
h3c_r->GetYaxis()->SetTitle("Ratio");
h2p_r->GetYaxis()->SetTitle("Ratio");
h3p_r->GetYaxis()->SetTitle("Ratio");

	TH1D* h2c_f = (TH1D*) ffull_val->Get("rc2S");
	TH1D* h3c_f = (TH1D*) ffull_val->Get("rc3S");
	TH1D* h3c_f_2s = (TH1D*) ffull_2s_val->Get("rc3S");
	TH1D* h2p_f = (TH1D*) ffull_val->Get("rp2S");
	TH1D* h3p_f = (TH1D*) ffull_val->Get("rp3S");
	TH1D* h3p_f_2s = (TH1D*) ffull_2s_val->Get("rp3S");

	TH1D* e2c_f = (TH1D*) ffull_err->Get("syst_comp/hsys_tot_c2S");
	TH1D* e3c_f = (TH1D*) ffull_err->Get("syst_comp/hsys_tot_c3S");
	TH1D* e2p_f = (TH1D*) ffull_err->Get("syst_comp/hsys_tot_p2S");
	TH1D* e3p_f = (TH1D*) ffull_err->Get("syst_comp/hsys_tot_p3S");

h2c_f->SetLineColor(kBlue+2);
h3c_f->SetLineColor(kBlue+2);
h3c_f_2s->SetLineColor(kBlue+2);
h2p_f->SetLineColor(kBlue+2);
h3p_f->SetLineColor(kBlue+2);
h3p_f_2s->SetLineColor(kBlue+2);

h2c_f->SetMarkerColor(kBlue+2);
h3c_f->SetMarkerColor(kBlue+2);
h3c_f_2s->SetMarkerColor(kBlue+2);
h2p_f->SetMarkerColor(kBlue+2);
h3p_f->SetMarkerColor(kBlue+2);
h3p_f_2s->SetMarkerColor(kBlue+2);

e2c_f->SetFillColorAlpha(kBlue+2,0.8);
e3c_f->SetFillColorAlpha(kBlue+2,0.8);
e2p_f->SetFillColorAlpha(kBlue+2,0.8);
e3p_f->SetFillColorAlpha(kBlue+2,0.8);

h2c_f->SetStats(0);
h3c_f->SetStats(0);
h3c_f_2s->SetStats(0);
h2p_f->SetStats(0);
h3p_f->SetStats(0);
h3p_f_2s->SetStats(0);

    auto pe = [](double b, double be, double f, double fe){
		b= b/4.; be = be/2.;
		double fee = fe* fe;
		double bee = be * be;
		double corr = (f* f ) - 2* f* b;
		double corrfull = corr/( b*b);
		double prop_e = TMath::Sqrt( fee + bee * corrfull) / (b* 4.);

        return prop_e;
    };

	xbins = h2c_b->GetNbinsX();
	for(auto id : ROOT::TSeqI(xbins) ){
		h2c_b->SetBinContent(id+1, h2c_b->GetBinContent(id+1) * 4 );
		h2c_b->SetBinError(id+1, h2c_b->GetBinError(id+1) * 2 );
		h2c_b->GetXaxis()->SetBinLabel(id+1, binc2s[id].c_str());
		h2c_r->SetBinContent( id+1, h2c_f->GetBinContent(id+1) / h2c_b->GetBinContent(id+1) );
        h2c_r->SetBinError(id+1, pe(h2c_b->GetBinContent(id+1), h2c_b->GetBinError(id+1), h2c_f->GetBinContent(id+1), h2c_f->GetBinError(id+1)));
		h2c_r->GetXaxis()->SetBinLabel(id+1, binc2s[id].c_str());
	}

	xbins = h3c_b->GetNbinsX();
	for(auto id : ROOT::TSeqI(xbins) ){
		h3c_b->SetBinContent(id+1, h3c_b->GetBinContent(id+1) * 4 );
		h3c_b->SetBinError(id+1,h3c_b->GetBinError(id+1) * 2 );
		h3c_b->GetXaxis()->SetBinLabel(id+1, binc3s[id].c_str());
		h3c_r->SetBinContent( id+1, h3c_f->GetBinContent(id+1) / h3c_b->GetBinContent(id+1) );
        h3c_r->SetBinError(id+1, pe(h3c_b->GetBinContent(id+1), h3c_b->GetBinError(id+1), h3c_f->GetBinContent(id+1), h3c_f->GetBinError(id+1)));
		h3c_r->GetXaxis()->SetBinLabel(id+1, binc3s[id].c_str());
	}

	xbins = h2p_b->GetNbinsX();
	for(auto id : ROOT::TSeqI(xbins) ){
		h2p_b->SetBinContent(id+1, h2p_b->GetBinContent(id+1) * 4 );
		h2p_b->SetBinError(id+1,h2p_b->GetBinError(id+1) * 2 );
		h2p_b->GetXaxis()->SetBinLabel(id+1, binp2s[id].c_str());
		h2p_r->SetBinContent( id+1, h2p_f->GetBinContent(id+1) / h2p_b->GetBinContent(id+1) );
        h2p_r->SetBinError(id+1, pe(h2p_b->GetBinContent(id+1), h2p_b->GetBinError(id+1), h2p_f->GetBinContent(id+1), h2p_f->GetBinError(id+1)));
		h2p_r->GetXaxis()->SetBinLabel(id+1, binp2s[id].c_str());
	}

	xbins = h3p_b->GetNbinsX();
	for(auto id : ROOT::TSeqI(xbins) ){
		h3p_b->SetBinContent(id+1, h3p_b->GetBinContent(id+1) * 4 );
		h3p_b->SetBinError(id+1,h3p_b->GetBinError(id+1) * 2 );
		h3p_b->GetXaxis()->SetBinLabel(id+1, binp3s[id].c_str());
		h3p_r->SetBinContent( id+1, h3p_f->GetBinContent(id+1) / h3p_b->GetBinContent(id+1) );
        h3p_r->SetBinError(id+1, pe(h3p_b->GetBinContent(id+1), h3p_b->GetBinError(id+1), h3p_f->GetBinContent(id+1), h3p_f->GetBinError(id+1)));
		h3p_r->GetXaxis()->SetBinLabel(id+1, binp3s[id].c_str());


	}

	xbins = h3c_b_2s->GetNbinsX();
	for(auto id : ROOT::TSeqI(xbins) ){
		h3c_b_2s->SetBinContent(id+1, h3c_b_2s->GetBinContent(id+1) * 4 );
		h3c_b_2s->SetBinError(id+1,h3c_b_2s->GetBinError(id+1) * 2 );
		h3c_b_2s->GetXaxis()->SetBinLabel(id+1, binc3s[id].c_str());
		h3c_r_2s->SetBinContent( id+1, h3c_f_2s->GetBinContent(id+1) / h3c_b_2s->GetBinContent(id+1) );
        h3c_r_2s->SetBinError(id+1, pe(h3c_b_2s->GetBinContent(id+1), h3c_b_2s->GetBinError(id+1), h3c_f_2s->GetBinContent(id+1), h3c_f_2s->GetBinError(id+1)));
		h3c_r_2s->GetXaxis()->SetBinLabel(id+1, binc3s[id].c_str());
	}

	xbins = h3p_b_2s->GetNbinsX();
	for(auto id : ROOT::TSeqI(xbins) ){
		h3p_b_2s->SetBinContent(id+1, h3p_b_2s->GetBinContent(id+1) * 4 );
		h3p_b_2s->SetBinError(id+1,h3p_b_2s->GetBinError(id+1) * 2 );
		h3p_b_2s->GetXaxis()->SetBinLabel(id+1, binp3s[id].c_str());
		h3p_r_2s->SetBinContent( id+1, h3p_f_2s->GetBinContent(id+1) / h3p_b_2s->GetBinContent(id+1) );
        h3p_r_2s->SetBinError(id+1, pe(h3p_b_2s->GetBinContent(id+1), h3p_b_2s->GetBinError(id+1), h3p_f_2s->GetBinContent(id+1), h3p_f_2s->GetBinError(id+1)));
		h3p_r_2s->GetXaxis()->SetBinLabel(id+1, binp3s[id].c_str());
	}

	TLegend* leg = new TLegend(0.15, 0.6,0.5, 0.8);
	TLegend* leg2= new TLegend(0.6, 0.55,0.9, 0.85);
	leg->AddEntry(h2c_b, "blind result", "le");
	leg->AddEntry(h2c_f, "full result", "le");
	leg2->AddEntry(h3c_r_2s, "Ratio full / blind", "le");
	leg->SetBorderSize(0);
	leg2->SetBorderSize(0);
	leg-> SetTextSize(0.035);
	leg2->SetTextSize(0.035);

	TCanvas* c1 = new TCanvas("c1", "" , 900, 1100);
	TCanvas* c2 = new TCanvas("c2", "" , 900, 1100);
	c1->SetLeftMargin(0.065);
	c2->SetLeftMargin(0.065);
	c1->SetRightMargin(0.03);
	c2->SetRightMargin(0.03);
	c1->Divide(2,3);
	c2->Divide(2,3);
	TLatex* tl = new TLatex();
	tl->SetTextSize(0.037);

	auto shift_h = [](TH1D* from, TH1D* to){
		TAxis* a = from->GetXaxis();
		double dx = a->GetBinWidth(1)/20;
		a = to->GetXaxis();
		a->Set(a->GetNbins(),a->GetXmin() - dx, a->GetXmax() - dx);
	};

	c1->cd(1);
	shift_h(h2c_b, h2c_f);
	h2c_b->Draw("pe");
	h2c_f->Draw("same");
//	e2c_b->Draw("E2");
//	e2c_f->Draw("E2");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(2S) Centrality R_{AA}");
	
	leg->Draw();

	c1->cd(2);


	shift_h(h3c_b, h3c_f);
	h3c_b->Draw("pe");
	h3c_f->Draw("same");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(3S) Centrality R_{AA}");

	c1->cd(3);
	shift_h(h2p_b, h2p_f);

	h2p_b->Draw("pe");
	h2p_f->Draw("same");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(2S) p_{T}");

	c1->cd(4);

	shift_h(h3p_b, h3p_f);
	h3p_b->Draw("pe");
	h3p_f->Draw("same");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(3S) p_{T}");

	c1->cd(5);

	h3c_b_2s->GetYaxis()->SetTitle("Invariant Yield");
	shift_h(h3c_b_2s, h3c_f_2s);
	h3c_b_2s->Draw("pe");
	h3c_f_2s->Draw("same");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(2S) Centrality in 3S bin");

	c1->cd(6);

	h3p_b_2s->GetYaxis()->SetTitle("Invariant Yield");
	shift_h(h3p_b_2s, h3p_f_2s);
	h3p_b_2s->Draw("pe");
	h3p_f_2s->Draw("same");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(2S) p_{T} in 3S bin");

///////////////////
	TLine* line_one = new TLine();
	line_one->SetLineWidth(2);
	line_one->SetLineStyle(2);
	c2->cd(1);
	h2c_r->SetStats(0);
	h2c_r->Draw("pe");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(2S) Centrality R_{AA}");
	line_one->DrawLine(0,1,9,1);
	
	leg2->Draw();

	c2->cd(2);

	h3c_r->SetStats(0);
	h3c_r->Draw("pe");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(3S) Centrality R_{AA}");
	line_one->DrawLine(0,1,4,1);

	c2->cd(3);

	h2p_r->SetStats(0);
	h2p_r->Draw("pe");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(2S) p_{T}");
	line_one->DrawLine(1,1,5,1);

	c2->cd(4);

	h3p_r->SetStats(0);
	h3p_r->Draw("pe");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(3S) p_{T}");
	line_one->DrawLine(1,1,4,1);

	c2->cd(5);

	h3c_r_2s->SetStats(0);
	h3c_r_2s->GetYaxis()->SetTitle("Ratio");
	h3c_r_2s->Draw("pe");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(2S) Centrality in 3S bin");
	line_one->DrawLine(0,1,4,1);

	c2->cd(6);

	h3p_r_2s->SetStats(0);
	h3p_r_2s->GetYaxis()->SetTitle("Ratio");
	h3p_r_2s->Draw("pe");
	tl->DrawLatexNDC(0.12,0.93, "#Upsilon(2S) p_{T} in 3S bin");
	line_one->DrawLine(1,1,4,1);

	c1->SaveAs("~/Upsilon3S/checkout/blind_result_check_RAA.pdf");
	c1->SaveAs("~/Upsilon3S/checkout/blind_result_check_RAA.png");
	c2->SaveAs("~/Upsilon3S/checkout/blind_result_check_RAARatio.pdf");
	c2->SaveAs("~/Upsilon3S/checkout/blind_result_check_RAARatio.png");



}
