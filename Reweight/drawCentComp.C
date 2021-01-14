#include <iostream>
#include "../cutsAndBinUpsilonV2.h" 
#include "../commonUtility.h"
#include "../Style_jaebeom_v2.h"
#include "TROOT.h"

using namespace std;

void drawCentComp()
{
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  setTDRStyle();
  writeExtraText= true;
  extraText = "Internal";
  int iPeriod = 2;
  int iPos = 33; 

  TFile *fMC = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/SkimmedFiles/MC/Y1S/OniaSkim_TrigS13_MC.root","read");
  TFile *fDATA = new TFile("/home/samba.old/CMS_Files/UpsilonAnalysis/Ups3S_PbPb2018/SkimmedFiles/Data/OniaSkim_TrigS13_PDty1_Switch0.root","read");

  TTree* trm = (TTree*) fMC->Get("mmepevt");
  TTree* trd = (TTree*) fDATA->Get("mmepevt");

  int nDimu_m, nDimu_d;
  int cBin_m, cBin_d;
  const long int MAXDimuonBranchSize = 1000;
  float mass_m[MAXDimuonBranchSize], mass_d[MAXDimuonBranchSize];
  float y_m[MAXDimuonBranchSize], y_d[MAXDimuonBranchSize];
  float pt_m[MAXDimuonBranchSize], pt_d[MAXDimuonBranchSize];
  float pt1_m[MAXDimuonBranchSize], pt2_m[MAXDimuonBranchSize], pt1_d[MAXDimuonBranchSize], pt2_d[MAXDimuonBranchSize];
  float eta1_m[MAXDimuonBranchSize], eta2_m[MAXDimuonBranchSize], eta1_d[MAXDimuonBranchSize], eta2_d[MAXDimuonBranchSize];
  int recoQQsign_m[MAXDimuonBranchSize], recoQQsign_d[MAXDimuonBranchSize];
  double weight_m, weight_d;

  trm->SetBranchAddress("nDimu",&nDimu_m);
  trm->SetBranchAddress("cBin",&cBin_m);
  trm->SetBranchAddress("weight",&weight_m);
  trm->SetBranchAddress("mass",mass_m);
  trm->SetBranchAddress("pt",pt_m);
  trm->SetBranchAddress("y",y_m);
  trm->SetBranchAddress("pt1",pt1_m);
  trm->SetBranchAddress("pt2",pt2_m);
  trm->SetBranchAddress("eta1",eta1_m);
  trm->SetBranchAddress("eta2",eta2_m);
  trm->SetBranchAddress("recoQQsign",recoQQsign_m);

  trd->SetBranchAddress("nDimu",&nDimu_d);
  trd->SetBranchAddress("cBin",&cBin_d);
  trd->SetBranchAddress("weight",&weight_d);
  trd->SetBranchAddress("mass",mass_d);
  trd->SetBranchAddress("pt",pt_d);
  trd->SetBranchAddress("y",y_d);
  trd->SetBranchAddress("pt1",pt1_d);
  trd->SetBranchAddress("pt2",pt2_d);
  trd->SetBranchAddress("eta1",eta1_d);
  trd->SetBranchAddress("eta2",eta2_d);
  trd->SetBranchAddress("recoQQsign",recoQQsign_d);

  double lowMassMC_l = 9.2;
  double lowMassMC_h = 9.8;

  double lowMassCut_ = 8;
  double highMassCut_ = 14;
  double lowMassReg_l = 8;
  double lowMassReg_h = 9;
  double sigMassReg_l = 9.2;
  double sigMassReg_h = 9.8;
  double highMassReg_l = 11;
  double highMassReg_h = 13;
  double SiMuPtCut = 3.5;
  double SiMuEtaCut = 2.4;
  double DBMuPtCut = 50;
  double DBMuYCut = 2.4;


  const int Nbins = 200;
  int cLow = 0; int cHigh =200;

  TH1D* hcent_data_sig = new TH1D("hcent_data_sig",";Centrality;",Nbins,cLow,cHigh);
  TH1D* hcent_data_low = new TH1D("hcent_data_low",";Centrality;",Nbins,cLow,cHigh);
  TH1D* hcent_data_high = new TH1D("hcent_data_high",";Centrality;",Nbins,cLow,cHigh);
  TH1D* hcent_mc = new TH1D("hcent_mc",";Centrality;",Nbins,cLow,cHigh);

  for(int i=0; i<trm->GetEntries(); i++){
    trm->GetEntry(i);
    for(int j=0; j<nDimu_m; j++){
      if(mass_m[j] < lowMassCut_ || mass_m[j] > highMassCut_) continue;
      if(pt_m[j] > DBMuPtCut || abs(y_m[j]) > DBMuYCut) continue;
      if(pt1_m[j] < SiMuPtCut || pt2_m[j] < SiMuPtCut || abs(eta1_m[j]) > SiMuEtaCut || abs(eta2_m[j]) > SiMuEtaCut) continue;
      if(recoQQsign_m[j] !=0 ) continue;
      
      if(mass_m[j]> lowMassMC_l && mass_m[j] < lowMassMC_h) hcent_mc->Fill(cBin_m,weight_m);
    }
  }

  for(int i=0; i<trd->GetEntries(); i++){
    trd->GetEntry(i);
    for(int j=0; j<nDimu_d; j++){
      if(mass_d[j] < lowMassCut_ || mass_d[j] > highMassCut_) continue;
      if(pt_d[j] > DBMuPtCut || abs(y_d[j]) > DBMuYCut) continue;
      if(pt1_d[j] < SiMuPtCut || pt2_d[j] < SiMuPtCut || abs(eta1_d[j]) > SiMuEtaCut || abs(eta2_d[j]) > SiMuEtaCut) continue;
      if(recoQQsign_d[j] !=0 ) continue;
      
      if(mass_d[j]> lowMassReg_l && mass_d[j] < lowMassReg_h) hcent_data_low->Fill(cBin_d,weight_d);
      if(mass_d[j]> sigMassReg_l && mass_d[j] < sigMassReg_h) hcent_data_sig->Fill(cBin_d,weight_d);
      if(mass_d[j]> highMassReg_l && mass_d[j] < highMassReg_h) hcent_data_high->Fill(cBin_d,weight_d);
    }
  }

  hcent_data_sig->Scale(1./hcent_data_sig->Integral());
  hcent_data_low->Scale(1./hcent_data_low->Integral());
  hcent_data_high->Scale(1./hcent_data_high->Integral());
  hcent_mc->Scale(1./hcent_mc->Integral());
  SetHistStyle(hcent_data_sig,2,0);
  SetHistStyle(hcent_data_low,4,1);
  SetHistStyle(hcent_data_high,5,2);
  SetHistStyle(hcent_mc,1,3);
  hcent_data_sig->GetXaxis()->SetTitle("Centrality x2 (%)");
  hcent_data_sig->GetXaxis()->CenterTitle();

  TH1D* hrat = (TH1D*) hcent_data_sig->Clone("hratio");
  hrat->Divide(hcent_mc);
  
  double ymax = 1.5; double ymin = 0.5;
  bool setLogopt = false;

  TCanvas* cr = makeHistRatioCanvas(hrat, hcent_data_sig, hcent_mc, ymax, ymin, setLogopt);
  TPad *pad1 = (TPad*) cr->GetPad(0);
  pad1->Draw();
  pad1->cd();

  double posx1 = 0.7; double posy1=0.6; double posx2 = 0.9; double posy2 = 0.8;
  TLegend* leg = new TLegend(posx1, posy1, posx2, posy2);
  SetLegendStyle(leg);
  leg->SetHeader("#bf{#varUpsilon(1S)}");
  leg->AddEntry(hcent_data_sig,"Data","pe");
  leg->AddEntry(hcent_mc,"MC","pe");
  leg->Draw("same"); 

  double kposx = 0.46;
  double kposy = 0.88;
  double kposdiff = 0.05;
  double kColor = 1;
  double kSize = 0.031;
  drawGlobText("9.2 < m_{#mu^{+}#mu^{-}} < 9.8 GeV/c^{2}",kposx,kposy,kColor,kSize);
  drawGlobText("p_{T}^{#mu^{+}#mu^{-}} < 50 GeV/c",kposx,kposy-kposdiff,kColor,kSize);
  drawGlobText("|y^{#mu^{+}#mu^{-}}| < 2.4",kposx,kposy-kposdiff*2,kColor,kSize);
  drawGlobText("p_{T}^{#mu} < 3.5 GeV/c",kposx,kposy-kposdiff*3,kColor,kSize);

  cr->cd();
  CMS_lumi_square( pad1, iPeriod, iPos);
//  hcent_data_low->Draw("same");
//  hcent_data_high->Draw("same");
  cr->SaveAs("centCompDATAMC.pdf");
  


  

} 
