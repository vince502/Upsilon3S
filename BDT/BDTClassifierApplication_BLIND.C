#include <cstdlib>
#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "TXMLDocument.h"
#include "blindsearch.cxx"


void BDTClassifierApplication_BLIND(long ts, int isMC = 0){
  std::pair<int,int> _bf = blindpair(ts);
  int whichtree = _bf.second;
  if (whichtree >5) {std::cout << "tree selection wrong? " << std::endl; return; }

  TMVA::Tools::Instance();
  TMVA::Reader *reader = new TMVA::Reader("!Silent");
  TXMLEngine xml;
  XMLDocPointer_t xmldoc = xml.ParseFile(Form("./dataset/weights/TMVA_BDT_Classifier_BDT_train_%ld.weights.xml", ts));
  XMLDocPointer_t mainnode = xml.DocGetRootElement(xmldoc);

//  bool IDonly = true;
//  bool MoreVar, IDvar;
//  MoreVar = (bool) std::stoi(fname.substr(fname.find("MoreVar")+7,1));
//  IDvar = (bool) std::stoi(fname.substr(fname.find("IDv")+3,1));

  Double_t mass, pt, y, pt1, pt2, eta1, eta2, dxy1, dxy2, dz1, dz2, QQVtxProb,QQMassErr; 
  Int_t cBin,  nPixWMea1, nPixWMea2, nTrkWMea1, nTrkWMea2,nMuValHits1, nMuValHits2, StationsMatched1, StationsMatched2;
  std::vector<string> namelist = {"mass", "pt", "y", "pt1", "pt2", "eta1", "eta2", "dxy1", "dxy2", "dz1", "dz2", "QQVtxProb", "QQMassErr", "cBin",  "nPixWMea1", "nPixWMea2", "nTrkWMea1", "nTrkWMea2","nMuValHits1", "nMuValHits2", "StationsMatched1", "StationsMatched2"};
  std::map<string, Double_t*>mdouble;
  std::map<string, Int_t*>mint;
  mdouble["mass"] = &mass;
  mdouble["pt"] = &pt;
  mdouble["y"] = &y;
  mdouble["pt1"] = &pt1;
  mdouble["pt2"] = &pt2;
  mdouble["eta1"] = &eta1;
  mdouble["eta2"] = &eta2;
  mdouble["dxy1"] = &dxy1;
  mdouble["dxy2"] = &dxy2;
  mdouble["dz1"] = &dz1;
  mdouble["dz2"] = &dz2;
  mdouble["QQVtxProb"] = &QQVtxProb;
  mdouble["QQMassErr"] = &QQMassErr;
  mint["cBin"] = &cBin;
  mint["nPixWMea1"] = &nPixWMea1;
  mint["nPixWMea2"] = &nPixWMea2;
  mint["nTrkWMea1"] = &nTrkWMea1;
  mint["nTrkWMea2"] = &nTrkWMea2;
  mint["nMuValHits1"] = &nMuValHits1;
  mint["nMuValHits2"] = &nMuValHits2;
  mint["StationsMatched1"] = &StationsMatched1;
  mint["StationsMatched2"] = &StationsMatched2;

  XMLNodePointer_t nodevar = xml.GetChild(mainnode);
  while( strcmp(xml.GetNodeName(nodevar),"Variables")!=0){
  nodevar = xml.GetNext(nodevar);
  }
  XMLNodePointer_t nodespc = xml.GetChild(mainnode);
  while( strcmp(xml.GetNodeName(nodespc),"Spectators")!=0){
  nodespc = xml.GetNext(nodespc);
  }
  int nvar = stoi(xml.GetAttrValue(xml.GetFirstAttr(nodevar)));
  int nspc = stoi(xml.GetAttrValue(xml.GetFirstAttr(nodespc)));
  Float_t varptr[nvar];
  Float_t spcptr[nspc];
  std::map<TString, Float_t*>mvar;
  std::map<TString, Float_t*>mspc;
  std::vector<TString> listvar;
  std::vector<TString> listspc;
  XMLNodePointer_t childvar = xml.GetChild(nodevar);
  XMLNodePointer_t childspc = xml.GetChild(nodespc);
  TString varname, spcname;
  for(int i=0; i < nvar; i++){
    varname =xml.GetAttr(childvar, "Expression"); 
    std::cout << varname << std::endl;
    mvar[varname]=&varptr[i];
    reader->AddVariable(varname, &varptr[i]);
    childvar = xml.GetNext(childvar);
  }
  for(int i=0; i < nspc; i++){
    spcname =(xml.GetAttr(childspc, "Expression"));
    mspc[spcname]=&spcptr[i];
    reader->AddSpectator(spcname, &spcptr[i]);
    childspc = xml.GetNext(childspc);
  }
  

  TString dir = "dataset/weights/";
  TString prefix = "TMVA_BDT_Classifier_BDT_train_";

  TString methodName = (Form("BDT_train_%ld",ts));
  TString weightfile = dir+prefix + TString::Format("%ld",ts)+ TString(".weights.xml");
  reader->BookMVA( methodName, weightfile );
  TH1F* histBDT = new TH1F( "MVA_BDT", "MVA_BDT", 100, -1, 1);
  TString dfname = (isMC==2) ? "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_1S.root" : (whichtree==0) ? "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC0_NewSkimWithTrackerMuonCut_QQVtxProb5Perc_AccPt3p5.root" : "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC0_NewSkimWithTrackerMuonCut_QQVtxProb5Perc_AccPt3p5_ForBLIND.root";
  //TString mfname = "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1.root";
  TString mfname =  "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_QQVtxProb1percAccPt3p5Cut.root";
  TFile* input(0);
  input = new TFile((isMC==1) ? mfname.Data() : dfname.Data(), "open");
  TString outtext = input->GetName();
  std::cout << "Using file: " << outtext << std::endl;


  TTree* tree;
  tree = (whichtree==0) ? (TTree*) input->Get(Form("tree")) : (TTree*) input->Get(Form("tree%d",whichtree));
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

//  TTreeReader newreader("tree", input);
  TFile *target;
  if (isMC ==0) target =new TFile(Form("./BDTAppliedData/BDTApp_%ld.root",ts),"recreate");
  else if (isMC==1) target =new TFile(Form("./BDTAppliedData/BDTApp_%ld_MC.root",ts),"recreate");
  else if (isMC==2) target = new TFile(Form("./BDTAppliedData/BDTApp_BLIND_Custom.root"),"recreate");
  TTree* outtree = tree->CloneTree(0);
  outtree->Branch("BDT", &BDT, "BDT/D");

  for(Long64_t ievt=0; ievt< tree->GetEntries();ievt++){
    tree->GetEntry(ievt);
    outtree->GetEntry(ievt);
    if (ievt%10000 == 0) std::cout << "--- ... Processing event: " << ievt << "\r";
    for( string name : namelist ){
      if( mvar[name] !=nullptr){
	if( mdouble[name] !=nullptr) *mvar[name] = *mdouble[name];
	if( mint[name] !=nullptr) *mvar[name] = *mint[name];
      }
      if( mspc[name] !=nullptr){
	if( mdouble[name] !=nullptr) *mspc[name] = *mdouble[name];
	if( mint[name] !=nullptr) *mspc[name] = *mint[name];
      }
    }
  BDT=reader->EvaluateMVA( Form("BDT_train_%ld",ts));
  outtree->Fill();
  }
  outtree->SetName("tree");
  outtree->Write();
  std::cout << "done Writiing " << target->GetName()<< std::endl;
  target->Close();

}
