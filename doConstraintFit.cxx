#include "./BDT/bininfo.h"
//#include "MassYieldFit_BDT_MC.C"
//#include "MassYieldFit_BDT_MC_GE.C"
#include "MassYieldFit_BDT_MC_CB3.C"
//#include "MassYieldFit_BDT_MC.C"
#include "MassYieldFit_data.cxx"
//#include "./BDT/GOBC.cxx"

void doConstraintFit(int step = 0){
  std::string type 			= "CB3:EE:FF"	;
  std::string type2 			= "CB3:CC2:FF"	;
  std::string constraints		="alpha:n:frac:frac2:x3S:x3S_2:sigma3S_1"	;
  std::string fixvars			="alpha:n:frac:frac2:x1S:x1S_2:sigma1S_1"	;
  long ts				= 1623391157; //71622626134;//	1621574976;//	//	1622517421;
  double ptMin				= 0		;
  double ptMax				= 30 		;
  double rapMin				= -2.4		;
  double rapMax				= 2.4		;
  TString MupT				= "3p5"		;
  std::string Trig			= "S13"		;
  int state				= 3		;
  bool fixvar				= false		;
  bool swflag				= false		;
  int cBinLow				= 0		;
  int cBinHigh				= 180 		;
  double cutQVP				= 0.01		;
  bool isBDT 				= true		;
  double cutBDTlow			= -1.0		;
  double cutBDThigh			= 1.0		;
  const std::string fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
  const std::string fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_Custom.root", ts, Trig.c_str());
/*
*/
//       cutBDTlow = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP ).first;
//      cutBDTlow = 0.20;
 //      MassYieldFit_BDT_MC_CB3(ts, "", fname3S, 0, 30, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
////       MassYieldFit_BDT_MC(ts, fname1S, "", ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, 1, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
////       MassYieldFit_BDT_MC(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, 3, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
      //new TFile(Form("%s/Yield/Yield_CB3_%dS_pt_%d-%d_rap_%d-%d_noWeight_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root",workdir.Data(), (int) state ,(int)0, (int)30, (int)(rapMin*10), (int)(rapMax*10), MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, cutQVP,(int) fixvar), "READ"); // Depricate this file name
//       MassYieldFit_BDT_MC_CB3(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);

      TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root", ts, (int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, cutQVP,(int) fixvar), "OPEN");

   
      RooFitResult* result_MC = (RooFitResult*) file_MCres_input->Get("fitresult_model_reducedDS");
      std::cout << file_MCres_input->GetName() << std::endl;
      auto list_fit_initial = result_MC->floatParsInit();
      auto list_fit_final = result_MC->floatParsFinal();
      auto list_var_toConst = parser_symbol(constraints);
      std::map< std::string,std::pair< double, double> > map_keyval;
      std::string opt_params_gc;
      for (auto keys : list_var_toConst){
      std::cout << keys << std::endl;
        RooRealVar* _var = (RooRealVar*) list_fit_final.find(keys.c_str());
        map_keyval[keys.c_str()] = {_var->getVal(), _var->getError()};
        opt_params_gc+=Form(":%s;%.6f",keys.c_str(), _var->getError());
      std::cout << keys <<": "<< _var->getVal() << ", "<< _var->getError() << std::endl;
      }
      opt_params_gc+=":GCPEND";
      type = type+opt_params_gc; 
      std::cout << type << std::endl;

       double mean_sigma1S1 =  map_keyval["sigma3S_1"].first*(U1S_mass/U3S_mass);
//      MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.0,0.1,0.1,0.1, -0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3, -0.3}, (Double_t[]) {0.31, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 0.1, 0.1, 0.3,0.3, 0.3}, 
//      MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 5.0,5.1,2.1,0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.31, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 9.1, 10.1, 2.3,0.3}, 
      MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 5.0,5.1,2.1,0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, 5.3, 1.3, 0.3,-0.3}, (Double_t[]) {-1, -1, -1, -1, 9.1, 7.1, 2.3,0.3}, 
       (std::map<string, params_vhl>) {
       {"frac2", {map_keyval["frac2"].first, 0, -1} }, 
       {"x3S", {map_keyval["x3S"].first,0,-1}}, 
       {"x3S_2", {map_keyval["x3S_2"].first,0,-1}},
       {"sigma3S_1", { mean_sigma1S1,0,-1}},
       });

