#pragma once
//#include "./BDT/bininfo.h"
#include <iostream>
#include <string>
#include "CMS_lumi_square.C"
#include "./BDT/bininfo.h"
#include "tdrstyle.C"
#include "TFile.h"
#include "RooPlot.h"
#include "RooFit.h"
#include "TROOT.h"


using namespace RooFit;

void DrawHistMC_(long ts,double ylim, float blow, float bhigh, float vcut, TString MupT = "3p5", string Trig = "S13", TString fittype = "freefit", string opt = "") {};
void DrawHistMC__();
void DrawHistMC(std::vector<std::string>  parsed,const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString MupT = "3p5", const string Trig = "", bool swflag= false, int cBinLow =0, int cBinHigh = 180, double cutQVP = 0.01, bool isBDT=true, long ts = 1, double cutBDTlow=-1, double cutBDThigh = 1., int bdtptMin =0, int bdtptMax = 30, double signif_ratio = 0.02,  int train_state =3, int sig_state= 3, bool draw_mag = false, double massMin= 8, double massMax = 14, string aux = "", string opt = ""){
  setTDRStyle();
  int Nmassbins = 80;

  std::string sig_func = parsed[0];
  std::string bkg_func = parsed[1];
  std::string fitdir = parsed[2];
  std::string name_fitmodel = "_"+sig_func+"_"+bkg_func;
  std::string name_sig_pdf = "twoCB";
  if(sig_func=="CB3"){
    name_sig_pdf = "threeCB";
  }
  if(sig_func=="CB2G"){
    name_sig_pdf = "twoCBGaus";
  }
  string fit_param, name_pdf_bkg, name_pdf_sig;
  if(fitdir.find("FF") != std::string::npos){
    fit_param = "freefit";
    if(fitdir.find("DD") != std::string::npos) fit_param = "iterative_fix";
  }
  if(fitdir.find("GC")!=std::string::npos) fit_param = "gaussconst";
  if(fitdir.find("DR")!=std::string::npos) {
    if(fitdir.find("DR2")!=std::string::npos) {
      fit_param = fit_param + "_DoubleRatio2";
    }
    else fit_param = fit_param + "_DoubleRatio";
  }
  if(bkg_func.find("EE")!= std::string::npos) name_pdf_bkg = "bkgErf";
  if(bkg_func.find("EX")!= std::string::npos) name_pdf_bkg = "Expo";
  if(bkg_func.find("CC")!= std::string::npos){
    name_pdf_bkg = "CCBkg";
    if(bkg_func.find("ECC")!= std::string::npos){
      name_pdf_bkg = "bkgECC";
      }
  }
  string s_bdtupdown = "";
  if(fitdir.find("bdt")!= std::string::npos){
    if(fitdir.find("bdtup")!=std::string::npos) s_bdtupdown = "SYSUP";
    if(fitdir.find("bdtdown")!=std::string::npos)  s_bdtupdown = "SYSDOWN";
  }

  int ylim10 = (int) (rapMax*10);
  int DDiter =0;
  std::pair<double, TGraph*> _hist_;
  TGraph* signif_hist;
  if( signif_ratio != -1){
    _hist_ = Get_Optimal_BDT(ts, ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP, signif_ratio, train_state, sig_state, bdtptMin, bdtptMax, "", "S2", s_bdtupdown.c_str()); 
    signif_hist = _hist_.second;
    if (signif_hist ==nullptr) {
      std::cout << "[Error] Significance plot not loaded, returning with null histogram" << std::endl;
      new(signif_hist) TGraph();
    }
  }

  std::string method_selection = (isBDT) ? "BDT" : "Data"; 
  long kts = (cutBDTlow != -1.0000) ? ts : 9999999999;
//  if(strcmp(aux.c_str(),"")!= 0 ) aux = "_"+aux;
  string type = Form("%s:%s:%s",parsed[0].c_str(), parsed[1].c_str(), parsed[2].c_str());
  std::string name_file_output = GetFit(__FITRESLATEST, true, sig_func, kts, train_state, sig_state, (int) ptMin, (int) ptMax, cBinLow, cBinHigh, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, aux);
//  std::string name_file_output = Form("%s/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f%s.root" ,workdir.Data(), kts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, aux.c_str() );
// if(ts >= 1634636609) name_file_output = Form("%s/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f%s.root" ,workdir.Data(), train_state, kts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, aux.c_str() );
  std::cout << name_file_output << std::endl;
  if( fitdir.find("DD") !=std::string::npos)
  {
    DDiter = fitdir[4] -48;
    name_file_output = name_file_output.substr(0, name_file_output.length()-5) + Form("_DDiter%d.root",DDiter);
  }
  TFile* file1 = new TFile(Form("%s/%s", workdir.Data(), name_file_output.c_str()),"read");
  string alt = "";
  if( strcmp(opt.c_str(),"")!=0) alt = "/"+opt;
  TString massDIR_base = Form("%s/MassDist/%s/%ld%s/Cent%d-%d_Pt%d-%d_y%.1f/%d/MC_BW", workdir.Data(), method_selection.c_str(), kts, alt.c_str(), cBinLow, cBinHigh, (int) ptMin, (int) ptMax, rapMax, sig_state);
  TString massDIR =massDIR_base;
  TString massDIRp = Form("%s/png", massDIR_base.Data() );
//  TString massDIR2 = Form("%s/MassDist/%s/%ld/%s/%s/%.1f/cent%d-%d/pT%.1f-%.1f/WithoutFit", workdir.Data(), method_selection.c_str(), ts, fit_param.c_str(),Trig.c_str(),rapMax, cBinLow, cBinHigh, ptMin, ptMax);
  void * dirpM = gSystem->OpenDirectory(massDIR.Data());
  if(dirpM) gSystem->FreeDirectory(dirpM);
  else{ gSystem->mkdir(massDIR.Data(), kTRUE);}
  void * dirpMp = gSystem->OpenDirectory(massDIRp.Data());
  if(dirpMp) gSystem->FreeDirectory(dirpMp);
  else gSystem->mkdir(massDIRp.Data(), kTRUE);



  RooWorkspace* works = (RooWorkspace*) file1->Get("workspace");
  std::string name_dataset_result = "fitresult_model_reducedDS";
  std::string name_model = "model";
  RooFitResult* Result = (RooFitResult*) file1->Get(name_dataset_result.c_str());

  RooDataSet* dataset = (RooDataSet*) works->data("reducedDS");
  if( dataset->sumEntries() <= 1000) Nmassbins = 60;
  RooRealVar* vmass = (RooRealVar*) works->var("mass");
  vmass->setRange("analysis",massMin,massMax);
  if(train_state ==3) vmass->setRange("signal",10,10.6);
  if(train_state ==2) vmass->setRange("signal",9.7,10.3);

  gStyle->SetOptTitle(0);

  RooPlot* plot1;

  TList* lst = file1->GetListOfKeys();
  string name_plotobj;

  for( auto item : *lst){
	if(string(item->GetName()).find("frame_mass") != std::string::npos) name_plotobj  = item->GetName();
  }
  plot1 =  (RooPlot*) file1->Get(name_plotobj.c_str() ); 
  Nmassbins = (plot1->GetXaxis()->GetXmax() - plot1->GetXaxis()->GetXmin()) * 30;
  
//  RooPlot* plot1 = vmass->frame(Nmassbins);
//  RooPlot* plot2 = vmass->frame();
//  plot2->SetAxisRange(10,10.6);
//  works->data("reducedDS")->plotOn(plot1, Name("massPlot"), MarkerSize(0.5), LineWidth(1));
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelPlot"), LineWidth(1));
//
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Components(RooArgSet(*works->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(1), LineStyle(1), LineColor(kGreen), MoveToBack() );
//
///////////////////////////////////////////////////////////////////////////////
//
//  works->data("reducedDS")->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Name("massPlot"), MarkerSize(0.5), LineWidth(1));
//  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"),  RooFit::NormRange("signal"),Name("modelPlot"), LineWidth(1));
//  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
//  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(1), LineStyle(1), LineColor(kGreen), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////

  TCanvas* c1 = new TCanvas("c1", "", 1100, 800);
  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.7, 0.94);
  TPad* pad_mass_3S = new TPad("pad_mass_3S", "pad_mass_3S", 0.62, 0.43, 0.92, 0.86);
  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.0, 0.7, 0.25);
  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.7, 0.25, 1.0, 1.0);
  TPad* pad_mag = new TPad("pad_mag", "pad_mag", 0.7, 0.0, 1.0, 0.25);
  c1->cd();
  pad_mass->SetBottomMargin(0.04);
  pad_mass->Draw();

  pad_pull->Draw();
  pad_leg->Draw();
  pad_mag->Draw();
  pad_mass->cd();
  plot1->Draw("ALP");
  plot1->GetXaxis()->SetLabelSize(0);
  plot1->GetXaxis()->SetTitleSize(0);
  TLatex* lt0 = new TLatex();
  FormLatex(lt0, 12, 0.033);
  lt0->DrawLatex(0.24,0.80, Form("BDT #in [%.2f, %.2f]",cutBDTlow, cutBDThigh));
  lt0->DrawLatex(0.24,0.75, Form("%d #leq BDT train p_{T} < %d GeV/c",bdtptMin, bdtptMax));
  double simu_pt = 3.5;
  lt0->DrawLatex(0.24,0.70, Form("p_{T}^{#mu} #geq %.1f GeV/c",simu_pt));
  lt0->DrawLatex(0.24,0.65, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int) ptMin, (int) ptMax));
  lt0->DrawLatex(0.24,0.60, Form("Centrality %d-%d %%",(int) cBinLow/2, (int) cBinHigh/2));
