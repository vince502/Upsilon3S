#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "TROOT.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"


void BDTClassifier_Function(bool IDvar = true, bool MoreVar = false, bool IDonly= false ){
  //Load Library
  TMVA::Tools::Instance();

  TFile* inputDATA = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC0.root","read");
  TFile* inputMC   = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1.root","read");
  TFile* output    = new TFile(Form("BDTresultY3S_IDv%d_MoreVar%d.root",(int) IDvar, (int) MoreVar),"recreate");

  TMVA::DataLoader *loader = new TMVA::DataLoader("dataset");
  TTree* SigTree =(TTree*) inputMC->Get("tree");
  TTree* BkgTree =(TTree*) inputDATA->Get("tree");
  
  TMVA::Factory *factory = new TMVA::Factory("TMVA_BDT_Classifier", output, "!V:Silent:Color:DrawProgressBar:Transformations=I;D;P;G;D:AnalysisType=Classification");
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
    if(IDonly){
      loader->AddSpectator("pt1","Single muon pt1",  "F");
      loader->AddSpectator("pt2","Single muon pt2",  "F");
      loader->AddSpectator("eta1","Single muon eta1",  "F");
      loader->AddSpectator("eta2","Single muon eta2",  "F");
    }
  }
  if(MoreVar){
    loader->AddVariable("nTrkHits1", "nTrk Hit 1", "I");
    loader->AddVariable("nTrkHits2", "nTrk Hit 2", "I");
    loader->AddVariable("nPixValHits1", "nPix Valid Hits 1", "I");
    loader->AddVariable("nPixValHits2", "nPix Valid Hits 2", "I");
    loader->AddVariable("highPurity1", "Purity Flag 1", "I", 0, 1);
    loader->AddVariable("highPurity2", "Purity Flag 2", "I", 0, 1);

    loader->AddVariable("QQVtxProb", "Vtx prob", "F");
 //   loader->AddVariable("ctau3D", "*ctau3D var", "F");
    loader->AddVariable("normChi2_global1", "global Nchi squared valu of mu 1", "F");
    loader->AddVariable("normChi2_global2", "global Nchi squared valu of mu 2", "F");
  }


  loader->AddSpectator("cBin","Centrality times 2 bin", "F");
  loader->AddSpectator("mass","Dimuon mass", "F");
  loader->AddSpectator("pt","Dimuon pt","F");
  loader->AddSpectator("y","Dimuon y",  "F");

  Double_t signalWeight     = 1.0;
  Double_t backgroundWeight = 1.0;

  loader->AddSignalTree     (SigTree, signalWeight);
  loader->AddBackgroundTree (BkgTree, backgroundWeight);

  loader->SetSignalWeightExpression("weight");

  TCut cut1 = "";
  TCut cut2 = "";

  loader->PrepareTrainingAndTestTree( cut1, cut2, "nTrain_Signal=50000:nTrain_Background=50000:SplitMode=Random:Random:NormMode=None:!V");
  factory->BookMethod( loader, TMVA::Types::kBDT, "BDT",
  	"!H:!V:NTrees=350:MaxDepth=3:MinNodeSize=4%:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=40:CreateMVAPdfs");

  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();
  auto c1 = factory->GetROCCurve(loader);
  c1->Draw();
  c1->SaveAs(Form("ROC_ID%d_MV%d.pdf",(int) IDvar,(int) MoreVar));
  output->Close();
}
void BDTClassifier(){
  BDTClassifier_Function(true,false, true);
//  BDTClassifier_Function(true, false, false);
//  BDTClassifier_Function(false, false, false);
//  BDTClassifier_Function(false, true);
//  BDTClassifier_Function(true, true);



}