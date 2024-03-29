#include <iostream>
#include <string>
#include "../CMS_lumi_square.C"
#include "../tdrstyle.C"
#include "TFile.h"
#include "RooPlot.h"
#include "RooFit.h"
#include "TROOT.h"
#include "../BDT/bininfo.h"

using namespace RooFit;
void DrawNominalMassDist_(ana_bins ab, long ts = 9999999999);
void DrawNominalMassDist(){
  DrawNominalMassDist_(ana_bm["3c"][3]);
  DrawNominalMassDist_(ana_bm["2c"][9]);
};
void DrawNominalMassDist_(ana_bins ab, long ts = 9999999999){
  int Nmassbins = 70;
  string fitdir = "GC";
  string name_fitmodel = "_CB3_CC2";
  string name_sig_pdf = "threeCB";
  string name_pdf_bkg = "CCBkg";

  std::string name_file_output = Form("%s/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f%s.root" ,workdir.Data(), ab.state, ts, fitdir.c_str(), name_fitmodel.c_str(), ab.pl, ab.ph, 24, 24, ab.cl, ab.ch, "3p5", "S13", 0, 1, Get_BDT(ts, ab), 1.0, 0.0000, "" );
  std::cout << name_file_output << std::endl;
  TFile* file1 = new TFile(name_file_output.c_str(),"read");

  RooWorkspace* works = (RooWorkspace*) file1->Get("workspace");
  std::string name_dataset_result = "fitresult_model_reducedDS";
  std::string name_model = "model";
  if(fitdir.find("GC")!=std::string::npos){
    name_dataset_result = "fitresult_model_gc_reducedDS";
    name_model = "model_gc";
  }
  RooFitResult* Result = (RooFitResult*) file1->Get(name_dataset_result.c_str());

  RooDataSet* dataset = (RooDataSet*) works->data("reducedDS");
  if( dataset->sumEntries() <= 1000) Nmassbins = 35;
  RooRealVar* vmass = (RooRealVar*) works->var("mass");
  vmass->setRange("analysis",8,11.5);
  if(ab.state ==3) vmass->setRange("signal",10,10.6);
  if(ab.state ==2) vmass->setRange("signal",9.7,10.3);

  gStyle->SetOptTitle(0);
  
  RooPlot* plot1 = vmass->frame(Nmassbins);
  RooPlot* plot2 = vmass->frame();
  plot2->SetAxisRange(10,10.6);
  works->data("reducedDS")->plotOn(plot1, Name("massPlot"), MarkerSize(0.5), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelPlot"), LineWidth(1));

  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_1S"),Components(RooArgSet(*works->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_2S"),Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_3S"),Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelBkg"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(1), LineStyle(1), LineColor(kGreen), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////

  works->data("reducedDS")->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Name("massPlot"), MarkerSize(0.5), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"),  RooFit::NormRange("signal"),Name("modelPlot"), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(1), LineStyle(1), LineColor(kGreen), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////


//  setTDRStyle();
  TCanvas* c1 = new TCanvas("c1", "", 1000, 1000);

  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0.05, 0.05, 1., 1.);
//  TPad* pad_mass_3S = new TPad("pad_mass_3S", "pad_mass_3S", 0.60, 0.43, 0.90, 0.86);
//  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.0, 0.7, 0.25);
//  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.7, 0.25, 1.0, 1.0);
//  TPad* pad_mag = new TPad("pad_mag", "pad_mag", 0.7, 0.0, 1.0, 0.25);
  c1->cd();
  pad_mass->SetTopMargin(0.07);
  pad_mass->Draw();

//  pad_pull->Draw();
//  pad_leg->Draw();
//  pad_mag->Draw();
  pad_mass->cd();
  plot1->Draw("ALP");
//  plot1->GetXaxis()->SetLabelSize(0);
//  plot1->GetXaxis()->SetTitleSize(0);
  TLatex* lt0 = new TLatex();
  FormLatex(lt0, 12, 0.032);
  lt0->DrawLatex(0.15,0.75, Form("%d < p_{T}^{#mu#mu} < %d GeV/c", ab.pl, ab.ph));
  lt0->DrawLatex(0.15,0.70, Form("|y^{#mu#mu}| < 2.4"));
  lt0->DrawLatex(0.15,0.65, Form("p_{T}^{#mu} > %s GeV/c", "3.5"));
  lt0->DrawLatex(0.15,0.60, Form("|#eta^{#mu}| < 2.4"));
  TLegend* leg = new TLegend(0.6, 0.45, 0.8,0.7 );
  leg->AddEntry("CB3_1S" ,"Signal", "l");
  leg->AddEntry("modelBkg" ,"Background", "l");
  leg->AddEntry("modelPlot" ,"Total", "l");
  leg->SetBorderSize(0);
  leg->Draw();