//  lt0->SetTextSize(0.03);
//  lt0->DrawLatex(0.42,0.55, Form("Trigger : %s", "HLT_HIL3Mu2p5NHitQ10 L2Mu2 M7toinf v1"));
  
  CMS_lumi_square( pad_mass, 2, 11);

//  if (draw_mag && train_state ==3){
//    pad_mass_3S->SetMargin(0.25, 0.01, 0.14, 0.01);
//    pad_mass_3S->Draw();
//    pad_mass_3S->cd();
//    plot2->GetXaxis()->SetLabelSize(0.06);
//    plot2->GetXaxis()->SetTitleSize(0.06);
//    plot2->GetXaxis()->SetTitle("mass (GeV/c^{2}) ");
//    plot2->GetXaxis()->SetTitleOffset(1.1);
//    plot2->GetYaxis()->SetLabelSize(0.08);
//    plot2->GetYaxis()->SetTitleSize(0.06);
//    plot2->GetYaxis()->SetTitleOffset(1.65);
//    plot2->GetYaxis()->SetRangeUser(0, (plot1->GetMaximum()/2.0));
//    plot2->Draw();
//  }


  pad_pull->cd();
  pad_pull->SetGrid(0,1);
  pad_pull->SetTopMargin(0.00);
  pad_pull->SetBottomMargin(0.30);
  TLine* line_pull = new TLine(plot1->GetXaxis()->GetXmin() ,0., plot1->GetXaxis()->GetXmax(), 0.);
  line_pull->SetLineColorAlpha(kRed, 0.5);
  RooHist* hpull = plot1->pullHist("massPlot", "modelPlot");

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

  RooPlot* pullPlot = works->var("mass")->frame(Title("Pull Distribution"));
  pullPlot->addPlotable(hpull, "P");
  pullPlot->GetYaxis()->SetLabelSize(0.13);
  pullPlot->GetXaxis()->SetLabelSize(0.10);
  pullPlot->GetXaxis()->SetTitleSize(0.10);
  pullPlot->Draw();
  line_pull->Draw("same");
  TLatex* NormChi2tex = new TLatex();
  FormLatex(NormChi2tex, 42, 0.10);
  NormChi2tex->DrawLatex(0.16, 0.15, Form("#chi^{2}/ndf: %3.f/%d", chi2, ndf));

  pad_mag->cd();
  pad_mag->SetTopMargin(0);

