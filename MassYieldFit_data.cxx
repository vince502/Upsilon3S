#include "./BDT/bininfo.h"
#include "./DrawHist.cxx"

//using namespace std;
using namespace RooFit;

void MassYieldFit_data(std::string type="CB2:CC3:GC",const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString MupT = "3p5", const string Trig = "", bool swflag= false, int cBinLow =0, int cBinHigh = 180, double cutQVP = 0.01, bool isBDT=true, long ts = 1, double cutBDTlow=-1, double cutBDThigh = 1. ,Double_t params[/*sigma1S_1, alpha, n , frac, k1, k2, k3*/]= {},Double_t paramslow[/*sigma1S_1, alpha, n , frac, k1, k2, k3*/]= {},Double_t paramshigh[/*sigma1S_1, alpha, n , frac, k1, k2, k3*/]= {}){

  massfitter mf = massfitter();
////////////////////////////////////////////////////////////////////////

  if (!isBDT) {
    cutBDTlow =0;
    cutBDThigh=0;
  }
  int ylim10 = (int) (rapMax*10);
  auto parsed = parser_symbol(type);
  std::string sig_func = parsed[0];
  std::string bkg_func = parsed[1];
  std::string fitdir = parsed[2];
  std::string name_fitmodel = "_"+bkg_func;

  SetStyle();
  Int_t Nmassbins;
  double range_mass_low, range_mass_high;
  if (massrng.find(ts) == massrng.end()){
    range_mass_low = 8;
    range_mass_high = 14;
    Nmassbins = 120;
    if(info_BDT(ts)[0]!="nan"){
      auto _pair_mass = parser_symbol(info_BDT(ts)[1],",");
      range_mass_low = stod(_pair_mass[0]);
      range_mass_high = stod(_pair_mass[1]);
      Nmassbins = (range_mass_high - range_mass_low)/0.05;
    }
  }
  else{
    range_mass_low = massrng[ts].first;
    range_mass_high = massrng[ts].second;
    Nmassbins = (range_mass_high - range_mass_low)/0.05;
  }

///////////////////////////////////////////////////////////////////////
//Need 
  std::string name_file_input;
  if(isBDT){
  name_file_input = Form("%s/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT.root",workdir.Data(),ts,Trig.c_str());
  }
  else name_file_input = Form("%s/roodatasetFiles/OniaRooDataSet_OniaSkim_Trig%s.root", workdir.Data(), Trig.c_str());
  std::string name_file_output = Form("%s/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f.root" ,workdir.Data(), ts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, Nmassbins, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, cutQVP );
  mf = massfitter( name_file_input.c_str(), name_file_output.c_str() );
  mf.Range_fit_low = range_mass_low;
  mf.Range_fit_high = range_mass_high;
  Double_t MupTCut = single_LepPtCut(MupT);
  Double_t etaMax= 2.4;
  Double_t etaMin = -2.4;

  if(!isBDT){
    mf.list_arg	= {"mass", "pt", "y", "cBin", "pt1", "pt2", "eta1", "eta2","QQVtxProb"};
    mf.dsCut	= Form("( pt >=%f && pt <=%f) && (y >= %f && y <=%f) && (cBin>=%d && cBin<=%d) &&(pt1 >= %f) && (pt2 >= %f) && (eta1 >= %f && eta1 <= %f) && ( eta2 >= %f && eta2 <= %f) &&(QQVtxProb > %.f", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, MupTCut, MupTCut, etaMin, etaMax, etaMin, etaMax, cutQVP);
  }
  if(isBDT){
    mf.list_arg	= {"mass", "pt", "y", "cBin", "pt1", "pt2", "eta1", "eta2", "QQVtxProb", "BDT"};
    mf.dsCut	= Form("( pt >=%f && pt <=%f) && (y >= %f && y <=%f) && (cBin>=%d && cBin<=%d) &&(pt1 >= %f) && (pt2 >= %f) && (eta1 >= %f && eta1 <= %f) && ( eta2 >= %f && eta2 <= %f) && (BDT>= %f && BDT < %f) && (QQVtxProb > %.f)", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, MupTCut, MupTCut, etaMin, etaMax, etaMin, etaMax, cutBDTlow, cutBDThigh, cutQVP);
  }




  mf.ws_init("dataset",mf.list_arg, "mass");
  mf.works->var("mass")->Print();

  TCanvas* c1 = new TCanvas("c1", "", 0, 0, 900, 600);
  TCanvas* c2 = new TCanvas("c2", "", 0, 0, 600, 600);
  c1->cd();
  TPad* pad_mass = new TPad("pad_mass", "pad_mass", 0, 0.25, 0.65, 1.0);
  pad_mass->Draw();
  TPad* pad_pull = new TPad("pad_pull", "pad_pull", 0, 0.05, 0.65, 0.25);
  pad_pull->SetBottomMargin(0);
  pad_pull->Draw();
  TPad* pad_leg = new TPad("pad_leg", "pad_leg", 0.66, 0.30, 0.96, 0.96);
  pad_leg->SetBottomMargin(0);
  pad_leg->Draw();

  TH1D* hYield = new TH1D("hYield", "", 3, 0, 3);

  pad_mass->cd();
  RooPlot* massPlot = mf.works->var("mass")->frame(Nmassbins);
  mf.works->data("reducedDS")->plotOn(massPlot, Name("massPlot"));
////////////////////////////////////////////////////////////////////////////////////

  RooRealVar mean1S("mean1S", "mean of Upsilon 1S", U1S_mass, U1S_mass-0.015, U1S_mass+0.015);

  RooRealVar mratio2("mratio2", "mratio2", U2S_mass/U1S_mass);
  RooRealVar mratio3("mratio3", "mratio3", U3S_mass/U1S_mass);
  RooFormulaVar mean2S("mean2S", "mean1S*mratio2", RooArgSet(mean1S, mratio2));
  //RooFormulaVar mean3S("mean3S", "mean1S*mratio3", RooArgSet(mean1S, mratio3));
  RooRealVar mean3S("mean3S", "mean of Upsilon 1S", U3S_mass, U3S_mass-0.010, U3S_mass+0.010);

  RooRealVar sigma1S_1("sigma1S_1", "sigma1 of 1S", 0.05, paramslow[0], paramshigh[0]);
  RooFormulaVar sigma2S_1("sigma2S_1", "@0*@1", RooArgList(sigma1S_1, mratio2));
  RooFormulaVar sigma3S_1("sigma3S_1", "@0*@1", RooArgList(sigma1S_1, mratio3));

  RooRealVar* x1S = new RooRealVar("x1S", "sigma ratio", 0.35, 0, 1);

  RooFormulaVar sigma1S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_1, *x1S));
  RooFormulaVar sigma2S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_2, mratio2));
  RooFormulaVar sigma3S_2("sigma1S_2", "@0*@1", RooArgList(sigma1S_2, mratio3));

  RooRealVar k("k", "k of Gaus-Exp Pdf", 1.0, 0, 5.0);
  RooRealVar alpha("alpha", "alpha of Crystal ball", 2.0, paramslow[1], paramshigh[1]);
  RooRealVar n("n", "n of Crystal ball", 2.0, paramslow[2], paramshigh[2]);
  RooRealVar* frac = new RooRealVar("frac", "CB fraction", 0.5, paramslow[3], paramshigh[3]);
  RooRealVar *ch4_k1, *ch4_k2, *ch4_k3, *ch4_k4;
  RooRealVar *Erfmean, *Erfp0, *Erfsigma;
  std::map<std::string, RooRealVar*> map_rrv;
  map_rrv = {
	{"alpha"	, &alpha	 },	
	{"n"		, &n		},	
	{"frac"		, frac		},
	{"x3S"		, x1S		},
    };

  fit_model_ups::CB2* cb2 ;
  fit_model_ups::ChebyChev* cc ;
  fit_model_ups::ErfExp* ee;
  RooGenericPdf* Signal1S;
  RooGenericPdf* Signal2S;
  RooGenericPdf* Signal3S;
  RooGenericPdf* Background;

  if (sig_func == "CB2"){
    cb2 = new fit_model_ups::CB2((mf.works->var("mass")), &mean1S, &mean2S, &mean3S, &sigma1S_1, &sigma2S_1, &sigma3S_1, &sigma1S_2, &sigma2S_2, &sigma3S_2, &alpha, &alpha, &alpha, &n, &n, &n, frac, frac, frac); 
    Signal1S = (RooGenericPdf*) cb2->twoCB1S;
    Signal2S = (RooGenericPdf*) cb2->twoCB2S;
    Signal3S = (RooGenericPdf*) cb2->twoCB3S;
    sigma1S_1.setVal(params[0]);
    alpha.setVal(params[1]);
    n.setVal(params[2]);
    frac->setVal(params[3]);
  }
  if (bkg_func.find("CC")!= std::string::npos){
    int order_CC = bkg_func[2]-'0';
    switch (order_CC){
      case 2 :
        ch4_k1 = new RooRealVar("ch4_k1", "ch4_k1", 0.02, paramslow[4], paramshigh[4]);
        ch4_k2 = new RooRealVar("ch4_k2", "ch4_k2", 0.02, paramslow[5], paramshigh[5]);
        cc = new fit_model_ups::ChebyChev((mf.works->var("mass")), ch4_k1, ch4_k2);
        ch4_k1->setVal(params[4]);
        ch4_k2->setVal(params[5]);
	break;
      case 3 :
        ch4_k1 = new RooRealVar("ch4_k1", "ch4_k1", 0.02, paramslow[4], paramshigh[4]);
        ch4_k2 = new RooRealVar("ch4_k2", "ch4_k2", 0.02, paramslow[5], paramshigh[5]);
        ch4_k3 = new RooRealVar("ch4_k3", "ch4_k3", 0.02, paramslow[6], paramshigh[6]);
        cc = new fit_model_ups::ChebyChev((mf.works->var("mass")), ch4_k1, ch4_k2, ch4_k3);
        ch4_k1->setVal(params[4]);
        ch4_k2->setVal(params[5]);
        ch4_k3->setVal(params[6]);
	break;
      case 4 :
        ch4_k1 = new RooRealVar("ch4_k1", "ch4_k1", 0.02, paramslow[4], paramshigh[4]);
        ch4_k2 = new RooRealVar("ch4_k2", "ch4_k2", 0.02, paramslow[5], paramshigh[5]);
        ch4_k3 = new RooRealVar("ch4_k3", "ch4_k3", 0.02, paramslow[6], paramshigh[6]);
        ch4_k4 = new RooRealVar("ch4_k4", "ch4_k4", 0.02, paramslow[7], paramshigh[7]);
        cc = new fit_model_ups::ChebyChev((mf.works->var("mass")), ch4_k1, ch4_k2, ch4_k3, ch4_k4);
        ch4_k1->setVal(params[4]);
        ch4_k2->setVal(params[5]);
        ch4_k3->setVal(params[6]);
        ch4_k4->setVal(params[7]);
	break;
    }
    Background = (RooGenericPdf*) cc->bkg;
  }
  if (bkg_func.find("EE")!=std::string::npos){
    Erfmean	= new RooRealVar("Erfmean", "Mean of Errfunction", params[4], paramslow[4], paramshigh[4]);
    Erfp0	= new RooRealVar("Erfp0", "1st parameter of Errfunction", params[5], paramslow[5], paramshigh[5]);
    Erfsigma	= new RooRealVar("Erfsigma", "Sigma of Errfunction", params[6], paramslow[6], paramshigh[6]);
    ee = new fit_model_ups::ErfExp((mf.works->var("mass")), Erfmean, Erfsigma, Erfp0);
    Background = (RooGenericPdf*) ee->bkgErf;
  }

  RooRealVar* nSig1S = new RooRealVar("nSig1S", "# of 1S signal", 400, -1000, 1000000);
  RooRealVar* nSig2S;
  RooRealVar* nSig3S;

  RooRealVar* frac2over1 = new RooRealVar("frac_2sOver1s","2S/1S",0.3,0,1);
  RooRealVar* frac3over1 = new RooRealVar("frac_3sOver1s","3S/1S",0.1,0,1);
  RooRealVar* nBkg = new RooRealVar("nBkg", "# of background signal", 300, -1000, 10000000);

  RooAddPdf* model,* model_sig;
  std::string use_model = "model";
  RooProdPdf* model_gc;
  if(fitdir=="DR"){
    model_sig = new RooAddPdf("model_sig", "1S+2S+3S", RooArgList(*Signal1S, *Signal2S, *Signal3S), RooArgList(*frac2over1, *frac3over1));
    model = new RooAddPdf("model", "1S+2S+3S", RooArgList(*model_sig, *Background), RooArgList(*nSig1S, *nBkg));
  }

  if((fitdir=="FF"||fitdir=="GC")){
    nSig2S = new RooRealVar("nSig2S", "# of 2S signal", 100, -1000, 300000);
    nSig3S = new RooRealVar("nSig3S", "# of 3S signal", 30, -10, 90000);
    std::cout << "added # of 2S, 3S signal as free parameter" << std::endl;
    model = new RooAddPdf("model", "1S+2S+3S+Bkg", RooArgList(*Signal1S, *Signal2S, *Signal3S, *Background), RooArgList(*nSig1S, *nSig2S, *nSig3S, *nBkg));

  }
  


