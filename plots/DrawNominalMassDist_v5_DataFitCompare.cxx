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
void DrawNominalMassDist_v5_DataFitCompare(){
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

//  string whatis_this = "No BDT, Blind data, Unblind fit / 4";
//  string whatis_this = "No BDT, Blind data, fit";
//  string whatis_this = "Nominal, Blind data, Unblind fit / 4";
  string whatis_this = "Nominal, Blind data, fit";

  double bl = Get_BDT(ts_alias(ts), ab);
//  bl = -0.9990 ;
  string name_file_output = GetFit(__FITRESLATEST, false, "CB3:EE:GC", ts_alias(ts), ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1, ab.bpl, ab.bph, 0, "");
  string name_file_blind_output = GetFit(__FITRESLATEST, false, "CB3:EE:GC", ts_alias(ts), ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1, ab.bpl, ab.bph, 0, "");
  std::cout << name_file_output << std::endl;
  TFile* file1 = new TFile(name_file_output.c_str(),"read");
  TFile* file2 = new TFile(name_file_blind_output.c_str(),"read");

  RooWorkspace* works = (RooWorkspace*) file1->Get("workspace");
  works->SetName("workspace_full");
RooWorkspace* works_blind = (RooWorkspace*) file2->Get("workspace");
  works_blind->SetName("workspace_blind");
  std::string name_dataset_result = "fitresult_model_reducedDS";
  std::string name_model = "model";
  if(fitdir.find("GC")!=std::string::npos){
    name_dataset_result = "fitresult_model_gc_reducedDS";
    name_model = "model_gc";
  }
  RooFitResult* Result = (RooFitResult*) file1->Get(name_dataset_result.c_str());

  RooDataSet* dataset = (RooDataSet*) works->data("reducedDS");
  dataset->SetName("reducedDS_full");
  RooDataSet* dataset_blind = (RooDataSet*) works_blind->data("reducedDS");
  dataset_blind->SetName("reducedDS_blind");
  if( dataset->sumEntries() <= 1000) Nmassbins = 35;
  RooRealVar* vmass = (RooRealVar*) works->var("mass");
  double ml =9.6;
  double mh =10.8;
  vmass->setRange("analysis",ml, mh);
  int sf = 5;
  Nmassbins = Nmassbins/sf;
  RooPlot* plot1 = vmass->frame(ml, mh, Nmassbins);
  RooPlot* pullPlot = works->var("mass")->frame(Range("analysis"), Title("Pull Distribution"));


  gStyle->SetOptTitle(0);
  

  std::cout << plot1->GetName() << std::endl;
  RooPlot* plot3 = (RooPlot*) plot1->Clone(); //vmass->frame(Nmassbins);
  std::cout << plot3->GetName() << std::endl;
  plot1->GetYaxis()->CenterTitle();
  plot1->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}} (GeV/c^{2})");
  plot1->GetXaxis()->CenterTitle();
  plot1->GetYaxis()->SetTitleSize(0.055);
  plot1->GetXaxis()->SetTitleSize(0.055);

  plot1->GetYaxis()->SetLabelSize(0.050);
  plot1->GetXaxis()->SetLabelSize(0.050);

  plot3->GetYaxis()->CenterTitle();
  plot3->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}} (GeV/c^{2})");
  plot3->GetXaxis()->CenterTitle();
  plot3->GetYaxis()->SetTitleSize(0.055);
  plot3->GetXaxis()->SetTitleSize(0.055);

  plot3->GetYaxis()->SetLabelSize(0.050);
  plot3->GetXaxis()->SetLabelSize(0.050);

  RooPlot* plot2 = vmass->frame();
//  plot1->SetAxisRange(10,10.8);

  if(ab.state ==3) vmass->setRange("signal",10,10.6);
  if(ab.state ==2) vmass->setRange("signal",9.7,10.3);
  works_blind->data("reducedDS_blind")->plotOn(plot1, Name("massPlot"), Range("analysis"), MarkerStyle(kFullCircle), MarkerSize(1.4), LineWidth(1));
//  works->data("reducedDS")->plotOn(plot3, Name("massPlot"), MarkerStyle(kFullCircle), MarkerSize(1.4), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelPlot"), LineWidth(3));

