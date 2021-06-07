#include "fitter.h"
#include "MassYieldFit_BDT_MC.C"
#include "MassYieldFit_data.cxx"
#include "./BDT/Get_Optimal_BDT.cxx"

void doDatadrivenFit(int step = 0){
  std::string type 			= Form("CB2:CC2:FFDD%d",step)	;
  std::string constraints		="alpha:n:frac"	;
  long ts				= 1621574976;//	1622626134;//	//	1622517421;
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
//	cutBDTlow = -0.3;
	std::cout << Form("pT : [ %.1f, %.1f ], y : [ %.1f, %.1f ], cBin [ %d, %d ], Optimal BDT Score : %.3f", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutBDTlow) << std::endl;
        TFile* file_input_iterstep ;
	RooFitResult* result_prevstep;	
	if(step >0 )
	{
//	  auto fitdir = parser_symbol(type)[2].substr(0,4);
//	  std::string name_fitmodel = Form("_%s",parser_symbol(type)[1].c_str());
//	  int ylim10 = rapMax*10;
//          std::string name_file_output = Form("%s/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f_DDiter%d.root" ,workdir.Data(), ts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, 70, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, cutQVP, step-1);
//      	  file_input_iterstep = TFile::Open(name_file_output.c_str());
//   	  result_prevstep  = (RooFitResult*) file_input_iterstep->Get("fitresult_model_reducedDS");
//          std::map< std::string,std::pair< double, double> > map_keyval;
//          std::string opt_params_gc;
//          for (auto keys : list_var_toConst){
//            RooRealVar* _var = (RooRealVar*) list_fit_final.find(keys.c_str());
//            map_keyval[keys.c_str()] = {_var->getVal(), _var->getError()};
//          }
//    	  auto list_fit_final = result_prevstep->floatParsFinal();
//          double sigma3S= 0.2; // list_fit_final.find("sigma3S_1")
      //  Double_t params[] = {};
      //  Double_t params_low[];
      //  Double_t params_high[];
//         MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.2,0.1,0.1,0.1}, (Double_t[]) {0.11, 1.0, 1.0, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.21, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 0.1, 0.1, 0.3,0.3});
//	  MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.1218, 1.53, 7.9,0.804, 0.2,0.1,0.1,0.1}, (Double_t[]) {0.11, 1.0, 0.7, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.21, 4.0, 15.0, 0.95, 0.1, 0.1, 0.3,0.3}); // FOR 0-30 GeV PT!!!!!!!!!!!!!!!!
//	  MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.113, 1.29, 9.0,0.945, 0.0,-0.1,0.1,0.1}, (Double_t[]) {0.05, 1.0, 0.7, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.21, 4.0, 10.0, 0.99, 0.1, 0.1, 0.3,0.3}); // FOR 0-6 GeV PT!!!!!!!!!!!!!!!!
	  MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.1194, 1.2, 19.87,0.944, 0.0,-0.1,0.1,0.1}, (Double_t[]) {0.05, 1.0, 19.5, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.31, 9.0, 20.5, 0.95, 0.1, 0.1, 0.3,0.3}); // FOR 6-30 GeV PT!!!!!!!!!!!!!!!!
        }

        if(step == 0)
	{
	  MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, 3.5, 3.0,0.53, 0.0,-0.1,0.1,0.1}, (Double_t[]) {0.03, 0.7, 0.7, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.41, 2.0, 20.0, 0.95, 0.1, 0.1, 0.3,0.3});
	}

//  TFile* x = new TFile("./BDT/test_OPT_BDT_method2.root","recreate");
//  x->Write();
//  x->Close();
  std::vector<std::pair<int, int> > cBinPair =  { {0,40}, {40, 100}, {100,180}, {0, 180} };
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
