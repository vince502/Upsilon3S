//#include "./BDT/bininfo.h"
//#include "MassYieldFit_BDT_MC.C"
//#include "MassYieldFit_BDT_MC_GE.C"
#include "MassYieldFit_BDT_MC_CB3.C"
//#include "MassYieldFit_BDT_MC.C"
#include "MassYieldFit_data.cxx"
#include "./BDT/yield_eff_signif.cxx"
#include "script_tools.h"

void doConstraintFit_NOM_combv2(int step = 0){
  std::string type 			= "CB3:CC3:GC"	;
  std::string type2 			= "CB3:CC4:DR2FF"	;
  std::string type_r 			= "CB3:CC4:DRGC"	;
  std::string typenobdt 		= "CB3:CC4:FF"	;
  std::string constraints		="alpha:n:frac:frac2:xNS:xNS_2:sigmaNS_1"	;
  std::string fixvars			="alpha:n:frac:frac2:x1S:x1S_2:sigma1S_1"	;
  long ts						= 10000000016	; 
  long ts_2						= 10000000016	;
  double ptMin					= 0		;
  double ptMax					= 30 		;
  int bdtptMin					= 0		;
  int bdtptMax					= 30 		;
  double rapMin					= -2.4		;
  double rapMax					= 2.4		;
  TString MupT					= "3p5"		;
  std::string Trig				= "S13"		;
  int train_state				= 3		;
  int state						= 3		;
  bool fixvar					= false		;
  bool swflag					= false		;
  int cBinLow					= 0		;
  int cBinHigh					= 181 		;
  double cutQVP					= 0.00		;
  bool isBDT 					= true		;
  double cutBDTlow				= 0.0859	;
  double cutBDThigh				= 1.0		;
  RooRealVar sb_ratio					;
  double drawonly					= 0;
   std::string fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
   std::string fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
   std::string fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
   std::pair<double, double> fitrange = {8, 14};
   int Nworkers 			= 30;
   string plot_dir_opt		= "";
   std::vector<Double_t> bkg_val ;
   std::vector<Double_t> bkg_low ;
   std::vector<Double_t> bkg_high;

//////////////////////////////////////////STEP : BDT VALUE DECISION/////////////////////////////////////////
auto prep_bdtval = [&] (double blow_ref = -0.3, int _step =0, bool redo_nobdt =false) mutable {
  double cutQVP_noBDT= 0.01;
  std::string fname;
  if(state ==1) fname = fname1S;
  if(state ==2) fname = fname2S;
  if(state ==3) fname = fname3S;
  std::cout << "[doConst] fname : " << fname.c_str() << std::endl;
  if(_step >=3 || _step == -103 || _step == -1031|| _step == -51){
	string query_file = GetFit(10, true, "CB3", ts, train_state, state, (int) ptMin, (int) ptMax, cBinLow, cBinHigh, -1, 1, bdtptMin, bdtptMax, cutQVP_noBDT,"" ); 
	std::cout <<"[doConstFit] No BDT file : "<< query_file.c_str() << std::endl;
	if(_step == -1031 || !checkFile(query_file) || redo_nobdt){
		std::cout << "Cannot find fitted data!" << std::endl;   MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP_noBDT, -1, cutBDThigh, bdtptMin, bdtptMax,plot_dir_opt);
	}
}
  dbg();
  if(_step >=2|| _step == -102 || _step == -52){
//    MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, blow_ref, cutBDThigh, bdtptMin, bdtptMax,plot_dir_opt);
}

      auto fit_mc_dat = [&] (string type_, double bl){
	  long kts = ts;
	  double app_cutQVP = cutQVP;
	  if(bl == -1.0000){ kts = 9999999999; app_cutQVP = cutQVP_noBDT; }
	  std::string mcres_input = GetFit(__FITRESLATEST, true, "CB3",kts, train_state, state, (int)ptMin, (int)ptMax, cBinLow, cBinHigh, bl, cutBDThigh, bdtptMin, bdtptMax, app_cutQVP, "");
	  TFile* file_MCres_input = TFile::Open(mcres_input.c_str());
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
      type_ = type_+opt_params_gc; 
      std::cout << type_ << std::endl;

       double mean_sigma1S1;
       if(state ==3) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U3S_mass);
       if(state ==2) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U2S_mass);
       if(state ==1) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U1S_mass);
      auto parsed = parser_symbol(type_,":");
      if(parsed[2].find("FF") ==std::string::npos){
      MassYieldFit_data(type_, train_state, state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, app_cutQVP, isBDT, ts, bl, cutBDThigh, bdtptMin, bdtptMax, 
	  (std::vector<Double_t>) { -0.02,0.0,0.1,0.1, -0.1},
	  (std::vector<Double_t>) {-0.5, -0.5, -0.5,-0.5, -0.5}, 
	  (std::vector<Double_t>) {0.5, 0.5, 0.5,0.5, 0.5}, 
      (std::map<string, params_vhl>) {
      {"massCut", { 0,8,14 }}, 
      {"mass_range", { 0,8,14 }}, 
	  {"sigma1S1", {mean_sigma1S1, 0.03, 0.41}}, 
	  {"alpha", {map_keyval["alpha"].first, 0.5, (map_keyval["alpha"].first+map_keyval["alpha"].second)}},
	  {"var_n", {map_keyval["n"].first, 0.4, (map_keyval["n"].first+map_keyval["n"].second)*4}},
	  {"frac", {map_keyval["frac"].first, 0.01, 0.99}},
	  {"frac2", {map_keyval["frac2"].first, 0.01, 0.99} }, 
      {"xNS", {map_keyval["xNS"].first,0.01,0.99}}, 
      {"xNS_2", {map_keyval["xNS_2"].first,0.01,0.99}},
      {"sigmaNS_1", { mean_sigma1S1,0.01,0.99}},
      {"mag", { 0, 0, 0 }},
      {"sb_ratio", { -1, 0, 0}},
      }, Nworkers, plot_dir_opt);
      }
      if(parsed[2].find("FF") !=std::string::npos){
      MassYieldFit_data(type_, train_state, state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, app_cutQVP, isBDT, ts, bl, cutBDThigh,  bdtptMin, bdtptMax, 
	  (std::vector<Double_t>) { -0.22,-0.05,0.05,-0.1, -0.1},
	  (std::vector<Double_t>) {-0.5, -0.5, -0.5,-0.5, -0.5}, 
	  (std::vector<Double_t>) {0.5, 0.5, 0.5,0.5, 0.5}, 
      (std::map<string, params_vhl>) {
      {"massCut", { 0,8,14 }}, 
      {"mass_range", { 0,8,14 }}, 
	  {"sigma1S1", {mean_sigma1S1, 0.11, -1}},
	  {"alpha", {map_keyval["alpha"].first,0, -1}},
	  {"var_n", {map_keyval["n"].first, 0.4, -1}},
	  {"frac", {map_keyval["frac"].first, 0.01, -1}},
      {"frac2", {map_keyval["frac2"].first, 0, -1} }, 
      {"xNS", {map_keyval["xNS"].first,0,-1}}, 
      {"xNS_2", {map_keyval["xNS_2"].first,0,-1}},
      {"sigmaNS_1", { mean_sigma1S1,0,-1}},
      {"mag", { 0, 0, 0 }},
      {"sb_ratio", { -1, 0, 0}},
      }, Nworkers, plot_dir_opt);
      }
    };
  if(_step >=1|| _step == -101 || _step == -1011 || _step == -51){
	string query_file2 = GetFit(__FITRESLATEST, false, "CB3:CC4:FF", ts, train_state, state, (int) ptMin, (int) ptMax, cBinLow, cBinHigh, -1, 1, bdtptMin, bdtptMax, cutQVP_noBDT,"" ); 
	if( _step == -1011 || !checkFile(query_file2)){
		fit_mc_dat(typenobdt, -1);
	}
  }
  if(_step >=0|| _step == -100 || _step == -52){
//    fit_mc_dat(type_r, blow_ref);
  }
  dbg();
  double res_blow;
  std::pair<double, TGraph*> res_GOB;
  RooRealVar sb_ratio;
  dbg(100);
    if( _step > -10 ){
  dbg(100);
    sb_ratio = get_eff_acc_v2(type_r, ts, rapMax, ptMin, ptMax, cBinLow, cBinHigh, blow_ref, 1.0, bdtptMin, bdtptMax, train_state, 1, state, false);
	std::cout << "sb_ratio: " << sb_ratio.getVal() << std::endl;
   res_GOB = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP , sb_ratio.getVal(), train_state, state, bdtptMin, bdtptMax, "", "S2");
  dbg();
    res_blow= res_GOB.first;
    }
    else{ res_blow = -1; sb_ratio = RooRealVar("d", "", 0); res_GOB = std::make_pair(0, nullptr); }


   if(_step <=-9999){
   auto h1 = res_GOB.second;
   auto list_func = (TList*) h1->GetListOfFunctions();
   std::cout << "THe FUNCTIONS " <<std::endl;
   std::cout << h1->GetName() << std::endl;
   std::cout << h1->GetFunction("Msignif")->GetName() << std::endl;
   
   TCanvas* cx =new TCanvas();
   cx->cd();
   h1->Draw();
   }
   std::cout <<"[INFO] " <<res_blow << " is the determined BDT \n\n\n" << std::endl;
   return std::make_pair(res_blow,sb_ratio);

};

