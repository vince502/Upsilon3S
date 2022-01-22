#define _TS 10000000016
#include "../LLR_CCorder_10000000016.h"
#define getNomBkgO getNomBkgO_10000000016
#define ana_bm ana_bm_comb
#include "../Systematics/GOF_test.cxx"
#include "../BDT/yield_eff_signif.cxx"
#include "../upsilonAna.h"

void getYield(){
	binplotter bp;
	std::string output;
	
	for(auto abm : ana_bm){
		for(auto item : abm.second){
			string fittype = (strcmp(item.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
			auto AICres = AICGOF_test(item);
			string bkgtype_nom = AICres[0].second;
			string type_nom = Form("CB3:%s:%s", bkgtype_nom.c_str(), fittype.c_str() );
			double bdt = Get_BDT(10000000016, item);
			bp = binplotter(type_nom, 10000000016, 2.4, item.pl, item.ph, item.cl, item.ch, 0, bdt, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			RooRealVar yield = bp.get_yield(item.state);

			double acc = upsi::getacceptance(item.pl, item.ph, -2.4, 2.4, 3.5, item.state).getVal();
			double eff = bp.get_eff(item.state, false).first;
			output += Form("%d-%d, %d-%d, %dS:		 	%.4f & %.3f & %.3f\n", item.centl, item.centh, item.pl, item.ph, item.state, bdt, eff, acc); 
//			output += Form("%d-%d, %d-%d, %dS: 	%.4f & %.3f & %.3f   &   %.3f $\\pm$ %.3f \n", item.centl, item.centh, item.pl, item.ph, item.state, bdt, eff, acc, yield.getVal(), yield.getError()); 
//			if(item.state == 3)output += Form("%d-%d, %d-%d, %dS: 	%.4f & & %.3f \n", item.cl, item.ch, item.pl, item.ph, item.state, bdt, eff);
 // 		std::cout << Form("%d-%d, %d-%d, %dS: 	%.3f $\\pm$ %.3f", item.cl, item.ch, item.pl, item.ph, item.state, yield.getVal(), yield.getError()) << std::endl;
		}
	}

std::cout << output ;
}
