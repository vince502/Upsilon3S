#include <iostream>
#include <vector>
#include "TROOT.h"
#include "../upsilonAna.h"

void drawCSplot(){
  long ts = 1614848550;
  double blow, bhigh, yhigh;
  blow =0.05;
  bhigh =1.0;
  yhigh = 2.4;


  std::pair<int, int> cbinrange = {0,180}; 
  TCanvas* c1 = new TCanvas("c1", "Cross Section plot", 800,700);
  Double_t* ptbinfour = new Double_t[5]{0,4,9,12,30};
  Double_t* ptbintwo = new Double_t[3]{0,6,30};
  TH1D* h1 = new TH1D("h1", "CS hist", 4, ptbinfour); 
//  c1->SetOptStat(0);
  for(int idx =0; idx <4; ++idx){
    RooRealVar cs_bin = upsi::getcrosssection(ts, ptbinfour[idx], ptbinfour[idx+1],0, yhigh, 3.5, (double)cbinrange.first, (double) cbinrange.second, blow, bhigh);
    h1->SetBinContent(idx+1, cs_bin.getVal());
    h1->SetBinError(idx+1, cs_bin.getError());
  }
  h1->Draw();
  c1->SetLogy();
  c1->SaveAs(Form("%s/plots/CrossSection/plot_test.pdf",workdir.Data()) );
  c1->SaveAs(Form("%s/plots/CrossSection/plot_test.cxx",workdir.Data()) );

}
