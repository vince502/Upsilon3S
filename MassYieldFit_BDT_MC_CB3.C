#include <TROOT.h>
#include "fitter.h"
#include "fitreslib.h"

using namespace std;
using namespace RooFit;


void MassYieldSingleStateMCFitCB3( struct Y1Sfitvar *Y1S ,long ts, const string fname = "", const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString MupT = "4", const string Trig = "",int cBinLow=0, int cBinHigh = 181, int train_state =3, int state = 1, bool fixvar = false, bool swflag = false, double cutQVP= 0.01, double bdtlow = -1., double bdthigh =1., int bdtptMin = 0, int bdtptMax = 30, string dir_opt = "" ){
  Double_t etaMax= 2.4;
  Double_t etaMin = -2.4;

  if( fname.find("Switch1") != std::string::npos) { swflag = true;}
  
  string alt =  "";
  if( strcmp(dir_opt.c_str(), "") !=0) alt = "/"+dir_opt; 
  TString mainDIR_base = Form("%s/MassDist/%s/%ld%s/Cent%d-%d_Pt%d-%d_y%.1f/%d/MC_BW" , workdir.Data(), "BDT", ts, alt.c_str(), cBinLow, cBinHigh,(int) ptMin, (int) ptMax, rapMax, state  );
  TString massDIR = mainDIR_base;
  TString massDIRp = mainDIR_base + "/png";
  TString massDIRcont = mainDIR_base + "/contour";
  void * dirpM = gSystem->OpenDirectory(massDIR.Data());
  if(dirpM) gSystem->FreeDirectory(dirpM);
  else gSystem->mkdir(massDIR.Data(), kTRUE);
  void * dirpMp = gSystem->OpenDirectory(massDIRp.Data());
  if(dirpMp) gSystem->FreeDirectory(dirpMp);
  else gSystem->mkdir(massDIRp.Data(), kTRUE);
  void * dirpMc = gSystem->OpenDirectory(massDIRcont.Data());
  if(dirpMc) gSystem->FreeDirectory(dirpMc);
  else gSystem->mkdir(massDIRcont.Data(), kTRUE);
  TString yieldDIR = workdir + "/Yield";
  void * dirpY = gSystem->OpenDirectory(yieldDIR.Data());
  if(dirpY) gSystem->FreeDirectory(dirpY);
  else gSystem->mkdir(yieldDIR.Data(), kTRUE);

  SetStyle();

   Double_t RangeLow, RangeHigh;
  if( state == 1){
    RangeLow = 8.8;
    RangeHigh = 10.1;
  }
  if( state == 2){
    RangeLow = 9.3;
    RangeHigh = 10.7;
  }
  if( state == 3){
    RangeLow = 9.6;
    RangeHigh = 11.0;
  }
  Int_t Nmassbins = (RangeHigh - RangeLow)*30;
  if(Trig == "Ups") Nmassbins = (RangeHigh -RangeLow)*30; 


  Double_t MupTCut = single_LepPtCut(MupT);

  TFile* fin;
  fin = new TFile(Form("./BDT/roodatasets/%s", fname.c_str()),"READ");
  RooDataSet* dataset;
  std::string name_dataset = "dataset";
  if(ts >= 1634636609) name_dataset= name_dataset + Form("_Y%dSpt%dto%d", train_state, bdtptMin, bdtptMax) ;
  std::cout << "[INFO] Importing dataset : " << name_dataset.c_str() << std::endl;
  dataset = (RooDataSet*) fin->Get(name_dataset.c_str());

  RooWorkspace* works1 = new RooWorkspace(Form("workspace"));
  works1->import(*dataset);

  RooArgSet* argRD  = new RooArgSet(*(works1->var("mass")), *(works1->var("pt")), *(works1->var("y")), *(works1->var("cBin")), *(works1->var("pt1")), *(works1->var("pt2")), *(works1->var("eta1")), *(works1->var("eta2")), *(works1->var("QQVtxProb")));
  argRD->add(*(works1->var("BDT")));
  RooDataSet* initialDS = (RooDataSet*) dataset->reduce(*argRD);
  initialDS->SetName("initialDS");
  
  RooDataSet* reducedDS = (RooDataSet*) initialDS->reduce(RooArgSet(*(works1->var("mass"))), Form("( pt >=%f && pt <=%f) && (y >= %f && y <=%f) && (cBin>=%d && cBin<%d) &&(pt1 >= %f) && (pt2 >= %f) && (eta1 >= %f && eta1 <= %f) && ( eta2 >= %f && eta2 <= %f) && (QQVtxProb > %f) && (BDT > %f && BDT < %f)", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, MupTCut, MupTCut, etaMin, etaMax, etaMin, etaMax, cutQVP, bdtlow, bdthigh));
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

  RooRealVar meanNS;
  if(state ==1) {
    meanNS = RooRealVar("meanNS", "mean of Upsilon NS", U1S_mass, U1S_mass-0.05, U1S_mass+0.05);
  }
  if(state ==2) {
    meanNS = RooRealVar("meanNS", "mean of Upsilon NS", U2S_mass, U2S_mass-0.03, U2S_mass+0.03);
  }
  if(state ==3) {
    meanNS = RooRealVar("meanNS", "mean of Upsilon NS", U3S_mass, U3S_mass-0.02, U3S_mass+0.02);
  }

  RooRealVar* sigmaNS_1;
  sigmaNS_1  = new RooRealVar("sigmaNS_1", "sigma of NS", 0.22, 0.02, 0.45);

  RooRealVar* xNS;

  xNS = new RooRealVar("xNS", "sigma ratio", 0.56, 0.01, 0.95);
  RooRealVar* xNS_2 = new RooRealVar("xNS_2", "sigma ratio", 0.318, 0.01, 0.95);
  works1->import(*xNS);

  RooFormulaVar* sigmaNS_2, *sigmaNS_3;
  sigmaNS_2 = new RooFormulaVar("sigmaNS_2", "@0*@1", RooArgList(*sigmaNS_1, *xNS));
  sigmaNS_3 = new RooFormulaVar("sigmaNS_3", "@0*@1", RooArgList(*sigmaNS_1, *xNS_2));

  RooRealVar *alpha, *n, *frac, *frac2;
  alpha = new RooRealVar("alpha", "alpha of Crystal bal1", 1.96, 1.0, 2.5 );
  n = new RooRealVar("n", "n of Crystal ball", 1.27, 0.8, 2.2);
  frac = new RooRealVar("frac", "CB fraction", 0.13, 0.01, 0.95);
  frac2 = new RooRealVar("frac2", "CB fraction 2", 0.25, 0.001, 0.95);
//  if(bdtlow == -1.){
//  PARAMSET FOR 2,3S
//    alpha->setVal(1.866);
//    n->setVal(1.40);
//    sigmaNS_1->setVal(0.217);
//    frac->setVal(0.1);
//    frac2->setVal(0.52);
//    xNS->setVal(0.54);
//    xNS_2->setVal(0.30);
//    PARAMSET FOR 1S
    alpha->setVal(1.866);
    n->setVal(1.50);
    sigmaNS_1->setVal(0.217);
    frac->setVal(0.1);
    frac2->setVal(0.32);
    xNS->setVal(0.54);
    xNS_2->setVal(0.30);
//  }

  RooCBShape* CBNS_1 = new RooCBShape("CBNS_1", "NS Crystal ball function1", *(works1->var("mass")), meanNS, *sigmaNS_1, *alpha, *n);
  RooCBShape* CBNS_2 = new RooCBShape("CBNS_2", "NS Crystal ball function2", *(works1->var("mass")), meanNS, *sigmaNS_2, *alpha, *n);
  RooCBShape* CBNS_3 = new RooCBShape("CBNS_3", "NS Crystal ball function3", *(works1->var("mass")), meanNS, *sigmaNS_3, *alpha, *n);

  RooAddPdf* threeCBNS = new RooAddPdf("threeCBNS", "Sum of NS Crystal ball", RooArgList(*CBNS_1, *CBNS_2, *CBNS_3), RooArgList(*frac, *frac2));

  RooGenericPdf* SignalNS;

  SignalNS = (RooGenericPdf*) threeCBNS;

  RooRealVar* nSigNS = new RooRealVar("nSigNS", "# of NS signal", 30, 0, 10000000);
  if (Trig == "Ups"){
    if(state ==1) {nSigNS->setMax(200000000); nSigNS->setVal(21000000);}
    if(state ==2) {nSigNS->setMax(40000000); nSigNS->setVal(1000000);}
    if(state ==3) {nSigNS->setMax(10000000); nSigNS->setVal(100000);}
  }
  RooAddPdf* model;
  model = new RooAddPdf("model", "NS", RooArgList(*SignalNS), RooArgList(*nSigNS));

  works1->import(*model);
/////////////////////////////////////////////////////////////FITTING START//////////////////////////////////////////////////////////////////////////////////////////
//  RooAbsReal* nll = works1->pdf("model")->createNLL(*reducedDS, Save(), PrefitDataFraction(0.005), Minimizer("Minuit","minimize"), NumCPU(38), Range(RangeLow, RangeHigh), AsymptoticError(kTRUE)/*SumW2Error(kTRUE)*/, Extended(kTRUE));
//  RooMinuit m;//*nll);
//  RooFitResult* Result = m.fit("shr");
//  Result->SetName("fitresult_model_reducedDS");

  RooFitResult* Result = works1->pdf("model")->fitTo(*reducedDS, Save(), PrefitDataFraction(0.005), Minimizer("Minuit","minimize"), NumCPU(38), Range(RangeLow, RangeHigh), /*AsymptoticError(kTRUE)*/SumW2Error(kTRUE), Extended(kTRUE));
  Result->SetName("fitresult_model_reducedDS");
  works1->pdf("model")->plotOn(massPlot, Name("modelPlot"));
 {works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*SignalNS)), LineColor(kRed), LineStyle(kDashed), MoveToBack()); works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*CBNS_1)), LineColor(kGreen), LineStyle(kSolid), MoveToBack()); works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*CBNS_2)), LineColor(kRed), LineStyle(kSolid), MoveToBack()); works1->pdf("model")->plotOn(massPlot, Components(RooArgSet(*CBNS_3)), LineColor(kMagenta), LineStyle(kDashDotted), MoveToBack());}
  massPlot->SetTitle("");
  TLatex* tl = new TLatex();
  FormLatex(tl, 42, 0.15);
  tl->DrawLatex(0.15,0.65, Form("BDT train p_{T} #in [ %d, %d ] GeV", bdtptMin, bdtptMax));
  massPlot->SetXTitle("M (GeV/c^2)");
  massPlot->SetYTitle("Counts");
  massPlot->Draw();
  Result->Print("v");
  WriteMessage("Fitting is dOnE ! ! !");
