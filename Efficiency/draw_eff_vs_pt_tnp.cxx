#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "../.workdir.h"

std::pair<TH1D*, TH1D*> func_draw_eff_vs_pt_tnp(
//  double plow, double phigh,
//  double ylow, double yhigh,
//  int clow, int chigh,
//  long ts,
//  double singlemupt,
){

  //TFile *f_reco = TFile::Open(Form("%s/BDT/EffCalc/mc_eff_BDT_1622626134_bdt_-1.000-1.000_pt0.0_30.0_y-2.4_2.4_SiMuPt3.5_mass9.0_11.0_cent0_180_isTnP1_isPtWeight1_ID.root", workdir.Data()) );
  TFile *f_reco = TFile::Open(Form("%s/BDT/EffCalc/mc_eff_BDT_1621574976_bdt_-1.000-1.000_pt0.0_30.0_y-2.4_2.4_SiMuPt4.0_mass9.0_11.0_cent0_180_isTnP1_isPtWeight1_ID.root", workdir.Data()) );
  TFile* f_gen = TFile::Open(Form("%s/BDT/EffCalc/mc_eff_pt0.0_30.0_y-2.4_2.4_SiMuPt4.0_mass9.0_11.0_cent0_180_isTnP1_isPtWeight1_TrigSelSwitchOff_Ups.root", workdir.Data()) );

  TH1D* h_reco_tnp = (TH1D*) f_reco->Get("hreco_tnp");
  TH1D* h_reco_xtnp = (TH1D*) f_reco->Get("hreco_xtnp");
  TH1D* h_gen= (TH1D*) f_gen->Get("hgen_bin");

  TH1D* h_eff_tnp = (TH1D*) h_reco_tnp->Clone();
  h_eff_tnp->Divide(h_gen);
  TH1D* h_eff_xtnp = (TH1D*) h_reco_xtnp->Clone();
  h_eff_xtnp->Divide(h_gen);

  return std::make_pair(h_eff_tnp, h_eff_xtnp);
};

void draw_eff_vs_pt_tnp(){
  auto res = func_draw_eff_vs_pt_tnp();

  TLegend* leg = new TLegend(0.64,0.15,0.84,0.3);
  gStyle->SetLegendFont(72);
  leg->SetBorderSize(0);
  leg->AddEntry(res.first, "#epsilon with tnp","lep");
  leg->AddEntry(res.second, "eff without tnp","lep");
  leg->SetTextFont(70);

  TLatex* tl = new TLatex();
  tl->SetNDC();
  tl->SetTextSize(0.025);



  gStyle->SetOptTitle(0);
  TCanvas* c1= new TCanvas("c1", "", 800,700);
  c1->cd();
  res.first->SetMarkerColor(kRed);
  res.first->SetMarkerSize(3);
  res.first->SetLineColor(kRed);
  res.first->GetYaxis()->SetRangeUser(0.2,1.);
  res.first->GetXaxis()->SetTitle("p_{T} ( GeV/c^{2} )");
  res.first->GetYaxis()->SetTitle("#varepsilon");
  res.first->Draw();
  res.second->SetMarkerSize(3);
  res.second->Draw("same,pe");
  leg->Draw();
  tl->DrawLatex(0.65, 0.43, "p_{T} #in [ 0.0, 30. ] GeV/c^{2}");
  tl->DrawLatex(0.65, 0.38, "y #in [ 2.4, -2.4 ]");
  tl->DrawLatex(0.65, 0.33, "Centrality #in [ 0, 90 ] %");

  c1->SaveAs(Form("%s/plots/for_AN/EffvsPt_BDT_fullPtEtaCent_wwo_tnp.pdf",workdir.Data()) );
  
}
