#define _TS 100019111111
//#include "../LLR_CCorder_10000000016.h"
//#define getNomBkgO getNomBkgO_10000000016

#include "../LLR_CCorder_200019111111.h"
#define getNomBkgO getNomBkgO_200019111111

#if _TS == 100019111111
	#define ana_bm ana_bm_comb
#endif

#if _TS == 200019111111
	#define ana_bm ana_bm_comb_ub
#endif
#include "../Systematics/GOF_test.cxx"
#include "../BDT/yield_eff_signif.cxx"
#include "../upsilonAna.h"

#define Pmode 0

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
			double bdt = Get_BDT(ts_alias(_TS), item);
    		auto getdiff = [=](){
    		    auto sb_ratio = get_eff_acc_v2(type_nom, ts, 2.4, (double) item.pl, (double) item.ph, item.cl, item.ch, bdt, 1.0, item.bpl, item.bph, item.train_state, 1, item.state, false);
    		    return Get_BDTTD(ts, item, sb_ratio.getVal());
    		};
    		auto res = getdiff();

			bp = binplotter(type_nom, _TS, 2.4, item.pl, item.ph, item.cl, item.ch, 0, bdt, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			bps1 = binplotter(type_bdtup, _TS, 2.4, item.pl, item.ph, item.cl, item.ch, 0, res.second, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			bps2 = binplotter(type_bdtdo, _TS, 2.4, item.pl, item.ph, item.cl, item.ch, 0, res.first, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			RooRealVar yield =		 bp.get_yield(1);//item.state);
			RooRealVar yieldsys1 = bps1.get_yield(1);//item.state);
			RooRealVar yieldsys2 = bps2.get_yield(1);//item.state);

			double acc=0; 

			double eff=0;
			if(Pmode == 0){
				acc = upsi::getacceptance(item.pl, item.ph, -2.4, 2.4, 3.5, item.state).getVal();
				eff = bp.get_eff(item.state, false).first;
			}
//			output += Form("%d-%d, %d-%d, %dS:		 	%.4f & %.3f & %.3f\n", item.centl, item.centh, item.pl, item.ph, item.state, bdt, eff, acc); 
//			output += Form("%d-%d, %d-%d, %dS: 	%.4f & %.3f & %.3f   &  %.3f $\\pm$ %.3f down \n", item.centl, item.centh, item.pl, item.ph, item.state, bdt, eff, acc, yield.getVal(), yield.getError()); 
			if(item.bintype == kPt){
					if(Pmode == 0 )output += Form("\033[0;31m%d-%d, %d-%d, %dS: 	%.4f & %.2f & %.2f   &  %.2f $\\pm$ %.2f down \033[0m\n", item.centl, item.centh, item.pl, item.ph, item.state, bdt, eff, acc, yield.getVal(), yield.getError()); 
  					if(Pmode == 1 )output += Form("\033[0;31m%2.f-%2.f, %2.f-%2.f, %dS: |||       Nominal : %.1f $\\pm$ %.1f  \033[0m\n", (double) item.centl, (double) item.centh, (double) item.pl, (double) item.ph, item.state, yield.getVal(), yield.getError()); 
					if(Pmode == 2 )output += Form("\033[0;31m%2.f-%2.f, %2.f-%2.f, %dS: 	%.4f    %.4f    & |||       up : %.1f $\\pm$ %.1f    |||     down : %.1f $\\pm$ %.1f \033[0m\n", (double) item.centl, (double) item.centh, (double) item.pl, (double) item.ph, item.state, res.second, res.first, yieldsys1.getVal(), yieldsys1.getError(), yieldsys2.getVal(), yieldsys2.getError()); 
   			}
  			if(item.bintype == kCent){
					if(Pmode == 0 )output += Form("\033[0;32m%d-%d, %d-%d, %dS: 	%.4f & %.2f & %.2f   &  %.2f $\\pm$ %.2f down \033[0m\n", item.centl, item.centh, item.pl, item.ph, item.state, bdt, eff, acc, yield.getVal(), yield.getError()); 
  					if(Pmode == 1 )output += Form("\033[0;32m%2.f-%2.f, %2.f-%2.f, %dS: |||       Nominal : %.1f $\\pm$ %.1f  \033[0m\n", (double) item.centl, (double) item.centh, (double) item.pl, (double) item.ph, item.state, yield.getVal(), yield.getError()); 
					if(Pmode == 2 )output += Form("\033[0;32m%2.f-%2.f, %2.f-%2.f, %dS: 	%.4f    %.4f    & |||       up : %.1f $\\pm$ %.1f    |||     down : %.1f $\\pm$ %.1f \033[0m\n", (double) item.centl, (double) item.centh, (double) item.pl, (double) item.ph, item.state, res.second, res.first, yieldsys1.getVal(), yieldsys1.getError(), yieldsys2.getVal(), yieldsys2.getError()); 
  			}
  			if(item.bintype == kInt){
					if(Pmode == 0 )output += Form("\033[0;34m%d-%d, %d-%d, %dS: 	%.4f & %.2f & %.2f   &  %.2f $\\pm$ %.2f down \033[0m\n", item.centl, item.centh, item.pl, item.ph, item.state, bdt, eff, acc, yield.getVal(), yield.getError()); 
  					if(Pmode == 1 )output += Form("\033[0;34m%2.f-%2.f, %2.f-%2.f, %dS: |||       Nominal : %.1f $\\pm$ %.1f  \033[0m\n", (double) item.centl, (double) item.centh, (double) item.pl, (double) item.ph, item.state, yield.getVal(), yield.getError()); 
					if(Pmode == 2 )output += Form("\033[0;34m%2.f-%2.f, %2.f-%2.f, %dS: 	%.4f    %.4f    & |||       up : %.1f $\\pm$ %.1f    |||     down : %.1f $\\pm$ %.1f \033[0m\n", (double) item.centl, (double) item.centh, (double) item.pl, (double) item.ph, item.state, res.second, res.first, yieldsys1.getVal(), yieldsys1.getError(), yieldsys2.getVal(), yieldsys2.getError()); 
   			}
   		
//			output += Form("%2.f-%2.f, %2.f-%2.f, %dS: 	%.4f    %.4f    & |||       up : %.3f $\\pm$ %.3f    |||     down : %.3f $\\pm$ %.3f \n", (double) item.centl, (double) item.centh, (double) item.pl, (double) item.ph, item.state, res.second, res.first, yieldsys1.getVal(), yieldsys1.getError(), yieldsys2.getVal(), yieldsys2.getError()); 
//			if(item.state == 3)output += Form("%d-%d, %d-%d, %dS: 	%.4f & & %.3f \n", item.cl, item.ch, item.pl, item.ph, item.state, bdt, eff);
 // 		std::cout << Form("%d-%d, %d-%d, %dS: 	%.3f $\\pm$ %.3f", item.cl, item.ch, item.pl, item.ph, item.state, yield.getVal(), yield.getError()) << std::endl;
		}
	}

std::cout << output ;
}
