void drawtest(long ts, TFile* f3, TFile* f2){
	TFile* f1 = TFile::Open(Form("NominalBKG_%ld.root", ts));
//	TFile* f2 = TFile::Open("./data/bkgPDF_unc_.root");
//	TFile* f3 = TFile::Open("./data/bkgPDF_unc_2item.root");

	TCanvas* c1 =new TCanvas("c1","", 1000, 800);
	TLatex* tl = new TLatex();
	double def_txtsz = tl->GetTextSize();
	tl->SetTextAlign(21);
	c1->Divide(2,2);
	double plt_rng_up = 1;
	double plt_rng_do =-1;

	TLine* tli = new TLine();
	tli->SetLineColor(kRed);
	tli->SetLineStyle(kDashed);

	c1->cd(1);
	auto h1 = (TH1D*) f1->Get("rc2S");
	h1->GetYaxis()->SetRangeUser(plt_rng_do,plt_rng_up);
	h1->Draw("X");
	((TH1D*) f2->Get("rc2S"))->Draw("same");
	((TH1D*) f3->Get("rc2S"))->Draw("same");
	auto h13 = (TH1D*) f3->Get("rc2S");
	auto use_hist = h13;
	tl->SetTextSize(def_txtsz*(8./(double) use_hist->GetXaxis()->GetNbins()));
	int nBins = h13->GetXaxis()->GetNbins();
	for(int ibin = 1; ibin <= nBins; ibin ++){
		string label = use_hist->GetXaxis()->GetBinLabel(ibin);
		tl->DrawLatex(use_hist->GetXaxis()->GetBinCenter(ibin), use_hist->GetBinContent(ibin), label.c_str());
	}
	tli->DrawLine(h1->GetXaxis()->GetXmin(),0,h1->GetXaxis()->GetXmax(),0);
	
	c1->cd(2);
	auto h2 = (TH1D*) f1->Get("rc3S");
	h2->GetYaxis()->SetRangeUser(plt_rng_do,plt_rng_up);
	h2->Draw("X");
	((TH1D*) f2->Get("rc3S"))->Draw("same");
	((TH1D*) f3->Get("rc3S"))->Draw("same");
	auto h23 = (TH1D*) f3->Get("rc3S");
	use_hist = h23;
	tl->SetTextSize(def_txtsz*(8./(double) use_hist->GetXaxis()->GetNbins()));
	nBins = use_hist->GetXaxis()->GetNbins();
	for(int ibin = 1; ibin <= nBins; ibin ++){
		string label = use_hist->GetXaxis()->GetBinLabel(ibin);
		tl->DrawLatex(use_hist->GetXaxis()->GetBinCenter(ibin), use_hist->GetBinContent(ibin), label.c_str());
	}
	tli->DrawLine(h2->GetXaxis()->GetXmin(),0,h2->GetXaxis()->GetXmax(),0);
	
	c1->cd(3);
	auto h3 = (TH1D*) f1->Get("rp2S");
	h3->GetYaxis()->SetRangeUser(plt_rng_do,plt_rng_up);
	h3->Draw("X");
	((TH1D*) f2->Get("rp2S"))->Draw("same");
	((TH1D*) f3->Get("rp2S"))->Draw("same");
	auto h33 = (TH1D*) f3->Get("rp2S");
	use_hist = h33;
	tl->SetTextSize(def_txtsz*(8./(double) use_hist->GetXaxis()->GetNbins()));
	nBins = h33->GetXaxis()->GetNbins();
	for(int ibin = 1; ibin <= nBins; ibin ++){
		string label = use_hist->GetXaxis()->GetBinLabel(ibin);
		tl->DrawLatex(use_hist->GetXaxis()->GetBinCenter(ibin), use_hist->GetBinContent(ibin), label.c_str());
	}
	tli->DrawLine(h3->GetXaxis()->GetXmin(),0,h3->GetXaxis()->GetXmax(),0);
	
	c1->cd(4);
	auto h4 = (TH1D*) f1->Get("rp3S");
	h4->GetYaxis()->SetRangeUser(plt_rng_do,plt_rng_up);
	h4->Draw("X");
	((TH1D*) f2->Get("rp3S"))->Draw("same");
	((TH1D*) f3->Get("rp3S"))->Draw("same");
	auto h43 = (TH1D*) f3->Get("rp3S");
	use_hist = h43;
	tl->SetTextSize(def_txtsz*(8./(double) use_hist->GetXaxis()->GetNbins()));
	nBins = h43->GetXaxis()->GetNbins();
	for(int ibin = 1; ibin <= nBins; ibin ++){
		string label = use_hist->GetXaxis()->GetBinLabel(ibin);
		tl->DrawLatex(use_hist->GetXaxis()->GetBinCenter(ibin), use_hist->GetBinContent(ibin), label.c_str());
	}
	tli->DrawLine(h4->GetXaxis()->GetXmin(),0,h4->GetXaxis()->GetXmax(),0);
};

void drawtestany(TFile* _f){
	TH1D* h1 = (TH1D*) _f->Get("rc2S");
	TH1D* h2 = (TH1D*) _f->Get("rc3S");
	TH1D* h3 = (TH1D*) _f->Get("rp2S");
	TH1D* h4 = (TH1D*) _f->Get("rp3S");
	TCanvas* c1 =new TCanvas();
	c1->Divide(2,2);
	TLine* tli = new TLine();
	tli->SetLineColor(kRed);
	tli->SetLineStyle(kDashed);

	c1->cd(1);
	h1->GetYaxis()->SetRangeUser(-1,1);
	h1->Draw();
	tli->DrawLine(h1->GetXaxis()->GetXmin(),0,h1->GetXaxis()->GetXmax(),0);
	c1->cd(2);
	h2->GetYaxis()->SetRangeUser(-1,1);
	h2->Draw();
	tli->DrawLine(h2->GetXaxis()->GetXmin(),0,h2->GetXaxis()->GetXmax(),0);
	c1->cd(3);
	h3->GetYaxis()->SetRangeUser(-1,1);
	h3->Draw();
	tli->DrawLine(h3->GetXaxis()->GetXmin(),0,h3->GetXaxis()->GetXmax(),0);
	c1->cd(4);
	h4->GetYaxis()->SetRangeUser(-1,1);
	h4->Draw();
	tli->DrawLine(h4->GetXaxis()->GetXmin(),0,h4->GetXaxis()->GetXmax(),0);
};

