#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <TFile.h>
#include <TH1D.h>
#include "../../cutsAndBinUpsilonV2.h"
#include "../../Efficiency/getEfficiencyBDT.C"
#include "../../Efficiency/getEfficiencyBDT_V3.C"
#include "../bininfo.h"
//#include "../../Efficiency/getEfficiency.C"
//
extern TString histName;
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

std::vector<double> getEffhist_SYS(float pl, float ph, float yl, float yh, int cl, int ch, bool istnp, bool wei, long ts, double bdt_low, double bdt_high, int bpl, int bph, int train_state =3,int state =3, double vcut =0.00, bool eff_old = false){
  double ml, mh;
  auto mp = mass_rng(state);
  ml = mp.first;
  mh = mp.second;
  string fname = GetEffNum(__FITRESLATEST, ts,train_state, state, bpl, bph, yl, yh, 3.5, ml, mh, cl, ch, vcut, istnp, wei);
//  string fname =Form("%s/BDT/EffCalc/mc_eff_BDT_%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID", workdir.Data(), state, ts, bdt_low, bdt_high, pl, ph, yl, yh, 3.5, ml, mh, cl, ch, vcut, istnp, wei);
//  if(ts >= 1634636609 && !eff_old) fname =Form("%s/BDT/EffCalc/mc_eff_BDT_%dS_train%dS_bdtpt%d-%d_%ld_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_fix_test", workdir.Data(), state, train_state, ts, bpl, bph, yl, yh, 3.5, ml, mh, cl, ch,vcut, istnp, wei);
 // if(ts >= 1634636609 && eff_old) fname =Form("%s/BDT/EffCalc/mc_eff_BDT_%dS_train%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID", workdir.Data(), state, train_state, ts, bdt_low, bdt_high, pl, ph, yl, yh, 3.5, ml, mh, cl, ch,vcut, istnp, wei);
  // if(!TFile::Open(Form("%s.root",fname.c_str()),"read")){
//    std::cout << "-----Calculate new Efficiency for current parameters-----" << std::endl;
//    string command = Form("root -l -b -q \'/home/vince402/Upsilon3S/Efficiency/getEfficiencyBDT.C(%.2f, %.2f, %.2f, %.2f, %d, %d, %d, %d, %ld, %.3f, %.5f, %d)\'",pl, ph, yl, yh, cl, ch, (int) istnp, (int) wei, ts, bdt_low, bdt_high, state);
//    int a = system(command.c_str());
  TFile* histfile = nullptr;
  histfile = new TFile(Form("%s",fname.c_str()),"read");
  std::cout << Form("%d, %d", bpl, bph) << std::endl;
  if(histfile == nullptr || histfile->IsZombie()){
    if (ts >= 1634636609 && !eff_old)getEfficiencyBDT_V3(pl, ph, yl, yh, cl, ch, istnp, wei, ts, bdt_low, bdt_high, bpl, bph, train_state, state, vcut); 
    else{ std::cout << "Running Legacy" << std::endl; getEfficiencyBDT(pl, ph, yl, yh, cl, ch, istnp, wei, ts, bdt_low, bdt_high, train_state, state, vcut); }
    histfile = new TFile(Form("%s",fname.c_str()),"read");
  }
  //}

  std::cout << fname.c_str() << std::endl;
  TList* list1 = (TList*) histfile->GetListOfKeys();
  std::cout<< list1->At(0)->GetName() << std::endl;
  TH3F* rechist = (TH3F*) histfile->Get("hreco");
  TH3F* rechist_NU = (TH3F*) histfile->Get("hreco_NU");
  TH3F* rechist_ND = (TH3F*) histfile->Get("hreco_ND");
  TH3F* rechist_UN = (TH3F*) histfile->Get("hreco_UN");
  TH3F* rechist_DN = (TH3F*) histfile->Get("hreco_DN");

  double NumReco, ErrReco;
  std::vector<double> v_NumReco;
  if (ts >= 1634636609 && !eff_old){
  	int ibdt_low = (bdt_low+1.0000)*10000 + 1;
	int ibdt_high = (bdt_high+1.0000)*10000 ;
	int ipl = (int) pl + 1;
	int iph = (int) ph;
	int chidx = (ch == 181) ? 180 : chidx;
	int cl_idx = cl/5; 
	int ch_idx = ch/5;
  	NumReco = rechist->Integral(ibdt_low, ibdt_high, pl+1, ph, cl_idx +1 , ch_idx);
  	ErrReco = TMath::Sqrt(NumReco);
	v_NumReco ={
		NumReco,
		rechist_NU->Integral(ibdt_low, ibdt_high, pl+1, ph, cl_idx +1 , ch_idx),
		rechist_ND->Integral(ibdt_low, ibdt_high, pl+1, ph, cl_idx +1 , ch_idx),
		rechist_UN->Integral(ibdt_low, ibdt_high, pl+1, ph, cl_idx +1 , ch_idx),
		rechist_DN->Integral(ibdt_low, ibdt_high, pl+1, ph, cl_idx +1 , ch_idx),
	};
  }
  else{
 	NumReco= rechist->GetBinContent(1);
  	ErrReco = rechist->GetBinError(1);
  }
  histfile->Close();
  return v_NumReco;
};

