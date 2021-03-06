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

using namespace std;

void getAcceptance(double ptLow = 0, double ptHigh=50, double yLow=0, double yHigh=2.4, double SiMuPtCut=3.5)
{
  gStyle->SetOptFit(kTRUE);

  TFile* f = new TFile("/home/samba.old/CMS_Files/5TeVUpsilonGENONLY/OniaTree_Ups3SMM_5p02TeV_TuneCUETP8M1_nofilter_pp502Fall15-MCRUN2_71_V1-v1_GENONLY.root","read");
  TTree* mytree = (TTree*) f->Get("hionia/myTree");

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

  TString histName = Form("pt%.1f_%.1f_y%.1f_%.1f_SimuPt%.1f",ptLow,ptHigh,yLow,yHigh,SiMuPtCut);

  TFile *wf = new TFile(Form("AccRes_%s.root",histName.Data()),"recreate");

  TH1D* hGen = new TH1D("hGen",";pT;",1,ptLow,ptHigh);
  TH1D* hGenAcc = new TH1D("hGenAcc",";pT;",1,ptLow,ptHigh);

  TLorentzVector* DimuV = new TLorentzVector;
  TLorentzVector* SimuMuPlV = new TLorentzVector;
  TLorentzVector* SimuMuMiV = new TLorentzVector;

  int nevt = mytree->GetEntries();
  double mass, y, pt, eta;
  double pt1, pt2, eta1, eta2;
  double SiMuEtaCut = 2.4;

  for(int iev=0; iev<nevt; iev++){
    mytree->GetEntry(iev);
    if(iev%100000==0) cout << ">>>>> EVENT " << iev << " / " << mytree->GetEntries() <<  " ("<<(int)(100.*iev/mytree->GetEntries()) << "%)" << endl;

    for(int igen=0; igen<Gen_QQ_size; igen++){

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

      if(abs(y)>yHigh || abs(y)<yLow) continue;
      if(pt<ptLow || pt>ptHigh) continue;
      hGen -> Fill(pt);

      if(pt1 < SiMuPtCut || pt2 < SiMuPtCut) continue;
      if(abs(eta1)>SiMuEtaCut || abs(eta2)>SiMuEtaCut) continue;
      hGenAcc -> Fill(pt);
    }
  }

  TH1D* hGenRat = (TH1D*) hGenAcc->Clone("hGenRatio");
  hGenRat->Divide(hGenRat,hGen,1,1,"B");
  wf->cd();
  hGen->Write();
  hGenAcc->Write();
  hGenRat->Write();

}


    




