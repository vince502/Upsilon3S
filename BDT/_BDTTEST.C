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

bool BDTClassifier_BLIND_Function( ){
  //Load Library
  TMVA::Tools::Instance();
  int traintree = 2;
  int testtree = 2;

  std::time_t tstamp = std::time(nullptr);
  _ts = (long) tstamp;
  std::cout <<"time stamp---> " <<  tstamp << std::endl;
//  std::system(Form("cat BDTClassifier_BLIND.C >> ./.past_source/_BDTClassifier_BLIND_%ld.old",(long) tstamp));
  ofstream log;
  log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  log << tstamp;
  char logbuf[2000];
  std::cout << "Write down description for this run :";
  std::cin.getline(logbuf,2000);


  TString mainDIR= workdir+ "/BDT";
  TString BDTDir = mainDIR + ("/BDTResult");
  void* dirp = gSystem->OpenDirectory(BDTDir.Data());
  if(dirp) gSystem->FreeDirectory(dirp);
  else gSystem->mkdir(BDTDir.Data(),kTRUE);
  
  //INPUT & OUTPUT Call
  TFile* inputDATA = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC0_v210416_ForBLIND.root","read");
  TFile* inputMC   = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_v210521.root","read");
  //new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_v210416.root","read");
  TFile* output    = new TFile(Form("%s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),(long) tstamp),"recreate");

  double ylim = 2.4;
  double massLow = 8;
  double massHigh = 11.5;
  string HybSoft = "&&nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&dxy1<0.3&&dxy2<0.3&&dz1<20&&dz2<20";
  string rejectNAN = "&&!TMath::IsNaN(ctau)&&!TMath::IsNaN(ctau3D)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";//"&&!TMath::IsNaN(QQMassErr)&&!TMath::IsNaN(dxyErr1)&&!TMath::IsNaN(dxyErr2)&&!TMath::IsNaN(QQVtxProb)&&!TMath::IsNaN(QQdca)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";
  TCut cut1 = Form("mass>%f&&mass<%f&&pt<30&&pt>0&&pt1>3.5&&pt2>3.5&&fabs(y)<%f%s%s", massLow, massHigh, ylim, HybSoft.c_str(),rejectNAN.c_str());
  TCut cut2 = Form("mass>%f&&mass<%f&&pt<30&&pt>0&&pt1>3.5&&pt2>3.5&&fabs(y)<%f%s%s", massLow, massHigh, ylim, HybSoft.c_str(),rejectNAN.c_str());

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
  loader->AddVariable("QQMassErr_e := QQMassErr && (y>1.2)", "Dimu Mass error", "F");
  loader->AddVariable("QQMassErr_b2 := QQMassErr && (y>0.6&&y<1.2)", "Dimu Mass error", "F");
  loader->AddVariable("QQMassErr_b1 := QQMassErr && (y<0.6)", "Dimu Mass error", "F");
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


  loader->PrepareTrainingAndTestTree( cut1, cut2, "SplitMode=Random:NormMode=None:!V");

  //Book Training BDT Method
  factory->BookMethod( loader, TMVA::Types::kBDT, TString::Format("BDT_train_%ld", (long) tstamp ),
  	"!H:!V:NTrees=200:MaxDepth=4:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=True:UseNvars=2:BaggedSampleFraction=0.4:nCuts=4000:CreateMVAPdfs");//:VarTransform=Gauss");

  //Train Test Evaluate
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
//  auto c1 = factory->GetROCCurve(loader);
//  c1->Draw();
//  c1->SaveAs(Form("%s/ROC_%ld.pdf",BDTDir.Data(), (long) tstamp));
  output->Close();
  log << "::"<< Form("%2.2f,%2.2f",massLow,massHigh) << "::" << Form("BLIND[%d,%d]:: ",traintree, testtree)<<logbuf << std::endl;

  log.close();
//  std::system(Form("rm %s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),(long) tstamp));

//  ofstream out;
//  out.open("timestamp.tmp");
//  out << tstamp ;
//  out.close();
  return true;
}

//Main Function
void _BDTTEST( ){
  bool res = BDTClassifier_BLIND_Function();
//  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
}