//////////////////////////////////////////STEP : GAUS CONSTRAIN FITTING/////////////////////////////////////////
  auto METHOD_MCGCDATA = [&](int mode = 1) mutable {
  std::cout << "cutBDTlow, sb_ratio in functoin : " << cutBDTlow << ", " << sb_ratio.getVal() << std::endl;
    std::string fname;
    if(state ==1) fname = fname1S;
    if(state ==2) fname = fname2S;
    if(state ==3) fname = fname3S;
	std::cout << Form("%ld,%.4f, %.4f, %d, %d, %d, %d, %.4f, %.4f, %d, %d", ts, ptMin, ptMax, cBinLow, cBinHigh, train_state, state, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax) << std::endl;
    if(mode ==1 || mode ==0){
       MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax,plot_dir_opt);
    }

    if(mode ==1 || mode ==2){
	  std::string mcres_input = GetFit(__FITRESLATEST, true, "CB3",ts, train_state, (int) state, (int)ptMin, (int)ptMax, cBinLow, cBinHigh, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, "");
	  std::cout << mcres_input << std::endl;

	  TFile* file_MCres_input = TFile::Open(mcres_input.c_str() );
   
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

       double mean_sigma1S1;
       if(state ==3) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U3S_mass);
       if(state ==2) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U2S_mass);
       if(state ==1) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U1S_mass);
      MassYieldFit_data(type, train_state, state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax,  
	  bkg_val, bkg_low, bkg_high,
      (std::map<string, params_vhl>) {
      {"massCut", { 0,fitrange.first,fitrange.second }},
	  {"sigma1S1", {mean_sigma1S1, 0.03, 0.41}}, 
	  {"alpha", {map_keyval["alpha"].first, 1.0, (map_keyval["alpha"].first+map_keyval["alpha"].second)}},
	  {"var_n", {map_keyval["n"].first, 0.6, (map_keyval["n"].first+map_keyval["n"].second)*4}},
	  {"frac", {map_keyval["frac"].first, 0.01, 0.99}},
      {"frac2", {map_keyval["frac2"].first, 0, 1} }, 
      {"xNS", {map_keyval["xNS"].first,0.01,2}}, 
      {"xNS_2", {map_keyval["xNS_2"].first,0.01,2}},
      {"sigmaNS_1", { mean_sigma1S1,0,1}},
      {"mag", { 0, 0, 0 }},
      {"sb_ratio", { sb_ratio.getVal(), 0, 0}},
      {"tmp", {0,0,0}},
	  {"DrawOnly", {drawonly, 0, 0}},
      }, Nworkers, plot_dir_opt);
    }

};
/////////////////////////////////////////////STEP : FREEFIT////////////////////////////////////////
  auto METHOD_FREEFIT = [&](string typef = "CB3:CC5:FF") mutable {
  std::cout << "cutBDTlow, sb_ratio in functoin : " << cutBDTlow << ", " << sb_ratio.getVal() << std::endl;
       MassYieldFit_data(typef, train_state, -1, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax,  
	  (std::vector<Double_t>) {8, 5,0.4,-0.01, -0.03},
	  (std::vector<Double_t>) { 5, 0, 0,-0.55, -0.2}, 
	  (std::vector<Double_t>) {10, 10,2,0.45, 0.2}, 
//	  (std::vector<Double_t>) {0.09,-0.07,0.03,-0.01, -0.03},
//	  (std::vector<Double_t>) { -0.5, -0.5, -0.4,-0.55, -0.2}, 
//	  (std::vector<Double_t>) {0.50, 0.50, 0.5,0.45, 0.2}, 
      (std::map<string, params_vhl>) {
      {"massCut", { 0,fitrange.first,fitrange.second }},
      {"mass_range", { 0,fitrange.first,fitrange.second }},
	  {"sigma1S1", {0.16, 0.11, 0.41}}, 
	  {"alpha", {1.8, 1.1, 3.0}},
	  {"var_n", {1.5, 1.1, 2.0}},
	  {"frac", {0.5, 0.01, 0.99}},
      {"frac2", {0.3, 0.01, 0.99} }, 
      {"xNS", {0.3,0.01,1}}, 
      {"xNS_2", {0.56,0.01,1}},
      {"sigmaNS_1", { 0.16,0,1}},
      {"mag", { 1, 0, 0 }},
      {"sb_ratio", { -1, 0, 0}},
      {"tmp", {0,0,0} },
	  {"signal_separate", {0,0,0}},
	  {"DrawOnly", {drawonly, 0, 0}},
      }, Nworkers, plot_dir_opt);
};

