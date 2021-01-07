#include <TMath.h>
#include <TROOT.h>

Double_t GausExp(Double_t x, Double_t meanx, Double_t k, Double_t sig){
if( (x-meanx)/sig >= -k){
  return TMath::Exp(-(0.5)*TMath::Power(((x-meanx)/sig),2));
  }
  else{
    return TMath::Exp(TMath::Power(k,2)/2+k*((x-meanx)/sig));
  }
};
