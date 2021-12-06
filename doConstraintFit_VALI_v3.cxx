//#include "./BDT/bininfo.h"
//#include "MassYieldFit_BDT_MC.C"
//#include "MassYieldFit_BDT_MC_GE.C"
#include "MassYieldFit_BDT_MC_CB3.C"
//#include "MassYieldFit_BDT_MC.C"
#include "MassYieldFit_data.cxx"
#include "./BDT/yield_eff_signif.cxx"
#include "script_tools.h"

void doConstraintFit_VALI_v3(int step = 0, long input_ts=0, int aux_train_state=0, double aux_BDT_cut = 0){
  std::string type 			= "CB3:CC3:GC"	;
  std::string type2 			= "CB3:CC2:DR2FF"	;
  std::string type_r 			= "CB3:CC2:DRGC"	;
  std::string typenobdt 		= "CB3:CC4:FF"	;
  std::string constraints		="alpha:n:frac:frac2:xNS:xNS_2:sigmaNS_1"	;
  std::string fixvars			="alpha:n:frac:frac2:x1S:x1S_2:sigma1S_1"	;
  long ts				= 1634894212;//1634805675	; 
  long ts_2				= 1634894212;//1634805675	;
  double ptMin				= 0		;
  double ptMax				= 30 		;
  int bdtptMin			= 0		;
  int bdtptMax			= 30 		;
  double rapMin				= -2.4		;
  double rapMax				= 2.4		;
  TString MupT				= "3p5"		;
  std::string Trig			= "S13"		;
  int train_state			= 3		;
  int state				= 3		;
  bool fixvar				= false		;
  bool swflag				= false		;
  int cBinLow				= 0		;
  int cBinHigh				= 181 		;
  double cutQVP				= 0.00		;
  bool isBDT 				= true		;
  double cutBDTlow			= 0.0859	;
  double cutBDThigh			= 1.0		;
  RooRealVar sb_ratio					;
   std::string fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
   std::string fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
   std::string fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
   std::pair<double, double> fitrange = {8, 11.5};
   int Nworkers 			= 30;

//////////////////////////////////////////STEP : BDT VALUE DECISION/////////////////////////////////////////
auto prep_bdtval = [&] (double blow_ref = -0.3, int _step =0) mutable {
  double cutQVP_noBDT= 0.01;
  std::string fname;
  if(state ==1) fname = fname1S;
  if(state ==2) fname = fname2S;
  if(state ==3) fname = fname3S;
  std::cout << "[doConst] fname : " << fname.c_str() << std::endl;
  if(_step >=3 || _step == -103 || _step == -1031|| _step == -51){
//	string str_prefit = Form("%s/Yield/Common/",workdir.Data() );
//	auto query_file =  getfileany(Form("%s/Yield", workdir.Data()), Form("Yield_9999999999_CB3_%dS_train:pt_%d-%d:cBin_%d-%d:BDT_-1.0000-1.0000:MC_0.root", state, (int) ptMin, (int) ptMax, cBinLow, cBinHigh ) );
	string query_file = GetFit(__FITRESLATEST, true, "CB3", ts, train_state, state, (int) ptMin, (int) ptMax, cBinLow, cBinHigh, -1, 1, bdtptMin, bdtptMax, cutQVP_noBDT,"" ); 
	if(_step == -1031 /*|| query_file.empty()*/){
		std::cout << "Cannot find fitted data!" << std::endl;   MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP_noBDT, -1, cutBDThigh, bdtptMin, bdtptMax);
	}
}
  dbg();
  if(_step >=2|| _step == -102 || _step == -52){
    MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, blow_ref, cutBDThigh, bdtptMin, bdtptMax);
}

      auto fit_mc_dat = [&] (string type_, double bl){
	  long kts = ts;
	  double app_cutQVP = cutQVP;
	  if(bl == -1.0000){ kts = 9999999999; app_cutQVP = cutQVP_noBDT; }
	  std::string mcres_input = GetFit(__FITRESLATEST, true, "CB3",kts, train_state, 0, (int)ptMin, (int)ptMax, cBinLow, cBinHigh, bl, cutBDThigh, bdtptMin, bdtptMax, app_cutQVP, "");
//      TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_train%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_%d.root", kts, (int) state ,train_state,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), bl, cutBDThigh, bdtptMin, bdtptMax,cutQVP,(int) fixvar), "OPEN");
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
      MassYieldFit_data(type_, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, app_cutQVP, isBDT, ts, bl, cutBDThigh, bdtptMin, bdtptMax, 
	  (std::vector<Double_t>) { -0.02,0.0,0.1,0.1, -0.1},
	  (std::vector<Double_t>) {-0.4, -0.5, -0.5,-0.3, -0.3}, 
	  (std::vector<Double_t>) {0.1, 0.2, 0.3,0.3, 0.3}, 
      (std::map<string, params_vhl>) {
      {"massCut", { 0,8,14 }}, 
      {"mass_range", { 0,8,14 }}, 
	  {"sigma1S1", {mean_sigma1S1, 0.11, 0.41}}, 
	  {"alpha", {map_keyval["alpha"].first, 0.5, (map_keyval["alpha"].first+map_keyval["alpha"].second)}},
	  {"var_n", {map_keyval["n"].first, 0.4, (map_keyval["n"].first+map_keyval["n"].second)*4}},
	  {"frac", {map_keyval["frac"].first, 0.01, 0.99}},
	  {"frac2", {map_keyval["frac2"].first, 0.01, 0.99} }, 
      {"xNS", {map_keyval["xNS"].first,0.01,0.99}}, 
      {"xNS_2", {map_keyval["xNS_2"].first,0.01,0.99}},
      {"sigmaNS_1", { mean_sigma1S1,0.01,0.99}},
      {"mag", { 0, 0, 0 }},
      {"sb_ratio", { -1, 0, 0}},
      }, Nworkers);
      }
      if(parsed[2].find("FF") !=std::string::npos){
      MassYieldFit_data(type_, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, app_cutQVP, isBDT, ts, bl, cutBDThigh,  bdtptMin, bdtptMax, 
	  (std::vector<Double_t>) { -0.02,0.0,0.1,0.1, -0.1},
	  (std::vector<Double_t>) {-0.4, -0.5, -0.5,-0.3, -0.3}, 
	  (std::vector<Double_t>) {0.1, 0.2, 0.3,0.3, 0.3}, 
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
      }, Nworkers);
      }
    };
  if(_step >=1|| _step == -101 || _step == -1011 || _step == -51){
	string str_prefit = Form("%s/Yield/",workdir.Data() );
	auto query_file =  getfileany(Form("%s/Yield", workdir.Data()), Form("Yield_:S_9999999999_FF_CB3_CC:pt_%d-%d:cbin_%d-%d:BDT1_cut-1.0000-1.0000:vp%.4f.root",  (int) ptMin, (int) ptMax, cBinLow, cBinHigh , cutQVP ) );
	if( _step == -1011 || query_file.empty()){
		fit_mc_dat(typenobdt, -1);
	}
	if(!(query_file.empty())){
		str_prefit += query_file[0];
	    if(!checkFile(str_prefit) )fit_mc_dat(typenobdt, -1);
		}
  }
  if(_step >=0|| _step == -100 || _step == -52){
    fit_mc_dat(type_r, blow_ref);
  }
  dbg();
  double res_blow;
  std::pair<double, TH1D*> res_GOB;
  RooRealVar sb_ratio;
  dbg(100);
    if( _step > -10 ){
  dbg(100);
    sb_ratio = get_eff_acc(type_r, ts, rapMax, ptMin, ptMax, cBinLow, cBinHigh, blow_ref, 1.0, bdtptMin, bdtptMax, train_state, 1, state, false);
	std::cout << "sb_ratio: " << sb_ratio.getVal() << std::endl;
   res_GOB = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP , sb_ratio.getVal(), train_state,bdtptMin, bdtptMax, "", "S2");
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
       MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax);
    }

    if(mode ==1 || mode ==2){
	  std::string mcres_input = GetFit(__FITRESLATEST, true, "CB3",ts, train_state, (int) state, (int)ptMin, (int)ptMax, cBinLow, cBinHigh, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, "");
	  std::cout << mcres_input << std::endl;

	  TFile* file_MCres_input = TFile::Open(mcres_input.c_str() );
//      TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_train%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_%d.root", ts, (int) state ,train_state,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, bdtptMin, bdtptMax,cutQVP,(int) fixvar), "OPEN");
   
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
      MassYieldFit_data(type, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax,  
//      MassYieldFit_data(type, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh,  bdtptMin, bdtptMax,(std::vector<Double_t>) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, -0.09,-0.07,0.03,0.0017, -0.03}, (std::vector<Double_t>) {0.14, 1.4, 1.3, 0.05, -0.4, -0.3, -0.2,-0.1, -0.1}, (std::vector<Double_t>) {-1,-1,-1,-1, 0.40, 0.30, 0.2,0.1, 0.1}, 
 //     MassYieldFit_data(type, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh,  bdtptMin, bdtptMax,(std::vector<Double_t>) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 5.0,5.1,2.1,0.1}, (std::vector<Double_t>) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3}, (std::vector<Double_t>) {0.31, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 9.1, 10.1, 2.3,0.3}, 
//      MassYieldFit_data(type2, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh,  bdtptMin, bdtptMax,(std::vector<Double_t>) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.0,0.1,0.1,0.1, -0.1}, (std::vector<Double_t>) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3, -0.3}, (std::vector<Double_t>) {-1, -1, -1, -1, 0.1, 0.1, 0.3,0.3, 0.3}, 
//      MassYieldFit_data(type2, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh,  bdtptMin, bdtptMax,(std::vector<Double_t>) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 5.0,5.1,2.1,0.1}, (std::vector<Double_t>) {0.11, 0.5, 0.4, 0.05, 5.3, 1.3, 0.3,-0.3}, (std::vector<Double_t>) {-1, -1, -1, -1, 9.1, 7.1, 2.3,0.3}, 
	  (std::vector<Double_t>) {0.09,-0.07,0.03,-0.001, -0.03},
	  (std::vector<Double_t>) { -0.5, -0.5, -0.4,-0.55, -0.2}, 
	  (std::vector<Double_t>) {0.50, 0.50, 0.5,0.45, 0.2}, 
      (std::map<string, params_vhl>) {
      {"massCut", { 0,fitrange.first,fitrange.second }},
	  {"sigma1S1", {mean_sigma1S1, 0.11, 0.41}}, 
	  {"alpha", {map_keyval["alpha"].first, 1.0, (map_keyval["alpha"].first+map_keyval["alpha"].second)}},
	  {"var_n", {map_keyval["n"].first, 1.0, (map_keyval["n"].first+map_keyval["n"].second)*4}},
	  {"frac", {map_keyval["frac"].first, 0.01, 0.99}},
      {"frac2", {map_keyval["frac2"].first, 0, 1} }, 
      {"xNS", {map_keyval["xNS"].first,0.01,1}}, 
      {"xNS_2", {map_keyval["xNS_2"].first,0.01,1}},
      {"sigmaNS_1", { mean_sigma1S1,0,1}},
      {"mag", { 1, 0, 0 }},
      {"sb_ratio", { sb_ratio.getVal(), 0, 0}},
      {"tmp", {0,0,0} },
      }, Nworkers);
    }

};
/////////////////////////////////////////////STEP : FREEFIT////////////////////////////////////////
  auto METHOD_FREEFIT = [&](string typef = "CB3:CC5:FF") mutable {
  std::cout << "cutBDTlow, sb_ratio in functoin : " << cutBDTlow << ", " << sb_ratio.getVal() << std::endl;
       MassYieldFit_data(typef, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax,  
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
      }, Nworkers);
};

