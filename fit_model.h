#ifndef FIT_MODEL
#define FIT_MODEL

#include "Custom_Pdf.h"

namespace fit_model_ups{
	class CB2
	{
		public :
			CB2(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooFormulaVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1, RooRealVar* frac2, RooRealVar* frac3);
			CB2(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooRealVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1, RooRealVar* frac2, RooRealVar* frac3);
			~CB2(){};

			RooCBShape *CB1S_1, *CB2S_1, *CB3S_1;
			RooCBShape *CB1S_2, *CB2S_2, *CB3S_2;
			RooAddPdf *twoCB1S, *twoCB2S, *twoCB3S;
	};

	CB2::CB2(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooFormulaVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1, RooRealVar* frac2, RooRealVar* frac3){
	  CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *mass, *mean1S, *sigma1S_1, *alpha1, *n1);
	  CB2S_1 = new RooCBShape("CB2S_1", "2S Crystal ball function1", *mass, *mean2S, *sigma2S_1, *alpha2, *n2);
	  CB3S_1 = new RooCBShape("CB3S_1", "3S Crystal ball function1", *mass, *mean3S, *sigma3S_1, *alpha3, *n3);
	  CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *mass, *mean1S, *sigma1S_2, *alpha1, *n1);
	  CB2S_2 = new RooCBShape("CB2S_2", "2S Crystal ball function2", *mass, *mean2S, *sigma2S_2, *alpha2, *n2);
	  CB3S_2 = new RooCBShape("CB3S_2", "3S Crystal ball function2", *mass, *mean3S, *sigma3S_2, *alpha3, *n3);
	  twoCB1S = new RooAddPdf("twoCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2), RooArgList(*frac1));
	  twoCB2S = new RooAddPdf("twoCB2S", "Sum of 2S Crystal ball", RooArgList(*CB2S_1, *CB2S_2), RooArgList(*frac2));
	  twoCB3S = new RooAddPdf("twoCB3S", "Sum of 3S Crystal ball", RooArgList(*CB3S_1, *CB3S_2), RooArgList(*frac3));
	};
	CB2::CB2(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooRealVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1, RooRealVar* frac2, RooRealVar* frac3){
	  CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *mass, *mean1S, *sigma1S_1, *alpha1, *n1);
	  CB2S_1 = new RooCBShape("CB2S_1", "2S Crystal ball function1", *mass, *mean2S, *sigma2S_1, *alpha2, *n2);
	  CB3S_1 = new RooCBShape("CB3S_1", "3S Crystal ball function1", *mass, *mean3S, *sigma3S_1, *alpha3, *n3);
	  CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *mass, *mean1S, *sigma1S_2, *alpha1, *n1);
	  CB2S_2 = new RooCBShape("CB2S_2", "2S Crystal ball function2", *mass, *mean2S, *sigma2S_2, *alpha2, *n2);
	  CB3S_2 = new RooCBShape("CB3S_2", "3S Crystal ball function2", *mass, *mean3S, *sigma3S_2, *alpha3, *n3);
	  twoCB1S = new RooAddPdf("twoCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2), RooArgList(*frac1));
	  twoCB2S = new RooAddPdf("twoCB2S", "Sum of 2S Crystal ball", RooArgList(*CB2S_1, *CB2S_2), RooArgList(*frac2));
	  twoCB3S = new RooAddPdf("twoCB3S", "Sum of 3S Crystal ball", RooArgList(*CB3S_1, *CB3S_2), RooArgList(*frac3));
	};

	class ChebyChev
	{
		public :
			ChebyChev(RooRealVar* mass, RooRealVar* cc_k1){
				bkg = new RooChebychev("CCBkg", "Background cc1", *mass, RooArgSet(*cc_k1));
			};
			ChebyChev(RooRealVar* mass, RooRealVar* cc_k1, RooRealVar* cc_k2){
				bkg = new RooChebychev("CCBkg", "Background cc2", *mass, RooArgSet(*cc_k1, *cc_k2));
			};
			ChebyChev(RooRealVar* mass, RooRealVar* cc_k1, RooRealVar* cc_k2, RooRealVar* cc_k3){
				bkg = new RooChebychev("CCBkg", "Background cc3", *mass, RooArgSet(*cc_k1, *cc_k2, *cc_k3));
			};
			ChebyChev(RooRealVar* mass, RooRealVar* cc_k1, RooRealVar* cc_k2, RooRealVar* cc_k3, RooRealVar* cc_k4){
				bkg = new RooChebychev("CCBkg", "Background cc4", *mass, RooArgSet(*cc_k1, *cc_k2, *cc_k3, *cc_k4));
			};
			~ChebyChev();
			RooChebychev* bkg;
	};

	class ErfExp
	{
	  	public :
			ErfExp(RooRealVar* mass, RooRealVar* mean, RooRealVar* sigma, RooRealVar* p0){ bkgErf = new RooGenericPdf("bkgErf", "ErfExp background", "TMath::Exp(-@0/@1)*(TMath::Erf((@0-@2)/(TMath::Sqrt(2)*@3))+1)*0.5", RooArgList(*mass, *p0, *mean, *sigma));
			};
			~ErfExp();

			RooGenericPdf* bkgErf;
	};
};

#endif
