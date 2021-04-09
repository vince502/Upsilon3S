#include <iostream>
#include "../commonUtility.h"
#include "../cutsAndBinUpsilonV2.h"
#include "../HiEvtPlaneList.h"
#include "../Style_jaebeom.h"
#include "../tdrstyle.C"
#include "../CMS_lumi_v2mass.C"
#include "../rootFitHeaders.h"
#include <RooGaussian.h>
#include <RooCBShape.h>
#include <RooWorkspace.h>
#include <RooChebychev.h>
#include <RooPolynomial.h>
#include "RooPlot.h"
#include "TText.h"
#include "TArrow.h"
#include "TFile.h"

using namespace std;
using namespace RooFit;

using namespace hi;

double getAccWeight(TH1D* h = 0, double pt = 0);
double getEffWeight(TH1D* h = 0, double pt = 0);
void GetHistSqrt(TH1D* h1 =0, TH1D* h2=0);

void makeRooDataset_fromBDT(long ts, bool isMC){
  string smc = "";
  if (isMC) smc = "_MC";

  TFile* rf; 
  if(!isMC) rf = new TFile(Form("./BDTAppliedData/BDTApp_%ld.root",ts), "OPEN");
  else if(isMC) rf = new TFile(Form("./BDTAppliedData/BDTApp_%ld_MC.root",ts), "OPEN");
  TTree* tree = (TTree*) rf->Get("tree");

  Int_t classID, cBin;
  Char_t className;
  Double_t  QQVtxProb, pt1, pt2, eta1, eta2, mass, y, weight, BDT, pBDT, pt;
  TBranch *b_classID, *b_className, *b_QQVtxProb, *b_cBin, *b_pt1, *b_pt2, *b_eta1, *b_eta2, *b_pt, *b_mass, *b_y, *b_weight, *b_BDT, *b_BDT_prob;
  
//  tree -> SetBranchAddress("classID", &classID, &b_classID);
//  tree -> SetBranchAddress("className", &className, &b_className);
  tree -> SetBranchAddress("QQVtxProb", &QQVtxProb, &b_QQVtxProb);
  tree -> SetBranchAddress("pt1", &pt1, &b_pt1);
  tree -> SetBranchAddress("pt2", &pt2, &b_pt2);
  tree -> SetBranchAddress("eta1", &eta1, &b_eta1);
  tree -> SetBranchAddress("eta2", &eta2, &b_eta2);
  tree -> SetBranchAddress("y", &y, &b_y);
  tree -> SetBranchAddress("pt", &pt, &b_pt);
  tree -> SetBranchAddress("cBin", &cBin, &b_cBin);
  tree -> SetBranchAddress("mass", &mass, &b_mass);
  tree -> SetBranchAddress("weight", &weight, &b_weight);
  tree -> SetBranchAddress("BDT", &BDT, &b_BDT);
//  tree -> SetBranchAddress(Form("prob_BDT_train_%s",ts.c_str()), &pBDT, &b_BDT_prob);


  ////////////////////////////////////////////////////////////////////////
  //////////////////  RooDataSet 
  ////////////////////////////////////////////////////////////////////////
  RooRealVar* massVar  = new RooRealVar("mass","mass variable",0,200,"GeV/c^{2}");
  RooRealVar* ptVar    = new RooRealVar("pt","pt variable", 0,100,"GeV/c");
  RooRealVar* yVar     = new RooRealVar("y","rapidity of the dimuon pair", -5,5,"");
  RooRealVar* pt1Var   = new RooRealVar("pt1","pt of muon+", 0,500,"GeV/c");
  RooRealVar* eta1Var  = new RooRealVar("eta1","eta of muon+", -4,4,"");
  RooRealVar* pt2Var   = (RooRealVar*)pt1Var->Clone("pt2");
  RooRealVar* eta2Var  = (RooRealVar*)eta1Var->Clone("eta2");
  RooRealVar* cBinVar   = new RooRealVar("cBin","Centrality bin", -100,500,"");
  RooRealVar* evtWeight = new RooRealVar("weight","corr weight", 0, 10000,"");
  RooRealVar* QQVPVar  = new RooRealVar("QQVtxProb", "dimuon Vertex Probability", 0,1, ""); 
  RooRealVar* BDTVar   = new RooRealVar("BDT", "BDT score", -1,1, ""); 
//  RooRealVar* pBDTVar  = new RooRealVar("pBDT", "BDT probabilty", 0,1, ""); 
  RooArgSet* argSet    = new RooArgSet(*massVar, *ptVar, *yVar, *pt1Var, *pt2Var, *eta1Var, *eta2Var,*evtWeight);
  argSet->add(*cBinVar);argSet->add(*QQVPVar); argSet->add(*BDTVar);// argSet->add(*pBDTVar);//argSet->add(*ctau3D);
  
  RooDataSet* dataSet  = new RooDataSet("dataset", " a dataset", *argSet);

  //Begin Dimuon Loop
  Int_t nEvt = tree->GetEntries();
  std::cout << "nEvt :" << nEvt<< std::endl;
  for(int i=0; i < nEvt; i++){
    if((i%10000)==0)std::cout<< "Fetching index : " << i << "\r";
    tree->GetEntry(i);
  //  if(!strcmp(&className,"Background")){
      massVar->setVal( (double)mass ) ;
      ptVar->setVal(   (double)pt   ) ;
      yVar->setVal(    (double)y    ) ;
      pt1Var->setVal(  (double)pt1  ) ;
      eta1Var->setVal( (double)eta1 ) ;
      pt2Var->setVal(  (double)pt2  ) ;
      eta2Var->setVal( (double)eta2 ) ;
      cBinVar->setVal( (double)cBin ) ;
      evtWeight->setVal( (double) 1.0) ;
      QQVPVar->setVal( (double)QQVtxProb ) ;
      BDTVar-> setVal( (double)BDT ) ;
//      pBDTVar->setVal( (double)pBDT ) ;
      dataSet->add( *argSet);
//    }
  }
  TFile* wf = new TFile(Form("roodatasets/OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT%s.root",ts,smc.c_str()),"recreate");
  wf->cd();
  dataSet->Write();
  wf->Write();
}

