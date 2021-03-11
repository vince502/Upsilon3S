#include <iostream>
#include <string>
#include "TFile.h"
#include "RooPlot.h"
#include "RooFit.h"
#include "TROOT.h"

using namespace RooFit;

void DrawTemp(long ts,double ylim, float blow, float bhigh, float vcut, TString MupT = "3p5", string Trig = "S13", TString fittype = "freefit"){
  string fitdir;
  int ylim10 = (int) (ylim*10);
  if( fittype=="freefit") fitdir = "FF";
  else if (fittype=="DatafixtoMC") fitdir = "DFM";
  TFile* file1 = new TFile(Form("Yield/Yield_%ld_%s_pt_0-30_rap_-%d-%d_120bin_cbin_0-180_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", ts, fitdir.c_str(), ylim10, ylim10, blow, bhigh, vcut),"read");
  TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
  TString massDIR = mainDIR +  Form("/MassDist/BDT/%ld/freefit/%s/%s/Temp/FitResult", ts,Trig.c_str(),MupT.Data());
  TString massDIRp = mainDIR + Form("/MassDist/BDT/%ld/freefit/%s/%s/Temp/FitResult/png",ts,Trig.c_str(),MupT.Data());
  TString massDIRl = mainDIR + Form("/MassDist/BDT/%ld/freefit/%s/%s/Temp/FitResult/logY",ts,Trig.c_str(),MupT.Data());
  TString massDIR2 = mainDIR + Form("/MassDist/BDT/%ld/freefit/%s/%s/WithoutFit",ts,Trig.c_str(),MupT.Data());
  void * dirpM = gSystem->OpenDirectory(massDIR.Data());
  if(dirpM) gSystem->FreeDirectory(dirpM);
  else{ gSystem->mkdir(massDIR.Data(), kTRUE); gSystem->mkdir(massDIRl.Data(),kTRUE);}
  void * dirpMl = gSystem->OpenDirectory(massDIRl.Data());
  if(dirpMl) gSystem->FreeDirectory(dirpMl);
  else gSystem->mkdir(massDIRl.Data(), kTRUE);
  void * dirpMp = gSystem->OpenDirectory(massDIRp.Data());
  if(dirpMp) gSystem->FreeDirectory(dirpMp);
  else gSystem->mkdir(massDIRp.Data(), kTRUE);

  RooWorkspace* works1 = (RooWorkspace*) file1->Get("workspace");
  RooFitResult* Result = (RooFitResult*) file1->Get("fitresult_model_reducedDS");

  RooDataSet* dataset = (RooDataSet*) works1->data("reducedDS");
  RooRealVar* vmass = (RooRealVar*) works1->var("mass");

  gStyle->SetOptTitle(0);
  
  RooPlot* plot1 = vmass->frame();
  works1->data("reducedDS")->plotOn(plot1, Name("massPlot"), MarkerSize(0.5), LineWidth(1));
  works1->pdf("model")->plotOn(plot1, Name("modelPlot"), LineWidth(1));

//  RooGenericPdf* cb1 = (RooGenericPdf*) works1->pdf("twoCB1S");
  works1->pdf("model")->plotOn(plot1, Components(RooArgSet(*works1->pdf("twoCB1S")) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works1->pdf("model")->plotOn(plot1, Components(RooArgSet(*works1->pdf("twoCB2S")) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works1->pdf("model")->plotOn(plot1, Components(RooArgSet(*works1->pdf("twoCB3S")) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works1->pdf("model")->plotOn(plot1, Components(RooArgSet(*works1->pdf("bkgErf")) ), LineWidth(1), LineStyle(1), LineColor(kGreen), MoveToBack() );

  TCanvas* c1 = new TCanvas("c1", "", 1100, 800);
  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.7, 1.0);
  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.0, 0.7, 0.25);
  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.7, 0.25, 1.0, 1.0);
  TPad* pad_mag = new TPad("pad_mag", "pad_mag", 0.7, 0.0, 1.0, 0.25);
  c1->cd();
  pad_mass->Draw();
  pad_pull->Draw();
  pad_leg->Draw();
  pad_mag->Draw();
  pad_mass->cd();
  plot1->Draw();


  pad_pull->cd();
  pad_pull->SetGrid(0,1);
  pad_pull->SetTopMargin(0);
  TLine* line_pull = new TLine(8.,0., 14., 0.);
  line_pull->SetLineColorAlpha(kRed, 0.5);
  RooHist* hpull = plot1->pullHist("massPlot", "modelPlot");
  RooPlot* pullPlot = works1->var("mass")->frame(Title("Pull Distribution"));
  pullPlot->addPlotable(hpull, "P");
  pullPlot->GetYaxis()->SetLabelSize(0.13);
  pullPlot->Draw();
  line_pull->Draw("same");

  pad_mag->cd();
  pad_mag->SetTopMargin(0);

  RooPlot* partplot = (RooPlot*)  plot1->Clone();
  partplot->GetXaxis()->SetRangeUser(9.6,10.8);
  partplot->GetYaxis()->SetLabelSize(0.13);
  pad_mag->SetLogy();
  pad_mag->SetLeftMargin(0);
  partplot->Draw();

  pad_leg->cd();
  RooPlot* legPlot = works1->var("mass")->frame(Name("Fit Results"), Title("Fit Results"));
  RooArgList parList = Result->floatParsFinal();
  works1->pdf("model")->paramOn(legPlot, Layout(0, 0.93, 0.97), Parameters(parList));
  legPlot->getAttText()->SetTextAlign(11);
  legPlot->getAttText()->SetTextSize(0.05);

  TPaveText* Ptext = (TPaveText*) legPlot->findObject(Form("%s_paramBox", works1->pdf("model")->GetName())); 
  Ptext->SetY1(0.03);
  Ptext->SetY2(0.93);
  Ptext->Draw();
   

  c1->Update();
  

  c1->SaveAs(Form("%s/FitPlot_%ld_%s_pt_0-30_rap_-24-24_120bin_cbin_0-180_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.pdf",massDIR.Data(), ts, fittype.Data(), blow, bhigh, vcut));
  c1->Close();

}
