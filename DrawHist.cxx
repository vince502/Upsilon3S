#include <iostream>
#include <string>
#include "TFile.h"
#include "RooPlot.h"
#include "RooFit.h"
#include "TROOT.h"
#include "fitter.h"

using namespace RooFit;

void DrawHist_(long ts,double ylim, float blow, float bhigh, float vcut, TString MupT = "3p5", string Trig = "S13", TString fittype = "freefit") {};
void DrawHist(std::vector<std::string>  parsed,const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString MupT = "3p5", const string Trig = "", bool swflag= false, int cBinLow =0, int cBinHigh = 180, double cutQVP = 0.01, bool isBDT=true, long ts = 1, double cutBDTlow=-1, double cutBDThigh = 1., int Nmassbins=140){

  std::string sig_func = parsed[0];
  std::string bkg_func = parsed[1];
  std::string fitdir = parsed[2];
  std::string name_fitmodel = "_"+bkg_func;
  string fit_param, name_pdf_bkg, name_pdf_sig;
  if(fitdir=="FF") fit_param = "freefit";
  if(fitdir=="GC") fit_param = "gaussconst";
  if(bkg_func=="EE") name_pdf_bkg = "bkgErf";
  if(bkg_func.find("CC")!= std::string::npos) name_pdf_bkg = "CCBkg";
  int ylim10 = (int) (rapMax*10);


  std::string method_selection = (isBDT) ? "BDT" : "Data"; 
  std::string name_file_output = Form("%s/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f.root" ,workdir.Data(), ts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, cutQVP );
  TFile* file1 = new TFile(name_file_output.c_str(),"read");
  TString massDIR =  Form("%s/MassDist/%s/%ld/freefit/%s/%.1f/cent%d-%d/pT%.1f-%.1f/FitResult", workdir.Data(), method_selection.c_str(), ts,Trig.c_str(),rapMax, cBinLow, cBinHigh, ptMin, ptMax);
  TString massDIRp = Form("%s/MassDist/%s/%ld/freefit/%s/%.1f/cent%d-%d/pT%.1f-%.1f/FitResult/png", workdir.Data(), method_selection.c_str(), ts,Trig.c_str(),rapMax, cBinLow, cBinHigh, ptMin, ptMax);
  TString massDIR2 = Form("%s/MassDist/%s/%ld/freefit/%s/%.1f/cent%d-%d/pT%.1f-%.1f/WithoutFit", workdir.Data(), method_selection.c_str(), ts,Trig.c_str(),rapMax, cBinLow, cBinHigh, ptMin, ptMax);
  void * dirpM = gSystem->OpenDirectory(massDIR.Data());
  if(dirpM) gSystem->FreeDirectory(dirpM);
  else{ gSystem->mkdir(massDIR.Data(), kTRUE);}
  void * dirpMp = gSystem->OpenDirectory(massDIRp.Data());
  if(dirpMp) gSystem->FreeDirectory(dirpMp);
  else gSystem->mkdir(massDIRp.Data(), kTRUE);

  RooWorkspace* works = (RooWorkspace*) file1->Get("workspace");
  std::string name_dataset_result = "fitresult_model_reducedDS";
  std::string name_model = "model";
  if(fitdir=="GC"){
    name_dataset_result = "fitresult_model_gc_reducedDS";
    name_model = "model_gc";
  }
  RooFitResult* Result = (RooFitResult*) file1->Get(name_dataset_result.c_str());

  RooDataSet* dataset = (RooDataSet*) works->data("reducedDS");
  RooRealVar* vmass = (RooRealVar*) works->var("mass");

  gStyle->SetOptTitle(0);
  
  RooPlot* plot1 = vmass->frame();
  works->data("reducedDS")->plotOn(plot1, Name("massPlot"), MarkerSize(0.5), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot1, Name("modelPlot"), LineWidth(1));

//  RooGenericPdf* cb1 = (RooGenericPdf*) works->pdf("twoCB1S");
  works->pdf(name_model.c_str())->plotOn(plot1, Components(RooArgSet(*works->pdf("twoCB1S")) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Components(RooArgSet(*works->pdf("twoCB2S")) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Components(RooArgSet(*works->pdf("twoCB3S")) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Components(RooArgSet(*works->pdf("CCBkg")) ), LineWidth(1), LineStyle(1), LineColor(kGreen), MoveToBack() );

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
  RooPlot* pullPlot = works->var("mass")->frame(Title("Pull Distribution"));
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
  RooPlot* legPlot = works->var("mass")->frame(Name("Fit Results"), Title("Fit Results"));
  RooArgList parList = Result->floatParsFinal();
  works->pdf(name_model.c_str())->paramOn(legPlot, Layout(0, 0.93, 0.97), Parameters(parList));
  legPlot->getAttText()->SetTextAlign(11);
  legPlot->getAttText()->SetTextSize(0.05);

  TPaveText* Ptext = (TPaveText*) legPlot->findObject(Form("%s_paramBox", works->pdf(name_model.c_str())->GetName())); 
  Ptext->SetY1(0.03);
  Ptext->SetY2(0.93);
  Ptext->Draw();
   

  c1->Update();
  c1->SaveAs(Form("%s/FitPlot_%ld_%s_%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f.pdf",massDIR.Data(), ts,fitdir.c_str(), bkg_func.c_str(), (int) (ptMin*10), (int) (ptMax*10), ylim10, ylim10, Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(),(int) swflag,(int) isBDT, cutBDTlow, cutBDThigh, cutQVP));
  c1->Close();

}
