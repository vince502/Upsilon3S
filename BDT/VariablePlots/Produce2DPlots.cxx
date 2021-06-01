#include <iostream>
#include "TFile.h"
#include "TROOT.h"
#include "../../.workdir.h"

void Produce2DPlots(){
  std::string name_file_inputDATA = "OutputSkim_isMC0_v210416_ForBLIND.root";
  std::string name_file_inputMC = "OutputSkim_isMC1_v210521.root";
  std::string abs_name_file_inputMC = Form("%s/%s ",store.Data(), name_file_inputMC.c_str());
  std::string abs_name_file_inputDATA = Form("%s/%s ",store.Data(), name_file_inputDATA.c_str());
  std::string name_file_output = "Mass_vs_TVar.root";
  std::string abs_name_file_output = Form("%s/BDT/VariablePlots/%s ",workdir.Data(), name_file_output.c_str());

  TFile* file_inputDATA = TFile::Open(abs_name_file_inputDATA.c_str());
  TFile* file_inputMC = TFile::Open(abs_name_file_inputMC.c_str());

  TTree* treeMC = (TTree*) file_inputMC->Get("tree");
  TTree* treeDATA = (TTree*) file_inputDATA->Get("tree2");

  TFile* file_output = new TFile(abs_name_file_output.c_str(),"recreate");
  
  TCanvas* c1 = new TCanvas();
  TH2D* plot_massVSvar = new TH2D();
  auto list_var_DATA = treeDATA->GetListOfBranches();
  auto list_var_MC = treeMC->GetListOfBranches();

  TH2D tuple_plot_var_DATA[10];
  TH2D tuple_plot_var_MC[10];
  {
  tuple_plot_var_DATA[0]	= TH2D("MassQQdca_DATA","Mass vs QQdca DATA", 120, 8, 14, 1000, -0, 10);
  tuple_plot_var_MC[0]		= TH2D("MassQQdca_MC","Mass vs QQdca MC", 120, 8, 14, 1000, -0, 10);
  tuple_plot_var_DATA[1]	= TH2D("MassQQVtxProb_DATA","Mass vs QQVtxProb DATA", 120, 8, 14,1000, 0, 1);
  tuple_plot_var_MC[1]		= TH2D("MassQQVtxProb_MC","Mass vs QQVtxProb MC", 120, 8, 14,1000, 0, 1);
  tuple_plot_var_DATA[2]	= TH2D("MassQQMassErr_DATA","Mass vs QQMassErr DATA", 120, 8, 14, 1000, 0, 0.5);
  tuple_plot_var_MC[2]		= TH2D("MassQQMassErr_MC","Mass vs QQMassErr MC", 120, 8, 14, 1000, 0, 0.5);
  tuple_plot_var_DATA[3]	= TH2D("Massctau_DATA","Mass vs ctau DATA", 120, 8, 14,200, -1, 1);
  tuple_plot_var_MC[3]		= TH2D("Massctau_MC","Mass vs ctau MC", 120, 8, 14,200, -1, 1);
  tuple_plot_var_DATA[4]	= TH2D("Massctau3D_DATA","Mass vs ctua3D DATA", 120, 8, 14,200, -1, 1);
  tuple_plot_var_MC[4]		= TH2D("Massctau3D_MC","Mass vs ctua3D MC", 120, 8, 14,200, -1, 1);
  tuple_plot_var_DATA[5]	= TH2D("MasscosAlpha_DATA","Mass vs cosAlpha DATA", 120, 8, 14,400, -1, 1);
  tuple_plot_var_MC[5]		= TH2D("MasscosAlpha_MC","Mass vs cosAlpha MC", 120, 8, 14,400, -1, 1);
  tuple_plot_var_DATA[6]	= TH2D("MasscosAlpha3D_DATA","Mass vs cosAlpha3D DATA", 120, 8, 14,400, -1, 1);
  tuple_plot_var_MC[6]		= TH2D("MasscosAlpha3D_MC","Mass vs cosAlpha3D MC", 120, 8, 14,400, -1, 1);
  tuple_plot_var_DATA[7]	= TH2D("MassQQMassErr_DATA_b1","Mass vs QQMassErr DATA barrel", 120, 8, 14, 1000, 0, 0.5);
  tuple_plot_var_MC[7]		= TH2D("MassQQMassErr_MC_b1","Mass vs QQMassErr MC barrel", 120, 8, 14, 1000, 0, 0.5);
  tuple_plot_var_DATA[8]	= TH2D("MassQQMassErr_DATA_b2","Mass vs QQMassErr DATA barrel", 120, 8, 14, 1000, 0, 0.5);
  tuple_plot_var_MC[8]		= TH2D("MassQQMassErr_MC_b2","Mass vs QQMassErr MC barrel", 120, 8, 14, 1000, 0, 0.5);
  tuple_plot_var_DATA[9]	= TH2D("MassQQMassErr_DATA_e","Mass vs QQMassErr DATA endcap", 120, 8, 14, 1000, 0, 0.5);
  tuple_plot_var_MC[9]		= TH2D("MassQQMassErr_MC_e","Mass vs QQMassErr MC endcap", 120, 8, 14, 1000, 0, 0.5);
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
      for( int idx_var = 0; idx_var < 7;  idx_var++){
      if((idx_entry%10000)==0)  std::cout << "POS : ("<<tuple_value_MC[7]<< ", "<< tuple_value_MC[idx_var] <<")"  << std::endl;
      tuple_plot_var_MC[idx_var].Fill(tuple_value_MC[7],tuple_value_MC[idx_var]);
    }
    if(fabs(y_MC) < 0.6 ) { tuple_plot_var_MC[7].Fill(tuple_value_MC[7],tuple_value_MC[2]); }
    if(fabs(y_MC) > 0.6 && fabs(y_MC) < 1.2) { tuple_plot_var_MC[8].Fill(tuple_value_MC[7],tuple_value_MC[2]); }
    if(fabs(y_MC) > 1.2 && fabs(y_MC) < 2.4) { tuple_plot_var_MC[9].Fill(tuple_value_MC[7],tuple_value_MC[2]); }
  }
  for ( int idx_entry=0; idx_entry < number_entries_DATA; idx_entry++){
    treeDATA->GetEntry(idx_entry);
    for( int idx_var = 0; idx_var < 7;  idx_var++){
      tuple_plot_var_DATA[idx_var].Fill(tuple_value_DATA[7],tuple_value_DATA[idx_var]);
    }
    if(fabs(y_DATA) < 0.6 ) { tuple_plot_var_DATA[7].Fill(tuple_value_DATA[7],tuple_value_DATA[2]); }
    if(fabs(y_DATA) > 0.6 && fabs(y_DATA) < 1.2) { tuple_plot_var_DATA[8].Fill(tuple_value_DATA[7],tuple_value_DATA[2]); }
    if(fabs(y_DATA) > 1.2 && fabs(y_DATA) < 2.4) { tuple_plot_var_DATA[9].Fill(tuple_value_DATA[7],tuple_value_DATA[2]); }
  }
  file_output->cd();
  c1->cd();
  for( TH2D plot : tuple_plot_var_DATA){
    plot.Draw();
    plot.Write();
  }
  for( TH2D plot : tuple_plot_var_MC){
    plot.Draw();
    plot.Write();
  }
  file_output->Close();

}
