#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooMCStudy.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
#include "/home/CMS/Analysis/Upsilon3S_pp2017Ref/Utility/rootFitHeaders.h"
#include "/home/CMS/Analysis/Upsilon3S_pp2017Ref/Utility/commonUtility.h"
#include "/home/CMS/Analysis/Upsilon3S_pp2017Ref/Utility/commonUtility.h"
#include "/home/CMS/Analysis/Upsilon3S_pp2017Ref/Utility/cutsAndBin.h"
#include "/home/CMS/Analysis/Upsilon3S_pp2017Ref/Utility/Style_jaebeom.h"
using namespace RooFit;
 
void mcToystudy_unblind_test(int rndmseed=3, double ptLow=0, double ptHigh=4, int cLow = 0, int cHigh=90, int state=3 )
{
   // C r e a t e   m o d e l   w i t h   p a r a m e t e r   c o n s t r a i n t
   // ---------------------------------------------------------------------------
 
   RooRandom::randomGenerator()->SetSeed(rndmseed);
   RooFit::BatchMode(kTRUE);
   //RooCmdArg::PrintLevel(-1);
   
   string fname = Form("%dS_pt_%.0f_%.0f_cent_%d_%d",state,ptLow,ptHigh,cLow,cHigh);
   
   TFile* rf = new TFile(Form("/home/vince402/shared/Upsilon3S_PostPreApp/Yield_nominal/unblind/fit_data_%s.root",fname.c_str()),"read");
   RooWorkspace *ws = (RooWorkspace*) rf->Get("workspace");
   
   TFile* roodataset = new TFile("/home/vince402/shared/Upsilon3S_PostPreApp/roodatasets/unblind_data.root","read");
   RooDataSet *dataset = (RooDataSet*) roodataset->Get("dataset_Y3Spt0to4");

  
   
   TFile* rfInt = new TFile(Form("/home/vince402/shared/Upsilon3S_PostPreApp/Yield_nominal/unblind/fit_data_%dS_pt_0_30_cent_0_90.root",state),"read");
   RooWorkspace *wsInt = (RooWorkspace*) rfInt->Get("workspace");

   RooRealVar mass = *(ws->var("mass"));
   
   double n1s_init  = ws->var("n")->getVal();
   double alpha1s_init  = ws->var("alpha")->getVal();
   double sigma1s_init  = ws->var("sigma1S_1")->getVal();
   double f1s_init  = ws->var("frac")->getVal();
   double f1s_2_init  = ws->var("frac2")->getVal();
   double x1s_init  = ws->var("x1S")->getVal();
   double x1s_2_init  = ws->var("x1S_2")->getVal();
  
  double m0_shiftlim = 0.03; 


  RooRealVar* nom_alpha = (RooRealVar*) ws->var("alpha");
  RooRealVar* nom_n= (RooRealVar*) ws->var("n");
  RooRealVar* nom_sigma     = (RooRealVar*) ws->var("sigma1S_1");
  RooRealVar* nom_f1    = (RooRealVar*) ws->var("frac");
  RooRealVar* nom_f2    = (RooRealVar*) ws->var("frac2");
  RooRealVar* nom_x1    = (RooRealVar*) ws->var("x1S");
  RooRealVar* nom_x2    = (RooRealVar*) ws->var("x1S_2");
  
  RooAddPdf* cb1s      = (RooAddPdf*) ws->pdf("threeCB1S");
  RooAddPdf* cb2s      = (RooAddPdf*) ws->pdf("threeCB2S");
  RooAddPdf* cb3s      = (RooAddPdf*) ws->pdf("threeCB3S");

  RooGenericPdf* bkg   = (RooGenericPdf*) ws->pdf("bkgErf");

  RooGaussian* alpha_con;
  RooGaussian* n_con    ; 
  RooGaussian* sigma_con; 
  RooGaussian* f1s_con  ; 
  RooGaussian* x1s_con  ; 
  RooGaussian* f1s_2_con; 
  RooGaussian* x1s_2_con; 
  if(cLow==0 && cLow==90){
    n_con = (RooGaussian*) ws->pdf("n_constraint");
    alpha_con= (RooGaussian*) ws->pdf("alpha_constraint");
    sigma_con= (RooGaussian*) ws->pdf("sigmaNS_1_constraint");
    f1s_con= (RooGaussian*) ws->pdf("frac_constraint");
    x1s_con= (RooGaussian*) ws->pdf("xNS_constraint");
    f1s_2_con= (RooGaussian*) ws->pdf("frac2_constraint");
    x1s_2_con= (RooGaussian*) ws->pdf("xNS_2_constraint");
  }
  else{
    n_con     = (RooGaussian*) wsInt->pdf("n_constraint");
    alpha_con = (RooGaussian*) wsInt->pdf("alpha_constraint");
    sigma_con = (RooGaussian*) wsInt->pdf("sigmaNS_1_constraint");
    f1s_con   = (RooGaussian*) wsInt->pdf("frac_constraint");
    x1s_con   = (RooGaussian*) wsInt->pdf("xNS_constraint");
    f1s_2_con = (RooGaussian*) wsInt->pdf("frac2_constraint");
    x1s_2_con = (RooGaussian*) wsInt->pdf("xNS_2_constraint");
  }
  double nSig1s_init = ws->var("nSig1S")->getVal();
  double nSig2s_init = ws->var("nSig2S")->getVal();
  double nSig3s_init = ws->var("nSig3S")->getVal();
  double nbkginput =  ws->var("nBkg")->getVal();
  int nGen = nbkginput + nSig1s_init+ nSig2s_init+ nSig3s_init;
  
  RooRealVar *nSig1s= new RooRealVar("nSig1s"," 1S signals",nSig1s_init, nSig1s_init*0.8, 100000);
  RooRealVar *nSig2s= new RooRealVar("nSig2s"," 2S signals",nSig2s_init, 0, 100000);
  RooRealVar *nSig3s= new RooRealVar("nSig3s"," 3S signals",nSig3s_init, -100, 10000);
  RooRealVar *nBkg = new RooRealVar("nBkg","fraction of component 1 in bkg",nbkginput,nbkginput*0.7,nbkginput*1.3);  
  
  RooRealVar *nSig1sInput= new RooRealVar("nSig1sInput"," 1S signals",nSig1s_init, 0, 100000);
  RooRealVar *nSig2sInput= new RooRealVar("nSig2sInput"," 2S signals",nSig2s_init, 0, 100000);
  RooRealVar *nSig3sInput= new RooRealVar("nSig3sInput"," 3S signals",nSig3s_init, -100, 10000);
  RooRealVar *nBkgInput = new RooRealVar("nBkgInput","fraction of component 1 in bkg",nbkginput,0,nGen);  
  
  
  RooAddPdf* model = new RooAddPdf("model","1S+2S+3S + Bkg",RooArgList(*cb1s, *cb2s, *cb3s, *bkg),RooArgList(*nSig1s,*nSig2s,*nSig3s,*nBkg));
  RooProdPdf* modelgc = new RooProdPdf("modelgc","model with constraint",RooArgSet(*model,RooArgSet(*n_con,*alpha_con,*sigma_con,*f1s_con,*x1s_con,*f1s_2_con,*x1s_2_con)));
  RooAddPdf* modelInput_gen = new RooAddPdf("modelGen","1S+2S+3S + Bkg",RooArgList(*cb1s, *cb2s, *cb3s, *bkg),RooArgList(*nSig1sInput,*nSig2sInput,*nSig3sInput,*nBkgInput));


  RooWorkspace *wso = new RooWorkspace("workspaceO");
  wso->import(*dataset);
  RooDataSet *reducedDS = (RooDataSet*)dataset->reduce(RooArgSet(*(wso->var("mass")), *(wso->var("pt")), *(wso->var("y"))), "BDT>0.2020 && pt<4" );
  wso->import(*modelgc);
   

  int nMassBin = 80;
  RooPlot* myPlot  = ws->var("mass")->frame(nMassBin);
  RooPlot* myPlot2 = (RooPlot*)myPlot->Clone();
  reducedDS->plotOn(myPlot2,Name("dataHist"),MarkerSize(.8));

  RooFit::BatchMode(kTRUE);
  RooFitResult* fitRes2 = wso->pdf("modelgc")->fitTo(*reducedDS,Constrain(RooArgSet(*nom_n,*nom_alpha,*nom_sigma,*nom_f1,*nom_x1,*nom_f2,*nom_x2)), Save(),PrefitDataFraction(0.1), Minimizer("Minuit","minimize"),Range(8,14), NumCPU(80),Extended(kTRUE),RooFit::BatchMode(kTRUE));
  fitRes2->Print("v");
  
  wso->pdf("modelgc")->plotOn(myPlot2,Name("modelInputHist"));
  wso->pdf("modelgc")->plotOn(myPlot2,Name("Sig1S"),Components(RooArgSet(*cb1s)),LineColor(kOrange+7),LineWidth(2),LineStyle(2));
  wso->pdf("modelgc")->plotOn(myPlot2,Components(RooArgSet(*cb2s)),LineColor(kOrange+7),LineWidth(2),LineStyle(2));
  wso->pdf("modelgc")->plotOn(myPlot2,Components(RooArgSet(*cb3s)),LineColor(kOrange+7),LineWidth(2),LineStyle(2));
  wso->pdf("modelgc")->plotOn(myPlot2,Name("bkgPDF"),Components(RooArgSet(*bkg)),LineColor(kBlue),LineStyle(kDashed),LineWidth(2));

  TCanvas* c1 =  new TCanvas("canvas2","My plots",4,45,550,520);
  c1->cd();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.16, 0.98, 1.0);
  pad1->SetTicks(1,1);
  pad1->Draw(); pad1->cd();
  myPlot2->SetFillStyle(4000);
  myPlot2->SetAxisRange(8, 14,"X");
  myPlot2->GetYaxis()->SetTitleOffset(1.4);
  myPlot2->GetYaxis()->CenterTitle();
  myPlot2->GetYaxis()->SetTitleSize(0.048);
  myPlot2->GetXaxis()->SetLabelSize(0);
  myPlot2->GetXaxis()->SetRangeUser(8,14);
  myPlot2->GetXaxis()->SetTitleSize(0);
  myPlot2->Draw();
  
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 0.98, 0.23);
  pad2->SetTopMargin(0); // Upper and lower plot are joined
  pad2->SetBottomMargin(0.63); 
  pad1->SetLeftMargin(0.15);
  pad2->SetLeftMargin(0.15);
  pad2->SetTicks(1,1);
  c1->cd();
  pad2->Draw();
  pad2->cd();
  
  RooHist* hpull = myPlot2->pullHist("dataHist","modelInputHist");
  hpull->SetMarkerSize(0.8);
  RooPlot* pullFrame = ws->var("mass")->frame(Title("Pull Distribution")) ;
  pullFrame->addPlotable(hpull,"P") ;
  pullFrame->SetTitleSize(0);
  pullFrame->GetYaxis()->SetTitleOffset(0.31) ;
  pullFrame->GetYaxis()->SetTitle("Pull") ;
  pullFrame->GetYaxis()->SetTitleSize(0.17) ;
  pullFrame->GetYaxis()->SetLabelSize(0.13) ;
  pullFrame->GetYaxis()->SetRangeUser(-4.5,4.5) ;
