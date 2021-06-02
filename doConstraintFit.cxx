#include "fitter.h"
#include "MassYieldFit_BDT_MC.C"
#include "MassYieldFit_data.cxx"
#include "./BDT/Get_Optimal_BDT.cxx"

void doConstraintFit(int step = 0){
  std::string type 			= "CB2:EE:FF"	;
  std::string constraints		="alpha:n:frac"	;
  long ts				= 1622626134;	//1621574976;	//	1622517421;
  double ptMin				= 0		;
  double ptMax				= 6		;
  double rapMin				= -2.4		;
  double rapMax				= 2.4		;
  TString MupT				= "3p5"		;
  std::string Trig			= "S13"		;
  int state				= 3		;
  bool fixvar				= false		;
  bool swflag				= false		;
  int cBinLow				= 0		;
  int cBinHigh				= 180 		;
  double cutQVP				= 0.00		;
  bool isBDT 				= true		;
  double cutBDTlow			= -1.0		;
  double cutBDThigh			= 1.0		;
  const std::string fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());

/*



*/
        cutBDTlow = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP ).first;
        MassYieldFit_BDT_MC(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
        TFile* file_MCres_input = new TFile(Form("%s/Yield/Yield_%dS_pt_%d-%d_rap_%d-%d_noWeight_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root",workdir.Data(), (int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, cutQVP,(int) fixvar), "READ");
      
        RooFitResult* result_MC = (RooFitResult*) file_MCres_input->Get("fitresult_model_reducedDS");
        auto list_fit_final = result_MC->floatParsFinal();
        auto list_var_toConst = parser_symbol(constraints);
        std::map< std::string,std::pair< double, double> > map_keyval;
        std::string opt_params_gc;
        for (auto keys : list_var_toConst){
          RooRealVar* _var = (RooRealVar*) list_fit_final.find(keys.c_str());
          map_keyval[keys.c_str()] = {_var->getVal(), _var->getError()};
          opt_params_gc+=Form(":%s;%.6f",keys.c_str(), _var->getVal());
        }
        type = type+opt_params_gc; 
        double sigma3S= 0.2; // list_fit_final.find("sigma3S_1")
      //  Double_t params[] = {};
      //  Double_t params_low[];
      //  Double_t params_high[];

        //MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.2,0.1,0.1,0.1}, (Double_t[]) {0.11, 1.0, 1.0, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.21, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 0.1, 0.1, 0.3,0.3});
        MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 7.2,5.1,1.1,0.1}, (Double_t[]) {0.11, 1.0, 1.0, 0.05, 5.3, 1.3, 0.3,-0.3}, (Double_t[]) {0.21, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 9.6, 10.1, 4.3,0.3});

  std::vector<std::pair<int, int> > cBinPair = { {0,40}, {40, 100}, {100,180}, {0, 180} };
  std::vector<std::pair<double, double> > ptPair = { {0, 6}, {6, 30}, {0, 30}};
  std::vector<std::pair<double, double> > rapPair = { {-2.4, 2.4}, {-1.2, 1.2} };
  for( auto rp : rapPair ) {
    for( auto pp : ptPair ) {
      for( auto cp : cBinPair ){
	rapMin		= rp.first;
	rapMax		= rp.second;
	ptMin		= pp.first;
	ptMax		= pp.second;
	cBinLow		= cp.first;
	cBinHigh	= cp.second;

      }
    }
  }



}