//////////////////////////////////////////STEP : FREE FITTING CENTRALITY/////////////////////////////////////////
auto fixfit = [&](int depth  = 5) mutable {
  if (!isBDT) {
    cutBDTlow =0;
    cutBDThigh=0;
  }
  int ylim10 = (int) (rapMax*10);
  auto parsed = parser_symbol(type);
  std::string sig_func = parsed[0];
  std::string bkg_func = parsed[1];
  std::string fitdir = parsed[2];
  std::string name_fitmodel = "_"+sig_func+"_"+bkg_func;

  SetStyle();
       //////////////////////////////////////////////////////////////////
       std::string name_file_data = Form("%s/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f.root" ,workdir.Data(), train_state, ts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP );
       std::cout << name_file_data << std::endl;
      TFile* file_DATAres_input = new TFile(name_file_data.c_str(), "OPEN");
 std::vector<std::pair<int, int> > cBinPair;
 cBinPair =	{/*{0,40}, {40, 100},  {100,181},*/{0, 181} ,  }; 
// if(train_state==2) cBinPair = {/* {0,10}, {10,20}, {20,40}, {40,60}, {60,80}, {80,100}, */{100,120}, {120, 140},/* {140, 181}*//* {0,181} */};	
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
//    std::pair<double, RooRealVar> res = prep_bdtval(-0.1, depth);
//    cutBDTlow = res.first;
    cutQVP= 0.00; //(!!! JUST FOR No BDT CONFIG !!!)
//    sb_ratio = res.second;
//    sb_ratio = RooRealVar("ratio","",-1);
//    for( int i = 11; i < 12; i++){
//         cutBDTlow = -1.0 + 0.1*i;
 	MassYieldFit_data(type2, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, xts, cutBDTlow, cutBDThigh,  bdtptMin, bdtptMax,
//(std::vector<Double_t>) {map_keyval_2["sigma1S_1"].first, map_keyval_2["alpha"].first, map_keyval_2["n"].first, map_keyval_2["frac"].first, -0.15,-0.1,0.1,0.1}, (std::vector<Double_t>) {0.05, 0.5, 0.4, 0.05, -0.3, -0.4, -0.4,-0.4}, (std::vector<Double_t>) {-1, -1, -1, -1, 0.2, 0.3, 0.35,0.35}, 
	  (std::vector<Double_t>) {0.09,-0.07,0.03,-0.001, -0.03},
	  (std::vector<Double_t>) { -0.5, -0.5, -0.4,-0.55, -0.2}, 
	  (std::vector<Double_t>) {0.50, 0.50, 0.5,0.45, 0.2}, 
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
      {"mag", { 1, 0, 0 }},
      {"sb_ratio", { sb_ratio.getVal(), 0, 0}},
      }, Nworkers);
