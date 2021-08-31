//#include "./BDT/bininfo.h"
#include "LLR_CCorder.h"
#include "MassYieldFit_BDT_MC_CB3.C"
//#include "MassYieldFit_BDT_MC.C"
#include "MassYieldFit_data.cxx"
#include "./BDT/yield_eff_signif.cxx"

void doConstraintFit_SYSBDTERR(int global_step = 1, int step = 0){
  std::string type 			= "CB3:CC2:GC"	;
  std::string type2 			= "CB3:CC2:DR2FF"	;
  std::string type_r 			= "CB3:CC2:DRGC"	;
  std::string typenobdt 		= "CB3:CC4:FF"	;
  std::string constraints		="alpha:n:frac:frac2:xNS:xNS_2:sigmaNS_1"	;
  std::string fixvars			="alpha:n:frac:frac2:x1S:x1S_2:sigma1S_1"	;
  long ts				= 9999999999	; 
  long ts_2				= 9999999999	;
  double ptMin				= 0		;
  double ptMax				= 30 		;
  double rapMin				= -2.4		;
  double rapMax				= 2.4		;
  TString MupT				= "3p5"		;
  std::string Trig			= "S13"		;
  int train_state			= 3		;
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
  double ratio						;
//////////////////////////////////////////UNIQUE/////////////////////////////////////////
    string bdt_seg			= (global_step ==-1) ? "bdtdown" : "bdtup";	 
  type 					= type + bdt_seg;
  type2 				= type + bdt_seg;
//////////////////////////////////////////CHANGE/////////////////////////////////////////
  const std::string fname3S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC.root", ts, Trig.c_str());
  const std::string fname2S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_2S.root", ts, Trig.c_str());
  const std::string fname1S		= Form("OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT_MC_1S.root", ts, Trig.c_str());

//////////////////////////////////////////STEP : BDT VALUE DECISION/////////////////////////////////////////
auto prep_bdtval = [&] (double blow_ref = -0.3, int _step =0) mutable {
//  std::string fname;
//  if(state ==1) fname = fname1S;
//  if(state ==2) fname = fname2S;
//  if(state ==3) fname = fname3S;
//  if(_step >=3 || _step == -103 || _step == -51){
//    MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, -1, cutBDThigh);
//  }
//  if(_step >=2|| _step == -102 || _step == -52){
//    MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, blow_ref, cutBDThigh);
//}
//
//      auto fit_mc_dat = [&] (string type_, double bl){
//      TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_train%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root", ts, (int) state ,train_state,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), bl, cutBDThigh, cutQVP,(int) fixvar), "OPEN");
//      RooFitResult* result_MC = (RooFitResult*) file_MCres_input->Get("fitresult_model_reducedDS");
//      std::cout << file_MCres_input->GetName() << std::endl;
//      auto list_fit_initial = result_MC->floatParsInit();
//      auto list_fit_final = result_MC->floatParsFinal();
//      auto list_var_toConst = parser_symbol(constraints);
//      std::map< std::string,std::pair< double, double> > map_keyval;
//      std::string opt_params_gc;
//      for (auto keys : list_var_toConst){
//      std::cout << keys << std::endl;
//        RooRealVar* _var = (RooRealVar*) list_fit_final.find(keys.c_str());
//        map_keyval[keys.c_str()] = {_var->getVal(), _var->getError()};
//        opt_params_gc+=Form(":%s;%.6f",keys.c_str(), _var->getError());
//      std::cout << keys <<": "<< _var->getVal() << ", "<< _var->getError() << std::endl;
//      }
//      opt_params_gc+=":GCPEND";
//      type_ = type_+opt_params_gc; 
//      std::cout << type_ << std::endl;
//
//       double mean_sigma1S1;
//       if(state ==3) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U3S_mass);
//       if(state ==2) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U2S_mass);
//       if(state ==1) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U1S_mass);
//      auto parsed = parser_symbol(type_,":");
//      if(parsed[2].find("FF") ==std::string::npos){
//      MassYieldFit_data(type_, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, bl, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, -0.02,0.0,0.1,0.1, -0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.4, -0.5, -0.5,-0.3, -0.3}, (Double_t[]) {0.41, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 0.1, 0.2, 0.3,0.3, 0.3}, 
//       (std::map<string, params_vhl>) {
//       {"frac2", {map_keyval["frac2"].first, 0.01, 0.99} }, 
//       {"xNS", {map_keyval["xNS"].first,0.01,0.99}}, 
//       {"xNS_2", {map_keyval["xNS_2"].first,0.01,0.99}},
//       {"sigmaNS_1", { mean_sigma1S1,0.01,0.99}},
//       {"mag", { 0, 0, 0 }},
//      {"sb_ratio", { -1, 0, 0}},
//       });
//      }
//      if(parsed[2].find("FF") !=std::string::npos){
//      MassYieldFit_data(type_, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, bl, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.0,0.1,0.1,0.1, -0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.2, -0.1}, (Double_t[]) {-1, -1, -1, -1, 0.1, 0.1, 0.3,0.2, 0.1}, 
//       (std::map<string, params_vhl>) {
//       {"frac2", {map_keyval["frac2"].first, 0, -1} }, 
//       {"xNS", {map_keyval["xNS"].first,0,-1}}, 
//       {"xNS_2", {map_keyval["xNS_2"].first,0,-1}},
//       {"sigmaNS_1", { mean_sigma1S1,0,-1}},
//       {"mag", { 0, 0, 0 }},
//      {"sb_ratio", { -1, 0, 0}},
//       });
//      }
//    };
//  if(_step >=1|| _step == -101 || _step == -51){
//    fit_mc_dat(typenobdt, -1);
//  }
//  if(_step >=0|| _step == -100 || _step == -52){
//    fit_mc_dat(type_r, blow_ref);
//  }
    auto sb_ratio = get_eff_acc(type_r, typenobdt, ts, rapMax, ptMin, ptMax, cBinLow, cBinHigh, blow_ref, 1.0, train_state, 1, state);
    if( _step == 1) ratio = sb_ratio.getVal() + sb_ratio.getError();
    if( _step == -1) ratio = sb_ratio.getVal() - sb_ratio.getError();
    if(_step == 0){ std::cout << "Why fitting Nominal here? " << std::endl;}
    std::cout << "\n\n\n\nDEBUG : RATIO = "<<ratio<<"\nDEBUG : REF RATIO = "<<sb_ratio.getVal() << ", Error = "<< sb_ratio.getError() << std::endl;
    std::string systype;
    if(_step ==  1 ) systype = "SYSUP";
    if(_step == -1 ) systype = "SYSDOWN";
    else std::cout << " !!! " << std::endl;
   auto res_GOB = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP , ratio, train_state, "", "S2", systype.c_str());
   auto res_GOB_ref = Get_Optimal_BDT(ts,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP , sb_ratio.getVal(), train_state, "", "S2");
   double res_blow = res_GOB.first;
   double res_blow_ref = res_GOB_ref.first;
   if (res_blow == res_blow_ref){
       std::cout << "[DBG0831] " <<res_blow << " , " << res_blow_ref<< std::endl;;
       std::cout << "[BDT val Getter] Referencing BDT ratio from Integrated Bin" << std::endl;
       auto sb_ratio_INT = get_eff_acc(type_r, typenobdt, ts, rapMax, 0, 30, 0, 181, -0.0, 1.0, train_state, 1, state);
       double ratio_INT_ref = sb_ratio_INT.getVal();
       double ratio_INT = ratio_INT_ref + ((double) _step * sb_ratio.getError() ); 
	std::cout << "[DBG0831] " << Form(" INT RATIOS (SB, REF, ratio_INT) %.6f %.6f %.6f" , sb_ratio_INT.getVal(), ratio_INT_ref, ratio_INT) << std::endl;
       double INT_BDT_ref = Get_Optimal_BDT(ts,0,30, rapMin, rapMax, 0, 181, cutQVP , ratio_INT_ref, train_state, "", "S2", "ST").first;
       double INT_BDT = Get_Optimal_BDT(ts,0,30, rapMin, rapMax, 0, 181, cutQVP , ratio_INT, train_state, "", "S2", "SYSNON2").first;
       double bdt_val_ratio = INT_BDT/INT_BDT_ref;
       std::cout << "[DBG0831] BDT_VAL_RATIO: " << bdt_val_ratio << std::endl;
       res_blow = res_blow_ref* bdt_val_ratio;
   }

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
   return std::make_pair(res_blow, ratio);

};

