#pragma once

#define ISDR 0
#define __SYSDEF__
//#define _TS 9999999999
//#define _TS 10000000016
//#define _TS 20000000000
//#define _TS 100019111111
#define _TS 200019111111

#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#	include "../LLR_CCorder_9999999999.h"
#	define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
#	include "../LLR_CCorder_10000000016.h"
#	define getNomBkgO getNomBkgO_10000000016
#	define ana_bm ana_bm_comb
#endif

#if _TS == 100019111111 && __has_include("../LLR_CCorder_100019111111.h")
#	include "../LLR_CCorder_100019111111.h"
#	define getNomBkgO getNomBkgO_100019111111
#	define ana_bm ana_bm_comb
#endif

#if _TS == 200019111111 && __has_include("../LLR_CCorder_200019111111.h")
#	include "../LLR_CCorder_200019111111.h"
#	define getNomBkgO getNomBkgO_200019111111
#	define ana_bm ana_bm_comb_ub
#endif


bool isDR = true;
const string labDR = (isDR) ? "_DR" : "" ;

int cross_state(int state){
	if( state == 3) return 2;
	if( state == 2) return 3;
	else return state;
}

#include "GOF_test.cxx"

#include "NominalBKG.cxx"
#include "BkgVariUnc.cxx"
//#include "SEFFVariUnc.cxx"
//#include "BDTPropVariUnc.cxx"
#include "BDTDiffVariUnc.cxx"
#include "ACCVariRMS_Unc.cxx"
#include "TNPUnc.cxx"
#include "DPTUnc.cxx"
#include "CENTVariUnc.cxx"
#include "SigParVariUnc.cxx"
#include "SigPdfVariUnc.cxx"
#include "systematic_ups_v2.cxx"
#include "systematic_ups_DR_v2.cxx"
#include "CorrectionUnc.cxx"

#include "./checkGCrange.C"
#include "BkgVariUnc1S.cxx"
#include "systematic_ups_v2_aux_1SBKG.cxx"
//#include "_BkgDiscreteProfile.cxx"
//#include "_DiscreteProfile.cxx"
//#include "_DiscreteProfileNLL.cxx"
//#include "_DiscreteProfileNLL2.cxx"
//#include "_DiscreteProfile_2POI.cxx"


//void sys_run(){};

void sys_run(){
//	NominalBKG();
//	BkgVariUnc();
	auto ab = ana_bm["3c"][0];
//	auto res = AICGOF_test(ab);

//	auto res = _DiscreteProfileNLL2(ab);
}
//
//void sys_run(int mode){
////	NominalBKG();
////	BkgVariUnc();
////	auto res = AICGOF_test(ab);
//	if( mode ==1){
//		for( auto ab : ana_bm["2c"]){
//			if( ab.cl == 0){
//				auto res = _DiscreteProfile(ab);
//			}
//		}
//	}
//	if( mode ==2){
//		for( auto ab : ana_bm["3c"]){
//			if( ab.cl == 0){
//				auto res = _DiscreteProfile(ab);
//			}
//		}
//	}
//	if( mode ==3){
//		for( auto ab : ana_bm["2p"]){
//			if( ab.bpl == 0){
//				auto res = _DiscreteProfile(ab);
//			}
//		}
//	}
//	if( mode ==4){
//		for( auto ab : ana_bm["3p"]){
//			if( ab.bpl  == 0){
//				auto res = _DiscreteProfile(ab);
//			}
//		}
//	}
//
//
//}
