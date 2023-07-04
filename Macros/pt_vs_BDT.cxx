#include "../.workdir.h"
void pt_vs_BDT(){
	TFile* fnom_ds = TFile::Open(Form("%s/BDT/roodatasets/OniaRooDataset_BDT200019111111_OniaSkim_TrigS13_BDT.root", workdir.Data() ));
	TFile* fnom_dsmc = TFile::Open(Form("%s/BDT/roodatasets/OniaRooDataset_BDT100019111111_OniaSkim_TrigS13_BDT_MC.root", workdir.Data() ));
	TTree* td = (TTree*) ( (RooDataSet*)fnom_dsmc->Get("dataset_Y3Spt0to30"))->GetClonedTree();

	double bdt, pt;
	td->SetBranchAddress("BDT", &bdt);
	td->SetBranchAddress("pt", &pt);

	int nBins = 100;
	TH1D* h1 = new TH1D("h1", "pT vs. BDT", nBins, -1, 1);
	TH1D* h2 = new TH1D("h2", "pT vs. BDT", nBins, -1, 1);
	TH1D* h3 = new TH1D("h3", "pT vs. BDT", nBins, -1, 1);
	TH1D* h4 = new TH1D("h4", "pT vs. BDT", nBins, -1, 1);
	TH1D* h5 = new TH1D("h5", "pT vs. BDT", nBins, -1, 1);
	TH1D* h6 = new TH1D("h6", "pT vs. BDT", nBins, -1, 1);
	TH1D* h7 = new TH1D("h7", "pT vs. BDT", nBins, -1, 1);
	TH1D* h8 = new TH1D("h8", "pT vs. BDT", nBins, -1, 1);
	
	auto inrng = [] (int t, int l, int h){
		if (t >=l && t < h) return true;
		return false;
	};

	for(auto idx : ROOT::TSeqL(td->GetEntries())){
		td->GetEntry(idx);
		h1->Fill(bdt);
		int pt_i = pt;
		if(inrng(pt_i, 0, 4)) h2->Fill(bdt);
		if(inrng(pt_i, 4, 9)) h3->Fill(bdt);
		if(inrng(pt_i, 9, 15)) h4->Fill(bdt);
		if(inrng(pt_i, 15, 30)) h5->Fill(bdt);
//		if(inrng(pt_i, 150, 181)) h6->Fill(bdt);
	}
	TCanvas* c1 = new TCanvas();
	h1->SetLineColor(kBlack);
	h2->SetLineColor(kRed);
	h3->SetLineColor(kOrange);
	h4->SetLineColor(kGreen);
	h5->SetLineColor(kMagenta);
//	h6->SetLineColor(kTeal+2);
	for( auto hist : {h1, h2, h3, h4, h5}){
		hist->Scale(1/hist->GetSum());
		hist->SetStats(0);
		hist->GetXaxis()->SetTitle("BDT");
		hist->GetYaxis()->SetTitle("a.u.");
	}
	h1->Draw();
	for( auto hist : {h2, h3, h4, h5}){
		hist->Draw("same");
	}
//	TLegend* leg= new TLegend(0.55, 0.50, 0.85, 0.85);
	TLegend* leg= new TLegend(0.15, 0.50, 0.45, 0.85);
	leg->AddEntry(h1, "int.",	 	"lpe");
	leg->AddEntry(h2, "0-4 GeV",  	"lpe");
	leg->AddEntry(h3, "4-9 GeV", 	"lpe");
	leg->AddEntry(h4, "9-15 GeV", 	"lpe");
	leg->AddEntry(h5, "15-30 GeV", 	"lpe");
//	leg->AddEntry(h6, "75-90 %", 	"lpe");
	leg->Draw();
	
	c1->SaveAs("./result/pt_vs_BDT_MC.pdf");
};
