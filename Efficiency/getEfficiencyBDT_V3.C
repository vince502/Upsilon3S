#pragma once
#include <iostream>

#include <TLorentzVector.h>
#include "../commonUtility.h"
#include "../cutsAndBinUpsilonV2.h"
#include "../Style_jaebeom.h"
#include "tnp_weight_lowptPbPb.h"
#include "BDTTreeSetting.h"
#include "../.workdir.h"
#include "../fitreslib.h"

using namespace std;

void getEfficiencyBDT_V3(
  float ptLow = 0.0, float ptHigh = 30.0,
  float yLow = -2.4, float yHigh = 2.4,
  int cLow = 0, int cHigh = 181, bool isTnP = true, bool isPtWeight = true, long  ts = 9999999999, double bdt_tsl = 0.0, double bdt_tsh =0.0, int bdtptMin =0, int bdtptMax = 1, int train_state = 3, int state= 3, double vcut = 0.00
  ) {
	std::cout << Form("%d, %d", bdtptMin, bdtptMax) << std::endl;

  gStyle->SetOptStat(0);
//  int kTrigSel_=0;
//  if(kTrigSel == kTrigUps) kTrigSel_ = 1;
//  else if(kTrigSel == kTrigL1DBOS40100) kTrigSel_ = 2; 

  float muPtCut = 3.5;
  float muEtaCut = 2.4;

  float massLow ;
  float massHigh;
  if(state ==1){
  	massLow =8.8;
  	massHigh = 10.2;
  }
  if(state ==2){
  	massLow =9.3;
  	massHigh = 10.7;
  }
  if(state ==3){
  	massLow =9.6;
  	massHigh = 11.0;
  }

  double xmin = ptLow;
  double xmax = ptHigh;

  int CentSwitch = 87;

//  string ftrigSel = (isSwitch) ? "SwitchOn" : "SwitchOff";
//  if(isSwitch) ftrigSel += "_UpsAndL1OS40100";
//  else if(!isSwitch) ftrigSel += Form("_%s",fTrigName[kTrigSel_].Data());

  //input files
  TFile* fPtW;
  TString inputMC;
  if( state ==1){
    inputMC = Form("/home/vince402/Upsilon3S/BDT/BDTAppliedData/BDTApp_%ld_MC_1S.root", ts);
    fPtW = new TFile(Form("%s/WeightedFunction/Func_dNdpT_1S.root", store.Data()),"read");
  }
  if( state ==2){
    inputMC = Form("/home/vince402/Upsilon3S/BDT/BDTAppliedData/BDTApp_%ld_MC_2S.root", ts);
    fPtW = new TFile(Form("%s/WeightedFunction/Func_dNdpT_2S.root", store.Data()),"read");
  }
  if( state ==3){
    inputMC =Form("/home/vince402/Upsilon3S/BDT/BDTAppliedData/BDTApp_%ld_MC.root", ts);
    fPtW = new TFile(Form("%s/WeightedFunction/Func_dNdpT_3S.root", store.Data()),"read");
  }
  std::cout << inputMC.Data()<<std::endl;
  TChain* mytree = new TChain("tree"); 
  mytree->Add(inputMC.Data());
  TF1* f1 = (TF1*) fPtW->Get("fitRatio");

  TF1 *f1_up, *f1_down, *f1_NU, *f1_ND, *f1_UN, *f1_DN;

  f1_up = (TF1*) f1->Clone();
  f1_down = (TF1*) f1->Clone();
  f1_NU = (TF1*) f1->Clone();
  f1_ND = (TF1*) f1->Clone();
  f1_UN = (TF1*) f1->Clone();
  f1_DN = (TF1*) f1->Clone();
  f1_up->SetParameters(f1->GetParameter(0) + f1->GetParError(0),f1->GetParameter(1) + f1->GetParError(1));
  f1_down->SetParameters(f1->GetParameter(0) - f1->GetParError(0),f1->GetParameter(1) - f1->GetParError(1));
  f1_NU->SetParameters(f1->GetParameter(0) - 0,f1->GetParameter(1) + f1->GetParError(1));
  f1_ND->SetParameters(f1->GetParameter(0) - 0,f1->GetParameter(1) - f1->GetParError(1));
  f1_UN->SetParameters(f1->GetParameter(0) + f1->GetParError(0),f1->GetParameter(1) - 0);
  f1_DN->SetParameters(f1->GetParameter(0) - f1->GetParError(0),f1->GetParameter(1) - 0);

  //SetBranchAddress
  SetTreeBDT settree_;
  settree_.TreeSetting(mytree, (ts >=1634636609), train_state, bdtptMin, bdtptMax);

  //pT reweighting function
//  TFile *fPtW = new TFile(Form("%s/Efficiency/Func_dNdpT_2S.root",workdir.Data()),"read");
//  TF1* f1 = (TF1*) fPtW->Get("fitRatio");

//  TString histName = Form("BDT_%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d", state, ts, bdt_tsl, bdt_tsh, ptLow,ptHigh,yLow,yHigh,muPtCut,massLow,massHigh,cLow,cHigh,isTnP,isPtWeight);
  TH3D* hreco = new TH3D(Form("hreco"),"hreco",20000,0,20000,50,0,50, 36, 0, 180);
  TH3D* hreco_NU = new TH3D(Form("hreco_NU"),"hrecoSYSNU",20000,0,20000,50,0,50, 36, 0, 180);
  TH3D* hreco_ND = new TH3D(Form("hreco_ND"),"hrecoSYSND",20000,0,20000,50,0,50, 36, 0, 180);
  TH3D* hreco_UN = new TH3D(Form("hreco_UN"),"hrecoSYSUN",20000,0,20000,50,0,50, 36, 0, 180);
  TH3D* hreco_DN = new TH3D(Form("hreco_DN"),"hrecoSYSDN",20000,0,20000,50,0,50, 36, 0, 180);
  TH3D* hreco_NO = new TH3D(Form("hreco_NO"),"hrecoSYSNO",20000,0,20000,50,0,50, 36, 0, 180);
  TH3D* hreco_tnp = new TH3D(Form("hreco_tnp"),"hreco_tnp",20000,0,20000,50,0,50, 36, 0, 180);
  TH3D* hreco_xtnp = new TH3D(Form("hreco_xtnp"),"hreco_xtnp",20000,0,20000,50,0,50, 36,  0, 180);

  hreco->Sumw2();
  hreco_NU->Sumw2();
  hreco_ND->Sumw2();
  hreco_UN->Sumw2();
  hreco_DN->Sumw2();
  hreco_NO->Sumw2();
  hreco_tnp->Sumw2();
  hreco_xtnp->Sumw2();

  hreco->SetTitle("Reco");
  hreco_xtnp->SetTitle("Reco no tnp");
  hreco_tnp->SetTitle("Reco with tnp");

// -------NO GEN info in BDT DS--------
//  TLorentzVector* JP_Gen= new TLorentzVector;
//  TLorentzVector* mupl_Gen = new TLorentzVector;
//  TLorentzVector* mumi_Gen = new TLorentzVector;

  TLorentzVector* JP_Reco = new TLorentzVector;
  TLorentzVector* mupl_Reco = new TLorentzVector;
  TLorentzVector* mumi_Reco = new TLorentzVector;

//  double tnp_weight = 1;
  double tnp_trig_weight_mupl = -1;
  double tnp_trig_weight_mumi = -1;
//  double pt_weight = 1;

  double pt_Weight_NN = 1;
  double pt_Weight_UP = 1;
  double pt_Weight_NU = 1;
  double pt_Weight_ND = 1;
  double pt_Weight_UN = 1;
  double pt_Weight_DN = 1;
  
  double tnp_trig_dimu=-1;

  int kL2filter = 38;
  int kL3filter = 39;

  int count =0;
  int counttnp =0;
  const int nevt =mytree->GetEntries();
  cout << "Total Events : " << nevt << endl;
  for(int iev=0; iev<nevt ; ++iev)
  {
    if(iev%100000==0) cout << ">>>>> EVENT " << iev << " / " << mytree->GetEntries() <<  " ("<<(int)(100.*iev/mytree->GetEntries()) << "%)" << endl;

    mytree->GetEntry(iev);
    if(!( fabs(y) < yHigh && fabs(y) > yLow && pt <= 50 && pt >=0 )) continue;
    if(!( pt1> muPtCut && pt2> muPtCut && fabs(eta1) < muEtaCut && fabs(eta2) < muEtaCut )) continue;
    if(!( QQVtxProb > vcut )) continue;
    if(!( cBin < 181 && cBin >= 0)) continue;
    if(!( mass < massHigh && mass > massLow)) continue;
    bool checkID = true; 
    if (checkID) {
      if(!( nTrkWMea1 >5 && nTrkWMea2 >5 && nPixWMea1 > 0 && nPixWMea2 > 0 && fabs(dxy1) < 0.3 && fabs(dxy2) < 0.3 && fabs(dz1) < 20. && fabs(dz2) < 20.) ) continue;

//    histName = Form("BDT_%dS_%ld_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID", state, ts,yLow,yHigh,muPtCut,massLow,massHigh,cLow,cHigh,vcut,isTnP,isPtWeight);
//    if(ts >= 1634636609) histName = Form("BDT_%dS_train%dS_%ld_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_fix_test", state, train_state, ts,yLow,yHigh,muPtCut,massLow,massHigh,cLow,cHigh,vcut,isTnP,isPtWeight);
    }
    double ptW =1;
    ptW = f1->Eval(pt);
    weight = weight ;//* ptW;
	pt_Weight_NU = f1_NU->Eval(pt);
	pt_Weight_ND = f1_ND->Eval(pt);
	pt_Weight_UN = f1_UN->Eval(pt);
	pt_Weight_DN = f1_DN->Eval(pt);
    int bdtidx = (BDT+1.0000)*10000; 
	int cbinfill = (cBin==180) ? 179 : cBin;
    hreco->		Fill(bdtidx, pt, cbinfill, weight);
	hreco_NO->	Fill(bdtidx, pt, cbinfill, (weight/ptW));
	hreco_NU->	Fill(bdtidx, pt, cbinfill, (weight/ptW)*pt_Weight_NU);
	hreco_ND->	Fill(bdtidx, pt, cbinfill, (weight/ptW)*pt_Weight_ND);
	hreco_UN->	Fill(bdtidx, pt, cbinfill, (weight/ptW)*pt_Weight_UN);
	hreco_DN->	Fill(bdtidx, pt, cbinfill, (weight/ptW)*pt_Weight_DN);
    hreco_tnp->	Fill(bdtidx, pt, cbinfill, weight);
    hreco_xtnp->Fill(bdtidx, pt, cbinfill, weight/tnp_weight);
    count++;

  }
  cout << "count " << count << endl;
	string histName = GetEffNum(__FITRESLATEST, ts, train_state, state, bdtptMin, bdtptMax, yLow, yHigh, muPtCut, massLow, massHigh, 0, 0, vcut, true, true);

  TFile* outFile = new TFile(histName.c_str(),"RECREATE");
//  heff->Write();
  hreco->Write();
  hreco_NO->Write();
  hreco_NU->Write();
  hreco_ND->Write();
  hreco_UN->Write();
  hreco_DN->Write();
  hreco_tnp->Write();
  hreco_xtnp->Write();
  outFile->Close();

}


