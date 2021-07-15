//#include "./BDT/bininfo.h"
//#include "MassYieldFit_BDT_MC.C"
//#include "MassYieldFit_BDT_MC_GE.C"
#include "MassYieldFit_BDT_MC_CB3.C"
//#include "MassYieldFit_BDT_MC.C"
#include "MassYieldFit_data.cxx"
#include "./BDT/yield_eff_signif.cxx"
//#include "./BDT/GOBC.cxx"

void doConstraintFit(int step = 0){
  std::string type 			= "CB3:CC4:GC"	;
  std::string type2 			= "CB3:CC2:DR2FF"	;
  std::string type_r 			= "CB3:CC2:DRGC"	;
  std::string typenobdt 		= "CB3:CC4:FF"	;
  std::string constraints		="alpha:n:frac:frac2:xNS:xNS_2:sigmaNS_1"	;
  std::string fixvars			="alpha:n:frac:frac2:x1S:x1S_2:sigma1S_1"	;
// std::string constraints		="alpha:n:frac:xNS:sigma3S_1"	;
// std::string fixvars			="alpha:n:frac:x1S:sigma1S_1"	;
  long ts				= 1625139244;// 1626100443; //1625558168; //  // Past nominal 1623391157; //71622626134;//	1621574976;//	//	1622517421;
  long ts_2				= 1625736641/*(LOWPT)*/; //1625558633/*(PERI)*/; //1625503068	;
  double ptMin				= 0		;
  double ptMax				= 30 		;
  double rapMin				= -2.4		;
  double rapMax				= 2.4		;
  TString MupT				= "3p5"		;
  std::string Trig			= "S13"		;
  int state				= 2		;
  bool fixvar				= false		;
  bool swflag				= false		;
  int cBinLow				= 0		;
  int cBinHigh				= 181 		;
  double cutQVP				= 0.00		;
  bool isBDT 				= true		;
  double cutBDTlow			= 0.0859	;
  double cutBDThigh			= 1.0		;
  RooRealVar sb_ratio					;
  const std::string fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
  const std::string fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
  const std::string fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());
/*
*/
auto prep_bdtval = [&] (double blow_ref = -0.3, int _step =0) mutable {
  std::string fname;
  if(state ==1) fname = fname1S;
  if(state ==2) fname = fname2S;
  if(state ==3) fname = fname3S;
  if(_step >=3 || _step == -103 || _step == -51){
    MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, -1, cutBDThigh);
//       MassYieldFit_BDT_MC(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, -1, cutBDThigh);
  }
  if(_step >=2|| _step == -102 || _step == -52){
    MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, blow_ref, cutBDThigh);
