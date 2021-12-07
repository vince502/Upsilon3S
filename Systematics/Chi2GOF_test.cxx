//Goodness of Fit decision macro, Chebyshev bkg order must be defined prior to this test
#pragma once
#include "../BDT/bininfo.h"
#include "../LLR_CCorder.h"

Chi2GOF_test(ana_bins ab){
	long ts = 9999999999;
	int CCO = getNomBkgO(ab);

	string typeCC = Form("CB3:CC%d:%s", CCO, fittype);
	string typeEE = Form("CB3:EE:%s", fittype);
	string typeEX = Form("CB3:EX:%s", fittype);

	string fitCC = GetFit(__FITRESLATEST, false, typeCC, ts, ab.state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	string fitCC = GetFit(__FITRESLATEST, false, typeEE, ts, ab.state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
	string fitCC = GetFit(__FITRESLATEST, false, typeEX, ts, ab.state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, Get_BDT(ts, ab), 1, ab.bpl, ab.bph, 0, "");
}
