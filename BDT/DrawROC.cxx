#include <iostream>
#include "bininfo.h"
//#include "TROOT.h"

void DrawROC()
{
  std::map<long, std::string> ts_map = {
//  	{10000000016, "Nominal"}, 
  	{100019111111, "Nominal"}, 
//  	{100019101111, "No QQdca"}, 
  	{100019111010, "No 3D Variables"}, 
  	{100019110101, "No 2D Variables"}, 
//  	{100119111111, "500 Trees"}, 
//  	{100219111111, "700 Trees"}, 
//  	{100319111111, "2100 Trees"}, 
//  	{100000000162, "No 2D variables"}, 
//  	{100009110111, "No ctau(2D)"}, 
//  	{100009111101, "No cosine alpha(2D)"}, 
//  	{8000000007, ""},
  };

  auto getROC = [&](long ts)
  {
    auto Infile = TFile::Open(Form("%s/BDT/BDTResult/BDTresultY3S_%ld_BLIND.root", workdir.Data(), ts) );

    TGraph* tg;
    tg = (TGraph*) Infile->Get("dataset/Graph");
    if(tg ==nullptr){
      tg = (TGraph*) Infile->Get("data/Y3Spt0to30/dataset1/ROCCurve");
      if(tg == nullptr){
        tg = (TGraph*) Infile->Get("dataset1_L/ROCCurve");
      }

    }
    TGraph* obj_return = (TGraph*) tg->Clone();
    return obj_return;
  };
  std::vector<Color_t> c_map = {  kOrange +8,  kBlack, kGreen, kMagenta, kBlue,kRed, kCyan, kPink, kAzure, kViolet};
 
  setTDRStyle();
  TCanvas *c1 = new TCanvas("c1","",1400, 1200);
  c1->cd();
  c1->SetTopMargin(0.10);

  TLegend* l1 = new TLegend(0.2,0.2,0.6,0.55);
  l1->SetBorderSize(0);
//  gStyle->SetOptTitle(0);
  std::map<long, std::string>::iterator it;
  int count =0;
  for( it = ts_map.begin(); it !=ts_map.end(); it++)
  {
//    if(count==2) break;
    TGraph* g1 = getROC(it->first);
    g1->SetTitle(Form("%s", it->second.c_str()));
    g1->SetLineColor(c_map[count]);
    g1->SetMarkerColor(c_map[count]);
//	g1->SetStats(0);
    l1->AddEntry(g1);
    if( it == ts_map.begin()){
      g1->Draw();
    }
    else g1->Draw("same");

    count++;
    
  }
  l1->Draw();
  CMS_lumi_square(c1, 31, 33 );

  c1->Update();
  c1->SaveAs("../Macros/ROC_plot.pdf");
  c1->SaveAs("../checkout/tmp/ROC_plot.png");

}
