#include "getEfficiencyBDT_SYSTNP.C"
#include "../BDT/bininfo.h"
#include "../BDT/BDTtraindiff.cxx"

void runEff_SYSTNP()
{
  	std::vector<ana_bins> bin2c = ana_bm_comb["2c"];
  	std::vector<ana_bins> bin3c = ana_bm_comb["3c"];
  	std::vector<ana_bins> bin2p = ana_bm_comb["2p"];
  	std::vector<ana_bins> bin3p = ana_bm_comb["3p"];
	std::vector<std::vector<ana_bins> > bx = {bin2c, bin3c, bin2p, bin3p};
	
	for(auto ab : bx){
	  for(auto bin : ab){
	    double bl = Get_BDT(100019111111, bin);
	    getEfficiencyBDT_SYSTNP((float) bin.pl,(float) bin.ph, -2.4, 2.4, bin.cl, bin.ch, true, true, 100019111111, bl, 1, bin.train_state, bin.state, 0);
	  }
	}

//	for(auto ab : bx){
//	  for(auto bin : ab){
//	    double bl = Get_BDT(10000000016, bin);
//	    getEfficiencyBDT_SYSTNP((float) bin.pl,(float) bin.ph, -2.4, 2.4, bin.cl, bin.ch, true, true, 10000000016, bl, 1, bin.train_state, bin.state, 0);
//	  }
//	}
}
