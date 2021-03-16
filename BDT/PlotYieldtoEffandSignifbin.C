#include "yield_eff_signif.h"
#include <memory>
#include <ROOT/TProcessExecutor.hxx>
#include <ROOT/TSeq.hxx>
#include <map>
#include "TSystem.h"

void PlotYieldtoEffandSignifbin(long ts = 1614848550, double ylim = 2.4, double ptlow = 0, double pthigh = 4, int cbinlow = 0, int cbinhigh = 180){
  if(ts == 1614848550){ylim = 2.4;}
  if(ts == 1614932252){ylim = 1.2;}

  TCanvas* c1 = new TCanvas("c1","c1", 600, 600);
  TPad* pad1 = new TPad("pad1","",0,0., 1,0.5);
  TPad* pad2 = new TPad("pad2","",0, 0.5, 1,1);
  c1->cd();
  pad1->Draw();
  pad2->Draw();
  TGraphAsymmErrors* g1 = new TGraphAsymmErrors();
  TGraphAsymmErrors* g2_1 = new TGraphAsymmErrors();
  TGraphAsymmErrors* g2 = new TGraphAsymmErrors();
//  TCanvas* c2 = new TCanvas("c1","c1", 600, 600);
//  RooRealVar x = bp->yield_eff();
  std::vector<std::pair<double, double> > bdtbin = {{-1, -0.2}, {-0.2, -0.1},{-0.1, 0.05},{0.05, 0.2}, {0.2, 0.4}, {0.4, 1.0}/*{-1, -0.1}, {-0.4,0.1}, {-0.1, 0.0}, {0.0, 0.1}, {0.1, 0.2}, {0.2, 0.3}, {0.3, 0.4},{-0.1, 0.1}, {0.1, 0.3}, {0.3, 1.0}, {0.1, 1.0}, {0.2, 1.0} lastconfig{-1., -0.3},{-1, 0.},{-0.3, -0.1},{-0.1, 0.0},{0.0, 0.1},{0.1, 1.0}*/};
  int nCores = bdtbin.size();
  ROOT::EnableImplicitMT(8);
  ROOT::TProcessExecutor mpe(nCores);
  auto getpoint = [&](int idx)
  {
    double b_low  = bdtbin[idx].first;
    double b_high = bdtbin[idx].second;
    std::cout << "[INFO] CORE " << idx << ", running BDT bin [" << b_low << ", " << b_high << "]" << std::endl;
    binplotter bp(ts, ylim, ptlow, pthigh, cbinlow, cbinhigh, b_low, b_high);

    RooRealVar adjY = bp.yield_eff();
    double s = bp.getsignificance(); 

    std::pair<RooRealVar, double> result = std::pair<RooRealVar, double>{adjY, s};
    return result;
  };

  const auto& res = mpe.Map(getpoint, ROOT::TSeqI(nCores));
  int count =0;
  for (const auto& r : res){
    double b_low  = bdtbin[count].first;
    double b_high = bdtbin[count].second;
    g1->SetPoint(count, (b_low+ b_high)/2, r.second);
    double binwidth = ( b_high - b_low)/2;
    g1->SetPointEXlow(count, binwidth);
    g1->SetPointEXhigh(count, binwidth);

    g2->SetPoint(count, (b_low+b_high)/2, r.first.getVal());
    g2->SetPointError(count, binwidth, binwidth, r.first.getError(), r.first.getError());
    std::cout << "idx: " << count << ", low: " << b_low << ", high: " << b_high << std::endl;
    count++;
  }

  pad1->cd();
  g1->SetMarkerStyle(11);
  g1->SetMarkerSize(1);
  g1->GetXaxis()->SetLimits(-1, 1);
  g1->GetXaxis()->SetRangeUser(-1, 1);

  g1->GetXaxis()->SetTitle("BDT");
  g1->GetYaxis()->SetTitle("S/#sqrt{S+B}");
  g1->Draw("pea");


  pad2->cd();
  TLegend* leg2= new TLegend(0.75,0.8,0.9,0.9);
  leg2->AddEntry(g2_1, "Normal Fit");
  leg2->AddEntry(g2, "BDT Fit");
  g2_1->SetPoint(0, 0, 1688.59);
  g2_1->SetPointError(0, 1, 1, 494.8, 494.8);
  g2_1->SetMarkerStyle(11);
  g2_1->SetMarkerSize(1);
  g2_1->SetMarkerColor(kGreen);
  g2->SetMarkerStyle(11);
  g2->SetMarkerSize(1);
  g2->SetMarkerColor(kRed);
  g2->GetXaxis()->SetLimits(-1, 1);
  g2->GetXaxis()->SetRangeUser(-1, 1);

  g2->GetYaxis()->SetTitle("Yield/Eff");

  g2->Draw("pea");
  leg2->Draw();
  g2_1->Draw("pe same");
  pad2->SetLogy();

  c1->Update();
  c1->SaveAs(Form("/home/vince402/Upsilon3S/BDT/YieldSigPlot/YtoE_SignifTest_pt_%.1f_%.1f_cBin_%d-%d.pdf", ptlow, pthigh, cbinlow, cbinhigh));
  c1->Close();

}
