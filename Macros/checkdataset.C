#include "../BDT/bininfo.h"
#include "../.workdir.h"

void checkdataset(){
	auto fref = TFile::Open(Form("%s/OutputSkim_isMC0_v210628_bkup.root", store.Data()));
	auto fref1 = TFile::Open(Form("%s/OutputSkim_isMC0_HFNom_NewMass_211019.root", store.Data()));
	auto ftest = TFile::Open(Form("%s/BDT/roodatasets/OniaRooDataset_BDT20000000000_OniaSkim_TrigS13_BDT.root", workdir.Data() ));

	TH1D* h1 = new TH1D();
	h1->SetName("h1");
	TH1D* h12 = new TH1D();
	h12->SetName("h12");
	TH1D* h2 = new TH1D();
	h2->SetName("h2");

	auto tref = (TTree*) fref->Get("tree");
	auto tref1 = (TTree*) fref1->Get("tree");
	auto ttest = (TTree*) ((RooDataSet*) ftest->Get("dataset_Y3Spt0to30"))->GetClonedTree();
	
	TCanvas* c1 =new TCanvas();
	c1->cd();
	tref->Draw("mass>>h1(140,8,14)", Form("pt<30&&pt1>3.5&&pt2>3.5&&%s", MuIDHybridSoft2018.c_str()));
	tref1->Draw("mass>>h12(140,8,14)", Form("mass>8&&mass<30&&pt<30&&pt1>3.5&&pt2>3.5&&%s", MuIDHybridSoft2018.c_str()));
	ttest->Draw("mass>>h2(140,8,14)","pt<30&&pt1>3.5&&pt2>3.5", "same");
	

}