//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::Normalization(1), Name("CB3_1S"),Components(RooArgSet(*works->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::Normalization(1), Name("CB3_2S"),Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::Normalization(1), Name("CB3_3S"),Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::Normalization(1), Name("modelBkg"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(2), LineStyle(3), LineColor(kBlue), MoveToBack() );
/////////////////////////
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::Normalization( (works->var("nSig1S")->getVal() + works->var("nSig2S")->getVal() + works->var("nSig3S")->getVal() + works->var("nBkg")->getVal() )/ 4 ) , Name("modelPlot"), LineWidth(3));
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::Normalization((works->var("nSig1S")->getVal() + works->var("nSig2S")->getVal() + works->var("nSig3S")->getVal() + works->var("nBkg")->getVal() )/ 4), Name("CB3_1S"),Components(RooArgSet(*works->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::Normalization((works->var("nSig1S")->getVal() + works->var("nSig2S")->getVal() + works->var("nSig3S")->getVal() + works->var("nBkg")->getVal() )/ 4), Name("CB3_2S"),Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::Normalization((works->var("nSig1S")->getVal() + works->var("nSig2S")->getVal() + works->var("nSig3S")->getVal() + works->var("nBkg")->getVal() )/ 4), Name("CB3_3S"),Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::Normalization((works->var("nSig1S")->getVal() + works->var("nSig2S")->getVal() + works->var("nSig3S")->getVal() + works->var("nBkg")->getVal() )/ 4), Name("modelBkg"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(2), LineStyle(3), LineColor(kBlue), MoveToBack() );
//works_blind->data("reducedDS_blind")->plotOn(plot1, Name("massPlot"), MarkerStyle(kFullCircle), MarkerSize(1.4), LineWidth(1), MoveToBack());
/////////////////////////

  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_1S"),Components(RooArgSet(*works->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_2S"),Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("CB3_3S"),Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(2), LineColor(kOrange+7) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelBkg"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(2), LineStyle(3), LineColor(kBlue), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////

 // works->data("reducedDS")->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Name("massPlot"), MarkerSize(0.5), LineWidth(1));
 // works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"),  RooFit::NormRange("signal"),Name("modelPlot"), LineWidth(1));
 // works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(4), LineColor(kRed) , MoveToBack());
 // works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(1), LineStyle(2), LineColor(kGreen), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////

	std::cout <<plot1->getObject(0)->GetName() << ": " <<  ((TGraph*) plot1->getObject(0))->Integral() << std::endl;
	std::cout <<plot1->getObject(1)->GetName() << ": " <<  ((TGraph*) plot1->getObject(1))->Integral() << std::endl;
	std::cout <<plot1->getObject(2)->GetName() << ": " <<  ((TGraph*) plot1->getObject(2))->Integral() << std::endl;
	std::cout <<plot1->getObject(3)->GetName() << ": " <<  ((TGraph*) plot1->getObject(3))->Integral() << std::endl;

	plot1->GetYaxis()->SetTitle("Events / (0.075 GeV/c^2)");
	plot1->GetYaxis()->SetLimits(100 *sf, 300 * sf);
	plot1->GetYaxis()->SetRangeUser( 100 *sf, 300 * sf);


	gStyle->SetEndErrorSize(0);

//  setTDRStyle();
  TCanvas* c1 = new TCanvas("c1", "", 800, 810);


  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0.00, 0.25, 1., 1.);
//  TPad* pad_mass_3S = new TPad("pad_mass_3S", "pad_mass_3S", 0.60, 0.43, 0.90, 0.86);
  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.0, 1.0, 0.25);
//  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.7, 0.25, 1.0, 1.0);
//  TPad* pad_mag = new TPad("pad_mag", "pad_mag", 0.7, 0.0, 1.0, 0.25);
  c1->cd();
  pad_mass->SetTopMargin(0.09);
  pad_mass->SetLeftMargin(0.23);
  pad_mass->SetRightMargin(0.03);
  pad_mass->SetBottomMargin(0.03);
  pad_mass->SetTicks();
  pad_mass->Draw();

  pad_pull->Draw();