////       MassYieldFit_BDT_MC(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
////       MassYieldFit_BDT_MC_GE(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
//
////       cutBDTlow = 0.15;
//
////        MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, 1, 1, 0.5, 0.0,-0.1,0.1,0.1}, (Double_t[]) {0.11, 1.0, 0.7, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.21, 5, 5, 0.95, 0.1, 0.1, 0.3,0.3});
//        //MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 7.2,5.1,1.1,0.1}, (Double_t[]) {0.11, 1.0, 1.0, 0.05, 5.3, 1.3, 0.3,-0.3}, (Double_t[]) {0.21, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 9.6, 10.1, 4.3,0.3});
/*
  if (!isBDT) {
    cutBDTlow =0;
    cutBDThigh=0;
  }
  int ylim10 = (int) (rapMax*10);
  auto parsed = parser_symbol(type);
  std::string sig_func = parsed[0];
  std::string bkg_func = parsed[1];
  std::string fitdir = parsed[2];
  std::string name_fitmodel = "_"+bkg_func;

  SetStyle();
  Int_t Nmassbins;
  double range_mass_low, range_mass_high;
  if (massrng.find(ts) == massrng.end()){
  range_mass_low = 8;
  range_mass_high = 14;
  Nmassbins = 120;
  if(info_BDT(ts)[0]!="nan"){
    auto _pair_mass = parser_symbol(info_BDT(ts)[1],",");
    range_mass_low = stod(_pair_mass[0]);
    range_mass_high = stod(_pair_mass[1]);
    Nmassbins = (range_mass_high - range_mass_low)/0.05;
  }
  }
  else{
    range_mass_low = massrng[ts].first;
    range_mass_high = massrng[ts].second;
    Nmassbins = (range_mass_high - range_mass_low)/0.05;
  }
       //////////////////////////////////////////////////////////////////
       std::string name_file_data = Form("%s/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f.root" ,workdir.Data(), ts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, cutQVP );
       std::cout << name_file_data << std::endl;
      TFile* file_DATAres_input = new TFile(name_file_data.c_str(), "OPEN");
 std::vector<std::pair<int, int> > cBinPair =	{ {0,40}, {40, 100}, {100,180}}; //{{0,10}, {10,20}, {20,40}, {40,60}, {60,80}, {80,100}, {100,120}, {120, 140}, {140, 180} };	//{ {0,40}, {40, 100}, {100,180}, {0, 180} };
 std::vector<std::pair<double, double> > ptPair = {{0, 30}};	//{ {0, 6}, {6, 30}, {0, 30}};
 std::vector<std::pair<double, double> > rapPair = {{-2.4, 2.4}};	//{ {-2.4, 2.4}, {-1.2, 1.2} };
 for( auto rp : rapPair ) {
   for( auto pp : ptPair ) {
     for( auto cp : cBinPair ){
       rapMin		= rp.first;
       rapMax		= rp.second;
       ptMin		= pp.first;
       ptMax		= pp.second;
       cBinLow		= cp.first;
       cBinHigh	= cp.second;
//       if(( cBinHigh == 180 && cBinLow ==0 && ptMin ==0 && ptMax ==30 && rapMax == 2.4)) continue;

       cutBDTlow = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP ).first;

       //////////////////////////////////////////////////////////////////

      RooFitResult* result_DATA = (RooFitResult*) file_DATAres_input->Get("fitresult_model_gc_reducedDS");
      std::cout << file_DATAres_input->GetName() << std::endl;
      auto list_fit_initial_2 = result_DATA->floatParsInit();
      auto list_fit_final_2 = result_DATA->floatParsFinal();
      auto list_var_forfix = parser_symbol(fixvars);
      std::map< std::string,std::pair< double, double> > map_keyval_2;
      for (auto keys : list_var_forfix){
      std::cout << keys << std::endl;
        RooRealVar* _var = (RooRealVar*) list_fit_final_2.find(keys.c_str());
        map_keyval_2[keys.c_str()] = {_var->getVal(), _var->getError()};
      }

       MassYieldFit_data(type2, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {map_keyval_2["sigma1S_1"].first, map_keyval_2["alpha"].first, map_keyval_2["n"].first, map_keyval_2["frac"].first, -0.15,-0.1,0.1,0.1}, (Double_t[]) {0.05, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {-1, -1, -1, -1, 0.1, 0.1, 0.3,0.3}, 
       (std::map<string, params_vhl>) {
       {"frac2", {map_keyval_2["frac2"].first, 0, -1} }, 
       {"x3S", {map_keyval_2["x1S"].first,0,-1}}, 
       {"x3S_2", {map_keyval_2["x1S_2"].first,0,-1}},
       {"sigma3S_1", { map_keyval_2["sigma1S_1"].first,0,-1}},
       });
     }
   }
 } */

////	DrawHist(parser_symbol(type), ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow , cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, 70);
 
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