//  lt0->DrawLatex(0.20,0.65, Form("Centrality %d-%d %%",ab.centl, ab.centh));
  
  CMS_lumi_square( pad_mass, 3, 11);

 // if (draw_mag && train_state ==3){
 //   pad_mass_3S->SetMargin(0.25, 0.01, 0.14, 0.01);
 //   pad_mass_3S->Draw();
 //   pad_mass_3S->cd();
 //   plot2->GetXaxis()->SetLabelSize(0.06);
 //   plot2->GetXaxis()->SetTitleSize(0.06);
 //   plot2->GetXaxis()->SetTitle("mass (GeV/c^{2}) ");
 //   plot2->GetXaxis()->SetTitleOffset(1.1);
 //   plot2->GetYaxis()->SetLabelSize(0.08);
 //   plot2->GetYaxis()->SetTitleSize(0.06);
 //   plot2->GetYaxis()->SetTitleOffset(1.65);
 //   plot2->GetYaxis()->SetRangeUser(0, (plot1->GetMaximum()/2.0));
 //   plot2->Draw();
 // }


//  pad_pull->cd();
//  pad_pull->SetGrid(0,1);
//  pad_pull->SetTopMargin(0.00);
//  pad_pull->SetBottomMargin(0.30);
//  TLine* line_pull = new TLine(8.,0., 11.5, 0.);
//  line_pull->SetLineColorAlpha(kRed, 0.5);
//  RooHist* hpull = plot1->pullHist("massPlot", "modelPlot");
//  RooPlot* pullPlot = works->var("mass")->frame(Title("Pull Distribution"));
//  pullPlot->addPlotable(hpull, "P");
//  pullPlot->GetYaxis()->SetLabelSize(0.13);
//  pullPlot->GetXaxis()->SetLabelSize(0.10);
//  pullPlot->GetXaxis()->SetTitleSize(0.10);
//  pullPlot->Draw();
//  line_pull->Draw("same");
//
//  pad_mag->cd();
//  pad_mag->SetTopMargin(0);
//
/////////////////////////////////////////
//  int num_bin_signif = signif_hist->GetMaximumBin();
/////////////////////////////////////////
//  RooPlot* partplot = (RooPlot*)  plot1->Clone();
//  partplot->GetXaxis()->SetRangeUser(9.6,10.8);
//  partplot->GetYaxis()->SetLabelSize(0.13);
//  pad_mag->SetLogy();
//  pad_mag->SetLeftMargin(0);
//
//  if(signif_ratio != -1){
//
//  std::cout << "[INFO] Drawing significance HISTOgram" << std::endl;
//  signif_hist->SetStats(kFALSE);
//  signif_hist->SetFillColor(kRed);
//  signif_hist->Draw();

//  signif_hist->GetXaxis()->SetRange(num_bin_signif, num_bin_signif);
//  }
//  partplot->Draw();

//  pad_leg->cd();
//  RooPlot* legPlot = works->var("mass")->frame(Name("Fit Results"), Title("Fit Results"));
//  RooArgList parList = Result->floatParsFinal();
//  works->pdf(name_model.c_str())->paramOn(legPlot, Layout(0, 0.93, 0.97), Parameters(parList));
//  legPlot->getAttText()->SetTextAlign(11);
//  legPlot->getAttText()->SetTextSize(0.05);
//
//  TPaveText* Ptext = (TPaveText*) legPlot->findObject(Form("%s_paramBox", works->pdf(name_model.c_str())->GetName())); 
//  Ptext->SetY1(0.03);
//  Ptext->SetY2(0.93);
//  Ptext->Draw();
   

  c1->Update();
//  c1->Draw();
  c1->SaveAs(Form("FitMass_NOM_%dS_%d-%dGeV_%d-%dCent.pdf", ab.state, ab.pl, ab.ph, ab.centl, ab.centh));
  c1->Close();

}