//    }

    }
//     }
   }
 } 
};
  //##########################################EXECUTION CODE#########################################//

//Step1, First reference integrated bin fit.
double INTBIN_BDTLOW = 0.1825;// =0.16;
train_state = 3;
state =3;
 //Sealed
 if(step == 1 || step == 99 || step == 11 || step == 111){
  for( auto ptpair : (std::vector<std::pair<double, double> >) {{12, 30}/*, {0, 6}, {6, 30}*/}){ 
    ptMin = ptpair.first;
    ptMax = ptpair.second;
    std::pair<double, RooRealVar> res = prep_bdtval(0.2, -1);
    cutBDTlow = res.first;
    sb_ratio = res.second;
    if(ptpair.first == 0 && ptpair.second == 30){ INTBIN_BDTLOW = res.first; }
    std::cout << "cutBDTlow, sb_ratio: " << cutBDTlow << ", "<< sb_ratio.getVal() << std::endl;
    METHOD_MCGCDATA(-2);
  }
}
if(step == 1031){
	ts = input_ts;
	train_state = 3;
	ptMin = 12;
	ptMax = 30;
	fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
	fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
	fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
	std::cout << "fname(nS) : " << fname3S.c_str() << std::endl;
	typenobdt= "CB3:CC5:FF";
	Nworkers = 20;
	std::pair<double, RooRealVar> res = prep_bdtval(-0.0,-1011 );
	
}

