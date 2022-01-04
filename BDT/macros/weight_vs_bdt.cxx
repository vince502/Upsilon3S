#include "TH1D.h"
#include "../../.workdir.h"

std::vector<TH1D*> hist_weight_vs_bdt(long ts, int state, int pl, int ph){
	string fname = "";
	if( state == 2) fname = Form("OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT_MC_2S.root",ts);
	if( state == 3) fname = Form("OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT_MC.root",ts);
	TFile* file = TFile::Open(Form("%s/BDT/roodatasets/%s", workdir.Data(), fname.c_str() ));
	TTree* t1 = (TTree*) file->Get(Form("RooTreeDataStore_dataset_Y%dSpt%dto%d__a_dataset", state, pl, ph));
	
	
	double wgt, bdt;
	t1->SetBranchAddress("weight", &wgt);
	t1->SetBranchAddress("BDT", &bdt);
	std::vector<TH1D*> h_wgt = {};

	double bin_high = (state ==2 || state ==1 ) ? 1 : 1000;
	for( int idx = 0; idx < 10; idx ++){
		h_wgt.push_back(new TH1D(Form("hist_idx%d",idx),"", 100,0, bin_high ));
	}
	for( int idx = 0 ; idx < t1->GetEntries(); idx ++ ){
		t1->GetEntry(idx);
		for( int h_idx = 0 ; h_idx < 10; h_idx ++ ){
			h_wgt[(int) floor(10*(bdt+1)/2)]->Fill(wgt);
		}
	}
	for( int idx = 0; idx < 10; idx ++){
		h_wgt[idx]->Scale(1/h_wgt[idx]->GetEntries());
	}
	std::cout << "dbg" << std::endl;
	return h_wgt;
};

std::vector<TH1D*> weight_vs_bdt(long ts, int state, int pl, int ph){
	auto res= hist_weight_vs_bdt(ts, state, pl, ph);
	double bin_high = (state ==2 || state ==1 ) ? 1 : 1000;
	std::vector<TF1*> fit_model;
	ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2", "Simplex");
	for( int idx = 0; idx < 10 ; idx ++){
		fit_model.push_back( new TF1(Form("pois_idx%d",idx), "pol9", 0, bin_high));
		res[idx]->Fit(Form("pois_idx%d",idx),"MFR", "", 0, bin_high);
	}
	
	return res;

}
