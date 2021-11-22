#include "TH1D.h"
#include "TFile.h"
#include "TROOT.h"
#include <iostream>


TH1D* loadHist(TFile* f, string s_hist = ""){
  TH1D* hist = (TH1D*) f->Get(s_hist.c_str()) ;
  return hist;
};
