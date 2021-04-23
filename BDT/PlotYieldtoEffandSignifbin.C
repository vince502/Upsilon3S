#include "yield_eff_signif.cxx"
#include "bininfo.h"
#include <memory>
#include <ROOT/TProcessExecutor.hxx>
#include <ROOT/TSeq.hxx>
#include <map>
#include <fstream>
#include "TSystem.h"
#include "plotresult.C"
#include "bininfo.h"


void PlotYieldtoEffandSignifbin(long ts = 1614848550, double ylim = 2.4, double ptlow = 0, double pthigh = 4, int cbinlow = 0, int cbinhigh = 180, double fitover = false, int binnum=5){
  string isblind = "";
  string fitfunc = "_CC3";
  if(ts == 1614848550){ylim = 2.4;}
  if(ts == 1614932252){ylim = 1.2;}
  if(ts == 1617963007){ylim = 2.4; isblind = "BLIND"; }
  if(ts == 1617964901){ylim = 1.2; isblind = "BLIND"; }

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
  std::vector<std::pair<double, double> > bdtbin;
  bdtbin = bdtbinsec[ts][binnum];
  if(bdtbinsec.find(ts) == bdtbinsec.end()){
  if (binnum==5) {bdtbin ={{-1, -0.2}, {-0.2, -0.1},{-0.1, 0.05},{0.05, 0.2}, {0.2, 1.0}/*{-1, -0.1}, {-0.4,0.1}, {-0.1, 0.0}, {0.0, 0.1}, {0.1, 0.2}, {0.2, 0.3}, {0.3, 0.4},{-0.1, 0.1}, {0.1, 0.3}, {0.3, 1.0}, {0.1, 1.0}, {0.2, 1.0} lastconfig{-1., -0.3},{-1, 0.},{-0.3, -0.1},{-0.1, 0.0},{0.0, 0.1},{0.1, 1.0}*/};}
  else if (binnum ==3) {bdtbin ={{-1, -0.2}, {-0.2, 0.05},{0.05, 1.0}};}
  }
  else std::cout << "BDT bin #"<< binnum <<" not defined" << std::endl;

  int nCores = bdtbin.size();
  string* summary = new string(" ---[INFO]--- Bin Criteria ---------- \n");
  ROOT::EnableImplicitMT();
  ROOT::TProcessExecutor mpe(nCores);
  auto getpoint = [&](int idx)
  {
    double b_low  = bdtbin[idx].first;
    double b_high = bdtbin[idx].second;
    std::cout << "[INFO] CORE " << idx << ", running BDT bin [" << b_low << ", " << b_high << "]" << std::endl;
    *summary += Form(" [INFO] CORE %d, [%.2f, %.2f]: ",idx, b_low, b_high);
    binplotter bp;
    bp = binplotter();

    bp = binplotter(ts, ylim, ptlow, pthigh, cbinlow, cbinhigh, b_low, b_high);
    bp.set_params("_CC3", 0.00);

    bp.dump();
    bp.refit = fitover;
    RooRealVar adjY = bp.yield_eff();
    RooRealVar s = bp.getsignificance(); 
    *summary += Form("nSig: %.2f +- %.3f, nBkg: %.2f += %.3f, Eff: %.5f, Signif: %.2f += %.3f \n",bp.NS->getVal(),bp.NS->getError(),bp.NB->getVal(), bp.NB->getError(), bp.Eff, s.getVal(), s.getError() );
    std::cout << *summary << std::endl;
    std::pair<std::pair<double, double> ,std::pair<RooRealVar, RooRealVar> >result = std::pair<std::pair<double, double>, std::pair<RooRealVar, RooRealVar>>{{b_low, b_high},{adjY, s}};
    return result;
  };

  const auto& res = mpe.Map(getpoint, ROOT::TSeqI(nCores));
  int count =0;
  for (const auto& r : res){
    double b_low  = r.first.first;
    double b_high = r.first.second;
    double binwidth = ( b_high - b_low)/2;
    g1->SetPoint(count, (b_low+ b_high)/2, r.second.second.getVal());
    g1->SetPointError(count, binwidth, binwidth, r.second.second.getError(), r.second.second.getError());

    g2->SetPoint(count, (b_low+b_high)/2, r.second.first.getVal());
    g2->SetPointError(count, binwidth, binwidth, r.second.first.getError(), r.second.first.getError());
    std::cout << "idx: " << count << ", low: " << b_low << ", high: " << b_high << std::endl;
    count++;
  }
  auto hybfitinfo_here = hybfitinfo[ylim][{{cbinlow,cbinhigh},{ptlow, pthigh}}];
  double hybeff = hybfitinfo_here.first;
  double hybval = hybfitinfo_here.second.first;
  double hyberr = hybfitinfo_here.second.second;
  double hybvaleff = hybval/hybeff;
  double hyberreff = hyberr/hybeff;

  pad1->cd();
  g1->SetMarkerStyle(kFullSquare);
  g1->SetMarkerSize(1);
  g1->GetXaxis()->SetLimits(-1, 1);
  g1->GetXaxis()->SetRangeUser(-1, 1);

  g1->GetXaxis()->SetTitle("BDT");
  g1->GetYaxis()->SetTitle("S/#sqrt{S+B}");
  g1->GetYaxis()->SetLimits(-5,8);
  g1->GetYaxis()->SetRangeUser(-5,8);
  g1->Draw("pea");


  pad2->cd();
  TLegend* leg2= new TLegend(0.75,0.8,0.9,0.9);
  leg2->AddEntry(g2_1, "Hybrid SoftID 2018");
  leg2->AddEntry(g2, "BDT Fit");
  g2_1->SetPoint(0, 0, hybvaleff);
  g2_1->SetPointError(0, 1, 1, hyberreff, hyberreff);
  g2_1->SetMarkerStyle(kFullCircle);
  g2_1->SetMarkerSize(1);
  g2_1->SetMarkerColor(kGreen);
  g2->SetMarkerStyle(kFullCircle);
  g2->SetMarkerSize(1);
  g2->SetMarkerColor(kRed);
  g2->GetXaxis()->SetLimits(-1, 1);
  g2->GetXaxis()->SetRangeUser(-1, 1);
  g2->GetYaxis()->SetLimits(hybvaleff - 6*hyberreff, hybvaleff + 6*hyberreff);
  g2->GetYaxis()->SetRangeUser(hybvaleff - 6*hyberreff, hybvaleff + 6*hyberreff);

  g2->GetYaxis()->SetTitle("Yield/Eff");


  g2->Draw("pea");
  TLine* zline = new TLine(-1, 0.,1.,0.);
  zline->SetLineColorAlpha(kRed, 0.5);
  zline->SetLineWidth(2);
  zline->Draw("same");
  TLatex* tl = new TLatex();
  tl->SetNDC();
  tl->DrawLatex(0.7,0.73,Form("pT #in [%.1f, %.1f]",ptlow, pthigh));
  tl->DrawLatex(0.7,0.68,Form("Cent #in [%d %%, %d %%]",cbinlow/2, cbinhigh/2));
  leg2->Draw();
  g2_1->Draw("pe same");

  c1->Update();
  c1->SaveAs(Form("/home/vince402/Upsilon3S/BDT/YieldSigPlot/YtoE_SignifTest_Nbin_%d_y%.1f_pt_%.1f_%.1f_cBin_%d-%d_%s.pdf",binnum, ylim, ptlow, pthigh, cbinlow, cbinhigh, fitfunc.c_str()));
  //c1->Close();
  plotresult(ts, ylim, (int) ptlow, (int) pthigh, cbinlow, cbinhigh ,0.00, "3p5", "S13", "freefit", binnum);

}
