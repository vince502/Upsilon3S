#define _TS 200019111111
//#include "../LLR_CCorder_10000000016.h"
//#define getNomBkgO getNomBkgO_10000000016

#include "../LLR_CCorder_200019111111.h"
#define getNomBkgO getNomBkgO_200019111111

#define ana_bm ana_bm_comb_ub
#include "../Systematics/GOF_test.cxx"
#include "../BDT/yield_eff_signif.cxx"
#include "../upsilonAna.h"

#define Pmode 2

void getYieldblindCMP(ana_bins ab){
	binplotter bp;
	binplotter bps1;
	binplotter bps2;
	std::string output;
	long ts = _TS;
	
			string fittype = (strcmp(item.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
			auto AICres = AICGOF_test(item);
			string bkgtype_nom = AICres[0].second;
			string type_nom = Form("CB3:%s:%s", bkgtype_nom.c_str(), fittype.c_str() );
			string type_bdtup = Form("CB3:%s:%sbdtup", bkgtype_nom.c_str(), fittype.c_str() );
			string type_bdtdo = Form("CB3:%s:%sbdtdown", bkgtype_nom.c_str(), fittype.c_str() );
			double bdt = Get_BDT(ts_alias(_TS), item);
    		auto getdiff = [=](){
    		    auto sb_ratio = get_eff_acc_v2(type_nom, ts, 2.4, (double) item.pl, (double) item.ph, item.cl, item.ch, bdt, 1.0, item.bpl, item.bph, item.train_state, 1, item.state, false);
    		    return Get_BDTTD(ts, item, sb_ratio.getVal());
    		};
    		auto res = getdiff();

			bp = binplotter(type_nom, _TS, 2.4, item.pl, item.ph, item.cl, item.ch, 0, bdt, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			bps1 = binplotter(type_nom, ts_alias(_TS), 2.4, item.pl, item.ph, item.cl, item.ch, 0, bdt, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
i//			bps1 = binplotter(type_bdtup, _TS, 2.4, item.pl, item.ph, item.cl, item.ch, 0, res.second, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			bps2 = binplotter(type_bdtdo, _TS, 2.4, item.pl, item.ph, item.cl, item.ch, 0, res.first, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			RooRealVar yield = bp.get_yield(item.state);
			RooRealVar yieldsys1 = bps1.get_yield(item.state);
//			RooRealVar yieldsys2 = bps2.get_yield(item.state);
	return std::make_pair(yield, yieldsys1);
}
