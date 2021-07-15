#include <iostream>
#include "bininfo.h"
#include "TROOT.h"

void DrawROC()
{
  std::map<long, std::string> ts_map = {{1625139244, "Nominal"}, {1625558168, "Without Mass dep. variable"}, {1624960022, "J/Psi acc"}, {1625107036, "Hyper Parameter(>Depth, <tree)"}, {1625106323, "Multi Bkg"}, {1625116683, "Single muon Pt imbalance"}, {1625679687, "Without QQVtxProb"} };

  auto getROC = [&](long ts)
  {
    auto Infile = TFile::Open(Form("%s/BDT/BDTResult/BDTresultY3S_%ld_BLIND.root", workdir.Data(), ts) );

    TGraph* tg;
    tg = (TGraph*) Infile->Get("dataset/Graph");
    if(tg ==nullptr){
      tg = (TGraph*) Infile->Get("dataset1/ROCCurve");
      if(tg == nullptr){
        tg = (TGraph*) Infile->Get("dataset1_L/ROCCurve");
      }

    }
    TGraph* obj_return = (TGraph*) tg->Clone();
    return obj_return;
  };
  std::vector<Color_t> c_map = {  kOrange,  kBlack, kGreen, kMagenta, kBlue,kRed, kCyan, kPink, kAzure, kViolet};
 
  setTDRStyle();
  TCanvas *c1 = new TCanvas("c1");
  c1->cd();

  TLegend* l1 = new TLegend(0.2,0.2,0.6,0.55);
  gStyle->SetOptTitle(0);
  std::map<long, std::string>::iterator it;
  int count =0;
  for( it = ts_map.begin(); it !=ts_map.end(); it++)
  {
//    if(count==2) break;
    TGraph* g1 = getROC(it->first);
    g1->SetTitle(Form("%s", it->second.c_str()));
    g1->SetLineColor(c_map[count]);
    l1->AddEntry(g1);
    if( it == ts_map.begin()){
      g1->Draw();
    }
    else g1->Draw("same");

    count++;
    
  }
  l1->Draw();
  CMS_lumi_square(c1, 2, 33 );

  c1->Update();
  c1->SaveAs("../Macros/PAG/ROC_plot.pdf");

}