if(step ==1200){
	for ( auto loopstates : { 3,} ){ 
	  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30}/*, {0, 6}, {6, 30}*/}){ 
		  for( auto bdtptpair : (std::vector<std::pair<double, double> >) {/*{6, 30},*/{0, 30},/* {0, 6}*/ }){ 
			ts = input_ts;
			train_state =loopstates;
			state = loopstates;
		    ptMin = ptpair.first;
		    ptMax = ptpair.second;
		    bdtptMax = bdtptpair.second;
		    bdtptMin = bdtptpair.first;
	    	fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
	    	fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
	    	fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
			std::cout << "fname(nS) : " << fname3S.c_str() << std::endl;
		    std::pair<double, RooRealVar> res = prep_bdtval(-0.0,-1 );
		    cutBDTlow = res.first;
		    sb_ratio = res.second;
		    if(ptpair.first == 0 && ptpair.second == 30){ INTBIN_BDTLOW = res.first; }
		    std::cout << "cutBDTlow, sb_ratio: " << cutBDTlow << ", "<< sb_ratio.getVal() << std::endl;
		    METHOD_MCGCDATA(1);
		  }
  	}
  }
}

if(step ==1201){
	for ( auto loopstates : { 3,  } ){ 
	  for( auto ptpair : (std::vector<std::pair<double, double> >) {/*{0,4},*/{0,2}/*{0, 6}, {0, 6}, {6, 30}*/}){ 
		  for( auto bdtptpair : (std::vector<std::pair<double, double> >) {{6, 30},{0, 6},{0, 30}  }){ 
			if( ptpair.second == 4 && bdtptpair.second == 6) continue;
			ts = input_ts;
			train_state =loopstates;
			state = loopstates;
		    ptMin = ptpair.first;
		    ptMax = ptpair.second;
		    bdtptMax = bdtptpair.second;
		    bdtptMin = bdtptpair.first;
	    	fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
	    	fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
	    	fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
			std::cout << "fname(nS) : " << fname3S.c_str() << std::endl;
		    std::pair<double, RooRealVar> res = prep_bdtval(-0.0, 3);
		    cutBDTlow = res.first;
		    sb_ratio = res.second;
		    if(ptpair.first == 0 && ptpair.second == 30){ INTBIN_BDTLOW = res.first; }
		    std::cout << "cutBDTlow, sb_ratio: " << cutBDTlow << ", "<< sb_ratio.getVal() << std::endl;
		    METHOD_MCGCDATA(1);
		  }
  	}
  }
}

 if( step == 1311){
  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 4}/*, {0, 6}, {6, 30}*/}){ 
//	ts = 9999999999;// 1635252097;// 1635139612;
	ts = input_ts;
	train_state =aux_train_state;
	state = aux_train_state;
	std::cout << ts << ", " << train_state << std::endl;
	sb_ratio.setVal(-1);
	fitrange= {8, 14};
	sb_ratio.setVal(-1);
		    bdtptMax = 4; 
		    bdtptMin = 0;
	Nworkers = 32;
    fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
    fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
    fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
    ptMin = ptpair.first;
    ptMax = ptpair.second;
    type 			= "CB3:CC3:GC"	;
//    std::pair<double, RooRealVar> res = prep_bdtval(-0.0, -1);
//	for(double xj : {0.9, 0.8, 0.6, 0.1,-0.2}/*}*/){
//	for(double xj : {0.0, 0.1, 0.2,0.25,0.3,0.35,0.4,0.6, 0.8}/*}*/){
//	for(double xj : VALI_V3_BDTTESTCUT/*}*/){
	for(double xj : {0.15, 0.2 } ){
    	cutBDTlow = xj;
    	type 			= "CB3:CC5:GC"	;
//		if(xj < -0.2) type = "CB3:CC4:GC";

    	METHOD_MCGCDATA(1);
//    	METHOD_FREEFIT("CB3:EE:FF");
	}
  }
}
 if( step == 1312){
  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30}/*, {0, 6}, {6, 30}*/}){ 
//	ts = 9999999999;// 1635252097;// 1635139612;
	ts = input_ts;
	train_state =aux_train_state;
	state = aux_train_state;
	std::cout << ts << ", " << train_state << std::endl;
	sb_ratio.setVal(-1);
	fitrange= {8, 14};
	sb_ratio.setVal(-1);
    fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
    fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
    fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
    ptMin = ptpair.first;
    ptMax = ptpair.second;
    type 			= "CB3:CC3:GC"	;
//    std::pair<double, RooRealVar> res = prep_bdtval(-0.0, -1);
//	for(double xj : VALI_V3_BDTTESTCUT3/*}*/){
	for(double xj : {0.8 } ){
    	cutBDTlow = xj;
    	type 			= "CB3:CC5:FF"	;
//		if(xj < -0.2) type = "CB3:CC4:GC";

    	METHOD_MCGCDATA(2);
//    	METHOD_FREEFIT("CB3:EE:FF");
	}
  }
}
 if( step == 13113){
  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30}/*, {0, 6}, {6, 30}*/}){ 
//	ts = 9999999999;// 1635252097;// 1635139612;
	ts = input_ts;
	train_state =aux_train_state;
	state = aux_train_state;
	std::cout << ts << ", " << train_state << std::endl;
	sb_ratio.setVal(-1);
	fitrange= {8, 14};
    fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
    fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
    fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
    ptMin = ptpair.first;
    ptMax = ptpair.second;
    type 			= "CB3:CC3:GC"	;
//    std::pair<double, RooRealVar> res = prep_bdtval(-0.0, -1);
//	for(double xj : {0.9, 0.8, 0.6, 0.1,-0.2}/*}*/){
//	for(double xj : {0.0, 0.1, 0.2,0.25,0.3,0.35,0.4,0.6, 0.8}/*}*/){
	for(double xj : VALI_V3_BDTTESTCUT3/*}*/){
    	cutBDTlow = xj;
    	type 			= "CB3:CC3:GC"	;
		if(xj < -0.2) type = "CB3:CC4:GC";

    	METHOD_MCGCDATA(1);
	}
  }
}
 if( step == 13111){
  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30}/*, {0, 6}, {6, 30}*/}){ 
//	ts = 9999999999;// 1635252097;// 1635139612;
	ts = input_ts;
	train_state =aux_train_state;
	state = aux_train_state;
	cutQVP= 0.05;
	sb_ratio.setVal(-1);
    fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
    fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
    fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
    ptMin = ptpair.first;
    ptMax = ptpair.second;
    type 			= "CB3:CC3:GC"	;
//    std::pair<double, RooRealVar> res = prep_bdtval(-0.0, -1);
	for(double xj : {0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.2,0.05,-0.1,-0.3,-0.5,-0.7,-0.8}/*}*/){
    	cutBDTlow = xj;
    	type 			= "CB3:CC3:GC"	;
		if(xj < -0.2) type = "CB3:CC4:GC";

    	METHOD_MCGCDATA(1);
	}
  }
}

 if( step == 1313){
  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30}/*, {0, 6}, {6, 30}*/}){ 
	ts = input_ts;
	train_state =1;
	state = 1;
	sb_ratio.setVal(-1);
    fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
    fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
    fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
    ptMin = ptpair.first;
    ptMax = ptpair.second;
	for(double xj : {-0.6,-0.3,-0.2,-0.1,-0.05,0.,0.05,0.1,0.15,0.2,0.25,0.3}){
    	cutBDTlow = xj;
    	type 			= "CB3:CC3:GC"	;
		if(xj < -0.2) type = "CB3:CC4:GC";

    	METHOD_MCGCDATA(2);
	}
  }
}


 if( step == 1314){
  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30}/*, {0, 6}, {6, 30}*/}){ 
	ts = input_ts;
	train_state =1;
	state = 1;
	if(aux_train_state !=0){
		train_state = aux_train_state / 10;
		state = aux_train_state % 10;
	}

	sb_ratio.setVal(-1);
    fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
    fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
    fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
    ptMin = ptpair.first;
    ptMax = ptpair.second;

		cutBDTlow = aux_BDT_cut;
    	type 			= "CB3:CC3:GC"	;
		if(cutBDTlow < -0.2) type = "CB3:CC4:GC";

    	METHOD_MCGCDATA(2);
	}
 }



