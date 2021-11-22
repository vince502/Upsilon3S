#include <iostream>
#include <cstdlib>
#include <string>
#include <TFile.h>
#include <TH1D.h>
#include "../../cutsAndBinUpsilonV2.h"
#include "../../Efficiency/getEfficiencyBDT.C"
#include "../../Efficiency/getEfficiencyBDT_V2.C"
#include "../bininfo.h"
//#include "../../Efficiency/getEfficiency.C"
//
extern TString histName;
extern std::pair<double, double> mass_rng(int state){
  if(state ==1){
    	return std::make_pair(8.8, 10.2);
  }
    if(state ==2){
    	return std::make_pair(9.3, 10.7);
    }
    if(state ==3){
    	return std::make_pair(9.6, 11.0);
    }
    else{
    	return std::make_pair(9.0, 11.0);
    }

};

std::pair<double, double> getEffhist(float pl, float ph, float yl, float yh, int cl, int ch, bool istnp, bool wei, long ts, double bdt_low, double bdt_high, int bpl, int bph, int train_state =3,int state =3, double vcut =0.00, bool eff_old = false){
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
    if (ts >= 1634636609 && !eff_old)getEfficiencyBDT_V2(pl, ph, yl, yh, cl, ch, istnp, wei, ts, bdt_low, bdt_high, bpl, bph, train_state, state, vcut); 
    else{ std::cout << "Running Legacy" << std::endl; getEfficiencyBDT(pl, ph, yl, yh, cl, ch, istnp, wei, ts, bdt_low, bdt_high, train_state, state, vcut); }
    histfile = new TFile(Form("%s",fname.c_str()),"read");
  }
  //}

  std::cout << fname.c_str() << std::endl;
  TList* list1 = (TList*) histfile->GetListOfKeys();
  std::cout<< list1->At(0)->GetName() << std::endl;
  TH2D* rechist = (TH2D*) histfile->Get(list1->At(0)->GetName());

  double NumReco, ErrReco;
  if (ts >= 1634636609 && !eff_old){
  	int ibdt_low = (bdt_low+1.0000)*10000 + 1;
	int ibdt_high = (bdt_high+1.0000)*10000 ;
	int ipl = (int) pl + 1;
	int iph = (int) ph;
  	NumReco = rechist->Integral(ibdt_low, ibdt_high, pl+1, ph);
  	ErrReco = TMath::Sqrt(NumReco);
  }
  else{
 	NumReco= rechist->GetBinContent(1);
  	ErrReco = rechist->GetBinError(1);
  }
  histfile->Close();
  return std::make_pair(NumReco, ErrReco);
};

std::pair<double, double> getEffhist(float pl, float ph, float yl, float yh, int cl, int ch, bool istnp, bool wei, int sw, int num_trig, int state =3){
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

  string fname =Form("%s/BDT/EffCalc/mc_eff_%dS_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d_TrigSel%s", workdir.Data(), state, pl, ph, yl, yh, 3.5, ml, mh, cl, ch, istnp, wei, ftrigSel.c_str());

  TFile* histfile = new TFile(Form("%s.root",fname.c_str()),"read");
  TList* list1 = (TList*) histfile->GetListOfKeys();
  TH1D* genhist = (TH1D*) histfile->Get(list1->At(0)->GetName());

  double NumGen = (double) genhist->GetBinContent(1);
  double ErrGen = (double) genhist->GetBinError(1);
  histfile->Close();

  return std::make_pair(NumGen,ErrGen);
};

std::pair<double, double> openEffhist(float _pl, float _ph, float _yl, float _yh, int _cl, int _ch, bool _istnp, bool wei, bool _sw, int kTrigSel, long _ts, double _bdt_tsl, double _bdt_tsh, int _bdtptMin, int _bdtptMax, int train_state =3, int state =3 , double _vcut = 0.00, bool eff_old = false, bool get_num = false){
  std::pair<double, double> gen = getEffhist( _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, _sw, kTrigSel, state);
  std::pair<double, double> reco = getEffhist( _pl,  _ph, _yl, _yh, _cl, _ch, _istnp, wei, _ts, _bdt_tsl, _bdt_tsh, _bdtptMin, _bdtptMax, train_state, state, _vcut, eff_old);
  double BDTratio = reco.first/gen.first;
  double BDTratioErr = BDTratio*TMath::Sqrt(TMath::Power(reco.second/reco.first,2)+TMath::Power(gen.second/gen.first,2));
  std::cout << Form( "[DIAGNOSIS] NOM NUMGEN, NUMREO= (%.1f, %.1f)", gen.first, reco.first) << std::endl;
  std::cout << Form("Efficiency of BDT %ld, ", _ts) << Form("Cut %f-%f : ", _bdt_tsl, _bdt_tsh) << BDTratio << ", " << BDTratioErr<< std::endl;
  if (get_num) return std::make_pair(gen.first, reco.first);
  else  return std::make_pair(BDTratio, BDTratioErr);
}
