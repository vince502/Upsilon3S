#ifndef UPSILONANA_H
#define UPSILONANA_H

#include "RooFit.h"
#include ".workdir.h"
#include "./BDT/yield_eff_signif.h"


namespace upsi{

	RooRealVar getacceptance(double ptlow, double pthigh, double ylow, double yhigh, double sm_ptcut, int sample_state = 3, bool isptWeight =true){
		TFile* accfile = TFile::Open(Form("%s/Acceptance/AccRes_%dS_pt%.1f_%.1f_y%.1f_%.1f_SimuPt%.1f_ptW%d.root",workdir.Data(), sample_state, ptlow, pthigh, ylow, yhigh, sm_ptcut, isptWeight));
		TH1D* htmp = (TH1D*) accfile->Get("hGenRatio");
		RooRealVar returnVal = RooRealVar("accVar","accVar", htmp->GetBinContent(1),-2,2);
		returnVal.setError(htmp->GetBinError(1));
		return returnVal;
	};

	RooRealVar getcrosssection(std::string type, long ts, double ptlow, double pthigh, double ylow, double yhigh, double sm_ptcut, double clow, double chigh, double blow, double bhigh);

};

std::map<int, double> bdt_tmp_val = { {1, -0.0810 }, {2, 0.1997 }, {3,0.0818 } };
std::map<int, double> bdt_tmp_val2 = { {3, 0.2898 }, {2, 0.0808 }, {1,-0.0673 } };

#endif