std::vector<double> getEffhist_SYS(float pl, float ph, float yl, float yh, int cl, int ch, bool istnp, bool wei, int sw, int num_trig, int state =3){
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

//  string fname =Form("%s/BDT/EffCalc/mc_eff_%dS_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d_TrigSel%s", workdir.Data(), state, pl, ph, yl, yh, 3.5, ml, mh, cl, ch, istnp, wei, ftrigSel.c_str());
  string fname = GetEffDen(__FITRESLATEST, state, ml, mh); 

  TFile* histfile = new TFile(fname.c_str(),"read");
  TList* list1 = (TList*) histfile->GetListOfKeys();
  TH2D* genhist = (TH2D*) histfile->Get("hgen");
  TH2F* genhist_NU = (TH2F*) histfile->Get("hgen_NU");
  TH2F* genhist_ND = (TH2F*) histfile->Get("hgen_ND");
  TH2F* genhist_UN = (TH2F*) histfile->Get("hgen_UN");
  TH2F* genhist_DN = (TH2F*) histfile->Get("hgen_DN");

  double NumGen, ErrGen;
  int chidx = (ch ==181) ? 180 : chidx;
  int cl_idx = cl/5;
  int ch_idx = ch/5;
  NumGen = genhist->Integral(pl+1,ph,cl_idx+1, ch_idx);
  std::vector<double> v_NumGen;
  v_NumGen ={
	NumGen,
	genhist_NU->Integral(pl+1, ph, cl_idx +1 , ch_idx),
	genhist_ND->Integral(pl+1, ph, cl_idx +1 , ch_idx),
	genhist_UN->Integral(pl+1, ph, cl_idx +1 , ch_idx),
	genhist_DN->Integral(pl+1, ph, cl_idx +1 , ch_idx),
  };
  ErrGen = TMath::Sqrt(NumGen);
  histfile->Close();

  return v_NumGen;
};

std::vector<double> openEffhist_SYS(float _pl, float _ph, float _yl, float _yh, int _cl, int _ch, bool _istnp, bool wei, bool _sw, int kTrigSel, long _ts, double _bdt_tsl, double _bdt_tsh, int _bdtptMin, int _bdtptMax, int train_state =3, int state =3 , double _vcut = 0.00, bool eff_old = false, bool get_num = false){
  std::vector<double> gen = getEffhist_SYS( _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, _sw, kTrigSel, state);
  std::vector<double> reco = getEffhist_SYS( _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, _ts, _bdt_tsl, _bdt_tsh, _bdtptMin, _bdtptMax, train_state, state, _vcut, eff_old);
  std::vector<double> BDTratio = { reco[0]/gen[0],reco[1]/gen[1],reco[2]/gen[2],reco[3]/gen[3],reco[4]/gen[4] };
  return BDTratio;
}
