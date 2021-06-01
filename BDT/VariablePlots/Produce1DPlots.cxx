#include <iostream>
#include "TFile.h"
#include "TROOT.h"
#include "../../.workdir.h"

void Produce1DPlots(){
  std::string name_file_inputDATA = "OutputSkim_isMC0_v210416_ForBLIND.root";
  std::string name_file_inputMC = "OutputSkim_isMC1_v210521.root";
  std::string abs_name_file_inputMC = Form("%s/%s ",store.Data(), name_file_inputMC.c_str());
  std::string abs_name_file_inputDATA = Form("%s/%s ",store.Data(), name_file_inputDATA.c_str());
  std::string name_file_output = "cosAlpha_by_Mass.root";
  std::string abs_name_file_output = Form("%s/BDT/VariablePlots/%s ",workdir.Data(), name_file_output.c_str());

  TFile* file_inputDATA = TFile::Open(abs_name_file_inputDATA.c_str());
  TFile* file_inputMC = TFile::Open(abs_name_file_inputMC.c_str());

  TTree* treeMC = (TTree*) file_inputMC->Get("tree");
  TTree* treeDATA = (TTree*) file_inputDATA->Get("tree2");

  TFile* file_output = new TFile(abs_name_file_output.c_str(),"recreate");
  
  TCanvas* c1 = new TCanvas();
  TH1D* plot_massVSvar = new TH1D();
  auto list_var_DATA = treeDATA->GetListOfBranches();
  auto list_var_MC = treeMC->GetListOfBranches();

  TH1D tuple_plot_var_DATA[10];
  TH1D tuple_plot_var_MC[10];
  {
  tuple_plot_var_DATA[0]	= TH1D("MasscosAlpha_DATA_lsb","Mass vs cosAlpha DATA", 100, -1, 1);
  tuple_plot_var_MC[0]		= TH1D("MasscosAlpha_MC_lsb","Mass vs cosAlpha MC", 100, -1, 1);
  tuple_plot_var_DATA[1]	= TH1D("MasscosAlpha3D_DATA_lsb","Mass vs cosAlpha3D DATA", 100, -1, 1);
  tuple_plot_var_MC[1]		= TH1D("MasscosAlpha3D_MC_lsb","Mass vs cosAlpha3D MC", 100, -1, 1);
  tuple_plot_var_DATA[2]	= TH1D("MasscosAlpha_DATA_sig","Mass vs cosAlpha DATA", 100, -1, 1);
  tuple_plot_var_MC[2]		= TH1D("MasscosAlpha_MC_sig","Mass vs cosAlpha MC", 100, -1, 1);
  tuple_plot_var_DATA[3]	= TH1D("MasscosAlpha3D_DATA_sig","Mass vs cosAlpha3D DATA", 100, -1, 1);
  tuple_plot_var_MC[3]		= TH1D("MasscosAlpha3D_MC_sig","Mass vs cosAlpha3D MC", 100, -1, 1);
  tuple_plot_var_DATA[4]	= TH1D("MasscosAlpha_DATA_rsb","Mass vs cosAlpha DATA", 100, -1, 1);
  tuple_plot_var_MC[4]		= TH1D("MasscosAlpha_MC_rsb","Mass vs cosAlpha MC", 100, -1, 1);
  tuple_plot_var_DATA[5]	= TH1D("MasscosAlpha3D_DATA_rsb","Mass vs cosAlpha3D DATA", 100, -1, 1);
  tuple_plot_var_MC[5]		= TH1D("MasscosAlpha3D_MC_rsb","Mass vs cosAlpha3D MC", 100, -1, 1);
//  tuple_plot_var_DATA[6]	= 
//  tuple_plot_var_MC[6]		= 
//  tuple_plot_var_DATA[7]	= TH2D("MassQQMassErr_DATA_b1","Mass vs QQMassErr DATA barrel", 120, 8, 14, 1000, 0, 0.5);
//  tuple_plot_var_MC[7]		= TH2D("MassQQMassErr_MC_b1","Mass vs QQMassErr MC barrel", 120, 8, 14, 1000, 0, 0.5);
//  tuple_plot_var_DATA[8]	= TH2D("MassQQMassErr_DATA_b2","Mass vs QQMassErr DATA barrel", 120, 8, 14, 1000, 0, 0.5);
//  tuple_plot_var_MC[8]		= TH2D("MassQQMassErr_MC_b2","Mass vs QQMassErr MC barrel", 120, 8, 14, 1000, 0, 0.5);
//  tuple_plot_var_DATA[9]	= TH2D("MassQQMassErr_DATA_e","Mass vs QQMassErr DATA endcap", 120, 8, 14, 1000, 0, 0.5);
//  tuple_plot_var_MC[9]		= TH2D("MassQQMassErr_MC_e","Mass vs QQMassErr MC endcap", 120, 8, 14, 1000, 0, 0.5);
  }
  double tuple_value_DATA[8];
  double tuple_value_MC[8];
  double y_DATA, y_MC;
  int count = 0;
  for(std::string item : { "QQdca", "QQVtxProb", "QQMassErr", "ctau", "ctau3D", "cosAlpha", "cosAlpha3D", "mass" } ){
    treeMC->SetBranchAddress(item.c_str(), &tuple_value_MC[count]);
    treeDATA->SetBranchAddress(item.c_str(), &tuple_value_DATA[count]);
    count++;
  }
  treeMC->SetBranchAddress("y", &y_MC);
  treeDATA->SetBranchAddress("y", &y_DATA);
  count=0;
  int number_entries_DATA = treeDATA->GetEntries(); 
  int number_entries_MC = treeMC->GetEntries(); 
  for ( int idx_entry=0; idx_entry < number_entries_MC; idx_entry++){
    treeMC->GetEntry(idx_entry);
  //    for( int idx_var = 0; idx_var < 6;  idx_var++){
  //    if((idx_entry%100000)==0)  std::cout << "POS : ("<<tuple_value_MC[7]<< ", "<< tuple_value_MC[idx_var] <<")"  << std::endl;
  //    tuple_plot_var_MC[idx_var].Fill(tuple_value_MC[7],tuple_value_MC[idx_var]);
  //  }
    if(tuple_value_MC[7] < 9.8) tuple_plot_var_MC[0].Fill(tuple_value_MC[5]);
    if(tuple_value_MC[7] < 9.8) tuple_plot_var_MC[1].Fill(tuple_value_MC[6]);
    if(tuple_value_MC[7] > 8 && tuple_value_MC[7] < 11) tuple_plot_var_MC[2].Fill(tuple_value_MC[5]);
    if(tuple_value_MC[7] > 8 && tuple_value_MC[7] < 11) tuple_plot_var_MC[3].Fill(tuple_value_MC[6]);
    if(tuple_value_MC[7] > 11) tuple_plot_var_MC[4].Fill(tuple_value_MC[5]);
    if(tuple_value_MC[7] > 11) tuple_plot_var_MC[5].Fill(tuple_value_MC[6]);
  }
  for ( int idx_entry=0; idx_entry < number_entries_DATA; idx_entry++){
    treeDATA->GetEntry(idx_entry);
  //  for( int idx_var = 0; idx_var < 6;  idx_var++){
  //    tuple_plot_var_DATA[idx_var].Fill(tuple_value_DATA[7],tuple_value_DATA[idx_var]);
  //  }
    if(tuple_value_DATA[7] < 8.6) tuple_plot_var_DATA[0].Fill(tuple_value_DATA[5]);
    if(tuple_value_DATA[7] < 8.6) tuple_plot_var_DATA[1].Fill(tuple_value_DATA[6]);
    if(tuple_value_DATA[7] > 8.6 && tuple_value_DATA[7] < 10.8) tuple_plot_var_DATA[2].Fill(tuple_value_DATA[5]);
    if(tuple_value_DATA[7] > 8.6 && tuple_value_DATA[7] < 10.8) tuple_plot_var_DATA[3].Fill(tuple_value_DATA[6]);
    if(tuple_value_DATA[7] > 10.8 && tuple_value_DATA[7] < 11.5) tuple_plot_var_DATA[4].Fill(tuple_value_DATA[5]);
    if(tuple_value_DATA[7] > 10.8 && tuple_value_DATA[7] < 11.5) tuple_plot_var_DATA[5].Fill(tuple_value_DATA[6]);
  }
  file_output->cd();
  c1->cd();
  for( TH1D plot : tuple_plot_var_DATA){
    plot.Scale(1/plot.GetEntries());
    plot.Draw();
    plot.Write();
    c1->Clear();
  }
  for( TH1D plot : tuple_plot_var_MC){
    plot.Scale(1/plot.GetEntries());
    plot.Draw();
    plot.Write();
    c1->Clear();
  }
  TCanvas* c2 = new TCanvas();
  c2->cd();
  c2->Divide(2,1);
  c2->cd(1);
  tuple_plot_var_DATA[0].Scale(1/tuple_plot_var_DATA[0].GetEntries());
  tuple_plot_var_DATA[0].GetYaxis()->SetRangeUser(0,tuple_plot_var_DATA[0].GetMaximum()*1.15);
  tuple_plot_var_DATA[0].SetMarkerSize(5);
  tuple_plot_var_DATA[0].Draw("pe");
  tuple_plot_var_MC[2].Scale(1/tuple_plot_var_MC[2].GetEntries());
  tuple_plot_var_MC[2].SetLineColor(kRed);
  tuple_plot_var_DATA[2].SetMarkerSize(5);
  tuple_plot_var_MC[2].Draw("pe:same");
  tuple_plot_var_DATA[4].Scale(1/tuple_plot_var_DATA[4].GetEntries());
  tuple_plot_var_DATA[4].SetLineColor(kGreen);
  tuple_plot_var_DATA[4].SetMarkerSize(5);
  tuple_plot_var_DATA[4].Draw("pe:same");
  c2->cd(2);
  tuple_plot_var_DATA[1].Scale(1/tuple_plot_var_DATA[1].GetEntries());
  tuple_plot_var_DATA[1].GetYaxis()->SetRangeUser(1,tuple_plot_var_DATA[1].GetMaximum()*1.15);
  tuple_plot_var_DATA[0].SetMarkerSize(5);
  tuple_plot_var_DATA[1].Draw("pe");
  tuple_plot_var_MC[3].Scale(1/tuple_plot_var_MC[3].GetEntries());
  tuple_plot_var_MC[3].SetLineColor(kRed);
  tuple_plot_var_DATA[3].SetMarkerSize(5);
  tuple_plot_var_MC[3].Draw("pe:same");
  tuple_plot_var_DATA[5].Scale(1/tuple_plot_var_DATA[5].GetEntries());
  tuple_plot_var_DATA[5].SetLineColor(kGreen);
  tuple_plot_var_DATA[5].SetMarkerSize(5);
  tuple_plot_var_DATA[5].Draw("pe:same");
  c2->Write();
  c2->Clear();

  file_output->Close();

}
