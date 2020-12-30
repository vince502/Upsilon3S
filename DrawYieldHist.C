#include <iostream>
#include <TFile.h>
#include <RooDataSet.h>
#include <RooWorkspace.h>
#include <RooFit.h>
#include <string>

using namespace RooFit;

void DrawYieldHist(const double ptCut = 3.5, int cBinLow = 0, int cBinHigh = 180, string Trig = "S1", bool trigSwitch = true){
  TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
  TString plotDIR = mainDIR + "/MassHisto";
  void * dirpM = gSystem->OpenDirectory(plotDIR.Data());
  if(dirpM) gSystem->FreeDirectory(dirpM);
  else gSystem->mkdir(plotDIR.Data(), kTRUE);

  string Sw = "";
  if (trigSwitch) Sw = "_Switch1";
  TFile* fTrigS1 = new TFile(Form("skimmedFiles/OniaRooDataSet_OniaSkim_Trig%s%s.root",Trig.c_str(), Sw.c_str()),"READ");
  RooDataSet* dsos40 = (RooDataSet*) fTrigS1->Get("dataset");
  RooWorkspace* works1 = new RooWorkspace(Form("workspace1"));
  works1->import(*dsos40); 
  RooDataSet* cut_dsos40 = (RooDataSet*) dsos40->reduce(RooArgSet(*(works1->var("mass"))),Form("(pt1>=%f)&&(pt2>=%f) && (eta1<2.4 && eta1> -2.4) && (eta2< 2.4 && eta2 > -2.4) && ( cBin >= %d && cBin <= %d)",ptCut,ptCut,cBinLow, cBinHigh));
  cut_dsos40->SetName("reducedOS40");
  works1->import(*cut_dsos40);
  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 800, 800);
  works1->var("mass")->setRange(8,14);

  RooPlot* massP40 = works1->var("mass")->frame(120);
  works1->data("reducedOS40")->plotOn(massP40,Name("massP40"));

  c1->cd();
  massP40->Draw();
  string sw = "Sw0";
  if (trigSwitch) sw = "Sw1";
  string NTrig = "";
  if (Trig == "S1") NTrig = "DBMuOS40100";
  else if (Trig == "S2") NTrig = "DBMu50100";
  else if (Trig == "S13") NTrig = "Ups";
  c1->SetTitle(Form("MassDist_cut%dp%dGeV_%s_%d-%d_%s",(int) ptCut, (int) (10*(ptCut-(int)ptCut)), NTrig.c_str(),(int) cBinLow/2, (int)  cBinHigh/2, sw.c_str()));
  c1->SaveAs(Form("MassHisto/MassDist_cut%dp%dGeV_%s_%d-%d_%s.pdf",(int) ptCut, (int) (10*(ptCut-(int)ptCut)), NTrig.c_str(),(int) cBinLow/2, (int)  cBinHigh/2, sw.c_str()));
  c1->Close();
  fTrigS1->Close();
}
