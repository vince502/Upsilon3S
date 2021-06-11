#include <TROOT.h>
#include "fitter.h"

using namespace std;
using namespace RooFit;

struct Y1Sfitvar{
  Double_t alp=0., frac=0., x1s=0., sigma=0., n=0.;
};

void MassYieldSingleStateMCFit( struct Y1Sfitvar *Y1S ,long ts, const string fname = "", const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString MupT = "4", const string Trig = "",int cBinLow=0, int cBinHigh = 180, int state = 1, bool fixvar = false, bool swflag = false, double cutQVP= 0.01, double bdtlow = -1., double bdthigh =1. ){
  Double_t etaMax= 2.4;
  Double_t etaMin = -2.4;

  if( fname.find("Switch1") != std::string::npos) { swflag = true;}
  
  TString mainDIR = workdir;
  TString massDIR  = mainDIR + Form("/MassDist/BDT/%ld/MC_GE3/%s/%s/%dS/%1.1f/cent%d-%d/pT%2.1f-%2.1f", ts, Trig.c_str(),MupT.Data(), state, rapMax, cBinLow, cBinHigh, ptMin, ptMax);
  TString massDIRp = mainDIR + Form("/MassDist/BDT/%ld/MC_GE3/%s/%s/%dS/%1.1f/cent%d-%d/pT%2.1f-%2.1f/png", ts, Trig.c_str(), MupT.Data(), state, rapMax, cBinLow, cBinHigh, ptMin, ptMax);
  void * dirpM = gSystem->OpenDirectory(massDIR.Data());
  if(dirpM) gSystem->FreeDirectory(dirpM);
  else gSystem->mkdir(massDIR.Data(), kTRUE);
  void * dirpMp = gSystem->OpenDirectory(massDIRp.Data());
  if(dirpMp) gSystem->FreeDirectory(dirpMp);
  else gSystem->mkdir(massDIRp.Data(), kTRUE);
  TString yieldDIR = mainDIR + "/Yield";
  void * dirpY = gSystem->OpenDirectory(yieldDIR.Data());
  if(dirpY) gSystem->FreeDirectory(dirpY);
  else gSystem->mkdir(yieldDIR.Data(), kTRUE);

  SetStyle();

   Double_t RangeLow, RangeHigh;
  if( state == 1){
    RangeLow = 8.8;
    RangeHigh = 10.1;
  }
  if( state == 3){
    RangeLow = 9.6;
    RangeHigh = 11.0;
  }
  Int_t Nmassbins = (RangeHigh - RangeLow)*30;
  if(Trig == "Ups") Nmassbins = (RangeHigh -RangeLow)*30; 
  TFile* fout;
  fout = new TFile(Form("Yield/Yield_%dS_pt_%d-%d_rap_%d-%d_noWeight_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_%d_GE2.root",(int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), MupT.Data(), Trig.c_str(), bdtlow, bdthigh, cutQVP,(int) fixvar), "RECREATE");

  Double_t MupTCut = single_LepPtCut(MupT);

  TFile* fin;
  fin = new TFile(Form("./BDT/roodatasets/%s", fname.c_str()),"READ");
  RooDataSet* dataset;
  dataset = (RooDataSet*) fin->Get("dataset");

  RooWorkspace* works1 = new RooWorkspace(Form("workspace"));
  works1->import(*dataset);

  RooArgSet* argRD  = new RooArgSet(*(works1->var("mass")), *(works1->var("pt")), *(works1->var("y")), *(works1->var("cBin")), *(works1->var("pt1")), *(works1->var("pt2")), *(works1->var("eta1")), *(works1->var("eta2")), *(works1->var("QQVtxProb")));
  argRD->add(*(works1->var("BDT")));
  RooDataSet* initialDS = (RooDataSet*) dataset->reduce(*argRD);
  initialDS->SetName("initialDS");
  
  RooDataSet* reducedDS = (RooDataSet*) initialDS->reduce(RooArgSet(*(works1->var("mass"))), Form("( pt >=%f && pt <=%f) && (y >= %f && y <=%f) && (cBin>=%d && cBin<=%d) &&(pt1 >= %f) && (pt2 >= %f) && (eta1 >= %f && eta1 <= %f) && ( eta2 >= %f && eta2 <= %f) && (QQVtxProb > %f) && (BDT > %f && BDT < %f)", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, MupTCut, MupTCut, etaMin, etaMax, etaMin, etaMax, cutQVP, bdtlow, bdthigh));
  reducedDS->SetName("reducedDS");
  works1->import(*reducedDS);
  works1->var("mass")->setRange(RangeLow, RangeHigh);
  works1->var("mass")->Print();

  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 600, 600);
  TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
  c1->cd();
  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.98, 1.0);
  pad_mass->Draw();
  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.05, 0.98, 0.25);
  pad_pull->SetBottomMargin(0);
  pad_pull->Draw();
  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.65, 0.35, 0.94, 0.92);
  pad_leg->SetBottomMargin(0);
  pad_leg->SetTopMargin(0);
  pad_leg->Draw();

  TH1D* hYield = new TH1D("hYield", "", 3, 0, 3);

  pad_mass->cd();
  RooPlot* massPlot = works1->var("mass")->frame(Nmassbins);
  works1->data("reducedDS")->plotOn(massPlot, Name("massPlot"));

  RooRealVar mean1S("mean1S", "mean of Upsilon 1S", U1S_mass, U1S_mass-0.01, U1S_mass+0.01);
  RooRealVar mean3S("mean3S", "mean of Upsilon 3S", U3S_mass, U3S_mass-0.02, U3S_mass+0.02);
