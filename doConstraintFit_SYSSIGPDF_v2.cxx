#pragma once

#if defined _TS
void doConstraintFit_SYSSIGPDF_v2(int step = 0){
  std::string type 			= "CB2G:CC3:GC"	;
  std::string type2 			= "CB2G:CC4:DR2FF"	;
  std::string type_r 			= "CB2G:CC4:DRGC"	;
  std::string typenobdt 		= "CB2G:CC4:FF"	;
  std::string constraints		="alpha:n:frac:frac2:xNS:xNS_2:sigmaNS_1"	;
  std::string fixvars			="alpha:n:frac:frac2:x1S:x1S_2:sigma1S_1"	;
  long ts						= _TS	; 
  long ts_2						= _TS	;
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
  double drawonly				= 0;
  RooRealVar sb_ratio					;
  string plot_dir_opt			= "";
   std::string fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
   std::string fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
   std::string fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
   std::pair<double, double> fitrange = {8, 14};
   int Nworkers 			= 30;
   std::vector<Double_t> bkg_val ;
   std::vector<Double_t> bkg_low ;
   std::vector<Double_t> bkg_high;


//////////////////////////////////////////STEP : GAUS CONSTRAIN FITTING/////////////////////////////////////////
  auto METHOD_MCGCDATA = [&](int mode = 1) mutable {
  std::cout << "cutBDTlow, sb_ratio in functoin : " << cutBDTlow << ", " << sb_ratio.getVal() << std::endl;
    std::string fname;
    if(state ==1) fname = fname1S;
    if(state ==2) fname = fname2S;
    if(state ==3) fname = fname3S;
	std::cout << Form("%ld,%.4f, %.4f, %d, %d, %d, %d, %.4f, %.4f, %d, %d", ts, ptMin, ptMax, cBinLow, cBinHigh, train_state, state, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax) << std::endl;
    if(mode ==1 || mode ==0){
       MassYieldFit_BDT_MC_CB2G(ts_alias(ts), "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, plot_dir_opt);
    }

    if(mode ==1 || mode ==2){
	  std::string mcres_input = GetFit(__FITRESLATEST, true, "CB2G",ts_alias(ts) , train_state, state, (int)ptMin, (int)ptMax, cBinLow, cBinHigh, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, "");
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
	  {"sigma1S1", {mean_sigma1S1, 0.13, 0.41}}, 
	  {"alpha", {map_keyval["alpha"].first, 0.8, (map_keyval["alpha"].first+map_keyval["alpha"].second*6)}},
	  {"var_n", {map_keyval["n"].first, 0.6, (map_keyval["n"].first+map_keyval["n"].second)*4}},
	  {"frac", {map_keyval["frac"].first, 0.0, 1.}},
      {"frac2", {map_keyval["frac2"].first, 0, 1} }, 
      {"xNS", {map_keyval["xNS"].first,0.00,1}}, 
      {"xNS_2", {map_keyval["xNS_2"].first,0.00,1}},
      {"sigmaNS_1", { mean_sigma1S1,0,1}},
      {"mag", { 1, 0, 0 }},
      {"sb_ratio", { sb_ratio.getVal(), 0, 0}},
      {"tmp", {0,0,0} },
	  {"DrawOnly", {drawonly, 0, 0}},
      }, Nworkers, plot_dir_opt);
    }

};
/////////////////////////////////////////////STEP : FREEFIT////////////////////////////////////////
  auto METHOD_FREEFIT = [&](string typef = "CB3:CC5:FF") mutable {
  std::cout << "cutBDTlow, sb_ratio in functoin : " << cutBDTlow << ", " << sb_ratio.getVal() << std::endl;
       MassYieldFit_data(typef, train_state, state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax,  
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
	  std::string name_file_data = GetFit(__FITRESLATEST, false, type,ts, train_state, (int) state, 0, 30, 0, 181, cutBDTlow, cutBDThigh, 0, 30, cutQVP, "");
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
	{"DrawOnly", {drawonly, 0, 0}},
	}, Nworkers, plot_dir_opt);
};
  //##########################################EXECUTION CODE#########################################//

plot_dir_opt = "Sys_SIG_PDF_CB2G_v7";

