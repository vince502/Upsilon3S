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
#include "../bininfo.h"
#include "../../.workdir.h"


void BDTClassifierApplication_NOM(long ts= 9999999999, int train_state =2, int target_state = 2, bool isMC = 0, bool isbbb = true, int ptLow =0, int ptHigh = 30, int mcmode= 0){
  std::cout <<"[BDT_APP] Initializing" << std::endl;
//  std::string info_blind;
//  if( !isbbb) info_blind = info_BDT(ts)[2];
//  if( isbbb ) info_blind = info_BDT(ts)[4];
//  std::cout << info_blind << std::endl;
//  std::pair<int,int> _bf= {stoi(info_blind.substr(6,1)),stoi(info_blind.substr(8,1)) };
//  int whichtree = _bf.second;
    int whichtree = 1;
//  if (whichtree >5) {std::cout << "if BLIND, is tree selection wrong? " << std::endl; return; }
//  if (whichtree !=0 && whichtree <6) {std::cout <<"Application in BLIND tree"<<whichtree<< std::endl;}


  TMVA::Tools::Instance();
  TMVA::Reader *reader1 = new TMVA::Reader("V:!Silent");
  TMVA::Reader *reader2 = new TMVA::Reader("V:!Silent");
  TXMLEngine xml;
  XMLDocPointer_t xmldoc = xml.ParseFile(Form("./data/Y%dSpt%dto%d/dataset1/weights/TMVA_BDT_Classifier1_%ld_BDT.weights.xml", train_state, ptLow, ptHigh, ts));
  XMLDocPointer_t mainnode = xml.DocGetRootElement(xmldoc);

  TString fname;
  if(isMC){
    if(target_state==1) {
		if(mcmode==0) fname =Form("%s/%s", store.Data(), ONIABDTMC1S_LATEST.c_str());
		if(mcmode==1) fname = Form("%s/BDT/BDTResults/BDTresultY3S_%ld_BLIND.root",workdir.Data(), ts);
	}
    if(target_state==2) {
		if(mcmode==0) fname =Form("%s/%s", store.Data(), ONIABDTMC2S_LATEST.c_str());
		if(mcmode==1) fname = Form("%s/BDT/BDTResults/BDTresultY3S_%ld_BLIND.root",workdir.Data(), ts);
	
	}
    if(target_state==3) {
		if(mcmode==0) fname =Form("%s/%s", store.Data(), ONIABDTMC_LATEST.c_str());
		if(mcmode==1) fname = Form("%s/BDT/BDTResults/BDTresultY3S_%ld_BLIND.root",workdir.Data(), ts);
	}
  }
  else if(!isMC){
    if(whichtree !=0){
      fname =Form("%s/%s", store.Data(), ONIABDTDATAB_LATEST.c_str() );
      if( ts == 9999999996) fname = Form("%s/%s", hfdir.Data(), SYS_HFUPDATA.c_str() );
      if( ts == 9999999995) fname = Form("%s/%s", hfdir.Data(), SYS_HFDOWNDATA.c_str() );
    }
    if(whichtree ==0) fname =Form("%s/%s", store.Data(), ONIABDTDATA_LATEST.c_str() );
  }

  TFile* input(0);
  input = new TFile(fname.Data(), "open");
  TTree* tree1;
  TTree* tree2;
  if(!isMC){
  tree1 = (TTree*) input->Get("tree3");
  tree2 = (TTree*) input->Get("tree2");
  }
  if(isMC){
  tree1 = (TTree*) input->Get("tree");
  tree2 = (TTree*) input->Get("tree");
  }
  
  std::vector<string> dnamelist;
  std::vector<string> inamelist;
  TObjArray* blist = tree1->GetListOfBranches();
  for (auto content : *blist){
    string Titler = content->GetTitle();
    char datype = Titler.back();
    if( datype=='D' ){dnamelist.push_back(content->GetName());}
    else if ( datype=='I' ){inamelist.push_back(content->GetName());}
    else continue;
  }
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
    reader1->AddVariable(varname, &varptr[i]);
    reader2->AddVariable(varname, &varptr[i]);
    childvar = xml.GetNext(childvar);
  }
  for(int i=0; i < nspc; i++){
    spcname =(xml.GetAttr(childspc, "Expression"));
    mspc[spcname]=&spcptr[i];
    reader1->AddSpectator(spcname, &spcptr[i]);
    reader2->AddSpectator(spcname, &spcptr[i]);
    childspc = xml.GetNext(childspc);
  }
  

  TString weightfile1 = Form("./data/Y%dSpt%dto%d/dataset1/weights/TMVA_BDT_Classifier1_%ld_BDT.weights.xml", train_state, ptLow, ptHigh, ts);
  TString weightfile2 = Form("./data/Y%dSpt%dto%d/dataset2/weights/TMVA_BDT_Classifier2_%ld_BDT.weights.xml", train_state, ptLow, ptHigh, ts);
  TString methodName1 = (Form("BDT"));
  TString methodName2 = (Form("BDT"));
  reader1->BookMVA( methodName1, weightfile1);
  reader2->BookMVA( methodName2, weightfile2 );

  TString outtext = input->GetName();
  std::cout << "Using file: " << outtext << std::endl;

  for (auto name : dnamelist){
    tree1->SetBranchAddress(name.c_str(), &*mdouble[name.c_str()]);
    tree2->SetBranchAddress(name.c_str(), &*mdouble[name.c_str()]);
  }
  for (auto name : inamelist){
    tree1->SetBranchAddress(name.c_str(), &*mint[name.c_str()]);
    tree2->SetBranchAddress(name.c_str(), &*mint[name.c_str()]);
  }
  
  Double_t effS = 0.7;
  Double_t BDT;
  int treeID;

  TFile *target;
  if (isMC ==0) target =new TFile(Form("%s/BDT/BDTAppliedData/BDTApp_%ld.root",workdir.Data(),ts),"update");
  else if (isMC==1)
  {
    if(target_state ==1 ) target =new TFile(Form("%s/BDT/BDTAppliedData/BDTApp_%ld_MC_1S.root",workdir.Data(),ts),"update");
    if(target_state ==2 ) target =new TFile(Form("%s/BDT/BDTAppliedData/BDTApp_%ld_MC_2S.root",workdir.Data(), ts),"update");
    if(target_state ==3 ) target =new TFile(Form("%s/BDT/BDTAppliedData/BDTApp_%ld_MC.root",workdir.Data(),ts),"update");
  }
  TTree* outtree;
  bool isNew = true;
  if( target->Get("tree") != nullptr){
    isNew = false;
    std::cout << "Fetching Existing Tree to add BDT branch" << std::endl;
    outtree = (TTree*) target->Get("tree");
    outtree->SetBranchAddress("treeID", &treeID );
  }
  else {
    outtree =tree1->CloneTree(0);
  outtree->SetName("tree");
  outtree->Branch("treeID", &treeID, "treeID/I");
  }
  TBranch* bdt_branch = outtree->Branch(Form("BDTY%dSpt%dto%d",train_state, ptLow, ptHigh) , &BDT, Form("BDTY%dSpt%dto%d/D",train_state, ptLow, ptHigh));


  int count = 0;
  int Nfirstloop;
  if( isMC ) Nfirstloop = (int) (tree1->GetEntries() /2) ;
  if( !isMC ) Nfirstloop = (int) tree1->GetEntries();
  std::cout << "First Loop Entries : " << Nfirstloop << std::endl;
  for(Long64_t ievt=0; ievt< Nfirstloop;ievt++){
    tree1->GetEntry(ievt);
    outtree->GetEntry(count);
    if (ievt%10000 == 0) std::cout << "--- ... Processing event: " << ievt << "\n";
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
  BDT=reader1->EvaluateMVA( Form("BDT"));
  treeID=1;
  if(isNew)  outtree->Fill();
  if(!isNew) bdt_branch->Fill();
  count ++;
  }
  int Nstart, Nsecondloop;
  if( isMC ) {Nstart = Nfirstloop; Nsecondloop = tree1->GetEntries(); }
  if( !isMC) {Nstart = 0; Nsecondloop = tree2->GetEntries(); }
  std::cout << "Nstart : " << Nstart << ", NsecondLoop : "<< Nsecondloop << std::endl;
  for(Long64_t ievt= Nstart; ievt< Nsecondloop;ievt++){
    tree2->GetEntry(ievt);
    outtree->GetEntry(count);
    if (ievt%10000 == 0) std::cout << "--- ... Processing event: " << ievt << "\n";
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
  BDT=reader2->EvaluateMVA( Form("BDT"));
  treeID=2;
  if(isNew)  outtree->Fill();
  if(!isNew) bdt_branch->Fill();
  count ++;
  }
  if(isbbb){
//    std::vector<std::string> bdt_info = info_BDT(ts);
//    auto ptpair = parser_symbol( bdt_info[2],",");
//    auto cBinpair = parser_symbol( bdt_info[3],",");
//    std::string cut = Form("pt>%s && pt <%s && cBin > %s && cBin < %s", ptpair[0].c_str(), ptpair[1].c_str(), cBinpair[0].c_str(), cBinpair[1].c_str() ) ;
//    cut = cut+"&&"+MuIDHybridSoft2018;2
//    outtree = (TTree*) outtree->CopyTree(cut.c_str());
  }
  std::cout << "TOTAL ENTRIES: " <<   outtree->GetEntries() << std::endl;
  outtree->Write("", TObject::kOverwrite);
  std::cout << "done Writiing " << target->GetName()<< std::endl;
  target->Close();

}
