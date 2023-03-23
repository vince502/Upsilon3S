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
void DrawNominalMassDist_v2(){
  DrawNominalMassDist_(ana_bm_comb["3c"][0], 2100019111111);
  DrawNominalMassDist_(ana_bm_comb["2c"][0], 2100019111111);
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
  string name_file_output = GetFit(__FITRESLATEST, false, "CB3:EE:GC", ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1, ab.bpl, ab.bph, 0, "");
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
  vmass->setRange("analysis",8,14);
  if(ab.state ==3) vmass->setRange("signal",10,10.6);
  if(ab.state ==2) vmass->setRange("signal",9.7,10.3);

  gStyle->SetOptTitle(0);
  
  RooPlot* plot1 = vmass->frame(Nmassbins);
  plot1->GetYaxis()->CenterTitle();
  //plot1->GetXaxis()->SetTitle("#it{m}_{#it{#mu}^{+}#it{#mu}^{#font[122]{\55}}} (GeV/#it{c}^{2})"); //Comment remove + -
  plot1->GetXaxis()->SetTitle("#it{m}_{#it{#mu}#it{#mu}} (GeV/#it{c}^{2})");
  plot1->GetXaxis()->CenterTitle();
  plot1->GetYaxis()->SetTitleSize(0.055);
  plot1->GetXaxis()->SetTitleSize(0.055);

  plot1->GetYaxis()->SetLabelSize(0.050);
  plot1->GetXaxis()->SetLabelSize(0.050);

  const float zmscl = 1.5; //Zoom scale for zoomed subplot
  RooPlot* plot1_1 = vmass->frame(Nmassbins* zmscl);
  plot1_1->GetYaxis()->CenterTitle();
  //plot1_1->GetXaxis()->SetTitle("#it{m}_{#it{#mu}^{+}#it{#mu}^{#font[122]{\55}}} (GeV/#it{c}^{2})"); //Comment remove + -
  plot1_1->GetXaxis()->SetTitle("#it{m}_{#it{#mu}#it{#mu}} (GeV/#it{c}^{2})");
  plot1_1->GetXaxis()->CenterTitle();
  plot1_1->GetYaxis()->SetTitleSize(0.055);
  plot1_1->GetXaxis()->SetTitleSize(0.055);

  plot1_1->GetYaxis()->SetLabelSize(0.050);
  plot1_1->GetXaxis()->SetLabelSize(0.050);

  RooPlot* plot2 = vmass->frame();
  plot2->SetAxisRange(10,10.6);
  works->data("reducedDS")->plotOn(plot1, Name("massPlot"), MarkerStyle(kFullCircle), MarkerSize(1.4), LineWidth(1));
  works->data("reducedDS")->plotOn(plot1_1, Name("massPlot_1"), MarkerStyle(kFullCircle), MarkerSize(1.4), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelPlot"), LineWidth(4));
  works->pdf(name_model.c_str())->plotOn(plot1_1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelPlot_1"), LineWidth(4));
  const bool drawSignalOnBkg = false;
  if(!drawSignalOnBkg){
    works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_1S"),Components(RooArgSet(*works->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(4),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
    works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_2S"),Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(4),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
    works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_3S"),Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(4),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
	plot1->GetYaxis()->SetRangeUser(0, 11000);
  }
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelBkg"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(4), LineStyle(5), LineColor(kBlue), MoveToBack() );
  works->pdf(name_model.c_str())->plotOn(plot1_1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelBkg"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(4), LineStyle(5), LineColor(kBlue), MoveToBack() );
  if(drawSignalOnBkg){
	plot1->GetYaxis()->SetLimits(800, 9450);
	plot1->GetYaxis()->SetRangeUser(800, 9450);
    works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_1S"),Components(RooArgSet(*works->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(4),LineStyle(2), LineColor(kOrange+7), MoveToBack(), AddTo("modelBkg", 1., 1.));
    works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_2S"),Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(4),LineStyle(2), LineColor(kOrange+7), MoveToBack(), AddTo("modelBkg", 1., 1.));
    works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_3S"),Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(4),LineStyle(2), LineColor(kOrange+7), MoveToBack(), AddTo("modelBkg", 1., 1.));
	plot1->GetYaxis()->SetRangeUser(800, 9450);
  }
//  works->pdf(name_model.c_str())->plotOn(plot1_1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_3S"),Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack(), AddTo("modelBkg",1., 1.));
 // works->pdf(name_model.c_str())->plotOn(plot1_1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_2S"),Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack(), AddTo("modelBkg", 1., 1.));

/////////////////////////////////////////////////////////////////////////////

  works->data("reducedDS")->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Name("massPlot"), MarkerSize(0.5), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"),  RooFit::NormRange("signal"),Name("modelPlot"), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(4), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(1), LineStyle(2), LineColor(kGreen), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////


	gStyle->SetEndErrorSize(0);

//  setTDRStyle();
  TCanvas* c1 = new TCanvas("c1", "", 800, 810);

  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0.00, 0.00, 1., 1.);
//  TPad* pad_mass_3S = new TPad("pad_mass_3S", "pad_mass_3S", 0.60, 0.43, 0.90, 0.86);
//  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.0, 0.7, 0.25);
//  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.7, 0.25, 1.0, 1.0);
//  TPad* pad_mag = new TPad("pad_mag", "pad_mag", 0.7, 0.0, 1.0, 0.25);
  c1->cd();
  pad_mass->SetTopMargin(0.09);
  pad_mass->SetLeftMargin(0.15);
  pad_mass->SetRightMargin(0.04);
  pad_mass->SetBottomMargin(0.13);
  pad_mass->SetTicks();
  pad_mass->Draw();

//  pad_pull->Draw();
//  pad_leg->Draw();
//  pad_mag->Draw();
  pad_mass->cd();

  plot1->GetYaxis()->SetMaxDigits(2);
  plot1_1->GetYaxis()->SetMaxDigits(2);
  plot1->GetYaxis()->SetLabelOffset(0.015);
  plot1->GetYaxis()->SetTitle("Events / (75 MeV/#it{c}^{2})");
  plot1->Draw("ALP");
//  plot1->GetXaxis()->SetLabelSize(0);
//  plot1->GetXaxis()->SetTitleSize(0);
  TLatex* lt0 = new TLatex();
  FormLatex(lt0, 12, 0.035);
  //lt0->DrawLatex(0.42,0.85, Form("#it{p}_{T}^{#it{#mu}^{+}#it{#mu}^{#font[122]{\55}}} < %d GeV/#it{c}", ab.ph));
  //lt0->DrawLatex(0.42,0.79, Form("|#it{y}^{#it{#mu}^{+}#it{#mu}^{#font[122]{\55}}}| < 2.4")); //Comment remove + - 
  lt0->DrawLatex(0.42,0.845, Form("#it{p}_{T} < %d GeV/#it{c}", ab.ph)); // FR Comment: remove #mu
  lt0->DrawLatex(0.42,0.7985, Form("|#it{y}| < 2.4")); // FR Comment: remove #mu
//  lt0->DrawLatex(0.42,0.73, Form("#it{p}_{T}^{#it{#mu}} > %s GeV/#it{c}", "3.5")); // FR Comment: remove
//  lt0->DrawLatex(0.42,0.67, Form("|#it{#eta}^{#it{#mu}}| < 2.4")); // FR Comment: remove
//  lt0->DrawLatex(0.42,0.62, Form("Centrality 0-90%%")); // FR Comment: move up
  lt0->DrawLatex(0.42,0.75, Form("Centrality 0-90%%"));
  TLegend* leg = new TLegend(0.69, 0.68, 0.93,0.875 );
  leg->SetTextSize(0.035);
  leg->AddEntry("massPlot" ,"Data", "ep");
  leg->AddEntry("modelPlot" ,"Total fit", "l");
  leg->AddEntry("CB3_1S" ,"Signal", "l");
  leg->AddEntry("modelBkg" ,"Background", "l");

  leg->SetBorderSize(0);
  leg->Draw();
//  lt0->DrawLatex(0.20,0.65, Form("Centrality %d-%d %%",ab.centl, ab.centh));

  CMS_lumi_square( pad_mass, 2, 11, -1);

  auto pad_zoom = new TPad("pad_zoom", "", 0.49, 0.28, 0.97, 0.71);
  pad_zoom->SetBottomMargin(0.2);
  pad_zoom->SetLeftMargin(0.23);
  pad_zoom->SetFillStyle(4000);
  pad_zoom->SetGrid();
//  pad_mass->cd();
  c1->cd();
  pad_zoom->Draw("same");
  pad_zoom->cd();
//  auto plotz = (RooPlot*) plot1->Clone("plt_zoom");
  auto plotz = plot1_1;
  plotz->GetXaxis()->SetRangeUser(9.95, 10.7);
  plotz->GetXaxis()->SetNdivisions(5);
  plotz->GetXaxis()->SetLabelSize(plotz->GetXaxis()->GetLabelSize() * 1.8);
  plotz->GetXaxis()->SetTitleSize(plotz->GetXaxis()->GetLabelSize() * 1.0);
//  plotz->GetXaxis()->SetMargin(1.0);
  plotz->GetYaxis()->SetRangeUser(2350 / zmscl, 3550 / zmscl);
  plotz->GetYaxis()->SetNdivisions(5);
  plotz->GetYaxis()->SetLabelSize(plotz->GetYaxis()->GetLabelSize() * 1.8);
  plotz->GetYaxis()->SetTitleSize(plotz->GetYaxis()->GetLabelSize() * 1.0);
  plotz->GetYaxis()->SetTitle("Events / (50 MeV/#it{c}^{2})");

  plotz->GetXaxis()->SetLabelOffset(plotz->GetXaxis()->GetLabelOffset() + 0.01);
  plotz->GetYaxis()->SetLabelOffset(plotz->GetYaxis()->GetLabelOffset() + 0.02);
  plotz->GetXaxis()->SetTitleOffset(plotz->GetXaxis()->GetTitleOffset()*1.0);
  plotz->GetYaxis()->SetTitleOffset(plotz->GetYaxis()->GetTitleOffset()*1.1);
  plotz->GetXaxis()->CenterTitle(kFALSE);
  plotz->GetYaxis()->CenterTitle(kFALSE);
  plotz->Draw("ALP");


  
//  auto pad_zoom = (TPad*) pad_mass->Clone("mass_zoom");
//  pad_zoom->SetPad("pad_zoom", "", 0.5, 0.3, 0.75, 0.55,0,0,0);
//  c1->cd();
//  pad_zoom->Draw();

 // if (draw_mag && train_state ==3){
 //   pad_mass_3S->SetMargin(0.25, 0.01, 0.14, 0.01);
 //   pad_mass_3S->Draw();
 //   pad_mass_3S->cd();
 //   plot2->GetXaxis()->SetLabelSize(0.06);
 //   plot2->GetXaxis()->SetTitleSize(0.06);
 //   plot2->GetXaxis()->SetTitle("mass (GeV/#it{c}^{2}) ");
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
  c1->SaveAs(Form("FitMass_NOM_v2_%ld_%dS_%d-%dGeV_%d-%dCent.pdf", ts, ab.state, ab.pl, ab.ph, ab.centl, ab.centh));
  c1->SaveAs(Form("../checkout/FitMass_NOM_v2_%ld_%dS_%d-%dGeV_%d-%dCent.pdf", ts, ab.state, ab.pl, ab.ph, ab.centl, ab.centh));
  c1->Close();

}