//       MassYieldFit_BDT_MC(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, blow_ref, cutBDThigh);
}

      auto fit_mc_dat = [=] (string type_, double bl){
//      TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root", ts, (int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), bl, cutBDThigh, cutQVP,(int) fixvar), "OPEN");
      TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root", ts, (int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), bl, cutBDThigh, cutQVP,(int) fixvar), "OPEN");
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
      MassYieldFit_data(type_, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, bl, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.0,0.0,0.1,0.1, -0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.5, -0.5, -0.5,-0.3, -0.3}, (Double_t[]) {0.41, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 0.1, 0.1, 0.3,0.3, 0.3}, 
       (std::map<string, params_vhl>) {
       {"frac2", {map_keyval["frac2"].first, 0, 1} }, 
       {"xNS", {map_keyval["xNS"].first,0,1}}, 
       {"xNS_2", {map_keyval["xNS_2"].first,0,1}},
       {"sigmaNS_1", { mean_sigma1S1,0,1}},
       {"mag", { 0, 0, 0 }},
      {"sb_ratio", { -1, 0, 0}},
       });
      }
      if(parsed[2].find("FF") !=std::string::npos){
      MassYieldFit_data(type_, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, bl, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.0,0.1,0.1,0.1, -0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3, -0.3}, (Double_t[]) {-1, -1, -1, -1, 0.1, 0.1, 0.3,0.3, 0.3}, 
       (std::map<string, params_vhl>) {
       {"frac2", {map_keyval["frac2"].first, 0, -1} }, 
       {"xNS", {map_keyval["xNS"].first,0,-1}}, 
       {"xNS_2", {map_keyval["xNS_2"].first,0,-1}},
       {"sigmaNS_1", { mean_sigma1S1,0,-1}},
       {"mag", { 0, 0, 0 }},
      {"sb_ratio", { -1, 0, 0}},
       });
      }
    };
  if(_step >=1|| _step == -101 || _step == -51){
    fit_mc_dat(typenobdt, -1);
  }
  if(_step >=0|| _step == -100 || _step == -52){
    fit_mc_dat(type_r, blow_ref);
  }
    auto sb_ratio = get_eff_acc(type_r, typenobdt, ts, rapMax, ptMin, ptMax, cBinLow, cBinHigh, blow_ref, 1.0, 1, 3);
   auto res_GOB = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP , sb_ratio.getVal(), "", "S2");
   double res_blow = res_GOB.first;

   if(_step <=-999){
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


//	TH1D* ratio_hist = new TH1D("ratio_hist", "", 10,-1,0);
//	 sb_ratio = get_eff_acc("CB3:CC4:DRGC", typenobdt, 1623391157, 2.4, 0, 30, 0, 180, -0.3, 1.0, 1, 3);
//	 ratio_hist->SetBinContent(ratio_hist->FindBin(-0.3), sb_ratio.getVal());
//	 ratio_hist->SetBinError(ratio_hist->FindBin(-0.3), sb_ratio.getError());
//	 sb_ratio = get_eff_acc("CB3:CC2:DRGC", typenobdt, 1623391157, 2.4, 0, 30, 0, 180, -0.1, 1.0, 1, 3);
//	 ratio_hist->SetBinContent(ratio_hist->FindBin(-0.1), sb_ratio.getVal());
//	 ratio_hist->SetBinError(ratio_hist->FindBin(-0.1), sb_ratio.getError());
//	 std::cout << "RATIO IS : " << sb_ratio.getVal() << std::endl;
////cutBDTlow = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP , sb_ratio.getVal()).first;
////   cutBDTlow = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP , sb_ratio.getVal(), "", "S2").first;
////   cutBDTlow = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP , 0.09, "", "S2").first;
//   std::cout << "BDTcutLow" << cutBDTlow << std::endl;
//       auto return_hist = func_hist_optimal_BDT();
//       TCanvas* c1= new TCanvas();
//       c1->cd();
//       c1->Draw();
//       ratio_hist->Draw();
////       return_hist->Draw();
//       c1->Update();

//      cutBDTlow = -0.30;
auto METHOD_MCGCDATA = [&](int mode = 1) mutable {
  std::cout << "cutBDTlow, sb_ratio in functoin : " << cutBDTlow << ", " << sb_ratio.getVal() << std::endl;
    std::string fname;
    if(state ==1) fname = fname1S;
    if(state ==2) fname = fname2S;
    if(state ==3) fname = fname3S;
    if(mode ==1 || mode ==0){
       MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
//       MassYieldFit_BDT_MC(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
    }
    if(mode ==1 || mode ==2){
      TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root", ts, (int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, cutQVP,(int) fixvar), "OPEN");
//      TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB2_%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root", ts, (int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, cutQVP,(int) fixvar), "OPEN");

   
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
      MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, -0.15,-0.05,0.01,0.00, -0.03}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.2, -0.2, -0.1,-0.1, -0.1}, (Double_t[]) {0.41, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 0.0, 0.1, 0.1,0.1, 0.1}, 
 //     MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 5.0,5.1,2.1,0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.31, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 9.1, 10.1, 2.3,0.3}, 
//      MassYieldFit_data(type2, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.0,0.1,0.1,0.1, -0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3, -0.3}, (Double_t[]) {-1, -1, -1, -1, 0.1, 0.1, 0.3,0.3, 0.3}, 
//      MassYieldFit_data(type2, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 5.0,5.1,2.1,0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, 5.3, 1.3, 0.3,-0.3}, (Double_t[]) {-1, -1, -1, -1, 9.1, 7.1, 2.3,0.3}, 
       (std::map<string, params_vhl>) {
       {"frac2", {map_keyval["frac2"].first, 0, 1} }, 
       {"xNS", {map_keyval["xNS"].first,0,1}}, 
       {"xNS_2", {map_keyval["xNS_2"].first,0,1}},
       {"sigmaNS_1", { mean_sigma1S1,0,1}},
       {"mag", { 1, 0, 0 }},
      {"sb_ratio", { sb_ratio.getVal(), 0, 0}},
//      {"sb_ratio", { -1, 0, 0}},
       });
    }

};