/////////////////////////////////////////////////////////////FITTING END////////////////////////////////////////////////////////////////////////////////////////////

  bool GetCont_ = false;
  RooPlot* cont_plt;
 // if(GetCont_) cont_plt = m.contour(*works1->var("n"), *works1->var("alpha"), 1, 2, 3);
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
  std::cout << " CB3S NLL : " << NLL << std::endl;
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
  YieldNS = works1->var("nSigNS")->getVal();
  YieldNSErr =  works1->var("nSigNS")->getError();

  hYield->SetBinContent(1, YieldNS);
  hYield->SetBinError(1, YieldNSErr);

  Double_t meanout, sigma1out, sigma2out;
  meanout = works1->var("meanNS")->getVal();
  sigma1out = works1->var("sigmaNS_1")->getVal();
  sigma2out = (works1->var("xNS")->getVal())*sigma1out;
  Double_t fracout = works1->var("frac")->getVal();
  Double_t sigmaout = TMath::Sqrt(fracout*sigma1out*sigma1out+(1-fracout)*sigma2out*sigma2out);

  TF1* SgnfcNS;

  SgnfcNS = works1->pdf("threeCBNS")->asTF(*(works1->var("mass")));

  Double_t TIntgrNS = SgnfcNS->Integral(RangeLow, RangeHigh);
  Double_t IntgrSig = SgnfcNS->Integral(meanout-2*sigmaout, meanout+2*sigmaout);

