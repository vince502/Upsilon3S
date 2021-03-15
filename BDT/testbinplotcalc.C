#include "yield_eff_signif.h"

void testbinplotcalc(){
  TCanvas* c1 = new TCanvas("c1","c1", 600, 600);
  TPad* pad1 = new TPad("pad1","",0,0., 1,0.5);
  TPad* pad2 = new TPad("pad2","",0, 0.5, 1,1);
  c1->cd();
  pad1->Draw();
  pad2->Draw();
  TGraphAsymmErrors* g1 = new TGraphAsymmErrors();
  TGraphAsymmErrors* g2 = new TGraphAsymmErrors();
//  TCanvas* c2 = new TCanvas("c1","c1", 600, 600);
//  RooRealVar x = bp->yield_eff();
  std::vector<std::pair<double, double> > bdtbin = {{-1., -0.3},{-0.3, -0.1},{-0.1, 0.0},{0.0, 0.1},{0.1, 1.0}};
  int count =0;
  double s;
  for( auto bin : bdtbin){
    binplotter bp(1614848550, 2.4, 0, 30, 0, 180, bin.first, bin.second);
    s = bp.getsignificance(); 
    RooRealVar adjY = bp.yield_eff();
    g1->SetPoint(count, (bin.first+bin.second)/2, s);
    double binwidth = (bin.second - bin.first)/2;
    g1->SetPointEXlow(count, binwidth);
    g1->SetPointEXhigh(count, binwidth);

    g2->SetPoint(count, (bin.first+bin.second)/2, adjY.getVal());
    g2->SetPointError(count, binwidth, binwidth, adjY.getError(), adjY.getError());
    std::cout << "idx: " << count << ", low: " << bin.first << ", high: " << bin.second << std::endl;
    count++;
  }
  pad1->cd();
  g1->SetMarkerStyle(11);
  g1->SetMarkerSize(1);
  g1->Draw("pea");
  pad2->cd();
  g2->SetMarkerStyle(11);
  g2->SetMarkerSize(1);
  g2->SetMarkerColor(kRed);
  g2->GetXaxis()->SetRangeUser(-1, 1);
  g2->Draw("pea");
  c1->Update();
  c1->SaveAs("SignifTest.pdf");
  c1->Close();

}
