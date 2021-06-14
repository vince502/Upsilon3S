#include <iostream>
#include "bininfo.h"
#include "../.workdir.h"

//static TH1D* Get_Optimal_BDT_HIST; 
//
std::pair<double,double> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, string name_input_opt = "", string formula_significance= "S12")
{

  int Nbins = (int) (1.5/interval_score);
  std::cout << interval_score << "interval, " << Nbins << "NBINS!!!!!" << std::endl;
  string tag_BLIND = "";
  if(info_BDT(ts)[2].find("BLIND")!=std::string::npos) tag_BLIND = "BLIND";
  if(info_BDT(ts)[4].find("BLIND")!=std::string::npos) tag_BLIND = "BLIND";

  std::cout << tag_BLIND << std::endl;
  std::string name_input = Form("%s/BDT/BDTResult/BDTresultY3S_%ld_%s%s.root", workdir.Data(), ts, name_input_opt.c_str(), tag_BLIND.c_str());

  TFile* file_input = TFile::Open(name_input.c_str());
  TFile* file_output = new TFile("output.root","recreate");
  TTree* tree_train_raw = (TTree*) file_input->Get("dataset/TrainTree");
  std::string theCut = Form("(mass<11.5 && mass>8.0) && (pt>%f) && (pt<%f) && (y>%f) && (y<%f) && (cBin>%d) && (cBin<%d) && (QQVtxProb>%f)", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP );
  TTree* tree_train = tree_train_raw->CopyTree(theCut.c_str());
  std::cout << tree_train_raw->GetEntries() << ", "<< tree_train->GetEntries() << Form(" cl, ch : %d, %d ",cBinLow, cBinHigh) << std::endl;
  Float_t val_bdt;
  Int_t bool_classID;
  tree_train->SetBranchAddress("classID", &bool_classID);
  tree_train->SetBranchAddress(Form("BDT_train_%ld",ts), &val_bdt);
  std::cout << Nbins << "NBINS!!!!!" << std::endl;
  
  TH1D* hist_res = new TH1D(Form("weighted_hist_res [%.1f,%.1f][%.1f,%.1f][%d,%d]",ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh), "signifcance vs BDT", Nbins, -0.5, 1);
  TH1D* hist_res_base = new TH1D(Form("base_hist_res [%.1f,%.1f][%.1f,%.1f][%d,%d]",ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh), "signifcance vs BDT", Nbins, -0.5, 1);

  int sig=0;
  int bkg=0;
  
  int max_sig = 20000;
  int max_bkg = 20000;
  int tuple_pass_sig[Nbins];
  int tuple_pass_bkg[Nbins];
  for (int idx =0; idx <Nbins; idx++){ tuple_pass_sig[idx]=0; tuple_pass_bkg[idx]=0;}
  for ( int idx =0; idx < tree_train->GetEntries(); idx++){
    tree_train->GetEntry(idx);
    if( (sig > max_sig ) && (bkg > max_bkg) ) break;
    int counts =0;
    for( double x = -0.5; x < 1; x+=interval_score){
      if( (sig < max_sig) && (bool_classID==0)){sig+=1; if(val_bdt> x) {tuple_pass_sig[counts]+=1;}}
      if( (bkg < max_bkg) && (bool_classID==1)){bkg+=1; if(val_bdt> x) {tuple_pass_bkg[counts]+=1;}}
      counts++;
    }
  }
  double _signif[Nbins];
  int pass_sig=0;
  int pass_bkg=0;
  for(int idx =0 ; idx <Nbins; idx++){
    pass_sig = tuple_pass_sig[idx];
    pass_bkg = tuple_pass_bkg[idx];
    if( formula_significance=="S12") _signif[idx] = 2*(TMath::Sqrt(pass_sig+pass_bkg)-TMath::Sqrt(pass_bkg));
    if( formula_significance=="S2") _signif[idx] = pass_sig/TMath::Sqrt(pass_sig+pass_bkg); 
    hist_res->SetBinContent(idx+1,_signif[idx]*( ((double)idx/10.)));
    hist_res_base->SetBinContent(idx+1,_signif[idx]);
  }
  Get_Optimal_BDT_HIST = hist_res_base;
  TFile* output;
  TCanvas* c1  = new TCanvas(Form("Plot [%.1f,%.1f][%.1f,%.1f][%d,%d]",ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh), "signifcance vs BDT");
  output = new TFile(Form("%s/BDT/test_OPT_BDT_method2.root",workdir.Data()),"update");
  output->cd();

  //TF1 *f1 = new TF1("poly3", "[0]*x^3+[1]*x^2+[2]*x+[3]",-0.3, 0.4);
//  hist_res_base->Fit("pol2","WQS");
//  hist_res->Draw();

  hist_res_base->Draw();
  c1->Write();

  output->Close();
 
//  auto res = hist_res_base->GetFunction("pol2");
//  double max_signif_bdt_fromfit = res->GetMaximumX(-0.3, 0.5); 
  double max_signif_bdt = -0.5+interval_score*(hist_res_base->GetMaximumBin()-1);
  double max_signif_val = hist_res_base->GetMaximum();
  c1->Close();

  return std::make_pair(max_signif_bdt, max_signif_val);
};
TH1D* func_hist_optimal_BDT(){
  return Get_Optimal_BDT_HIST;
  }