//
//    bool HLTPass = false;
//    if(isSwitch){ 
//      if(Centrality>=CentSwitch){kTrigSel = kTrigL1DBOS40100;}
//      else if(Centrality<CentSwitch){kTrigSel = kTrigUps;}
//    }
//    if((HLTriggers&((ULong64_t)pow(2, kTrigSel))) == ((ULong64_t)pow(2, kTrigSel)) ) HLTPass=true;
//
//    for (Int_t irqq=0; irqq<Reco_QQ_size; irqq++) 
//    {
//      JP_Reco = (TLorentzVector*) Reco_QQ_4mom->At(irqq);
//      mupl_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mupl_idx[irqq]);
//      mumi_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mumi_idx[irqq]);
//      
//      bool HLTFilterPass=false;
//      if( (Reco_QQ_trig[irqq]&((ULong64_t)pow(2, kTrigSel))) == ((ULong64_t)pow(2, kTrigSel)) ) HLTFilterPass=true;
//
//      if(Reco_mu_whichGen[Reco_QQ_mupl_idx[irqq]] == -1) continue;
//      if(Reco_mu_whichGen[Reco_QQ_mumi_idx[irqq]] == -1) continue;
//
//      if(!settree_.SoftMuIdCut(irqq)) continue;
//
//      
//      if ( Reco_QQ_VtxProb[irqq]  < 0.01 ) continue;
//      if(Reco_QQ_sign[irqq]!=0) continue;  
//      
//      if(!( fabs(JP_Reco->Rapidity())<yHigh && fabs(JP_Reco->Rapidity())>yLow && (mupl_Reco->Pt()>muPtCut && fabs(mupl_Reco->Eta())<muEtaCut) && (mumi_Reco->Pt()>muPtCut && fabs(mumi_Reco->Eta())<muEtaCut) && JP_Reco->Pt()<ptHigh && JP_Reco->Pt()>ptLow  && JP_Reco->M()>massLow && JP_Reco->M()<massHigh)) continue;
//     
//      if(HLTPass==true && HLTFilterPass==true) count++;
//      if(isTnP){
//        tnp_weight = 1;
//        tnp_trig_weight_mupl = -1;
//        tnp_trig_weight_mumi = -1;
//        tnp_weight = tnp_weight * tnp_weight_muid_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 0) * tnp_weight_muid_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 0); //mu id
//        tnp_weight = tnp_weight * tnp_weight_trk_pbpb(mupl_Reco->Eta(), 0) * tnp_weight_trk_pbpb(mumi_Reco->Eta(), 0); //inner tracker
//
//        //Trigger part
//        if(!((Reco_mu_trig[Reco_QQ_mupl_idx[irqq]]&((ULong64_t)pow(2, kL2filter))) == ((ULong64_t)pow(2, kL2filter)) && (Reco_mu_trig[Reco_QQ_mumi_idx[irqq]]&((ULong64_t)pow(2, kL2filter))) == ((ULong64_t)pow(2, kL2filter)) ) ){
//          //         cout << "irqq : " << irqq << " - iev : " << iev << endl;
//          //         cout << "TnP ERROR !!!! ::: No matched L2 filter1 " << endl;
//          continue;
//        }
//        bool mupl_L2Filter = ( (Reco_mu_trig[Reco_QQ_mupl_idx[irqq]]&((ULong64_t)pow(2, kL2filter))) == ((ULong64_t)pow(2, kL2filter)) ) ? true : false ;
//        bool mupl_L3Filter = ( (Reco_mu_trig[Reco_QQ_mupl_idx[irqq]]&((ULong64_t)pow(2, kL3filter))) == ((ULong64_t)pow(2, kL3filter)) ) ? true : false ;
//        bool mumi_L2Filter = ( (Reco_mu_trig[Reco_QQ_mumi_idx[irqq]]&((ULong64_t)pow(2, kL2filter))) == ((ULong64_t)pow(2, kL2filter)) ) ? true : false ;
//        bool mumi_L3Filter = ( (Reco_mu_trig[Reco_QQ_mumi_idx[irqq]]&((ULong64_t)pow(2, kL3filter))) == ((ULong64_t)pow(2, kL3filter)) ) ? true : false ;
//        if(mupl_L2Filter == false || mumi_L2Filter == false){ cout << "TnP ERROR !!!! ::: No matched L2 filter2 " << endl; cout << endl;} 
//
//        bool mupl_isL2 = (mupl_L2Filter && !mupl_L3Filter) ? true : false;
//        bool mupl_isL3 = (mupl_L2Filter && mupl_L3Filter) ? true : false;
//        bool mumi_isL2 = (mumi_L2Filter && !mumi_L3Filter) ? true : false;
//        bool mumi_isL3 = (mumi_L2Filter && mumi_L3Filter) ? true : false;
//        bool SelDone = false;
//
//        if( mupl_isL2 && mumi_isL3){
//          tnp_trig_weight_mupl = tnp_weight_trg_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 2, 0);
//          tnp_trig_weight_mumi = tnp_weight_trg_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 3, 0);
//          SelDone = true;
//        }
//        else if( mupl_isL3 && mumi_isL2){
//          tnp_trig_weight_mupl = tnp_weight_trg_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 3, 0);
//          tnp_trig_weight_mumi = tnp_weight_trg_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 2, 0);
//          SelDone = true;
//        }
//        else if( mupl_isL3 && mumi_isL3){
//          int t[2] = {-1,1}; // mupl, mumi
//          int l = rand() % (2); 
//          //pick up what will be L2
//          if(t[l]==-1){
//            tnp_trig_weight_mupl = tnp_weight_trg_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 2, 0);
//            tnp_trig_weight_mumi = tnp_weight_trg_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 3, 0);
//          }
//          else if(t[l]==1){
//            tnp_trig_weight_mupl = tnp_weight_trg_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 3, 0);
//            tnp_trig_weight_mumi = tnp_weight_trg_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 2, 0);
//          }
//          else {cout << "ERROR :: No random selection done !!!!" << endl; continue;}
//          SelDone = true;
//        }    
//
//        if(SelDone == false){cout << "ERROR :: No muon filter combination selected !!!!" << endl; continue;}
//        if((tnp_trig_weight_mupl == -1 || tnp_trig_weight_mumi == -1)){cout << "ERROR :: No trigger muon tnp scale factors selected !!!!" << endl; continue;}
//        tnp_weight = tnp_weight * tnp_trig_weight_mupl * tnp_trig_weight_mumi;
//        if(HLTPass==true && HLTFilterPass==true){
//          counttnp++;
//          tnp_trig_dimu = tnp_trig_weight_mupl * tnp_trig_weight_mumi;
//          //hpt_tnp_trig->Fill(JP_Reco->Pt(),tnp_trig_dimu);
//        }
//      }
//
//      pt_weight = 1;
//      //if(isPtWeight) pt_weight = f1->Eval(JP_Reco->Pt());
//
//      if(HLTPass==true && HLTFilterPass==true) hreco->Fill(JP_Reco->Pt(),weight * tnp_weight * pt_weight);
//    
//     //  hpt_reco_NoTrig->Fill(JP_Reco->Pt(),weight * tnp_weight * pt_weight);
//    }
