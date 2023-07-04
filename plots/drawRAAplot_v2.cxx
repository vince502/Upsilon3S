//#define _TS 9999999999
//#define _TS 10000000016
//#define _TS 200019111111
#define _TS 2100019111111
//#define _TS 400019111111
#if _TS == 9999999999 && __has_include("../LLRHeader/LLR_CCorder_9999999999.h")
#   include "../LLRHeader/LLR_CCorder_9999999999.h"
#   define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLRHeader/LLR_CCorder_10000000016.h")
#   include "../LLRHeader/LLR_CCorder_10000000016.h"
#   define getNomBkgO getNomBkgO_10000000016
#endif

#if _TS == 100019111111 && __has_include("../LLRHeader/LLR_CCorder_100019111111.h")
#   include "../LLRHeader/LLR_CCorder_100019111111.h"
#	define ana_bm ana_bm_comb
#   define getNomBkgO getNomBkgO_100019111111
#endif

#if _TS == 200019111111 && __has_include("../LLRHeader/LLR_CCorder_200019111111.h")
#   include "../LLRHeader/LLR_CCorder_200019111111.h"
#	define ana_bm ana_bm_comb_ub
#   define getNomBkgO getNomBkgO_200019111111
#endif

#if _TS == 2100019111111 && __has_include("../LLRHeader/LLR_CCorder_2100019111111.h")
#   include "../LLRHeader/LLR_CCorder_2100019111111.h"
#	define ana_bm ana_bm_comb_ub_ib
#   define getNomBkgO getNomBkgO_2100019111111
#endif

#if _TS == 400019111111 && __has_include("../LLRHeader/LLR_CCorder_200019111111.h")
#   include "../LLRHeader/LLR_CCorder_400019111111.h"
#	define ana_bm ana_bm_comb_ub
#   define getNomBkgO getNomBkgO_400019111111
#endif

#if _TS == 10000000003 && __has_include("../LLRHeader/LLR_CCorder_10000000003.h")
#   include "../LLRHeader/LLR_CCorder_10000000003.h"
#   define getNomBkgO getNomBkgO_10000000003
#endif

//#if _TS != 9999999999
//#	define ana_bm ana_bm_comb
//#endif


#include "plot_wr_helper.cxx"
#include "measurement.cxx"

// Centrality RAA function
//////////////////////////////////////////////////////////////////////////////

void drawRAAplot_v2(int state =3, double bdt_fix = -2, int shift =0){
	long ts = _TS;
//	plot_wr_helper(Form("RAA_%ld_NOSF.root",ts), getRAAValue, ts);
//	plot_wr_helper(Form("RAA_%ld_only2S.root",ts), getRAAValue, ts, 2);
//	plot_wr_helper_aux(Form("RAA_%ld_ptcheck.root",ts), getRAAValue, ts);
//	plot_wr_helper_aux3(Form("RAA_%ld_1S_result_2Sbin.root",ts), getRAAValue, ts);
//	plot_wr_helper_aux3_2(Form("RAA_%ld_1S_result_2Sbin_2Snominal.root",ts), getRAAValue, ts);
	plot_wr_helper_aux3_3(Form("CS_%ld_result.root",ts), getRAAValue, ts);
//	plot_wr_helper(Form("RAA_%ld.root",ts), getRAAValue, ts);

};