//Step2, Analysis bin fit
//Sealed
if(step ==1 || step == 99 || step ==12){
  ptMin = 0;
  ptMax = 30;
  cutBDTlow = INTBIN_BDTLOW;
  type2 = "CB3:CC2:FF";
  fixfit(-1);
//  cutBDTlow = INTBIN_BDTLOW;
//  cBinLow = 0;
//  cBinHigh = 181;
//  type2 = "CB3:CC2:DR2FF";
//  fixfit(-1);
//  cutBDTlow = INTBIN_BDTLOW;
//  cBinLow = 0;
//  cBinHigh = 181;
//  type2 = "CB3:CC2:FF";
//  fixfit(-1);
}


INTBIN_BDTLOW = 0.2689;
train_state = 2;
state =2;
 //Sealed
if(step ==2 || step ==99|| step ==21){
  cBinLow = 0;
  cBinHigh = 181;
  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30},/* {0, 4}, {4, 9},{9, 30}*/ }){ 
    ptMin = ptpair.first;
    ptMax = ptpair.second;
    std::pair<double, RooRealVar> res = prep_bdtval(-0.0, -1);
    cutBDTlow = 0.2;// res.first;
    sb_ratio = res.second;
    if(ptpair.first == 0 && ptpair.second == 30){ INTBIN_BDTLOW = res.first; }
    std::cout << "cutBDTlow, sb_ratio: " << cutBDTlow << ", "<< sb_ratio.getVal() << std::endl;
    METHOD_MCGCDATA(1);
  }
};


