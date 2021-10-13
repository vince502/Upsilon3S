#include <iostream>
#include "TClonesArray.h"
#include "TH1.h"
#include "TFile.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TMath.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "../.workdir.h"

using namespace std;

void getAcceptance(double ptLow = 0, double ptHigh=50, double yLow=0, double yHigh=2.4, double SiMuPtCut=3.5, bool isPtWeight= true,  int state =3, int IsSys = 0)
{
  gStyle->SetOptFit(kTRUE);

  TFile* f, *fPtW;
    if(state ==1){	f =new TFile("/home/samba.old/CMS_Files/5TeVUpsilonGENONLY/OniaTree_Ups1SMM_5p02TeV_TuneCUETP8M1_nofilter_pp502Fall15-MCRUN2_71_V1-v1_GENONLY.root","read");
	fPtW = new TFile(Form("%s/WeightedFunction/Func_dNdpT_1S.root",store.Data()),"read");
    }
    if(state ==2){	f =new TFile("/home/samba.old/CMS_Files/5TeVUpsilonGENONLY/OniaTree_Ups2SMM_5p02TeV_TuneCUETP8M1_nofilter_pp502Fall15-MCRUN2_71_V1-v1_GENONLY.root","read");
	fPtW = new TFile(Form("%s/WeightedFunction/Func_dNdpT_2S.root",store.Data()),"read");
    }
    if(state ==3){
    	f =new TFile("/home/samba.old/CMS_Files/5TeVUpsilonGENONLY/OniaTree_Ups3SMM_5p02TeV_TuneCUETP8M1_nofilter_pp502Fall15-MCRUN2_71_V1-v1_GENONLY.root","read");
	fPtW = new TFile(Form("%s/WeightedFunction/Func_dNdpT_3S.root",store.Data()),"read"); // Yes, it is 2S
    }
  

  std::cout << Form("%s \n %s", f->GetName(), fPtW->GetName()) <<std::endl;
  TTree* mytree = (TTree*) f->Get("hionia/myTree");
  TF1* f1 = (TF1*) fPtW->Get("fitRatio");
  TF1 *f1_up, *f1_down, *f1_NU, *f1_ND, *f1_UN, *f1_DN;
  if(IsSys !=0){
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


  TClonesArray* Gen_QQ_4mom;
  TClonesArray* Gen_QQ_mupl_4mom;
  TClonesArray* Gen_QQ_mumi_4mom;
  Int_t Gen_QQ_size;
  
  Gen_QQ_4mom=0;
  Gen_QQ_mupl_4mom=0;
  Gen_QQ_mumi_4mom=0;

  mytree->SetBranchAddress("Gen_QQ_4mom",&Gen_QQ_4mom);
  mytree->SetBranchAddress("Gen_QQ_mupl_4mom",&Gen_QQ_mupl_4mom);
  mytree->SetBranchAddress("Gen_QQ_mumi_4mom",&Gen_QQ_mumi_4mom);
  mytree->SetBranchAddress("Gen_QQ_size",&Gen_QQ_size);

  TString histName = Form("pt%.1f_%.1f_y%.1f_%.1f_SimuPt%.1f_ptW%d",ptLow,ptHigh,yLow,yHigh,SiMuPtCut, (int) isPtWeight);
  if( IsSys != 0) histName = histName +"_SYSPT"; 

  TFile *wf = new TFile(Form("AccRes_%dS_%s.root",state,histName.Data()),"recreate");

  TH1D* hGen = new TH1D("hGen",";pT;",1,ptLow,ptHigh);
  TH1D* hGen_NU = new TH1D("hGen_NU",";pT;",1,ptLow,ptHigh);
  TH1D* hGen_ND = new TH1D("hGen_ND",";pT;",1,ptLow,ptHigh);
  TH1D* hGen_UN = new TH1D("hGen_UN",";pT;",1,ptLow,ptHigh);
  TH1D* hGen_DN = new TH1D("hGen_DN",";pT;",1,ptLow,ptHigh);
  TH1D* hGenAcc = new TH1D("hGenAcc",";pT;",1,ptLow,ptHigh);
  TH1D* hGenAcc_NU = new TH1D("hGenAcc_NU",";pT;",1,ptLow,ptHigh);
  TH1D* hGenAcc_ND = new TH1D("hGenAcc_ND",";pT;",1,ptLow,ptHigh);
  TH1D* hGenAcc_UN = new TH1D("hGenAcc_UN",";pT;",1,ptLow,ptHigh);
  TH1D* hGenAcc_DN = new TH1D("hGenAcc_DN",";pT;",1,ptLow,ptHigh);

  TLorentzVector* DimuV = new TLorentzVector;
  TLorentzVector* SimuMuPlV = new TLorentzVector;
  TLorentzVector* SimuMuMiV = new TLorentzVector;

  int nevt = mytree->GetEntries();
  double mass, y, pt, eta;
  double pt1, pt2, eta1, eta2;
  double SiMuEtaCut = 2.4;
  double ptWeight =1.;
  double ptWeight_up =1.;
  double ptWeight_down =1.;
  double ptWeightNU = 1.;
  double ptWeightND = 1.;
  double ptWeightUN = 1.;
  double ptWeightDN = 1.;

  for(int iev=0; iev<nevt; iev++){
    mytree->GetEntry(iev);
    if(iev%100000==0) cout << ">>>>> EVENT " << iev << " / " << mytree->GetEntries() <<  " ("<<(int)(100.*iev/mytree->GetEntries()) << "%)" << endl;

    for(int igen=0; igen<Gen_QQ_size; igen++){
      ptWeight =1.;
      ptWeight_up =1.;
      ptWeight_down =1.;
      ptWeightNU = 1.;
      ptWeightND = 1.;
      ptWeightUN = 1.;
      ptWeightDN = 1.;


      DimuV = (TLorentzVector*) Gen_QQ_4mom->At(igen);
      SimuMuPlV = (TLorentzVector*) Gen_QQ_mupl_4mom->At(igen);
      SimuMuMiV = (TLorentzVector*) Gen_QQ_mumi_4mom->At(igen);

      mass = DimuV->M();
      y = DimuV->Rapidity();
      pt = DimuV->Pt();
      pt1 = SimuMuPlV->Pt();
      pt2 = SimuMuMiV->Pt();
      eta1 = SimuMuPlV->Eta();
      eta2 = SimuMuMiV->Eta();
      if(isPtWeight){
        ptWeight = f1->Eval(pt);
	if(IsSys){
	  ptWeight_up = f1_up->Eval(pt);
	  ptWeight_down = f1_down->Eval(pt);
	  ptWeightNU = f1_NU->Eval(pt);
	  ptWeightND = f1_ND->Eval(pt);
	  ptWeightUN = f1_UN->Eval(pt);
	  ptWeightDN = f1_DN->Eval(pt);

	  ptWeight = ( fabs(ptWeight_up-ptWeight) > fabs(ptWeight_down - ptWeight) ) ? ptWeight_up : ptWeight_down; 
	}
      }

      if(abs(y)>yHigh || abs(y)<yLow) continue;
      if(pt<ptLow || pt>ptHigh) continue;
      hGen -> Fill(pt,ptWeight);
      hGen_NU -> Fill(pt,ptWeightNU);
      hGen_ND -> Fill(pt,ptWeightND);
      hGen_UN -> Fill(pt,ptWeightUN);
      hGen_DN -> Fill(pt,ptWeightDN);

      if(pt1 < SiMuPtCut || pt2 < SiMuPtCut) continue;
      if(abs(eta1)>SiMuEtaCut || abs(eta2)>SiMuEtaCut) continue;
      hGenAcc -> Fill(pt, ptWeight);
      hGenAcc_NU -> Fill(pt,ptWeightNU);
      hGenAcc_ND -> Fill(pt,ptWeightND);
      hGenAcc_UN -> Fill(pt,ptWeightUN);
      hGenAcc_DN -> Fill(pt,ptWeightDN);
    }
  }

  TH1D* hGenRat = (TH1D*) hGenAcc->Clone("hGenRatio");
  TH1D* hGenRat_NU = (TH1D*) hGenAcc_NU->Clone("hGenRatio_NU");
  TH1D* hGenRat_ND = (TH1D*) hGenAcc_ND->Clone("hGenRatio_ND");
  TH1D* hGenRat_UN = (TH1D*) hGenAcc_UN->Clone("hGenRatio_UN");
  TH1D* hGenRat_DN = (TH1D*) hGenAcc_DN->Clone("hGenRatio_DN");
  hGenRat->Divide(hGenRat,hGen,1,1,"B");
  hGenRat_NU->Divide(hGenRat_NU,hGen_NU,1,1,"B");
  hGenRat_ND->Divide(hGenRat_ND,hGen_ND,1,1,"B");
  hGenRat_UN->Divide(hGenRat_UN,hGen_UN,1,1,"B");
  hGenRat_DN->Divide(hGenRat_DN,hGen_DN,1,1,"B");
  wf->cd();
  hGen->Write();
  hGen_NU->Write();
  hGen_ND->Write();
  hGen_UN->Write();
  hGen_DN->Write();
  hGenAcc->Write();
  hGenAcc_NU->Write();
  hGenAcc_ND->Write();
  hGenAcc_UN->Write();
  hGenAcc_DN->Write();
  hGenRat->Write();
  hGenRat_NU->Write();
  hGenRat_ND->Write();
  hGenRat_UN->Write();
  hGenRat_DN->Write();

}


    




