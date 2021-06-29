#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "TROOT.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"
#include <ctime>
#include "../.workdir.h"
long _ts;
char logbuf[2000];

bool BDTClassifier_BLIND_Function(int idxBkg , int idxDat , double ptLow, double ptHigh, int cBinLow, int cBinHigh, std::string opt = ""){
  //Load Library
  TMVA::Tools::Instance();
  int traintree, testtree;
  if(idxDat ==1) {
    traintree=2;
    testtree=3;
  }
  if(idxDat ==2) {
    traintree=3;
    testtree=2;
  }
  if(idxDat ==0){
    traintree=1;
    testtree=1;
  }

  std::time_t tstamp = std::time(nullptr);
  _ts = (long) tstamp;
  std::cout <<"time stamp---> " <<  tstamp << std::endl;
  std::system(Form("cat BDTClassifier_BLIND.C >> ./.past_source/_BDTClassifier_BLIND_%ld.old",(long) tstamp));
  ofstream log;
  log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
//  log << tstamp;

  TString mainDIR= workdir+"/BDT";
  TString BDTDir = mainDIR + ("/BDTResult");
  void* dirp = gSystem->OpenDirectory(BDTDir.Data());
  if(dirp) gSystem->FreeDirectory(dirp);
  else gSystem->mkdir(BDTDir.Data(),kTRUE);
  
  //INPUT & OUTPUT Call
  TFile* inputDATA = new TFile(Form("%s/%s", store.Data(), ONIABDTDATAB_LATEST.c_str()),"read");
  TFile* inputMC   = new TFile(Form("%s/%s", store.Data(), ONIABDTMC_LATEST.c_str()),"read");
  //new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_v210416.root","read");
  TFile* output    = new TFile(Form("%s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),(long) tstamp),"recreate");

  double ylim = 2.4;
  double massLow = 8;
  double massHigh = 11.5;
  string HybSoft = "&&nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&dxy1<0.3&&dxy2<0.3&&dz1<20&&dz2<20";
  string rejectNAN = "&&!TMath::IsNaN(ctau)&&!TMath::IsNaN(ctau3D)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";//"&&!TMath::IsNaN(QQMassErr)&&!TMath::IsNaN(dxyErr1)&&!TMath::IsNaN(dxyErr2)&&!TMath::IsNaN(QQVtxProb)&&!TMath::IsNaN(QQdca)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";
  TCut cut1 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>0.0&&pt2>0.0&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, ylim, HybSoft.c_str(),rejectNAN.c_str());
  TCut cut2 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>0.0&&pt2>0.0&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, ylim, HybSoft.c_str(),rejectNAN.c_str());

  TMVA::DataLoader *loader = new TMVA::DataLoader("dataset");
  TTree* SigTree =(TTree*) inputMC->Get("tree");
  TTree* BkgTreeTest_primary =(TTree*) inputDATA->Get(Form("tree%d",testtree));
  TTree* BkgTreeTest1 = BkgTreeTest_primary->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<11.5)");
  TTree* BkgTreeTest2 =(TTree*) BkgTreeTest_primary->CloneTree();
  BkgTreeTest1->SetName("tree2Clone1");
  BkgTreeTest2->SetName("tree2Clone2");
  TTree* BkgTreeTrain_primary =(TTree*) inputDATA->Get(Form("tree%d",traintree));
  TTree* BkgTreeTrain1 = BkgTreeTrain_primary->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<11.5)");
  TTree* BkgTreeTrain2 = BkgTreeTrain_primary->CopyTree("(mass>10.8&&mass<11.5)");
  std::cout << "Number of Events in Trees (Sig, BkgTest, BkgTrain) : ( " << SigTree->GetEntries(cut1) << ", "<< BkgTreeTest1->GetEntries(cut2) << ", " << BkgTreeTrain1->GetEntries(cut2) << " )" << std::endl;
  //Factory Call
  TMVA::Factory *factory = new TMVA::Factory("TMVA_BDT_Classifier", output, "!V:Silent:Color:DrawProgressBar:Transformations=G:AnalysisType=Classification");
  loader->AddVariable("QQMassErr", "Dimu Mass error", "F");
  loader->AddVariable("ctau3D", "3 dim ctau of the dimuon","F");
  loader->AddVariable("ctau", "2 dim ctau of the dimuon","F");
  loader->AddVariable("QQVtxProb", "Vtx prob", "F");
  loader->AddVariable("QQdca", "QQdca", "F");
  loader->AddVariable("cosAlpha", "cos alpha for trajectory angle", "F");
  loader->AddVariable("cosAlpha3D", "cos alpha for trajectory angle 3D", "F");
//  loader->AddVariable("dcosMuTheta", "single muon angle diff", "F");
  loader->AddVariable("PtImb", "single muon pt imbalance", "F");
