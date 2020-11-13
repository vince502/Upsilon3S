#include <iostream>
#include <TFile.h>
#include <RooDataSet.h>
#include <RooWorkspace.h>
#include <RooFit.h>

using namespace RooFit;

void DrawYieldHist(const double ptCut = 3.5, int cBinHigh = 90){
  TFile* fTrigS1 = new TFile("skimmedFiles/OniaRooDataSet_OniaSkim_TrigS1.root","READ");
  TFile* fTrigS2 = new TFile("skimmedFiles/OniaRooDatSet_OniaSkim_TrigS2_wOS.root","READ");
  RooDataSet* dsos40 = (RooDataSet*) fTrigS1->Get("dataset");
  RooDataSet* dsos50 = (RooDataSet*) fTrigS2->Get("sdataset");

  RooWorkspace* works1 = new RooWorkspace(Form("workspace1"));
  RooWorkspace* works2 = new RooWorkspace(Form("workspace2"));
  works1->import(*dsos40); 
  works2->import(*dsos50);
  RooDataSet* cut_dsos40 = (RooDataSet*) dsos40->reduce(RooArgSet(*(works1->var("mass"))),Form("(pt1>=%f)&&(pt2>=%f) && (eta1<2.4 && eta1> -2.4) && (eta2< 2.4 && eta2 > -2.4) && ( cBin >= 80 && cBin <= %d)",ptCut,ptCut, cBinHigh));
  RooDataSet* cut_dsos50 = (RooDataSet*) dsos50->reduce(RooArgSet(*(works2->var("mass"))),Form("(pt1>=%f)&&(pt2>=%f)&& (eta1<2.4 && eta1> -2.4) && (eta2< 2.4 && eta2 > -2.4)&& (cBin >= 100 && cBin<= %d)",ptCut, ptCut, cBinHigh));
  cut_dsos40->SetName("reducedOS40");
  cut_dsos50->SetName("reducedOS50");
  works1->import(*cut_dsos40);
  works2->import(*cut_dsos50);
  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 800, 800);
  TCanvas* c2 = new TCanvas("c2", "", 0, 0, 800, 800);
  works1->var("mass")->setRange(8,14);
  works2->var("mass")->setRange(8,14);

  RooPlot* massP40 = works1->var("mass")->frame(120);
  works1->data("reducedOS40")->plotOn(massP40,Name("massP40"));
  RooPlot* massP50 = works2->var("mass")->frame(120);
  works2->data("reducedOS50")->plotOn(massP50,Name("massP50"));

  c1->cd();
  massP40->Draw();
  c2->cd();
  massP50->Draw();

  c1->SetTitle(Form("MassDist_cut%dp%dGeV_Cent40-90",(int) ptCut, (int) (10*(ptCut-(int)ptCut))));
  c1->SaveAs(Form("MassDist_cut%dp%dGeV_Cent40-90.pdf",(int) ptCut, (int) (10*(ptCut-(int)ptCut))));
  c2->SetTitle(Form("MassDist_cut%dp%dGeV_Cent50-90",(int) ptCut, (int) (10*(ptCut-(int)ptCut))));
  c2->SaveAs(Form("MassDist_cut%dp%dGeV_Cent50-90.pdf",(int) ptCut, (int) (10*(ptCut-(int)ptCut))));
  c1->Close();
  c2->Close();
  fTrigS1->Close();
  fTrigS2->Close();
}
