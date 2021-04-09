#ifndef CALC_CXX
#define CALC_CXX

#include "BDT/yield_eff_signif.cxx"
#include "glauberparams_PbPb5TeV.h"

using namespace glp;

binplotter bp = binplotter();
try: bp.yield_eff();
RooRealVar* resyield = bp.yield;
double resEff = bp.Eff();
double resAcc;

Double_t cs = resyield.getVal()/(resAcc*resEff);

#endif
