#include <iostream>
#include "../commonUtility.h"
#include "../cutsAndBinUpsilonV2.h"
#include "../Style_jaebeom.h"
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

double getAccWeight(TH1D* h = 0, double pt = 0);
double getEffWeight(TH1D* h = 0, double pt = 0);
void GetHistSqrt(TH1D* h1 =0, TH1D* h2=0);

void makeRooDataset_fromBDT(long ts, bool cutID, bool isMC, std::string aux_opt = "nan"){
  string smc = "";
  if (isMC) smc = "_MC";
  if ( aux_opt!="nan") smc = "_"+aux_opt;

  TFile* rf; 
  if(aux_opt =="nan"){
  if(!isMC) rf = new TFile(Form("./BDTAppliedData/BDTApp_%ld.root",ts), "OPEN");
  else if(isMC) rf = new TFile(Form("./BDTAppliedData/BDTApp_%ld_MC.root",ts), "OPEN");
  }
  if(aux_opt !="nan") rf = new TFile(Form("./BDTAppliedData/BDTApp_%ld_%s.root",ts, aux_opt.c_str()), "OPEN");

  TTree* tree = (TTree*) rf->Get("tree");

  Int_t classID, cBin;
  Char_t className;
  Double_t  QQVtxProb, pt1, pt2, eta1, eta2, mass, y, weight, BDT, pBDT, pt;
  Double_t dz1, dz2, dxy1, dxy2;
  Int_t nTrkWMea1, nTrkWMea2, nPixWMea1, nPixWMea2;
  TBranch *b_dz1, *b_dz2, *b_dxy1, *b_dxy2, *b_nTrkWMea1, *b_nTrkWMea2, *b_nPixWMea1, *b_nPixWMea2;
  TBranch *b_classID, *b_className, *b_QQVtxProb, *b_cBin, *b_pt1, *b_pt2, *b_eta1, *b_eta2, *b_pt, *b_mass, *b_y, *b_weight, *b_BDT, *b_BDT_prob;
  
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
  if( cutID){
    tree ->SetBranchAddress("dz1", &dz1, &b_dz1);
    tree ->SetBranchAddress("dz2", &dz2, &b_dz2);
    tree ->SetBranchAddress("dxy1", &dxy1, &b_dxy1);
    tree ->SetBranchAddress("dxy2", &dxy2, &b_dxy2);
    tree ->SetBranchAddress("nTrkWMea1", &nTrkWMea1, &b_nTrkWMea1);
    tree ->SetBranchAddress("nTrkWMea2", &nTrkWMea2, &b_nTrkWMea2);
    tree ->SetBranchAddress("nPixWMea1", &nPixWMea1, &b_nPixWMea1);
    tree ->SetBranchAddress("nPixWMea2", &nPixWMea2, &b_nPixWMea2);
  }
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
    if((i%10000)==0)std::cout<< "Fetching index : " << i << "\n";
    tree->GetEntry(i);
    if( !(fabs(dz1)<0.3&&fabs(dz2)<0.3&&fabs(dxy1)<20&&fabs(dxy2)<20&&nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5 && pt1>3.5&&pt2>3.5) ) continue;
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

