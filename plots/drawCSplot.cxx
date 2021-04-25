#include <iostream>
#include <vector>
#include "TROOT.h"
#include "../upsilonAna.h"

void drawCSplot(){
  long ts =1618913300; //1619021800;
  double blow, bhigh, yhigh;
  blow =0.20;
  bhigh =1.0;
  yhigh = 2.4;


  std::pair<int, int> cbinrange = {0,180}; 
  TCanvas* c1 = new TCanvas("c1", "Cross Section plot", 900,700);
  Double_t* ptbinfour = new Double_t[5]{0,4,9,12,30};
  Double_t* ptbintwo = new Double_t[3]{0,6,30};
  TH1D* h1 = new TH1D("h1", "CS hist", 4, ptbinfour); 
  gStyle->SetOptStat(kFALSE);
  gStyle->SetOptTitle(kFALSE);
  for(int idx =0; idx <4; ++idx){
    RooRealVar cs_bin = upsi::getcrosssection(ts, ptbinfour[idx], ptbinfour[idx+1],0, yhigh, 3.5, (double)cbinrange.first, (double) cbinrange.second, blow, bhigh);
    h1->SetBinContent(idx+1, cs_bin.getVal());
    h1->SetBinError(idx+1, cs_bin.getError());
  }
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kBlue);
  h1->SetLineColor(kBlue);
  h1->GetYaxis()->SetTitle("B #frac{1}{T_{AA}} #frac{dN}{dp_{T}} (nb GeV/c)");
  c1->SetLeftMargin(0.13);
  h1->GetXaxis()->SetTitle("p_{T}");
  h1->Draw();
  TLatex* bdtlabel = new TLatex();
  bdtlabel->SetNDC();
  bdtlabel->DrawLatex(0.25,0.8, Form("BDT #in [%.2f, %.2f]",blow, bhigh));
  c1->SetLogy();
  c1->SaveAs(Form("%s/plots/CrossSection/plot_test_%ld_cBin_%d_%d_%.2f.pdf", workdir.Data(), ts, cbinrange.first, cbinrange.second, blow ));
  c1->SaveAs(Form("%s/plots/CrossSection/plot_test_%ld_cBin_%d_%d_%.2f.cxx", workdir.Data(), ts, cbinrange.first, cbinrange.second, blow ));

}