//  TH1D* hfrac = new TH1D("hfrac", "", 6, 0, 6);
//    hfrac->SetBinContent(1, SgnfcNS->Eval(UNS_mass));
//    hfrac->SetBinContent(2, Bkgfc->Eval(UNS_mass));
//    hfrac->SetBinContent(3, SgnfcNS->Integral(10.3, 10.4));
//    hfrac->SetBinContent(4, Bkgfc->Integral(10.3, 10.4));
//    hfrac->SetBinContent(5, SgnfcNS->Integral(10.1, 10.6));
//    hfrac->SetBinContent(6, Bkgfc->Integral(10.1, 10.6));
//  TH1D* hfracdist;
//  if( state == 1) hfracdist = new TH1D("hfracdist","",20, 9, 10);
//  if( state == 3) hfracdist = new TH1D("hfracdist","",20, 9.9, 10.9);
//  for(Int_t i =0; i <20; i++){
//    hfracdist->SetBinContent(i+1, SgnfcNS->Eval(9+0.05*i)/(SgnfcNS->Eval(9+0.05*i)+Bkgfc->Eval(9+0.05*i)));
//  }
  
  //fout = new TFile(Form("Yield/Yield_%dS_pt_%d-%d_rap_%d-%d_noWeight_MupT%s_%s_BDT_%d-%d_vp_%d_MC_%d.root",(int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), MupT.Data(), Trig.c_str(), bdtlow, bdthigh, cutQVP,(int) fixvar), "RECREATE");

  c1->SaveAs(Form("%s/CB3_MassDistribution_%dS_pt_%d-%d_rap_%d-%d_%dbin_noWeight_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_fix%d.pdf",massDIR.Data(), state,(int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Nmassbins, MupT.Data(), Trig.c_str(), bdtlow, bdthigh, bdtptMin, bdtptMax, cutQVP,(int) fixvar));
  c1->SaveAs(Form("%s/png/MassDistribution_%dS_pt_%d-%d_rap_%d-%d_%dbin_noWeight_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_fix%d.png",massDIR.Data(), state,(int)(ptMin*10), (int)(ptMax*10), (int)(rapMin*10), (int)(rapMax*10), Nmassbins, MupT.Data(), Trig.c_str(), bdtlow, bdthigh, bdtptMin, bdtptMax, cutQVP, (int) fixvar));
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

//  if(GetCont_){
//    TCanvas* cc = new TCanvas();
//    cc->cd();
//    cont_plt->Draw();
//    cc->SaveAs(Form("%s/cont.pdf",massDIRcont.Data()) );
//  }

  TFile* fout;
  long outputts = ( bdtlow == -1) ? 9999999999 : ts;
  std::string name_output = GetFit(__FITRESLATEST, true, "CB3", outputts, train_state, state,  (int) ptMin, (int) ptMax, cBinLow, cBinHigh, bdtlow, bdthigh, bdtptMin, bdtptMax, cutQVP, "");  
//  std::string name_output = Form("Yield/Yield_%ld_CB3_%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_%d.root", outputts, (int) state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), bdtlow, bdthigh, bdtptMin, bdtptMax, cutQVP,(int) fixvar);
//  if(ts >= 1634636609) name_output = Form("Yield/Yield_%ld_CB3_%dS_train%dS_pt_%d-%d_rap_%d-%d_cBin_%d-%d_MupT%s_%s_BDT_%.4f-%.4f_bdtpt_%d_%d_vp_%.4f_MC_%d.root", outputts, (int) state, train_state ,(int)ptMin, (int)ptMax, (int)(rapMin*10), (int)(rapMax*10), cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), bdtlow, bdthigh, bdtptMin, bdtptMax, cutQVP,(int) fixvar);
  fout = new TFile(name_output.c_str(), "RECREATE");

  fout->cd();
  works1->Write();
  Result->Write();
  massPlot->Write();
  hYield->Write();
  hmass->Write();
//  SgnfcNS->Write();
//  hfrac->Write();
//
//hfracdist->Write();
  std::cout << fout->GetName() << std::endl;
  fout->Close(); 
};