//  RooRealVar mratio2("mratio2", "mratio2", U2S_mass/U1S_mass);
  RooRealVar mratio3("mratio3", "mratio3", U3S_mass/U1S_mass);
//  RooFormulaVar mean2S("mean2S", "mean1S*mratio2", RooArgSet(mean1S, mratio2));
//  RooFormulaVar mean3S("mean3S", "mean1S*mratio3", RooArgSet(mean1S, mratio3));
  RooRealVar sigma1S_1("sigma1S_1", "sigma1 of 1S", 0.16, 0.01, 0.35);
  RooRealVar* sigma3S_1;
  if(fixvar == false) sigma3S_1  = new RooRealVar("sigma3S_1", "sigma3 of 1S", 0.14, 0.10, 0.25);
  if(fixvar == true ) sigma3S_1  = new RooRealVar("sigma3S_1", "sigma3 of 1S", (Double_t) (Y1S->sigma*(mratio3.getVal())));
//  RooFormulaVar sigma2S_1("sigma2S_1", "@0*@1", RooArgList(sigma1S_1, mratio2));
//  RooFormulaVar sigma3S_1("sigma3S_1", "@0*@1", RooArgList(sigma1S_1, mratio3));

//std::cout << "///////////////////////////////////////////////////////// test code ////////////////////////////////////////////////////////////" << std::endl;
  RooRealVar* x1S;

  Double_t _tmp_x1S = Y1S->x1s;
  if( state == 3 && fixvar == true  ) x1S = new RooRealVar("x1S", "sigma ratio", _tmp_x1S);
  else x1S = new RooRealVar("x1S", "sigma ratio", 0.45, 0, 1);
  
  RooRealVar* x3S = new RooRealVar("x3S", "sigma ratio", 0.54, 0.10, 2.00);
  RooRealVar* x3S_2 = new RooRealVar("x3S_2", "sigma ratio 2", 1.04, 0.10, 3.00);
  works1->import(*x1S);
  works1->import(*x3S);

