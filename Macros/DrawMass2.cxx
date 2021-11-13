#include "../BDT/bininfo.h"

std::vector<TH1D*> Get_hists(long ts, int state)
{
	auto cut = VALI_V3_BDTTESTCUT;
	int nbins = cut.size();
//	TFile* f_data = TFile::Open(Form("%s/BDT/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1634633971_OniaSkim_TrigS13_BDT.root"));
//	TFile* f_data = TFile::Open(Form("%s/BDT/Validation/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1634805675_OniaSkim_TrigS13_BDT.root"));
	TFile* f_data = TFile::Open(Form("%s/BDT/roodatasets/%s", workdir.Data(), Form("OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT.root",ts)));
//	TFile* f_data = TFile::Open(Form("%s/BDT/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT9999999999_OniaSkim_TrigS13_BDT.root"));
	double mass;
	double bdt;
	RooDataSet* rd = (RooDataSet*) f_data->Get(Form("dataset_Y%dSpt0to30",state) );
	TTree* t_data = (TTree*) rd->GetClonedTree();
	t_data->SetBranchAddress("mass", &mass);
	t_data->SetBranchAddress("BDT", &bdt);
	TH1D* hist[nbins];
	for(int idx = 0; idx<nbins; idx++)
	{
		hist[idx] = new TH1D(Form("h_%d",idx), "", 140,6, 14);
	}
	int nE = t_data->GetEntries();
	for(int evt =0; evt < nE; evt++)
	{
		t_data->GetEntry(evt);
//		double cut[6] = {-1, -0.3,  0.1, 0.4,  0.7, 0.9};
		for(int idx = 0; idx<6; idx++)
		{
			
			if( bdt > cut[idx]) hist[idx]->Fill(mass);
		}
	}
	std::vector<TH1D*> hist_stack;
	for(int idx = 0; idx<6; idx++)
	{
		hist_stack.push_back(hist[idx]);
	}
	return hist_stack;

};

void DrawMass2(long ts, int state)
{
	auto hists = Get_hists(ts, state);
	int nhists = hists.size();
	TCanvas* c1 =new TCanvas("c1", "", 1200, 900);
	Color_t colrs[12] = {kBlack , kBlue , kMagenta , kTeal , kOrange , kRed, kBlue -6, kMagenta +3, kTeal +3, kOrange -3, kRed -7, kCyan +2, };
	for (int idx =0; idx < nhists; idx++)
	{

			hists[idx]->SetMarkerColor(colrs[idx]);
			hists[idx]->SetLineColor(colrs[idx]);
			if( idx == 0 )
			{
				hists[idx]->GetYaxis()->SetRangeUser(1,4000);
				hists[idx]->Draw("pe");
			}
			hists[idx]->Draw("same pe");
	}
	c1->SaveAs(Form("./FullMassBDT/FullMassBDTCompare_fullmass_m614_%ld_%d.C", ts, state));
}

