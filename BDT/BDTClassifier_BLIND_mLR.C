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
  int traintree = 2;
  int testtree = 3;

  std::time_t tstamp = std::time(nullptr);
  _ts = (long) tstamp;
  std::cout <<"time stamp---> " <<  tstamp << std::endl;
//  std::system(Form("cat BDTClassifier_BLIND.C >> ./.past_source/_BDTClassifier_BLIND_%ld.old",(long) tstamp));
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

  double ylim 		= 2.4;
  double massLow 	= 8;
  double massHigh 	= 11.5;
  double Simucut  	= 0.0;
  string HybSoft 	= "&&nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&fabs(dxy1)<0.3&&fabs(dxy2)<0.3&&fabs(dz1)<20&&fabs(dz2)<20";
  string rejectNAN 	= "&&!TMath::IsNaN(ctau)&&!TMath::IsNaN(ctau3D)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";//"&&!TMath::IsNaN(QQMassErr)&&!TMath::IsNaN(dxyErr1)&&!TMath::IsNaN(dxyErr2)&&!TMath::IsNaN(QQVtxProb)&&!TMath::IsNaN(QQdca)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";
  TCut cut1 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>%f&&pt2>%f&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, Simucut, Simucut, ylim, HybSoft.c_str(),rejectNAN.c_str());
  TCut cut2 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>%f&&pt2>%f&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, Simucut, Simucut, ylim, HybSoft.c_str(),rejectNAN.c_str());

  TMVA::DataLoader *loader1_L = new TMVA::DataLoader("dataset1_L");
  TMVA::DataLoader *loader2_L = new TMVA::DataLoader("dataset2_L");
  TMVA::DataLoader *loader1_R = new TMVA::DataLoader("dataset1_R");
  TMVA::DataLoader *loader2_R = new TMVA::DataLoader("dataset2_R");
  TTree* SigTree =(TTree*) inputMC->Get("tree");
  TTree* BkgTreeTest_primary1 =(TTree*) inputDATA->Get(Form("tree3"));
  TTree* BkgTreeTest_primary2 =(TTree*) inputDATA->Get(Form("tree2"));
  TTree* BkgTreeTest1_L = BkgTreeTest_primary1->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<11.5)");
  TTree* BkgTreeTest1_R = BkgTreeTest_primary1->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<11.5)");
  TTree* BkgTreeTest2_L = BkgTreeTest_primary2->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<11.5)");
  TTree* BkgTreeTest2_R = BkgTreeTest_primary2->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<11.5)");

  BkgTreeTest1_L->SetName("tree3_L");
  BkgTreeTest1_R->SetName("tree3_R");
  BkgTreeTest2_L->SetName("tree2_L");
  BkgTreeTest2_R->SetName("tree2_R");
  TTree* BkgTreeTrain_primary1 =(TTree*) inputDATA->Get(Form("tree2"));
  TTree* BkgTreeTrain_primary2 =(TTree*) inputDATA->Get(Form("tree3"));
  TTree* BkgTreeTrain0 = BkgTreeTrain_primary1->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<11.5)");
  TTree* BkgTreeTrain1_L = BkgTreeTrain_primary1->CopyTree("(mass>8.&&mass<8.6)");
  TTree* BkgTreeTrain1_R = BkgTreeTrain_primary1->CopyTree("(mass>10.8&&mass<11.5)");
  TTree* BkgTreeTrain2_L = BkgTreeTrain_primary2->CopyTree("(mass>8.&&mass<8.6)");
  TTree* BkgTreeTrain2_R = BkgTreeTrain_primary2->CopyTree("(mass>10.8&&mass<11.5)");
  std::cout << "Number of Events in Trees (Sig, BkgTest, BkgTrain) : ( " << SigTree->GetEntries(cut1) << ", "<< BkgTreeTest1_L->GetEntries(cut2) << ", " << BkgTreeTrain1_L->GetEntries(cut2) << " )" << std::endl;
  //Factory Call
  TMVA::Factory *factory1_L = new TMVA::Factory(Form("TMVA_BDT_Classifier1L_%ld",(long) tstamp),  output, "!V:Silent:Color:DrawProgressBar:Transformations=G:AnalysisType=Classification");
  TMVA::Factory *factory1_R = new TMVA::Factory(Form("TMVA_BDT_Classifier1R_%ld",(long) tstamp),  output, "!V:Silent:Color:DrawProgressBar:Transformations=G:AnalysisType=Classification");
  TMVA::Factory *factory2_L = new TMVA::Factory(Form("TMVA_BDT_Classifier2L_%ld",(long) tstamp),  output, "!V:Silent:Color:DrawProgressBar:Transformations=G:AnalysisType=Classification");
  TMVA::Factory *factory2_R = new TMVA::Factory(Form("TMVA_BDT_Classifier2R_%ld",(long) tstamp),  output, "!V:Silent:Color:DrawProgressBar:Transformations=G:AnalysisType=Classification");
  for( auto loader : {loader1_L, loader1_R, loader2_L, loader2_R} ) 
  {
    loader->AddVariable("QQMassErr", "Dimu Mass error", "F");
    loader->AddVariable("ctau3D", "3 dim ctau of the dimuon","F");
    loader->AddVariable("ctau", "2 dim ctau of the dimuon","F");
    loader->AddVariable("QQVtxProb", "Vtx prob", "F");
    loader->AddVariable("QQdca", "QQdca", "F");
    loader->AddVariable("cosAlpha", "cos alpha for trajectory angle", "F");
    loader->AddVariable("cosAlpha3D", "cos alpha for trajectory angle 3D", "F");
//    loader->AddVariable("dcosMuTheta", "single muon angle diff", "F");
//    loader->AddVariable("PtImb", "single muon pt imbalance", "F");
//    loader->AddVariable("ptimb", "single muon scalar pt imbalance", "F");
//    loader->AddVariable("pt1", "single muon pt1", "F");
//    loader->AddVariable("pt2", "single muon pt2", "F");
//    loader->AddVariable("eta1", "single muon eta1", "F");
//    loader->AddVariable("eta2", "single muon eta2", "F");
//    loader->AddVariable("phi1", "single muon phi1", "F");
//    loader->AddVariable("phi2", "single muon phi2", "F");

    //Spectator Call, Will NOT Use For Training
//    loader->AddSpectator("QQVtxProb", "Vtx prob", "F");
    loader->AddSpectator("pt1","Single muon pt1",  "F");
    loader->AddSpectator("pt2","Single muon pt2",  "F");
    loader->AddSpectator("eta1","Single muon eta1",  "F");
    loader->AddSpectator("eta2","Single muon eta2",  "F");
    loader->AddSpectator("cBin","Centrality times 2 bin", "F");
    loader->AddSpectator("mass","Dimuon mass", "F");
    loader->AddSpectator("pt","Dimuon pt","F");
    loader->AddSpectator("y","Dimuon y",  "F");



  }
    Double_t signalWeight     = 1;// 1.4e-6 ;
    Double_t backgroundWeight = 20; //1e-3;
    loader1_L->AddSignalTree     (SigTree, signalWeight);
    loader1_R->AddSignalTree     (SigTree, signalWeight);
    loader2_L->AddSignalTree     (SigTree, signalWeight);
    loader2_R->AddSignalTree     (SigTree, signalWeight);
    loader1_L->AddBackgroundTree (BkgTreeTrain1_L, backgroundWeight, "Train");
    loader1_L->AddBackgroundTree (BkgTreeTest1_L, backgroundWeight, "Test");
    loader1_R->AddBackgroundTree (BkgTreeTrain1_R, backgroundWeight, "Train");
    loader1_R->AddBackgroundTree (BkgTreeTest1_R, backgroundWeight, "Test");

    loader2_L->AddBackgroundTree (BkgTreeTrain2_L, backgroundWeight, "Train");
    loader2_L->AddBackgroundTree (BkgTreeTest2_L, backgroundWeight, "Test");
    loader2_R->AddBackgroundTree (BkgTreeTrain2_R, backgroundWeight, "Train");
    loader2_R->AddBackgroundTree (BkgTreeTest2_R, backgroundWeight, "Test");


    loader1_L->SetSignalWeightExpression("weight");
    loader1_R->SetSignalWeightExpression("weight");
    loader2_L->SetSignalWeightExpression("weight");
    loader2_R->SetSignalWeightExpression("weight");

    loader1_L->PrepareTrainingAndTestTree( cut1, cut2, "SplitSeed=100:SplitMode=Alternate:NormMode=NumEvents:!V");
    loader1_R->PrepareTrainingAndTestTree( cut1, cut2, "SplitSeed=100:SplitMode=Alternate:NormMode=NumEvents:!V");
    loader2_L->PrepareTrainingAndTestTree( cut1, cut2, "SplitSeed=100:SplitMode=Alternate:NormMode=NumEvents:!V");
    loader2_R->PrepareTrainingAndTestTree( cut1, cut2, "SplitSeed=100:SplitMode=Alternate:NormMode=NumEvents:!V");


  //Book Training BDT Method
  factory1_L->BookMethod( loader1_L, TMVA::Types::kBDT, TString::Format("BDT1L"  ),
  	"!H:!V:NTrees=200:MaxDepth=4:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=4000:CreateMVAPdfs");//:VarTransform=Gauss");
  factory1_R->BookMethod( loader1_R, TMVA::Types::kBDT, TString::Format("BDT1R"  ),
  	"!H:!V:NTrees=200:MaxDepth=4:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=4000:CreateMVAPdfs");//:VarTransform=Gauss");
  factory2_L->BookMethod( loader2_L, TMVA::Types::kBDT, TString::Format("BDT2L"  ),
  	"!H:!V:NTrees=200:MaxDepth=4:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=4000:CreateMVAPdfs");//:VarTransform=Gauss");
  factory2_R->BookMethod( loader2_R, TMVA::Types::kBDT, TString::Format("BDT2R"  ),
  	"!H:!V:NTrees=200:MaxDepth=4:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=4000:CreateMVAPdfs");//:VarTransform=Gauss");
  //Train Test Evaluate
  
  for( auto setting : std::map<TMVA::Factory*, std::pair<TMVA::DataLoader*, string> > {{factory1_L, {loader1_L, "BDT1L"}}, {factory1_R,  {loader1_R, "BDT1R"}} , {factory2_L, {loader2_L, "BDT2L"} }, {factory2_R, {loader2_R, "BDT2R"} } } )
  {
  std::cout << setting.second.second;
   if(opt.find("pre")!=std::string::npos){
     std::cout << " Running Only 1L " << std::endl;
     if((setting.second.second.find("BDT1L")==std::string::npos) ) continue;
   }
  auto factory = setting.first;
  auto loader = setting.second.first;
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
  auto c1 = factory->GetROCCurve(loader, setting.second.second);
  auto c2 = factory->GetROCIntegral(loader, setting.second.second);
  std::cout << "ROC Integral is " << c2 << std::endl;
  c1->SetName("ROCCurve");
  c1->Write();
  c1->Delete();
  }
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
void BDTClassifier_BLIND_new( ){
  ofstream log;
  //log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  //log << "Bin by Bin training start----------------------" <<std::endl; ; 
  //log.close();

  std::pair<long, long> tsrange;
  std::vector<long > v_ts;
  std::cout << "Write down description for this run :";
  std::cin.getline(logbuf,2000);
  bool res; 
  res = BDTClassifier_BLIND_Function(0,0,0,30, 0,180, "");
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
