/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef EXPGAUSEXP
#define EXPGAUSEXP

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class ExpGausExp : public RooAbsPdf {
public:
  ExpGausExp() {} ; 
  ExpGausExp(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _meanx,
	      RooAbsReal& _kl,
	      RooAbsReal& _kh,
	      RooAbsReal& _sig);
  ExpGausExp(const ExpGausExp& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new ExpGausExp(*this,newname); }
  inline virtual ~ExpGausExp() { }

protected:

  RooRealProxy x ;
  RooRealProxy meanx ;
  RooRealProxy kl ;
  RooRealProxy kh ;
  RooRealProxy sig ;
  
  Double_t evaluate() const ;

private:

  ClassDef(ExpGausExp,1) // Your description goes here...
};
 
#endif