//Step1, First reference integrated bin fit.
double INTBIN_BDTLOW = 0.1825;// =0.16;
train_state = 3;
state =3;
 //Sealed
 if(step == 1 || step == 99 || step == 11 || step == 111){
  for( auto ap : ana_bm){
	  for( auto ab : ap.second){
		if( !((ab.bin_attr.find("i")!=std::string::npos && ab.state == 3))) continue;
//		if( !(ab.cl==80&&ab.ch==100&&(ab.bin_attr.find("c")!=std::string::npos && ab.state ==2))) continue;
//		if( !(ab.pl==9&&ab.ph==15&&(ab.bin_attr.find("p")!=std::string::npos && true))) continue;
//		if( !(ab.bin_attr.find("p")!=std::string::npos && ab.ph > 29 && ab.state ==2)) continue;
		string fittype = (strcmp(ab.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	  	ptMin = ab.pl;
		ptMax = ab.ph;
		bdtptMin = ab.bpl;
		bdtptMax = ab.bph;
		cBinLow = ab.cl;
		cBinHigh = ab.ch;
		train_state = ab.train_state;
		state = ab.state;

	  	cutBDTlow = Get_BDT(ts_alias(ts), ab);
		dbg();
	    sb_ratio = RooRealVar("sb_ratio", "",-1);
		bool fitdata = true;
		drawonly = 0;
		if(fitdata){
			auto CTEST = AICGOF_test(ab);
			string bkgNom = CTEST[0].second;
			Nworkers = 40;
		    std::cout << "cutBDTlow, sb_ratio: " << cutBDTlow << ", "<< sb_ratio.getVal() << std::endl;
			type			= "CB2G:"+ bkgNom  + ":" + fittype.c_str();
			type2			= "CB2G:"+ bkgNom  + ":" + fittype.c_str();
			if(strcmp(ab.bin_attr.c_str(),"c")==0){
				double cbl = cutBDTlow;
				cutBDTlow = Get_BDT(ts_alias(ts), ab.train_state, ab.state, 0, 30, 0, 30, 0, 181, 0.00, 2.4, 2); 
				string bkgNomREF = AICGOF_test(ana_bm[Form("%dc",ab.state)][0])[0].second;
				type			= "CB2G:"+ bkgNomREF  + ":" + "GC";
				if(bkgNom.find("CC")!=std::string::npos){
	    			bkg_val  = {-0.4, -0.07, 0.03,  -0.001, -0.03, 0.0, 0.0, 0.0, 0.0};
	    			bkg_low  = {-0.8, -0.6, -0.6,  -0.6, -0.5, -0.5, -0.5, -0.5, -0.5};
	    			bkg_high = {0.6, 0.6, 0.6, 0.6, 0.6, 0.5, 0.5, 0.5, 0.5};
					fixfit(cbl);

					}
				if(bkgNom.find("EE")!=std::string::npos){
		    		bkg_val  = {7.5, 4.0, 1.3,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		    		bkg_low  = {6.0, 2.0, 0.01,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
		    		bkg_high = {9, 9.0, 4.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
					fixfit(cbl);
					}
				if(bkgNom.find("EX")!=std::string::npos){
			    	bkg_val  = {-1.1, 4.0, 1.5,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
			    	bkg_low  = {-10.0, 2.0, 0.2,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
			    	bkg_high = {0.1 , 20.0, 3.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
					fixfit(cbl);
					}
			}
			else{
				if(bkgNom.find("CC")!=std::string::npos){
	    			bkg_val  = {-0.4, -0.07, 0.03,  -0.001, -0.03, 0.0, 0.0, 0.0, 0.0};
	    			bkg_low  = {-0.8, -0.6, -0.6,  -0.6, -0.5, -0.5, -0.5, -0.5, -0.5};
	    			bkg_high = {0.6, 0.6, 0.6, 0.6, 0.6, 0.5, 0.5, 0.5, 0.5};
		    		METHOD_MCGCDATA(2);
					}
				if(bkgNom.find("EE")!=std::string::npos){
		    		bkg_val  = {7.18, 5.18, 1.15,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		    		bkg_low  = {6.0, 2.0, 0.50,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
		    		bkg_high = {8.3, 8.0, 4.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
//		    		bkg_high = {50, 10, 9, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
		    		METHOD_MCGCDATA(2);
					}
				if(bkgNom.find("EX")!=std::string::npos){
			    	bkg_val  = {-1.1, 4.0, 1.5,    0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
			    	bkg_low  = {-10.0, 2.0, 0.2,  -0.5, -0.5, -0.5, -0.5, -0.5, -0.5};
			    	bkg_high = {0.1 , 20.0, 3.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5};
		    		METHOD_MCGCDATA(2);
					}
			}
		}
	  	}
  }
}
}
#endif



#if defined __CLING__
#endif
