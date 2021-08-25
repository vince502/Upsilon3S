#ifndef FIT_MODEL
#define FIT_MODEL

#include "Custom_Pdf.h"

namespace fit_model_ups{
	class CB2
	{
		public :
			CB2(){};
			CB2(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooFormulaVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1, RooRealVar* frac2, RooRealVar* frac3);
			CB2(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooRealVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1, RooRealVar* frac2, RooRealVar* frac3);
			CB2(RooRealVar* mass, RooRealVar* mean1S, RooRealVar* sigma1S_1, RooFormulaVar* sigma1S_2, RooRealVar* alpha1, RooRealVar* n1, RooRealVar* frac1);
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
	CB2::CB2(RooRealVar* mass, RooRealVar* mean1S,  RooRealVar* sigma1S_1, RooFormulaVar* sigma1S_2, RooRealVar* alpha1, RooRealVar* n1, RooRealVar* frac1){
	  CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *mass, *mean1S, *sigma1S_1, *alpha1, *n1);
	  CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *mass, *mean1S, *sigma1S_2, *alpha1, *n1);
	  twoCB1S = new RooAddPdf("twoCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2), RooArgList(*frac1));
	};
	
	class CB2Gaus : public CB2
	{
	  	public :
			CB2Gaus() : CB2(){};
			CB2Gaus(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooFormulaVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooFormulaVar* sigma1S_3, RooFormulaVar* sigma2S_3, RooFormulaVar* sigma3S_3, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1_1, RooRealVar* frac2_1, RooRealVar* frac3_1, RooRealVar* frac1_2, RooRealVar* frac2_2, RooRealVar* frac3_2) : CB2(mass, mean1S, mean2S, mean3S, sigma1S_1, sigma2S_1, sigma3S_1, sigma1S_2, sigma2S_2, sigma3S_2, alpha1, alpha2, alpha3, n1, n2, n3, frac1_1, frac2_1, frac3_1){
				G1S = new RooGaussian("G1S", "Gaussian of 1S of CB2G", *mass, *mean1S, *sigma1S_3);
				G2S = new RooGaussian("G2S", "Gaussian of 2S of CB2G", *mass, *mean2S, *sigma2S_3);
				G3S = new RooGaussian("G3S", "Gaussian of 3S of CB2G", *mass, *mean3S, *sigma3S_3);
				CBG1S = new RooAddPdf("twoCBGaus1S", "Sum of 1S Double CB and Gaus", RooArgList(*CB1S_1, *CB1S_2, *G1S), RooArgList(*frac1_1, *frac1_2) );
				CBG2S = new RooAddPdf("twoCBGaus2S", "Sum of 2S Double CB and Gaus", RooArgList(*CB2S_1, *CB2S_2, *G2S), RooArgList(*frac2_1, *frac2_2) );
				CBG3S = new RooAddPdf("twoCBGaus3S", "Sum of 3S Double CB and Gaus", RooArgList(*CB3S_1, *CB3S_2, *G3S), RooArgList(*frac3_1, *frac3_2) );
			};
			CB2Gaus(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooRealVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooFormulaVar* sigma1S_3, RooFormulaVar* sigma2S_3, RooFormulaVar* sigma3S_3, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1_1, RooRealVar* frac2_1, RooRealVar* frac3_1, RooRealVar* frac1_2, RooRealVar* frac2_2, RooRealVar* frac3_2) : CB2(mass, mean1S, mean2S, mean3S, sigma1S_1, sigma2S_1, sigma3S_1, sigma1S_2, sigma2S_2, sigma3S_2, alpha1, alpha2, alpha3, n1, n2, n3, frac1_1, frac2_1, frac3_1){
				G1S = new RooGaussian("G1S", "Gaussian of 1S of CB2G", *mass, *mean1S, *sigma1S_3);
				G2S = new RooGaussian("G2S", "Gaussian of 2S of CB2G", *mass, *mean2S, *sigma2S_3);
				G3S = new RooGaussian("G3S", "Gaussian of 3S of CB2G", *mass, *mean3S, *sigma3S_3);
				CBG1S = new RooAddPdf("twoCBGaus1S", "Sum of 1S Double CB and Gaus", RooArgList(*CB1S_1, *CB1S_2, *G1S), RooArgList(*frac1_1, *frac1_2) );
				CBG2S = new RooAddPdf("twoCBGaus2S", "Sum of 2S Double CB and Gaus", RooArgList(*CB2S_1, *CB2S_2, *G2S), RooArgList(*frac2_1, *frac2_2) );
				CBG3S = new RooAddPdf("twoCBGaus3S", "Sum of 3S Double CB and Gaus", RooArgList(*CB3S_1, *CB3S_2, *G3S), RooArgList(*frac3_1, *frac3_2) );
			};
			CB2Gaus(RooRealVar* mass, RooRealVar* mean1S, RooRealVar* sigma1S_1, RooFormulaVar* sigma1S_2,RooFormulaVar* sigma1S_3, RooRealVar* alpha1, RooRealVar* n1,RooRealVar* frac1_1,RooRealVar* frac1_2) : CB2(mass, mean1S, sigma1S_1, sigma1S_2, alpha1, n1, frac1_1){
				G1S = new RooGaussian("GNS", "Gaussian of 1S of CB2G", *mass, *mean1S, *sigma1S_3);
				CBG1S = new RooAddPdf("twoCBGausNS", "Sum of NS Double CB and Gaus", RooArgList(*CB1S_1, *CB1S_2, *G1S), RooArgList(*frac1_1, *frac1_2) );
			};
			~CB2Gaus(){};
			RooGaussian *G1S, *G2S, *G3S;
			RooAddPdf *CBG1S, *CBG2S, *CBG3S;
	};

