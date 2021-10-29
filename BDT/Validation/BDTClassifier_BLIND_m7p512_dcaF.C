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
#include "../../.workdir.h"
long _ts;
long _real_time;
char logbuf[2000];
long _ts_buf=0;

bool BDTClassifier_BLIND_Function(int state , int idx , double ptLow, double ptHigh, int cBinLow, int cBinHigh, std::string opt = ""){
  //Load Library
  TMVA::Tools::Instance();
  int traintree, testtree;
    traintree=1;
    testtree=1;

  std::time_t tstamp = std::time(nullptr);
  _ts = (long) tstamp;
  if(_ts_buf==0) _ts_buf = _ts;
  if(strcmp(opt.c_str(), "continue")==0) _ts = _ts_buf;
  _ts_buf = _ts;
  _real_time = (long) tstamp;
  std::cout <<"time stamp---> " <<  tstamp << std::endl;
//  if(strcmp(opt.c_str(),"NOMINAL")==0) _ts = (long) 9999999999;
//  if(strcmp(opt.c_str(),"NOMINAL2")==0) _ts = (long) 99999999992;
  std::system(Form("cat BDTClassifier_BLIND_m7p512_dcaF.C >> ../.past_source/_BDTClassifier_BLIND_m7p512_dcaF%ld.old",(long) tstamp));
  ofstream log, log2;

//  log << tstamp;

  TString mainDIR= workdir+"/BDT";
  TString BDTDir = mainDIR + ("/BDTResult");
  void* dirp = gSystem->OpenDirectory(BDTDir.Data());
  if(dirp) gSystem->FreeDirectory(dirp);
  else gSystem->mkdir(BDTDir.Data(),kTRUE);
  
  //INPUT & OUTPUT Call
  TFile* inputDATA = new TFile(Form("%s/%s", store.Data(), ONIABDTDATAB_LATEST.c_str()),"read");
//  TFile* inputDATA = new TFile(Form("%s/%s", hfdir.Data(), SYS_HFDOWNDATA.c_str()),"read");
  TFile* inputMC   ;
  if(state ==1) inputMC= new TFile(Form("%s/%s", store.Data(), ONIABDTMC1S_LATEST.c_str()),"read");
  if(state ==2) inputMC= new TFile(Form("%s/%s", store.Data(), ONIABDTMC2S_LATEST.c_str()),"read");
  if(state ==3) inputMC= new TFile(Form("%s/%s", store.Data(), ONIABDTMC_LATEST.c_str()),"read");
  //new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_v210416.root","read");
  TFile* output;
  if(strcmp(opt.c_str(), "NOMINAL") ==0 ) output = new TFile(Form("%s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),_ts),"update");
  else if(strcmp(opt.c_str(), "continue") ==0) output = new TFile(Form("%s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),_ts),"update");
  else output = new TFile(Form("%s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),_ts),"recreate");

  double ylim 		= 2.4;
  double massLow 	= 7.5;
  double massHigh 	= 12.5;
  double Simucut  	= 3.5;
  string HybSoft 	= "&&nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&fabs(dxy1)<0.3&&fabs(dxy2)<0.3&&fabs(dz1)<20&&fabs(dz2)<20";
  string rejectNAN 	= "&&!TMath::IsNaN(ctau)&&!TMath::IsNaN(ctau3D)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";//"&&!TMath::IsNaN(QQMassErr)&&!TMath::IsNaN(dxyErr1)&&!TMath::IsNaN(dxyErr2)&&!TMath::IsNaN(QQVtxProb)&&!TMath::IsNaN(QQdca)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";
  TCut cut1 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>%f&&pt2>%f&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, Simucut, Simucut, ylim, HybSoft.c_str(),rejectNAN.c_str());
  TCut cut2 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>%f&&pt2>%f&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, Simucut, Simucut, ylim, HybSoft.c_str(),rejectNAN.c_str());

  TMVA::DataLoader *loader1 = new TMVA::DataLoader(Form("data/Y%dSpt%dto%d/dataset1", state, (int) ptLow, (int) ptHigh));
  TMVA::DataLoader *loader2 = new TMVA::DataLoader(Form("data/Y%dSpt%dto%d/dataset2", state, (int) ptLow, (int) ptHigh));
  TTree* SigTree =(TTree*) inputMC->Get("tree");
  TTree* BkgTreeTest_primary1 =(TTree*) inputDATA->Get(Form("tree3"));
  TTree* BkgTreeTest_primary2 =(TTree*) inputDATA->Get(Form("tree2"));
  TTree* BkgTreeTest1 = BkgTreeTest_primary1->CopyTree("(mass>7.5&&mass<8.6)||(mass>11&&mass<12.5)");
  TTree* BkgTreeTest2 = BkgTreeTest_primary2->CopyTree("(mass>7.5&&mass<8.6)||(mass>11&&mass<12.5)");

  BkgTreeTest1->SetName("tree3");
  BkgTreeTest2->SetName("tree2");
  TTree* BkgTreeTrain_primary1 =(TTree*) inputDATA->Get(Form("tree2"));
  TTree* BkgTreeTrain_primary2 =(TTree*) inputDATA->Get(Form("tree3"));
//  TTree* BkgTreeTrain0 = BkgTreeTrain_primary1->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<11.5)");
  TTree* BkgTreeTrain1 = BkgTreeTrain_primary1->CopyTree("(mass>7.5&&mass<8.6)||(mass>11&&mass<12.5)");
  TTree* BkgTreeTrain2 = BkgTreeTrain_primary2->CopyTree("(mass>7.5&&mass<8.6)||(mass>11&&mass<12.5)");
  std::cout << "Number of Events in Trees (Sig, BkgTest, BkgTrain) : ( " << SigTree->GetEntries(cut1) << ", "<< BkgTreeTest1->GetEntries(cut2) << ", " << BkgTreeTrain2->GetEntries(cut2) << " )" << std::endl;
  //Factory Call
  TMVA::Factory *factory1 = new TMVA::Factory(Form("TMVA_BDT_Classifier1_%ld",_ts),  output, "V:Color:DrawProgressBar:Transformations=G:AnalysisType=Classification");
  TMVA::Factory *factory2 = new TMVA::Factory(Form("TMVA_BDT_Classifier2_%ld",_ts),  output, "V:Color:DrawProgressBar:Transformations=G:AnalysisType=Classification");
  for( auto loader : {loader1, loader2} ) 
  {
    loader->AddVariable("QQMassErr", "Dimu Mass error", "F");
    loader->AddVariable("ctau3D", "3 dim ctau of the dimuon","F");
    loader->AddVariable("ctau", "2 dim ctau of the dimuon","F");
    loader->AddVariable("QQVtxProb", "Vtx prob", "F");
    loader->AddVariable("QQdca", "QQdca", "F");
    loader->AddVariable("cosAlpha", "cos alpha for trajectory angle", "F");
    loader->AddVariable("cosAlpha3D", "cos alpha for trajectory angle 3D", "F");
	loader->AddVariable("dcaFrac := ctau3D*sqrt(1-cosAlpha3D*cosAlpha3D)/QQdca", 'F');
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
    Double_t backgroundWeight = 40; //1e-3;
    loader1->AddSignalTree     (SigTree, signalWeight);
    loader2->AddSignalTree     (SigTree, signalWeight);
    loader1->AddBackgroundTree (BkgTreeTrain1, backgroundWeight, "Train");
    loader1->AddBackgroundTree (BkgTreeTest1, backgroundWeight, "Test");
    loader2->AddBackgroundTree (BkgTreeTrain2, backgroundWeight, "Train");
    loader2->AddBackgroundTree (BkgTreeTest2, backgroundWeight, "Test");



    loader1->SetSignalWeightExpression("weight");
    loader2->SetSignalWeightExpression("weight");

    loader1->PrepareTrainingAndTestTree( cut1, cut2, "SplitSeed=100:SplitMode=Alternate:NormMode=NumEvents:!V");
    loader2->PrepareTrainingAndTestTree( cut1, cut2, "SplitSeed=100:SplitMode=Alternate:NormMode=NumEvents:!V");


  //Book Training BDT Method
  factory1->BookMethod( loader1, TMVA::Types::kBDT, TString::Format("BDT"  ),
  	"!H:!V:NTrees=300:MaxDepth=2:MinNodeSize=15%:BoostType=AdaBoost:AdaBoostBeta=0.7:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=4000:CreateMVAPdfs");//:VarTransform=Gauss");
  factory2->BookMethod( loader2, TMVA::Types::kBDT, TString::Format("BDT"  ),
  	"!H:!V:NTrees=300:MaxDepth=2:MinNodeSize=15%:BoostType=AdaBoost:AdaBoostBeta=0.7:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=4000:CreateMVAPdfs");//:VarTransform=Gauss");
  //Train Test Evaluate
  
  for( auto setting : std::map<TMVA::Factory*, std::pair<TMVA::DataLoader*, string> > {{factory1, {loader1, "BDT"}}, {factory2,  {loader2, "BDT"}}} )
  {
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
  log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  log2.open("../BDT_description.log", std::ios_base::out|std::ios_base::app);
  if(opt!= "") 
    if(strcmp(opt.c_str(),"NOMINAL")==0) opt=Form("ALIAS_TS->%ld", (long) tstamp);
    opt +="::";
  if(opt!="NR"){
  log << _ts << "::"<< Form("%2.2f,%2.2f",massLow,massHigh) << "::" << Form("%2.2f,%2.2f",ptLow, ptHigh) <<"::" << Form("%d,%d",cBinLow, cBinHigh) <<  "::" << Form("BLIND[%d,%d]::%dS::%s",traintree, testtree, state, opt.c_str())<<logbuf << std::endl;
  log2 << _ts << "::"<< Form("%2.2f,%2.2f",massLow,massHigh) << "::" << Form("%2.2f,%2.2f",ptLow, ptHigh) <<"::" << Form("%d,%d",cBinLow, cBinHigh) <<  "::" << Form("BLIND[%d,%d]::%dS::%s",traintree, testtree, state, opt.c_str())<<logbuf << std::endl;
  }

  log.close();

  ofstream out;
  out.open("timestamp.tmp");
  out << tstamp ;
  out.close();
  return true;
}

//Main Function
void BDTClassifier_BLIND_m7p512_dcaF(){
  ofstream log;
  //log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  //log << "Bin by Bin training start----------------------" <<std::endl; ; 
  //log.close();

  std::pair<long, long> tsrange;
  std::vector<long > v_ts;
  std::cout << "Write down description for this run :";
  std::cin.getline(logbuf,2000);
  bool res; 

  std::vector<std::pair<int, int> >bin1spt = {/*{0,30},{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,8},{8,10},{10,12},{18,30}*/{12,18},{12,15},{15,30}};
  std::vector<std::pair<int, int> >bin2spt = {/*{0,2},{2,4},{4,6},{6,9},{9,12},{12,15},{15,20},{12,20},{12,24},{20,50},{24,50},{30,50}*/{12,50}, {15, 50}};
  std::vector<std::pair<int, int> >bin3spt = {/*{0,4},{4,9},{9,12},{12,15},{15,50},{12,24},{24,50},{12,20},{20,50},{12,30},{30,50},{15,30}*/};
//  for( auto pair : bin3spt) 
//  {
//  	res = BDTClassifier_BLIND_Function(3,0,pair.first,pair.second, 0,181, "NOMINAL");
//  	if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
//  }
//  for( auto pair : bin2spt) 
//  {
//  	res = BDTClassifier_BLIND_Function(2,0,pair.first,pair.second, 0,181, "NOMINAL");
//  	if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
//  }
//  for( auto pair : bin1spt) 
//  {
//  	res = BDTClassifier_BLIND_Function(1,0,pair.first,pair.second, 0,181, "NOMINAL");
  	res = BDTClassifier_BLIND_Function(1,0,0,30, 0,181, "");
  	res = BDTClassifier_BLIND_Function(2,0,0,30, 0,181, "continue");
  	res = BDTClassifier_BLIND_Function(3,0,0,30, 0,181, "continue");
  	if(!res)std::system(Form("rm ../.past_source/_BDT_Blind_Classifier_m7p512_dcaF%ld.old",(long) _real_time));
//  }
//  res = BDTClassifier_BLIND_Function(3,0,0,6, 0,181, "NOMINAL");
//  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
//  res = BDTClassifier_BLIND_Function(3,0,6,30, 0,181, "NOMINAL");
//  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
//  res = BDTClassifier_BLIND_Function(3,0,0,30, 0,181, "NOMINAL");
//  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
//  res = BDTClassifier_BLIND_Function(2,0,0,30, 0,181, "NOMINAL");
//  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
//  res = BDTClassifier_BLIND_Function(2,0,0,4, 0,181, "NOMINAL");
//  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
//  res = BDTClassifier_BLIND_Function(2,0,4,9, 0,181, "NOMINAL");
//  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
//  res = BDTClassifier_BLIND_Function(2,0,9,30, 0,181, "NOMINAL");
//  if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
//  tsrange.first = _real_time;
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
  //  res = BDTClassifier_BLIND_Function(0,6, 0,180);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
  //  res = BDTClassifier_BLIND_Function(6,30, 0, 180);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));

  //res = BDTClassifier_BLIND_Function(0,30, 0,40);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
  //  res = BDTClassifier_BLIND_Function(0,6, 0,40);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
  //  res = BDTClassifier_BLIND_Function(6,30,0, 40);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));

  //res = BDTClassifier_BLIND_Function(0,30, 40,100);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
  //  res = BDTClassifier_BLIND_Function(0,6, 40,100);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
  //  res = BDTClassifier_BLIND_Function(6,30,40, 100);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
  //
  //res = BDTClassifier_BLIND_Function(0,30, 100,180);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
  //  res = BDTClassifier_BLIND_Function(0,6, 100,180);
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));
  //  res = BDTClassifier_BLIND_Function(6,30, 100, 180);
  //tsrange.second = _real_time;
  //if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _real_time));

  //log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  //log << "TS coleection::{";
  //for ( const auto ts : v_real_time){ 
  //  log << Form(" %s,",ts);
  //} log << "}" << std::endl;

  //log << "Bin by Bin training end::" << Form("%ld,%ld",tsrange.first,tsrange.second) << std::endl;
  //log.close();
}
