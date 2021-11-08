#ifndef UPSILONANA_H
#define UPSILONANA_H

#include "RooFit.h"
#include ".workdir.h"
#include "./BDT/yield_eff_signif.h"


namespace upsi{

	RooRealVar getacceptance(double ptlow, double pthigh, double ylow, double yhigh, double sm_ptcut, int sample_state = 3, bool isptWeight =true){
		TFile* accfile = TFile::Open(Form("%s/Acceptance/AccRes_%dS_y%.1f_%.1f_SimuPt%.1f_ptW%d.root",workdir.Data(), sample_state, ylow, yhigh, sm_ptcut, isptWeight));
		TH1D* hGen = (TH1D*) accfile->Get("hGen");
		TH1D* hGenAcc = (TH1D*) accfile->Get("hGenAcc");
		double NGen = hGen->Integral((int) ptlow +1, (int) pthigh);
		double NGenAcc = hGenAcc->Integral((int) ptlow +1, (int) pthigh);
		double Acc = NGenAcc/NGen;
		RooRealVar returnVal = RooRealVar("accVar","accVar", Acc,-2,2);
		returnVal.setError(TMath::Sqrt(Acc));
		return returnVal;
	};

	RooRealVar getcrosssection(std::string type, long ts, double ptlow, double pthigh, double ylow, double yhigh, double sm_ptcut, double clow, double chigh, double blow, double bhigh, int bdtptMin, int bdtptMax, int state =3, bool find_bdt = false);

};

//std::map<int, double> bdt_tmp_val = { {1, -0.0810 }, {2, 0.1997 }, {3,0.0818 } };
//std::map<int, double> bdt_tmp_val2 = { {3, 0.2898 }, {2, 0.0808 }, {1,-0.0673 } };
std::map<int, double> bdt_tmp_val = { {1, 0.0 }, {2, 0.}, {3,0.0 } };
std::map<int, double> bdt_tmp_val2 = { {3, 0. }, {2, 0. }, {1,0. } };
std::map<int, double> bdt_tmp_val3 = { {1, 0. }, {2, 0.}, {3, -1 } };
std::map<int, double> bdt_tmp_val4 = { {3, -1}, {2, -1 }, {1, -1 } };

#endif