//////////////////////////////////////////STEP : GAUS CONSTRAIN FITTING/////////////////////////////////////////
  auto METHOD_MCGCDATA = [&](int mode = 1) mutable {
  std::cout << "cutBDTlow, ratio in functoin : " << cutBDTlow << ", " << ratio << std::endl;
    std::string fname;
    if(state ==1) fname = fname1S;
    if(state ==2) fname = fname2S;
    if(state ==3) fname = fname3S;
    if(mode ==1 || mode ==0){
       MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, cutBDTlow, cutBDThigh);
    }
    if(mode ==1 || mode ==2){
      TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_train%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root", ts, (int) state, train_state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, cutQVP,(int) fixvar), "OPEN");
   
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
      type = Form("%s:CC%d:%s", parser_symbol(type)[0].c_str(), getNomBkgO(state, (int) ptMin, (int) ptMax, cBinLow, cBinHigh), parser_symbol(type)[2].c_str());
      type = type+opt_params_gc; 
      std::cout << type << std::endl;

       double mean_sigma1S1;
       if(state ==3) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U3S_mass);
       if(state ==2) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U2S_mass);
       if(state ==1) mean_sigma1S1 = map_keyval["sigmaNS_1"].first*(U1S_mass/U1S_mass);
      MassYieldFit_data(type, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, -0.05,0.10,0.01,0.00, -0.03}, (Double_t[]) {0.11, 0.5, 0.4, 0.01, -0.4, -0.3, -0.1,-0.1, -0.1}, (Double_t[]) {0.41, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 0.20, 0.20, 0.1,0.1, 0.1}, 
 //     MassYieldFit_data(type, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 5.0,5.1,2.1,0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {0.31, (map_keyval["alpha"].first+map_keyval["alpha"].second)*2, (map_keyval["n"].first+map_keyval["n"].second)*4, 0.95, 9.1, 10.1, 2.3,0.3}, 
