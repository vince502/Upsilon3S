#include <cstdlib>
#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

void BDTClassifierApplication(string fname, long ts){

  TMVA::Tools::Instance();
  TMVA::Reader *reader = new TMVA::Reader("!Silent");
  bool IDonly = true;
  bool MoreVar, IDvar;
  MoreVar = (bool) std::stoi(fname.substr(fname.find("MoreVar")+7,1));
  IDvar = (bool) std::stoi(fname.substr(fname.find("IDv")+3,1));

  Double_t mass, pt, y, pt1, pt2, eta1, eta2, dxy1, dxy2, dz1, dz2, QQVtxProb,QQMassErr; 
  Int_t cBin,  nPixWMea1, nPixWMea2, nTrkWMea1, nTrkWMea2,nMuValHits1, nMuValHits2, StationsMatched1, StationsMatched2;
  Float_t cBin_f,  nPixWMea1_f, nPixWMea2_f, nTrkWMea1_f, nTrkWMea2_f,nMuValHits1_f, nMuValHits2_f, StationsMatched1_f, StationsMatched2_f, mass_f, pt_f, y_f, pt1_f, pt2_f, eta1_f, eta2_f, dxy1_f, dxy2_f, dz1_f, dz2_f, QQVtxProb_f,QQMassErr_f;
  if(!IDonly){
  reader->AddVariable("pt1", &pt1_f);
  reader->AddVariable("pt2", &pt2_f);
  reader->AddVariable("eta1", &eta1_f);
  reader->AddVariable("eta2", &eta2_f);
  }
  if(IDvar){
    reader->AddVariable("nPixWMea1",&nPixWMea1_f);
    reader->AddVariable("nPixWMea2",&nPixWMea2_f);
    reader->AddVariable("nTrkWMea1",&nTrkWMea1_f);
    reader->AddVariable("nTrkWMea2",&nTrkWMea2_f);
    reader->AddVariable("dxy1", &dxy1_f);
    reader->AddVariable("dxy2", &dxy2_f);
    reader->AddVariable("dz1",&dz1_f);
    reader->AddVariable("dz2",&dz2_f);
    if(!MoreVar){
      reader->AddSpectator("QQVtxProb", &QQVtxProb_f);
    }
    if(IDonly){
      reader->AddSpectator("pt1",  &pt1_f);
      reader->AddSpectator("pt2",  &pt2_f);
      reader->AddSpectator("eta1",  &eta1_f);
      reader->AddSpectator("eta2",  &eta2_f);
    }
  }
  if(MoreVar){
   // reader->AddVariable("nTrkHits1", "nTrk Hit 1", "I"_f);
   // reader->AddVariable("nTrkHits2", "nTrk Hit 2", "I"_f);
   // reader->AddVariable("nPixValHits1", "nPix Valid Hits 1", "I"_f);
   // reader->AddVariable("nPixValHits2", "nPix Valid Hits 2", "I"_f);
    reader->AddVariable("nMuValHits1", &nMuValHits1_f);
    reader->AddVariable("nMuValHits2", &nMuValHits2_f);
//    reader->AddVariable("StationsMatched1", &StationsMatched1_f);
//    reader->AddVariable("StationsMatched2", &StationsMatched2_f);
    reader->AddVariable("QQMassErr",&QQMassErr_f);

    reader->AddSpectator("QQVtxProb",&QQVtxProb_f);
 //   reader->AddVariable("ctau3D", "F"_f);
//    reader->AddVariable("normChi2_global1", "F"_f);
//    reader->AddVariable("normChi2_global2", "F"_f);
    if(IDonly){
      reader->AddSpectator("pt1", &pt1_f);
      reader->AddSpectator("pt2", &pt2_f);
      reader->AddSpectator("eta1", &eta1_f);
      reader->AddSpectator("eta2", &eta2_f);
    }
  }

  //Spectator Call, Will NOT Use For Training
  reader->AddSpectator("cBin",&cBin_f);
  reader->AddSpectator("mass",&mass_f);
  reader->AddSpectator("pt",&pt_f);
  reader->AddSpectator("y",&y_f);

  TString dir = "dataset/weights/";
  TString prefix = "TMVA_BDT_Classifier_BDT_train_";

  TString methodName = (Form("BDT_train_%ld",ts));
  TString weightfile = dir+prefix + TString::Format("%ld",ts)+ TString(".weights.xml");
  reader->BookMVA( methodName, weightfile );
  TH1F* histBDT = new TH1F( "MVA_BDT", "MVA_BDT", 100, -1, 1);
  TFile* input(0);
  input = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC0.root", "open");

  TTree* tree = (TTree*) input->Get("tree");
  tree->SetBranchAddress("cBin", &cBin);
  tree->SetBranchAddress("pt", &pt);
  tree->SetBranchAddress("y", &y);
  tree->SetBranchAddress("mass", &mass);
  tree->SetBranchAddress("pt1", &pt1);
  tree->SetBranchAddress("pt2", &pt2);
  tree->SetBranchAddress("eta1", &eta1);
  tree->SetBranchAddress("eta2", &eta2);
  tree->SetBranchAddress("nPixWMea1", &nPixWMea1);
  tree->SetBranchAddress("nPixWMea2", &nPixWMea2);
  tree->SetBranchAddress("nTrkWMea1", &nTrkWMea1);
  tree->SetBranchAddress("nTrkWMea2", &nTrkWMea2);
  tree->SetBranchAddress("dxy1", &dxy1);
  tree->SetBranchAddress("dxy2", &dxy2);
  tree->SetBranchAddress("dz1", &dz1);
  tree->SetBranchAddress("dz2", &dz2);
  tree->SetBranchAddress("QQVtxProb", &QQVtxProb);
  tree->SetBranchAddress("QQMassErr", &QQMassErr);
  tree->SetBranchAddress("nMuValHits1", &nMuValHits1);
  tree->SetBranchAddress("nMuValHits2", &nMuValHits2);
  tree->SetBranchAddress("StationsMatched1", &StationsMatched1);
  tree->SetBranchAddress("StationsMatched2", &StationsMatched2);
  
  Double_t effS = 0.7;
  Double_t BDT;

  TTreeReader newreader("tree", input);
  TFile *target = new TFile(Form("./BDTAppliedData/BDTApp_%ld.root",ts),"recreate");
  TTree* outtree = tree->CloneTree(0);
  outtree->Branch("BDT", &BDT, "BDT/D");


  for(Long64_t ievt=0; ievt< tree->GetEntries();ievt++){
    tree->GetEntry(ievt);
    outtree->GetEntry(ievt);
    if (ievt%10000 == 0) std::cout << "--- ... Processing event: " << ievt << "\r";
    cBin_f=cBin;pt_f=pt;y_f=y;mass_f=mass;pt1_f=pt1;pt2_f=pt2;eta1_f=eta1;eta2_f=eta2;nPixWMea1_f=nPixWMea1;nPixWMea2_f=nPixWMea2;nTrkWMea1_f=nTrkWMea1;nTrkWMea2_f=nTrkWMea2;dxy1_f=dxy1;dxy2_f=dxy2;dz1_f=dz1;dz2_f=dz2;QQVtxProb_f=QQVtxProb;nMuValHits1_f=nMuValHits1;nMuValHits2_f=nMuValHits2;StationsMatched1_f=StationsMatched1;
  BDT=reader->EvaluateMVA( Form("BDT_train_%ld",ts));
  outtree->Fill();
  }
  outtree->Write();
  std::cout << "done Writiing " << Form("BDTApp_%ld.root",ts) << std::endl;
  target->Close();






}