void MassYieldFit_BDT_MC_CB3(long _ts, const string _fname1s = "", const string _fname3s = "", const Double_t _ptMin = 0, const Double_t _ptMax = 30, const Double_t _rapMin = -2.4, const Double_t _rapMax = 2.4, const TString _MupT = "4", const string _Trig = "", int _cBinLow = 0, int _cBinHigh = 180, int _train_state =3, int _state = 1, bool _fixvar =false, bool _swflag = false, double _cutQVP = 0.01, double _bdtlow =-1., double _bdthigh = 1., int _bdtptMin =0, int _bdtptMax = 30, string dir_opt = ""){
  struct Y1Sfitvar Y1Svar;
//  if( _fixvar == true){
//    MassYieldSingleStateMCFit( &Y1Svar, _fname1s, _ptMin, _ptMax, _rapMin, _rapMax, _MupT , _Trig, _cBinHigh, 1, _fixvar);
//    std::cout << "x1sftjj,,, alpha : " << Y1Svar.alp << ", n : " << Y1Svar.n << ", x1S : " << Y1Svar.x1s << ", frac : " << Y1Svar.frac << ", sigma 1S : " << Y1Svar.sigma << std::endl;
//    MassYieldSingleStateMCFit( &Y1Svar, _fname3s, _ptMin, _ptMax, _rapMin, _rapMax, _MupT , _Trig, _cBinHigh, 3, _fixvar);
//  }
//  else if( _fixvar ==false){
    {MassYieldSingleStateMCFitCB3( &Y1Svar,_ts, _fname3s, _ptMin, _ptMax, _rapMin, _rapMax, _MupT , _Trig, _cBinLow, _cBinHigh, _train_state, _state, _fixvar, _swflag, _cutQVP, _bdtlow, _bdthigh, _bdtptMin, _bdtptMax, dir_opt);}
//  }
}

