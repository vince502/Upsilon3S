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

void sys_run(){
	NominalBKG();
	BkgVariUnc();
}
