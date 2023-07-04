#include "wrapper.cxx"

auto ax = ana_bm["3c"][0];
auto testt = fits_wrapper(400019111111, ax, "CB3:EE:GC",  std::vector<double> {0.2363});
auto cont = testt.getContent(0).second;
void test(){
testt.eval();
auto g = testt.createGraph("");
std::cout << g->GetPointY(0) << std::endl; 
g->Draw("APE");
//gROOT->GetListOfFiles()->Print();
//gROOT->GetListOfMappedFiles()->Print();
//gROOT->GetListOfClasses()->Print();
}
