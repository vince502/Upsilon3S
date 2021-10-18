#include <iostream>
#include <cstdlib>
#include "TROOT.h"
#include "TFile.h"
#include "../.workdir.h"

std::vector<TH1D*> DrawBDTdistribution(long ts, string s = ""){
  TFile* input = TFile::Open(Form("%s/BDT/BDTResult/BDTresultY3S_%ld_BLIND.root", workdir.Data(), ts));
  TTree* t1 = (TTree*) input->Get("dataset1/TrainTree");
  TTree* t2 = (TTree*) input->Get("dataset2/TrainTree");

  int classID1, classID2;
  float pt1, mass1, bdt1, cbin1;
  float pt2, mass2, bdt2, cbin2;

  t1->SetBranchAddress("pt", &pt1);
  t1->SetBranchAddress("mass", &mass1);
  t1->SetBranchAddress("BDT", &bdt1);
  t1->SetBranchAddress("cBin", &cbin1);
  t1->SetBranchAddress("classID", &classID1);
  
  t2->SetBranchAddress("pt", &pt2);
  t2->SetBranchAddress("mass", &mass2);
  t2->SetBranchAddress("BDT", &bdt2);
  t2->SetBranchAddress("cBin", &cbin2);
  t2->SetBranchAddress("classID", &classID2);

  TH1D *h_sig_low, *h_sig_high, *h_bkg_low, *h_bkg_high;
  TH1D *h_sig_low2, *h_sig_high2, *h_bkg_low2, *h_bkg_high2;
  h_sig_low = new TH1D("BDTsl", "", 100, -0.5, 0.5);
  h_sig_high = new TH1D("BDTsh", "", 100, -0.5, 0.5);

  h_bkg_low = new TH1D("BDTbl", "", 100, -0.5, 0.5);
  h_bkg_high = new TH1D("BDTbh", "", 100, -0.5, 0.5);

  h_sig_low2 = new TH1D("BDTsl2", "", 100, -0.5, 0.5);
  h_sig_high2 = new TH1D("BDTsh2", "", 100, -0.5, 0.5);

  h_bkg_low2 = new TH1D("BDTbl2", "", 100, -0.5, 0.5);
  h_bkg_high2 = new TH1D("BDTbh2", "", 100, -0.5, 0.5);

  for(int idx = 0; idx< t1->GetEntries(); idx++){
    t1->GetEntry(idx);
    if(classID1 == 0){
      if(pt1<6){
        h_sig_low->Fill(bdt1);
      }
      if(pt1>6&&pt1<30){
        h_sig_high->Fill(bdt1);
      }
    }
    if(classID1 == 1){
      if(pt1<6){
        h_bkg_low->Fill(bdt1);
      }
      if(pt1>6&&pt1<30){
        h_bkg_high->Fill(bdt1);
      }
    }
  }

  for(int idx = 0; idx< t2->GetEntries(); idx++){
    t2->GetEntry(idx);
    if(classID2 == 0){
      if(pt2<6){
        h_sig_low2->Fill(bdt2);
      }
      if(pt2>6&&pt2<30){
        h_sig_high2->Fill(bdt2);
      }
    }
    if(classID2 == 1){
      if(pt2<6){
        h_bkg_low2->Fill(bdt2);
      }
      if(pt2>6&&pt2<30){
        h_bkg_high2->Fill(bdt2);
      }
    }
  }
  h_sig_low->Scale(1/h_sig_low->GetEntries());
  h_sig_high->Scale(1/h_sig_high->GetEntries());
  h_bkg_low->Scale(1/h_bkg_low->GetEntries());
  h_bkg_high->Scale(1/h_bkg_high->GetEntries());

  h_sig_low2->Scale(1/h_sig_low2->GetEntries());
  h_sig_high2->Scale(1/h_sig_high2->GetEntries());
  h_bkg_low2->Scale(1/h_bkg_low2->GetEntries());
  h_bkg_high2->Scale(1/h_bkg_high2->GetEntries());
  return std::vector<TH1D*>{h_sig_low,h_sig_high,h_bkg_low,h_bkg_high, h_sig_low2,h_sig_high2,h_bkg_low2,h_bkg_high2};
};

std::vector<TH1D*> DrawBDTdistribution(long ts, int cbincut = 40){
  TFile* input = TFile::Open(Form("%s/BDT/BDTResult/BDTresultY3S_%ld_BLIND.root", workdir.Data(), ts));
  TTree* t1 = (TTree*) input->Get("dataset1/TrainTree");
  TTree* t2 = (TTree*) input->Get("dataset2/TrainTree");

  int classID1, classID2;
  float pt1, mass1, bdt1, cbin1;
  float pt2, mass2, bdt2, cbin2;

  t1->SetBranchAddress("pt", &pt1);
  t1->SetBranchAddress("mass", &mass1);
  t1->SetBranchAddress("BDT", &bdt1);
  t1->SetBranchAddress("cBin", &cbin1);
  t1->SetBranchAddress("classID", &classID1);
  
  t2->SetBranchAddress("pt", &pt2);
  t2->SetBranchAddress("mass", &mass2);
  t2->SetBranchAddress("BDT", &bdt2);
  t2->SetBranchAddress("cBin", &cbin2);
  t2->SetBranchAddress("classID", &classID2);

  TH1D *h_sig_low, *h_sig_high, *h_bkg_low, *h_bkg_high;
  h_sig_low = new TH1D("BDTsl", "", 100, -0.5, 0.5);
  h_sig_high = new TH1D("BDTsh", "", 100, -0.5, 0.5);

  h_bkg_low = new TH1D("BDTbl", "", 100, -0.5, 0.5);
  h_bkg_high = new TH1D("BDTbh", "", 100, -0.5, 0.5);

  for(int idx = 0; idx< t1->GetEntries(); idx++){
    t1->GetEntry(idx);
    if(classID1 == 0){
      if(cbin1 < cbincut){
        h_sig_low->Fill(bdt1);
      }
      if(cbin1 >= cbincut){
        h_sig_high->Fill(bdt1);
      }
    }
    if(classID1 == 1){
      if(cbin1 < cbincut){
        h_bkg_low->Fill(bdt1);
      }
      if(cbin1 >= cbincut){
        h_bkg_high->Fill(bdt1);
      }
    }
  }

  for(int idx = 0; idx< t2->GetEntries(); idx++){
    t2->GetEntry(idx);
    if(classID2 == 0){
      if(cbin2 < cbincut){
        h_sig_low->Fill(bdt2);
      }
      if(cbin2 >= cbincut){
        h_sig_high->Fill(bdt2);
      }
    }
    if(classID2 == 1){
      if(cbin2 < cbincut){
        h_bkg_low->Fill(bdt2);
      }
      if(cbin2 >= cbincut){
        h_bkg_high->Fill(bdt2);
      }
    }
  }
  h_sig_low->Scale(1/h_sig_low->GetEntries());
  h_sig_high->Scale(1/h_sig_high->GetEntries());
  h_bkg_low->Scale(1/h_bkg_low->GetEntries());
  h_bkg_high->Scale(1/h_bkg_high->GetEntries());
  return std::vector<TH1D*>{h_sig_low,h_sig_high,h_bkg_low,h_bkg_high};
}
