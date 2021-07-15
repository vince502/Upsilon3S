#include <cstdlib>
#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"
#include "TXMLDocument.h"
#include "bininfo.h"
#include "../.workdir.h"



void CompareBDTs(long ts)
{
  auto bdtinfo = info_BDT(ts);
  long ts_pair = stol(parser_symbol(bdtinfo[5], "->")[1]);
  std::cout << ts_pair<< std::endl;

  TFile *f1_D, *f2_D;
  TFile *f1_M, *f2_M;

  f1_D = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_%ld.root", workdir.Data(), ts));
  f2_D = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_%ld.root", workdir.Data(), ts_pair));
  f1_M = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_%ld_MC.root", workdir.Data(), ts));
  f2_M = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_%ld_MC.root", workdir.Data(), ts_pair));

  TTree *t1_D, *t2_D;
  TTree *t1_M, *t2_M;
  std::cout << f1_D->GetName() << std::endl; 
  std::cout << f2_D->GetName() << std::endl; 
  t1_D = (TTree*) f1_D->Get("tree");
  t2_D = (TTree*) f2_D->Get("tree");
  std::string iDcut = "nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&fabs(dxy1)<20&&fabs(dxy2)< 20 &&fabs(dz1) <0.3&&fabs(dz2)<0.3";

}

TH1D Draw_func(TTree* tree, double bdt, bool iD = true, bool jpsiacc = true)
{
  TH1D hist = TH1D("hist","",70, 8, 11.5);
  if(iD)
  {
    
    tree->Draw(Form(" \"mass>>hist()\", \"nPixWMea1 > 0 && nPixWMea2 >0 && nTrkWMea1 >5 && nTrkWMea2 >5 && fabs(dz1) <20 &&fabs(dz2) <20 && fabs(dxy1)< 0.3 && fabs(dxy2) < 0.3 && pt1 > 3.5 && pt2 > 3.5 && fabs(eta1) < 2.4 &&fabs(eta2) < 2.4 && cBin>=0 && cBin < 181 && fabs(y) < 2.4&&  BDT > %.f \"", bdt) );
  }
  return hist;
}
