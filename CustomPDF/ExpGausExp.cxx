/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "ExpGausExp.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(ExpGausExp); 

 ExpGausExp::ExpGausExp(const char *name, const char *title, 
                        RooAbsReal& _x,
                        RooAbsReal& _meanx,
                        RooAbsReal& _kl,
                        RooAbsReal& _kh,
                        RooAbsReal& _sig) :
   RooAbsPdf(name,title), 
   x("x","x",this,_x),
   meanx("meanx","meanx",this,_meanx),
   kl("kl","kl",this,_kl),
   kh("kh","kh",this,_kh),
   sig("sig","sig",this,_sig)
 { 
 } 


 ExpGausExp::ExpGausExp(const ExpGausExp& other, const char* name) :  
   RooAbsPdf(other,name), 
   x("x",this,other.x),
   meanx("meanx",this,other.meanx),
   kl("kl",this,other.kl),
   kh("kh",this,other.kh),
   sig("sig",this,other.sig)
 { 
 } 



 Double_t ExpGausExp::evaluate() const 
 { 
  if((x-meanx)/sig <= -kl){
    return TMath::Exp(TMath::Power(kl,2)/2 + kl*((x-meanx)/sig));
    }
  else if(((x-meanx)/sig > -kl) && ((x-meanx)/sig) <= kh){
    return TMath::Exp(-(1/2)*TMath::Power(((x-meanx)/sig),2));
    }
  else if(((x-meanx)/sig > kh)){
    return TMath::Exp(TMath::Power(kl,2)/2 - kh*((x-meanx)/sig));
  }
  else return 0;
 } 