//      MassYieldFit_data(type2, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 0.0,0.1,0.1,0.1, -0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3, -0.3}, (Double_t[]) {-1, -1, -1, -1, 0.1, 0.1, 0.3,0.3, 0.3}, 
//      MassYieldFit_data(type2, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, 5.0,5.1,2.1,0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, 5.3, 1.3, 0.3,-0.3}, (Double_t[]) {-1, -1, -1, -1, 9.1, 7.1, 2.3,0.3}, 
       (std::map<string, params_vhl>) {
       {"frac2", {map_keyval["frac2"].first, 0, 1} }, 
       {"xNS", {map_keyval["xNS"].first,0.01,1}}, 
       {"xNS_2", {map_keyval["xNS_2"].first,0.01,1}},
       {"sigmaNS_1", { mean_sigma1S1,0,1}},
       {"mag", { 1, 0, 0 }},
      {"sb_ratio", { ratio, 0, 0}},
       });
    }

};

//////////////////////////////////////////STEP : FREE FITTING CENTRALITY/////////////////////////////////////////
auto fixfit = [&](int depth  = 5) mutable {
  if (!isBDT) {
    cutBDTlow =0;
    cutBDThigh=0;
  }
      type = Form("%s:CC%d:%s", parser_symbol(type)[0].c_str(), getNomBkgO(state, (int) ptMin, (int) ptMax, cBinLow, cBinHigh), parser_symbol(type)[2].c_str());
  int ylim10 = (int) (rapMax*10);
  auto parsed = parser_symbol(type);
  std::string sig_func = parsed[0];
  std::string bkg_func = parsed[1];
  std::string fitdir = parsed[2];
  std::string name_fitmodel = "_"+sig_func+"_"+bkg_func;

  SetStyle();
       //////////////////////////////////////////////////////////////////
       std::string name_file_data = Form("%s/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f.root" ,workdir.Data(), train_state, ts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, cutQVP );
       std::cout << name_file_data << std::endl;
      TFile* file_DATAres_input = new TFile(name_file_data.c_str(), "OPEN");
 std::vector<std::pair<int, int> > cBinPair;
 cBinPair =	{{0,40}, {40, 100},  {100,181}, /*{0, 181} ,*/  }; 
 if(train_state==2) cBinPair = { {0,10}, {10,20}, {20,40}, {40,60}, {60,80}, {80,100}, {100,120}, {120, 140}, {140, 181} /*{0,181} */};	
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
    std::pair<double, double> res = prep_bdtval(-0.1, depth);
    cutBDTlow = res.first;
    std::cout << Form( "\n\n Bin : C%d-%d, PT%d-%d; BDT : %.6f ", cBinLow, cBinHigh, (int) ptMin, (int) ptMax, cutBDTlow) << std::endl;
    cutQVP= 0.00; //(!!! JUST FOR No BDT CONFIG !!!)
    ratio = res.second;
    sb_ratio = RooRealVar("ratio","",-1);
    type2 = Form("%s:CC%d:%s", parser_symbol(type2)[0].c_str(), getNomBkgO(state, (int) ptMin, (int) ptMax, cBinLow, cBinHigh), parser_symbol(type2)[2].c_str());
 	MassYieldFit_data(type2, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, xts, cutBDTlow, cutBDThigh, (Double_t[]) {map_keyval_2["sigma1S_1"].first, map_keyval_2["alpha"].first, map_keyval_2["n"].first, map_keyval_2["frac"].first, -0.15,-0.1,0.1,0.1}, (Double_t[]) {0.05, 0.5, 0.4, 0.05, -0.3, -0.3, -0.3,-0.3}, (Double_t[]) {-1, -1, -1, -1, 0.2, 0.1, 0.3,0.3}, 
         (std::map<string, params_vhl>) {
         {"frac2", {map_keyval_2["frac2"].first, 0, -1} }, 
         {"xNS", {map_keyval_2["x1S"].first,0,-1}}, 
         {"xNS_2", {map_keyval_2["x1S_2"].first,0,-1}},
         {"sigmaNS_1", { map_keyval_2["sigma1S_1"].first,0,-1}},
         {"mag", { 1, 0, 0 }},
        {"sb_ratio", { sb_ratio.getVal(), 0, 0}},
         });

       }
