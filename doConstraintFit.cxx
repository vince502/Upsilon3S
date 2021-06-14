#include "./BDT/bininfo.h"
//#include "MassYieldFit_BDT_MC.C"
//#include "MassYieldFit_BDT_MC_GE.C"
#include "MassYieldFit_BDT_MC_CB3.C"
#include "MassYieldFit_data.cxx"

void doConstraintFit(int step = 0){
  std::string type 			= "CB3:CC2:GC"	;
  std::string constraints		="alpha:n:frac:frac2"	;
  long ts				= 1623391157; //71622626134;//	1621574976;//	//	1622517421;
  double ptMin				= 6		;
  double ptMax				= 30		;
  double rapMin				= -2.4		;
  double rapMax				= 2.4		;
  TString MupT				= "3p5"		;
  std::string Trig			= "S13"		;
  int state				= 3		;
  bool fixvar				= false		;
  bool swflag				= false		;
  int cBinLow				= 100		;
  int cBinHigh				= 180 		;
  double cutQVP				= 0.00		;
  bool isBDT 				= true		;
  double cutBDTlow			= -1.0		;
  double cutBDThigh			= 1.0		;
  const std::string fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
/*
*/


//        MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, 1, 1, 0.5, 0.0,-0.1,0.1,0.1}, (Double_t[]) {0.11, 1.0, 0.7, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.21, 5, 5, 0.95, 0.1, 0.1, 0.3,0.3});
        //MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 7.2,5.1,1.1,0.1}, (Double_t[]) {0.11, 1.0, 1.0, 0.05, 5.3, 1.3, 0.3,-0.3}, (Double_t[]) {0.21, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 9.6, 10.1, 4.3,0.3});



//  TFile* x = new TFile("./BDT/test_OPT_BDT_method2.root","recreate");
//  x->Write();
 // x->Close();
 std::vector<std::pair<int, int> > cBinPair =		{ {0,40}, {40, 100}, {100,180}, {0, 180} };
 std::vector<std::pair<double, double> > ptPair =	{ {0, 6}, {6, 30}, {0, 30}};
 std::vector<std::pair<double, double> > rapPair =	{ {-2.4, 2.4}, {-1.2, 1.2} };
 for( auto rp : rapPair ) {
   for( auto pp : ptPair ) {
     for( auto cp : cBinPair ){
       rapMin		= rp.first;
       rapMax		= rp.second;
       ptMin		= pp.first;
       ptMax		= pp.second;
       cBinLow		= cp.first;
       cBinHigh	= cp.second;
       cutBDTlow = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP ).first;
//       MassYieldFit_BDT_MC(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
//       MassYieldFit_BDT_MC_GE(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
//       MassYieldFit_BDT_MC_CB3(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
//       cutBDTlow = 0.15;
       TFile* file_MCres_input = new TFile(Form("%s/Yield/Yield_CB3_%dS_pt_%d-%d_rap_%d-%d_noWeight_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root",workdir.Data(), (int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, cutQVP,(int) fixvar), "READ");
      
       RooFitResult* result_MC = (RooFitResult*) file_MCres_input->Get("fitresult_model_reducedDS");
       auto list_fit_final = result_MC->floatParsFinal();
       auto list_var_toConst = parser_symbol(constraints);
       std::map< std::string,std::pair< double, double> > map_keyval;
       std::string opt_params_gc;
       for (auto keys : list_var_toConst){
       std::cout << keys << std::endl;
         RooRealVar* _var = (RooRealVar*) list_fit_final.find(keys.c_str());
         map_keyval[keys.c_str()] = {_var->getVal(), _var->getError()};
         opt_params_gc+=Form(":%s;%.6f",keys.c_str(), _var->getVal());
       }
       type = type+opt_params_gc; 
       double sigma3S= 0.2; // list_fit_final.find("sigma3S_1")

       MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.2,0.1,0.1,0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.31, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 0.1, 0.1, 0.3,0.3}, (std::map<string, params_vhl>) {{"frac2", {map_keyval["frac2"].first, 0, 1} }});

     std::cout << Form("pT : [ %.1f, %.1f ], y : [ %.1f, %.1f ], cBin [ %d, %d ], Optimal BDT Score : %.3f", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutBDTlow) << std::endl; 

     }
   }
 }
//  std::vector< long > v_ts ={ /*1623391157, 1623349746, 1623349844,i*/  1623349902, 1623349943,  1623349971, 1623349993,  1623350045, 1623350081, 1623350105, 1623350172, 1623350222  }; //};
//  for( const auto ts : v_ts) {
//    	std::cout << "Working on TimeStamp : " << ts << std::endl;
//	std::vector<string> info =  info_BDT(ts);
//	auto ptpair = parser_symbol(info[2],",");
//	auto cBinpair = parser_symbol(info[3], ",");
//	ptMin = stod(ptpair[0]);
//	ptMax = stod(ptpair[1]);
//	cBinLow = stoi(cBinpair[0]);
//	cBinHigh = stoi(cBinpair[1]);
//        cutBDTlow = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP ).first;
//        MassYieldFit_BDT_MC_CB3(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
//        cutBDTlow = 0.15;
//        TFile* file_MCres_input = new TFile(Form("%s/Yield/Yield_CB3_%dS_pt_%d-%d_rap_%d-%d_noWeight_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root",workdir.Data(), (int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, cutQVP,(int) fixvar), "READ");
//      
 //       RooFitResult* result_MC = (RooFitResult*) file_MCres_input->Get("fitresult_model_reducedDS");
 //       auto list_fit_final = result_MC->floatParsFinal();
 //       auto list_var_toConst = parser_symbol(constraints);
 //       std::map< std::string,std::pair< double, double> > map_keyval;
 //       std::string opt_params_gc;
 //       for (auto keys : list_var_toConst){
 //         std::cout << keys << std::endl;
 //         RooRealVar* _var = (RooRealVar*) list_fit_final.find(keys.c_str());
 //         map_keyval[keys.c_str()] = {_var->getVal(), _var->getError()};
 //         opt_params_gc+=Form(":%s;%.6f",keys.c_str(), _var->getVal());
 //       }
 //       type = type+opt_params_gc; 
  //      double sigma3S= 0.2; // list_fit_final.find("sigma3S_1")

 //       MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.2,0.1,0.1,0.1}, (Double_t[]) {0.11, 1.0, 1.0, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.21, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 0.1, 0.1, 0.3,0.3}, (std::map<string, params_vhl>) {{"frac2", {map_keyval["frac2"].first, 0, 1} }});

//	std::cout << Form("pT : [ %.1f, %.1f ], y : [ %.1f, %.1f ], cBin [ %d, %d ], Optimal BDT Score : %.3f", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutBDTlow) << std::endl; 
//          MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, 1, 1, 0.5, 0.0,-0.1,0.1,0.1}, (Double_t[]) {0.11, 1.0, 0.7, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.21, 5, 5, 0.95, 0.1, 0.1, 0.3,0.3});
//	for (double x =0; x<5; x+=1){
//	  cutBDTlow = cutBDTlow + (double) (0.05*x-0.1);
//	}
//  }

}