//std::cout << "///////////////////////////////////////////////////////// test code ////////////////////////////////////////////////////////////" << std::endl;
  RooFormulaVar sigma1S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_1, *x1S));
  RooFormulaVar* sigma3S_2, *sigma3S_3;
  if (fixvar == false ) {
    sigma3S_2 = new RooFormulaVar("sigma3S_2", "@0*@1", RooArgList(*sigma3S_1, *x3S));
    sigma3S_3 = new RooFormulaVar("sigma3S_3", "@0*@1", RooArgList(*sigma3S_1, *x3S_2));
  }
  if (fixvar == true ) sigma3S_2 = new RooFormulaVar("sigma3S_2", "@0*@1", RooArgList(*sigma3S_1, *x1S));
//  RooFormulaVar sigma2S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_2, mratio2));
//  RooFormulaVar sigma3S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_2, mratio3));

  RooRealVar *alpha, *n, *frac, *frac2, *k_1, *k_2, *k_3;
  if ( state == 1 || fixvar == false ){
     alpha = new RooRealVar("alpha", "alpha of Crystal ball", 1.6, 0.5, 2.0);
     n = new RooRealVar("n", "n of Crystal ball", 2, 1.4, 4.0);
     frac = new RooRealVar("frac", "GE fraction", 0.3, 0.10, 0.60);
     frac2 = new RooRealVar("frac2", "GE fraction 2", 0.3, 0.10, 0.60);
     k_1 = new RooRealVar("k_1", "k1 of GausExp", 0.8, 0.1, 6); 
     k_2 = new RooRealVar("k_2", "k2 of GausExp", 1.8, 0.11, 6); 
     k_3 = new RooRealVar("k_3", "k3 of GausExp", 0.8, 0.11, 3); 
   }
   if ( fixvar == true && state == 3 ){
     alpha = new RooRealVar("alpha", "alpha of Crystal ball", Y1S->alp);
     n = new RooRealVar("n", "n of Crystal ball", Y1S->n);
     frac = new RooRealVar("frac", "CB fraction", Y1S->frac);
   }
dbg();
  fit_model_ups::DoubleGausExp* DGE = new fit_model_ups::DoubleGausExp(3, (works1->var("mass")), &mean3S, k_1, k_2, k_3, sigma3S_1, sigma3S_2, sigma3S_3, frac, frac2);
dbg();
  RooBreitWigner* BW3S_1 = new RooBreitWigner("BW3S_1", "3S Breit Wigner function 1", *(works1->var("mass")), mean3S, *sigma3S_3);
  RooCBShape* CB1S_1 = new RooCBShape("CB1S_1", "1S Crystal ball function1", *(works1->var("mass")), mean1S, sigma1S_1, *alpha, *n);
  RooCBShape* CB3S_1 = new RooCBShape("CB3S_1", "3S Crystal ball function1", *(works1->var("mass")), mean3S, *sigma3S_1, *alpha, *n);
//  RooCBShape* CB2S_1 = new RooCBShape("CB2S_1", "2S Crystal ball function1", *(works1->var("mass")), mean2S, sigma2S_1, alpha, n);
//  RooCBShape* CB3S_1 = new RooCBShape("CB3S_1", "3S Crystal ball function1", *(works1->var("mass")), mean3S, sigma3S_1, alpha, n);
  RooCBShape* CB1S_2 = new RooCBShape("CB1S_2", "1S Crystal ball function2", *(works1->var("mass")), mean1S, sigma1S_2, *alpha, *n);
  RooCBShape* CB3S_2 = new RooCBShape("CB3S_2", "3S Crystal ball function2", *(works1->var("mass")), mean3S, *sigma3S_2, *alpha, *n);
