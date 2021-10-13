#include <iostream>

#include <TLorentzVector.h>
#include "../commonUtility.h"
#include "../cutsAndBinUpsilonV2.h"
#include "../Style_jaebeom.h"
#include "tnp_weight_lowptPbPb.h"
#include "TreeSetting.h"
#include "../.workdir.h"

using namespace std;

void getEfficiency_SYSDPT(
  float ptLow = 0.0, float ptHigh = 30.0,
  float yLow = 0.0, float yHigh = 2.4,
  int cLow = 0, int cHigh = 181, bool isTnP = false, bool isPtWeight = false, bool isSwitch=false, int kTrigSel = kTrigUps, bool isBDT = false, int state =3, int isSys =1
  ) {

  gStyle->SetOptStat(0);
  int kTrigSel_;
  if(kTrigSel == kTrigUps) kTrigSel_ = 1;
  else if(kTrigSel == kTrigL1DBOS40100) kTrigSel_ = 2; 

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

  string ftrigSel = (isSwitch) ? "SwitchOn" : "SwitchOff";
  if(isSwitch) ftrigSel += "_UpsAndL1OS40100";
  else if(!isSwitch) ftrigSel += Form("_%s",fTrigName[kTrigSel_].Data());

  //input files
  TString inputMC =  "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/OniaTree/MC/Oniatree_Y3SMC_v210618_pdgfix.root";
  if(state ==1) inputMC = "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/OniaTree/MC/OniaTree_Ups1SMC_HydjetDrumMB_5p02TeV_v210621.root";
  if(state ==2) inputMC = "/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/OniaTree/MC/OniaTree_Ups2SMC_HydjetDrumMB_5p02TeV_v210628.root";
  TChain* mytree = new TChain("hionia/myTree"); 
  mytree->Add(inputMC.Data());

  //SetBranchAddress
  SetTree settree_;
  settree_.TreeSetting(mytree,1,0);

  //pT reweighting function
  TFile *fPtW;
  if(state==1) fPtW = new TFile(Form("%s/WeightedFunction/Func_dNdpT_1S.root",store.Data()),"read");
  if(state==2) fPtW = new TFile(Form("%s/WeightedFunction/Func_dNdpT_2S.root",store.Data()),"read");
  if(state==3) fPtW = new TFile(Form("%s/WeightedFunction/Func_dNdpT_3S.root",store.Data()),"read");
  TF1* f1 = (TF1*) fPtW->Get("fitRatio");
  TF1 *f1_up, *f1_down, *f1_NU, *f1_ND, *f1_UN, *f1_DN;

  if(isSys !=0){
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
  }

  TString histName = Form("%dS_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_isTnP%d_isPtWeight%d_TrigSel%s_SYSPT",state, ptLow,ptHigh,yLow,yHigh,muPtCut,massLow,massHigh,cLow,cHigh,isTnP,isPtWeight,ftrigSel.c_str());
//  TH1D* hreco = new TH1D(Form("hreco"),"hreco",1,xmin,xmax);
  TH1D* hgen = new TH1D(Form("hgen"),"hgen",1,xmin,xmax);
  TH1D* hgen_NU = new TH1D(Form("hgen_NU"),"hgen",1,xmin,xmax);
  TH1D* hgen_ND = new TH1D(Form("hgen_ND"),"hgen",1,xmin,xmax);
  TH1D* hgen_UN = new TH1D(Form("hgen_UN"),"hgen",1,xmin,xmax);
  TH1D* hgen_DN = new TH1D(Form("hgen_DN"),"hgen",1,xmin,xmax);
  TH1D* hgen_bin = new TH1D(Form("hgen_bin"),"hgen",(int) (xmax-xmin),xmin,xmax);

//  hreco->Sumw2();
  hgen->Sumw2();
  hgen_bin->Sumw2();

//  hreco->SetTitle("Reco");
  hgen->SetTitle("Gen");
  hgen_bin->SetTitle("Gen bin");
  
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
  double pt_Weight = 1;
  double pt_Weight_NU=1;
  double pt_Weight_ND=1;
  double pt_Weight_UN=1;
  double pt_Weight_DN=1;
  
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
    if(Centrality >= cHigh || Centrality < cLow) continue;
    weight = findNcoll(Centrality) * Gen_weight;
    
    for(int igen = 0; igen<Gen_QQ_size; igen++){
      JP_Gen = (TLorentzVector*) Gen_QQ_4mom->At(igen);
      mupl_Gen = (TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mupl_idx[igen]);
      mumi_Gen = (TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mumi_idx[igen]);

      if(!( fabs(JP_Gen->Rapidity())<yHigh && fabs(JP_Gen->Rapidity())>yLow && (mupl_Gen->Pt()>muPtCut && fabs(mupl_Gen->Eta())<muEtaCut) && (mumi_Gen->Pt()>muPtCut && fabs(mumi_Gen->Eta())<muEtaCut) )) continue;
      if(JP_Gen->Pt()>ptHigh || JP_Gen->Pt()<ptLow) continue;

      if(Gen_mu_charge[Gen_QQ_mupl_idx[igen]]*Gen_mu_charge[Gen_QQ_mumi_idx[igen]]>0) continue;

      pt_Weight = 1;
      if(isPtWeight){
	pt_Weight = f1->Eval(JP_Gen->Pt()); 
	if( isSys){
	  pt_Weight_NU = f1_NU->Eval(JP_Gen->Pt());
	  pt_Weight_ND = f1_ND->Eval(JP_Gen->Pt());
	  pt_Weight_UN = f1_UN->Eval(JP_Gen->Pt());
	  pt_Weight_DN = f1_DN->Eval(JP_Gen->Pt());

	}
      }

      hgen->Fill(JP_Gen->Pt(),weight*pt_Weight);
      hgen_NU->Fill(JP_Gen->Pt(),weight*pt_Weight_NU);
      hgen_ND->Fill(JP_Gen->Pt(),weight*pt_Weight_ND);
      hgen_UN->Fill(JP_Gen->Pt(),weight*pt_Weight_UN);
      hgen_DN->Fill(JP_Gen->Pt(),weight*pt_Weight_DN);
      hgen_bin->Fill(JP_Gen->Pt(),weight*pt_Weight);
    }

  //  bool HLTPass = false;
  //  if(isSwitch){ 
  //    if(Centrality>=CentSwitch){kTrigSel = kTrigL1DBOS40100;}
  //    else if(Centrality<CentSwitch){kTrigSel = kTrigUps;}
  //  }
  //  if((HLTriggers&((ULong64_t)pow(2, kTrigSel))) == ((ULong64_t)pow(2, kTrigSel)) ) HLTPass=true;

  //  for (Int_t irqq=0; irqq<Reco_QQ_size; irqq++) 
  //  {
  //    JP_Reco = (TLorentzVector*) Reco_QQ_4mom->At(irqq);
  //    mupl_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mupl_idx[irqq]);
  //    mumi_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mumi_idx[irqq]);
  //    
  //    bool HLTFilterPass=false;
  //    if( (Reco_QQ_trig[irqq]&((ULong64_t)pow(2, kTrigSel))) == ((ULong64_t)pow(2, kTrigSel)) ) HLTFilterPass=true;

  //    if(Reco_mu_whichGen[Reco_QQ_mupl_idx[irqq]] == -1) continue;
  //    if(Reco_mu_whichGen[Reco_QQ_mumi_idx[irqq]] == -1) continue;

 ////     if(!settree_.SoftMuIdCut(irqq)) continue;

  //    
  //    if ( Reco_QQ_VtxProb[irqq]  < 0.01 ) continue;
  //    if(Reco_QQ_sign[irqq]!=0) continue;  
  //    
  //    if(!( fabs(JP_Reco->Rapidity())<yHigh && fabs(JP_Reco->Rapidity())>yLow && (mupl_Reco->Pt()>muPtCut && fabs(mupl_Reco->Eta())<muEtaCut) && (mumi_Reco->Pt()>muPtCut && fabs(mumi_Reco->Eta())<muEtaCut) && JP_Reco->Pt()<ptHigh && JP_Reco->Pt()>ptLow  && JP_Reco->M()>massLow && JP_Reco->M()<massHigh)) continue;
  //   
  //    if(HLTPass==true && HLTFilterPass==true) count++;
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
//      if(isPtWeight) pt_weight = f1->Eval(JP_Reco->Pt());
//
//      if(HLTPass==true && HLTFilterPass==true) hreco->Fill(JP_Reco->Pt(),weight * tnp_weight * pt_weight);
//    
//     //  hpt_reco_NoTrig->Fill(JP_Reco->Pt(),weight * tnp_weight * pt_weight);
//    }
  }


  //Draw
  //RECO
//  TCanvas * creco = new TCanvas(Form("creco_%s",histName.Data()),"creco",0,0,400,400);
//  creco->cd();
//  hreco->Draw();
  
  //GEN
  TCanvas * cgen = new TCanvas(Form("cgen_%s",histName.Data()),"creco",0,0,400,400);
  cgen->cd();
  hgen->Draw();

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
  TString outFileName = Form("mc_eff_%s.root",histName.Data());
  if(isBDT){ outFileName = Form("/home/vince402/Upsilon3S/BDT/EffCalc/DNDPT/mc_eff_%s.root",histName.Data());}
  TFile* outFile = new TFile(outFileName,"RECREATE");
//  heff->Write();
//  hreco->Write();
  hgen->Write();
  hgen_NU->Write();
  hgen_ND->Write();
  hgen_UN->Write();
  hgen_DN->Write();
  hgen_bin->Write();
  cgen->Close();
  outFile->Close();
}
