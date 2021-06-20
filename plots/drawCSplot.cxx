#include <iostream>
#include <vector>
#include "TROOT.h"
#include "../upsilonAna.cxx"

void f_drawCSplot(){
  long ts = 1623391157; // 1621574976; //2D var 1621568219 ;//1619743777;//11.0 mass up //1619742556; //11.5 mass////// 1618913300; //1619021800;
  double blow, bhigh, yhigh;
  blow =0.20;
  bhigh =1.0;
  yhigh = 2.4;

  std::pair<int, int> cbinrange = {0,180}; 
  TCanvas* c1 = new TCanvas("c1", "Cross Section plot", 900,700);
  c1->cd();
  Double_t* ptbinfour = new Double_t[5]{0,4,9,12,30};
  Double_t* ptbintwo = new Double_t[3]{0,6,30};
  TH1D* h1 = new TH1D("h1", "CS hist", 2, ptbintwo); 
  gStyle->SetOptStat(kFALSE);
  gStyle->SetOptTitle(kFALSE);
  for(int idx =0; idx <2; ++idx){
    blow = Get_Optimal_BDT(ts, ptbintwo[idx], ptbintwo[idx+1], -2.4, 2.4, cbinrange.first, cbinrange.second, 0.00).first;
//    RooRealVar cs_bin = upsi::getcrosssection("CB2:CC2:FFDD3",ts, ptbintwo[idx], ptbintwo[idx+1],0, yhigh, 3.5, (double)cbinrange.first, (double) cbinrange.second, blow, bhigh);
    RooRealVar cs_bin = upsi::getcrosssection("CB3:CC2:GC",ts, ptbintwo[idx], ptbintwo[idx+1],0, yhigh, 3.5, (double)cbinrange.first, (double) cbinrange.second, blow, bhigh);
    h1->SetBinContent(idx+1, cs_bin.getVal());
    h1->SetBinError(idx+1, cs_bin.getError());
    std::cout << cs_bin.getVal() << " +- " << cs_bin.getError() << std::endl; 
  }
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kBlue);
  h1->SetLineColor(kBlue);
  h1->GetYaxis()->SetTitle("B #frac{1}{T_{AA}} #frac{dN}{dp_{T}} (nb GeV/c)");
  c1->SetLeftMargin(0.13);
  h1->GetXaxis()->SetTitle("p_{T}");
  h1->Draw("APL");
  TLatex* bdtlabel = new TLatex();
  bdtlabel->SetNDC();
  bdtlabel->DrawLatex(0.25,0.8, Form("BDT #in [%.2f, %.2f]",blow, bhigh));
  c1->SetLogy();
  c1->Draw();
  c1->Update();
//  c1->SaveAs(Form("%s/plots/CrossSection/plot_%s_%d_%ld_cBin_%d_%d_%.2f.pdf", workdir.Data(), "GC", 2,ts, cbinrange.first, cbinrange.second, blow ));
  c1->SaveAs(Form("%s/plots/CrossSection/plot.pdf", workdir.Data() ));
  c1->SaveAs(Form("%s/plots/CrossSection/plot_%s_%d_%ld_cBin_%d_%d_%.2f.cxx", workdir.Data(), "GC", 2,ts, cbinrange.first, cbinrange.second, blow ));

};

void drawCSplot(){
  f_drawCSplot();
}
