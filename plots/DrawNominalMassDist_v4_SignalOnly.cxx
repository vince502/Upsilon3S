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
void DrawNominalMassDist_v4_SignalOnly(){
  DrawNominalMassDist_(ana_bm_comb["3c"][0], 200019111111);
//  DrawNominalMassDist_(ana_bm_comb["2c"][0], 200019111111);
//  DrawNominalMassDist_(ana_bm_comb["3c"][0], 10000000016);
//  DrawNominalMassDist_(ana_bm_comb["2c"][0], 10000000016);
};
void DrawNominalMassDist_(ana_bins ab, long ts = 9999999999){
  int Nmassbins = 80;
  string fitdir = "GC";
  string name_fitmodel = "_CB3_EE";
  string name_sig_pdf = "threeCB";
  string name_pdf_bkg = "bkgErf";

  double bl = Get_BDT(ts_alias(ts), ab);
  string name_file_output = GetFit(__FITRESLATEST, false, "CB3:EE:GC", ts_alias(ts), ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1, ab.bpl, ab.bph, 0, "");
  string name_file_full_output = GetFit(__FITRESLATEST, false, "CB3:EE:GC", ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1, ab.bpl, ab.bph, 0, "");
  std::cout << name_file_output << std::endl;
  TFile* file1 = new TFile(name_file_output.c_str(),"read");
  TFile* file2 = new TFile(name_file_full_output.c_str(),"read");

  RooWorkspace* works = (RooWorkspace*) file1->Get("workspace");
  works->SetName("workspace_blind");
  RooWorkspace* works_full = (RooWorkspace*) file2->Get("workspace");
  works_full->SetName("workspace_full");
  std::string name_dataset_result = "fitresult_model_reducedDS";
  std::string name_model = "model";
  if(fitdir.find("GC")!=std::string::npos){
    name_dataset_result = "fitresult_model_gc_reducedDS";
    name_model = "model_gc";
  }
  RooFitResult* Result = (RooFitResult*) file1->Get(name_dataset_result.c_str());
  RooFitResult* Result_full = (RooFitResult*) file2->Get(name_dataset_result.c_str());

  RooDataSet* dataset = (RooDataSet*) works->data("reducedDS");
  dataset->SetName("reducedDS_blind");
  RooDataSet* dataset_full = (RooDataSet*) works_full->data("reducedDS");
  dataset_full->SetName("reducedDS_full");
  if( dataset->sumEntries() <= 1000) Nmassbins = 35;
  RooRealVar* vmass = (RooRealVar*) works->var("mass");
  vmass->SetName("mass_blind");
  RooRealVar* vmass_full = (RooRealVar*) works_full->var("mass");
  vmass_full->SetName("mass_full");
  vmass->setRange("analysis",8,14);
  vmass_full->setRange("analysis_full",8,14);
  if(ab.state ==3) vmass->setRange("signal",10,10.6);
  if(ab.state ==2) vmass->setRange("signal",9.7,10.3);

  if(ab.state ==3) vmass_full->setRange("signal_full",10,10.6);
  if(ab.state ==2) vmass_full->setRange("signal_full",9.7,10.3);

  gStyle->SetOptTitle(0);
  
  RooPlot* plot1 = vmass->frame(Nmassbins);
  RooPlot* plot2 = vmass_full->frame(Nmassbins);
  std::cout << plot1->GetName() << std::endl;
  plot1->GetYaxis()->CenterTitle();
  plot1->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}} (GeV/c^{2})");
  plot1->GetXaxis()->CenterTitle();
  plot1->GetYaxis()->SetTitleSize(0.055);
  plot1->GetXaxis()->SetTitleSize(0.055);

  plot1->GetYaxis()->SetLabelSize(0.050);
  plot1->GetXaxis()->SetLabelSize(0.050);

  plot2->GetYaxis()->CenterTitle();
  plot2->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}} (GeV/c^{2})");
  plot2->GetXaxis()->CenterTitle();
  plot2->GetYaxis()->SetTitleSize(0.055);
  plot2->GetXaxis()->SetTitleSize(0.055);

  plot2->GetYaxis()->SetLabelSize(0.050);
  plot2->GetXaxis()->SetLabelSize(0.050);
// works->data("reducedDS")->plotOn(plot1, Name("massPlot"), MarkerStyle(kFullCircle), MarkerSize(1.4), LineWidth(1));
//  works->data("reducedDS")->plotOn(plot3, Name("massPlot"), MarkerStyle(kFullCircle), MarkerSize(1.4), LineWidth(1));
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelPlot"), LineWidth(3));

  works->pdf("threeCB1S")->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
  works->pdf("threeCB2S")->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
  works->pdf("threeCB3S")->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
  works->pdf("bkgErf")->plotOn(plot1, Range("analysis"), RooFit::Normalization(4), RooFit::NormRange("analysis"), LineWidth(2),LineStyle(2), LineColor(kOrange+3) , MoveToBack());

  works_full->pdf("threeCB1S")->plotOn(plot2, Range("analysis"), RooFit::NormRange("analysis"), LineWidth(2),LineStyle(3), LineColor(kTeal+1) , MoveToBack());
  works_full->pdf("threeCB2S")->plotOn(plot2, Range("analysis"), RooFit::NormRange("analysis"), LineWidth(2),LineStyle(3), LineColor(kTeal+1) , MoveToBack());
  works_full->pdf("threeCB3S")->plotOn(plot2, Range("analysis"), RooFit::NormRange("analysis"), LineWidth(2),LineStyle(3), LineColor(kTeal+1) , MoveToBack());
  works_full->pdf("bkgErf")->plotOn(plot2, Range("analysis"), RooFit::Normalization(4), RooFit::NormRange("analysis"), LineWidth(2),LineStyle(3), LineColor(kTeal-3) , MoveToBack());

 // works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_1S"),Components(RooArgSet(*works->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
 // works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_2S"),Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
 // works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_3S"),Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());

 // works_full->pdf(name_model.c_str())->plotOn(plot2, Range("analysis_full"), RooFit::NormRange("analysis_full"), Name("CB3_1S"),Components(RooArgSet(*works_full->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(3), LineColor(kRed-1) , MoveToBack());
 // works_full->pdf(name_model.c_str())->plotOn(plot2, Range("analysis_full"), RooFit::NormRange("analysis_full"), Name("CB3_2S"),Components(RooArgSet(*works_full->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(3), LineColor(kRed-1) , MoveToBack());
 // works_full->pdf(name_model.c_str())->plotOn(plot2, Range("analysis_full"), RooFit::NormRange("analysis_full"), Name("CB3_3S"),Components(RooArgSet(*works_full->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(3), LineColor(kRed-1) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelBkg"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(2), LineStyle(3), LineColor(kBlue), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////