////       MassYieldFit_BDT_MC(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
////       MassYieldFit_BDT_MC_GE(ts, "", fname3S, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
//
////       cutBDTlow = 0.15;
//
////        MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, 1, 1, 0.5, 0.0,-0.1,0.1,0.1}, (Double_t[]) {0.11, 1.0, 0.7, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.21, 5, 5, 0.95, 0.1, 0.1, 0.3,0.3});
//        //MassYieldFit_data(type, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {0.2, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 7.2,5.1,1.1,0.1}, (Double_t[]) {0.11, 1.0, 1.0, 0.05, 5.3, 1.3, 0.3,-0.3}, (Double_t[]) {0.21, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 9.6, 10.1, 4.3,0.3});

auto fixfit = [&](int targetState= 3) mutable {
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
 std::vector<std::pair<int, int> > cBinPair;
 cBinPair =	{{0,40}, {40, 100},  {100,181}, /*  {0, 181} , */ }; 
 if(targetState==2) cBinPair = {/* {0,10}, {10,20}, {20,40}, {40,60}, {60,80}, {80,100}, {100,120}, {120, 140},*/ {140, 181} };	//{ {0,40}, {40, 100}, {100,180}, {0, 180} };
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

//	cutBDTlow = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP , sb_ratio.getVal(), "", "S2").first;


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
      if (cp == (std::pair<int, int>){100,181})
      {
//	xts = ts_2;
      }

//  for( double idx = -1; idx < 0.3; idx += 0.1)
//  {
//    std::pair<double, RooRealVar> res = prep_bdtval(-0.1, 6);
    cutBDTlow = -0.1; //res.first;
//    cutBDTlow = idx;
    cutQVP= 0.00; //(!!! JUST FOR No BDT CONFIG !!!)
    sb_ratio = RooRealVar("x","",-1); // res.second; //    std::cout << "cutBDTlow, sb_ratio: " << cutBDTlow << ", "<< sb_ratio.getVal() << std::endl;
  
         MassYieldFit_data(type2, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, xts, cutBDTlow, cutBDThigh, (Double_t[]) {map_keyval_2["sigma1S_1"].first, map_keyval_2["alpha"].first, map_keyval_2["n"].first, map_keyval_2["frac"].first, -0.15,-0.1,0.1,0.1}, (Double_t[]) {0.05, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {-1, -1, -1, -1, 0.1, 0.1, 0.3,0.3}, 
         (std::map<string, params_vhl>) {
         {"frac2", {map_keyval_2["frac2"].first, 0, -1} }, 
         {"xNS", {map_keyval_2["x1S"].first,0,-1}}, 
         {"xNS_2", {map_keyval_2["x1S_2"].first,0,-1}},
         {"sigmaNS_1", { map_keyval_2["sigma1S_1"].first,0,-1}},
         {"mag", { 1, 0, 0 }},
        {"sb_ratio", { sb_ratio.getVal(), 0, 0}},
  //      {"sb_ratio", { -1, 0, 0}},
         });
       }
//     }
   }
 } 
};
 /**/



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
  
  //##########################################EXECUTION CODE#########################################//

//Step1, First reference integrated bin fit.
if(step ==1){
//  ts = ts_2;
  std::pair<double, RooRealVar> res = prep_bdtval(-0.0, -2);
  cutBDTlow = res.first;
//  cutBDTlow = -0.1;
  sb_ratio = RooRealVar("ratio","",-1);// res.second;
  std::cout << "cutBDTlow, sb_ratio: " << cutBDTlow << ", "<< sb_ratio.getVal() << std::endl;
  METHOD_MCGCDATA(0);
}
//Step2, Analysis bin fit

if(step ==2 ) fixfit(3);


};

