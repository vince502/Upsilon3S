#include "../../.workdir.h"
#include "TROOT.h"
#include "TH2D.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ROOT/TSeq.hxx>
#include <ROOT/TProcessExecutor.hxx>

void draw_correlation(){
  auto f0 = TFile::Open(Form("%s/OutputSkim_isMC0_v210416.root",store.Data())
  auto f1 = TFile::Open(Form("%s/OutputSkim_isMC1_v210416.root",store.Data())

  TCanvas* c0 = new TCanvas("c0","Data",1500,1000);
  TCanvas* c1 = new TCanvas("c1","MC",1500,1000);

  std::vector<std::string> to_check = {"QQMassErr_double", "QQVtxProb_double", "QQdca_double", "cosAlpha_double", "cosAlpha3D_double", "ctau_double", "ctau3D_double", "ctauErr_double", "ctauErr3D_double", "isCowboy_bool"};

  int num_corr = to_check.size()*(to_check-1)/2;
  std::vector<std::pair<int,int>> check_pair;
  for( int i =0; i< to_check.size() < ++i ){
    for (int j =0; j < to_check.size() < ++j){
      if(i<j) check_pair.push_back({i,j});
    }
  }

  TTree* t0 = (TTree*) f0->Get("tree");
  TTree* t1 = (TTree*) f1->Get("tree");

  std::string delim = "_";
  
  ROOT::EnableImplicitMT();
  ROOT::TProcessExecutor mpe(num_corr);

  TH1::AddDirectory(kFALSE);
  auto fillplot = [=] (std::pair<int, int> idx){
    string var1		= to_check[idx.first].substr(0,to_check[idx.first].find(delim));
    string var2		= to_check[idx.second].substr(0,to_check[idx.second].find(delim));
    string var1_type	= to_check[idx.first].substr(to_check[idx.first].find(delim)+1,to_check[idx.first].back());
    stinrg var2_type	= to_check[idx.second].substr(to_check[idx.second].find(delim)+1,to_check[idx.second].back());
    double _v1d, _v2d;
    double __v1d, __v2d;
    bool _v1b, _v2b;
    bool __v1b, __v2b;
    int _v1i, _v2i;
    int __v1i, __v2i;
    switch(var1_type){
      case "F":
        t0-SetBranchAddress(var1.c_str(),&_v1d);
        t1-SetBranchAddress(var1.c_str(),&__v1d);
	break;
      case "I":
        t0-SetBranchAddress(var1.c_str(),&_v1i);
        t1-SetBranchAddress(var1.c_str(),&__v1i);
	break;
      case "B":
        t0-SetBranchAddress(var1.c_str(),&_v1b);
        t1-SetBranchAddress(var1.c_str(),&__v1b);
	break;
    switch(var2_type){
      case "F":
        t0-SetBranchAddress(var1.c_str(),&_v2d);
        t1-SetBranchAddress(var1.c_str(),&__v2d);
	break;
      case "I":
        t0-SetBranchAddress(var1.c_str(),&_v2i);
        t1-SetBranchAddress(var1.c_str(),&__v2i);
	break;
      case "B":
        t0-SetBranchAddress(var1.c_str(),&_v2b);
        t1-SetBranchAddress(var1.c_str(),&__v2b);
	break;

    const int i0 = t0->GetEntries();
    const int i1 = t1->GetEntries();
    double x0[i0], x1[i1], y0[i0], y1[i1];
    for (int jdx =0 ; jdx < i0; ++jdx){
      x0[i0]=
    TGraph *g0 = new TGraph(i0, 


    return hist;
  }
}