//     }
   }
 } 
};
  //##########################################EXECUTION CODE#########################################//

//Step1, First reference integrated bin fit.
double INTBIN_BDTLOW ;// =0.16;
INTBIN_BDTLOW = (global_step == -1 )  ?  0.1851 : 0.1802; 
train_state = 3;
state =3;
 //Sealed
 if(step == 1 || step == 99 || step == 11 || step == 31){
  for( auto ptpair : (std::vector<std::pair<double, double> >) {{0, 30}/*,{0, 6}, {6, 30}*/}){ 
    ptMin = ptpair.first;
    ptMax = ptpair.second;
    std::pair<double, double> res = prep_bdtval(-0.0, global_step);
    cutBDTlow = res.first;
    ratio = res.second;
    if(ptpair.first == 0 && ptpair.second == 30){ INTBIN_BDTLOW = res.first; }
    std::cout << "cutBDTlow, ratio: " << cutBDTlow << ", "<< ratio << std::endl;
//    METHOD_MCGCDATA(1);
  }
}



//Step2, Analysis bin fit
//Sealed
if(step ==1 || step == 99 || step ==12){
  ptMin = 0;
  ptMax = 30;
  cutBDTlow = INTBIN_BDTLOW;
  type2 = "CB3:CC2:DRFF" + bdt_seg;
  fixfit(global_step);
  cutBDTlow = INTBIN_BDTLOW;
  cBinLow = 0;
  cBinHigh = 181;
  type2 = "CB3:CC2:DR2FF" + bdt_seg;
  fixfit(global_step);
  cutBDTlow = INTBIN_BDTLOW;
  cBinLow = 0;
  cBinHigh = 181;
  type2 = "CB3:CC2:FF" + bdt_seg;
  fixfit(global_step);
}


