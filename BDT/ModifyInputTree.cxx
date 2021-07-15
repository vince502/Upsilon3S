#include <iostream>
#include "TFile.h"
#include "TROOT.h"
#include "../.workdir.h"

void ModifyInputTree()
{
  TFile* input = new TFile(Form("%s/OutputSkim_isMC1_1S_v210628_bkup.root", store.Data()) ,"update");
  TTree* tree = (TTree*) input->Get("tree");
  double pt1, pt2, eta1, eta2, phi1, phi2, mass;
  mass = 0.1057; // #mu (GeV/c^2)
  tree->SetBranchAddress("pt1", &pt1);
  tree->SetBranchAddress("pt2", &pt2);
  tree->SetBranchAddress("eta1", &eta1);
  tree->SetBranchAddress("eta2", &eta2);
  tree->SetBranchAddress("phi1", &phi1);
  tree->SetBranchAddress("phi2", &phi2);
  ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<Double32_t> >P1mu, P2mu, Pplus, Pminus;

  Double_t PtImb;
  TBranch* PtImb_b = tree->Branch("PtImb", &PtImb, "PtImb/D");

  Long64_t nentries = tree->GetEntries(); 
  for( Long64_t idx = 0 ; idx < nentries; idx++)
  {
    tree->GetEntry(idx);
    if( (idx%100000)==0 ) 
    {
      std::cout << Form("pts : %.4f, %.4f, etas : %.4f, %.4f, phis : %.4f, %.4f",pt1, pt2, eta1, eta2, phi1, phi2 )  << std::endl;
    }

    P1mu = ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<Double32_t> >(pt1,eta1, phi1, mass);
    P2mu = ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<Double32_t> >(pt2,eta2, phi2, mass);
    Pplus = P1mu + P2mu;
    Pminus = P1mu - P2mu;
    auto AbsPpl = TMath::Sqrt( TMath::Power(Pplus.Px(),2) + TMath::Power(Pplus.Py(),2) + TMath::Power(Pplus.Pz(),2) ); 
    auto AbsPmi = TMath::Sqrt( TMath::Power(Pminus.Px(),2) + TMath::Power(Pminus.Py(),2) + TMath::Power(Pminus.Pz(),2) ); 
    PtImb = AbsPmi/AbsPpl;
    if( (idx%100000)==0 ) 
    {
      std::cout << "AbsPpl: " << AbsPpl << ", AbsPmi: " << AbsPmi << std::endl;
    }
    PtImb_b->Fill();
  }
  tree->Write();
  input->Close();

}