//  RooCBShape* CB2S_2 = new RooCBShape("CB2S_2", "2S Crystal ball function2", *(works1->var("mass")), mean2S, sigma2S_2, alpha, n);
//  RooCBShape* CB3S_2 = new RooCBShape("CB3S_2", "3S Crystal ball function2", *(works1->var("mass")), mean3S, sigma3S_2, alpha, n);
//  RooGaussian* G1S = new RooGaussian("G1S", "1S Gaussian", *(works1->var("mass")), mean1S, sigma1S_2);
//  RooGaussian* G2S = new RooGaussian("G2S", "2S Gaussian", *(works1->var("mass")), mean2S, sigma2S_2);
//  RooGaussian* G3S = new RooGaussian("G3S", "3S Gaussian", *(works1->var("mass")), mean3S, sigma3S_2);
  RooAddPdf* GEBW3S = new RooAddPdf("GEBW3S", "Sum of 3S GE BW", RooArgList(*DGE->GE3S_1, *DGE->GE3S_2, *BW3S_1), RooArgList(*frac, *frac2));
  RooAddPdf* twoCB1S = new RooAddPdf("twoCB1S", "Sum of 1S Crystal ball", RooArgList(*CB1S_1, *CB1S_2), RooArgList(*frac));
  RooAddPdf* twoCB3S = new RooAddPdf("twoCB3S", "Sum of 3S Crystal ball", RooArgList(*CB3S_1, *CB3S_2), RooArgList(*frac));
//  RooAddPdf* twoCB2S = new RooAddPdf("twoCB2S", "Sum of 2S Crystal ball", RooArgList(*CB2S_1, *CB2S_2), RooArgList(*frac));
//  RooAddPdf* twoCB3S = new RooAddPdf("twoCB3S", "Sum of 3S Crystal ball", RooArgList(*CB3S_1, *CB3S_2), RooArgList(*frac));
//  RooAddPdf* CBG1S = new RooAddPdf("CBG1S", "Sum of 1S Crystal ball Gauss", RooArgList(*CB1S_1, *G1S), RooArgList(*frac));
//  RooAddPdf* CBG2S = new RooAddPdf("CBG2S", "Sum of 2S Crystal ball Gauss", RooArgList(*CB2S_1, *G2S), RooArgList(*frac));
//  RooAddPdf* CBG3S = new RooAddPdf("CBG3S", "Sum of 3S Crystal ball Gauss", RooArgList(*CB3S_1, *G3S), RooArgList(*frac));
//  RooRealVar Erfmean("Erfmean", "Mean of Errfunction", 5, 0, 10.0);//for 0~40, 4~7 GeV
//  RooRealVar Erfsigma("Erfsigma", "Sigma of Errfunction", 1, 0, 100);//for 0~40, 4~7 GeV
//  RooRealVar Erfp0("Erfp0", "1st parameter of Errfunction", 1, 0, 100);
  RooRealVar ch4_k1("ch4_k1", "ch4_k1", -0.02, -3.0, 3.0);
  RooRealVar ch4_k2("ch4_k2", "ch4_k2", -0.05, -3.0, 3.00);
//  RooGenericPdf* bkgErf = new RooGenericPdf("bkgErf", "Error background", "TMath::Exp(-@0/@1)*(TMath::Erf((@0-@2)/(TMath::Sqrt(2)*@3))+1)*0.5", RooArgList(*(works1->var("mass")), Erfp0, Erfmean, Erfsigma));
  RooChebychev *bkg = new RooChebychev("cPol1Bkg", "Background", *(works1->var("mass")), RooArgSet(ch4_k1, ch4_k2));


  RooGenericPdf* Signal1S;
//  RooGenericPdf* Signal2S;
  RooGenericPdf* Signal3S;

//  Signal1S = (RooGenericPdf*) twoCB1S;
//  Signal2S = (RooGenericPdf*) twoCB2S;
//  Signal3S = (RooGenericPdf*) twoCB3S;
  Signal3S = (RooGenericPdf*) GEBW3S;
//  std::cout << DGE->GE3S_1->GetName() << std::endl;
//  std::cout << DGE->threeGE3S->GetName() << std::endl;
//  std::cout << Signal3S->GetName() << std::endl;
dbg();
  RooRealVar* nSig1S = new RooRealVar("nSig1S", "# of 1S signal",70000, 0, 1000000);
