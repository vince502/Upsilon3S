#define _TS 10000000016
#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#   include "../LLR_CCorder_9999999999.h"
#   define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
#   include "../LLR_CCorder_10000000016.h"
#   define getNomBkgO getNomBkgO_10000000016
#endif

#if _TS == 10000000003 && __has_include("../LLR_CCorder_10000000003.h")
#   include "../LLR_CCorder_10000000003.h"
#   define getNomBkgO getNomBkgO_10000000003
#endif

#if _TS != 9999999999
#   define ana_bm ana_bm_comb
#endif

#include "plot_wr_helper.cxx"
#include "../Systematics/GOF_test.cxx"

RooRealVar effratio(ana_bins ab, long ts = 10000000016){
	string fittype = (strcmp(ab.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	string bkgtype = AICGOF_test(ab)[0].second;
	string type = Form("CB3:%s:%s", bkgtype.c_str(), fittype.c_str());
	double bl = Get_BDT(ts, ab);
//	std::cout << "[bl, type]: " <<bl << ", " << type.c_str()  << std::endl;
	auto bp = new binplotter(type, ts, 2.4, ab.pl,  ab.ph, ab.cl, ab.ch, 0., bl, 1, ab.bpl, ab.bph, ab.train_state, ab.state, false, false);
	RooRealVar _yacc_2s = upsi::getacceptance(ab.pl, ab.ph, -2.4,2.4, 3.5, 2);
	RooRealVar _yacc_3s = upsi::getacceptance(ab.pl, ab.ph, -2.4,2.4, 3.5, 3);
	auto _yeff_2s = bp->get_eff(2);
	auto _yeff_3s = bp->get_eff(3);
	RooRealVar theratio("ratio", "", 0);
	std::cout << Form("[mc ratio]: eff, acc 2,3S : %.4f, %.4f, %.4f, %.4f",_yeff_2s.first, _yacc_2s.getVal(), _yeff_3s.first, _yacc_3s.getVal()) << std::endl;
	double _ratio = (  (_yacc_2s.getVal()) * (_yeff_2s.first) ) / ( (_yacc_3s.getVal()) * (_yeff_3s.first) );
//	double _ratio = (  (_yacc_2s.getVal())  ) / ( (_yacc_3s.getVal()) );
	theratio.setVal(1/_ratio);
	std::cout << "ratio: " << theratio.getVal() << std::endl;
	return theratio;
}

void MC2MC3ratio(){
	plot_wr_helper("MCratio_220121.root", effratio, 10000000016);	
	
}