	class ChebyChev
	{
		public :
			ChebyChev(){};
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
			ChebyChev(RooRealVar* mass, RooRealVar* cc_k1, RooRealVar* cc_k2, RooRealVar* cc_k3, RooRealVar* cc_k4, RooRealVar* cc_k5){
				bkg = new RooChebychev("CCBkg", "Background cc5", *mass, RooArgSet(*cc_k1, *cc_k2, *cc_k3, *cc_k4, *cc_k5));
			};
			ChebyChev(RooRealVar* mass, RooRealVar* cc_k1, RooRealVar* cc_k2, RooRealVar* cc_k3, RooRealVar* cc_k4, RooRealVar* cc_k5, RooRealVar* cc_k6){
				bkg = new RooChebychev("CCBkg", "Background cc6", *mass, RooArgSet(*cc_k1, *cc_k2, *cc_k3, *cc_k4, *cc_k5, *cc_k6));
			};
			~ChebyChev(){};
			RooChebychev* bkg = nullptr;
	};
	class ExpChebyChev : public ChebyChev
	{
		public :
			ExpChebyChev(RooChebychev* _bkg) : ChebyChev() {
				if (_bkg == nullptr) return;
				auto tmp = new RooConstVar("ce", "coeff exponent",1);
			  	bkgECC = (RooGenericPdf*) new RooExponential("bkgECC", "", *_bkg, *tmp );
				delete tmp;
			}
			~ExpChebyChev(){};
			RooGenericPdf* bkgECC;
	};

	class ErfExp
	{
	  	public :
			ErfExp(RooRealVar* mass, RooRealVar* mean, RooRealVar* sigma, RooRealVar* p0){ bkgErf = new RooGenericPdf("bkgErf", "ErfExp background", "TMath::Exp(-@0/@1)*(TMath::Erf((@0-@2)/(TMath::Sqrt(2)*@3))+1)*0.5", RooArgList(*mass, *p0, *mean, *sigma));
			};
			~ErfExp(){};

			RooGenericPdf* bkgErf;
	};
	
