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
#include "yield_eff_signif.cxx"
long _ts;
long _real_time;
char logbuf[2000];
long _ts_buf=0;

bool BDTClassifier_BLIND_Function(int state , int idx , double ptLow, double ptHigh, int cBinLow, int cBinHigh, std::string opt = "", long inputts =0, string bookOpt = "", string datprep =""){
  //Load Library
  ROOT::EnableImplicitMT(20);
  TMVA::Tools::Instance();
///////////////
  binplotter *bp2s = new binplotter("CB3:CC4:FF", 9999999999, 2.4, (int) ptLow, (int) ptHigh, cBinLow, cBinHigh,0.01, -1,1, (int) ptLow, (int) ptHigh, 0, 0,false,false );
  binplotter *bp3s = new binplotter("CB3:CC4:FF", 9999999999, 2.4, (int) ptLow, (int) ptHigh, cBinLow, cBinHigh,0.01, -1,1, (int) ptLow, (int) ptHigh, 0, 0,false,false );
  RooWorkspace* wsp = (RooWorkspace*) bp3s->file1->Get("workspace");
  auto ccpdf = (TF1*) wsp->pdf("CCBkg")->asTF(*(wsp->var("mass")));
  double yieldBkg = ( bp3s->get_bkg() ).getVal() *( ccpdf->Integral(8.8,10.7)/ ccpdf->Integral(8.,14.));
  double yield2S =bp2s->get_yield(2).getVal();
  if(yield2S <=0) yield2S= bp2s->get_yield(2).getVal()+ bp2s->get_yield(2).getError();
  if(yield2S <=0) yield2S = 0;
  double yield3S =bp3s->get_yield(3).getVal();
  if(yield3S <=0) yield3S= bp3s->get_yield(3).getVal()+ bp3s->get_yield(3).getError();
  if(yield3S <=0) yield3S = 0;
  std::cout << Form("[GOB] raw 2S, 3S yield : %.2f, %.2f ",yield2S, yield3S) << std::endl;

///////////////
  int traintree, testtree;
    traintree=1;
    testtree=1;

  std::time_t tstamp = inputts;
  _ts = inputts;
  (long) tstamp;
  if(_ts_buf==0) _ts_buf = _ts;
  if(strcmp(opt.c_str(), "continue")==0) _ts = _ts_buf;
  _ts_buf = _ts;
  _real_time = (long) tstamp;
  std::cout <<"time stamp---> " <<  tstamp << std::endl;
  if(strcmp(opt.c_str(),"NOMINAL")==0) _ts = (long) 10000000016;
  std::system(Form("cat BDTClassifier_BLIND_BDTCOMB.C >> ./.past_source/_BDTClassifier_BLIND_BDTCOMB_%ld.old",(long) tstamp));
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
  TFile* inputMC2S   ;
  TFile* inputMC3S   ;
  inputMC2S= new TFile(Form("%s/%s", store.Data(), ONIABDTMC2S_LATEST.c_str()),"read");
  inputMC3S= new TFile(Form("%s/%s", store.Data(), ONIABDTMC_LATEST.c_str()),"read");
  //new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/ForBDT/OutputSkim_isMC1_v210416.root","read");
  TFile* output;
  if(strcmp(opt.c_str(), "NOMINAL") ==0 ) output = new TFile(Form("%s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),_ts),"update");
  else if(strcmp(opt.c_str(), "continue") ==0) output = new TFile(Form("%s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),_ts),"update");
  else output = new TFile(Form("%s/BDTresultY3S_%ld_BLIND.root",BDTDir.Data(),_ts),"recreate");

  double ylim 		= 2.4;
  double massLow 	= 8;
  double massHigh 	= 14;
  double Simucut  	= 3.5;
  string HybSoft 	= "&&nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&fabs(dxy1)<0.3&&fabs(dxy2)<0.3&&fabs(dz1)<20&&fabs(dz2)<20";
  string rejectNAN 	= "&&!TMath::IsNaN(ctau)&&!TMath::IsNaN(ctau3D)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";//"&&!TMath::IsNaN(QQMassErr)&&!TMath::IsNaN(dxyErr1)&&!TMath::IsNaN(dxyErr2)&&!TMath::IsNaN(QQVtxProb)&&!TMath::IsNaN(QQdca)&&!TMath::IsNaN(cosAlpha)&&!TMath::IsNaN(cosAlpha3D)";
  TCut cut1 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>%f&&pt2>%f&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, Simucut, Simucut, ylim, HybSoft.c_str(),rejectNAN.c_str());
  TCut cut2 = Form("mass>%f&&mass<%f&&pt<%f&&pt>%f&&cBin>%d&&cBin<%d&&pt1>%f&&pt2>%f&&fabs(y)<%f%s%s", massLow, massHigh, ptHigh, ptLow, cBinLow, cBinHigh, Simucut, Simucut, ylim, HybSoft.c_str(),rejectNAN.c_str());

  TMVA::DataLoader *loader1 = new TMVA::DataLoader(Form("data/Y%dSpt%dto%d/dataset1", state, (int) ptLow, (int) ptHigh));
  TMVA::DataLoader *loader2 = new TMVA::DataLoader(Form("data/Y%dSpt%dto%d/dataset2", state, (int) ptLow, (int) ptHigh));
  TTree* SigTree2S =(TTree*) inputMC2S->Get("tree");
  TTree* SigTree3S =(TTree*) inputMC3S->Get("tree");
  TTree* BkgTreeTest_primary1 =(TTree*) inputDATA->Get(Form("tree3"));
  TTree* BkgTreeTest_primary2 =(TTree*) inputDATA->Get(Form("tree2"));
  TTree* BkgTreeTest1 = BkgTreeTest_primary1->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<14)");
  TTree* BkgTreeTest2 = BkgTreeTest_primary2->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<14)");

  BkgTreeTest1->SetName("tree3");
  BkgTreeTest2->SetName("tree2");
  TTree* BkgTreeTrain_primary1 =(TTree*) inputDATA->Get(Form("tree2"));
  TTree* BkgTreeTrain_primary2 =(TTree*) inputDATA->Get(Form("tree3"));
//  TTree* BkgTreeTrain0 = BkgTreeTrain_primary1->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<11.5)");
  TTree* BkgTreeTrain1 = BkgTreeTrain_primary1->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<14)");
  TTree* BkgTreeTrain2 = BkgTreeTrain_primary2->CopyTree("(mass>8.&&mass<8.6)||(mass>10.8&&mass<14)");
  std::cout << "Number of Events in Trees (Sig2S, Sig3S, BkgTest, BkgTrain) : ( " << SigTree2S->GetEntries(cut1) << ", "<< SigTree3S->GetEntries(cut1) << ", "<< BkgTreeTest1->GetEntries(cut2) << ", " << BkgTreeTrain2->GetEntries(cut2) << " )" << std::endl;
  //Factory Call
  TMVA::Factory *factory1 = new TMVA::Factory(Form("TMVA_BDT_Classifier1_%ld",_ts),  output, "V:Color:DrawProgressBar:Transformations=G+D:AnalysisType=Classification");
  TMVA::Factory *factory2 = new TMVA::Factory(Form("TMVA_BDT_Classifier2_%ld",_ts),  output, "V:Color:DrawProgressBar:Transformations=G+D::AnalysisType=Classification");
  for( auto loader : {loader1, loader2} ) 
  {
//    loader->AddVariable("QQMassErr", "Dimu Mass error", "F");
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
    Double_t backgroundWeight = 1; //1e-3;
	auto getSumW = [=] (TTree* t)
	{
		double _sumw = 0.;
		TTreeReader _tr(t);
		TTreeReaderValue<double> _wgt(_tr, "weight");
		TTreeReaderValue<double> _pt(_tr, "pt");
		TTreeReaderValue<double> _pt1(_tr, "pt1");
		TTreeReaderValue<double> _pt2(_tr, "pt2");
		TTreeReaderValue<int> _cbin(_tr, "cBin");
		while(_tr.Next()){
			if(  (*_pt <ptHigh && *_pt > ptLow) && (*_pt1 > Simucut && *_pt2 > Simucut ) && (*_cbin < cBinHigh && *_cbin > cBinLow)) _sumw += *_wgt;
		}
		std::cout << Form("Sum Weight For %s: %.3f", t->GetName(), _sumw) << std::endl;
		return _sumw;
	};

	double nSigTree2S = getSumW(SigTree2S);
	double nSigTree3S = getSumW(SigTree3S);
    loader1->AddSignalTree     (SigTree2S, (double) (signalWeight*yield2S/nSigTree2S));
    loader1->AddSignalTree     (SigTree3S, (double) (signalWeight*yield3S/nSigTree3S));
    loader2->AddSignalTree     (SigTree2S, (double) (signalWeight*yield2S/nSigTree2S));
    loader2->AddSignalTree     (SigTree3S, (double) (signalWeight*yield3S/nSigTree3S));
    loader1->AddBackgroundTree (BkgTreeTrain1,	backgroundWeight*yieldBkg/BkgTreeTrain1->GetEntries(cut1), "Train");
    loader1->AddBackgroundTree (BkgTreeTest1,	backgroundWeight*yieldBkg/BkgTreeTest1->GetEntries(cut1), "Test");
    loader2->AddBackgroundTree (BkgTreeTrain2,	backgroundWeight*yieldBkg/BkgTreeTrain2->GetEntries(cut2), "Train");
    loader2->AddBackgroundTree (BkgTreeTest2,	backgroundWeight*yieldBkg/BkgTreeTest2->GetEntries(cut2), "Test");

//	int nBkg_Smpl = 2*(BkgTreeTrain2->GetEntries(cut2)+ BkgTreeTrain1->GetEntries(cut2)) ;

    loader1->SetSignalWeightExpression("weight");
    loader2->SetSignalWeightExpression("weight");

//	datprep = datprep+ Form(":nTrain_Signal=%d:nTest_Signal=%d", nBkg_Smpl*2, nBkg_Smpl*2 );

    loader1->PrepareTrainingAndTestTree( cut1, cut2, datprep.c_str());
    loader2->PrepareTrainingAndTestTree( cut1, cut2, datprep.c_str());


  //Book Training BDT Method
  factory1->BookMethod( loader1, TMVA::Types::kBDT, TString::Format("BDT"  ),
//  	"!H:!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:Transformations=G+D+G+D+G"
		bookOpt.c_str()
  );//");
  factory2->BookMethod( loader2, TMVA::Types::kBDT, TString::Format("BDT"  ),
//  	"!H:!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.6:UseBaggedBoost:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:Transformations=G+D+G+D+G");//");
		bookOpt.c_str()
  );//");
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
void BDTClassifier_BLIND_BDTCOMB( long _inputts , string _bookOpt, string _datprep, bool nomonly = false){
  ofstream log;
  //log.open("BDT_description.log", std::ios_base::out|std::ios_base::app);
  //log << "Bin by Bin training start----------------------" <<std::endl; ; 
  //log.close();

  std::pair<long, long> tsrange;
  std::vector<long > v_ts;
  std::cout << "Write down description for this run :";
  strcpy(logbuf,  "NOMINAL, GAUS transformation, small Signal smaple, Gradboost5 fisher cuts ");
  bool res; 


  std::vector<std::pair<int, int> >bin1spt = {{0,30},{0, 4},{4, 9},{9, 12},{12,30},{12, 50}};//{/*{0,30},{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,8},{8,10},{10,12},{18,30}*/{12,18},{12,15},{15,30}};
  std::vector<std::pair<int, int> >bin2spt = {{0,30},{9, 15},{15,30}};//{/*{0,2},{2,4},{4,6},{6,9},{9,12},{12,15},{15,20},{12,20},{12,24},{20,50},{24,50},{30,50}*/{12,50}, {15, 50}};
//  std::vector<std::pair<int, int> >bin3spt = {{0,3}};//{/*{0,4},{4,9},{9,12},{12,15},{15,50},{12,24},{24,50},{12,20},{20,50},{12,30},{30,50},{15,30}*/};
  std::vector<std::pair<int, int> >bin3spt = {/*{0,30},{0,3},*/{3,6},{6,9},{0, 4},{4, 9},{9, 15},{15,30}};//{/*{0,4},{4,9},{9,12},{12,15},{15,50},{12,24},{24,50},{12,20},{20,50},{12,30},{30,50},{15,30}*/};
  if(!nomonly){
  for( auto pair : bin3spt) 
  {
  	res = BDTClassifier_BLIND_Function(3,0,pair.first,pair.second, 0,181, "NOMINAL", _inputts, _bookOpt, _datprep);
  	if(!res)std::system(Form("rm ./.past_source/_BDT_Blind_Classifier__BDT%ld.old",(long) _real_time));
  }

}
}