// std::map<std::string, RooGaussian* > map_var_gc;
 RooArgSet list_var_gc;
 std::vector<RooGaussian*> map_var_gc;

  if(fitdir=="GC"){
    int count_var=0;
    for( std::vector<std::string>::iterator it_var= parsed.begin()+3; it_var != parsed.end(); it_var++){
      auto key_val = parser_symbol(it_var->c_str(),";");
      std::string name_dvar_gaussian = key_val[0]+"_constraint"; 
      double value_dvar_gaussian = stod(key_val[1]); 
      RooGaussian* _var_rg = new RooGaussian(name_dvar_gaussian.c_str(), name_dvar_gaussian.c_str(), *map_rrv[key_val[0].c_str()], RooConst(map_rrv[key_val[0].c_str()]->getVal()), RooConst(value_dvar_gaussian));
      map_var_gc.push_back(_var_rg);
      list_var_gc.add(*map_var_gc[count_var]);
      count_var++;
    }
    model_gc = new RooProdPdf("model_gc","model with gauss constraint", RooArgSet(*model,list_var_gc));
  }


////////////////////////////////////////////////////////////////////////////////////


  if(fitdir=="GC"){
    mf.works->import(*model_gc);
    model_gc->Print();
    use_model = "model_gc";
  }
  else if(fitdir!="GC"){
    mf.works->import(*model);
    mf.works->Print();
  }

  std::cout << mf.works->pdf(use_model.c_str())->GetName() << std::endl;

  RooFitResult* Result = mf.works->pdf(use_model.c_str())->fitTo(*mf.fDS, Save(), NumCPU(2), Hesse(kTRUE), Range(mf.Range_fit_low, mf.Range_fit_high), Minos(0), SumW2Error(kTRUE), Extended(kTRUE));
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Name("modelPlot"));
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Components(RooArgSet(*Signal1S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Components(RooArgSet(*Signal2S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Components(RooArgSet(*Signal3S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Components(RooArgSet(*Background)), LineColor(kBlue), LineStyle(kDashed));
  massPlot->SetTitle("");
  massPlot->SetXTitle("M (GeV/c^2)");
  massPlot->SetYTitle("Counts");
  massPlot->Draw();
  TLatex* lt0 = new TLatex();
  FormLatex(lt0, 12, 0.038);
  lt0->DrawLatex(0.53,0.85, Form("BDT #in [%.2f, %.2f]",cutBDTlow, cutBDThigh));
  lt0->DrawLatex(0.53,0.80, Form("p_{T}^{#mu} #geq %.1f GeV/c",MupTCut));
  lt0->DrawLatex(0.53,0.75, Form("%d #leq p_{T}^{#mu#mu} < %d GeV/c", (int) ptMin, (int) ptMax));
  lt0->DrawLatex(0.53,0.70, Form("Centrality %d-%d %%",(int) cBinLow/2, (int) cBinHigh/2));
  lt0->DrawLatex(0.53,0.65, Form("Trigger# : %s", Trig.c_str()));
  Result->Print("v");
  WriteMessage("Fitting is dOnE ! ! !");

  pad_pull->cd();
  pad_pull->SetGrid(0,1);
  TLine* line_pull = new TLine(mf.Range_fit_low,0.,mf.Range_fit_high, 0.);
  line_pull->SetLineColorAlpha(kRed, 0.5);
  line_pull->SetLineWidth(3);
  RooHist* hpull = massPlot->pullHist("massPlot", "modelPlot");
  RooPlot* pullPlot = mf.works->var("mass")->frame(Title("Pull Distribution"));
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
  ofstream log;
  log.open("BDT_fitcomparisonNLL.log",std::ios_base::out|std::ios_base::app);
  log << "\n"<<ts << Form(", pt eta : %.1f-%.1f |%.1f|, BDT [ %.2f, %.2f ]", ptMin, ptMax, rapMax, cutBDTlow, cutBDThigh) << std::endl;
  log << "BDT with Chebychev3  NLL : " << NLL; 
  log.close();
  std::cout << "NLL : " << NLL << std::endl;
  Int_t ndf = Npullbin - Nfitpar;

  TLatex* NormChi2tex = new TLatex();
  FormLatex(NormChi2tex, 42, 0.13);
  NormChi2tex->DrawLatex(0.15, 0.95, Form("#chi^{2}/ndf: %3.f/%d", chi2, ndf));
  WriteMessage("Pull distribution is dOnE !!!");

  pad_leg->cd();
  RooPlot* legPlot = mf.works->var("mass")->frame(Name("Fit Results"), Title("Fit Results"));
  RooArgList parList = Result->floatParsFinal();
  parList.Print("v");
  mf.works->pdf(use_model.c_str())->paramOn(legPlot, Layout(0, 0.93, 0.97), Parameters(parList));
  legPlot->getAttText()->SetTextAlign(11);
  legPlot->getAttText()->SetTextSize(0.05);

  TPaveText* Ptext = (TPaveText*) legPlot->findObject(Form("%s_paramBox", mf.works->pdf(use_model.c_str())->GetName()));
  Ptext->SetY1(0.01);
  Ptext->SetY2(0.95);
  Ptext->Draw();

  WriteMessage("Writting result is dOnE !!!");

  Double_t Yield1S	= mf.works->var("nSig1S")->getVal();
  Double_t Yield1SErr	= mf.works->var("nSig1S")->getError();
  Double_t Yield2S, Yield3S, Yield2SErr, Yield3SErr;
  if(fitdir !="DR"){
    Yield2S 	= mf.works->var("nSig2S")->getVal();
    Yield2SErr 	= mf.works->var("nSig2S")->getError();
    Yield3S 	= mf.works->var("nSig3S")->getVal();
    Yield3SErr 	= mf.works->var("nSig3S")->getError();

  }
  if(fitdir == "DR"){
    Double_t frac2to1 = mf.works->var("frac_2sOver1s")->getVal();
    Double_t frac3to1 = mf.works->var("frac_3sOver1s")->getVal();
    Yield2S 	= frac2to1 * Yield1S;
    Yield3S 	= frac3to1 * Yield1S;
    Yield2SErr 	= Yield2S*Yield1SErr+Yield1S*(mf.works->var("frac_2sOver1s")->getError());
    Yield3SErr 	= Yield3S*Yield1SErr+Yield1S*(mf.works->var("frac_3sOver1s")->getError());
    nSig2S = new RooRealVar("nSig2S", "# of 2S signal",Yield2S,-1000,300000); 
    nSig3S = new RooRealVar("nSig3S", "# of 2S signal",Yield3S,-10, 90000); 
    nSig2S->setError(Yield2SErr);
    nSig3S->setError(Yield3SErr);
    mf.works->import(RooArgList(*nSig2S,*nSig3S));
  }
  Double_t YieldBkg 	= mf.works->var("nBkg")->getVal();

  hYield->SetBinContent(1, Yield1S);
  hYield->SetBinError(1, Yield1SErr);
  hYield->SetBinContent(2, Yield2S);
  hYield->SetBinError(2, Yield2SErr);
  hYield->SetBinContent(3, Yield3S);
  hYield->SetBinError(3, Yield3SErr);

  Double_t meanout = mf.works->var("mean1S")->getVal();
  Double_t sigma1out = mf.works->var("sigma1S_1")->getVal();
  Double_t sigma2out = (mf.works->var("x1S")->getVal())*sigma1out;
  Double_t fracout = mf.works->var("frac")->getVal();
  Double_t sigmaout = TMath::Sqrt(fracout*sigma1out*sigma1out+(1-fracout)*sigma2out*sigma2out);

  TF1* Sgnfc1S;
  TF1* Sgnfc2S;
  TF1* Sgnfc3S;

  Sgnfc1S = mf.works->pdf("twoCB1S")->asTF(*(mf.works->var("mass")));
  Sgnfc2S = mf.works->pdf("twoCB2S")->asTF(*(mf.works->var("mass")));
  Sgnfc3S = mf.works->pdf("twoCB3S")->asTF(*(mf.works->var("mass")));

  TF1* Bkgfc;
  if(bkg_func.find("CC")!= std::string::npos){
    Bkgfc = mf.works->pdf("CCBkg")->asTF(*(mf.works->var("mass")));
  }
  if(bkg_func.find("EE")!= std::string::npos){
    Bkgfc = mf.works->pdf("bkgErf")->asTF(*(mf.works->var("mass")));
  }

  Double_t TIntgr1S = Sgnfc1S->Integral(mf.Range_fit_low, mf.Range_fit_high);
  Double_t TIntgr2S = Sgnfc2S->Integral(mf.Range_fit_low, mf.Range_fit_high);
  Double_t TIntgr3S = Sgnfc3S->Integral(mf.Range_fit_low, mf.Range_fit_high);
  Double_t TIntgrBkg = Bkgfc->Integral(mf.Range_fit_low, mf.Range_fit_high);
  Double_t IntgrSig = Sgnfc1S->Integral(meanout-2*sigmaout, meanout+2*sigmaout);
  Double_t IntgrBkg = Bkgfc->Integral(meanout-2*sigmaout, meanout+2*sigmaout);
  Double_t Significance =(Yield1S*IntgrSig/TIntgr1S/TMath::Sqrt(((Yield1S*IntgrSig/TIntgr1S)+(YieldBkg*IntgrBkg/TIntgrBkg))));

  TH1D* hfrac = new TH1D("hfrac", "", 6, 0, 6);
  hfrac->SetBinContent(1, Sgnfc1S->Eval(U1S_mass));
  hfrac->SetBinContent(2, Bkgfc->Eval(U1S_mass));
  hfrac->SetBinContent(3, Sgnfc1S->Integral(9.3, 9.6));
  hfrac->SetBinContent(4, Bkgfc->Integral(9.3, 9.6));
  hfrac->SetBinContent(5, Sgnfc1S->Integral(9.1, 9.8));
  hfrac->SetBinContent(6, Bkgfc->Integral(9.1, 9.8));

  TH1D* hfracdist = new TH1D("hfracdist","",20, 9, 10);
  for(Int_t i =0; i <20; i++){
    hfracdist->SetBinContent(i+1, Sgnfc1S->Eval(9+0.05*i)/(Sgnfc1S->Eval(9+0.05*i)+Bkgfc->Eval(9+0.05*i)));
  }
  /**/
  mf.fout->cd();
  RooWorkspace* wtmp = new RooWorkspace("workspace");
  wtmp->import(*mf.works->var("mass")); 
  wtmp->import(*mf.works->var("nSig2S"));
  wtmp->import(*mf.works->var("nSig3S"));
  wtmp->import(*mf.works->pdf(use_model.c_str())); 
  wtmp->import(*mf.works->data("reducedDS")); 
  wtmp->Write();
  Result->Write();
  massPlot->Write();



  hYield->Write();
  Sgnfc1S->Write();
  Sgnfc2S->Write();
  Sgnfc3S->Write();
  hfrac->Write();
  hfracdist->Write();
  mf.fout->Close();

  DrawHist(parsed, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, Nmassbins);
 
}