//////////////////////////////////////////STEP : FREE FITTING CENTRALITY/////////////////////////////////////////
auto fixfit = [&](double cBinBDTcut) mutable {
	if (!isBDT) {
	  cutBDTlow =0;
	  cutBDThigh=0;
	}
	SetStyle();
       //////////////////////////////////////////////////////////////////
//       std::string name_file_data = Form("%s/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f.root" ,workdir.Data(), train_state, ts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP );
	  std::string name_file_data = GetFit(__FITRESLATEST, false, "CB3:EE:GC",ts, train_state, (int) state, 0, 30, 0, 181, cutBDTlow, cutBDThigh, 0, 30, cutQVP, "");
	std::cout << name_file_data << std::endl;
	TFile* file_DATAres_input = new TFile(name_file_data.c_str(), "OPEN");
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
	long xts = ts;
	MassYieldFit_data(type2, train_state, state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, xts, cBinBDTcut, cutBDThigh,  bdtptMin, bdtptMax,
	bkg_val, bkg_low, bkg_high,
	(std::map<string, params_vhl>) {
	{"massCut", { 0,fitrange.first,fitrange.second }},
	{"sigma1S1", {map_keyval_2["sigma1S_1"].first, 0.11, -1}}, 
	{"alpha", {map_keyval_2["alpha"].first, 1.0, -1}},
	{"var_n", {map_keyval_2["n"].first, 1.0, -1}},
	{"frac", {map_keyval_2["frac"].first, 0.01, -1}},
	{"massCut", { 0,8,11.5 }},
	{"frac2", {map_keyval_2["frac2"].first, 0, -1} }, 
	{"xNS", {map_keyval_2["x1S"].first,0,-1}}, 
	{"xNS_2", {map_keyval_2["x1S_2"].first,0,-1}},
	{"sigmaNS_1", { map_keyval_2["sigma1S_1"].first,0,-1}},
	{"mag", { 0, 0, 0 }},
	{"sb_ratio", { sb_ratio.getVal(), 0, 0}},
	}, Nworkers, plot_dir_opt);
};
  //##########################################EXECUTION CODE#########################################//
  int GLOBAL_NWORKERS= 40 ;
  plot_dir_opt = "Nom_changed_signif_v8";