//  RooRealVar* nSig2S = new RooRealVar("nSig2S", "# of 2S signal", 100, -1000, 300000);
  RooRealVar* nSig3S = new RooRealVar("nSig3S", "# of 3S signal", 3000, 0, 1000000);
//  RooRealVar* nBkg = new RooRealVar("nBkg", "# of background signal", 300, -1000, 10000000); //Erf* mean
  RooRealVar* nBkg = new RooRealVar("nBkg", "# of background signal", -100, 100000);
  if (Trig == "Ups"){ nSig3S->setMax(10000000); nSig3S->setVal(100000); nSig1S->setMax(10000000); nSig1S->setVal(1000000); nBkg->setMax(10000000);}
  RooAddPdf* model;
  if( state == 1) model = new RooAddPdf("model", "1S+Bkg", RooArgList(*Signal1S,*bkg), RooArgList(*nSig1S, *nBkg));
  //if( state == 3) model = new RooAddPdf("model", "3S+Bkg", RooArgList(*Signal3S,*bkg), RooArgList(*nSig3S, *nBkg));
dbg(100);
  if( state == 3) model = new RooAddPdf("model", "3S", RooArgList(*Signal3S), RooArgList(*nSig3S));

dbg(100);
  works1->import(*model);
dbg();
/////////////////////////////////////////////////////////////FITTING START//////////////////////////////////////////////////////////////////////////////////////////
  RooFitResult* Result = works1->pdf("model")->fitTo(*reducedDS, Save(), Hesse(kTRUE), Range(RangeLow, RangeHigh), Minos(0), SumW2Error(kTRUE), Extended(kTRUE));
  works1->pdf("model")->plotOn(massPlot, Name("modelPlot"));
//  works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal2S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  if( state ==1 ) {works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal1S)), LineColor(kRed), LineStyle(kDashed), MoveToBack()); works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*CB1S_1)), LineColor(kGreen), LineStyle(kSolid), MoveToBack()); works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*CB1S_2)), LineColor(kMagenta), LineStyle(kDashDotted), MoveToBack());}
//  if( state ==3 ) {works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal3S)), LineColor(kRed), LineStyle(kDashed), MoveToBack()); works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*CB3S_1)), LineColor(kGreen), LineStyle(kSolid), MoveToBack()); works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*CB3S_2)), LineColor(kMagenta), LineStyle(kDashDotted), MoveToBack());}
  if( state ==3 ) {works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*Signal3S)), LineColor(kRed), LineStyle(kDashed), MoveToBack()); works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*DGE->GE3S_1)), LineColor(kGreen), LineStyle(kSolid), MoveToBack()); works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*DGE->GE3S_2)), LineColor(kMagenta), LineStyle(kDashDotted), MoveToBack());works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*BW3S_1)), LineColor(kOrange), LineStyle(kDotted), MoveToBack());}
  massPlot->SetTitle("");
  massPlot->SetXTitle("M (GeV/c^2)");
  massPlot->SetYTitle("Counts");
  massPlot->Draw();
  Result->Print("v");
  WriteMessage("Fitting is dOnE ! ! !");