INTBIN_BDTLOW = (global_step == -1 )  ?  0.2738 : 0.2645; 
train_state = 2;
state =2;
 //Sealed
if(step ==2 || step ==99 || step == 21 || step == 31){
  cBinLow = 0;
  cBinHigh = 181;
  for( auto ptpair : (std::vector<std::pair<double, double> >) {/*{0, 30}, */{0, 4}, {4, 9},{9, 30} } ){ 
    ptMin = ptpair.first;
    ptMax = ptpair.second;
    std::pair<double, double> res = prep_bdtval(-0.0, global_step);
    cutBDTlow = res.first;
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
  dbg();
  cutBDTlow = INTBIN_BDTLOW;
  type2 = "CB3:CC2:DRFF" + bdt_seg;
  fixfit(global_step);
  dbg();
  cutBDTlow = INTBIN_BDTLOW;
  cBinLow = 0;
  cBinHigh = 181;
  type2 = "CB3:CC2:DR2FF" + bdt_seg;
  fixfit(global_step);
  dbg();
  cutBDTlow = INTBIN_BDTLOW;
  cBinLow = 0;
  cBinHigh = 181;
  type2 = "CB3:CC2:FF" + bdt_seg;
  fixfit(global_step);
  dbg();
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
//  std::pair<double, double> res = prep_bdtval(-0.1, 999);
//  res = prep_bdtval(-0.1, -103);
  
};

if(step == 4){
  std::string type_ = "CB3:CC4:FF"+ bdt_seg;
      type_ = Form("%s:CC%d:%s", parser_symbol(type_)[0].c_str(), getNomBkgO(state, (int) ptMin, (int) ptMax, cBinLow, cBinHigh), parser_symbol(type_)[2].c_str());
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
  MassYieldFit_BDT_MC_CB3(ts, "", fname, ptMin, ptMax, rapMin, rapMax, MupT, Trig, cBinLow, cBinHigh, train_state, state, fixvar, swflag, cutQVP, -1, cutBDThigh);
  string _tpye = type_;
  double bl = cutBDTlow;
    TFile* file_MCres_input = new TFile(Form("Yield/Yield_%ld_CB3_%dS_train%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root", ts, (int) state ,train_state,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), bl, cutBDThigh, cutQVP,(int) fixvar), "OPEN");
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

     MassYieldFit_data(type_, train_state, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, bl, cutBDThigh, (Double_t[]) {mean_sigma1S1, map_keyval["alpha"].first, map_keyval["n"].first, map_keyval["frac"].first, -0.02,0.0,0.1,0.1, -0.1}, (Double_t[]) {0.11, 0.5, 0.4, 0.05, -0.4, -0.5, -0.5,-0.3, -0.3}, (Double_t[]) {-1,-1,-1,-1, 0.1, 0.2, 0.3,0.3, 0.3}, 
       (std::map<string, params_vhl>) {
       {"frac2", {0.3, 0, -1} }, 
       {"xNS", {0.3,0,-1}}, 
       {"xNS_2", {0.5,0,-1}},
       {"sigmaNS_1", { 0.21 ,0,-1}},
       {"mag", { 0, 0, 0 }},
       {"sb_ratio", { -1, 0, 0}},
       });
}
};
