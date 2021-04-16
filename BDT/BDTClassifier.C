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
long _ts;

bool BDTClassifier_Function(bool IDvar = false, bool MoreVar = true, bool IDonly= true ){
  //Load Library
  TMVA::Tools::Instance();

  std::time_t tstamp = std::time(nullptr);
  _ts = (long) tstamp;
  std::cout <<"time stamp---> " <<  tstamp << std::endl;
  std::system(Form("cat BDTClassifier.C >> ./.past_source/_BDTClassifier_%ld.old",(long) tstamp));
  ofstream log;
  log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  log << tstamp;
  char logbuf[2000];
  std::cout << "Write down description for this run :";
  std::cin.getline(logbuf,2000);
  log << ", " << logbuf << std::endl;

  TString mainDIR= gSystem->ExpandPathName(gSystem->pwd());
  TString BDTDir = mainDIR + ("/BDTResult");
  void* dirp = gSystem->OpenDirectory(BDTDir.Data());
  if(dirp) gSystem->FreeDirectory(dirp);
  else gSystem->mkdir(BDTDir.Data(),kTRUE);
  
  //INPUT & OUTPUT Call
  TFile* inputDATA = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC0_v210416.root","read");
  TFile* inputMC   = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_v210416.root","read");
  TFile* output    = new TFile(Form("%s/BDTresultY3S_%ld_IDv%d_MoreVar%d.root",BDTDir.Data(),(long) tstamp, (int) IDvar, (int) MoreVar),"recreate");
	
  double ylim = 2.4;
  string HybSoft = "&&nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&dxy1<0.2&&dxy2<0.2&&dz1<20&&dz2<20";
  string rejectNAN = "&&!TMath::IsNaN(ctau)&&!TMath::IsNaN(ctau3D)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";//"&&!TMath::IsNaN(QQMassErr)&&!TMath::IsNaN(dxyErr1)&&!TMath::IsNaN(dxyErr2)&&!TMath::IsNaN(QQVtxProb)&&!TMath::IsNaN(QQdca)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";
  TCut cut1 = Form("pt1>3.5&&pt2>3.5&&fabs(y)<%f%s%s",ylim, HybSoft.c_str(),rejectNAN.c_str());
  TCut cut2 = Form("pt1>3.5&&pt2>3.5&&fabs(y)<%f%s%s",ylim, HybSoft.c_str(),rejectNAN.c_str());

  TMVA::DataLoader *loader = new TMVA::DataLoader("dataset");
  TTree* SigTree =(TTree*) inputMC->Get("tree");
  TTree* BkgTreeTest =(TTree*) inputDATA->Get("tree");
  TTree* BkgTreeTrain = BkgTreeTest->CopyTree("(mass>10.5&&mass<14)||(mass>8.&&mass<8.6)");
  std::cout << "Number of Events in Trees (Sig, BkgTest, BkgTrain) : ( " << SigTree->GetEntries(cut1) << ", "<< BkgTreeTest->GetEntries(cut2) << ", " << BkgTreeTrain->GetEntries(cut2) << " )" << std::endl;
  //Factory Call
  TMVA::Factory *factory = new TMVA::Factory("TMVA_BDT_Classifier", output, "!V:Silent:Color:DrawProgressBar:Transformations=I;D;P;G;D:AnalysisType=Classification");
  //factory->SetVerbose();
  if(!IDonly){
  loader->AddVariable("pt1","Single muon pt1",  "F");
  loader->AddVariable("pt2","Single muon pt2",  "F");
  loader->AddVariable("eta1","Single muon eta1",  "F");
  loader->AddVariable("eta2","Single muon eta2",  "F");
  }
  if(IDvar){
    loader->AddVariable("nPixWMea1", "nPix Mea 1", "I");
    loader->AddVariable("nPixWMea2", "nPix Mea 2", "I");
    loader->AddVariable("nTrkWMea1", "nTrk Mea 1", "I");
    loader->AddVariable("nTrkWMea2", "nTrk Mea 2", "I");
    loader->AddVariable("dxy1", "dxy of single mu 1", "F");
    loader->AddVariable("dxy2", "dxy of single mu 2", "F");
    loader->AddVariable("dz1", "dz of single mu 1", "F");
    loader->AddVariable("dz2", "dz of single mu 2", "F");
    if(!MoreVar){
      loader->AddSpectator("QQVtxProb","Vrtx prob", "F");
    }
    if(IDonly){
      loader->AddSpectator("pt1","Single muon pt1",  "F");
      loader->AddSpectator("pt2","Single muon pt2",  "F");
      loader->AddSpectator("eta1","Single muon eta1",  "F");
      loader->AddSpectator("eta2","Single muon eta2",  "F");
    }
  }
  if(MoreVar){
  //  loader->AddVariable("nTrkHits1", "nTrk Hit 1", "I");
  //  loader->AddVariable("nTrkHits2", "nTrk Hit 2", "I");
  //  loader->AddVariable("nPixValHits1", "nPix Valid Hits 1", "I");
  //  loader->AddVariable("nPixValHits2", "nPix Valid Hits 2", "I");
  //  loader->AddVariable("nMuValHits1", "global pt error1", "I");
  //  loader->AddVariable("nMuValHits2", "global pt error2", "I");
  //  loader->AddVariable("StationsMatched1", "global pt error1", "I");
  //  loader->AddVariable("StationsMatched2", "global pt error2", "I");
  //  loader->AddVariable("normChi2_inner1", "global pt error1", "F");
  //  loader->AddVariable("normChi2_inner2", "global pt error2", "F");
  //  loader->AddVariable("StationsMatched1", "Single muon Matched to Muon Station 1", "I");
    loader->AddVariable("QQMassErr", "Dimu Mass error", "F");
  //  loader->AddVariable("dxyErr1", "Single Muon vertex position error1", "F");
  //  loader->AddVariable("dxyErr2", "Single Muon vertex position error2", "F");
  //  loader->AddVariable("ptErr_inner1", "pterr of inner tracker single muon 1", "F");
  //  loader->AddVariable("ptErr_inner2", "pterr of inner tracker single muon 2", "F");

    loader->AddVariable("ctau3D", "3 dim ctau of the dimuon","F");
//    loader->AddVariable("ctau", "2 dim ctau of the dimuon","F");
    loader->AddVariable("QQVtxProb", "Vtx prob", "F");
//    loader->AddSpectator("QQVtxProb", "Vtx prob", "F");
    loader->AddVariable("QQdca", "QQdca", "F");
//    loader->AddVariable("cosAlpha", "cos alpha for trajectory angle", "F");
    loader->AddVariable("cosAlpha3D", "cos alpha for trajectory angle 3D", "F");

 //   loader->AddVariable("ctau3D", "*ctau3D var", "F");
//    loader->AddVariable("normChi2_global1", "global Nchi squared valu of mu 1", "F");
//    loader->AddVariable("normChi2_global2", "global Nchi squared valu of mu 2", "F");
    if(IDonly){
      loader->AddSpectator("pt1","Single muon pt1",  "F");
      loader->AddSpectator("pt2","Single muon pt2",  "F");
      loader->AddSpectator("eta1","Single muon eta1",  "F");
      loader->AddSpectator("eta2","Single muon eta2",  "F");
    }
  }

  //Spectator Call, Will NOT Use For Training
  loader->AddSpectator("cBin","Centrality times 2 bin", "F");
  loader->AddSpectator("mass","Dimuon mass", "F");
  loader->AddSpectator("pt","Dimuon pt","F");
  loader->AddSpectator("y","Dimuon y",  "F");

  Double_t signalWeight     = 1.0;
  Double_t backgroundWeight = 1.0;

  loader->AddSignalTree     (SigTree, signalWeight);
//  loader->AddBackgroundTree (BkgTreeTest, backgroundWeight, "Test");
  loader->AddBackgroundTree (BkgTreeTrain, backgroundWeight);

  loader->SetSignalWeightExpression("weight");
//  loader->SetBackgroundWeightExpression("weight");

  //Preselection Cut -> Conventional Kinematics 


  loader->PrepareTrainingAndTestTree( cut1, cut2, "nTrain_Signal=200000:nTrain_Background=200000:SplitMode=Random:Random:NormMode=NumEvents:!V");

  //Book Training BDT Method
  factory->BookMethod( loader, TMVA::Types::kBDT, TString::Format("BDT_train_%ld", (long) tstamp ),
  	"!H:!V:NTrees=200:MaxDepth=4:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=True:UseNvars=2:BaggedSampleFraction=0.4:nCuts=20000:CreateMVAPdfs");

  //Train Test Evaluate
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
  auto c1 = factory->GetROCCurve(loader);
  c1->Draw();
  c1->SaveAs(Form("%s/ROC_%ld_ID%d_MV%d.pdf",BDTDir.Data(), (long) tstamp,(int) IDvar,(int) MoreVar));
  output->Close();

  ofstream out;
  out.open("timestamp.tmp");
  out << tstamp ;
  out.close();
  return true;
}

//Main Function
void BDTClassifier(bool _IDvar = true, bool _MoreVar = false, bool _IDonly= false ){
  bool res = BDTClassifier_Function(_IDvar, _MoreVar, _IDonly);
  if(!res)std::system(Form("rm ./.past_source/_BDTClassifier_%ld.old",(long) _ts));
//  BDTClassifier_Function(true, false, false);
//  BDTClassifier_Function(false, false, false);
}
