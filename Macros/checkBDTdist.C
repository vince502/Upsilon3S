#include "../.workdir.h"
#include "../BDT/bininfo.h"
#include "../script_tools.h"
#include "../plots/measurement.cxx"

void checkBDTdist(){
	TFile* f = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_200019111111.root", workdir.Data()));
	TFile* f2 = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_400019111111.root", workdir.Data()));
	TTree* t  = (TTree*) f->Get("tree");
	TTree* t2  = (TTree*) f2->Get("tree");
	TH1D* h1 = new TH1D("h1", "", 120, 8, 14);
	TH1D* h2 = new TH1D("h2", "", 120, 8, 14);
	TH1D* h3 = new TH1D("h3", "", 120, 8, 14);
	TH1D* h4 = new TH1D("h4", "", 120, 8, 14);
	TH1D* h5 = new TH1D("h5", "", 120, 8, 14);

	TH1D* h1_2 = new TH1D("h1_2", "", 120, 8, 14);

	int pl = 0 ;
	int ph = 30 ;
	int bpl = 0 ;
	int bph = 4 ;

	//long ts1 = 200019111111;
	long ts1 = 2100019111111;
	long ts2 = 400019111111;
	ana_bins ab1 = ana_bm_comb_ub["3p"][0];
	ana_bins ab2 = ana_bm_comb_ub_ib["3p"][0];
	double bl1 = Get_BDT(ts_alias(ts1), 3, 3, pl, ph, pl, ph, 0, 181);
	double bl2 = Get_BDT(ts_alias(ts2), 3, 3, pl, ph, pl, ph, 0, 181);
	double bcut1 = 0.2649;
	//double bcut2 = 0.2020;
	double bcut2 = 0.2229;

	bcut1 = bl1;
	bcut2 = bl2;

	double mass, pt, bdt1, bdt2;
	double weight = 1.;
	t->SetBranchAddress("mass", &mass);
	t->SetBranchAddress("weight", &weight);
	t->SetBranchAddress("pt", &pt);
	t->SetBranchAddress("BDTY3Spt0to30", &bdt1);
	t->SetBranchAddress(Form("BDTY3Spt%dto%d", bpl, bph), &bdt2);

	double mass_2, pt_2, bdt1_2, bdt2_2;
	double weight_2 = 1.;
	t2->SetBranchAddress("mass", &mass_2);
	t2->SetBranchAddress("weight", &weight_2);
	t2->SetBranchAddress("pt", &pt_2);
	t2->SetBranchAddress("BDTY3Spt0to30", &bdt1_2);
	t2->SetBranchAddress(Form("BDTY3Spt%dto%d", bpl, bph), &bdt2_2);

	for( auto idx : ROOT::TSeqI(t->GetEntries() ) ){
		t->GetEntry(idx);
		t2->GetEntry(idx);
		if( ( pt < ph & pt > pl ) ){
			if( bdt1 > bcut1 && bdt2 > bcut2){
				h1->Fill(mass, weight);
			}
			if( bdt1 > bcut1 && bdt2 < bcut2){
				h2->Fill(mass, weight);
			}
			if( bdt1 < bcut1 && bdt2 < bcut2){
				h3->Fill(mass, weight);
			}
			if( bdt1 > bcut1 ){
				h4->Fill(mass, weight);
			}
			if( bdt2 > bcut2 ){
				h5->Fill(mass, weight);
			}
		}

		if( ( pt_2 < ph & pt_2 > pl ) && ( pt < ph & pt > pl ) ){
			if( (bdt1_2 > bcut2 && bdt1 < bcut1)){
		//	if( (bdt1 > bcut1 && bdt2 > bcut2) && (bdt1_2 > bcut1 && bdt2_2 > bcut2)){
				h1_2->Fill(mass_2, weight);
			}
		}
	}

	h1->SetLineColor(kBlue);
	h2->SetLineColor(kRed);
	h3->SetLineColor(kBlack);

	h1->SetMarkerColor(kBlue);
	h2->SetMarkerColor(kRed);
	h3->SetMarkerColor(kBlack);

	h1->SetMarkerStyle(kFullCircle);
	h2->SetMarkerStyle(kFullCircle);
	h3->SetMarkerStyle(kFullCircle);

//	h3->GetYaxis()->SetRangeUser(0, 0.02);

	TCanvas* c00 = new TCanvas("c00", "", 640*3, 480*2);
	c00->Divide(3,2);
//	TCanvas* c0 = new TCanvas("c0", "", 640, 480);
//	TCanvas* c1 = new TCanvas("c1", "", 640, 480);
//	TCanvas* c2 = new TCanvas("c2", "", 640, 480);
//	TCanvas* c3 = new TCanvas("c3", "", 640, 480);
	c00->cd();
	c00->cd(1); h1->Draw("ple");
	c00->cd(2); h2->Draw("ple");
	c00->cd(3); h3->Draw("ple");
	c00->cd(4); h4->Draw("ple");
	c00->cd(5); h5->Draw("ple");
	c00->cd(6); h1_2->Draw("ple");

	auto sh1 = (TH1D*) h1->Clone("sh1");sh1->Scale(1/h1->GetSum() );
	auto sh2 = (TH1D*) h2->Clone("sh2");sh2->Scale(1/h2->GetSum() );
	auto sh3 = (TH1D*) h3->Clone("sh3");sh3->Scale(1/h3->GetSum() );
	auto sh4 = (TH1D*) h4->Clone("sh4");sh4->Scale(1/h4->GetSum() );
	auto sh5 = (TH1D*) h5->Clone("sh5");sh5->Scale(1/h5->GetSum() );
//	c00->cd(6); sh1->Draw("ple"); sh2->Draw("same"); sh3->Draw("same");
//	c0->cd();
//	h3->Draw("ple");
//	h2->Draw("same");
//	h1->Draw("same");
//	c1->cd();
//	h1->Draw("ple");
//	c2->cd();
//	h2->Draw("ple");
//	c3->cd();
//	h3->Draw("ple");
};
