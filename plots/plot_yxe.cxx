#include "drawRAAplot.cxx"

TH1D plot_yxe( int state =2, std::pair<int, int> cbpair = {0,181}, std::pair<double, double> ptpair = {0,30} , std::string type= "CB3:CC2:FF" ){
  TH1D h1= TH1D("h1", "" , 260, -1.3, 1);
  for(double idx = -1.0; idx < 0.3; idx +=0.1){

    if(idx>-0.001 && idx < 0.001){idx =0.0000;}
   //   { std::cout << "\n\n\n\n\n NO room for 00000.00000 !!!!!!! \n\n\n\n\n" << std::endl; continue;}
    if(idx< 0.11) { type = "CB3:CC4:FF"; }
    if(idx> 0.11) { type = "CB3:CC2:FF"; }
    auto r1 = getDoubleRatioValue( cbpair, ptpair, type, idx, state, 1, 1625139244); 
    if(idx>-0.001 && idx < 0.001)
      idx= 0.0001;//{ std::cout << "\n\n\n\n\n NO room for 00000.00000 !!!!!!! \n\n\n\n\n" << std::endl; continue;}
    h1.SetBinContent(h1.FindBin(idx), r1.getVal() );
    h1.SetBinError(h1.FindBin(idx), r1.getError() );
    if(idx>-0.001 && idx < 0.001)
      idx= 0.000;//{ std::cout << "\n\n\n\n\n NO room for 00000.00000 !!!!!!! \n\n\n\n\n" << std::endl; continue;}
  }
    auto r1 = getDoubleRatioValue( cbpair, ptpair, "CB3:CC2:GC", 0.2674, state, 1); 
    h1.SetBinContent(h1.FindBin(0.2674), r1.getVal() );
    h1.SetBinError(h1.FindBin(0.2674), r1.getError() );

    r1 = getDoubleRatioValue( cbpair, ptpair, "CB3:CC2:GC", 0.1616, state, 1); 
    h1.SetBinContent(h1.FindBin(0.1616), r1.getVal() );
    h1.SetBinError(h1.FindBin(0.1616), r1.getError() );

    r1 = getDoubleRatioValue( cbpair, ptpair, "CB3:CC2:GC", 0.2308, state, 1); 
    h1.SetBinContent(h1.FindBin(0.2308), r1.getVal() );
    h1.SetBinError(h1.FindBin(0.2308), r1.getError() );

  return h1;
}



