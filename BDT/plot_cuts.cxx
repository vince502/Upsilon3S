#include <iostream>
#include "bininfo.h"
#include "../.workdir.h"
#include "GOBC.cxx"

TH1D* plot_cuts(){

  TH1D* hist = new TH1D("Hist", "" , 99, 1, 100);
  for ( int i = 1 ; i < 10; i+=4){
    auto res = GOBC(1623391157, 0, 30, -2.4, 2.4, 0, 180, 0.00, (1./ (double) i), "", "S2") ;
    hist->SetBinContent(i, res.first);
  }

  return hist;
};
TH2D* plot_cuts2d(){

  TH2D* hist = new TH2D("Hist", "" , 99, 1, 100, (int) (1.5/interval_score), -0.5, 1);
  for ( int i = 1 ; i < 100; i++){
    auto res = GOBC(1623391157, 0, 30, -2.4, 2.4, 0, 180, 0.00, (1.* (double) i)) ;
    std::cout << res.first << std::endl;
    auto histo1D = func_hist_optimal_BDT();
    int NBINS = histo1D->GetNbinsX();
    for (int idx = 1 ; idx < NBINS+1 ; idx++){
      Double_t content = histo1D->GetBinContent(idx);
      Double_t conterr = histo1D->GetBinError(idx);
      hist->SetBinContent(i, idx, content);
      hist->SetBinError(i, idx, conterr);
    }

  }

  return hist;
};
void plot_cuts_2(){

    auto res = GOBC(1623391157, 0, 30, -2.4, 2.4, 0, 180, 0.00, (1./ (double) 20)) ;
    std::cout << res.first << std::endl;

};