//  pullFrame->GetYaxis()->SetLimits(-6,6) ;
  pullFrame->GetYaxis()->CenterTitle();

  pullFrame->GetXaxis()->SetTitle("m_{#mu^{+}#mu^{-}} (GeV/c^{2})");
  pullFrame->GetXaxis()->SetTitleOffset(1.20) ;
  pullFrame->GetXaxis()->SetLabelOffset(0.04) ;
  pullFrame->GetXaxis()->SetLabelSize(0.183) ;
  pullFrame->GetXaxis()->SetTitleSize(0.25) ;
  pullFrame->GetXaxis()->CenterTitle();
  
  pullFrame->GetYaxis()->SetTickSize(0.02);
  pullFrame->GetYaxis()->SetNdivisions(505);
  pullFrame->GetXaxis()->SetTickSize(0.03);
  pullFrame->Draw() ;
  
  double chisq = 0;
  int nFullBinsPull = 0;
  int nBins = nMassBin; 
  double *ypull = hpull->GetY();
  for(int i=0;i<nBins;i++)
  {
    if(ypull[i] == 0) continue;
    chisq += TMath::Power(ypull[i],2);
    nFullBinsPull++;
  }

  int numFitPar = fitRes2->floatParsFinal().getSize();
  int ndf = nFullBinsPull - numFitPar;

  double minNLL = fitRes2->minNll();

  string fDIR = "TEST_Unblind_ToyDir_" + fname;
  void * dirf = gSystem->OpenDirectory(fDIR.c_str());
  if(dirf) gSystem->FreeDirectory(dirf);
  else gSystem->mkdir(fDIR.c_str(), kTRUE);

  TFile *wf = new TFile(Form("%s/Toy_%d.root",fDIR.c_str(),rndmseed),"recreate");
  TH1D* hyield = new TH1D("hyield","",6,0,6);
  hyield->SetBinContent(1, wso->var("nSig1s")->getVal());
  hyield->SetBinContent(2, wso->var("nSig2s")->getVal());
  hyield->SetBinContent(3, wso->var("nSig3s")->getVal());
  hyield->SetBinError(1, wso->var("nSig1s")->getError());
  hyield->SetBinError(2, wso->var("nSig2s")->getError());
  hyield->SetBinError(3, wso->var("nSig3s")->getError());
  hyield->SetBinContent(4,chisq);
  hyield->SetBinContent(5,ndf);
  hyield->SetBinContent(6,(double)chisq/ndf);
  hyield->SetBinContent(7,minNLL);
  wf->cd();
  hyield->Write();
  wso->Write();
  c1->Write();

  c1->SaveAs(Form("%s/Toy_%d.pdf",fDIR.c_str(),rndmseed));


  //RooMCStudy* mcstudy = new RooMCStudy(*modelc, mass, Constrain(RooArgSet(n1s_1,alpha1s_1,sigma1s_1,*f1s,*x1s,*f1s_2,*x1s_2)),Extended(),NumCPU(40), FitOptions(Save(kTRUE)), PrintEvalErrors(0));
  //mcstudy->generateAndFit(10,initSig);

  //   TH1D* h_nsig3s = mcstudy->fitParDataSet().createHistogram("nSig3S",40);
}
