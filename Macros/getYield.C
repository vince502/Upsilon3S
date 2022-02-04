#define _TS 10000000016
#include "../LLR_CCorder_10000000016.h"
#define getNomBkgO getNomBkgO_10000000016
#define ana_bm ana_bm_comb
#include "../Systematics/GOF_test.cxx"
#include "../BDT/yield_eff_signif.cxx"
#include "../upsilonAna.h"

void getYield(){
	binplotter bp;
	binplotter bps1;
	binplotter bps2;
	std::string output;
	long ts = _TS;
	
	for(auto abm : ana_bm){
		for(auto item : abm.second){
			string fittype = (strcmp(item.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
			auto AICres = AICGOF_test(item);
			string bkgtype_nom = AICres[0].second;
			string type_nom = Form("CB3:%s:%s", bkgtype_nom.c_str(), fittype.c_str() );
			string type_bdtup = Form("CB3:%s:%sbdtup", bkgtype_nom.c_str(), fittype.c_str() );
			string type_bdtdo = Form("CB3:%s:%sbdtdown", bkgtype_nom.c_str(), fittype.c_str() );
			double bdt = Get_BDT(10000000016, item);
    		auto getdiff = [=](){
    		    auto sb_ratio = get_eff_acc_v2(type_nom, ts, 2.4, (double) item.pl, (double) item.ph, item.cl, item.ch, bdt, 1.0, item.bpl, item.bph, item.train_state, 1, item.state, false);
    		    return Get_BDTTD(ts, item, sb_ratio.getVal());
    		};
    		auto res = getdiff();

			bp = binplotter(type_nom, 10000000016, 2.4, item.pl, item.ph, item.cl, item.ch, 0, bdt, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			bps1 = binplotter(type_bdtup, 10000000016, 2.4, item.pl, item.ph, item.cl, item.ch, 0, res.second, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			bps2 = binplotter(type_bdtdo, 10000000016, 2.4, item.pl, item.ph, item.cl, item.ch, 0, res.first, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			RooRealVar yield = bp.get_yield(item.state);
			RooRealVar yieldsys1 = bps1.get_yield(item.state);
			RooRealVar yieldsys2 = bps2.get_yield(item.state);

//			double acc = upsi::getacceptance(item.pl, item.ph, -2.4, 2.4, 3.5, item.state).getVal();
//			double eff = bp.get_eff(item.state, false).first;
//			output += Form("%d-%d, %d-%d, %dS:		 	%.4f & %.3f & %.3f\n", item.centl, item.centh, item.pl, item.ph, item.state, bdt, eff, acc); 
//			output += Form("%d-%d, %d-%d, %dS: 	%.4f & %.3f & %.3f   &  %.3f $\\pm$ %.3f down \n", item.centl, item.centh, item.pl, item.ph, item.state, bdt, eff, acc, yield.getVal(), yield.getError()); 
			output += Form("%2.f-%2.f, %2.f-%2.f, %dS: 	%.4f    %.4f    & |||       up : %.3f $\\pm$ %.3f    |||     down : %.3f $\\pm$ %.3f \n", (double) item.centl, (double) item.centh, (double) item.pl, (double) item.ph, item.state, res.second, res.first, yieldsys1.getVal(), yieldsys1.getError(), yieldsys2.getVal(), yieldsys2.getError()); 
//			if(item.state == 3)output += Form("%d-%d, %d-%d, %dS: 	%.4f & & %.3f \n", item.cl, item.ch, item.pl, item.ph, item.state, bdt, eff);
 // 		std::cout << Form("%d-%d, %d-%d, %dS: 	%.3f $\\pm$ %.3f", item.cl, item.ch, item.pl, item.ph, item.state, yield.getVal(), yield.getError()) << std::endl;
		}
	}

std::cout << output ;
}
