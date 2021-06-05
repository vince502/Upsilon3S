#include <iostream>
#include <cstdlib>
#include <string>
#include <TFile.h>
#include <TH1D.h>
#include "../../cutsAndBinUpsilonV2.h"
//#include "../../Efficiency/getEfficiencyBDT.C"
#include "../../Efficiency/getEfficiency.C"

double getEffhist(string what,float pl, float ph, float yl, float yh, int cl, int ch, bool istnp, bool wei, int opt1, double opt2, double opt22, int opt3){

TString histName;

if(what=="reco"){
  string fname =Form("/home/vince402/Upsilon3S/BDT/EffCalc/mc_eff_BDT_%d_bdt_%.3f-%.3f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d", opt1, opt2, opt22, pl, ph, yl, yh, 3.5, 9.0, 11.0, cl, ch, istnp, wei);
  // if(!TFile::Open(Form("%s.root",fname.c_str()),"read")){
    std::cout << "-----Calculate new Efficiency for current parameters-----" << std::endl;
    string command = Form("root -l -b -q \'/home/vince402/Upsilon3S/Efficiency/getEfficiencyBDT.C(%.2f, %.2f, %.2f, %.2f, %d, %d, %d, %d, %ld, %.3f, %.5f)\'",pl, ph, yl, yh, cl, ch, (int) istnp, (int) wei, (long) opt1, opt2, opt22);
    int a = system(command.c_str());
    getEfficiencyBDT(pl, ph, yl, yh, cl, ch, istnp, wei, (long) opt1, opt2, opt22); 
  //}
  TFile* histfile = new TFile(Form("%s.root",fname.c_str()),"read");
  std::cout << fname.c_str() << std::endl;
  TList* list1 = (TList*) histfile->GetListOfKeys();
  TH1D* rechist = (TH1D*) histfile->Get(list1->At(1)->GetName());
  double NumReco = rechist->GetBinContent(1);
  return NumReco;
  
}

else if(what=="gen"){
  int kTrigSel_;
  if ( opt3 == kTrigUps ) kTrigSel_=1;
  else if( opt3 == kTrigL1DBOS40100 ) kTrigSel_=2;
  string ftrigSel = (opt1) ? "SwtichOn" : "SwitchOff";
  if(opt1) ftrigSel += "_UpsAndL1OS40100";
  else if (!opt1) ftrigSel += Form("_%s",fTrigName[kTrigSel_].Data());

  string fname =Form("/home/vince402/Upsilon3S/BDT/EffCalc/mc_eff_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d_TrigSel%s", pl, ph, yl, yh, 3.5, 9.0, 11.0, cl, ch, istnp, wei, ftrigSel.c_str());
//   if(!TFile::Open(Form("%s.root",fname.c_str()),"read")){
//    std::cout << "-----Calculate new Efficiency for current parameters-----" << std::endl;
    getEfficiency(pl, ph, yl, yh, cl, ch, istnp, wei, opt1, opt3, true); 
//  }

  TFile* histfile = new TFile(Form("%s.root",fname.c_str()),"read");
  TList* list1 = (TList*) histfile->GetListOfKeys();
  TH1D* genhist = (TH1D*) histfile->Get(list1->At(2)->GetName());

  double NumGen = (double) genhist->GetBinContent(1);

  return NumGen;

}

else return 10000.0;

};

double openEffhist(float _pl, float _ph, float _yl, float _yh, int _cl, int _ch, bool _istnp, bool wei, bool _sw, int kTrigSel, int _ts, double _bdt_tsl, double _bdt_tsh ){
  double gen = getEffhist("gen", _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, (int) _sw, 0.,0., kTrigSel);
  double reco = getEffhist("reco", _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, _ts, _bdt_tsl, _bdt_tsh, 0);
  double BDTratio = reco/gen;
  std::cout << Form("Efficiency of BDT %d, ", _ts) << Form("Cut %f-%f : ", _bdt_tsl, _bdt_tsh) << BDTratio << std::endl;
  return BDTratio;
}
