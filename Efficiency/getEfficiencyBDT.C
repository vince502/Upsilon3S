#include <iostream>

#include <TLorentzVector.h>
#include "../commonUtility.h"
#include "../cutsAndBinUpsilonV2.h"
#include "../Style_jaebeom.h"
#include "tnp_weight_lowptPbPb.h"
#include "BDTTreeSetting.h"
#include "../.workdir.h"

using namespace std;

void getEfficiencyBDT(
  float ptLow = 0.0, float ptHigh = 30.0,
  float yLow = 0.0, float yHigh = 2.4,
  int cLow = 0, int cHigh = 181, bool isTnP = false, bool isPtWeight = false, long  ts = 9999999999, double bdt_tsl = 0.0, double bdt_tsh =0.0, int train_state = 3, int state= 3, double vcut = 0.00
  ) {

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
  TChain* mytree = new TChain("tree"); 
  mytree->Add(inputMC.Data());
  TF1* f1 = (TF1*) fPtW->Get("fitRatio");

  //SetBranchAddress
  SetTreeBDT settree_;
  settree_.TreeSetting(mytree, (ts >=1634636609), train_state,(int) ptLow, (int) ptHigh);

  //pT reweighting function
//  TFile *fPtW = new TFile(Form("%s/Efficiency/Func_dNdpT_2S.root",workdir.Data()),"read");
//  TF1* f1 = (TF1*) fPtW->Get("fitRatio");

  TString histName = Form("BDT_%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d", state, ts, bdt_tsl, bdt_tsh, ptLow,ptHigh,yLow,yHigh,muPtCut,massLow,massHigh,cLow,cHigh,isTnP,isPtWeight);
  TH1D* hreco = new TH1D(Form("hreco"),"hreco",1,xmin,xmax);
  TH1D* hreco_tnp = new TH1D(Form("hreco_tnp"),"hreco_tnp",(int) ((xmax-xmin)),xmin,xmax);
  TH1D* hreco_xtnp = new TH1D(Form("hreco_xtnp"),"hreco_xtnp",(int) ((xmax-xmin)),xmin,xmax);

  hreco->Sumw2();
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
    if(BDT< bdt_tsl || BDT> bdt_tsh) continue;
    if(!( fabs(y) < yHigh && fabs(y) > yLow && pt < ptHigh && pt >ptLow )) continue;
    if(!( pt1> muPtCut && pt2> muPtCut && fabs(eta1) < muEtaCut && fabs(eta2) < muEtaCut )) continue;
    if(!( QQVtxProb > vcut )) continue;
    if(!( cBin < cHigh && cBin >= cLow)) continue;
    if(!( mass < massHigh && mass > massLow)) continue;
    bool checkID = true; 
    if (checkID) {
      if(!( nTrkWMea1 >5 && nTrkWMea2 >5 && nPixWMea1 > 0 && nPixWMea2 > 0 && fabs(dxy1) < 0.3 && fabs(dxy2) < 0.3 && fabs(dz1) < 20. && fabs(dz2) < 20.) ) continue;

    histName = Form("BDT_%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID", state, ts, bdt_tsl, bdt_tsh,ptLow,ptHigh,yLow,yHigh,muPtCut,massLow,massHigh,cLow,cHigh,vcut,isTnP,isPtWeight);
    if(ts >= 1634636609) histName = Form("BDT_%dS_train%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_fix", state, train_state, ts, bdt_tsl, bdt_tsh,ptLow,ptHigh,yLow,yHigh,muPtCut,massLow,massHigh,cLow,cHigh,vcut,isTnP,isPtWeight);
    }
    double ptW =1;
    if( isPtWeight) ptW = f1->Eval(pt);
    weight = weight ;//* ptW;
    
    hreco->Fill(pt,weight);
    hreco_tnp->Fill(pt,weight);
    hreco_xtnp->Fill(pt, weight/tnp_weight);
    count++;

  }
  cout << "count " << count << endl;

  //Draw
  //RECO
  TCanvas * creco = new TCanvas(Form("creco_%s",histName.Data()),"creco",0,0,400,400);
  creco->cd();
  hreco->Draw();

  //RECO TnP
  TCanvas * creco_tnp = new TCanvas(Form("creco_tnp_%s",histName.Data()),"creco with tnp",0,0,400,400);
  creco_tnp->cd();
  hreco_tnp->Draw("pe");
  
  //RECO xTnP
//  TCanvas * creco_xtnp = new TCanvas(Form("creco_xtnp_%s",histName.Data()),"creco no tnp",0,0,400,400);
  hreco_xtnp->Draw("same,pe");

  //Divide
//  TH1D* heff;
//  heff = (TH1D*)hreco->Clone(Form("heff_%s",histName.Data()));
//  heff->Divide(heff, hgen, 1, 1, "B");
//  heff->SetTitle("Efficiency");
//  TCanvas * ceff = new TCanvas(Form("ceff_%s",histName.Data()),"ceff",0,400,400,400);
//  ceff->cd();
//  heff->Draw();

  //Save efficiency files for later use.
//  heff->SetName(Form("mc_eff_vs_pt_TnP%d_dNdPt%d_Cent%d%d",isTnP, isPtWeight, cLow, cHigh));
  TString outFileName = Form("/home/vince402/Upsilon3S/BDT/EffCalc/mc_eff_%s.root",histName.Data());
  TFile* outFile = new TFile(outFileName,"RECREATE");
//  heff->Write();
  hreco->Write();
  hreco_tnp->Write();
  hreco_xtnp->Write();
//  hgen->Write();
  creco->Close();
  creco_tnp->Close();
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
