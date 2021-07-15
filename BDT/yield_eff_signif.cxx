#include "yield_eff_signif.h"
#include "Get_Optimal_BDT.cxx"

binplotter::binplotter(){
};

binplotter::binplotter(std::string _type, long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _blow, double _bhigh, bool find_bdt = true){
  type = _type; ts = _ts; ylim = _ylim;  pl = _pl; ph = _ph; cl = _cl; ch = _ch; blow = _blow; bhigh = _bhigh;

  int nbin = 120;
  if (massrng.find(ts) != massrng.end()) { nbin = (int) ((massrng[ts].second - massrng[ts].first)/0.05); } 
  init(find_bdt);
  std::cout << "--------------------Calculated nbin : " << nbin << "----------------------"<< std::endl;
};

binplotter::~binplotter(){ file1->Close(); };

void binplotter::init(bool get_bdt= true){
  auto info_fit = parser_symbol(type, ":");
  fitfunc = info_fit[1];
  int ylim10 = (int) (ylim*10);
  int nbin = 120;
  std::string fitdir, markDDiter;
  auto info_string_BDT = info_BDT(ts);

  if (massrng.find(ts) != massrng.end()) { nbin = (int) ((massrng[ts].second - massrng[ts].first)/0.05); } 
  else if (info_string_BDT[1] != "nan") {
    auto m_pair =  parser_symbol(info_string_BDT[1],",");
    double m_low = stod( m_pair[0].c_str()) ;
    double m_high = stod( m_pair[1].c_str()) ;
    nbin = (int) ((m_high - m_low)/0.05) ; 
  }
  fitdir = info_fit[2].c_str();
  fittype =fitdir;
  
  if(get_bdt){ blow = Get_Optimal_BDT(ts, pl, ph,(double) -1*ylim, ylim, cl, ch, vcut).first; }
  
  filename = Form("/home/vince402/Upsilon3S/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", ts, fitdir.c_str(),Form("_%s",fitfunc.c_str()) ,pl,ph, ylim10, ylim10,nbin, cl, ch, blow, bhigh, vcut);
  if(fitdir.find("DD") != std::string::npos){
    filename = filename.substr(0, filename.length() -5) + Form("_DDiter%d.root",fitdir[4]-48); 
  }

  std::cout << "Opening Yield file : " << filename.c_str() << std::endl;
  if(TFile::Open(filename.c_str(), "open")==nullptr || TFile::Open(filename.c_str(),"read")->IsZombie()|| refit){
    std::cout << "Running Fitter for new Yield" << std::endl;
    string command;
    if(strcmp(fitfunc.c_str(),"")==0){ command =Form("root -l -b -q \'../MassYieldFit_BDT.C(\"/home/vince402/Upsilon3S/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT.root\", %d, %d, %.1f, %.1f, \"3p5\", \"S13\", %d, %d, %.3f, %.2f, %.2f , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 0.5, 0.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 4, 7, 0.95, 9, 4.0, 8})\'",ts, pl, ph,-1*ylim,ylim, cl, ch, vcut, blow, bhigh);}
    if(strcmp(fitfunc.c_str(),"_CC3")==0){ command =Form("root -l -b -q \'../MassYieldFit_BDT_CC3.C(\"/home/vince402/Upsilon3S/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT.root\", %d, %d, %.1f, %.1f, \"3p5\", \"S13\", %d, %d, %.3f, %.2f, %.2f , (Double_t[]) {0.13, 1.54, 3.68, 0.56, -0.1, -0.1, 0.0}, (Double_t[]) {0.01, 0.5, 0.5, 0.15, -0.2, -0.2, -0.1}, (Double_t[]) {0.25, 4, 7, 0.95, 0.2,0.2,0.2})\'",ts, pl, ph,-1*ylim,ylim, cl, ch, vcut, blow, bhigh);}
    int a = system(command.c_str());
  }
  file1 =TFile::Open(filename.c_str());
  res = (RooFitResult*) file1->Get("fitresult_model_reducedDS");
  if(res==nullptr)
  {
    res = (RooFitResult*) file1->Get("fitresult_model_gc_reducedDS");
  }
  worksp = (RooWorkspace*) file1->Get("workspace");
};

void binplotter::set_params(double _vcut){
  vcut = _vcut;
  init();
};
void binplotter::set_params(string _fitfunc){
  fitfunc = _fitfunc;
  init();
};

void binplotter::set_params(string _fitfunc, double _vcut){
  fitfunc = _fitfunc;
  vcut = _vcut;
  init();
};

