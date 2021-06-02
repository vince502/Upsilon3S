#include <iostream>
#include "bininfo.h"
#include "../.workdir.h"


std::pair<double,double> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, string name_input_opt = "", string formula_significance= "S12")
{
  string tag_BLIND = "";
  if(info_BDT(ts)[2].find("BLIND")!=std::string::npos) tag_BLIND = "BLIND";
  std::cout << tag_BLIND << std::endl;
  std::string name_input = Form("%s/BDT/BDTResult/BDTresultY3S_%ld_%s%s.root", workdir.Data(), ts, name_input_opt.c_str(), tag_BLIND.c_str());

  TFile* file_input = TFile::Open(name_input.c_str());
  TFile* file_output = new TFile("output.root","recreate");
  TTree* tree_train_raw = (TTree*) file_input->Get("dataset/TrainTree");
  std::string theCut = Form("(mass<11.5 && mass>8.0) && (pt>%f) && (pt<%f) && (y>%f) && (y<%f) && (cBin>%d) && (cBin<%d) && (QQVtxProb>%f)", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP );
  TTree* tree_train = tree_train_raw->CopyTree(theCut.c_str());
  Float_t val_bdt;
  Int_t bool_classID;
  tree_train->SetBranchAddress("classID", &bool_classID);
  tree_train->SetBranchAddress(Form("BDT_train_%ld",ts), &val_bdt);
  
  TH1D* hist_res = new TH1D("hist_res", "signifcance vs BDT", 150, -0.5, 1);

  int sig=0;
  int bkg=0;
  
  int max_sig = 20000;
  int max_bkg = 10000;
  int tuple_pass_sig[150];
  int tuple_pass_bkg[150];
  for (int idx =0; idx <150; idx++){ tuple_pass_sig[idx]=0; tuple_pass_bkg[idx]=0;}
  for ( int idx =0; idx < tree_train->GetEntries(); idx++){
    tree_train->GetEntry(idx);
    if( (sig > max_sig ) && (bkg > max_bkg) ) break;
    int counts =0;
    for( double x = -0.5; x < 1; x+=0.01){
      if( (sig < max_sig) && (bool_classID==0)){sig+=1; if(val_bdt> x) {tuple_pass_sig[counts]+=1;}}
      if( (bkg < max_bkg) && (bool_classID==1)){bkg+=1; if(val_bdt> x) {tuple_pass_bkg[counts]+=1;}}
      counts++;
    }
  }
  double _signif[150];
  int pass_sig=0;
  int pass_bkg=0;
  for(int idx =0 ; idx <150; idx++){
    pass_sig = tuple_pass_sig[idx];
    pass_bkg = tuple_pass_bkg[idx];
    if( formula_significance=="S12") _signif[idx] = 2*(TMath::Sqrt(pass_sig+pass_bkg)-TMath::Sqrt(pass_bkg));
    if( formula_significance=="S2") _signif[idx] = pass_sig/TMath::Sqrt(pass_sig+pass_bkg); 
    hist_res->SetBinContent(idx+1,_signif[idx]);
  }
//  TCanvas* c1 =new TCanvas();
//  c1->cd();
//  hist_res->Draw();
//  c1->SaveAs("test_optBDT.pdf");
 
  double max_signif_bdt = -0.5+0.01*hist_res->GetMaximumBin();
  double max_signif_val = hist_res->GetMaximum();

  return std::make_pair(max_signif_bdt, max_signif_val);
}
