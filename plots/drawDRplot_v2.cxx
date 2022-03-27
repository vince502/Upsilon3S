//#define _TS 9999999999
//#define _TS 10000000016
//#define _TS 100019111111
#define _TS 200019111111
#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#   include "../LLR_CCorder_9999999999.h"
#   define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
#   include "../LLR_CCorder_10000000016.h"
#   define getNomBkgO getNomBkgO_10000000016
#endif

#if _TS == 100019111111 && __has_include("../LLR_CCorder_100019111111.h")
#   include "../LLR_CCorder_100019111111.h"
#   define getNomBkgO getNomBkgO_100019111111
#	define ana_bm ana_bm_comb
#endif

#if _TS == 200019111111 && __has_include("../LLR_CCorder_200019111111.h")
#   include "../LLR_CCorder_200019111111.h"
#   define getNomBkgO getNomBkgO_200019111111
#	define ana_bm ana_bm_comb_ub
#endif

#if _TS == 10000000003 && __has_include("../LLR_CCorder_10000000003.h")
#   include "../LLR_CCorder_10000000003.h"
#   define getNomBkgO getNomBkgO_10000000003
#endif

//#if _TS != 9999999999
//#	define ana_bm ana_bm_comb
//#endif


#include "plot_wr_helper.cxx"
#include "measurement.cxx"

void drawDRplot_v2(){
	long ts = _TS;
	plot_wr_helper(Form("DR_%ld_aux.root",ts),getDRValue, ts);
};
