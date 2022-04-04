#include "../BDT/bininfo.h"
#include "../.workdir.h"

void DrawBDT(long ts = 10000000016){
	TFile* f_in = TFile::Open(Form("%s/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT.root",workdir.Data(),ts));

	RooDataSet* ds = (RooDataSet*) f_in->Get("dataset_Y3Spt0to30");
	auto ds_reduced_full = ds->reduce("mass>8 && pt1 >3.5 && pt2 > 3.5");
	TH1* hist_ds_full =  ds_reduced_full->createHistogram("BDT", 200);
	hist_ds_full->SetName("hist_ds_full");
	hist_ds_full->SetTitle("Normalized BDT distribution of data");
	auto ds_reduced_sb = ds->reduce(" (mass<8.6 || mass > 10.7) && pt1 >3.5 && pt2 > 3.5");
	TH1* hist_ds_sb =  ds_reduced_sb->createHistogram("BDT", 200);
	hist_ds_sb->SetName("hist_ds_sb");
	auto hist_full_copy = (TH1*) hist_ds_full->Clone("hist_full_copy");
	hist_full_copy->Add(hist_ds_sb, -1);
	
	hist_ds_full->Scale(1/hist_ds_full->Integral() );
	hist_ds_sb->Scale(1/hist_ds_sb->Integral() );
	hist_full_copy->Scale(1/hist_full_copy->Integral() );

	hist_ds_sb->SetStats(0);
	hist_ds_full->SetStats(0);
	hist_full_copy->SetStats(0);

	TCanvas* c1 = new TCanvas("c1", "", 700, 600);
	c1->cd();
	c1->SetLeftMargin(0.13);
	hist_ds_full->SetMarkerStyle(kFullCircle);
	hist_ds_full->SetMarkerSize(0.8);
	hist_ds_full->GetYaxis()->SetTitleOffset(1.5);
	hist_ds_full->GetYaxis()->SetRangeUser(0,0.04);
//	hist_ds_full->GetYaxis()->SetRangeUser(-0.005,0.04);
	hist_ds_full->Draw("pe");
	hist_full_copy->SetLineColor(kMagenta-3);
	hist_full_copy->SetMarkerColor(kMagenta-3);
	hist_full_copy->SetMarkerStyle(kFullCircle);
	hist_full_copy->SetMarkerSize(0.8);
	hist_full_copy->Draw("same");
	hist_ds_sb->SetLineColor(kRed-3);
	hist_ds_sb->SetMarkerColor(kRed-3);
	hist_ds_sb->SetMarkerStyle(kFullCircle);
	hist_ds_sb->SetMarkerSize(0.8);
	hist_ds_sb->Draw("same");

	TLegend* leg= new TLegend(0.55, 0.5, 0.8, 0.75);
	leg->SetBorderSize(0);
	leg->AddEntry(hist_ds_full, "full mass range", "pe");
	leg->AddEntry(hist_ds_sb, "training mass range", "pe");
	leg->AddEntry(hist_full_copy, "signal region", "pe");
	leg->Draw();

	c1->SaveAs("../checkout/BDTmass_dist.pdf");

}
