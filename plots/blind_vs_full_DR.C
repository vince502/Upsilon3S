

void blind_vs_full_DR(){
	TFile* fblind_val = new TFile("./result/DR_100019111111_NOSF.root");
	TFile* fblind_err = new TFile("../Systematics/data/total_systematics_DR_100019111111.root");
	TFile* ffull_val = new TFile("./result/DR_200019111111.root");
	TFile* ffull_err = new TFile("../Systematics/data/total_systematics_DR_200019111111.root");

//	TH1D* h2c_b = (TH1D*) fblind_val->Get("rc2S");
	TH1D* h3c_b = (TH1D*) fblind_val->Get("rc3S");
//	TH1D* h2p_b = (TH1D*) fblind_val->Get("rp2S");
	TH1D* h3p_b = (TH1D*) fblind_val->Get("rp3S");

//	TH1D* e2c_b = (TH1D*) fblind_err->Get("syst_comp/hsys_tot_c2S");
	TH1D* e3c_b = (TH1D*) fblind_err->Get("syst_comp/hsys_tot_c3S");
//	TH1D* e2p_b = (TH1D*) fblind_err->Get("syst_comp/hsys_tot_p2S");
	TH1D* e3p_b = (TH1D*) fblind_err->Get("syst_comp/hsys_tot_p3S");

	TH1D* h3c_r = (TH1D*) h3c_b->Clone("rc3S_ratio");
	TH1D* h3p_r = (TH1D*) h3p_b->Clone("rp3S_ratio");

	double xbins = 0;
	std::vector<string> binc2s, binc3s, binp2s, binp3s;
	binc2s = {"int.", "0-5", "5-10", "10-20", "20-30", "30-40", "40-50", "50-60", "60-70", "70-90"};
	binc3s = {"int.", "0-30", "30-50", "50-70", "70-90"};
	binp2s = {"0-3", "3-6", "6-9", "9-15", "15-30"};
	binp3s = {"0-4", "4-9", "9-15", "15-30" };

//h2c_b->SetLineColor(kRed);
h3c_b->SetLineColor(kRed);
//h2p_b->SetLineColor(kRed);
h3p_b->SetLineColor(kRed);

//h2c_b->SetMarkerColor(kRed);
h3c_b->SetMarkerColor(kRed);
//h2p_b->SetMarkerColor(kRed);
h3p_b->SetMarkerColor(kRed);

//e2c_b->SetFillColorAlpha(kRed,0.8);
e3c_b->SetFillColorAlpha(kRed,0.8);
//e2p_b->SetFillColorAlpha(kRed,0.8);
e3p_b->SetFillColorAlpha(kRed,0.8);

//h2c_b->SetStats(0);
h3c_b->SetStats(0);
//h2p_b->SetStats(0);
h3p_b->SetStats(0);

//h2c_b->GetXaxis()->SetTitle("Centrality (%)");
h3c_b->GetXaxis()->SetTitle("Centrality (%)");
//h2p_b->GetXaxis()->SetTitle("pT (GeV/c)");
h3p_b->GetXaxis()->SetTitle("pT (GeV/c)");

//h2c_b->GetYaxis()->SetTitle("R_{AA}");
h3c_b->GetYaxis()->SetTitle("Ratio");
//h2p_b->GetYaxis()->SetTitle("R_{AA}");
h3p_b->GetYaxis()->SetTitle("Ratio");

//	TH1D* h2c_f = (TH1D*) ffull_val->Get("rc2S");
	TH1D* h3c_f = (TH1D*) ffull_val->Get("rc3S");
//	TH1D* h2p_f = (TH1D*) ffull_val->Get("rp2S");
	TH1D* h3p_f = (TH1D*) ffull_val->Get("rp3S");

//	TH1D* e2c_f = (TH1D*) ffull_err->Get("syst_comp/hsys_tot_c2S");
	TH1D* e3c_f = (TH1D*) ffull_err->Get("syst_comp/hsys_tot_c3S");
//	TH1D* e2p_f = (TH1D*) ffull_err->Get("syst_comp/hsys_tot_p2S");
	TH1D* e3p_f = (TH1D*) ffull_err->Get("syst_comp/hsys_tot_p3S");

//h2c_f->SetLineColor(kBlue+2);
h3c_f->SetLineColor(kBlue+2);
//h2p_f->SetLineColor(kBlue+2);
h3p_f->SetLineColor(kBlue+2);

//h2c_f->SetMarkerColor(kBlue+2);
h3c_f->SetMarkerColor(kBlue+2);
//h2p_f->SetMarkerColor(kBlue+2);
h3p_f->SetMarkerColor(kBlue+2);

//e2c_f->SetFillColorAlpha(kBlue+2,0.8);
e3c_f->SetFillColorAlpha(kBlue+2,0.8);
//e2p_f->SetFillColorAlpha(kBlue+2,0.8);
e3p_f->SetFillColorAlpha(kBlue+2,0.8);

//h2c_f->SetStats(0);
h3c_f->SetStats(0);
//h2p_f->SetStats(0);
h3p_f->SetStats(0);

//	xbins = h2c_b->GetNbinsX();
//	for(auto id : ROOT::TSeqI(xbins) ){
//		h2c_b->SetBinError(id+1, h2c_b->GetBinError(id+1) * 1 );
//		h2c_b->GetXaxis()->SetBinLabel(id+1, binc2s[id].c_str());
//	}

	auto pe = [](double b, double be, double f, double fe){
        double fee = (16.) * fe* fe;
        double bee = be * be;
        double corr = ((16.) *f* f ) - 8. * f* b;
        double corrfull = corr/( b*b);
//		corrfull= 1;
        double prop_e = TMath::Sqrt( (fee + bee  ) / 2 );
//        double prop_e = TMath::Sqrt( (fee + bee *corrfull )) / (4. * b );

		return prop_e;
	};

	xbins = h3c_b->GetNbinsX();
	for(auto id : ROOT::TSeqI(xbins) ){
		h3c_b->SetBinError(id+1,h3c_b->GetBinError(id+1) * 1 );
		h3c_b->GetXaxis()->SetBinLabel(id+1, binc3s[id].c_str());
		h3c_r->SetBinContent( id+1, h3c_f->GetBinContent(id+1) / h3c_b->GetBinContent(id+1) );
		h3c_r->SetBinError(id+1, pe(h3c_b->GetBinContent(id+1), h3c_b->GetBinError(id+1), h3c_f->GetBinContent(id+1), h3c_f->GetBinError(id+1)));
	}

//	xbins = h2p_b->GetNbinsX();
//	for(auto id : ROOT::TSeqI(xbins) ){
//		h2p_b->SetBinError(id+1,h2p_b->GetBinError(id+1) * 1 );
//		h2p_b->GetXaxis()->SetBinLabel(id+1, binp2s[id].c_str());
//	}

	xbins = h3p_b->GetNbinsX();
	for(auto id : ROOT::TSeqI(xbins) ){
		h3p_b->SetBinError(id+1,h3p_b->GetBinError(id+1) * 1 );
		h3p_b->GetXaxis()->SetBinLabel(id+1, binp3s[id].c_str());
		h3p_r->SetBinContent( id+1, h3p_f->GetBinContent(id+1) / h3p_b->GetBinContent(id+1) );
		h3p_r->SetBinError(id+1, pe(h3p_b->GetBinContent(id+1), h3p_b->GetBinError(id+1), h3p_f->GetBinContent(id+1), h3p_f->GetBinError(id+1)));
//		h3p_r->SetBinError(id+1, 0.2);
	}


	TLegend* leg = new TLegend(0.53, 0.17,0.87, 0.28);
	leg->AddEntry(h3c_b, "blind result", "le");
	leg->AddEntry(h3c_f, "full result", "le");
//	leg->AddEntry(h3c_r, "ratio", "le");
	leg->SetBorderSize(0);
    TLatex* tl = new TLatex();
    tl->SetTextSize(0.037);
	TCanvas* c1 = new TCanvas("c1", "" , 1100, 600);
	c1->Divide(2,1);
	c1->cd(1);
//	h2c_b->Draw("pe");
//	h2c_f->Draw("same");
//	e2c_b->Draw("E2");
//	e2c_f->Draw("E2");

	auto shift_h = [](TH1D* from, TH1D* to){
		TAxis* a = from->GetXaxis();
		double dx = a->GetBinWidth(1)/20;
		a = to->GetXaxis();
		a->Set(a->GetNbins(),a->GetXmin() - dx, a->GetXmax() - dx);
	};

	c1->cd(1);

	h3c_b->GetYaxis()->SetRangeUser(0,1.8);
	
	shift_h(h3c_b, h3c_f);
	h3c_b->Draw("pe");
	h3c_f->Draw("same");
    tl->DrawLatexNDC(0.12,0.93, "#Upsilon(3S) / #Upsilon(2S) Centrality");
	leg->Draw();

	c1->cd(2);

//	h2p_b->Draw("pe");
//	h2p_f->Draw("same");
	c1->cd(2);

	h3p_b->GetYaxis()->SetRangeUser(0,1.6);


	shift_h(h3p_b, h3p_f);
	h3p_b->Draw("pe");
	h3p_f->Draw("same");
    tl->DrawLatexNDC(0.12,0.93, "#Upsilon(3S) / #Upsilon(2S) p_{T}");

	c1->SaveAs("~/Upsilon3S/checkout/blind_result_check_DR.pdf");
	c1->SaveAs("~/Upsilon3S/checkout/blind_result_check_DR.png");

//	c1->cd(3);
//
//	h3c_r->GetYaxis()->SetRangeUser(0,1.6);
//
//	h3c_r->Draw("pe");
//
//	c1->cd(4);
//
//	h3p_r->GetYaxis()->SetRangeUser(0,1.6);
//
//	h3p_r->Draw("pe");
}
