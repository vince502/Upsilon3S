#include <iostream>
#include <cstdlib>
#include <string>
#include <TFile.h>
#include <TH1D.h>
#include "../../../cutsAndBinUpsilonV2.h"
//#include "../../Efficiency/getEfficiencyBDT.C"
#include "../../bininfo.h"
//#include "../../Efficiency/getEfficiency.C"
//
//TString histName;
//std::pair<double, double> mass_rng(int state){
//  if(state ==1){
//    	return std::make_pair(8.8, 10.2);
//  }
//    if(state ==2){
//    	return std::make_pair(9.3, 10.7);
//    }
//    if(state ==3){
//    	return std::make_pair(9.6, 11.0);
//    }
//    else{
//    	return std::make_pair(9.0, 11.0);
//    }
//
//};

std::pair<double, double> getEffhist_SYSDPT(float pl, float ph, float yl, float yh, int cl, int ch, bool istnp, bool wei, long ts, double bdt_low, double bdt_high, int train_state =3,int state =3, double vcut =0.00, std::string what = "UP"){
  double ml, mh;
  auto mp = mass_rng(state);
  ml = mp.first;
  mh = mp.second;

  string fname =Form("%s/BDT/EffCalc/DNDPT/mc_eff_BDT_%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID", workdir.Data(), state, ts, bdt_low, bdt_high, pl, ph, yl, yh, 3.5, ml, mh, cl, ch, vcut, istnp, wei);
  if(ts >= 9999999990) fname =Form("%s/BDT/EffCalc/DNDPT/mc_eff_BDT_%dS_train%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_SYSPT%s", workdir.Data(), state, train_state, ts, bdt_low, bdt_high, pl, ph, yl, yh, 3.5, ml, mh, cl, ch,vcut, istnp, wei, what.c_str());
  // if(!TFile::Open(Form("%s.root",fname.c_str()),"read")){
//    std::cout << "-----Calculate new Efficiency for current parameters-----" << std::endl;
//    string command = Form("root -l -b -q \'/home/vince402/Upsilon3S/Efficiency/getEfficiencyBDT.C(%.2f, %.2f, %.2f, %.2f, %d, %d, %d, %d, %ld, %.3f, %.5f, %d)\'",pl, ph, yl, yh, cl, ch, (int) istnp, (int) wei, ts, bdt_low, bdt_high, state);
//    int a = system(command.c_str());
  TFile* histfile = nullptr;
  histfile = new TFile(Form("%s.root",fname.c_str()),"read");
  if(histfile == nullptr || histfile->IsZombie()){
//    getEfficiencyBDT(pl, ph, yl, yh, cl, ch, istnp, wei, ts, bdt_low, bdt_high, train_state, state, vcut); 
//    histfile = new TFile(Form("%s.root",fname.c_str()),"read");
    std::cout << " NO FILE : " << fname.c_str() << ".root" << std::endl;
  }
  //}

  std::cout << fname.c_str() << std::endl;
  TList* list1 = (TList*) histfile->GetListOfKeys();
  TH1D* rechist = (TH1D*) histfile->Get(list1->At(0)->GetName());
  double NumReco = rechist->GetBinContent(1);
  double ErrReco = rechist->GetBinError(1);
  histfile->Close();
  return std::make_pair(NumReco, ErrReco);
};

std::pair<double, double> getEffhist_SYSDPT(float pl, float ph, float yl, float yh, int cl, int ch, bool istnp, bool wei, int sw, int num_trig, int state =3, std::string what = "UP"){
  double ml, mh;
  auto mp = mass_rng(state);
  ml = mp.first;
  mh = mp.second;

  int kTrigSel_;
  if ( num_trig == kTrigUps ) kTrigSel_=1;
  else if( num_trig == kTrigL1DBOS40100 ) kTrigSel_=2;
  string ftrigSel = (sw) ? "SwtichOn" : "SwitchOff";
  if(sw) ftrigSel += "_UpsAndL1OS40100";
  else if (!sw) ftrigSel += Form("_%s",fTrigName[kTrigSel_].Data());

  string fname =Form("%s/BDT/EffCalc/DNDPT/mc_eff_%dS_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d_TrigSel%s_SYSPT%s", workdir.Data(), state, pl, ph, yl, yh, 3.5, ml, mh, cl, ch, istnp, wei, ftrigSel.c_str(), what.c_str());

  TFile* histfile = new TFile(Form("%s.root",fname.c_str()),"read");
  TList* list1 = (TList*) histfile->GetListOfKeys();
  TH1D* genhist = (TH1D*) histfile->Get(list1->At(0)->GetName());

  double NumGen = (double) genhist->GetBinContent(1);
  double ErrGen = (double) genhist->GetBinError(1);
  histfile->Close();

  return std::make_pair(NumGen,ErrGen);
};

std::pair<double, double> openEffhist_SYSDPT(float _pl, float _ph, float _yl, float _yh, int _cl, int _ch, bool _istnp, bool wei, bool _sw, int kTrigSel, long _ts, double _bdt_tsl, double _bdt_tsh, int train_state =3, int state =3 , double _vcut = 0.00, std::string what = "UP", bool get_num = false){
  std::pair<double, double> gen = getEffhist_SYSDPT( _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, _sw, kTrigSel, state, what);
  std::pair<double, double> reco = getEffhist_SYSDPT( _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, _ts, _bdt_tsl, _bdt_tsh, train_state, state, _vcut, what);
  double BDTratio = reco.first/gen.first;
  double BDTratioErr = BDTratio*TMath::Sqrt(TMath::Power(reco.second/reco.first,2)+TMath::Power(gen.second/gen.first,2));
  std::cout << Form( "[DIAGNOSIS] DNDPT %s NUMGEN, NUMREO= (%.1f, %.1f)", what.c_str(), gen.first, reco.first) << std::endl;
  std::cout << Form("[SYSTEMATIC] Efficiency of BDT %ld, ", _ts) << Form("Cut %f-%f : ", _bdt_tsl, _bdt_tsh) << BDTratio << ", " << BDTratioErr<< std::endl;
  if (get_num) return std::make_pair(gen.first, reco.first);
  else return std::make_pair(BDTratio, BDTratioErr);
}