//Step1, First reference integrated bin fit.
double INTBIN_BDTLOW = 0.1825;// =0.16;
train_state = 3;
state =3;
 //Sealed
 if(step == 1 || step == 99 || step == 11 || step == 111){
//    bkg_val  = {7.0, 4.0, 1.5,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
//    bkg_low  = {5.0, 2.0, 0.2,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
//    bkg_high = {8.5, 9.0, 3.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

  for( auto ptpair : (std::vector<std::pair<std::pair<double, double>, std::pair<double, double> > >) {
//  {{0,30},{0,30}},
//  {{0,4}, {0,4}},
//  {{4,9},{4,9}},
  {{9,15 },{9,15}} ,
//  {{15,30},{15,30}}
  }){ 

    bkg_val  = {-0.4, 0.000, 0.002,  -0.001, -0.03, 0.0, 0.0, 0.0, 0.0};
    bkg_low  = {-0.5, -0.02, -0.10,  -0.6, -0.5, -0.5, -0.5, -0.5, -0.5};
    bkg_high = {0.1, 0.02, 0.10, 0.6, 0.6, 0.5, 0.5, 0.5, 0.5};
    ptMin = ptpair.first.first;
    ptMax = ptpair.first.second;
	bdtptMin = ptpair.second.first;
	bdtptMax = ptpair.second.second;
    std::pair<double, RooRealVar> res = prep_bdtval(0.2,5);
    cutBDTlow = res.first;
    sb_ratio = res.second;
	bool fitdata = true;
	drawonly = 0;
	if(fitdata){
		Nworkers = GLOBAL_NWORKERS;
	    if(ptpair.first.first == 0 && ptpair.first.second == 30){ INTBIN_BDTLOW = res.first; }
	    std::cout << "cutBDTlow, sb_ratio: " << cutBDTlow << ", "<< sb_ratio.getVal() << std::endl;
//	    type 			= "CB3:CC1:GC"	;
//	    METHOD_MCGCDATA(1);
//	    type 			= "CB3:CC2:GC"	;
//	    METHOD_MCGCDATA(2);
//	    type 			= "CB3:CC3:GC"	;
//	    METHOD_MCGCDATA(2);
//	    type 			= "CB3:CC4:GC"	;
//	    METHOD_MCGCDATA(2);
//	    type 			= "CB3:CC5:GC"	;
//	    METHOD_MCGCDATA(2);
//	    type 			= "CB3:CC6:GC"	;
//	    METHOD_MCGCDATA(2);
	    type 			= "CB3:EE:GC"	;
	    bkg_val  = {6.5, 7.0, 2.5,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	    bkg_low  = {2.0, 2.0, 0.11,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
	    bkg_high = {118.5, 25.0, 9.2, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
//	    METHOD_MCGCDATA(2);
		if(ptpair.first.first>= 9){
		    bkg_val  = {-0.1, 4.0, 1.5,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		    bkg_low  = {-2.0, 2.0, 0.2,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
		    bkg_high = {0.0 , 20.0, 3.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
		    type 			= "CB3:EX:GC"	;
		    METHOD_MCGCDATA(2);
		}
	}
  	}
}

if(step == 1 || step == 99 || step == 12 || step == 112){
ptMin = 0;
ptMax = 30;
bdtptMin = 0;
bdtptMax = 30;
cutBDTlow = Get_BDT(ts, train_state, state, bdtptMin, bdtptMax, (int) ptMin, (int) ptMax, 0, 181); 
for( auto cbinpair : (std::vector<std::pair<int, int> >) {
//{0,20}, 
//{0,40}, 
{0,60}, 
//{40,80}, 
//{20,40},
//{40, 60},
//{40, 100},
//{60, 80}, 
//{60, 100}, 
//{80, 100},
//{80, 120},
//{100, 140},
//{140, 181}, 
//{120, 181} 
}){ 
    bkg_val  = {-0.4, -0.07, 0.03,  -0.001, -0.03, 0.0, 0.0, 0.0, 0.0};
    bkg_low  = {-0.8, -0.6, -0.6,  -0.6, -0.5, -0.5, -0.5, -0.5, -0.5};
    bkg_high = {0.6, 0.6, 0.6, 0.6, 0.6, 0.5, 0.5, 0.5, 0.5};
	cBinLow  = cbinpair.first;
	cBinHigh = cbinpair.second;
//	if(!(cBinLow == 140 && cBinHigh == 181 ) ) continue;
    std::pair<double, RooRealVar> res = prep_bdtval(0.0,5);
    double CBINBDTLOW = res.first;
	sb_ratio = res.second;

	bool fitdata = 1;
	bool fit_aux = false;
	if(fitdata){
		Nworkers = GLOBAL_NWORKERS;
	    type2			= "CB3:CC1:FF"	;
//		fixfit(CBINBDTLOW);
//	    type2			= "CB3:CC2:FF"	;
//		fixfit(CBINBDTLOW);
//	    type2			= "CB3:CC3:FF"	;
//		fixfit(CBINBDTLOW);
//	    type2			= "CB3:CC4:FF"	;
//		fixfit(CBINBDTLOW);
//	    type2			= "CB3:CC5:FF"	;
//		fixfit(CBINBDTLOW);
//	    type2			= "CB3:CC6:FF"	;
//		fixfit(CBINBDTLOW);
	    type2			= "CB3:EE:FF"	;
	    bkg_val  = {8.5, 5.01, 4.111,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	    bkg_low  = {7.0, 1.1, 0.1,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
	    bkg_high = {9.6, 9.0, 9.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
		fixfit(CBINBDTLOW);
		if(fit_aux){
		    bkg_val  = {-1.1, 4.0, 1.5,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		    bkg_low  = {-10.0, 2.0, 0.2,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
		    bkg_high = {0.1 , 20.0, 3.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
		    type2			= "CB3:EX:FF"	;
			fixfit(CBINBDTLOW);
		}
	}
  	}
}

train_state = 3;
state =2;
cBinLow = 0;
cBinHigh = 181;
 //Sealed
 if(step == 2 || step == 99 || step == 11 || step == 222){
//    bkg_val  = {7.0, 4.0, 1.5,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
//    bkg_low  = {5.0, 2.0, 0.2,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
//    bkg_high = {8.5, 9.0, 3.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};

  for( auto ptpair : (std::vector<std::pair<std::pair<double, double>, std::pair<double, double> > >) { 
  {{0,30},{0,30}},
  {{0,3},{0,3}}, 
  {{3,6},{3,6}},
  {{6,9},{6,9}},
  {{9,15},{9,15}},
  {{15,30},{15,30}}
  }){ 
    bkg_val  = {-0.4, -0.07, 0.03,  -0.001, -0.03, 0.0, 0.0, 0.0, 0.0};
    bkg_low  = {-0.8, -0.6, -0.6,  -0.6, -0.5, -0.5, -0.5, -0.5, -0.5};
    bkg_high = {0.6, 0.6, 0.6, 0.6, 0.6, 0.5, 0.5, 0.5, 0.5};
    ptMin = ptpair.first.first;
    ptMax = ptpair.first.second;
	bdtptMin = ptpair.second.first;
	bdtptMax = ptpair.second.second;
    std::pair<double, RooRealVar> res = prep_bdtval(0.2,5);
    cutBDTlow = res.first;
    sb_ratio = res.second;
	bool fitdata =true;
	if(fitdata){
		Nworkers = GLOBAL_NWORKERS;
	    std::cout << "cutBDTlow, sb_ratio: " << cutBDTlow << ", "<< sb_ratio.getVal() << std::endl;
	    type 			= "CB3:CC1:GC"	;
	    METHOD_MCGCDATA(1);
	    type 			= "CB3:CC2:GC"	;
	    METHOD_MCGCDATA(2);
	    type 			= "CB3:CC3:GC"	;
	    METHOD_MCGCDATA(2);
	    type 			= "CB3:CC4:GC"	;
	    METHOD_MCGCDATA(2);
	    type 			= "CB3:CC5:GC"	;
	    METHOD_MCGCDATA(2);
	    type 			= "CB3:CC6:GC"	;
	    METHOD_MCGCDATA(2);
	    type 			= "CB3:EE:GC"	;
	    bkg_val  = {7.0, 5.5, 6.4,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	    bkg_low  = {1.0, 2.1, 0.21,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
	    bkg_high = {8.1, 11.0, 12.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
	    METHOD_MCGCDATA(2);
		if(ptpair.first.first>= 3){
		    bkg_val  = {-1.1, 4.0, 0.5,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		    bkg_low  = {-10.0, 2.0, 0.002,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
		    bkg_high = {0.1 , 20.0, 3.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
		    type 			= "CB3:EX:GC"	;
//		    METHOD_MCGCDATA(2);
		}
	}
  	}
}

if(step == 2 || step == 99 || step == 12 || step == 221){
ptMin = 0;
ptMax = 30;
bdtptMin = 0;
bdtptMax = 30;
cutBDTlow = Get_BDT(ts, train_state, state, bdtptMin, bdtptMax, (int) ptMin, (int) ptMax, 0, 181); 
for( auto cbinpair : (std::vector<std::pair<int, int> >) {
//{0, 10}, 
//{10, 20}, 
//{0, 20}, 
//{20, 40},
//{40, 60},
//{60, 80},
//{80, 100},
//{100, 120},
//{120, 140},
//{140, 181},
{140, 160},
{160, 181},
/*{140, 160},
{160, 181} -> too small stats*/
}){
    bkg_val  = {-0.4, -0.07, 0.03,  -0.001, -0.03, 0.0, 0.0, 0.0, 0.0};
    bkg_low  = {-0.8, -0.6, -0.6,  -0.6, -0.5, -0.5, -0.5, -0.5, -0.5};
    bkg_high = {0.6, 0.6, 0.6, 0.6, 0.6, 0.5, 0.5, 0.5, 0.5};
	cBinLow  = cbinpair.first;
	cBinHigh = cbinpair.second;
    std::pair<double, RooRealVar> res = prep_bdtval(0.0,5);
    double CBINBDTLOW = res.first;
	sb_ratio = res.second;
	bool fitdata = 1;
	bool fit_aux = 0;
	if(fitdata){
		Nworkers = GLOBAL_NWORKERS;
	    type2			= "CB3:CC1:FF"	;
		fixfit(CBINBDTLOW);
	    type2			= "CB3:CC2:FF"	;
		fixfit(CBINBDTLOW);
	    type2			= "CB3:CC3:FF"	;
		fixfit(CBINBDTLOW);
	    type2			= "CB3:CC4:FF"	;
		fixfit(CBINBDTLOW);
	    type2			= "CB3:CC5:FF"	;
		fixfit(CBINBDTLOW);
	    type2			= "CB3:CC6:FF"	;
		fixfit(CBINBDTLOW);
	    type2			= "CB3:EE:FF"	;
	    bkg_val  = {7.1, 8.01, 5.111,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	    bkg_low  = {3.0, 2.1, 0.01,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
	    bkg_high = {18.7, 20.1, 9.1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
		fixfit(CBINBDTLOW);
		if(fit_aux){
		    bkg_val  = {-1.1, 4.0, 1.5,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		    bkg_low  = {-10.0, 2.0, 0.2,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
		    bkg_high = {0.1 , 20.0, 3.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
		    type2			= "CB3:EX:FF"	;
			fixfit(CBINBDTLOW);
		}
	}
  	}
}

// if( step == 1311){
//  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30}/*, {0, 6}, {6, 30}*/}){ 
////	ts = 9999999999;// 1635252097;// 1635139612;
//	ts = input_ts;
//	train_state =aux_train_state;
//	state = aux_train_state;
//	std::cout << ts << ", " << train_state << std::endl;
//	sb_ratio.setVal(-1);
//	fitrange= {8, 14};
//	sb_ratio.setVal(-1);
//	Nworkers = 20;
//    fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
//    fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
//    fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
//    ptMin = ptpair.first;
//    ptMax = ptpair.second;
//    type 			= "CB3:CC3:GC"	;
////    std::pair<double, RooRealVar> res = prep_bdtval(-0.0, -1);
////	for(double xj : {0.9, 0.8, 0.6, 0.1,-0.2}/*}*/){
////	for(double xj : {0.0, 0.1, 0.2,0.25,0.3,0.35,0.4,0.6, 0.8}/*}*/){
//	for(double xj : VALI_V3_BDTTESTCUT/*}*/){
////	for(double xj : {0.1, -0.1 } ){
//    	cutBDTlow = xj;
//    	type 			= "CB3:CC5:GC"	;
////		if(xj < -0.2) type = "CB3:CC4:GC";
//
//    	METHOD_MCGCDATA(1);
////    	METHOD_FREEFIT("CB3:EE:FF");
//	}
//  }
//}
// if( step == 1312){
//  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30}/*, {0, 6}, {6, 30}*/}){ 
////	ts = 9999999999;// 1635252097;// 1635139612;
//	ts = input_ts;
//	train_state =aux_train_state;
//	state = aux_train_state;
//	std::cout << ts << ", " << train_state << std::endl;
//	sb_ratio.setVal(-1);
//	fitrange= {8, 14};
//	sb_ratio.setVal(-1);
//    fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
//    fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
//    fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
//    ptMin = ptpair.first;
//    ptMax = ptpair.second;
//    type 			= "CB3:CC3:GC"	;
////    std::pair<double, RooRealVar> res = prep_bdtval(-0.0, -1);
////	for(double xj : VALI_V3_BDTTESTCUT3/*}*/){
//	for(double xj : {0.8 } ){
//    	cutBDTlow = xj;
//    	type 			= "CB3:CC5:FF"	;
////		if(xj < -0.2) type = "CB3:CC4:GC";
//
//    	METHOD_MCGCDATA(2);
////    	METHOD_FREEFIT("CB3:EE:FF");
//	}
//  }
//}

}



#if defined __CLING__
#endif
