#pragma once
#include "yield_eff_signif.h"
#include "Get_Optimal_BDT.cxx"
#include "BDTtraindiff.cxx"
#include "../script_tools.h"

binplotter::binplotter(){};

#ifdef GETBKGOX
binplotter::binplotter(ana_bins x, int _bdtptMin, int _bdtptMax ){
  type = Form("CB3:CC%d:%s", getNomBkgO(x), findtype(x).c_str()) ;
  ts = 9999999999; ylim = 2.4, pl = (double) x.pl; ph = (double) x.ph; cl = x.cl; ch = x.ch; blow = Get_BDT(ts, x.train_state, x.state, pl, ph, cl, ch, 0., ylim, 2); bhigh = 1; bdtptMin = _bdtptMin; bdtptMax = _bdtptMax; train_state = x.state; eff_old = false; train_state = x.train_state;
  init(false);
};
#endif
binplotter::binplotter(long _ts, ana_bins _x, string _type, double _bcut){
  type = _type; ts = _ts; ylim = 2.4, pl = (double) _x.pl; ph = (double) _x.ph; cl = _x.cl; ch = _x.ch; blow = _bcut; bhigh = 1; bdtptMin = _x.bpl; bdtptMax = _x.bph; target_state = _x.state; eff_old = false; train_state = _x.train_state;
  init(false);
};
binplotter::binplotter(std::string _type, long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _vcut, double _blow, double _bhigh, int _bdtptMin, int _bdtptMax, int _train_state =3, int _target_state=3,  bool find_bdt = false, bool _eff_old = false){
  type = _type; ts = _ts; ylim = _ylim;  pl = _pl; ph = _ph; cl = _cl; ch = _ch; blow = _blow; bhigh = _bhigh; bdtptMin = _bdtptMin; bdtptMax = _bdtptMax;train_state = _train_state; target_state = _target_state; eff_old = _eff_old; vcut= _vcut;

  int nbin = 120;
  if (massrng.find(ts) != massrng.end()) { nbin = (int) ((massrng[ts].second - massrng[ts].first)/0.05); } 
  init(find_bdt);
};

//binplotter::binplotter(std::string _type, long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _blow, double _bhigh, int _bdtptMin, int _bdtptMax, int _train_state =3, int _target_state=3,  bool find_bdt = false, bool _eff_old = false) : binplotter( _type, _ts, _ylim, _pl, _ph, _cl, _ch, 0, _blow, _bhigh, _bdtptMin, _bdtptMax, _train_state, _target_state, find_bdt, _eff_old){};

binplotter::binplotter(std::string _type, long _ts, double _ylim, int _pl, int _ph, int _cl, int _ch, double _blow, double _bhigh, int _bdtptMin, int _bdtptMax, int _train_state =3, int _target_state =3,  bool find_bdt = false, bool _eff_old = false) : binplotter( _type, _ts, _ylim, _pl, _ph, _cl, _ch, 0., _blow, _bhigh, _bdtptMin, _bdtptMax, _train_state, _target_state, find_bdt, _eff_old){};

binplotter::~binplotter(){ 
	std::cout << "[bp][Deconstruct] call" << std::endl;
	if(file1->IsOpen() ) file1->Close();
//	if( NS ) delete NS;
//	if( NB ) delete NB;
};