//  works->data("reducedDS")->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Name("massPlot"), MarkerSize(0.5), LineWidth(1));
//  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"),  RooFit::NormRange("signal"),Name("modelPlot"), LineWidth(1));
//  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(4), LineColor(kRed) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(1), LineStyle(2), LineColor(kGreen), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////


	gStyle->SetEndErrorSize(0);

//  setTDRStyle();
  TCanvas* c1 = new TCanvas("c1", "", 800, 810);

  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0.00, 0.0, 1., 1.);
//  TPad* pad_mass_3S = new TPad("pad_mass_3S", "pad_mass_3S", 0.60, 0.43, 0.90, 0.86);
  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.0, 1.0, 0.25);
//  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.7, 0.25, 1.0, 1.0);
//  TPad* pad_mag = new TPad("pad_mag", "pad_mag", 0.7, 0.0, 1.0, 0.25);
  c1->cd();
  pad_mass->SetTopMargin(0.09);
  pad_mass->SetLeftMargin(0.18);
  pad_mass->SetRightMargin(0.03);
  pad_mass->SetBottomMargin(0.13);
  pad_mass->SetTicks();
  pad_mass->Draw();

//  pad_pull->Draw();
//  pad_leg->Draw();
//  pad_mag->Draw();
  pad_mass->cd();
  plot1->GetXaxis()->SetLabelSize(0.032);
  plot1->GetXaxis()->SetTitleSize(0.035);

  plot1->GetYaxis()->SetTitle("a.u.");
  plot1->GetYaxis()->SetTitleSize(0.035);
  plot1->GetYaxis()->SetLabelSize(0.032);

  plot1->Draw("ALP");
  plot2->Draw("L same");


  TLatex* lt0 = new TLatex();
  FormLatex(lt0, 12, 0.030);
  lt0->DrawLatex(0.52,0.8, Form("p_{T}^{#mu#mu} < %d GeV/c", ab.ph));
  lt0->DrawLatex(0.52,0.74, Form("|y^{#mu#mu}| < 2.4"));
  lt0->DrawLatex(0.52,0.68, Form("p_{T}^{#mu} > %s GeV/c", "3.5"));
  lt0->DrawLatex(0.52,0.62, Form("|#eta^{#mu}| < 2.4"));
  TLegend* leg = new TLegend(0.66, 0.33, 0.95,0.57 );
  leg->SetTextSize(0.030);
  leg->AddEntry(plot1->getObject(3),"Signal Blind", "l");
  leg->AddEntry(plot2->getObject(3),"Signal Full", "l");
  leg->AddEntry(plot1->getObject(0),"Background Blind", "l");
  leg->AddEntry(plot2->getObject(0),"Background Full", "l");
  std::cout<<( (TGraph*) plot1->getObject(0))->Integral(8, 14) << std::endl ;
  std::cout<<( (TGraph*) plot1->getObject(1))->Integral(8, 14) << std::endl ;
  std::cout<<( (TGraph*) plot1->getObject(2))->Integral(8, 14) << std::endl ;

  leg->SetBorderSize(0);
  leg->Draw();
//  lt0->DrawLatex(0.20,0.65, Form("Centrality %d-%d %%",ab.centl, ab.centh));
  

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
//  pad_pull->SetLeftMargin(0.23);
//  pad_pull->SetRightMargin(0.03);
//  TLine* line_pull = new TLine(8.,0., 14., 0.);
//  line_pull->SetLineColorAlpha(kRed, 0.5);
//
//  pullPlot->addPlotable(hpull, "P");
//  pullPlot->GetYaxis()->SetLabelSize(0.13);
//  pullPlot->GetXaxis()->SetLabelSize(0.10);
//  pullPlot->GetXaxis()->SetTitleSize(0.10);
//  pullPlot->Draw();
//  line_pull->Draw("same");
  CMS_lumi_square( pad_mass, 2, 33);
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
  c1->SaveAs(Form("FitMass_NOMSIG_v4_%ld_%dS_%d-%dGeV_%d-%dCent.pdf", ts, ab.state, ab.pl, ab.ph, ab.centl, ab.centh));
  c1->SaveAs(Form("../checkout/FitMass_NOMSIG_v4_%ld_%dS_%d-%dGeV_%d-%dCent.pdf", ts, ab.state, ab.pl, ab.ph, ab.centl, ab.centh));
  c1->Clear();
}
