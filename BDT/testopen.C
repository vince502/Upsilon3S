#include "yield_eff_signif.h"

void testopen(){
  std::vector<std::pair<double, double> > bdtbin = {/*{-1., -0.3},*/{-1, 0.},{-0.3, -0.1},{-0.1, 0.0},{0.0, 0.1},{0.1, 1.0}};
  int count =0;
  double s;
  for( auto bin : bdtbin){
    binplotter bp(1614848550, 2.4, 0, 30, 0, 180, bin.first, bin.second);
    //s = bp.getsignificance(); 
    RooRealVar adjY = bp.yield_eff();
    std::cout << "idx: " << count << ", low: " << bin.first << ", high: " << bin.second << std::endl;
    count++;
  }
  }
