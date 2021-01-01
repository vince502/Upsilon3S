#include <iostream>
#include <TFile.h>
#include <RooDataSet.h>
#include <RooWorkspace.h>
#include <RooFit.h>
#include <string>
#include "Headers/Style_Upv2.h"

using namespace RooFit;

void DrawYieldHist(const double ptMin = 0., const double ptMax = 50., const double ptCut = 3.5, int cBinLow = 0, int cBinHigh = 180, string Trig = "S1", bool trigSwitch = true){
  TString mainDIR = gSystem->ExpandPathName(gSystem->pwd());
  TString plotDIR = mainDIR + "/MassHisto";
  void * dirpM = gSystem->OpenDirectory(plotDIR.Data());
  if(dirpM) gSystem->FreeDirectory(dirpM);
  else gSystem->mkdir(plotDIR.Data(), kTRUE);

  string Sw = "";
  if (trigSwitch) Sw = "_Switch1";
  TFile* fTrigS1 = new TFile(Form("roodatasetFiles/OniaRooDataSet_OniaSkim_Trig%s%s.root",Trig.c_str(), Sw.c_str()),"READ");
  RooDataSet* dsos40 = (RooDataSet*) fTrigS1->Get("dataset");
  RooWorkspace* works1 = new RooWorkspace(Form("workspace1"));
  works1->import(*dsos40); 
  RooDataSet* cut_dsos40 = (RooDataSet*) dsos40->reduce(RooArgSet(*(works1->var("mass"))),Form("((pt >= %f ) && (pt <= %f ))&&(pt1>=%f)&&(pt2>=%f) && (eta1<2.4 && eta1> -2.4) && (eta2< 2.4 && eta2 > -2.4) && ( cBin >= %d && cBin <= %d && (recoQQsign ==0))",ptMin, ptMax, ptCut,ptCut,cBinLow, cBinHigh));
  cut_dsos40->SetName("reducedOS40");
  works1->import(*cut_dsos40);
  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 900, 800);
  works1->var("mass")->setRange(8,14);

  RooPlot* massP40 = works1->var("mass")->frame(120);
  works1->data("reducedOS40")->plotOn(massP40,Name("massP40"));

  c1->cd();
  gStyle->SetTitle(0);
  massP40->SetTitle("");
  massP40->GetYaxis()->SetLabelSize(0.03);
  massP40->GetYaxis()->SetTitleOffset(1.4);
  massP40->Draw();
  lumiText(0.65, 0.91);
  TLatex* lt1 = new TLatex();
  FormLatex(lt1, 12, 0.035);
  lt1->DrawLatex(0.55,0.75, Form("p_{T}^{#mu} #geq %.1f GeV/c", ptCut));
  lt1->DrawLatex(0.55,0.70, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int) ptMin, (int) ptMax));
  TLatex* lt2 = new TLatex();
  FormLatex(lt2, 12, 0.04);
  lt2->DrawLatex(0.1, 0.93, Form("Centrality %d-%d %%",(int) cBinLow/2, (int) cBinHigh/2));
  string sw = "Sw0";
  if (trigSwitch) sw = "Sw1";
  string NTrig = "";
  if (Trig == "S1") NTrig = "DBMuOS40100";
  else if (Trig == "S2") NTrig = "DBMu50100";
  else if (Trig == "S13") NTrig = "Ups";
  lt1->DrawLatex(0.55,0.80, Form("Trigger : %s", NTrig.c_str()));
  c1->SaveAs(Form("MassHisto/MassDist_%.0f-%.0f_cut%dp%dGeV_%s_%d-%d_%s.pdf",ptMin, ptMax, (int) ptCut, (int) (10*(ptCut-(int)ptCut)), NTrig.c_str(),(int) cBinLow/2, (int)  cBinHigh/2, sw.c_str()));
  c1->Close();
  fTrigS1->Close();
}