/////////////////////////////////////////////////////////////FITTING END////////////////////////////////////////////////////////////////////////////////////////////
  pad_pull->cd();
  pad_pull->SetGrid(0,1);
  TLine* line_pull = new TLine(RangeLow,0.,RangeHigh, 0.);
  line_pull->SetLineColorAlpha(kRed, 0.5);
  line_pull->SetLineWidth(3);
  RooHist* hpull = massPlot->pullHist("massPlot", "modelPlot");
  RooPlot* pullPlot = works1->var("mass")->frame(Title("Pull Distribution"));
  pullPlot->addPlotable(hpull, "P");
  pullPlot->GetYaxis()->SetLabelSize(0.13);
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
  Double_t NLL = Result->minNll();
  std::cout << "NLL : " << NLL << std::endl;
  Int_t ndf = Npullbin - Nfitpar;

  TLatex* NormChi2tex = new TLatex();
  FormLatex(NormChi2tex, 42, 0.13);
  NormChi2tex->DrawLatex(0.15, 0.95, Form("#chi^{2}/ndf: %3.f/%d", chi2, ndf));
  WriteMessage("Pull distribution is dOnE !!!");

  pad_leg->cd();
  RooPlot* legPlot = works1->var("mass")->frame(Name("Fit Results"), Title("Fit Results"));
  RooArgList parList = Result->floatParsFinal();
  parList.Print("v");
  works1->pdf("model")->paramOn(legPlot, Layout(0, 0.93, 0.97), Parameters(parList));
  legPlot->getAttText()->SetTextAlign(11);
  legPlot->getAttText()->SetTextSize(0.05);

  TPaveText* Ptext = (TPaveText*) legPlot->findObject(Form("%s_paramBox", works1->pdf("model")->GetName()));
  Ptext->SetY1(0.01);
  Ptext->SetY2(0.95);
  Ptext->Draw();
  WriteMessage("Writting result is dOnE !!!");

  Double_t YieldNS, YieldNSErr;
  if( state ==1 ){
    YieldNS = works1->var("nSig1S")->getVal();
    YieldNSErr =  works1->var("nSig1S")->getError();
  }
  if( state ==3 ){
    YieldNS = works1->var("nSig3S")->getVal();
    YieldNSErr =  works1->var("nSig3S")->getError();
  }
//  Double_t Yield2S = works1->var("nSig2S")->getVal();
//  Double_t Yield2SErr = works1->var("nSig2S")->getError();
//  Double_t Yield3S = works1->var("nSig3S")->getVal();
//  Double_t Yield3SErr = works1->var("nSig3S")->getError();
//  Double_t YieldBkg = works1->var("nBkg")->getVal();

  hYield->SetBinContent(1, YieldNS);
  hYield->SetBinError(1, YieldNSErr);
//  hYield->SetBinContent(2, Yield2S);
//  hYield->SetBinError(2, Yield2SErr);
//  hYield->SetBinContent(3, Yield3S);
//  hYield->SetBinError(3, Yield3SErr);


  Double_t meanout, sigma1out, sigma2out;
  if( state == 1 ){
    meanout = works1->var("mean1S")->getVal();
    sigma1out = works1->var("sigma1S_1")->getVal();
    sigma2out = (works1->var("x1S")->getVal())*sigma1out;
    if( fixvar == true){ Y1S->sigma = sigma1out; Y1S->x1s = works1->var("x1S")->getVal(); Y1S->n = works1->var("n")->getVal(); Y1S->alp = works1->var("alpha")->getVal(); Y1S->frac =works1->var("frac")->getVal(); }
  }
  if( state == 3 ){
    meanout = works1->var("mean3S")->getVal();
    sigma1out = works1->var("sigma3S_1")->getVal();
    if( fixvar == false ) sigma2out = (works1->var("x3S")->getVal())*sigma1out;
    if( fixvar == true ) sigma2out = (works1->var("x1S")->getVal())*sigma1out;
  }
  Double_t fracout = works1->var("frac")->getVal();
  Double_t sigmaout = TMath::Sqrt(fracout*sigma1out*sigma1out+(1-fracout)*sigma2out*sigma2out);

  TF1* SgnfcNS;
//  TF1* Sgnfc2S;
//  TF1* Sgnfc3S;

  if( state ==1 )SgnfcNS = works1->pdf("twoCB1S")->asTF(*(works1->var("mass")));
//  if( state ==3 )SgnfcNS = works1->pdf("twoGE3S")->asTF(*(works1->var("mass")));
  if( state ==3 )SgnfcNS = works1->pdf("GEBW3S")->asTF(*(works1->var("mass")));
