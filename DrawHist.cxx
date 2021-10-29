#include <iostream>
#include <string>
#include "CMS_lumi_square.C"
#include "tdrstyle.C"
#include "TFile.h"
#include "RooPlot.h"
#include "RooFit.h"
#include "TROOT.h"
#include "./BDT/bininfo.h"

using namespace RooFit;

void DrawHist_(long ts,double ylim, float blow, float bhigh, float vcut, TString MupT = "3p5", string Trig = "S13", TString fittype = "freefit") {};
void DrawHist__();
void DrawHist(std::vector<std::string>  parsed,const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString MupT = "3p5", const string Trig = "", bool swflag= false, int cBinLow =0, int cBinHigh = 180, double cutQVP = 0.01, bool isBDT=true, long ts = 1, double cutBDTlow=-1, double cutBDThigh = 1., double signif_ratio = 0.02,  int train_state =3, bool draw_mag = false, string aux = ""){
  setTDRStyle();
  int Nmassbins = 140;

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
  std::pair<double, TH1D*> _hist_;
  TH1D* signif_hist;
  if( signif_ratio != -1){
    _hist_ = Get_Optimal_BDT(ts, ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP, signif_ratio, train_state, "", "S2", s_bdtupdown.c_str()); 
    signif_hist = _hist_.second;
    if (signif_hist ==nullptr) {
      std::cout << "[Error] Significance plot not loaded, returning with null histogram" << std::endl;
      new(signif_hist) TH1D("NULLPATCH", "", 1,0,1);
    }
  }

  std::string method_selection = (isBDT) ? "BDT" : "Data"; 
//  if(strcmp(aux.c_str(),"")!= 0 ) aux = "_"+aux;
  std::string name_file_output = Form("%s/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f%s.root" ,workdir.Data(), ts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, cutQVP, aux.c_str() );
 if(ts >= 1634636609) name_file_output = Form("%s/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f%s.root" ,workdir.Data(), train_state, ts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, cutQVP, aux.c_str() );
  std::cout << name_file_output << std::endl;
  if( fitdir.find("DD") !=std::string::npos)
  {
    DDiter = fitdir[4] -48;
    name_file_output = name_file_output.substr(0, name_file_output.length()-5) + Form("_DDiter%d.root",DDiter);
  }
  TFile* file1 = new TFile(name_file_output.c_str(),"read");
  TString massDIR_base = Form("%s/MassDist/%s/%ld/Cent%d-%d_Pt%d-%d_y%.1f/%d/%s", workdir.Data(), method_selection.c_str(), ts, cBinLow, cBinHigh, (int) ptMin, (int) ptMax, rapMax, train_state, fit_param.c_str());
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
  if(fitdir.find("GC")!=std::string::npos){
    name_dataset_result = "fitresult_model_gc_reducedDS";
    name_model = "model_gc";
  }
  RooFitResult* Result = (RooFitResult*) file1->Get(name_dataset_result.c_str());

  RooDataSet* dataset = (RooDataSet*) works->data("reducedDS");
  if( dataset->sumEntries() <= 1000) Nmassbins = 35;
  RooRealVar* vmass = (RooRealVar*) works->var("mass");
  vmass->setRange("analysis",8,11.5);
  if(train_state ==3) vmass->setRange("signal",10,10.6);
  if(train_state ==2) vmass->setRange("signal",9.7,10.3);

  gStyle->SetOptTitle(0);
  
  RooPlot* plot1 = vmass->frame(Nmassbins);
  RooPlot* plot2 = vmass->frame();
  plot2->SetAxisRange(10,10.6);
  works->data("reducedDS")->plotOn(plot1, Name("massPlot"), MarkerSize(0.5), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Name("modelPlot"), LineWidth(1));

  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Components(RooArgSet(*works->pdf(Form("%s1S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Components(RooArgSet(*works->pdf(Form("%s2S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot1, Range("analysis"), RooFit::NormRange("analysis"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(1), LineStyle(1), LineColor(kGreen), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////

  works->data("reducedDS")->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Name("massPlot"), MarkerSize(0.5), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"),  RooFit::NormRange("signal"),Name("modelPlot"), LineWidth(1));
  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(Form("%s3S",name_sig_pdf.c_str()))) ), LineWidth(2),LineStyle(1), LineColor(kRed) , MoveToBack());
  works->pdf(name_model.c_str())->plotOn(plot2, Range("signal"), RooFit::NormRange("signal"), Components(RooArgSet(*works->pdf(name_pdf_bkg.c_str())) ), LineWidth(1), LineStyle(1), LineColor(kGreen), MoveToBack() );

/////////////////////////////////////////////////////////////////////////////

  TCanvas* c1 = new TCanvas("c1", "", 1100, 800);
  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.7, 1.0);
  TPad* pad_mass_3S = new TPad("pad_mass_3S", "pad_mass_3S", 0.60, 0.43, 0.90, 0.86);
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
  FormLatex(lt0, 12, 0.038);
  lt0->DrawLatex(0.20,0.80, Form("BDT #in [%.2f, %.2f]",cutBDTlow, cutBDThigh));
  lt0->DrawLatex(0.20,0.75, Form("p_{T}^{#mu} #geq %s GeV/c",MupT.Data()));
  lt0->DrawLatex(0.20,0.70, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int) ptMin, (int) ptMax));
  lt0->DrawLatex(0.20,0.65, Form("Centrality %d-%d %%",(int) cBinLow/2, (int) cBinHigh/2));
  lt0->DrawLatex(0.20,0.60, Form("Trigger : %s", Trig.c_str()));
  
  CMS_lumi_square( pad_mass, 2, 11);

  if (draw_mag && train_state ==3){
    pad_mass_3S->SetMargin(0.25, 0.01, 0.14, 0.01);
    pad_mass_3S->Draw();
    pad_mass_3S->cd();
    plot2->GetXaxis()->SetLabelSize(0.06);
    plot2->GetXaxis()->SetTitleSize(0.06);
    plot2->GetXaxis()->SetTitle("mass (GeV/c^{2}) ");
    plot2->GetXaxis()->SetTitleOffset(1.1);
    plot2->GetYaxis()->SetLabelSize(0.08);
    plot2->GetYaxis()->SetTitleSize(0.06);
    plot2->GetYaxis()->SetTitleOffset(1.65);
    plot2->GetYaxis()->SetRangeUser(0, (plot1->GetMaximum()/2.0));
    plot2->Draw();
  }


  pad_pull->cd();
  pad_pull->SetGrid(0,1);
  pad_pull->SetTopMargin(0.00);
  pad_pull->SetBottomMargin(0.30);
  TLine* line_pull = new TLine(8.,0., 11.5, 0.);
  line_pull->SetLineColorAlpha(kRed, 0.5);
  RooHist* hpull = plot1->pullHist("massPlot", "modelPlot");
  RooPlot* pullPlot = works->var("mass")->frame(Title("Pull Distribution"));
  pullPlot->addPlotable(hpull, "P");
  pullPlot->GetYaxis()->SetLabelSize(0.13);
  pullPlot->GetXaxis()->SetLabelSize(0.10);
  pullPlot->GetXaxis()->SetTitleSize(0.10);
  pullPlot->Draw();
  line_pull->Draw("same");

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

  if(signif_ratio != -1){

  std::cout << "[INFO] Drawing significance HISTOgram" << std::endl;
  signif_hist->SetStats(kFALSE);
  signif_hist->SetFillColor(kRed);
  signif_hist->Draw();

//  signif_hist->GetXaxis()->SetRange(num_bin_signif, num_bin_signif);
  }
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
  c1->SaveAs(Form("%s/FitPlot_train%dS_%ld_%s_%s-%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f%s.pdf",massDIR.Data(), train_state, ts,fitdir.c_str(), sig_func.c_str(), bkg_func.c_str(), (int) (ptMin*10), (int) (ptMax*10), ylim10, ylim10, Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(),(int) swflag,(int) isBDT, cutBDTlow, cutBDThigh, cutQVP, aux.c_str()));
  c1->Close();

};
void DrawHist__(){
  DrawHist({"CB3","CC4","FF"}, 0, 30, -2.4, 2.4, "3p5", "S13", false, 0 ,180, 0.00, true, 1623391157, -1, 1, 70);
}