	class DoubleGausExp
	{
	  	public :
			DoubleGausExp(int state, RooRealVar* mass, RooRealVar* mean, RooRealVar* k_1, RooRealVar* k_2, RooRealVar* sigma_1, RooFormulaVar* sigma_2, RooRealVar* frac);
			DoubleGausExp(int state, RooRealVar* mass, RooRealVar* mean, RooRealVar* k_1, RooRealVar* k_2, RooRealVar* k_3, RooRealVar* sigma_1, RooFormulaVar* sigma_2, RooFormulaVar* sigma_3, RooRealVar* frac1, RooRealVar* frac2);
			DoubleGausExp(RooRealVar* mass, RooRealVar* mean1S, RooRealVar* mean2S, RooRealVar* mean3S, RooRealVar* k, RooRealVar* sigma1S_1, RooRealVar* sigma1S_2, RooRealVar* sigma2S_1, RooRealVar* sigma2S_2, RooRealVar* sigma3S_1, RooRealVar* sigma3S_2, RooRealVar* frac);
			~DoubleGausExp(){};

			GausExp *GE1S_1, *GE2S_1, *GE3S_1;
			GausExp *GE1S_2, *GE2S_2, *GE3S_2;
			GausExp *GE1S_3, *GE2S_3, *GE3S_3;
			RooAddPdf *twoGE1S, *twoGE2S, *twoGE3S;
			RooAddPdf *threeGE1S, *threeGE2S, *threeGE3S;
			std::map<int, std::pair<GausExp**, GausExp**> > map_state = { {1, {&GE1S_1, &GE1S_2}}, {2, {&GE2S_1, &GE2S_1}}, {3, {&GE3S_1, &GE3S_2}} };
			std::map<int, GausExp**> map_state_3 = { {1,  &GE1S_3}, {2, &GE2S_3}, {3,&GE3S_3} };
			std::map<int, RooAddPdf** > map_bindfunc = { {1,&twoGE1S}, {2, &twoGE2S}, {3, &twoGE3S},
	 {11,&threeGE1S}, {12, &threeGE2S}, {13, &threeGE3S} 		};
	};

	DoubleGausExp::DoubleGausExp(int state, RooRealVar* mass, RooRealVar* mean, RooRealVar* k_1, RooRealVar* k_2, RooRealVar* sigma_1, RooFormulaVar* sigma_2, RooRealVar* frac1){
	  *map_state[state].first = new GausExp(Form("GE%dS_1",state),Form("GE%dS_1 function",state), *mass, *mean, *k_1, *sigma_1);
	  *map_state[state].second = new GausExp(Form("GE%dS_2",state),Form("GE%dS_2 function",state), *mass, *mean, *k_2, *sigma_2);
	  *map_bindfunc[state] = new RooAddPdf(Form("twoGE%dS",state),Form("Sum of %dS GausExp function",state), RooArgList(**map_state[state].first, **map_state[state].second), RooArgList(*frac1) );
	};
	DoubleGausExp::DoubleGausExp(int state, RooRealVar* mass, RooRealVar* mean, RooRealVar* k_1, RooRealVar* k_2, RooRealVar* k_3, RooRealVar* sigma_1, RooFormulaVar* sigma_2, RooFormulaVar* sigma_3, RooRealVar* frac, RooRealVar* frac2){
	  *map_state[state].first = new GausExp(Form("GE%dS_1",state),Form("GE%dS_1 function",state), *mass, *mean, *k_1, *sigma_1);
	  *map_state[state].second = new GausExp(Form("GE%dS_2",state),Form("GE%dS_2 function",state), *mass, *mean, *k_2, *sigma_2);
	  *map_state_3[state]= new GausExp(Form("GE%dS_3",state),Form("GE%dS_3 function",state), *mass, *mean, *k_3, *sigma_3);
	  *map_bindfunc[10+state] = new RooAddPdf(Form("threeGE%dS",state),Form("Sum of %dS GausExp function",state), RooArgList(**map_state[state].first, **map_state[state].second, **map_state_3[state]), RooArgList(*frac,*frac2) );
	};

	DoubleGausExp::DoubleGausExp(RooRealVar* mass, RooRealVar* mean1S, RooRealVar* mean2S, RooRealVar* mean3S, RooRealVar* k, RooRealVar* sigma1S_1, RooRealVar* sigma1S_2, RooRealVar* sigma2S_1, RooRealVar* sigma2S_2, RooRealVar* sigma3S_1, RooRealVar* sigma3S_2, RooRealVar* frac){

	  };


