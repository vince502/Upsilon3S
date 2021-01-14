#include <iostream>

#include <TLorentzVector.h>
#include "../commonUtility.h"
#include "../HiEvtPlaneList.h"
#include "../cutsAndBinUpsilonV2.h"
#include "../Style_jaebeom.h"
#include "tnp_weight_lowptPbPb.h"
#include "TreeSetting.h"

using namespace std;

void getEfficiency(
  float ptLow = 0.0, float ptHigh = 50.0,
  float yLow = 0.0, float yHigh = 2.4,
  int cLow = 0, int cHigh = 180, bool isTnP = false, bool isPtWeight = false, bool isSwitch=false, int kTrigSel = kTrigUps
  ) {

  gStyle->SetOptStat(0);
  int kTrigSel_;
  if(kTrigSel == kTrigUps) kTrigSel_ = 1;
  else if(kTrigSel == kTrigL1DBOS40100) kTrigSel_ = 2; 

  float muPtCut = 3.5;
  float muEtaCut = 2.4;

  float massLow = 9.0;
  float massHigh = 11.0;

  double xmin = ptLow;
  double xmax = ptHigh;

  int CentSwitch = 87;

  string ftrigSel = (isSwitch) ? "SwitchOn" : "SwitchOff";
  if(isSwitch) ftrigSel += "_UpsAndL1OS40100";
  else if(!isSwitch) ftrigSel += Form("_%s",fTrigName[kTrigSel_].Data());

  //input files
  TString inputMC = "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/SkimmedFiles/MC/OniaTree_MC_Ups3S_PbPb2018_HydjetDrumMB_5p02TeV_merged.root";
  TChain* mytree = new TChain("hionia/myTree"); 
  mytree->Add(inputMC.Data());

  //SetBranchAddress
  SetTree settree_;
  settree_.TreeSetting(mytree,1,0);

  //pT reweighting function
  //TFile *fPtW = new TFile("../Reweight/WeightedFunc/Func_dNdpT_3S.root","read");
  //TF1* f1 = (TF1*) fPtW->Get("fitRatio");

  TString histName = Form("pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d_TrigSel%s",ptLow,ptHigh,yLow,yHigh,muPtCut,massLow,massHigh,cLow,cHigh,isTnP,isPtWeight,ftrigSel.c_str());
  TH1D* hreco = new TH1D(Form("hreco_%s",histName.Data()),"hreco",1,xmin,xmax);
  TH1D* hgen = new TH1D(Form("hgen_%s",histName.Data()),"hgen",1,xmin,xmax);

  hreco->Sumw2();
  hgen->Sumw2();

  hreco->SetTitle("Reco");
  hgen->SetTitle("Gen");
  
  TLorentzVector* JP_Gen= new TLorentzVector;
  TLorentzVector* mupl_Gen = new TLorentzVector;
  TLorentzVector* mumi_Gen = new TLorentzVector;

  TLorentzVector* JP_Reco = new TLorentzVector;
  TLorentzVector* mupl_Reco = new TLorentzVector;
  TLorentzVector* mumi_Reco = new TLorentzVector;

  double weight = 1;
  double tnp_weight = 1;
  double tnp_trig_weight_mupl = -1;
  double tnp_trig_weight_mumi = -1;
  double pt_weight = 1;
  
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
    if(Centrality > cHigh || Centrality < cLow) continue;
    weight = findNcoll(Centrality) * Gen_weight;
    
    for(int igen = 0; igen<Gen_QQ_size; igen++){
      JP_Gen = (TLorentzVector*) Gen_QQ_4mom->At(igen);
      mupl_Gen = (TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mupl_idx[igen]);
      mumi_Gen = (TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mumi_idx[igen]);

      if(!( fabs(JP_Gen->Rapidity())<yHigh && fabs(JP_Gen->Rapidity())>yLow && (mupl_Gen->Pt()>muPtCut && fabs(mupl_Gen->Eta())<muEtaCut) && (mumi_Gen->Pt()>muPtCut && fabs(mumi_Gen->Eta())<muEtaCut) )) continue;
      if(JP_Gen->Pt()>ptHigh || JP_Gen->Pt()<ptLow) continue;

      if(Gen_mu_charge[Gen_QQ_mupl_idx[igen]]*Gen_mu_charge[Gen_QQ_mumi_idx[igen]]>0) continue;

      pt_weight = 1;
      //if(isPtWeight) pt_weight = f1->Eval(JP_Gen->Pt()); 

      hgen->Fill(JP_Gen->Pt(),weight*pt_weight);
    }

    bool HLTPass = false;
    if(isSwitch){ 
      if(Centrality>=CentSwitch){kTrigSel = kTrigL1DBOS40100;}
      else if(Centrality<CentSwitch){kTrigSel = kTrigUps;}
    }
    if((HLTriggers&((ULong64_t)pow(2, kTrigSel))) == ((ULong64_t)pow(2, kTrigSel)) ) HLTPass=true;

    for (Int_t irqq=0; irqq<Reco_QQ_size; irqq++) 
    {
      JP_Reco = (TLorentzVector*) Reco_QQ_4mom->At(irqq);
      mupl_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mupl_idx[irqq]);
      mumi_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mumi_idx[irqq]);
      
      bool HLTFilterPass=false;
      if( (Reco_QQ_trig[irqq]&((ULong64_t)pow(2, kTrigSel))) == ((ULong64_t)pow(2, kTrigSel)) ) HLTFilterPass=true;

      if(Reco_mu_whichGen[Reco_QQ_mupl_idx[irqq]] == -1) continue;
      if(Reco_mu_whichGen[Reco_QQ_mumi_idx[irqq]] == -1) continue;

      if(!settree_.SoftMuIdCut(irqq)) continue;

      
      if ( Reco_QQ_VtxProb[irqq]  < 0.01 ) continue;
      if(Reco_QQ_sign[irqq]!=0) continue;  
      
      if(!( fabs(JP_Reco->Rapidity())<yHigh && fabs(JP_Reco->Rapidity())>yLow && (mupl_Reco->Pt()>muPtCut && fabs(mupl_Reco->Eta())<muEtaCut) && (mumi_Reco->Pt()>muPtCut && fabs(mumi_Reco->Eta())<muEtaCut) && JP_Reco->Pt()<ptHigh && JP_Reco->Pt()>ptLow  && JP_Reco->M()>massLow && JP_Reco->M()<massHigh)) continue;
     
      if(HLTPass==true && HLTFilterPass==true) count++;
      if(isTnP){
        tnp_weight = 1;
        tnp_trig_weight_mupl = -1;
        tnp_trig_weight_mumi = -1;
        tnp_weight = tnp_weight * tnp_weight_muid_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 0) * tnp_weight_muid_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 0); //mu id
        tnp_weight = tnp_weight * tnp_weight_trk_pbpb(mupl_Reco->Eta(), 0) * tnp_weight_trk_pbpb(mumi_Reco->Eta(), 0); //inner tracker

        //Trigger part
        if(!((Reco_mu_trig[Reco_QQ_mupl_idx[irqq]]&((ULong64_t)pow(2, kL2filter))) == ((ULong64_t)pow(2, kL2filter)) && (Reco_mu_trig[Reco_QQ_mumi_idx[irqq]]&((ULong64_t)pow(2, kL2filter))) == ((ULong64_t)pow(2, kL2filter)) ) ){
          //         cout << "irqq : " << irqq << " - iev : " << iev << endl;
          //         cout << "TnP ERROR !!!! ::: No matched L2 filter1 " << endl;
          continue;
        }
        bool mupl_L2Filter = ( (Reco_mu_trig[Reco_QQ_mupl_idx[irqq]]&((ULong64_t)pow(2, kL2filter))) == ((ULong64_t)pow(2, kL2filter)) ) ? true : false ;
        bool mupl_L3Filter = ( (Reco_mu_trig[Reco_QQ_mupl_idx[irqq]]&((ULong64_t)pow(2, kL3filter))) == ((ULong64_t)pow(2, kL3filter)) ) ? true : false ;
        bool mumi_L2Filter = ( (Reco_mu_trig[Reco_QQ_mumi_idx[irqq]]&((ULong64_t)pow(2, kL2filter))) == ((ULong64_t)pow(2, kL2filter)) ) ? true : false ;
        bool mumi_L3Filter = ( (Reco_mu_trig[Reco_QQ_mumi_idx[irqq]]&((ULong64_t)pow(2, kL3filter))) == ((ULong64_t)pow(2, kL3filter)) ) ? true : false ;
        if(mupl_L2Filter == false || mumi_L2Filter == false){ cout << "TnP ERROR !!!! ::: No matched L2 filter2 " << endl; cout << endl;} 

        bool mupl_isL2 = (mupl_L2Filter && !mupl_L3Filter) ? true : false;
        bool mupl_isL3 = (mupl_L2Filter && mupl_L3Filter) ? true : false;
        bool mumi_isL2 = (mumi_L2Filter && !mumi_L3Filter) ? true : false;
        bool mumi_isL3 = (mumi_L2Filter && mumi_L3Filter) ? true : false;
        bool SelDone = false;

        if( mupl_isL2 && mumi_isL3){
          tnp_trig_weight_mupl = tnp_weight_trg_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 2, 0);
          tnp_trig_weight_mumi = tnp_weight_trg_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 3, 0);
          SelDone = true;
        }
        else if( mupl_isL3 && mumi_isL2){
          tnp_trig_weight_mupl = tnp_weight_trg_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 3, 0);
          tnp_trig_weight_mumi = tnp_weight_trg_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 2, 0);
          SelDone = true;
        }
        else if( mupl_isL3 && mumi_isL3){
          int t[2] = {-1,1}; // mupl, mumi
          int l = rand() % (2); 
          //pick up what will be L2
          if(t[l]==-1){
            tnp_trig_weight_mupl = tnp_weight_trg_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 2, 0);
            tnp_trig_weight_mumi = tnp_weight_trg_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 3, 0);
          }
          else if(t[l]==1){
            tnp_trig_weight_mupl = tnp_weight_trg_pbpb(mupl_Reco->Pt(), mupl_Reco->Eta(), 3, 0);
            tnp_trig_weight_mumi = tnp_weight_trg_pbpb(mumi_Reco->Pt(), mumi_Reco->Eta(), 2, 0);
          }
          else {cout << "ERROR :: No random selection done !!!!" << endl; continue;}
          SelDone = true;
        }    

        if(SelDone == false){cout << "ERROR :: No muon filter combination selected !!!!" << endl; continue;}
        if((tnp_trig_weight_mupl == -1 || tnp_trig_weight_mumi == -1)){cout << "ERROR :: No trigger muon tnp scale factors selected !!!!" << endl; continue;}
        tnp_weight = tnp_weight * tnp_trig_weight_mupl * tnp_trig_weight_mumi;
        if(HLTPass==true && HLTFilterPass==true){
          counttnp++;
          tnp_trig_dimu = tnp_trig_weight_mupl * tnp_trig_weight_mumi;
          //hpt_tnp_trig->Fill(JP_Reco->Pt(),tnp_trig_dimu);
        }
      }

      pt_weight = 1;
      //if(isPtWeight) pt_weight = f1->Eval(JP_Reco->Pt());

      if(HLTPass==true && HLTFilterPass==true) hreco->Fill(JP_Reco->Pt(),weight * tnp_weight * pt_weight);
    
     //  hpt_reco_NoTrig->Fill(JP_Reco->Pt(),weight * tnp_weight * pt_weight);
    }
  }

  cout << "count " << count << endl;
  cout << "counttnp " << counttnp << endl;
  


  //Draw
  //RECO
  TCanvas * creco = new TCanvas(Form("creco_%s",histName.Data()),"creco",0,0,400,400);
  creco->cd();
  hreco->Draw();
  
  //GEN
  TCanvas * cgen = new TCanvas(Form("cgen_%s",histName.Data()),"creco",0,0,400,400);
  cgen->cd();
  hgen->Draw();

  //Divide
  TH1D* heff;
  heff = (TH1D*)hreco->Clone(Form("heff_%s",histName.Data()));
  heff->Divide(heff, hgen, 1, 1, "B");
  heff->SetTitle("Efficiency");
  TCanvas * ceff = new TCanvas(Form("ceff_%s",histName.Data()),"ceff",0,400,400,400);
  ceff->cd();
  heff->Draw();

  //Save efficiency files for later use.
  heff->SetName(Form("mc_eff_vs_pt_TnP%d_Cent090",isTnP));
  TString outFileName = Form("mc_eff_%s.root",histName.Data());
  TFile* outFile = new TFile(outFileName,"RECREATE");
  heff->Write();
  hreco->Write();
  hgen->Write();
  outFile->Close();
}