//  Sgnfc2S = works1->pdf("twoCB2S")->asTF(*(works1->var("mass")));
//  Sgnfc3S = works1->pdf("twoCB3S")->asTF(*(works1->var("mass")));

  TF1* Bkgfc;
//  Bkgfc = works1->pdf("cPol1Bkg")->asTF(*(works1->var("mass")));

  Double_t TIntgrNS = SgnfcNS->Integral(RangeLow, RangeHigh);
//  Double_t TIntgr2S = Sgnfc2S->Integral(RangeLow, RangeHigh);
//  Double_t TIntgr3S = Sgnfc3S->Integral(RangeLow, RangeHigh);
//  Double_t TIntgrBkg = Bkgfc->Integral(RangeLow, RangeHigh);
  Double_t IntgrSig = SgnfcNS->Integral(meanout-2*sigmaout, meanout+2*sigmaout);
//  Double_t IntgrBkg = Bkgfc->Integral(meanout-2*sigmaout, meanout+2*sigmaout);
//  Double_t Significance =(YieldNS*IntgrSig/TIntgrNS/TMath::Sqrt(((YieldNS*IntgrSig/TIntgrNS)+(YieldBkg*IntgrBkg/TIntgrBkg))));

/*  TH1D* hfrac = new TH1D("hfrac", "", 6, 0, 6);
  if( state == 1){
    hfrac->SetBinContent(1, SgnfcNS->Eval(U1S_mass));
    hfrac->SetBinContent(2, Bkgfc->Eval(U1S_mass));
    hfrac->SetBinContent(3, SgnfcNS->Integral(9.3, 9.6));
    hfrac->SetBinContent(4, Bkgfc->Integral(9.3, 9.6));
    hfrac->SetBinContent(5, SgnfcNS->Integral(9.1, 9.8));
    hfrac->SetBinContent(6, Bkgfc->Integral(9.1, 9.8));
  }
  if( state == 3){
    hfrac->SetBinContent(1, SgnfcNS->Eval(U3S_mass));
    hfrac->SetBinContent(2, Bkgfc->Eval(U3S_mass));
    hfrac->SetBinContent(3, SgnfcNS->Integral(10.3, 10.4));
    hfrac->SetBinContent(4, Bkgfc->Integral(10.3, 10.4));
    hfrac->SetBinContent(5, SgnfcNS->Integral(10.1, 10.6));
    hfrac->SetBinContent(6, Bkgfc->Integral(10.1, 10.6));
  }
  TH1D* hfracdist;
  if( state == 1) hfracdist = new TH1D("hfracdist","",20, 9, 10);
  if( state == 3) hfracdist = new TH1D("hfracdist","",20, 9.9, 10.9);
  for(Int_t i =0; i <20; i++){
    hfracdist->SetBinContent(i+1, SgnfcNS->Eval(9+0.05*i)/(SgnfcNS->Eval(9+0.05*i)+Bkgfc->Eval(9+0.05*i)));
  }
  */