/////////////////////////////////////////
//  int num_bin_signif = signif_hist->GetMaximumBin();
/////////////////////////////////////////
//  RooPlot* partplot = (RooPlot*)  plot1->Clone();
//  partplot->GetXaxis()->SetRangeUser(9.6,10.8);
//  partplot->GetYaxis()->SetLabelSize(0.13);
//  pad_mag->SetLogy();
  pad_mag->SetLeftMargin(0);

//  if(signif_ratio != -1){
//
//  std::cout << "[INFO] Drawing significance HISTOgram" << std::endl;
////  signif_hist->SetStats(kFALSE);
//  signif_hist->SetFillColor(kRed);
//  signif_hist->SetMarkerStyle(kFullCircle);
//  auto ycol = signif_hist->GetY();
//  double ymax = TMath::MaxElement(signif_hist->GetN(), ycol);
//  signif_hist->SetMarkerSize(0.5);
//  signif_hist->Draw("AP");
//
////  TLine histL(cutBDTlow, signif_hist->GetYaxis()->GetXmin(), cutBDTlow, ymax);
//  TLine histL(cutBDTlow, 0, cutBDTlow, 1);
//  TMarker histP(cutBDTlow, ymax, kFullCircle);
//  histL.SetLineStyle(kDashDotted);
//  histP.SetMarkerSize(0.6);
//  histP.SetMarkerColor(kRed);
//
//  histP.Draw("same");
//  histL.Draw("same");
//
////  signif_hist->GetXaxis()->SetRange(num_bin_signif, num_bin_signif);
//  }
//  partplot->Draw();

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
//  c1->Draw();
//  c1->SaveAs(Form("%s/FitPlot_train%dS_Sig%d_%ld_%s_%s-%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f%s.pdf",massDIR.Data(), train_state, sig_state, ts,fitdir.c_str(), sig_func.c_str(), bkg_func.c_str(), (int) (ptMin*10), (int) (ptMax*10), ylim10, ylim10, Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(),(int) swflag,(int) isBDT, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, aux.c_str()));
  c1->SaveAs(Form("/home/vince402/Upsilon3S/%s/%s_MassDistribution_%dS_pt_%d-%d_rap_%d-%d_%dbin_noWeight_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_fix%d_v2.pdf", massDIR.Data(), sig_func.c_str(), sig_state,(int)(ptMin*10), (int)(ptMax*10), -ylim10,ylim10, Nmassbins, MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, 0));
  c1->Close();

};





