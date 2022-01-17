#include "../.workdir.h"
void Centrality_vs_BDT(){
	TFile* fnom_ds = TFile::Open(Form("%s/BDT/roodatasets/OniaRooDataset_BDT10000000016_OniaSkim_TrigS13_BDT.root", workdir.Data() ));
	TTree* td = (TTree*) ( (RooDataSet*)fnom_ds->Get("dataset_Y3Spt0to30"))->GetClonedTree();

	double bdt, cbin;
	td->SetBranchAddress("BDT", &bdt);
	td->SetBranchAddress("cBin", &cbin);

	int nBins = 100;
	TH1D* h1 = new TH1D("h1", "Centrality vs. BDT", nBins, -1, 1);
	TH1D* h2 = new TH1D("h2", "Centrality vs. BDT", nBins, -1, 1);
	TH1D* h3 = new TH1D("h3", "Centrality vs. BDT", nBins, -1, 1);
	TH1D* h4 = new TH1D("h4", "Centrality vs. BDT", nBins, -1, 1);
	TH1D* h5 = new TH1D("h5", "Centrality vs. BDT", nBins, -1, 1);
	TH1D* h6 = new TH1D("h6", "Centrality vs. BDT", nBins, -1, 1);
	TH1D* h7 = new TH1D("h7", "Centrality vs. BDT", nBins, -1, 1);
	TH1D* h8 = new TH1D("h8", "Centrality vs. BDT", nBins, -1, 1);
	
	auto inrng = [] (int t, int l, int h){
		if (t >=l && t < h) return true;
		return false;
	};

	for(auto idx : ROOT::TSeqL(td->GetEntries())){
		td->GetEntry(idx);
		h1->Fill(bdt);
		int cbin_i = cbin;
		if(inrng(cbin_i, 0, 40)) h2->Fill(bdt);
		if(inrng(cbin_i, 40, 80)) h3->Fill(bdt);
		if(inrng(cbin_i, 80, 120)) h4->Fill(bdt);
		if(inrng(cbin_i, 120, 181)) h5->Fill(bdt);
//		if(inrng(cbin_i, 150, 181)) h6->Fill(bdt);
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
	TLegend* leg= new TLegend(0.55, 0.50, 0.85, 0.85);
	leg->AddEntry(h1, "int.",	 	"lpe");
	leg->AddEntry(h2, "0-20 %",  	"lpe");
	leg->AddEntry(h3, "20-40 %", 	"lpe");
	leg->AddEntry(h4, "40-60 %", 	"lpe");
	leg->AddEntry(h5, "60-90 %", 	"lpe");
//	leg->AddEntry(h6, "75-90 %", 	"lpe");
	leg->Draw();
	
	c1->SaveAs("./result/Centrality_vs_BDT.pdf");
};
