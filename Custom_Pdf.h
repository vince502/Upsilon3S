#ifndef CUSTOMPDF_H
#define CUSTOMPDF_H
#include <TMath.h>
#include <TROOT.h>
#include "./CustomPDF/GausExp.cxx"
#include "./CustomPDF/ExpGausExp.cxx"

//Double_t GausExp(Double_t x, Double_t meanx, Double_t k, Double_t sig){
//if( (x-meanx)/sig >= -k){
//  return TMath::Exp(-(0.5)*TMath::Power(((x-meanx)/sig),2));
//  }
//  else{
//    return TMath::Exp(TMath::Power(k,2)/2+k*((x-meanx)/sig));
//  }
//};
//
//Double_t ExpGausExp(Double_t x, Double_t meanx, Double_t kl, Double_t kh, Double_t sig ){
//  if((x-meanx)/sig <= -kl){
//    return TMath::Exp(TMath::Power(kl,2)/2 + kl*((x-meanx)/sig));
//    }
//  else if(((x-meanx)/sig > -kl) && ((x-meanx)/sig) <= kh){
//    return TMath::Exp(-(1/2)*TMath::Power(((x-meanx)/sig),2));
//    }
//  else if(((x-meanx)/sig > kh)){
//    return TMath::Exp(TMath::Power(kl,2)/2 - kh*((x-meanx)/sig));
//  }
//  else return 0;
//};
#endif
