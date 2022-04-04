void getPbPbCorr_SR(){
	auto f1 = TFile::Open("~/Upsilon3S/plots/result/DR_200019111111_aux.root");
	auto f2 = TFile::Open("~/Upsilon3S/Systematics/data/Correction_unc_DR_200019111111_PbPb.root");

	TH1D* hc = (TH1D*) f1->Get("rc3S");
	TH1D* hp = (TH1D*) f1->Get("rp3S");

	TH1D* hCor_c = (TH1D*) f2->Get("rc3S");
	TH1D* hCor_p = (TH1D*) f2->Get("rp3S");

	TH1D* hc_new = (TH1D*) hc->Clone("PbPbSR_IntCent");
	TH1D* hp_new = (TH1D*) hp->Clone("PbPbSR_Pt");

	hc_new->GetXaxis()->SetBinLabel(1,"integrated");
	hc_new->GetXaxis()->SetBinLabel(2,"0-30 %");
	hc_new->GetXaxis()->SetBinLabel(3,"30-50 %");
	hc_new->GetXaxis()->SetBinLabel(4,"50-70 %");
	hc_new->GetXaxis()->SetBinLabel(5,"70-90 %");

	hc_new->SetBinContent(1, hc_new->GetBinContent(1) / hCor_c->GetBinContent(1));
	hc_new->SetBinContent(2, hc_new->GetBinContent(2) / hCor_c->GetBinContent(2));
	hc_new->SetBinContent(3, hc_new->GetBinContent(3) / hCor_c->GetBinContent(3));
	hc_new->SetBinContent(4, hc_new->GetBinContent(4) / hCor_c->GetBinContent(4));
	hc_new->SetBinContent(5, hc_new->GetBinContent(5) / hCor_c->GetBinContent(5));

	hc_new->SetBinError(1,hc_new->GetBinError(1) / hCor_c->GetBinContent(1));
	hc_new->SetBinError(2,hc_new->GetBinError(2) / hCor_c->GetBinContent(1));
	hc_new->SetBinError(3,hc_new->GetBinError(3) / hCor_c->GetBinContent(3));
	hc_new->SetBinError(4,hc_new->GetBinError(4) / hCor_c->GetBinContent(4));
	hc_new->SetBinError(5,hc_new->GetBinError(5) / hCor_c->GetBinContent(5));

	hp_new->GetXaxis()->SetBinLabel(1,"0-4 GeV");
	hp_new->GetXaxis()->SetBinLabel(2,"4-9 GeV");
	hp_new->GetXaxis()->SetBinLabel(3,"9-15 GeV");
	hp_new->GetXaxis()->SetBinLabel(4,"15-30 GeV");

	hp_new->SetBinContent(1, hp_new->GetBinContent(1) / hCor_p->GetBinContent(1));
	hp_new->SetBinContent(2, hp_new->GetBinContent(2) / hCor_p->GetBinContent(2));
	hp_new->SetBinContent(3, hp_new->GetBinContent(3) / hCor_p->GetBinContent(3));
	hp_new->SetBinContent(4, hp_new->GetBinContent(4) / hCor_p->GetBinContent(4));

	hp_new->SetBinError(1, hp_new->GetBinError(1) / hCor_p->GetBinContent(1));
	hp_new->SetBinError(2, hp_new->GetBinError(2) / hCor_p->GetBinContent(1));
	hp_new->SetBinError(3, hp_new->GetBinError(3) / hCor_p->GetBinContent(3));
	hp_new->SetBinError(4, hp_new->GetBinError(4) / hCor_p->GetBinContent(4));

	TFile* output = new TFile("PbPb2018Upsilon_SingleRatio.root","recreate");
	output->cd();
	hc_new->Write();
	hp_new->Write();
}