void DrawHistMC(TFile* file1 ){
  RooWorkspace* works = (RooWorkspace*) file1->Get("workspace");
  std::string name_dataset_result = "fitresult_model_reducedDS";
  std::string name_model = "model";
  RooFitResult* Result = (RooFitResult*) file1->Get(name_dataset_result.c_str());

  int Nmassbins = 70;
  RooDataSet* dataset = (RooDataSet*) works->data("reducedDS");
  if( dataset->sumEntries() <= 1000) Nmassbins = 60;
  RooRealVar* vmass = (RooRealVar*) works->var("mass");
//  vmass->setRange("analysis",massMin,massMax);
//  if(train_state ==3) vmass->setRange("signal",10,10.6);
//  if(train_state ==2) vmass->setRange("signal",9.7,10.3);

  gStyle->SetOptTitle(0);

  RooPlot* plot1;

  TList* lst = file1->GetListOfKeys();
  string name_plotobj;

  for( auto item : *lst){
	if(string(item->GetName()).find("frame_mass") != std::string::npos) name_plotobj  = item->GetName();
  }
  plot1 =  (RooPlot*) file1->Get(name_plotobj.c_str() ); 
  Nmassbins = (plot1->GetXaxis()->GetXmax() - plot1->GetXaxis()->GetXmin()) * 30;
  

  TCanvas* c1 = new TCanvas("c1", "", 1100, 800);
  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.7, 0.94);
  TPad* pad_mass_3S = new TPad("pad_mass_3S", "pad_mass_3S", 0.62, 0.43, 0.92, 0.86);
  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.0, 0.7, 0.25);
  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.7, 0.25, 1.0, 1.0);
  TPad* pad_mag = new TPad("pad_mag", "pad_mag", 0.7, 0.0, 1.0, 0.25);
  c1->cd();
  pad_mass->SetBottomMargin(0.04);
  pad_mass->Draw();

  pad_pull->Draw();
  pad_leg->Draw();
  pad_mag->Draw();
  pad_mass->cd();
  plot1->Draw("ALP");
  plot1->GetXaxis()->SetLabelSize(0);
  plot1->GetXaxis()->SetTitleSize(0);
 // TLatex* lt0 = new TLatex();
 // FormLatex(lt0, 12, 0.033);
 // lt0->DrawLatex(0.24,0.80, Form("BDT #in [%.2f, %.2f]",cutBDTlow, cutBDThigh));
 // lt0->DrawLatex(0.24,0.75, Form("%d #leq BDT train p_{T} < %d GeV/c",bdtptMin, bdtptMax));
 // double simu_pt = 3.5;
 // lt0->DrawLatex(0.24,0.70, Form("p_{T}^{#mu} #geq %.1f GeV/c",simu_pt));
 // lt0->DrawLatex(0.24,0.65, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int) ptMin, (int) ptMax));
 // lt0->DrawLatex(0.24,0.60, Form("Centrality %d-%d %%",(int) cBinLow/2, (int) cBinHigh/2));
  
  CMS_lumi_square( pad_mass, 2, 11);



  pad_pull->cd();
  pad_pull->SetGrid(0,1);
  pad_pull->SetTopMargin(0.00);
  pad_pull->SetBottomMargin(0.30);
  TLine* line_pull = new TLine(plot1->GetXaxis()->GetXmin() ,0., plot1->GetXaxis()->GetXmax(), 0.);
  line_pull->SetLineColorAlpha(kRed, 0.5);
  RooHist* hpull = plot1->pullHist("massPlot", "modelPlot");

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

  RooPlot* pullPlot = works->var("mass")->frame(Title("Pull Distribution"));
  pullPlot->addPlotable(hpull, "P");
  pullPlot->GetYaxis()->SetLabelSize(0.13);
  pullPlot->GetXaxis()->SetLabelSize(0.10);
  pullPlot->GetXaxis()->SetTitleSize(0.10);
  pullPlot->Draw();
  line_pull->Draw("same");
  TLatex* NormChi2tex = new TLatex();
  FormLatex(NormChi2tex, 42, 0.10);
  NormChi2tex->DrawLatex(0.16, 0.15, Form("#chi^{2}/ndf: %3.f/%d", chi2, ndf));

  pad_mag->cd();
  pad_mag->SetTopMargin(0);