//  loader->AddVariable("pt1", "single muon pt1", "F");
//  loader->AddVariable("pt2", "single muon pt2", "F");
//  loader->AddVariable("eta1", "single muon eta1", "F");
//  loader->AddVariable("eta2", "single muon eta2", "F");
//  loader->AddVariable("phi1", "single muon phi1", "F");
//  loader->AddVariable("phi2", "single muon phi2", "F");

  //Spectator Call, Will NOT Use For Training
//  loader->AddSpectator("QQVtxProb", "Vtx prob", "F");
  loader->AddSpectator("pt1","Single muon pt1",  "F");
  loader->AddSpectator("pt2","Single muon pt2",  "F");
  loader->AddSpectator("eta1","Single muon eta1",  "F");
  loader->AddSpectator("eta2","Single muon eta2",  "F");
  loader->AddSpectator("cBin","Centrality times 2 bin", "F");
  loader->AddSpectator("mass","Dimuon mass", "F");
  loader->AddSpectator("pt","Dimuon pt","F");
  loader->AddSpectator("y","Dimuon y",  "F");

  Double_t signalWeight     = 1;// 1.4e-6 ;
  Double_t backgroundWeight = 20; //1e-3;

  loader->AddSignalTree     (SigTree, signalWeight);
  if(idxBkg ==0){
    loader->AddBackgroundTree (BkgTreeTrain1, backgroundWeight, "Train");
    loader->AddBackgroundTree (BkgTreeTest1, backgroundWeight, "Test");
//    loader->AddBackgroundTree (BkgTreeTrain2, backgroundWeight);
  }
  if(idxBkg ==1)  loader->AddBackgroundTree (BkgTreeTrain1, backgroundWeight);
  if(idxBkg ==2) loader->AddBackgroundTree (BkgTreeTrain2, backgroundWeight);


  loader->SetSignalWeightExpression("weight");
//  loader->SetBackgroundWeightExpression("weight");

  //Preselection Cut -> Conventional Kinematics 


  loader->PrepareTrainingAndTestTree( cut1, cut2, "SplitSeed=100:SplitMode=Alternate:NormMode=None:!V");

  //Book Training BDT Method
  factory->BookMethod( loader, TMVA::Types::kBDT, TString::Format("BDT_train_%ld", (long) tstamp ),
  	"!H:!V:NTrees=400:MaxDepth=3:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=4000:CreateMVAPdfs");//:VarTransform=Gauss");

  //Train Test Evaluate
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
  auto c1 = factory->GetROCCurve(loader, TString::Format("BDT_train_%ld", (long) tstamp ));
  c1->Write();
  output->Close();
  if(opt!= "") opt +="::";
  if(opt!="NR"){
  log << tstamp << "::"<< Form("%2.2f,%2.2f",massLow,massHigh) << "::" << Form("%2.2f,%2.2f",ptLow, ptHigh) <<"::" << Form("%d,%d",cBinLow, cBinHigh) <<  "::" << Form("BLIND[%d,%d]::%s",traintree, testtree, opt.c_str())<<logbuf << std::endl;
  }

  log.close();

  ofstream out;
  out.open("timestamp.tmp");
  out << tstamp ;
  out.close();
  return true;
}

//Main Function
void BDTClassifier_BLIND( ){
  ofstream log;
  //log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  //log << "Bin by Bin training start----------------------" <<std::endl; ; 
  //log.close();

  std::pair<long, long> tsrange;
  std::vector<long > v_ts;
  std::cout << "Write down description for this run :";
  std::cin.getline(logbuf,2000);
  bool res; 
  res = BDTClassifier_BLIND_Function(0,0,0,30, 0,180);
  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
//  res = BDTClassifier_BLIND_Function(0,1,0,30, 0,180);
//  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  tsrange.first = _ts;
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  //  res = BDTClassifier_BLIND_Function(0,6, 0,180);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  //  res = BDTClassifier_BLIND_Function(6,30, 0, 180);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));

  //res = BDTClassifier_BLIND_Function(0,30, 0,40);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  //  res = BDTClassifier_BLIND_Function(0,6, 0,40);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  //  res = BDTClassifier_BLIND_Function(6,30,0, 40);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));

  //res = BDTClassifier_BLIND_Function(0,30, 40,100);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  //  res = BDTClassifier_BLIND_Function(0,6, 40,100);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  //  res = BDTClassifier_BLIND_Function(6,30,40, 100);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  //
  //res = BDTClassifier_BLIND_Function(0,30, 100,180);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  //  res = BDTClassifier_BLIND_Function(0,6, 100,180);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
  //  res = BDTClassifier_BLIND_Function(6,30, 100, 180);
  //tsrange.second = _ts;
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));

  //log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  //log << "TS coleection::{";
  //for ( const auto ts : v_ts){ 
  //  log << Form(" %s,",ts);
  //} log << "}" << std::endl;

  //log << "Bin by Bin training end::" << Form("%ld,%ld",tsrange.first,tsrange.second) << std::endl;
  //log.close();
}