//Step2, Analysis bin fit
//Sealed
if(step ==2 || step == 99 || step == 22){
  ptMin = 0;
  ptMax = 30;
  cutBDTlow = INTBIN_BDTLOW;
  type2 = "CB3:CC2:DRFF";
  fixfit(-1);
//  cutBDTlow = INTBIN_BDTLOW;
//  cBinLow = 0;
//  cBinHigh = 181;
//  type2 = "CB3:CC2:DR2FF";
//  fixfit(-1);
//  dbg();
//  cutBDTlow = INTBIN_BDTLOW;
//  cBinLow = 0;
//  cBinHigh = 181;
//  type2 = "CB3:CC2:FF";
//  fixfit(-1);
}



if(step ==3){
  cutBDTlow = INTBIN_BDTLOW;
  state =2;
  train_state =2;
  ptMin = 0;
  ptMax = 30;
  cBinLow = 0;
  cBinHigh = 181;
  type2 = "CB3:CC4:FF";
  fixfit(5);
//  std::pair<double, RooRealVar> res = prep_bdtval(-0.1, 999);
//  res = prep_bdtval(-0.1, -103);
  
};

if(step == 4){
  std::string type_ = "CB3:CC4:FF";
  train_state =2;
  state =2;
  ptMin = 0;
  ptMax = 30;
  cBinLow = 0;
  cBinHigh = 181; 
  cutQVP = 0.01;
  cutBDTlow = -1;
  cutBDThigh =1;
  std::string fname;
  if(state ==1) fname = fname1S;
  if(state ==2) fname = fname2S;
  if(state ==3) fname = fname3S;
  MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, -1, cutBDThigh, bdtptMin, bdtptMax);
  string _tpye = type_;
  double bl = cutBDTlow;
    TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_train%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_%d.root", ts, (int) state ,train_state,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), bl, cutBDThigh, bdtptMin, bdtptMax, cutQVP,(int) fixvar), "OPEN");
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

     MassYieldFit_data(type_, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, bl, cutBDThigh, bdtptMin, bdtptMax, (std::vector<Double_t>) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, -0.02,0.0,0.1,0.1, -0.1}, (std::vector<Double_t>) {0.11, 0.5, 0.4, 0.05, -0.4, -0.5, -0.5,-0.3, -0.3}, (std::vector<Double_t>) {-1,-1,-1,-1, 0.1, 0.2, 0.3,0.3, 0.3}, 
       (std::map<string, params_vhl>) {
         {"massCut", { 0,8,14 }},
       {"frac2", {0.3, 0, -1} }, 
       {"xNS", {0.3,0,-1}}, 
       {"xNS_2", {0.5,0,-1}},
       {"sigmaNS_1", { 0.21 ,0,-1}},
       {"mag", { 0, 0, 0 }},
       {"sb_ratio", { -1, 0, 0}},
       });
}
};

#if defined __CLING__
#endif
