#include <iostream>
#include <cstdlib>

#include "bininfo.h"
/*
	1. get timestamps with pt, cbin info
	2. do BDT Application
	3. make RooDataSet -> apply cuts

*/
void ApplyBDT(){
  std::vector< long > v_ts = { 1623391157}; //, 1623349746, 1623349844,  1623349902, 1623349943, 1623349971, 1623349993,  1623350045, 1623350081, 1623350105, 1623350172, 1623350222}; // };
  for( const auto ts : v_ts){
    std::cout << "looping over: " <<  ts << std::endl;
    std::string command11 = Form("root -l -b -q \'BDTClassifierApplication.C( %ld,0, true)\'",ts) ;
    std::string command12 = Form("root -l -b -q \'BDTClassifierApplication.C( %ld,1, true)\'",ts) ;
    std::string command21 = Form("root -l -b -q \'makeRooDataset_fromBDT.C( %ld, true, 0)\'",ts);
    std::string command22 = Form("root -l -b -q \'makeRooDataset_fromBDT.C( %ld, true, 1)\'",ts);
    int a11 = system(command11.c_str());
    int a12 = system(command12.c_str());
    int a21 = system(command21.c_str());
    int a22 = system(command22.c_str());
  }

}
