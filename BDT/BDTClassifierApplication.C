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
#include "bininfo.h"


void BDTClassifierApplication(long ts, int isMC = 0){
  std::pair<int,int> _bf = blindpair(ts);
  int whichtree = _bf.second;
  if (whichtree >5) {std::cout << "if BLIND, is tree selection wrong? " << std::endl; return; }
  if (whichtree !=0 && whichtree <6) {std::cout <<"Application in BLIND tree"<<whichtree<< std::endl;}

  TMVA::Tools::Instance();
  TMVA::Reader *reader = new TMVA::Reader("!Silent");
  TXMLEngine xml;
  XMLDocPointer_t xmldoc = xml.ParseFile(Form("./dataset/weights/TMVA_BDT_Classifier_BDT_train_%ld.weights.xml", ts));
  XMLDocPointer_t mainnode = xml.DocGetRootElement(xmldoc);

  TString dfname = (isMC==2) ? "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_1S.root" : (whichtree==0) ? "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC0_v210416.root" : "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC0_v210416_ForBLIND.root";
      TString mfname =  "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_v210416.root";

  TFile* input(0);
  input = new TFile((isMC==1) ? mfname.Data() : dfname.Data(), "open");
  TTree* tree;
  tree = (whichtree==0|| isMC ==1 ) ? (TTree*) input->Get(Form("tree")) : (TTree*) input->Get(Form("tree%d",whichtree));
  
  std::vector<string> dnamelist;
  std::vector<string> inamelist;
  TObjArray* blist = tree->GetListOfBranches();
  for (auto content : *blist){
    string Titler = content->GetTitle();
    char datype = Titler.back();
    if( datype=='D' ){dnamelist.push_back(content->GetName());}
    else if ( datype=='I' ){inamelist.push_back(content->GetName());}
    else continue;
  }
//  std::vector<string> dep_dnamelist = {"mass", "pt", "y", "pt1", "pt2", "eta1", "eta2", "dxy1", "dxy2", "dz1", "dz2", "QQVtxProb", "QQMassErr" };
//  std::vector<string> dep_inamelist = {"cBin",  "nPixWMea1", "nPixWMea2", "nTrkWMea1", "nTrkWMea2","nMuValHits1", "nMuValHits2", "StationsMatched1", "StationsMatched2"};
  Double_t *dmass = new Double_t[dnamelist.size()];
  Int_t *imass = new Int_t[inamelist.size()];
  std::map<string, Double_t*>mdouble;
  std::map<string, Int_t*>mint;
  int idx= 0;
  for (auto name : dnamelist){
    mdouble[name]  = &dmass[idx];
    idx++;
  }
  idx=0;
  for (auto name : inamelist){
    mint[name] = &imass[idx];
    idx++;
  }

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

  TString outtext = input->GetName();
  std::cout << "Using file: " << outtext << std::endl;

  for (auto name : dnamelist){
    tree->SetBranchAddress(name.c_str(), &*mdouble[name.c_str()]);
  }
  for (auto name : inamelist){
    tree->SetBranchAddress(name.c_str(), &*mint[name.c_str()]);
  }
  
  Double_t effS = 0.7;
  Double_t BDT;

  string treename = (whichtree ==0 ||isMC ==1) ? "tree" : Form("tree%d",whichtree);
  TTreeReader newreader(treename.c_str(), input);
  TFile *target;
  if (isMC ==0) target =new TFile(Form("./BDTAppliedData/BDTApp_%ld.root",ts),"recreate");
  else if (isMC==1) target =new TFile(Form("./BDTAppliedData/BDTApp_%ld_MC.root",ts),"recreate");
  else if (isMC==2) target = new TFile(Form("./BDTAppliedData/BDTApp_Custom.root"),"recreate");
  TTree* outtree = tree->CloneTree(0);
  outtree->SetName("tree");
  outtree->Branch("BDT", &BDT, "BDT/D");


  for(Long64_t ievt=0; ievt< tree->GetEntries();ievt++){
    tree->GetEntry(ievt);
    outtree->GetEntry(ievt);
    if (ievt%10000 == 0) std::cout << "--- ... Processing event: " << ievt << "\r";
    for( string name : dnamelist ){
      if( mvar[name] !=nullptr){
	if( mdouble[name] !=nullptr) *mvar[name] = *mdouble[name];
      }
      if( mspc[name] !=nullptr){
	if( mdouble[name] !=nullptr) *mspc[name] = *mdouble[name];
      }
    }
    for( string name : inamelist ){
      if( mvar[name] !=nullptr){
	if( mint[name] !=nullptr) *mvar[name] = *mint[name];
      }
      if( mspc[name] !=nullptr){
	if( mint[name] !=nullptr) *mspc[name] = *mint[name];
      }
    }
  BDT=reader->EvaluateMVA( Form("BDT_train_%ld",ts));
  outtree->Fill();
  }
  outtree->Write();
  std::cout << "done Writiing " << target->GetName()<< std::endl;
  target->Close();

}
