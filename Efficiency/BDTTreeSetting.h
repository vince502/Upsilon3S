#ifndef BDTTreeSetting_h
#define BDTTreeSetting_h

#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "TROOT.h"
#include "TClonesArray.h"
#include "TChain.h"

using namespace std;


#if !defined(TreeSetting_h)
extern const long int maxBranchSize = 100000;
#endif

// import the tree to the RooDataSet
int		 cBin;
int		 nTrkHits1;
int		 nTrkHits2;
int		 normChi2_global1;
int		 normChi2_global2;
int		 nMuValHits1;
int		 nMuValHits2;
int		 StationsMatched1;
int		 StationsMatched2;
int		 nPixWMea1;
int		 nPixWMea2;
int		 nTrkWMea1;
int		 nTrkWMea2;
int		 ctau;
int		 ctau3D;
int		 highPurity1;
int		 highPurity2;
double		 mass;
double		 pt;
double		 y;
double		 pt1;
double		 pt2;
double		 eta1;
double		 eta2;
double		 eta;
double		 dxy1;
double		 dxy2;
double		 dz1;
double		 dz2;
double		 dxyErr1;
double		 dxyErr2;
double		 dzErr1;
double		 dzErr2;
double		 QQVtxProb;
double		 QQMassErr;
double		 normChi2_inner1;
double		 normChi2_inner2;
double		 ptErr_inner1;
double		 ptErr_inner2;
double		 weight;
double		 tnp_weight;
double		 pt_weight;
double		 BDT;

//  muon id 
/////////////////////////////////////////
////// Gen QQ 
/////////////////////////////////////////
// NO Gen Info
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~//
//~*~*~*~*~*~*~*Conversion~*~*~*~*~*~*~*~*~//
//~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~//

class SetTreeBDT
{
  public:
    SetTreeBDT(){};

    virtual ~SetTreeBDT();
    virtual void TreeSetting(TTree* tree, bool NOM, int train_state, int ptLow, int ptHigh);
};

SetTreeBDT::~SetTreeBDT()
{
}


void SetTreeBDT::TreeSetting(TTree* tree, bool NOM ,int train_state, int ptLow, int ptHigh)
{
  tree->SetBranchAddress("mass", &mass);
  tree->SetBranchAddress("cBin", &cBin);
  tree->SetBranchAddress("pt", &pt);
  tree->SetBranchAddress("y", &y);
  tree->SetBranchAddress("pt1", &pt1);
  tree->SetBranchAddress("pt2", &pt2);
  tree->SetBranchAddress("eta1", &eta1);
  tree->SetBranchAddress("eta2", &eta2);
  tree->SetBranchAddress("eta", &eta);
  tree->SetBranchAddress("weight", &weight);
  tree->SetBranchAddress("tnp_weight", &tnp_weight);
  tree->SetBranchAddress("pt_weight", &pt_weight);
  tree->SetBranchAddress("QQVtxProb", &QQVtxProb);
  if(!NOM)  tree->SetBranchAddress("BDT", &BDT);
  if(NOM){if( tree->SetBranchAddress(Form("BDTY%dSpt%dto%d", train_state, ptLow, ptHigh), &BDT)<0){ std::cout << Form("[Error] NO BDT BRANCH in tree \"%s\" \"BDTY%dSpt%dto%d\"! ", tree->GetName(), train_state, ptLow, ptHigh) <<std::endl; throw std::exception();}}
  tree->SetBranchAddress("nTrkWMea1", &nTrkWMea1);
  tree->SetBranchAddress("nTrkWMea2", &nTrkWMea2);
  tree->SetBranchAddress("nPixWMea2", &nPixWMea2);
  tree->SetBranchAddress("nPixWMea1", &nPixWMea1);
  tree->SetBranchAddress("dxy1", &dxy1);
  tree->SetBranchAddress("dxy2", &dxy2);
  tree->SetBranchAddress("dz1", &dz1);
  tree->SetBranchAddress("dz2", &dz2);

};

class SetTreeBDT_SYSREF
{
  public:
    SetTreeBDT_SYSREF(){};

    virtual ~SetTreeBDT_SYSREF();
    virtual void TreeSetting(TTree* tree, bool NOM, int train_state, int ptLow, int ptHigh);
};

SetTreeBDT_SYSREF::~SetTreeBDT_SYSREF()
{
}


void SetTreeBDT_SYSREF::TreeSetting(TTree* tree, bool NOM ,int train_state, int ptLow, int ptHigh)
{
  tree->SetBranchStatus("weight", 0);
  tree->SetBranchStatus("tnp_weight", 0);
  tree->SetBranchStatus("pt_weight", 0);
  tree->SetBranchAddress("mass", &mass);
  tree->SetBranchAddress("cBin", &cBin);
  tree->SetBranchAddress("pt", &pt);
  tree->SetBranchAddress("y", &y);
  tree->SetBranchAddress("pt1", &pt1);
  tree->SetBranchAddress("pt2", &pt2);
  tree->SetBranchAddress("eta1", &eta1);
  tree->SetBranchAddress("eta2", &eta2);
  tree->SetBranchAddress("eta", &eta);
  if(!NOM)  tree->SetBranchAddress("BDT", &BDT);
  if(NOM){if( tree->SetBranchAddress(Form("BDTY%dSpt%dto%d", train_state, ptLow, ptHigh), &BDT)<0){ std::cout << "[Error] NO BDT BRANCH! " <<std::endl; throw std::exception();}}
  tree->SetBranchAddress("QQVtxProb", &QQVtxProb);
  tree->SetBranchAddress("nTrkWMea1", &nTrkWMea1);
  tree->SetBranchAddress("nTrkWMea2", &nTrkWMea2);
  tree->SetBranchAddress("nPixWMea2", &nPixWMea2);
  tree->SetBranchAddress("nPixWMea1", &nPixWMea1);
  tree->SetBranchAddress("dxy1", &dxy1);
  tree->SetBranchAddress("dxy2", &dxy2);
  tree->SetBranchAddress("dz1", &dz1);
  tree->SetBranchAddress("dz2", &dz2);
};

class SetTreeSYS
{
  public:
    SetTreeSYS(){};

    virtual ~SetTreeSYS();
    virtual void TreeSetting(TTree* tree, bool NOM, int train_state, int ptLow, int ptHigh);
    double i_weight, i_tnp_weight, i_pt_weight;
};

SetTreeSYS::~SetTreeSYS()
{
}


void SetTreeSYS::TreeSetting(TTree* tree, bool NOM ,int train_state, int ptLow, int ptHigh)
{
  tree->SetBranchStatus("*", 0);
  tree->SetBranchStatus("weight", 1);
  tree->SetBranchStatus("tnp_weight", 1);
  tree->SetBranchStatus("pt_weight", 1);
  tree->SetBranchAddress("weight", &i_weight);
  tree->SetBranchAddress("tnp_weight", &i_tnp_weight);
  tree->SetBranchAddress("pt_weight", &i_pt_weight);

};


#endif 