void binplotter::dump(){
  std::cout << Form(" ts %ld ylim %.4f blow %.4f bhigh %.4f pl %d ph %d cl %d ch %d vcut %.4f MupT %s Trig %s fittype %s filename %s fitfunc %s",ts, ylim, blow, bhigh, pl, ph, cl, ch, vcut, MupT.Data(), Trig.c_str(), fittype.c_str(), filename.c_str(), fitfunc.c_str()) << std::endl;
};


std::pair<RooRealVar, RooRealVar> binplotter::get_frac(){

  RooRealVar Yield1S, Frac2S, Frac3S;
  const RooArgList& paramList = res->floatParsFinal();
  for( auto arg : paramList) {
    if(strcmp(arg->GetName(),"nSig1S")==0){
      Yield1S = RooRealVar( *((RooRealVar*) arg));
    }
    if(strcmp(arg->GetName(),"frac_2sOver1s")==0){
      Frac2S = RooRealVar(*((RooRealVar*) arg));
    }
    if(fittype.find("DR2")==std::string::npos){
      if(strcmp(arg->GetName(),"frac_3sOver1s")==0){
        Frac3S = RooRealVar(*((RooRealVar*) arg));
      }
    }
  if(fittype.find("DR2")!=std::string::npos){
      if(strcmp(arg->GetName(),"frac_3sOver2s")==0){
        Frac3S = RooRealVar(*((RooRealVar*) arg));
      }
    }
  }
  yield1S = Yield1S;
  frac2S = Frac2S;
  frac3S = Frac3S;
  return std::make_pair(Frac2S, Frac3S);

};

RooRealVar binplotter::get_bkg(int state = 3)
{
  TH1D* _hfrac  = (TH1D*) file1->Get("hfrac");
  double int_frac = _hfrac->GetBinContent(7);
  double int_norm = _hfrac->GetBinContent(8);
  double bkg_frac = int_frac/int_norm;
  RooRealVar nBkg;
  const RooArgList& paramList = res->floatParsFinal();
  for( auto arg : paramList) {
    if(strcmp(arg->GetName(),"nBkg")==0){
      nBkg = RooRealVar(*((RooRealVar*) arg) );
      std::cout << "BKG YIELD: " <<  nBkg.getVal() << ", frac: " << bkg_frac << std::endl;
    }
  }
  RooRealVar res_var = RooRealVar(Form("%dSBKG", state),"", bkg_frac*nBkg.getVal());
  res_var.setError(bkg_frac*nBkg.getError());
  return res_var;
};

RooRealVar binplotter::get_yield(int state =3 ){
  RooRealVar Yield1S, Yield2S, Yield3S;
  const RooArgList& paramList = res->floatParsFinal();
  Yield1S = *(RooRealVar*) worksp->var("nSig1S");
  Yield2S = *(RooRealVar*) worksp->var("nSig2S");
  Yield3S = *(RooRealVar*) worksp->var("nSig3S");
  for( auto arg : paramList) {
    if(strcmp(arg->GetName(),"nSig1S")==0){
      Yield1S = RooRealVar(*((RooRealVar*) arg));
    }
    if(strcmp(arg->GetName(),"nSig2S")==0){
      Yield2S = RooRealVar(*((RooRealVar*) arg));
    }
    if(strcmp(arg->GetName(),"nSig3S")==0){
      Yield3S = RooRealVar(*((RooRealVar*) arg));
    }
  }
  yield1S = Yield1S;
  yield2S = Yield2S;
  yield3S = Yield3S;
  if(state ==1) return Yield1S;
  if(state ==2) return Yield2S;
  else return Yield3S;

};

std::pair<double, double> binplotter::get_eff(int state =3){
  std::pair<double, double> bdteff = openEffhist((float) pl, (float) ph, -1.*(ylim), ylim, cl, ch, true, true, false, kTrigUps, ts, blow, bhigh, state);  
  return bdteff;
};

RooRealVar binplotter::yield_eff(){
  RooRealVar Yield3S = binplotter::get_yield();
  double bdteff = get_eff().first;
  std::cout << Yield3S.GetName()<< ": " << Yield3S.getVal() << ", Error: " << Yield3S.getError()<< std::endl;
  std::cout << "BDT efficiency of : " << bdteff << std::endl;
  RooRealVar YoverE("YE","Yield over Eff", (Yield3S.getVal()/bdteff), -100, 100000);
  YoverE.setError(Yield3S.getError()/bdteff);
  return YoverE;
};
