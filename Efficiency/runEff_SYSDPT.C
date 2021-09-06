#include "getEfficiency_SYSDPTUP.C"
#include "getEfficiency_SYSDPTDOWN.C"
#include "getEfficiencyBDT_SYSDPTUP.C"
#include "getEfficiencyBDT_SYSDPTDOWN.C"
#include "../BDT/bininfo.h"

void runEff_SYSTNP()
{
  	std::vector<ana_bins> bin2c = ana_bm["2c"];
  	std::vector<ana_bins> bin3c = ana_bm["3c"];
  	std::vector<ana_bins> bin2p = ana_bm["2p"];
  	std::vector<ana_bins> bin3p = ana_bm["3p"];
	std::vector<std::vector<ana_bins> > bx = {bin2c, bin3c, bin2p, bin3p};
	
	for(auto ab : bx){
	  for(auto bin : ab){
	    double bl = Get_BDT(9999999999, bin.state, bin.pl, bin.ph, bin.cl, bin.ch, 0, 2.4, 2);
	    getEfficiency_SYSDPTUP((float) bin.pl,(float) bin.ph, -2.4, 2.4, bin.cl, bin.ch, true, true, false, kTrigUps, true, bin.state, 1);
	    getEfficiency_SYSDPTDOWN((float) bin.pl,(float) bin.ph, -2.4, 2.4, bin.cl, bin.ch, true, true, false, kTrigUps, true, bin.state, 1);
	    getEfficiencyBDT_SYSDPTUP((float) bin.pl,(float) bin.ph, -2.4, 2.4, bin.cl, bin.ch, true, true, 9999999999, bl, 1, bin.state, bin.state, 0);
	    getEfficiencyBDT_SYSDPTDOWN((float) bin.pl,(float) bin.ph, -2.4, 2.4, bin.cl, bin.ch, true, true, 9999999999, bl, 1, bin.state, bin.state, 0);
	  }
	}
}
