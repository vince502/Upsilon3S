#include <iostream>
#include "TFile.h"
#include "TROOT.h"
#include "TH1D.h"
#include <string>

void Draw_CentRatio(){
 TFile* fdata = new TFile("../skimmedFiles/OniaFlowSkim_forCent_TrigS13_PDty1_Switch0.root","READ");
 TFile* fmc = new TFile("../skimmedFiles/OniaSkim_forCent_TrigS13_MC_Switch0.root","READ");

 TTree* tdata = (TTree*) fdata->Get("mmepevt");
 TTree* tmc = (TTree*) fmc->Get("mmepevt");
 
 TH1D *hd, *hm;
 hd = new TH1D("hd","", 200, 0, 200);
 hm = new TH1D("hm","", 200, 0, 200);
 const int MaxDimu =1000 ;
 Int_t nevtd = -1;
 Int_t nevtm = -1;
 int cBind, cBinm, nDimuD, nDimuM;
 Double_t weight;
 TBranch *b_cBind, *b_cBinm, *b_weight, *b_nDimuD, *b_nDimuM;
 int wc;
 float massD[MaxDimu];
 float massM[MaxDimu];
 TBranch *b_massD, *b_massM;

 tdata->SetBranchAddress("cBin", &cBind, &b_cBind);
 tdata->SetBranchAddress("nDimu", &nDimuD, &b_nDimuD);
 tdata->SetBranchAddress("mass", &massD, &b_massD);
 Float_t pt1d; TBranch* b_pt1d;
 tdata->SetBranchAddress("pt1", &pt1d, &b_pt1d); 
 Float_t pt2d; TBranch* b_pt2d;
 tdata->SetBranchAddress("pt2", &pt2d, &b_pt2d); 
 Float_t eta1d; TBranch* b_eta1d;
 tdata->SetBranchAddress("eta1", &eta1d, &b_eta1d); 
 Float_t eta2d; TBranch* b_eta2d;
 tdata->SetBranchAddress("eta2", &eta2d, &b_eta2d); 
 tmc->SetBranchAddress("cBin", &cBinm, &b_cBinm);
 tmc->SetBranchAddress("weight", &weight, &b_weight);
 tmc->SetBranchAddress("nDimu", &nDimuM, &b_nDimuM);
 tmc->SetBranchAddress("mass", &massM, &b_massM);
 Float_t pt1m; TBranch* b_pt1m;
 tmc->SetBranchAddress("pt1", &pt1m, &b_pt1m); 
 Float_t pt2m; TBranch* b_pt2m;
 tmc->SetBranchAddress("pt2", &pt2m, &b_pt2m); 
 Float_t eta1m; TBranch* b_eta1m;
 tdata->SetBranchAddress("eta1", &eta1m, &b_eta1m); 
 Float_t eta2m; TBranch* b_eta2m;
 tdata->SetBranchAddress("eta2", &eta2m, &b_eta2m); 

 nevtd = tdata->GetEntries();
 nevtm = tmc->GetEntries();
 std::cout << "Total Events : (Data  " << nevtd << "), (MC "<< nevtm << ")"<<  std::endl;

 for(int iev = 0; iev < nevtd; ++iev){
  tdata->GetEntry(iev);
  for(int idi = 0; idi < nDimuD; ++idi){
    if(cBind <= 180 && (massD[idi] >=9.2 && massD[idi]<=9.8) && (pt1d >3.5 && pt2d >3.5)&& ( eta1d > -2,4 && eta1d <2.4 ) && (eta2d > -2.4 && eta2d <2.4) ) hd->Fill(cBind);
  }
 }

 for(int iev = 0; iev < nevtm; ++iev){
  tmc->GetEntry(iev);
    for(int idi = 0; idi < nDimuM; ++idi){
      if(cBinm <=180 && (massM[idi] >= 9.2 && massM[idi]<= 9.8)&& (pt1m >3.5 && pt2m >3.5)&& ( eta1m > -2,4 && eta1m <2.4 ) && (eta2m > -2.4 && eta2m <2.4)) hm->Fill(cBinm,weight);
    }
 }
 TH1D* hn = (TH1D*) hd->Clone("hn"); 
 hn->Sumw2();
 hd->SetMarkerStyle(20);
 hd->SetMarkerColor(kRed);
 hd->SetLineColor(kRed);
 hm->SetMarkerStyle(22);
 hm->SetMarkerColor(kBlue);
 hm->SetLineColor(kBlue);
 
 gStyle->SetOptStat(0);

 TCanvas* c1 =new TCanvas("c1","Centrality Ratio",800,900);
 TPad* pd = new TPad("pd", "", 0,0.31, 1,1);
 TPad* pr = new TPad("pr", "", 0,0, 1,0.3);
 pd->SetBottomMargin(0);
 pr->SetTopMargin(0);
 pr->SetBottomMargin(0.1);
 pd->SetGridx();
 pr->SetGridx();
 c1->cd();
 pd->Draw(); pr->Draw();
 pd->cd();
 TLegend* leg = new TLegend(0.7,0.7,0.95,0.9);
 leg->AddEntry(hd, "Data", "lep");
 leg->AddEntry(hm, "MC", "lep");
 gStyle->SetLegendBorderSize(0);
 gStyle->SetLegendTextSize(0.04);
 hm->SetTitle("Centrality Ratio");
 hm->GetYaxis()->SetTitle("arbitrary unit");
 hm->DrawNormalized();
 hd->DrawNormalized("same");
 leg->Draw();
 pr->cd();

 hn->Divide(hn,hm,hm->GetSumOfWeights(),hn->GetEntries());
 pr->SetLogy();
 hn->SetTitle("");
 hn->SetStats(kFALSE);
 hn->SetMarkerColor(kBlack);
 hn->SetLineColor(kBlack);
 hn->GetYaxis()->SetTitle("Ratio Data/MC");
 hn->GetYaxis()->SetTitleSize(0.07);
 hn->SetLabelSize(1.2);
 hn->GetYaxis()->SetMoreLogLabels(kTRUE);
 hn->GetYaxis()->SetRangeUser(0.4,4);
 hn->Draw();
 c1->SaveAs("CentralityRatio.pdf");
 c1->Close();
}