//  FILE* ftxt = 0;
//  if(ftxt != NULL){
//    fprintf(ftxt, "mean sigma1 sigma2 fraction totsigma totsig totbkg sig bkg nsig nbkg significance \n");
//    fprintf(ftxt, "%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f	%.3f \n", meanout, sigma1out, sigma2out, fracout, sigmaout, TIntgrNS, TIntgrBkg, IntgrSig, IntgrBkg, YieldNS, YieldBkg, Significance);
//    fprintf(ftxt, "mean  U1sigma1  fraction  alpha  n  Erfmean  Erfsigma  Erfp0 \n");
//    fprintf(ftxt, "%.3f   %.3f   %.3f   %.3f \n", YieldNS, YieldBkg, TIntgrNS, TIntgrBkg);
//  }
  
  //fout = new TFile(Form("Yield/Yield_%dS_pt_%d-%d_rap_%d-%d_noWeight_MupT%s_%s_BDT_%d-%d_vp_%d_MC_%d.root",(int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), MupT.Data(), Trig.c_str(), bdtlow, bdthigh, cutQVP,(int) fixvar), "RECREATE");

  c1->SetLogy();
  c1->Update();
  c1->SaveAs(Form("%s/MassDistribution_%dS_pt_%d-%d_rap_%d-%d_%dbin_noWeight_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_fix%d.pdf",massDIR.Data(), state,(int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Nmassbins, MupT.Data(), Trig.c_str(), bdtlow, bdthigh, cutQVP,(int) fixvar));
  c1->SaveAs(Form("%s/png/MassDistribution_%dS_pt_%d-%d_rap_%d-%d_%dbin_noWeight_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_fix%d.png",massDIR.Data(), state,(int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Nmassbins, MupT.Data(), Trig.c_str(), bdtlow, bdthigh, cutQVP, (int) fixvar));
  TH1D* hmass = new TH1D("hmass", ";M (GeV/c^2);Counts", Nmassbins, RangeLow, RangeHigh);
  reducedDS->fillHistogram(hmass, (*works1->var("mass")));
  FormTH1Marker(hmass, 0, 0, 1.4);
  c2->cd();
  hmass->Draw("pe");
  lumiText(0.56, 0.92);
  TLatex* lt1 = new TLatex();
  FormLatex(lt1, 12, 0.04);
  lt1->DrawLatex(0.6, 0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c", MupTCut));
  lt1->DrawLatex(0.6, 0.75, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int) ptMin, (int) ptMax));

//  c2->SaveAs(Form("%s/WithoutFit_%dS_pt_%d-%d_rap_%d-%d_%dbin_noWeight_MupT%s_%s_BDT_%.4f-%.4f_vp_%.4f_MC_fix%d.pdf",massDIR.Data(), state, (int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10),  Nmassbins, MupT.Data(), Trig.c_str(),  bdtlow, bdthigh, cutQVP, (int) fixvar));

  fout->cd();
  Result->Write();
  massPlot->Write();
  hYield->Write();
  hmass->Write();
  SgnfcNS->Write();
 // hfrac->Write();
 // hfracdist->Write();
 
};

void MassYieldFit_BDT_MC_GE(long _ts, const string _fname1s = "", const string _fname3s = "", const Double_t _ptMin = 0, const Double_t _ptMax = 30, const Double_t _rapMin = -2.4, const Double_t _rapMax = 2.4, const TString _MupT = "4", const string _Trig = "", int _cBinLow = 0, int _cBinHigh = 180, int _state = 1, bool _fixvar =false, bool _swflag = false, double _cutQVP = 0.01, double _bdtlow =-1., double _bdthigh = 1.){
  struct Y1Sfitvar Y1Svar;
//  if( _fixvar == true){
//    MassYieldSingleStateMCFit( &Y1Svar, _fname1s, _ptMin, _ptMax, _rapMin, _rapMax, _MupT , _Trig, _cBinHigh, 1, _fixvar);
//    std::cout << "x1sftjj,,, alpha : " << Y1Svar.alp << ", n : " << Y1Svar.n << ", x1S : " << Y1Svar.x1s << ", frac : " << Y1Svar.frac << ", sigma 1S : " << Y1Svar.sigma << std::endl;
//    MassYieldSingleStateMCFit( &Y1Svar, _fname3s, _ptMin, _ptMax, _rapMin, _rapMax, _MupT , _Trig, _cBinHigh, 3, _fixvar);
//  }
//  else if( _fixvar ==false){
    if( _state == 3){MassYieldSingleStateMCFit( &Y1Svar,_ts, _fname3s, _ptMin, _ptMax, _rapMin, _rapMax, _MupT , _Trig, _cBinLow, _cBinHigh, 3, _fixvar, _swflag, _cutQVP, _bdtlow, _bdthigh);}
//  }
}