//  pad_leg->Draw();
//  pad_mag->Draw();
  pad_mass->cd();
  plot1->GetXaxis()->SetLabelSize(0);
  plot1->GetXaxis()->SetTitleSize(0);
  plot1->Draw("ALP");

  TLatex* lt0 = new TLatex();
  FormLatex(lt0, 12, 0.030);
  lt0->DrawLatex(0.5,0.8, Form("p_{T}^{#mu#mu} < %d GeV/c", ab.ph));
  lt0->DrawLatex(0.5,0.74, Form("|y^{#mu#mu}| < 2.4"));
  lt0->DrawLatex(0.5,0.68, Form("p_{T}^{#mu} > %s GeV/c", "3.5"));
  lt0->DrawLatex(0.5,0.62, Form("|#eta^{#mu}| < 2.4"));
  FormLatex(lt0, 12, 0.035);
  lt0->DrawLatex(0.24,0.93, Form("%s", whatis_this.c_str()));

  TLegend* leg = new TLegend(0.71, 0.42, 0.95,0.7 );
  leg->SetTextSize(0.030);
  leg->AddEntry("massPlot" ,"Data", "ep");
  leg->AddEntry("modelPlot" ,"Total fit", "l");
 // leg->AddEntry("CB3_1S" ,"Signal", "l");
  leg->AddEntry("modelBkg" ,"Background", "l");

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


  pad_pull->cd();
  pad_pull->SetGrid(0,1);
  pad_pull->SetTopMargin(0.00);
  pad_pull->SetBottomMargin(0.30);
  pad_pull->SetLeftMargin(0.23);
  pad_pull->SetRightMargin(0.03);
  TLine* line_pull = new TLine(ml,0., mh, 0.);
  line_pull->SetLineColorAlpha(kRed, 0.5);
  RooHist* hpull = plot1->pullHist("massPlot", "modelPlot");
  pullPlot->addPlotable(hpull, "P");
  pullPlot->GetYaxis()->SetLabelSize(0.13);
  pullPlot->GetXaxis()->SetLabelSize(0.10);
  pullPlot->GetXaxis()->SetTitleSize(0.10);
  pullPlot->Draw();
  line_pull->Draw("same");

  Double_t chi2 = 0.;
  Double_t *ypull = hpull->GetY();
  Double_t Npullbin = 0;
  for(Int_t ibin = 0; ibin < Nmassbins; ibin++){
    if(ypull[ibin] ==0) continue;
    chi2 += TMath::Power(ypull[ibin],2);
    Npullbin++;
  }
  Int_t Nfitpar = Result->floatParsFinal().getSize();
  Int_t ndf = Npullbin - Nfitpar;
  TLatex* NormChi2tex = new TLatex();
  FormLatex(NormChi2tex, 42, 0.10);
//  NormChi2tex->DrawLatex(0.22, 0.15, Form("#chi^{2}/ndf: %3.f/%d", chi2, ndf));

//  pad_mag->cd();
//  pad_mag->SetTopMargin(0);

  CMS_lumi_square( pad_mass, 2, 33);
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
  c1->SaveAs(Form("FitMass_NOMFIT_v5_%ld_%dS_%d-%dGeV_%d-%dCent.pdf", ts, ab.state, ab.pl, ab.ph, ab.centl, ab.centh));
  c1->SaveAs(Form("../checkout/FitMass_NOMFIT_v5_%ld_%dS_%d-%dGeV_%d-%dCent.pdf", ts, ab.state, ab.pl, ab.ph, ab.centl, ab.centh));

//  TCanvas* c2 = new TCanvas("c2", "", 800, 760);
//  TPad* pad_mass_raw = new TPad("pad_mass_raw", "pad_mass_raw", 0.00, 0.00, 1., 1.);
//  pad_mass_raw->SetTopMargin(0.09);
//  pad_mass_raw->SetLeftMargin(0.23);
//  pad_mass_raw->SetRightMargin(0.03);
//  pad_mass_raw->SetBottomMargin(0.15);
//  pad_mass_raw->SetTicks();
//  c2->cd();
//  pad_mass_raw->Draw();
//  pad_mass_raw->cd();
//  plot3->Draw();
//  pad_mass_raw->Draw();
//
//  FormLatex(lt0, 12, 0.030);
//  lt0->DrawLatex(0.5,0.8, Form("p_{T}^{#mu#mu} < %d GeV/c", ab.ph));
//  lt0->DrawLatex(0.5,0.74, Form("|y^{#mu#mu}| < 2.4"));
//  lt0->DrawLatex(0.5,0.68, Form("p_{T}^{#mu} > %s GeV/c", "3.5"));
//  lt0->DrawLatex(0.5,0.62, Form("|#eta^{#mu}| < 2.4"));
//  TLegend* leg2 = new TLegend(0.71, 0.52, 0.95,0.6 );
//  leg2->SetTextSize(0.030);
//  leg2->AddEntry("massPlot" ,"Data", "ep");
//
//  leg2->SetBorderSize(0);
//  leg2->Draw();
//
//  CMS_lumi_square( pad_mass_raw, 2, 33);
//  c2->Update();
//  c2->Draw();
//
//  c2->SaveAs(Form("FitMass_NOMRAW_v5_%ld_%dS_%d-%dGeV_%d-%dCent.pdf", ts, ab.state, ab.pl, ab.ph, ab.centl, ab.centh));
//  c2->SaveAs(Form("../checkout/FitMass_NOMRAW_v5_%ld_%dS_%d-%dGeV_%d-%dCent.pdf", ts, ab.state, ab.pl, ab.ph, ab.centl, ab.centh));
  c1->Clear();
//  c2->Clear();
}