void binplotter::init(bool get_bdt= true){
  std::cout << "Init binplotter " << std::endl;
//  if ( file1 != nullptr && file1-> ) file1->Close();
  auto info_fit = parser_symbol(type, ":");
  fitfunc = info_fit[0]+"_"+info_fit[1];
  int ylim10 = (int) (ylim*10);
  int nbin = 120;
  std::string fitdir, markDDiter;
  bool getfromstream = false;
  if (massrng.find(ts) != massrng.end()) { nbin = (int) ((massrng[ts].second - massrng[ts].first)/0.05); } 
  if(getfromstream){
    auto info_string_BDT = info_BDT(ts);
    if (info_string_BDT[1] != "nan") {
 	auto m_pair =  parser_symbol(info_string_BDT[1],",");
	double m_low = stod( m_pair[0].c_str()) ;
    	double m_high = stod( m_pair[1].c_str()) ;
  	nbin = (int) ((m_high - m_low)/0.05) ; 
    }
  }
  else {
    double m_low = 8;
    double m_high = 11.5;
    nbin = (int) ((m_high - m_low)/0.05);
  }
  fitdir = info_fit[2].c_str();
  fittype =fitdir;
  
  if(get_bdt){ blow = Get_BDT(ts_alias(ts), train_state, bdtptMin, bdtptMax, pl, ph, cl, ch, vcut, (double)ylim);}//Get_Optimal_BDT(ts, pl, ph,(double) -1*ylim, ylim, cl, ch, vcut, train_state).first; }
  filename = GetFit(__FITRESLATEST, false, type, ts, train_state, target_state, pl, ph, cl, ch, blow, bhigh, bdtptMin, bdtptMax, vcut,"");  
//  filename = Form("/home/vince402/Upsilon3S/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f.root", ts, fitdir.c_str(),Form("_%s",fitfunc.c_str()) ,pl,ph, ylim10, ylim10,nbin, cl, ch, blow, bhigh,  bdtptMin, bdtptMax, vcut);
//  if(ts >= 1634636609) filename = Form("/home/vince402/Upsilon3S/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_bdtpt_%d_%d_vp%.4f.root", train_state, ts, fitdir.c_str(),Form("_%s",fitfunc.c_str()) ,pl,ph, ylim10, ylim10, cl, ch, blow, bhigh, bdtptMin, bdtptMax, vcut);
//  if( blow == -1.0000){
//	  filename = Form("/home/vince402/Upsilon3S/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", ts, fitdir.c_str(),Form("_%s",fitfunc.c_str()) ,pl,ph, ylim10, ylim10,nbin, cl, ch, blow, bhigh,  vcut);
//	  if(ts >= 1634636609){ auto query_file =  getfileany(Form("%s/Yield", workdir.Data()), Form("Yield_:S_9999999999_FF_CB3_CC4:pt_%d-%d:cbin_%d-%d:BDT1_cut-1.0000-1.0000:vp%.4f.root",pl, ph, cl, ch, vcut) );
//	  if(!query_file.empty()) filename = Form("%s/Yield/%s",workdir.Data(), query_file[0].c_str());
//	  }
		  //Form("/home/vince402/Upsilon3S/Yield/Yield_%dS_%ld_%s%s_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-%.4f_vp%.4f.root", train_state, ts, fitdir.c_str(),Form("_%s",fitfunc.c_str()) ,pl,ph, ylim10, ylim10, cl, ch, blow, bhigh,  vcut);
//  }
  std::cout << "[bp] yield file name : " << filename.c_str() << std::endl;
  if(fitdir.find("DD") != std::string::npos){
    filename = filename.substr(0, filename.length() -5) + Form("_DDiter%d.root",fitdir[4]-48); 
  }

//  std::cout << "Opening Yield file : " << filename.c_str() << std::endl;
  file1 =TFile::Open(filename.c_str());
  std::cout << "[bp][init] file1 is open? : " << file1->IsOpen() << std::endl;
  if(file1==nullptr || file1->IsZombie()|| refit){
	throw std::invalid_argument( "No Fit Results found! Fit the data first" );
  }
  auto file_keys = file1->GetListOfKeys();
	std::cout << "[bp][init] keys in files : ";
  for ( auto key : *file_keys ){
	std::cout << key->GetName() << ", ";
  }
    std::cout << std::endl;

  RooFitResult *res_tmp;
  res_tmp = (RooFitResult*) file1->Get("fitresult_model_reducedDS");

  if(res_tmp==nullptr)
  {
    res_tmp = (RooFitResult*) file1->Get("fitresult_model_gc_reducedDS");
  }
  worksp = (RooWorkspace*) file1->Get("workspace");
  res = (RooFitResult*) res_tmp->Clone();
//  std::cout << "[bp][init] res : " << static_cast<void*> (res) << ", " << res->GetName() << std::endl;

//  res->SetDirectory(0);
//  worksp->SetDirectory(0);
};

