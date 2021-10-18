#include "../BDT/yield_eff_signif.cxx"
#include "../upsilonAna.h"

void getYield(){
  binplotter bp;
  std::string output;
  for(auto abm : ana_bm){
    for(auto item : abm.second){
    bp = binplotter(item);
    RooRealVar yield = bp.get_yield(item.state);
    double bdt = Get_BDT(9999999999, item.state, item.pl, item.ph, item.cl, item.ch);
    double acc = upsi::getacceptance(item.pl, item.ph, -2.4, 2.4, 3.5, item.state).getVal();
    double eff = bp.get_eff(item.state, false).first;
    if(item.state == 2)output += Form("%d-%d, %d-%d, %dS: 	%.4f & %.3f \n", item.cl, item.ch, item.pl, item.ph, item.state, bdt, eff); 
    if(item.state == 3)output += Form("%d-%d, %d-%d, %dS: 	%.4f & & %.3f \n", item.cl, item.ch, item.pl, item.ph, item.state, bdt, eff);
 //   std::cout << Form("%d-%d, %d-%d, %dS: 	%.3f $\\pm$ %.3f", item.cl, item.ch, item.pl, item.ph, item.state, yield.getVal(), yield.getError()) << std::endl;
	}
  }



std::cout << output ;
}
