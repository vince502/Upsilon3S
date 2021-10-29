#include "../BDT/bininfo.h"


int numEnts = 2;
std::vector<TH1D*> Get_hists()
{
//	TFile* f_data = TFile::Open(Form("%s/BDT/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1634633971_OniaSkim_TrigS13_BDT.root"));
//	TFile* f_data = TFile::Open(Form("%s/BDT/Validation/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1634805675_OniaSkim_TrigS13_BDT.root"));
//	TFile* f_data = TFile::Open(Form("%s/BDT/Validation/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1634894212_OniaSkim_TrigS13_BDT.root"));
	TFile* f_data = TFile::Open(Form("%s/BDT/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT9999999999_OniaSkim_TrigS13_BDT.root"));
	double mass;
	double bdt;
	double pt;
	RooDataSet* rd = (RooDataSet*) f_data->Get("dataset_Y3Spt0to30");
	TTree* t_data = (TTree*) rd->GetClonedTree();
	t_data->SetBranchAddress("mass", &mass);
	t_data->SetBranchAddress("BDT", &bdt);
	t_data->SetBranchAddress("pt", &pt);

	TH1D* hist[numEnts];
	for(int idx = 0; idx<numEnts; idx++)
	{
		hist[idx] = new TH1D(Form("h_%d",idx), "", 120, 8, 14);
	}
	int nE = t_data->GetEntries();
	for(int evt =0; evt < nE; evt++)
	{
		t_data->GetEntry(evt);
		std::vector<std::pair<double, double>> ptrang = {{0,30},{0,4},{4,9},{9,30}};
		for(int idx = 0; idx<numEnts; idx++)
		{
			
			if( bdt > 0.1 && (pt > ptrang[idx].first && pt < ptrang[idx].second)) hist[idx]->Fill(mass);
		}
	}
	std::vector<TH1D*> hist_stack;
	for(int idx = 0; idx<numEnts; idx++)
	{
		hist_stack.push_back(hist[idx]);
	}
	return hist_stack;

};

void DrawMassPt()
{
	auto hists = Get_hists();
	TCanvas* c1 =new TCanvas("c1", "", 1200, 900);
	EColor colrs[6] = {kBlack , kBlue , kMagenta , kTeal , kOrange , kRed};
	for (int idx =0; idx < numEnts; idx++)
	{
			hists[idx]->Scale(1/hists[idx]->GetEntries());
			hists[idx]->SetMarkerColor(colrs[idx]);
			hists[idx]->SetLineColor(colrs[idx]);
			if( idx == 0 )
			{
				hists[idx]->GetYaxis()->SetRangeUser(0, 0.05);
				hists[idx]->SetMarkerStyle(kFullCircle);
				hists[idx]->SetMarkerSize(1);
				hists[idx]->Draw("pe");
			}
			hists[idx]->Draw("same pe");
	}
	std::cout << "KS Test 0-30 vs. 0-4 GeV/c :" <<hists[0]->KolmogorovTest(hists[1]) << std::endl;;
	c1->SaveAs("FullMassBDTCompare_ptspec.C");
}