/////////////////////////////////////////
//  int num_bin_signif = signif_hist->GetMaximumBin();
/////////////////////////////////////////
//  RooPlot* partplot = (RooPlot*)  plot1->Clone();
//  partplot->GetXaxis()->SetRangeUser(9.6,10.8);
//  partplot->GetYaxis()->SetLabelSize(0.13);
//  pad_mag->SetLogy();
  pad_mag->SetLeftMargin(0);

//  if(signif_ratio != -1){
//
//  std::cout << "[INFO] Drawing significance HISTOgram" << std::endl;
////  signif_hist->SetStats(kFALSE);
//  signif_hist->SetFillColor(kRed);
//  signif_hist->SetMarkerStyle(kFullCircle);
//  auto ycol = signif_hist->GetY();
//  double ymax = TMath::MaxElement(signif_hist->GetN(), ycol);
//  signif_hist->SetMarkerSize(0.5);
//  signif_hist->Draw("AP");
//
////  TLine histL(cutBDTlow, signif_hist->GetYaxis()->GetXmin(), cutBDTlow, ymax);
//  TLine histL(cutBDTlow, 0, cutBDTlow, 1);
//  TMarker histP(cutBDTlow, ymax, kFullCircle);
//  histL.SetLineStyle(kDashDotted);
//  histP.SetMarkerSize(0.6);
//  histP.SetMarkerColor(kRed);
//
//  histP.Draw("same");
//  histL.Draw("same");
//
////  signif_hist->GetXaxis()->SetRange(num_bin_signif, num_bin_signif);
//  }
//  partplot->Draw();

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
 // c1->SaveAs(Form("/home/vince402/Upsilon3S/%s/%s_MassDistribution_%dS_pt_%d-%d_rap_%d-%d_%dbin_noWeight_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_fix%d_v2.pdf", massDIR.Data(), sig_func.c_str(), sig_state,(int)(ptMin*10), (int)(ptMax*10), -ylim10,ylim10, Nmassbins, MupT.Data(), Trig.c_str(), cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, 0));
 // c1->Close();

};




void DrawHistMC__(){
  DrawHistMC({"CB3","CC4","FF"}, 0, 30, -2.4, 2.4, "3p5", "S13", false, 0 ,180, 0.00, true, 1623391157, -1, 1, 70);
}
