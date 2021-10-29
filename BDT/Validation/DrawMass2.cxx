#include "../../BDT/bininfo.h"

std::vector<std::pair<string, TH1D*> > Get_hists()
{
//	TFile* f_data = TFile::Open(Form("%s/BDT/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1634633971_OniaSkim_TrigS13_BDT.root"));
//	TFile* f_data = TFile::Open(Form("%s/BDT/Validation/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1634805675_OniaSkim_TrigS13_BDT.root"));
	TFile* f_data1 = TFile::Open(Form("%s/BDT//roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT9999999999_OniaSkim_TrigS13_BDT.root"));
	TFile* f_data2 = TFile::Open(Form("%s/BDT/Validation/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1635129350_OniaSkim_TrigS13_BDT.root"));
	TFile* f_data3 = TFile::Open(Form("%s/BDT/Validation/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1635139612_OniaSkim_TrigS13_BDT.root"));
	TFile* f_data4 = TFile::Open(Form("%s/BDT/Validation/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT1635129352_OniaSkim_TrigS13_BDT.root"));
//	TFile* f_data = TFile::Open(Form("%s/BDT/roodatasets/%s", workdir.Data(), "OniaRooDataset_BDT9999999999_OniaSkim_TrigS13_BDT.root"));

	double mass,mass1,mass2,mass3,mass4;
	double bdt,bdt1,bdt2,bdt3,bdt4;
	RooDataSet* rd1= (RooDataSet*) f_data1->Get("dataset_Y1Spt0to30");
	RooDataSet* rd2= (RooDataSet*) f_data2->Get("dataset_Y1Spt0to30");
	RooDataSet* rd3= (RooDataSet*) f_data3->Get("dataset_Y1Spt0to30");
	RooDataSet* rd4= (RooDataSet*) f_data4->Get("dataset_Y1Spt0to30");
	TTree* t_data1 = (TTree*) rd1->GetClonedTree();
	TTree* t_data2 = (TTree*) rd2->GetClonedTree();
	TTree* t_data3 = (TTree*) rd3->GetClonedTree();
	TTree* t_data4 = (TTree*) rd4->GetClonedTree();
	t_data1->SetBranchAddress("mass", &mass);
	t_data2->SetBranchAddress("mass", &mass);
	t_data3->SetBranchAddress("mass", &mass);
	t_data4->SetBranchAddress("mass", &mass);
	t_data1->SetBranchAddress("BDT", &bdt);
	t_data2->SetBranchAddress("BDT", &bdt);
	t_data3->SetBranchAddress("BDT", &bdt);
	t_data4->SetBranchAddress("BDT", &bdt);
	std::vector<std::pair< string, TTree*> > map_data = {{"Nominal", t_data1},{"noQQMassErr", t_data2},{"mass [7.5, 12.5], noQQMassErr",t_data3},{"mass [7.5, 12.5]", t_data4}};
	TH1D* hist[4];
	for(int idx = 0; idx<4; idx++)
	{
		hist[idx] = new TH1D(Form("h_%d",idx), "", 140,8, 14);
	}
	int histidx=0;
	for(auto pair : map_data){
		int nE = pair.second->GetEntries();
		mass=0;
		bdt=0;
		for(int evt =0; evt < nE; evt++)
		{
			pair.second->GetEntry(evt);
				if( bdt > 0.2) hist[histidx]->Fill(mass);
		}
		histidx++;
	}
	std::vector<std::pair<string, TH1D*> > hist_stack;
	for(int idx = 0; idx<4; idx++)
	{
		std::pair<string, TH1D*> hpair = {map_data[idx].first, hist[idx]};
		hist_stack.push_back(hpair);
	}
	return hist_stack;

};

void DrawMass()
{
	auto hists = Get_hists();

	TCanvas* c1 =new TCanvas("c1", "", 1200, 900);
	EColor colrs[6] = {kBlack , kBlue , kMagenta , kTeal , kOrange , kRed};
	TLegend* leg  = new TLegend();
	for (int idx =0; idx < 4; idx++)
	{
			hists[idx].second->Scale(1/hists[idx].second->GetEntries());
			hists[idx].second->SetMarkerColor(colrs[idx]);
			hists[idx].second->SetLineColor(colrs[idx]);
			if( idx == 0 )
			{
				hists[idx].second->GetYaxis()->SetRangeUser(0.001,0.04);
				hists[idx].second->Draw("pe");
			}
			hists[idx].second->Draw("same pe");
			leg->AddEntry(hists[idx].second,hists[idx].first.c_str(), "l");
	}

	leg->SetX1NDC(0.5);
	leg->SetX2NDC(0.7);
	leg->SetY1NDC(0.5);
	leg->SetY2NDC(0.7);
	leg->Draw("same");
	c1->SaveAs("FullMassBDTCompare_methods.C");
};

void DrawMass2()
{
	gStyle->SetOptStat(0);
	auto hists = Get_hists();
	EColor colrs[6] = {kRed , kBlue , kOrange , kTeal , kBlack , kMagenta};
	int idx=0;

	for(auto hpair: hists){
		hpair.second->Scale(1/hpair.second->GetEntries());
		hpair.second->SetLineColor(colrs[idx]);
		idx++;
	}

	TCanvas* c0= new TCanvas("c0", "",2400,1000);
	TPad* pads[6];
	pads[0]=  new TPad("p0", "",0,0.5,0.33,1);
	pads[1]=  new TPad("p1", "",0.33,0.5,0.66,1);
	pads[2]=  new TPad("p2", "",0.66,0.5,1,1);
	pads[3]=  new TPad("p3", "",0,0.0,0.33,0.5);
	pads[4]=  new TPad("p4", "",0.33,0.0,0.66,0.5);
	pads[5]=  new TPad("p5", "",0.66,0.0,1,0.5);
	
	idx=0;
	TLatex* tl = new TLatex();
	tl->SetTextSize(0.04);
	std::vector<std::pair<int,int>>matchs = { {0,1}, {0,2}, {0,3}, {1,2}, {1,3}, {2,3} };
	for(idx; idx<6;idx++){
		c0->cd();
		pads[idx]->Draw();
		pads[idx]->cd();
		hists[matchs[idx].first].second->Draw("pe");
		hists[matchs[idx].second].second->Draw("same pe");
		tl->DrawLatexNDC(0.5,0.7, Form("Comparison of")); 
		tl->DrawLatexNDC(0.5,0.65, Form("#color[%d]{%s}", colrs[matchs[idx].first], hists[matchs[idx].first].first.c_str()));
		tl->DrawLatexNDC(0.5,0.6, Form("and #color[%d]{%s}",colrs[matchs[idx].second],hists[matchs[idx].second].first.c_str()));
	}
	c0->SaveAs("FullMassBDTCompare_methods1S.C");
	
}
