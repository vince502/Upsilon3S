#pragma once

#define ISDR 0
#define __SYSDEF__
//#define _TS 9999999999
#define _TS 10000000016

#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#	include "../LLR_CCorder_9999999999.h"
#	define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
#	include "../LLR_CCorder_10000000016.h"
#	define getNomBkgO getNomBkgO_10000000016
#	define ana_bm ana_bm_comb
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
#include "SEFFVariUnc.cxx"
#include "BDTPropVariUnc.cxx"
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



void sys_run(){
//	NominalBKG();
//	BkgVariUnc();
	auto ab = ana_bm["3c"][0];
	auto res = AICGOF_test(ab);
}
