#include "./BDT/bininfo.h"
#include "./DrawHist.cxx"

//using namespace std;
using namespace RooFit;

struct params_vhl{
  Double_t val;
  Double_t low;
  Double_t high;
};
//void MassYieldFit_data(std::string type="CB2:CC3:GC",int train_state =3, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString MupT = "3p5", const string Trig = "", bool swflag= false, int cBinLow =0, int cBinHigh = 181, double cutQVP = 0.00, bool isBDT=true, long ts = 1, double cutBDTlow=-1, double cutBDThigh = 1. ,int bdtptMin =0, int bdtptMax = 30, Double_t params[/*sigma1S_1, alpha, n , frac, k1, k2, k3*/]= {},Double_t paramslow[/*sigma1S_1, alpha, n , frac, k1, k2, k3*/]= {},Double_t paramshigh[/*sigma1S_1, alpha, n , frac, k1, k2, k3*/]= {}, std::map<std::string, params_vhl> map_params={}, int workers = 10){
void MassYieldFit_data(std::string type="CB2:CC3:GC",int train_state =3, const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2.4, const Double_t rapMax = 2.4, const TString MupT = "3p5", const string Trig = "", bool swflag= false, int cBinLow =0, int cBinHigh = 181, double cutQVP = 0.00, bool isBDT=true, long ts = 1, double cutBDTlow=-1, double cutBDThigh = 1. ,int bdtptMin =0, int bdtptMax = 30, std::vector<Double_t> params= {}, std::vector<Double_t> paramslow= {}, std::vector<Double_t> paramshigh= {}, std::map<std::string, params_vhl> map_params={}, int workers = 10){
  massfitter mf = massfitter();
////////////////////////////////////////////////////////////////////////
  int DDiter = 0;

  if (!isBDT) {
    cutBDTlow =0;
    cutBDThigh=0;
  }
  int ylim10 = (int) (rapMax*10);
  std::cout << "[INPUT] Data Fitter type : " << type << std::endl;
  auto parsed = parser_symbol(type);
  std::string sig_func = parsed[0];
  std::string bkg_func = parsed[1];
  std::string fitdir = parsed[2];
  std::string name_fitmodel = "_"+sig_func+"_"+bkg_func;
  dbg();

  SetStyle();
  double range_mass_low, range_mass_high;
  if (massrng.find(ts) == massrng.end()){
    range_mass_low = 8;
    range_mass_high = 14;
  }
  else{
  dbg();
    range_mass_low = massrng[ts].first;
    range_mass_high = massrng[ts].second;
  }
  if( map_params.find("mass_range") != map_params.end()){
  dbg();
    range_mass_low = map_params["mass_range"].low;
    range_mass_high = map_params["mass_range"].high;
  }
  dbg();

///////////////////////////////////////////////////////////////////////
//Need
  std::string name_file_input;
  if(isBDT){
  name_file_input = Form("%s/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_Trig%s_BDT.root",workdir.Data(),ts,Trig.c_str());
    if(map_params.find("SYSHF") != map_params.end() ){
      if( ts==9999999998 && map_params["SYSHF"].val ==  1){ name_file_input =Form("%s/BDT/roodatasets/OniaRooDataset_BDT9999999998_OniaSkim_Trig%s_BDT_SYSHFUP.root",workdir.Data(),Trig.c_str());}
      if( ts==9999999997 && map_params["SYSHF"].val ==  1){ name_file_input =Form("%s/BDT/roodatasets/OniaRooDataset_BDT9999999997_OniaSkim_Trig%s_BDT_SYSHFDOWN.root",workdir.Data(),Trig.c_str());}

    }
  }
  else name_file_input = Form("%s/roodatasetFiles/OniaRooDataSet_OniaSkim_Trig%s.root", workdir.Data(), Trig.c_str());
  string aux = "";
  if(map_params.find("tmp") != map_params.end() &&map_params["tmp"].val == 1) aux = "_tmp";
  long outputts = ( cutBDTlow == -1 ) ? 9999999999 : ts;
  std::string name_file_output = GetFit(__FITRESLATEST, false, type, outputts, train_state, 0, (int) ptMin, (int) ptMax, cBinLow, cBinHigh, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, aux);
//  std::string name_file_output = Form("%s/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f%s.root" ,workdir.Data(), outputts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10,  cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, aux.c_str() );
//
// if( ts >= 1634636609) name_file_output = Form("%s/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f%s.root" ,workdir.Data(), train_state, outputts, fitdir.c_str(), name_fitmodel.c_str(), (int) ptMin, (int) ptMax,  ylim10, ylim10, cBinLow, cBinHigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, cutQVP, aux.c_str() );
  if(fitdir.find("DD") != std::string::npos){
    DDiter = fitdir[4]-48;
    name_file_output = name_file_output.substr(0,name_file_output.length()-5) + Form("_DDiter%d.root", DDiter);
  }
  mf = massfitter( name_file_input.c_str(), name_file_output.c_str() );
  mf.Range_fit_low = range_mass_low;
  mf.Range_fit_high = range_mass_high;
  if( map_params.find("mass_range") != map_params.end()){
    mf.Range_fit_low = map_params["mass_range"].low;
    mf.Range_fit_high = map_params["mass_range"].high;
  }
  Double_t MupTCut = single_LepPtCut(MupT);
  Double_t etaMax= 2.4;
  Double_t etaMin = -2.4;
  Double_t massMin= 0;
  Double_t massMax= 999;
  if(map_params.find("massCut")!=map_params.end()){
	  massMin = map_params["massCut"].low;
	  massMax = map_params["massCut"].high;
  	  mf.Range_fit_low = map_params["massCut"].low;
      mf.Range_fit_high = map_params["massCut"].high;
  }
  if(!isBDT){
    mf.list_arg	= {"mass", "pt", "y", "cBin", "pt1", "pt2", "eta1", "eta2","QQVtxProb"};
    mf.dsCut	= Form("(mass >=%f && mass <=%f) && ( pt >=%f && pt <=%f) && (y >= %f && y <=%f) && (cBin>=%d && cBin<%d) &&(pt1 >= %f) && (pt2 >= %f) && (eta1 >= %f && eta1 <= %f) && ( eta2 >= %f && eta2 <= %f) &&(QQVtxProb > %.f", massMin, massMax, ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, MupTCut, MupTCut, etaMin, etaMax, etaMin, etaMax, cutQVP);
  }
  if(isBDT){
    mf.list_arg	= {"mass", "pt", "y", "cBin", "pt1", "pt2", "eta1", "eta2", "QQVtxProb", "BDT"};
    mf.dsCut	= Form("(mass >= %f && mass <= %f) &&( pt >=%f && pt <=%f) && (y >= %f && y <=%f) && (cBin>%d && cBin<=%d) &&(pt1 >= %f) && (pt2 >= %f) && (eta1 >= %f && eta1 <= %f) && ( eta2 >= %f && eta2 <= %f) && (BDT>= %f && BDT < %f) && (QQVtxProb > %.f)", massMin, massMax,ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, MupTCut, MupTCut, etaMin, etaMax, etaMin, etaMax, cutBDTlow, cutBDThigh, cutQVP);
  }
  std::string name_dataset = "dataset";
  int ds_state = train_state;
  int ds_pl = (int) bdtptMin;
  int ds_ph = (int) bdtptMax;
  if(map_params.find("DS_alter") !=map_params.end()){
	  params_vhl altpar = map_params["DS_alter"];
	  ds_state = altpar.val;
	  ds_pl = altpar.low;
	  ds_ph = altpar.high;
  }
  if( ts >= 1634636609 ) name_dataset = name_dataset + Form("_Y%dSpt%dto%d", ds_state, ds_pl, ds_ph);
  mf.ws_init(name_dataset.c_str(),mf.list_arg, "mass");
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
  RooPlot* massPlot = mf.works->var("mass")->frame();
  mf.works->data("reducedDS")->plotOn(massPlot, Name("massPlot"));
////////////////////////////////////////////////////////////////////////////////////

  RooRealVar *mean1S = new RooRealVar("mean1S", "mean of Upsilon 1S", U1S_mass, U1S_mass-0.05, U1S_mass+0.05);

  RooRealVar *mratio2 = new RooRealVar("mratio2", "mratio2", U2S_mass/U1S_mass);
  RooRealVar *mratio3 = new RooRealVar("mratio3", "mratio3", U3S_mass/U1S_mass);
  RooFormulaVar *mean2S = new RooFormulaVar("mean2S", "mean1S*mratio2", RooArgSet(*mean1S, *mratio2));
  RooFormulaVar *mean3S = new RooFormulaVar("mean3S", "mean1S*mratio3", RooArgSet(*mean1S, *mratio3));
  //RooRealVar mean3S("mean3S", "mean of Upsilon 1S", U3S_mass, U3S_mass-0.010, U3S_mass+0.010);

  RooRealVar *sigma1S_1 = new RooRealVar("sigma1S_1", "sigma1 of 1S", map_params["sigma1S1"].val, map_params["sigma1S1"].low,map_params["sigma1S1"].high);


  RooFormulaVar *sigma2S_1 = new RooFormulaVar("sigma2S_1", "@0*@1", RooArgList(*sigma1S_1, *mratio2));
  RooFormulaVar *sigma3S_1 = new RooFormulaVar("sigma3S_1", "@0*@1", RooArgList(*sigma1S_1, *mratio3));

  RooRealVar* x1S = new RooRealVar("x1S", "sigma ratio", 0.1, 0.01, 2);
  RooRealVar* x1S_2 = new RooRealVar("x1S_2", "sigma ratio", 0.4, 0.01, 2);


  RooFormulaVar *sigma1S_2 = new RooFormulaVar("sigma1S_2", "@0*@1", RooArgList(*sigma1S_1, *x1S));
  RooFormulaVar *sigma2S_2 = new RooFormulaVar("sigma2S_2", "@0*@1", RooArgList(*sigma1S_2, *mratio2));
  RooFormulaVar *sigma3S_2 = new RooFormulaVar("sigma3S_2", "@0*@1", RooArgList(*sigma1S_2, *mratio3));

  RooFormulaVar *sigma1S_3 = new RooFormulaVar("sigma1S_3", "@0*@1", RooArgList(*sigma1S_1, *x1S_2));
  RooFormulaVar *sigma2S_3 = new RooFormulaVar("sigma2S_3", "@0*@1", RooArgList(*sigma1S_3, *mratio2));
  RooFormulaVar *sigma3S_3 = new RooFormulaVar("sigma3S_3", "@0*@1", RooArgList(*sigma1S_3, *mratio3));

  RooRealVar k("k", "k of Gaus-Exp Pdf", 1.0, 0, 5.0);
  RooRealVar *alpha, *frac2;
  alpha = new RooRealVar("alpha", "alpha of Crystal ball", map_params["alpha"].val, map_params["alpha"].low,map_params["alpha"].high);

  RooRealVar* n = new RooRealVar("n", "n of Crystal ball", map_params["var_n"].val, map_params["var_n"].low,map_params["var_n"].high);
  RooRealVar* frac = new RooRealVar("frac", "CB fraction", map_params["frac"].val, map_params["frac"].low,map_params["frac"].high);
  if(sig_func=="CB3"|| sig_func=="CB2G" )
  {
    frac2 = new RooRealVar("frac2", "CB fraction", map_params["frac2"].val,  map_params["frac2"].low, map_params["frac2"].high);
    if(map_params.find("xNS")!=map_params.end()){
      x1S->setVal(map_params["xNS"].val);
      x1S->setRange(map_params["xNS"].low, map_params["xNS"].high);
  }
    if(map_params.find("xNS_2")!=map_params.end()){
      std::cout << map_params["xNS_2"].val << std::endl;
      x1S_2->setVal(map_params["xNS_2"].val);
      x1S_2->setRange(map_params["xNS_2"].low, map_params["xNS_2"].high);
  }
  }

  if(map_params["sigma1S1"].high==-1){ sigma1S_1->setConstant(); sigma1S_1->setRange(0,999); sigma1S_1->setVal(map_params["sigma1S1"].val); }
  if(map_params["alpha"].high==-1){ alpha->setConstant(); alpha->setRange(0,999); alpha->setVal(map_params["alpha"].val); }
  if(map_params["var_n"].high==-1){ n->setConstant(); n->setRange(0,999); n->setVal(map_params["var_n"].val); }
  if(map_params["frac"].high==-1){ frac->setConstant(); frac->setRange(0,999); frac->setVal(map_params["frac"].val); }
  if(map_params["frac2"].high == -1){ frac2->setConstant(); frac2->setRange(0,999); frac2->setVal(map_params["frac2"].val); };
  if(map_params["xNS"].high == -1){ x1S->setConstant(); x1S->setRange(0,999); x1S->setVal(map_params["xNS"].val); };
  if(map_params["xNS_2"].high == -1){ x1S_2->setConstant(); x1S_2->setRange(0,999); x1S_2->setVal(map_params["xNS_2"].val); };

  RooRealVar *ch4_k1, *ch4_k2, *ch4_k3, *ch4_k4, *ch4_k5, *ch4_k6;
  RooRealVar *Erfmean, *Erfp0, *Erfsigma;
  std::map<std::string, RooRealVar*> map_rrv;
  if(fitdir.find("DD") != std::string::npos)
  {
    if((int) (fitdir[4]-48)>0)
    {
      alpha->setConstant();
      if( (int) (fitdir[4]-48 >1) )
      {
	frac->setConstant();
	if( (int) (fitdir[4]-48) > 2)
	{
	  x1S->setConstant();
	  x1S->setVal(0.248);
	  if( (int) (fitdir[4]-48) > 3)
	  {
	    sigma1S_1->setConstant();
	    if( (int) (fitdir[4]-48) > 4 )
	    {
	      n->setConstant();
	    }
	  }
	}
      }
    }
  }
  map_rrv = {
	{"alpha"	, alpha	 },	
	{"n"		, n		},	
	{"frac"		, frac		},
	{"frac2"	, frac2		},
	{"xNS"		, x1S		},
	{"xNS_2"	, x1S_2		},
	{"sigmaNS_1"	, sigma1S_1	},
    };

  fit_model_ups::CB2* cb2 ;
  fit_model_ups::CB3* cb3 ;
  fit_model_ups::CB2Gaus* cb2g ;
  fit_model_ups::ChebyChev* cc ;
  fit_model_ups::ExpChebyChev* ecc;
  fit_model_ups::ErfExp* ee;
  RooGenericPdf* Signal1S;
  RooGenericPdf* Signal2S;
  RooGenericPdf* Signal3S;
  RooGenericPdf* Background;
  std::string name_sig_pdf= "twoCB";

  if (sig_func == "CB3"){
    name_sig_pdf="threeCB";    
	if(map_params.find("signal_separate") != map_params.end()){
		if(map_params["signal_separate"].val == 1){
    	cb3 = new fit_model_ups::CB3((mf.works->var("mass")), mean1S, mean2S, mean3S, sigma1S_1, sigma2S_1, sigma3S_1, sigma1S_2, sigma2S_2, sigma3S_2, sigma1S_3, sigma2S_3, sigma3S_3, alpha, n,frac, frac2); 
		}
    	else cb3 = new fit_model_ups::CB3((mf.works->var("mass")), mean1S, mean2S, mean3S, sigma1S_1, sigma2S_1, sigma3S_1, sigma1S_2, sigma2S_2, sigma3S_2, sigma1S_3, sigma2S_3, sigma3S_3, alpha, n,frac, frac2); 
	}
	else{
    cb3 = new fit_model_ups::CB3((mf.works->var("mass")), mean1S, mean2S, mean3S, sigma1S_1, sigma2S_1, sigma3S_1, sigma1S_2, sigma2S_2, sigma3S_2, sigma1S_3, sigma2S_3, sigma3S_3, alpha, n,frac, frac2); 
	}
    Signal1S = (RooGenericPdf*) cb3->threeCB1S;
    Signal2S = (RooGenericPdf*) cb3->threeCB2S;
    Signal3S = (RooGenericPdf*) cb3->threeCB3S;
	
  }

  if (sig_func == "CB2G"){
    name_sig_pdf="twoCBGaus";    
    cb2g = new fit_model_ups::CB2Gaus((mf.works->var("mass")), mean1S, mean2S, mean3S, sigma1S_1, sigma2S_1, sigma3S_1, sigma1S_2, sigma2S_2, sigma3S_2, sigma1S_3, sigma2S_3, sigma3S_3, alpha, alpha, alpha, n, n, n, frac, frac, frac, frac2, frac2, frac2); 
    Signal1S = (RooGenericPdf*) cb2g->CBG1S;
    Signal2S = (RooGenericPdf*) cb2g->CBG2S;
    Signal3S = (RooGenericPdf*) cb2g->CBG3S;
  }
  if (sig_func == "CB2"){
    cb2 = new fit_model_ups::CB2((mf.works->var("mass")), mean1S, mean2S, mean3S, sigma1S_1, sigma2S_1, sigma3S_1, sigma1S_2, sigma2S_2, sigma3S_2, alpha, alpha, alpha, n, n, n, frac, frac, frac); 
    Signal1S = (RooGenericPdf*) cb2->twoCB1S;
    Signal2S = (RooGenericPdf*) cb2->twoCB2S;
    Signal3S = (RooGenericPdf*) cb2->twoCB3S;
  }

  if (bkg_func.find("CC")!= std::string::npos){
    int order_CC = bkg_func[bkg_func.find_last_of("CC")+1] - 48;
    switch (order_CC){
      case 1 :
        ch4_k1 = new RooRealVar("ch4_k1", "ch4_k1", 0.02, paramslow[0], paramshigh[0]);
        cc = new fit_model_ups::ChebyChev((mf.works->var("mass")), ch4_k1);
        ch4_k1->setVal(params[0]);
	break;
      case 2 :
        ch4_k1 = new RooRealVar("ch4_k1", "ch4_k1", 0.02, paramslow[0], paramshigh[0]);
        ch4_k2 = new RooRealVar("ch4_k2", "ch4_k2", 0.02, paramslow[1], paramshigh[1]);
        cc = new fit_model_ups::ChebyChev((mf.works->var("mass")), ch4_k1, ch4_k2);
        ch4_k1->setVal(params[0]);
        ch4_k2->setVal(params[1]);
	break;
      case 3 :
        ch4_k1 = new RooRealVar("ch4_k1", "ch4_k1", 0.02, paramslow[0], paramshigh[0]);
        ch4_k2 = new RooRealVar("ch4_k2", "ch4_k2", 0.02, paramslow[1], paramshigh[1]);
        ch4_k3 = new RooRealVar("ch4_k3", "ch4_k3", 0.02, paramslow[2], paramshigh[2]);
        cc = new fit_model_ups::ChebyChev((mf.works->var("mass")), ch4_k1, ch4_k2, ch4_k3);
        ch4_k1->setVal(params[0]);
        ch4_k2->setVal(params[1]);
        ch4_k3->setVal(params[2]);
	break;
      case 4 :
        ch4_k1 = new RooRealVar("ch4_k1", "ch4_k1", 0.02, paramslow[0], paramshigh[0]);
        ch4_k2 = new RooRealVar("ch4_k2", "ch4_k2", 0.02, paramslow[1], paramshigh[1]);
        ch4_k3 = new RooRealVar("ch4_k3", "ch4_k3", 0.02, paramslow[2], paramshigh[2]);
        ch4_k4 = new RooRealVar("ch4_k4", "ch4_k4", 0.02, paramslow[3], paramshigh[3]);
        cc = new fit_model_ups::ChebyChev((mf.works->var("mass")), ch4_k1, ch4_k2, ch4_k3, ch4_k4);
        ch4_k1->setVal(params[0]);
        ch4_k2->setVal(params[1]);
        ch4_k3->setVal(params[2]);
        ch4_k4->setVal(params[3]);
	break;
      case 5 :
        ch4_k1 = new RooRealVar("ch4_k1", "ch4_k1", 0.02, paramslow[0], paramshigh[0]);
        ch4_k2 = new RooRealVar("ch4_k2", "ch4_k2", 0.02, paramslow[1], paramshigh[1]);
        ch4_k3 = new RooRealVar("ch4_k3", "ch4_k3", 0.02, paramslow[2], paramshigh[2]);
        ch4_k4 = new RooRealVar("ch4_k4", "ch4_k4", 0.02, paramslow[3], paramshigh[3]);
        ch4_k5 = new RooRealVar("ch4_k5", "ch4_k5", 0.02, paramslow[4], paramshigh[4]);
        cc = new fit_model_ups::ChebyChev((mf.works->var("mass")), ch4_k1, ch4_k2, ch4_k3, ch4_k4, ch4_k5);
        ch4_k1->setVal(params[0]);
        ch4_k2->setVal(params[1]);
        ch4_k3->setVal(params[2]);
        ch4_k4->setVal(params[3]);
        ch4_k5->setVal(params[4]);
	break;
      case 6 :
        ch4_k1 = new RooRealVar("ch4_k1", "ch4_k1", 0.02, paramslow[0], paramshigh[0]);
        ch4_k2 = new RooRealVar("ch4_k2", "ch4_k2", 0.02, paramslow[1], paramshigh[1]);
        ch4_k3 = new RooRealVar("ch4_k3", "ch4_k3", 0.02, paramslow[2], paramshigh[2]);
        ch4_k4 = new RooRealVar("ch4_k4", "ch4_k4", 0.02, paramslow[3], paramshigh[3]);
        ch4_k5 = new RooRealVar("ch4_k5", "ch4_k5", 0.02, paramslow[4], paramshigh[4]);
        ch4_k6 = new RooRealVar("ch4_k6", "ch4_k6", 0.02, paramslow[5], paramshigh[5]);
        cc = new fit_model_ups::ChebyChev((mf.works->var("mass")), ch4_k1, ch4_k2, ch4_k3, ch4_k4, ch4_k5, ch4_k6);
        ch4_k1->setVal(params[0]);
        ch4_k2->setVal(params[1]);
        ch4_k3->setVal(params[2]);
        ch4_k4->setVal(params[3]);
        ch4_k5->setVal(params[4]);
        ch4_k5->setVal(params[5]);
	break;
    }
    if( (bkg_func.find("ECC")!=std::string::npos)){
      ecc = new fit_model_ups::ExpChebyChev(cc->bkg);
      std::cout << ecc->bkgECC->GetName() << std::endl;
      Background = (RooGenericPdf*) ecc->bkgECC;
    }

    if( (bkg_func.find("ECC")==std::string::npos)) Background = (RooGenericPdf*) cc->bkg;
  }
  if (bkg_func.find("EE")!=std::string::npos){
    Erfmean	= new RooRealVar("Erfmean", "Mean of Errfunction", params[0], paramslow[0], paramshigh[0]);
    Erfp0	= new RooRealVar("Erfp0", "1st parameter of Errfunction", params[1], paramslow[1], paramshigh[1]);
    Erfsigma	= new RooRealVar("Erfsigma", "Sigma of Errfunction", params[2], paramslow[2], paramshigh[2]);
    ee = new fit_model_ups::ErfExp((mf.works->var("mass")), Erfmean, Erfsigma, Erfp0);
    Background = (RooGenericPdf*) ee->bkgErf;
  }

dbg(1000);
  RooRealVar* nSig1S = new RooRealVar("nSig1S", "# of 1S signal", 900, -1000, 1000000);
  RooRealVar* nSig2S;
  RooRealVar* nSig3S;

dbg(1000);
  RooRealVar* frac2over1 = new RooRealVar("frac_2sOver1s","2S/1S",0.15,-0.,0.4);
  RooRealVar* frac3over1 = new RooRealVar("frac_3sOver1s","3S/1S",0.03,-0.02,0.20);
  RooRealVar* frac3over2 = new RooRealVar("frac_3sOver2s","3S/2S",0.3,-0.2,1);
  RooRealVar* nBkg = new RooRealVar("nBkg", "# of background signal", 300, -1000, 10000000);

dbg(1000);
  RooAddPdf* model,* model_sig, *model_sig2;
  std::string use_model = "model";
  RooProdPdf* model_gc;
  if(fitdir.find("DR")!=std::string::npos){
    if(fitdir.find("DR2")!=std::string::npos){
      std::cout << "Making model for fractional yield parameters" << std::endl;
      model_sig2 = new RooAddPdf("model_sig2", "2S+3S", RooArgList(*Signal2S, *Signal3S), RooArgList(RooConst(1), *frac3over2));
      model_sig = new RooAddPdf("model_sig", "1S+2S+3S", RooArgList(*Signal1S, *model_sig2), RooArgList(RooConst(1), *frac2over1));
      model = new RooAddPdf("model", "1S+2S+3S", RooArgList(*model_sig, *Background), RooArgList(*nSig1S, *nBkg));
    }
    else {
      std::cout << "Making model for fractional yield parameters" << std::endl;
    model_sig = new RooAddPdf("model_sig", "1S+2S+3S", RooArgList(*Signal1S, *Signal2S, *Signal3S), RooArgList(RooConst(1), *frac2over1, *frac3over1));
    model = new RooAddPdf("model", "1S+2S+3S", RooArgList(*model_sig, *Background), RooArgList(*nSig1S, *nBkg));
    }
  }
dbg(1000);

  if((fitdir.find("DR")==std::string::npos)&&(fitdir.find("FF")!=std::string::npos||fitdir.find("GC")!= std::string::npos||fitdir.find("DD") != std::string::npos)){
    nSig2S = new RooRealVar("nSig2S", "# of 2S signal", 100, -1000, 10000);
    nSig3S = new RooRealVar("nSig3S", "# of 3S signal", 30, -100, 2000);
    std::cout << "added # of 2S, 3S signal as free parameter" << std::endl;
    model = new RooAddPdf("model", "1S+2S+3S+Bkg", RooArgList(*Signal1S, *Signal2S, *Signal3S, *Background), RooArgList(*nSig1S, *nSig2S, *nSig3S, *nBkg));

  }
  


// std::map<std::string, RooGaussian* > map_var_gc;
 RooArgSet list_var_gc;
 RooArgSet list_var_for_gc;
 std::vector<RooGaussian*> map_var_gc;
 

  if(fitdir.find("GC")!=std::string::npos){
    int count_var=0;
    std::cout << "[GAUS CONSTRAIN] Initializing Paramters for Constrain Fit" << std::endl;
    std::cout << parsed[3] << std::endl;
    for( std::vector<std::string>::iterator it_var= parsed.begin()+3; it_var != parsed.end(); it_var++){
      std::cout << it_var->c_str() << std::endl;
      if(strcmp(it_var->c_str(),"GCPEND")==0) break;
      auto key_val = parser_symbol(it_var->c_str(),";");
      for( auto val : key_val){
	std::cout << val << std::endl;
      }
      std::string name_dvar_gaussian = key_val[0]+"_constraint"; 
      double value_dvar_gaussian = stod(key_val[1]); 
      RooGaussian* _var_rg = new RooGaussian(name_dvar_gaussian.c_str(), name_dvar_gaussian.c_str(), *map_rrv[key_val[0].c_str()], RooConst(map_rrv[key_val[0].c_str()]->getVal()), RooConst(value_dvar_gaussian));
      _var_rg->Print();
      map_var_gc.push_back(_var_rg);
      list_var_gc.add(*map_var_gc[count_var]);
      list_var_for_gc.add(*map_rrv[key_val[0].c_str()]);
      count_var++;
    }
    model_gc = new RooProdPdf("model_gc","model with gauss constraint", RooArgSet(*model,list_var_gc));
  }


////////////////////////////////////////////////////////////////////////////////////


  if(fitdir.find("GC")!=std::string::npos){
    mf.works->import(*model_gc);
    model_gc->Print();
    use_model = "model_gc";
  }
  else if(fitdir.find("GC")==std::string::npos){
    dbg(1021);
    mf.works->import(*model);
    mf.works->Print();
  }
  dbg(1000);

  std::cout << mf.works->pdf(use_model.c_str())->GetName() << std::endl;

  RooFitResult* Result;
  if(fitdir.find("GC")!=std::string::npos){
    std::cout << "Fitting with Gaussian Constraint" << std::endl;
    Result = mf.works->pdf(use_model.c_str())->fitTo(*mf.fDS, Save(), Constrain(list_var_for_gc), PrefitDataFraction(0.1), Minimizer("Minuit","minimize"), NumCPU(workers), Range(mf.Range_fit_low, mf.Range_fit_high), SumW2Error(kTRUE), Extended(kTRUE));
  }
  else  {Result = mf.works->pdf(use_model.c_str())->fitTo(*mf.fDS, Save(), PrefitDataFraction(0.1),  Minimizer("Minuit","minimize"), NumCPU(workers), Range(mf.Range_fit_low, mf.Range_fit_high), SumW2Error(kTRUE), Extended(kTRUE));}
dbg();
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Name("modelPlot"));
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Components(RooArgSet(*Signal1S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Components(RooArgSet(*Signal2S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Components(RooArgSet(*Signal3S)), LineColor(kRed), LineStyle(kDashed), MoveToBack());
  mf.works->pdf(use_model.c_str())->plotOn(massPlot, Components(RooArgSet(*Background)), LineColor(kBlue), LineStyle(kDashed));
  dbg(1000);
  massPlot->SetTitle("");
  massPlot->SetXTitle("M (GeV/c^2)");
  massPlot->SetYTitle("Counts");
  massPlot->Draw();
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
  Int_t Nfitpar = Result->floatParsFinal().getSize();
  Double_t NLL = Result->minNll();
  ofstream log;
  log.open("BDT_fitcomparisonNLL.log",std::ios_base::out|std::ios_base::app);
  log << "\n"<<ts << Form(", pt eta : %.1f-%.1f |%.1f|, BDT [ %.4f, %.4f ]", ptMin, ptMax, rapMax, cutBDTlow, cutBDThigh) << std::endl;
  log << Form("BDT with %s%s  NLL : ",sig_func.c_str(), name_fitmodel.c_str() ) << NLL; 
  log.close();
  std::cout << "NLL : " << NLL << std::endl;
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

int i = 499;
dbg(i);i++;
  Double_t Yield1S	= mf.works->var("nSig1S")->getVal();
  Double_t Yield1SErr	= mf.works->var("nSig1S")->getError();
  Double_t Yield2S, Yield3S, Yield2SErr, Yield3SErr;
  if(fitdir.find("DR")==std::string::npos){
    Yield2S 	= mf.works->var("nSig2S")->getVal();
    Yield2SErr 	= mf.works->var("nSig2S")->getError();
    Yield3S 	= mf.works->var("nSig3S")->getVal();
    Yield3SErr 	= mf.works->var("nSig3S")->getError();

  }
  if(fitdir.find("DR")!=std::string::npos){
    if(fitdir.find("DR2")!=std::string::npos){
      Double_t frac2to1 = mf.works->var("frac_2sOver1s")->getVal();
      Double_t frac3to2 = mf.works->var("frac_3sOver2s")->getVal();
      Yield2S 	= frac2to1 * Yield1S;
      Yield3S 	= frac2to1*frac3to2 * Yield1S;
      Yield2SErr 	= TMath::Sqrt( TMath::Power(frac2to1*Yield1SErr,2)+TMath::Power(Yield1S*(mf.works->var("frac_2sOver1s")->getError()),2) );
      Yield3SErr 	= TMath::Sqrt( TMath::Power(frac2to1*frac3to2*Yield1SErr,2)+TMath::Power(Yield2S*(mf.works->var("frac_3sOver2s")->getError()),2) +TMath::Power(Yield1S*(mf.works->var("frac_2sOver1s")->getError())*frac3to2, 2));
      nSig2S = new RooRealVar("nSig2S", "# of 2S signal",Yield2S,-1000,300000); 
      nSig3S = new RooRealVar("nSig3S", "# of 2S signal",Yield3S,-100, 90000); 
      nSig2S->setError(Yield2SErr);
      nSig3S->setError(Yield3SErr);
      mf.works->import(RooArgList(*nSig2S,*nSig3S));
    }
    else {
      Double_t frac2to1 = mf.works->var("frac_2sOver1s")->getVal();
      Double_t frac3to1 = mf.works->var("frac_3sOver1s")->getVal();
      Yield2S 	= frac2to1 * Yield1S;
      Yield3S 	= frac3to1 * Yield1S;
      Yield2SErr 	= TMath::Sqrt( TMath::Power(frac2to1*Yield1SErr,2)+TMath::Power(Yield1S*(mf.works->var("frac_2sOver1s")->getError()),2) );
      Yield3SErr 	= TMath::Sqrt( TMath::Power(frac3to1*Yield1SErr,2)+TMath::Power(Yield1S*(mf.works->var("frac_3sOver1s")->getError()),2) );
      nSig2S = new RooRealVar("nSig2S", "# of 2S signal",Yield2S,-1000,300000); 
      nSig3S = new RooRealVar("nSig3S", "# of 2S signal",Yield3S,-100, 90000); 
      nSig2S->setError(Yield2SErr);
      nSig3S->setError(Yield3SErr);
      mf.works->import(RooArgList(*nSig2S,*nSig3S));
    }
  }

  Double_t YieldBkg 	= mf.works->var("nBkg")->getVal();
  dbg();
  hYield->SetBinContent(1, Yield1S);
  hYield->SetBinError(1, Yield1SErr);
  hYield->SetBinContent(2, Yield2S);
  hYield->SetBinError(2, Yield2SErr);
  hYield->SetBinContent(3, Yield3S);
  hYield->SetBinError(3, Yield3SErr);
  dbg();

  Double_t meanout = mf.works->var("mean1S")->getVal();
  if(fitdir.find("DR") ==std::string::npos){
//    Double_t meanout3S = mf.works->var("mean3S")->getVal();
  }
  Double_t sigma1out = mf.works->var("sigma1S_1")->getVal();
  Double_t sigma2out = (mf.works->var("x1S")->getVal())*sigma1out;
  Double_t fracout = mf.works->var("frac")->getVal();
  Double_t sigmaout = TMath::Sqrt(fracout*sigma1out*sigma1out+(1-fracout)*sigma2out*sigma2out);

  TF1* Sgnfc1S;
  TF1* Sgnfc2S;
  TF1* Sgnfc3S;

  std::cout << name_sig_pdf.c_str() << std::endl;

  Sgnfc1S = mf.works->pdf(Form("%s1S", name_sig_pdf.c_str()))->asTF(*(mf.works->var("mass")));
  Sgnfc2S = mf.works->pdf(Form("%s2S", name_sig_pdf.c_str()))->asTF(*(mf.works->var("mass")));
  Sgnfc3S = mf.works->pdf(Form("%s3S", name_sig_pdf.c_str()))->asTF(*(mf.works->var("mass")));

  TF1* Bkgfc;
  if(bkg_func.find("CC")!= std::string::npos){
    Bkgfc = mf.works->pdf("CCBkg")->asTF(*(mf.works->var("mass")));
  }
  if(bkg_func.find("EE")!= std::string::npos){
    Bkgfc = mf.works->pdf("bkgErf")->asTF(*(mf.works->var("mass")));
  }

  dbg();
  Double_t TIntgr1S = Sgnfc1S->Integral(mf.Range_fit_low, mf.Range_fit_high);
  Double_t TIntgr2S = Sgnfc2S->Integral(mf.Range_fit_low, mf.Range_fit_high);
  Double_t TIntgr3S = Sgnfc3S->Integral(mf.Range_fit_low, mf.Range_fit_high);
  Double_t TIntgrBkg = Bkgfc->Integral(mf.Range_fit_low, mf.Range_fit_high);
  Double_t IntgrSig = Sgnfc1S->Integral(meanout-2*sigmaout, meanout+2*sigmaout);
  Double_t IntgrBkg = Bkgfc->Integral(meanout-2*sigmaout, meanout+2*sigmaout);
  Double_t Significance =(Yield1S*IntgrSig/TIntgr1S/TMath::Sqrt(((Yield1S*IntgrSig/TIntgr1S)+(YieldBkg*IntgrBkg/TIntgrBkg))));

  dbg();
  TH1D* hfrac = new TH1D("hfrac", "", 7, 0, 7);
  hfrac->SetBinContent(1, Sgnfc1S->Eval(U1S_mass));
  hfrac->SetBinContent(2, Bkgfc->Eval(U1S_mass));
  hfrac->SetBinContent(3, Sgnfc1S->Integral(9.3, 9.6));
  hfrac->SetBinContent(4, Bkgfc->Integral(9.3, 9.6));
  hfrac->SetBinContent(5, Sgnfc1S->Integral(9.1, 9.8));
  hfrac->SetBinContent(6, Bkgfc->Integral(9.1, 9.8));
  hfrac->SetBinContent(7, Bkgfc->Integral(8.0, 8.6)+Bkgfc->Integral(10.8, mf.Range_fit_high));
  hfrac->SetBinContent(8, Bkgfc->Integral(mf.Range_fit_low, mf.Range_fit_high));

  dbg();
  TH1D* hfracdist = new TH1D("hfracdist","",20, 9, 10);
  for(Int_t i =0; i <20; i++){
    hfracdist->SetBinContent(i+1, Sgnfc1S->Eval(9+0.05*i)/(Sgnfc1S->Eval(9+0.05*i)+Bkgfc->Eval(9+0.05*i)));
  dbg();
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
  int drawmag = (int) map_params["mag"].val; 

  DrawHist(parsed, ptMin, ptMax, rapMin, rapMax, MupT, Trig, swflag, cBinLow, cBinHigh, cutQVP, isBDT, ts, cutBDTlow, cutBDThigh, bdtptMin, bdtptMax, map_params["sb_ratio"].val, train_state, (bool) drawmag, massMin, massMax, aux );
 
}