void binplotter::set_params(double _vcut){
  vcut = _vcut;
  init(false);
};
void binplotter::set_params(string _fitfunc){
  fitfunc = _fitfunc;
  init(false);
};

void binplotter::set_params(string _fitfunc, double _vcut){
  fitfunc = _fitfunc;
  vcut = _vcut;
  init();
};

void binplotter::dump(){
  std::cout << Form(" ts %ld ylim %.4f blow %.4f bhigh %.4f pl %d ph %d cl %d ch %d vcut %.4f MupT %s Trig %s fittype %s filename %s fitfunc %s",ts, ylim, blow, bhigh, pl, ph, cl, ch, vcut, MupT.Data(), Trig.c_str(), fittype.c_str(), filename.c_str(), fitfunc.c_str()) << std::endl;
};


RooRealVar binplotter::return_23s_frac( bool withEff =false){

  RooRealVar Yield2S, Yield3S;
  const RooArgList& paramList = res->floatParsFinal();
  Yield2S = *(RooRealVar*) worksp->var("nSig2S");
  Yield3S = *(RooRealVar*) worksp->var("nSig3S");

  if ( withEff ){
  	  auto eff2s = this->get_eff(2);
  	  auto eff3s = this->get_eff(3);
	  return RooRealVar("23frac_eff", "", (Yield3S.getVal()* eff2s.first) /( eff3s.first * Yield2S.getVal()));
  }
  else{ 
	  return RooRealVar("23frac", "", (Yield3S.getVal()) /(Yield2S.getVal()));
  }

};

RooRealVar binplotter::get_frac(int state){

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
  if(state == 3) return Frac3S;
  if(state ==2) return Frac2S;
  else return RooRealVar("wrongState","",0);

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
  RooRealVar res_var = RooRealVar(Form("%dSBKG", state),"", nBkg.getVal());
  res_var.setError(nBkg.getError());
  return res_var;
};

RooRealVar binplotter::get_yield(int state =3 ){
	std::cout << "[bp][get_yield] state : " << state << std::endl;
//	std::cout << "[bp][get_yield] res alive? : " << static_cast<void*>(res) << std::endl;
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

std::pair<double, double> binplotter::get_eff(int state =3, bool getNum = false){
	std::cout << "[bp][get_eff] :" << train_state << ", " << state << std::endl;
  std::pair<double, double> bdteff = openEffhist((float) pl, (float) ph, -1.*(ylim), ylim, cl, ch, true, true, false, kTrigUps, ts_alias(ts), blow, bhigh, bdtptMin, bdtptMax, train_state, state, vcut, eff_old, getNum);  
  return bdteff;
};

std::pair<double, double> binplotter::get_eff_sysdpt(int state =3, std::string what = "", bool getNum = false){
  std::pair<double, double> bdteff;
  if(what == "NO") bdteff= openEffhist_SYSNODPT((float) pl, (float) ph, -1.*(ylim), ylim, cl, ch, true, true, false, kTrigUps, ts_alias(ts), blow, bhigh, train_state, state, vcut, what, getNum);  
  else bdteff = openEffhist_SYSDPT((float) pl, (float) ph, -1.*(ylim), ylim, cl, ch, true, true, false, kTrigUps, ts_alias(ts), blow, bhigh, train_state, state, vcut, what, getNum);  
  return bdteff;
};

std::vector<double> binplotter::get_eff_NN(int state =3){
  std::vector<double> bdteff = openEffhist_SYS((float) pl, (float) ph, -1.*(ylim), ylim, cl, ch, true, true, false, kTrigUps, ts_alias(ts), blow, bhigh, bdtptMin, bdtptMax, train_state, state, vcut, eff_old, false);  
//  std::vector<double> bdteff = openEffhist_SYSDPT_NN((float) pl, (float) ph, -1.*(ylim), ylim, cl, ch, true, true, false, kTrigUps, ts_alias(ts), blow, bhigh, train_state, state, vcut, "",eff_old);  
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
