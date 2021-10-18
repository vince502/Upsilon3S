#include "../bininfo.h"

void BDTDistribution()
{
	TFile* f_res = TFile::Open(Form("%s/BDT/BDTResult/BDTresultY3S_9999999999_BLIND.root", workdir.Data() ));
	dbg();
	auto bdtdir = [&](int state, int pl, int ph)
	{
		string s_dir = Form("data/Y%dSpt%dto%d",state,pl,ph);
		return s_dir;
	};
	dbg();
	TTree *t_train, *t_test;
	t_train = (TTree*) f_res->Get(Form("%s/dataset1/TrainTree",bdtdir(3,12,30).c_str()));
	t_test = (TTree*) f_res->Get(Form("%s/dataset1/TestTree",bdtdir(3,12,30).c_str()));
	dbg();
	TH1D* hist_s_tr = new TH1D("h_s_tr", "", 40, -0.6, 0.6);
	TH1D* hist_b_tr = new TH1D("h_b_tr", "", 40, -0.6, 0.6);
	TH1D* hist_s_te = new TH1D("h_s_te", "", 40, -0.6, 0.6);
	TH1D* hist_b_te = new TH1D("h_b_te", "", 40, -0.6, 0.6);
	dbg();
	float bdt_tr, bdt_te;
	t_train->SetBranchAddress("BDT", &bdt_tr);
	t_test->SetBranchAddress("BDT", &bdt_te);
	int nEtr, nEte, id_tr, id_te;
	t_train->SetBranchAddress("classID", &id_tr);
	t_test->SetBranchAddress("classID", &id_te);
	dbg();

	nEtr = t_train->GetEntries();
	nEte = t_test->GetEntries();

	for(int idx=0; idx < nEtr; idx++)
	{
		t_train->GetEntry(idx);
		if(id_tr == 0)
		{
			hist_s_tr->Fill(bdt_tr);
		}
		if(id_tr == 1)
		{
			hist_b_tr->Fill(bdt_tr);
		}
	}
	dbg();
	for(int idx=0; idx < nEte; idx++)
	{
		t_test->GetEntry(idx);
		if(id_te == 0)
		{
			hist_s_te->Fill(bdt_te);
		}
		if(id_te == 1)
		{
			hist_b_te->Fill(bdt_te);
		}
	}
	dbg();
	hist_s_tr->Scale(40/hist_s_tr->GetEntries());
	hist_b_tr->Scale(40/hist_b_tr->GetEntries());
	hist_s_te->Scale(40/hist_s_te->GetEntries());
	hist_b_te->Scale(40/hist_b_te->GetEntries());
	TCanvas* c1 = new TCanvas("c1","", 800, 700);
	hist_s_tr->SetMarkerColor(kBlue);
	hist_s_te->SetMarkerColor(kBlue);
	hist_b_tr->SetMarkerColor(kRed);
	hist_b_te->SetMarkerColor(kRed);

	hist_s_tr->SetLineColor(kBlue);
	hist_s_te->SetLineColor(kBlue);
	hist_b_tr->SetLineColor(kRed);
	hist_b_te->SetLineColor(kRed);
	Double_t signal_KS_res, bkg_KS_res;
	signal_KS_res = hist_s_tr->KolmogorovTest(hist_s_te);
	bkg_KS_res = hist_b_tr->KolmogorovTest(hist_b_te);

	std::cout << "Kolmogorov-Smirnov test : signal (background) probability =" << Form(" %.4f (%.4f)",signal_KS_res, bkg_KS_res) << std::endl;
	
	hist_s_tr->Draw("pe");
	hist_b_tr->Draw("same,pe");
	hist_s_te->Draw("same,l");
	hist_b_te->Draw("same,l");

	dbg();
	c1->SaveAs("BDTDistplot.C");

}
