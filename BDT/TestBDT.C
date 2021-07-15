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

bool BDTClassifier_BLIND_Function(double ptLow, double ptHigh, int cBinLow, int cBinHigh){
  //Load Library
  TMVA::Tools::Instance();
  int traintree = 1;
  int testtree = 1;

  std::time_t tstamp = std::time(nullptr);
  _ts = (long) tstamp;
  std::cout <<"time stamp---> " <<  tstamp << std::endl;
  std::system(Form("cat BDTClassifier_BLIND.C >> ./.past_source/_BDTClassifier_BLIND_%ld.old",(long) tstamp));
  ofstream log;
  log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  log << tstamp;

  TString mainDIR= workdir+"/BDT";
  TString BDTDir = mainDIR + ("/BDTResult");
  void* dirp = gSystem->OpenDirectory(BDTDir.Data());
  if(dirp) gSystem->FreeDirectory(dirp);
  else gSystem->mkdir(BDTDir.Data(),kTRUE);
  
  //INPUT & OUTPUT Call
  TFile* inputDATA = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC0_v210628_ForBLIND.root","read");
  TFile* inputMC   = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_3S_v210628.root","read");
  //new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_v210416.root","read");
  TFile* output    = new TFile(Form("%s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),(long) tstamp),"recreate");

  double ylim = 2.4;
  double massLow = 8;
  double massHigh = 11.5;
  string HybSoft = "&&nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&dxy1<0.3&&dxy2<0.3&&dz1<20&&dz2<20";
  string rejectNAN = "&&!TMath::IsNaN(ctau)&&!TMath::IsNaN(ctau3D)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";//"&&!TMath::IsNaN(QQMassErr)&&!TMath::IsNaN(dxyErr1)&&!TMath::IsNaN(dxyErr2)&&!TMath::IsNaN(QQVtxProb)&&!TMath::IsNaN(QQdca)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";
  TCut cut1 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>3.5&&pt2>3.5&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, ylim, HybSoft.c_str(),rejectNAN.c_str());
  TCut cut2 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>3.5&&pt2>3.5&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, ylim, HybSoft.c_str(),rejectNAN.c_str());

  TMVA::DataLoader *loader = new TMVA::DataLoader("dataset");
  TTree* SigTree =(TTree*) inputMC->Get("tree");
  TTree* BkgTreeTest_primary =(TTree*) inputDATA->Get(Form("tree%d",testtree));
  TTree* BkgTreeTest =(TTree*) BkgTreeTest_primary->CloneTree();
  BkgTreeTest->SetName("tree2Clone");
  TTree* BkgTreeTrain_primary =(TTree*) inputDATA->Get(Form("tree%d",traintree));
  TTree* BkgTreeTrain = BkgTreeTrain_primary->CopyTree("(mass>10.8&&mass<11.5)||(mass>8.&&mass<8.6)");
  std::cout << "Number of Events in Trees (Sig, BkgTest, BkgTrain) : ( " << SigTree->GetEntries(cut1) << ", "<< BkgTreeTest->GetEntries(cut2) << ", " << BkgTreeTrain->GetEntries(cut2) << " )" << std::endl;
  //Factory Call
  TMVA::Factory *factory = new TMVA::Factory("TMVA_BDT_Classifier", output, "!V:Silent:Color:DrawProgressBar:Transformations=I;D;P;G;D:AnalysisType=Classification");
  loader->AddVariable("QQMassErr", "Dimu Mass error", "F");
  loader->AddVariable("ctau3D", "3 dim ctau of the dimuon","F");
  loader->AddVariable("ctau", "2 dim ctau of the dimuon","F");
  loader->AddVariable("QQVtxProb", "Vtx prob", "F");
  loader->AddSpectator("QQVtxProb", "Vtx prob", "F");
  loader->AddVariable("QQdca", "QQdca", "F");
  loader->AddVariable("cosAlpha", "cos alpha for trajectory angle", "F");
   loader->AddVariable("cosAlpha3D", "cos alpha for trajectory angle 3D", "F");

  //Spectator Call, Will NOT Use For Training
  loader->AddSpectator("pt1","Single muon pt1",  "F");
  loader->AddSpectator("pt2","Single muon pt2",  "F");
  loader->AddSpectator("eta1","Single muon eta1",  "F");
  loader->AddSpectator("eta2","Single muon eta2",  "F");
  loader->AddSpectator("cBin","Centrality times 2 bin", "F");
  loader->AddSpectator("mass","Dimuon mass", "F");
  loader->AddSpectator("pt","Dimuon pt","F");
  loader->AddSpectator("y","Dimuon y",  "F");

  Double_t signalWeight     = 1.0;
  Double_t backgroundWeight = 20.0;

  loader->AddSignalTree     (SigTree, signalWeight);
  loader->AddBackgroundTree (BkgTreeTest, backgroundWeight, "Test");
  loader->AddBackgroundTree (BkgTreeTrain, backgroundWeight, "Train");

  loader->SetSignalWeightExpression("weight");
//  loader->SetBackgroundWeightExpression("weight");

  //Preselection Cut -> Conventional Kinematics 


  loader->PrepareTrainingAndTestTree( cut1, cut2, "SplitSeed=100:NormMode=None:!V");

  //Book Training BDT Method
  factory->BookMethod( loader, TMVA::Types::kBDT, TString::Format("BDT_train_%ld", (long) tstamp ),
  	"!H:!V:NTrees=200:MaxDepth=4:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=4000:CreateMVAPdfs");//:VarTransform=Gauss");

  //Train Test Evaluate
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
  auto c1 = factory->GetROCCurve(loader);
  c1->Draw();
  output->Close();

  return true;
}

//Main Function
void TestBDT( ){
  ofstream log;
  //log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  //log << "Bin by Bin training start----------------------" <<std::endl; ; 
  //log.close();

  std::pair<long, long> tsrange;
  std::vector<long > v_ts;
  std::cout << "Write down description for this run :";
  std::cin.getline(logbuf,2000);
  bool res = BDTClassifier_BLIND_Function(0,30, 0,180);
  tsrange.first = _ts;
  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
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
  //  res = BDTClassifier_BLIND_Function(0,30, 100,180);
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
