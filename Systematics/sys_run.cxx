#pragma once
#define __SYSDEF__
//#define _TS 9999999999
#define _TS 10000000002
//#define _TS 10000000003

#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#	include "../LLR_CCorder_9999999999.h"
#	define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000002 && __has_include("../LLR_CCorder_10000000002.h")
#	include "../LLR_CCorder_10000000002.h"
#	define getNomBkgO getNomBkgO_10000000002
#	define ana_bm ana_bm_comb
#endif

#if _TS == 10000000003 && __has_include("../LLR_CCorder_10000000003.h")
#	include "../LLR_CCorder_10000000003.h"
#	define getNomBkgO getNomBkgO_10000000003
#	define ana_bm ana_bm_comb
#endif

#include "GOF_test.cxx"
