#pragma once
#define FITRESLIB_H 
#include <string>
#include "TString.h"
#include ".workdir.h"
#include "fitter.h"
double __FITRESLATEST = 10;
struct BDTstdFitOpt{
	string mupt = "3p5";
	string trig = "S13";
	bool swflag = false;
	bool isBDT = true;
	bool fixvar = false;
	double rl = 2.4;
	double rh = 2.4;
};

string GetFit();
string GetFit(int version, bool isMC, string type, int train_state, int target_state, int pl, int ph, double rl, double rh, string mupt, string trig, bool swflag, int cl, int ch, double cutqvp, bool isBDT, long ts, double bl, double bh, int bpl, int bph, bool fixvar, string aux){
	//Check Once Again the NO-BDT fits (with other paramters opened) match timestamp nominal
	if( version > 9 && bl == -1.0000){ 
		if( ts != 9999999999) { 
			std::cout << "[GetFit] Warning! Requested result timestamp does not match, maybe check psets?" << std::endl;
			ts = 9999999999;
		}
		bh = 1.0000; bpl = 0.0000; bph = 0.0000; train_state = 0; target_state = 0; 
	}
	std::string wanted_string;
	//Parse type string
	auto parsed = parser_symbol(type);
	string signal_model = parsed[0]; 
	string fitdir, name_fitmodel;
	if( !isMC ){
	   fitdir = parsed[2];
	   name_fitmodel = "_" +parsed[0] +"_"+ parsed[1];
	}
	//Version 1 : Preliminary study on BDT configuration
	if( version == 1 ){
		if( !isMC ) wanted_string = Form("%s/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f%s.root" ,workdir.Data(), ts, fitdir.c_str(), name_fitmodel.c_str(), pl, ph,  (int) (rl*10), (int) (rh*10),  cl, ch, mupt.c_str(), trig.c_str(), (int) swflag, (int) isBDT, bl, bh, bpl, bph, cutqvp, aux.c_str() );
		if( isMC ) wanted_string = Form("%s/Yield_%ld_%s_%dS_pt_%d-%d_rap_-%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_%d.root",workdir.Data(), ts, signal_model.c_str(),train_state , pl, ph, (int)(rl*10), (int)(rh*10), cl, ch, mupt.c_str(), trig.c_str(), bl, bh, bpl, bph, cutqvp,(int) fixvar);
	}

	//Version 9 : Mostly Nominal Results
	if( version == 9 ){
//		Yield_9999999999_CB2G_2S_train2S_pt_0-30_rap_-24-24_cBin_0-181_MupT3p5_S13_BDT_0.2689-1.0000_vp_0.0000_MC_0.root
//		Yield_3S_9999999998_DRFF_CB3_CC1_pt_0-30_rap_-24-24_cbin_100-181_MupT3p5_Trig_S13_SW0_BDT1_cut0.1664-1.0000_vp0.0000.root
		if( isMC ) wanted_string = Form("%s/Yield_%ld_%s_%dS_train%dS_pt_%d-%d_rap_-%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d.root",workdir.Data(), ts, signal_model.c_str(), target_state, train_state, pl, ph, (int) (rl*10), (int) (rh*10), cl, ch, mupt.c_str(), trig.c_str(), bl, bh, cutqvp, (int) fixvar);
		if( !isMC ) wanted_string = Form("%s/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f%s.root",workdir.Data(),train_state, ts, fitdir.c_str(), name_fitmodel.c_str(), pl, ph, (int) (rl*10), (int) (rh*10), cl, ch, mupt.c_str(), trig.c_str(), (int) swflag, (int) isBDT, bl, bh, cutqvp, aux.c_str());
	}


	//Version 10 : Post Pre-Approval jobs v1
	if( version == 10 ){
		if( isMC ) wanted_string = Form("%s/Yield/Yield_%ld_%s_%dS_train%dS_pt_%d-%d_rap_-%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_%d.root",workdir.Data(), ts, signal_model.c_str(), target_state, train_state ,pl, ph, (int)(rl*10), (int)(rh*10), cl, ch,  mupt.c_str(), trig.c_str(), bl, bh, bpl, bph, cutqvp,(int) fixvar);
		if( !isMC ) wanted_string = Form("%s/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f%s.root" ,workdir.Data(), train_state, ts, fitdir.c_str(), name_fitmodel.c_str(), pl, ph,  (int) (rl*10), (int) (rh*10), cl, ch, mupt.c_str(), trig.c_str(), (int) swflag, (int) isBDT, bl, bh, bpl, bph, cutqvp, aux.c_str() );
	}
	return wanted_string;
};
string GetFit(int version, bool isMC, string type, long ts, int train_state, int target_state, int pl, int ph, int cl, int ch, double bl, double bh, int bpl, int bph, double cutqvp, string aux){
	BDTstdFitOpt x;
	return GetFit(version, isMC, type, train_state, target_state, pl, ph, x.rl, x.rh, x.mupt, x.trig, x.swflag, cl, ch, cutqvp, x.isBDT, ts, bl, bh, bpl, bph, x.fixvar, aux);
}


string GetEffNum(int version, long ts, int train_state, int target_state, int bpl, int bph, double yl, double yh, double muptcut, double masslow, double masshigh, int clow, int chigh, double vcut, bool istnp, bool isptw ){
	string wanted_string_eff;
	if( version == 10 ){
		wanted_string_eff = Form("%s/BDT/EffCalc/mc_eff_BDT_%dS_train_%dS_bdtpt%d_%d_%ld_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_fix_test.root", workdir.Data(), target_state, train_state, bpl, bph, ts, yl, yh, muptcut, masslow, masshigh, clow, chigh, vcut, istnp, isptw);
	}
	return wanted_string_eff;
};


#if defined BININFO_H
#endif
