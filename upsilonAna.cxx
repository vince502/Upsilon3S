#include "upsilonAna.h"
#include "./BDT/yield_eff_signif.cxx"
#include "glauberparams_PbPb5TeV.h"

RooRealVar upsi::getcrosssection(std::string type, long ts, double ptlow, double pthigh, double ylow, double yhigh, double sm_ptcut, double clow, double chigh, double blow, double bhigh, int bdtptMin, int bdtptMax, int state =3, bool find_bdt= false)
{
		RooRealVar yield, acc, eff, Lum;
		binplotter bp = binplotter(type, ts, yhigh, ptlow, pthigh, (int) clow, (int) chigh, blow, bhigh, bdtptMin, bdtptMax, state, find_bdt);
		yield = bp.get_yield(state);
		auto eff_pair = bp.get_eff(state);
		eff= RooRealVar("eff", "efficiency" ,eff_pair.first);
		eff.setError(eff_pair.second);
		acc = upsi::getacceptance(ptlow, pthigh, ylow, yhigh, sm_ptcut);

		double Nmb = 11968044281; 
		double upstrig_lumi = 1606.509095330;
		double mbtrig_lumi = 1716.401564710;
		double pre_scale = mbtrig_lumi/upstrig_lumi;
		double Nmb_corr = Nmb/pre_scale;
		std::pair<double, double> taa = glp::Taa[{(int) (clow/2), (int) (chigh/2)}];
		double Lum_err = taa.second*Nmb_corr; 
		std::cout << Form("Nmb_crr %.4f, cbin{%d, %d}, taa{%.4f, %4f}",Nmb_corr, (int) clow, (int) chigh, taa.first, taa.second) << std::endl;

		Lum= RooRealVar("lumi","luminosity 2018", Nmb_corr*taa.first/1e+6);
		Lum.setError(Lum_err);

		double vary, varacc, vareff, varlum;
		double erry, erracc, erreff, errlum;
		vary = yield.getVal(); erry = yield.getError();
		varacc = acc.getVal(); erracc = acc.getError();
		vareff = eff.getVal(); erreff = eff.getError();
		varlum = Lum.getVal(); errlum = Lum.getError();
		double dpt, drap;
		erreff =0;
		erracc =0;
		Lum.setError(0);
		dpt = pthigh-ptlow;
		drap = yhigh*2;
		double bval =  vary/(varacc*vareff*varlum*dpt*drap);
		double berr = bval*TMath::Sqrt(TMath::Power(erry/vary, 2)+(1/(vary*varacc))*TMath::Power(erracc,2)+(1/(vary*vareff))*TMath::Power(erreff,2)+(1/(vary*varlum))*TMath::Power(errlum,2));
		berr = (bval/vary)*erry;
		std::cout << " yield, acc, eff, lum : " << vary <<", "<<varacc << ", " << vareff << ", "<< varlum << std::endl;

		RooRealVar branchFrac = RooRealVar("cs","cross section",bval);
		branchFrac.setError(berr);
		return branchFrac;
	};
