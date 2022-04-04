#pragma once

#define ISDR 0
#define __SYSDEF__
//#define _TS 9999999999
//#define _TS 10000000016
#define _TS 200019111111

#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#   include "../LLR_CCorder_9999999999.h"
#   define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
#   include "../LLR_CCorder_10000000016.h"
#   define getNomBkgO getNomBkgO_10000000016
#   define ana_bm ana_bm_comb
#endif

#if _TS == 200019111111 && __has_include("../LLR_CCorder_200019111111.h")
#   include "../LLR_CCorder_200019111111.h"
#   define getNomBkgO getNomBkgO_200019111111
#   define ana_bm ana_bm_comb_ub
#endif

#include "../BDT/bininfo.h"
#include "../fitreslib.h"
#include "../Systematics/GOF_test.cxx"

long ts = 200019111111;

void mv_yield(){
	string target_dir = "/home/vince402/shared/Upsilon3S_PostPreApp/Yield_nominal";
	for( auto abv : ana_bm){
		for( auto ab : abv.second){
			string fit_type = (ab.bintype == kCent) ? "FF" : "GC";
			string sig_pdf = "CB3";
			string bkg_pdf = AICGOF_test(ab)[0].second;
			string type = Form("%s:%s:%s",sig_pdf.c_str(), bkg_pdf.c_str(), fit_type.c_str() );
			double bl = Get_BDT(ts_alias(ts), ab);
			string filename_data = GetFit(__FITRESLATEST, false, type, ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1, ab.bpl, ab.bph, 0.00, "");
			string data_newname = Form("fit_data_%dS_pt_%d_%d_cent_%d_%d.root", ab.state, ab.pl, ab.ph, ab.centl, ab.centh);
			string filename_mc = GetFit(__FITRESLATEST, true, type, ts_alias(ts), ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1, ab.bpl, ab.bph, 0.00, "");
			string mc_newname = Form("fit_mc_%dS_pt_%d_%d_cent_%d_%d.root", ab.state, ab.pl, ab.ph, ab.centl, ab.centh);
			system(Form("cp %s %s/%s", filename_data.c_str(), target_dir.c_str(), data_newname.c_str() ) );
			system(Form("cp %s %s/%s", filename_mc.c_str(), target_dir.c_str(), mc_newname.c_str() ) );
		}
	}

}
