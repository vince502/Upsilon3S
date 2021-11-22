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

std::vector<double> getEffhist_SYSDPT_NN(float pl, float ph, float yl, float yh, int cl, int ch, bool istnp, bool wei, long ts, double bdt_low, double bdt_high, int train_state =3,int state =3, double vcut =0.00, std::string what = "UP"){
  double ml, mh;
  auto mp = mass_rng(state);
  ml = mp.first;
  mh = mp.second;

  string fname =Form("%s/BDT/EffCalc/DNDPT/mc_eff_BDT_%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID", workdir.Data(), state, ts, bdt_low, bdt_high, pl, ph, yl, yh, 3.5, ml, mh, cl, ch, vcut, istnp, wei);
  if(ts >= 9999999990) fname =Form("%s/BDT/EffCalc/DNDPT/mc_eff_BDT_%dS_train%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_SYSDPT", workdir.Data(), state, train_state, ts, bdt_low, bdt_high, pl, ph, yl, yh, 3.5, ml, mh, cl, ch,vcut, istnp, wei);
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
  TH1D* rechist = (TH1D*) histfile->Get("hreco");
  TH1D* rechist_NU = (TH1D*) histfile->Get("hreco_NU");
  TH1D* rechist_ND = (TH1D*) histfile->Get("hreco_ND");
  TH1D* rechist_UN = (TH1D*) histfile->Get("hreco_UN");
  TH1D* rechist_DN = (TH1D*) histfile->Get("hreco_DN");
  std::vector<double> NumReco= {rechist->GetBinContent(1), rechist_NU->GetBinContent(1),rechist_ND->GetBinContent(1),rechist_UN->GetBinContent(1),rechist_DN->GetBinContent(1)};
  histfile->Close();
  return NumReco; 
};

std::vector<double> getEffhist_SYSDPT_NN(float pl, float ph, float yl, float yh, int cl, int ch, bool istnp, bool wei, int sw, int num_trig, int state =3, std::string what = "UP"){
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

  string fname =Form("%s/BDT/EffCalc/DNDPT/mc_eff_%dS_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d_TrigSel%s_SYSPT", workdir.Data(), state, pl, ph, yl, yh, 3.5, ml, mh, cl, ch, istnp, wei, ftrigSel.c_str());

  TFile* histfile = new TFile(Form("%s.root",fname.c_str()),"read");
  TList* list1 = (TList*) histfile->GetListOfKeys();
  TH1D* genhist = (TH1D*) histfile->Get("hgen");
  TH1D* genhist_NU = (TH1D*) histfile->Get("hgen_NU");
  TH1D* genhist_ND = (TH1D*) histfile->Get("hgen_ND");
  TH1D* genhist_UN = (TH1D*) histfile->Get("hgen_UN");
  TH1D* genhist_DN = (TH1D*) histfile->Get("hgen_DN");

  std::vector<double> NumGen = {genhist->GetBinContent(1), genhist_NU->GetBinContent(1),genhist_ND->GetBinContent(1),genhist_UN->GetBinContent(1),genhist_DN->GetBinContent(1)};
  return NumGen;
//  double NumGen[5] = {genhist->GetBinContent(1), genhist_NU->GetBinContent(1),genhist_ND->GetBinContent(1),genhist_UN->GetBinContent(1),genhist_DN->GetBinContent(1)};
//  for(int i = 0; i < 5; i++){
//    std::cout << NumGen[i] << std::endl;
//  }
//
//  double ErrGen = (double) genhist->GetBinError(1);
//  histfile->Close();
//
//  return new double*(NumGen);
};

std::vector<double> openEffhist_SYSDPT_NN(float _pl, float _ph, float _yl, float _yh, int _cl, int _ch, bool _istnp, bool wei, bool _sw, int kTrigSel, long _ts, double _bdt_tsl, double _bdt_tsh, int train_state =3, int state =3 , double _vcut = 0.00, std::string what = "UP", bool get_num = false){
  std::vector<double> gen = getEffhist_SYSDPT_NN( _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, _sw, kTrigSel, state, what);
  std::vector<double> reco = getEffhist_SYSDPT_NN( _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, _ts, _bdt_tsl, _bdt_tsh, train_state, state, _vcut, what);
  std::vector<double> BDTratio = { reco[0]/gen[0], reco[1]/gen[1], reco[2]/gen[2], reco[3]/gen[3], reco[4]/gen[4]}; 
  for(int i = 0; i < 5; i++){
    std::cout << Form("gen[i]: %.4f, reco[i]: %.4f)", gen[i], reco[i]) << std::endl;
    std::cout << BDTratio[i] << std::endl;
  }
  return BDTratio;
}