	class CB3
	{
		public :
			CB3(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooFormulaVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooFormulaVar* sigma1S_3, RooFormulaVar* sigma2S_3, RooFormulaVar* sigma3S_3, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1_1, RooRealVar* frac2_1, RooRealVar* frac3_1, RooRealVar* frac1_2, RooRealVar* frac2_2, RooRealVar* frac3_2);
			CB3(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooFormulaVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooFormulaVar* sigma1S_3, RooFormulaVar* sigma2S_3, RooFormulaVar* sigma3S_3, RooRealVar* alpha1, RooRealVar* n1, RooRealVar* frac1_1, RooRealVar* frac1_2);
			CB3(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooRealVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooFormulaVar* sigma1S_3, RooFormulaVar* sigma2S_3, RooFormulaVar* sigma3S_3, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1_1, RooRealVar* frac1_2);
			~CB3(){};

			RooCBShape *CB1S_1, *CB2S_1, *CB3S_1;
			RooCBShape *CB1S_2, *CB2S_2, *CB3S_2;
			RooCBShape *CB1S_3, *CB2S_3, *CB3S_3;
			RooAddPdf *threeCB1S, *threeCB2S, *threeCB3S;
	};

	CB3::CB3(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooFormulaVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooFormulaVar* sigma1S_3, RooFormulaVar* sigma2S_3, RooFormulaVar* sigma3S_3, RooRealVar* alpha1, RooRealVar* n1, RooRealVar* frac1_1, RooRealVar* frac1_2){
	  
	  CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *mass, *mean1S, *sigma1S_1, *alpha1, *n1);
	  CB2S_1 = new RooCBShape("CB2S_1", "2S Crystal ball function1", *mass, *mean2S, *sigma2S_1, *alpha1, *n1);
	  CB3S_1 = new RooCBShape("CB3S_1", "3S Crystal ball function1", *mass, *mean3S, *sigma3S_1, *alpha1, *n1);
	  CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *mass, *mean1S, *sigma1S_2, *alpha1, *n1);
	  CB2S_2 = new RooCBShape("CB2S_2", "2S Crystal ball function2", *mass, *mean2S, *sigma2S_2, *alpha1, *n1);
	  CB3S_2 = new RooCBShape("CB3S_2", "3S Crystal ball function2", *mass, *mean3S, *sigma3S_2, *alpha1, *n1);
	  CB1S_3 = new RooCBShape("CB1S_3", "1S Crystal ball function3", *mass, *mean1S, *sigma1S_3, *alpha1, *n1);
	  CB2S_3 = new RooCBShape("CB2S_3", "2S Crystal ball function3", *mass, *mean2S, *sigma2S_3, *alpha1, *n1);
	  CB3S_3 = new RooCBShape("CB3S_3", "3S Crystal ball function3", *mass, *mean3S, *sigma3S_3, *alpha1, *n1);
	  threeCB1S = new RooAddPdf("threeCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2, *CB1S_3), RooArgList(*frac1_1, *frac1_2));
	  threeCB2S = new RooAddPdf("threeCB2S", "Sum of 2S Crystal ball", RooArgList(*CB2S_1, *CB2S_2, *CB2S_3), RooArgList(*frac1_1, *frac1_2));
	  threeCB3S = new RooAddPdf("threeCB3S", "Sum of 3S Crystal ball", RooArgList(*CB3S_1, *CB3S_2, *CB3S_3), RooArgList(*frac1_1, *frac1_2));
	};

	CB3::CB3(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooFormulaVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooFormulaVar* sigma1S_3, RooFormulaVar* sigma2S_3, RooFormulaVar* sigma3S_3, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1_1, RooRealVar* frac2_1, RooRealVar* frac3_1, RooRealVar* frac1_2, RooRealVar* frac2_2, RooRealVar* frac3_2){
	  CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *mass, *mean1S, *sigma1S_1, *alpha1, *n1);
	  CB2S_1 = new RooCBShape("CB2S_1", "2S Crystal ball function1", *mass, *mean2S, *sigma2S_1, *alpha2, *n2);
	  CB3S_1 = new RooCBShape("CB3S_1", "3S Crystal ball function1", *mass, *mean3S, *sigma3S_1, *alpha3, *n3);
	  CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *mass, *mean1S, *sigma1S_2, *alpha1, *n1);
	  CB2S_2 = new RooCBShape("CB2S_2", "2S Crystal ball function2", *mass, *mean2S, *sigma2S_2, *alpha2, *n2);
	  CB3S_2 = new RooCBShape("CB3S_2", "3S Crystal ball function2", *mass, *mean3S, *sigma3S_2, *alpha3, *n3);
	  CB1S_3 = new RooCBShape("CB1S_2", "1S Crystal ball function3", *mass, *mean1S, *sigma1S_3, *alpha1, *n1);
	  CB2S_3 = new RooCBShape("CB2S_2", "2S Crystal ball function3", *mass, *mean2S, *sigma2S_3, *alpha2, *n2);
	  CB3S_3 = new RooCBShape("CB3S_2", "3S Crystal ball function3", *mass, *mean3S, *sigma3S_3, *alpha3, *n3);
	  threeCB1S = new RooAddPdf("threeCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2, *CB1S_3), RooArgList(*frac1_1, *frac1_2));
	  threeCB2S = new RooAddPdf("threeCB2S", "Sum of 2S Crystal ball", RooArgList(*CB2S_1, *CB2S_2, *CB2S_3), RooArgList(*frac2_1, *frac2_2));
	  threeCB3S = new RooAddPdf("threeCB3S", "Sum of 3S Crystal ball", RooArgList(*CB3S_1, *CB3S_2, *CB3S_3), RooArgList(*frac3_1, *frac3_2));
	};

	CB3::CB3(RooRealVar* mass, RooRealVar* mean1S, RooFormulaVar* mean2S, RooRealVar* mean3S, RooRealVar* sigma1S_1, RooFormulaVar* sigma2S_1,RooFormulaVar* sigma3S_1, RooFormulaVar* sigma1S_2, RooFormulaVar* sigma2S_2, RooFormulaVar* sigma3S_2, RooFormulaVar* sigma1S_3, RooFormulaVar* sigma2S_3, RooFormulaVar* sigma3S_3, RooRealVar* alpha1, RooRealVar* alpha2, RooRealVar* alpha3, RooRealVar* n1, RooRealVar* n2, RooRealVar* n3, RooRealVar* frac1_1, RooRealVar* frac1_2){
	  CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *mass, *mean1S, *sigma1S_1, *alpha1, *n1);
	  CB2S_1 = new RooCBShape("CB2S_1", "2S Crystal ball function1", *mass, *mean2S, *sigma2S_1, *alpha2, *n2);
	  CB3S_1 = new RooCBShape("CB3S_1", "3S Crystal ball function1", *mass, *mean3S, *sigma3S_1, *alpha3, *n3);
	  CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *mass, *mean1S, *sigma1S_2, *alpha1, *n1);
	  CB2S_2 = new RooCBShape("CB2S_2", "2S Crystal ball function2", *mass, *mean2S, *sigma2S_2, *alpha2, *n2);
	  CB3S_2 = new RooCBShape("CB3S_2", "3S Crystal ball function2", *mass, *mean3S, *sigma3S_2, *alpha3, *n3);
	  CB1S_3 = new RooCBShape("CB1S_2", "1S Crystal ball function3", *mass, *mean1S, *sigma1S_3, *alpha1, *n1);
	  CB2S_3 = new RooCBShape("CB2S_2", "2S Crystal ball function3", *mass, *mean2S, *sigma2S_3, *alpha2, *n2);
	  CB3S_3 = new RooCBShape("CB3S_2", "3S Crystal ball function3", *mass, *mean3S, *sigma3S_3, *alpha3, *n3);
	  threeCB1S = new RooAddPdf("threeCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2, *CB1S_3), RooArgList(*frac1_1, *frac1_2));
	  threeCB2S = new RooAddPdf("threeCB2S", "Sum of 2S Crystal ball", RooArgList(*CB2S_1, *CB2S_2, *CB2S_3), RooArgList(*frac1_1, *frac1_2));
	  threeCB3S = new RooAddPdf("threeCB3S", "Sum of 3S Crystal ball", RooArgList(*CB3S_1, *CB3S_2, *CB3S_3), RooArgList(*frac1_1, *frac1_2));
	};

};
#endif
