#ifndef BININFO_H
#define BININFO_H
#include <vector>
#include <map>
#include "../tdrstyle.C"
#include "../CMS_lumi_square.C"
#include "../.workdir.h"
#include "../fitter.h"
#include "../fitreslib.h"

static TH1D* Get_Optimal_BDT_HIST; 
const double interval_score = 0.05;

std::string MuIDHybridSoft2018 = "nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&fabs(dxy1)<0.3&&fabs(dxy2)<0.3&&fabs(dz1)<20&&fabs(dz2)<20";

std::map<long, std::map<int, std::vector<std::pair<double,double> > > >bdtbinsec =
{
	{1618900983, 
		{
			{ 3, {{-1.0, -0},{0, 0.34},{0.34, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.2},{0.2, 0.34},{0.34, 1.0}}
			}
		}
	}
};

std::map<long, std::pair<double,double> > massrng = 
{
	{1620630542, {8, 11.5} }
};

//STANDARD ID FIT RESULT YIELD, EFFICIENCY MAP, NOT GOING TO BE USED FOR NOMINAL RESULTS
//std::map<std::map<YLIM ,std::pair<std::pair<CBINL, CBINH>, std::pair<PTLOW ,PTHIGH> >, std::pair<EFF, std::pair<YIELD, ERR>> >> 
std::map<double ,std::map<std::pair<std::pair<int, int>, std::pair<double,double> >, std::pair<double, std::pair<double,double>> >> hybfitinfo= {
	{2.4,
		{
		{{{0,180},{0,4}},{0.4750,{304,40}}},{{{0,180},{4,9}},{0.5135,{264,139}}},{{{0,180},{9,12}},{0.5849,{57,68}}},{{{0,180},{12,30}},{0.6358,{174,48}}},{{{0,180},{0,30}},{0.5100,{860,252}}},
		{{{0,40},{0,6}},{0.4750,{304,40}}}, {{{0,40},{6,30}},{0.5135,{264,139}}},{{{0,40},{0,30}},{0.5849,{57,68}}},
		{{{40,100},{0,6}},{0.4750,{304,40}}}, {{{40,100},{6,30}},{0.5135,{264,139}}},{{{40,100},{0,30}},{0.5849,{57,68}}},
		{{{100,180},{0,6}},{0.4750,{304,40}}}, {{{100,180},{6,30}},{0.5135,{264,139}}},{{{100,180},{0,30}},{0.5849,{57,68}}},
		{{{0,180},{0,6}},{0.4750,{304,40}}}, {{{0,180},{6,30}},{0.5135,{264,139}}}
		}
	},
	{1.2,
		{
		{{{0,180},{0,4}},{0.4750,{304,40}}},{{{0,180},{4,9}},{0.5135,{264,139}}},{{{0,180},{9,12}},{0.5849,{57,68}}},{{{0,180},{12,30}},{0.6358,{174,48}}},{{{0,180},{0,30}},{0.5100,{860,252}}},
		{{{0,40},{0,6}},{0.4750,{304,40}}}, {{{0,40},{6,30}},{0.5135,{264,139}}},{{{0,40},{0,30}},{0.5849,{57,68}}},
		{{{40,100},{0,6}},{0.4750,{304,40}}}, {{{40,100},{6,30}},{0.5135,{264,139}}},{{{40,100},{0,30}},{0.5849,{57,68}}},
		{{{100,180},{0,6}},{0.4750,{304,40}}}, {{{100,180},{6,30}},{0.5135,{264,139}}},{{{100,180},{0,30}},{0.5849,{57,68}}},
		{{{0,180},{0,6}},{0.4750,{304,40}}}, {{{0,180},{6,30}},{0.5135,{264,139}}}
		}
	}
};

std::pair<int, int> blindpair(long ts= 1618557840){

  fstream input;
  input.open(Form("%s/BDT/BDT_description.log",workdir.Data()));
  std::map<int, std::string> dictmap;
  std::string stringbuf;
  while (input.peek() != EOF){
    std::getline(input, stringbuf);
    int inputts = stoi(stringbuf.substr(0,10));
    dictmap[inputts] = stringbuf.substr(12);
  }
  if(strcmp(dictmap[ts].substr(0,5).c_str(),"BLIND")==0){
    int nttrain = std::stoi(dictmap[ts].substr(6,1));
    int nttest = std::stoi(dictmap[ts].substr(8,1));
    return std::pair<int, int> (nttrain, nttest);
  }
  else{ std::cout << "This timestamp is not for BLIND train" << std::endl; return std::pair<int, int>(0,0);}
  input.close();
};

std::vector< std::string > info_BDT(long ts, std::string aux = "")
{
	std::fstream input;
	input.open(Form("%s/BDT/BDT_description.log",workdir.Data()), std::fstream::in | std::fstream::app);
	if(!input.is_open())  std::cout<< "File not open \n";
	std::map<long, std::string> dictmap;
	std::string stringbuf;
	while (input.peek() != EOF){
	  std::getline(input, stringbuf);
	  long inputts;
	  if(strcmp(&stringbuf[0], "#")==0) continue;
	  try{
	    try{
	      stol( stringbuf.substr(0,10));
	      inputts = stol( stringbuf.substr(0,10));
	    }
	    catch(...){
	      stol( stringbuf.substr(0,11));
	      inputts = stol( stringbuf.substr(0,11));
	    }
	  }
	  catch(...){
	    if( aux != ""){
	      continue;
//	      if( input.find(aux) != std::string::npos){
//	        return parser_symbol(input);
//	      }
	    }
	    else continue;
	  }
	  dictmap[inputts] = stringbuf;
	}
	input.close();
	if(input.is_open())  std::cout<< "File still open \n";
	try{
	  return parser_symbol(dictmap[ts], "::");
	}
	catch(...){
	  std::vector<std::string> null_pair = {{""}};
	  return null_pair;
	}

};
double Get_BDT(long ts, int state, int bdtptMin, int bdtptMax, int ptMin, int ptMax, int cBinLow, int cBinHigh, double vcut =0.00, double rap = 2.4, int signif_ = 2, string opt= ""){
  string name_file = Form("%s/BDT/Significance_hist/HIST_train%dS_bdtpt_%d_%d_%ld_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_vp_%.4f_S%d.root", workdir.Data(), state, bdtptMin, bdtptMax, ts, ptMin, ptMax, (int) (rap*10), (int) (rap*10), cBinLow, cBinHigh, vcut, signif_);
  TFile* input_file;
  TNamed* key;
  string BDTkey = "latest";
  if(strcmp(opt.c_str(),"")!=0) BDTkey += "_" +opt;
  try{
  input_file =TFile::Open(name_file.c_str());
  key = (TNamed*) input_file->Get(BDTkey.c_str());
  input_file->Close();
  }
  catch(...){return -2;}

  return stod(key->GetTitle());
};


std::pair<double,TH1D*> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, double ratio =0.16, int train_state =3, int bdtptMin = 0, int bdtptMax = 30 , string name_input_opt = "", string formula_significance= "S2", string the_opt ="", bool save = true);
std::pair<double,TH1D*> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, RooRealVar r_ratio, int train_state =3, int bdtptMin = 0, int bdtptMax = 30 , string name_input_opt = "", string formula_significance= "S2");

RooRealVar get_eff_acc(std::string type, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh,int train_state =3 , int bdtptMin = 0, int bdtptMax = 30,  int state1 =1, int state2 = 3, bool eff_old = false);

TH1D* func_hist_optimal_BDT();

//#if !defined(YIELD_EFF_SIGNIF_H)
//struct ana_bins : TObject{
struct ana_bins{
//	ana_bins() =default ;
//	ana_bins(TString _bin_attr, int _pl, int _ph, int _cl, int _ch, int _centl, int _centh, int _plot_idx, int _state){ bin_attr = _bin_attr; pl = _pl ; ph = _ph; cl = _cl; ch = _ch; centl = _centl; centh = _centh; plot_idx =_plot_idx; state = _state;};
	string bin_attr;
	int bpl, bph, pl, ph, cl, ch, centl, centh, plot_idx, state;
	bool operator==( ana_bins a){
		return ((a.pl==pl&&a.ph==ph&&a.cl==cl&&a.ch==ch&&a.state==state) || (a.pl==pl&&a.ph==ph&&a.centl==centl&&a.centh==centh&&a.state==state) );
	};
	bool operator()(ana_bins a, ana_bins b){
		return (a < b);
	};
	bool operator<(const ana_bins& b) const{
		return ( stoi(Form("%d%d%d%d%d", state, pl, ph, centl, centh)) < stoi(Form("%d%d%d%d%d", b.state, b.pl, b.ph, b.centl, b.centh)) );
	};
};
//#endif

double Get_BDT(long ts, ana_bins x, int bdtptMin, int bdtptMax, double vcut =0.00, double rap =2.4, int signif_ =2, string opt_ = ""){
  return Get_BDT(ts, x.state, bdtptMin, bdtptMax, x.pl, x.ph, x.cl, x.ch, vcut, rap, signif_, opt_);
};
double Get_BDT(long ts, ana_bins x, string opt_= "", double vcut =0.00, double rap =2.4, int signif_ =2){
  return Get_BDT(ts, x.state, x.bpl, x.bph, x.pl, x.ph, x.cl, x.ch, vcut, rap, signif_, opt_);
};

std::map<std::string, std::vector<ana_bins> > ana_bm ={
	{"2c", 	{
		{"i", 0, 30, 0, 30, 0, 181, 0, 90, 9, 2},
		{"c", 0, 30, 0, 30,  0, 20, 0, 10, 8, 2},
		{"c", 0, 30, 0, 30, 20, 40, 10, 20, 7, 2},
		{"c", 0, 30, 0, 30, 40, 60, 20, 30, 6, 2},
		{"c", 0, 30, 0, 30, 60, 80, 30, 40, 5, 2},
		{"c", 0, 30, 0, 30, 80, 100, 40, 50, 4, 2},
		{"c", 0, 30, 0, 30, 100, 120, 50, 60, 3, 2},
		{"c", 0, 30, 0, 30, 120, 140, 60, 70, 2, 2},
		{"c", 0, 30, 0, 30, 140, 181, 70, 90, 1, 2},
		}
	},
	{"3c", 	{
		{"i", 0, 30, 0, 30, 0, 181, 0, 90, 8, 3},
		{"c", 0, 30, 0, 30,  0, 20, 0, 10, 7, 3},
		{"c", 0, 30, 0, 30, 20, 40, 10, 20, 6, 3},
		{"c", 0, 30, 0, 30, 40, 60, 20, 30, 5, 3},
		{"c", 0, 30, 0, 30, 60, 80, 30, 40, 4, 3},
		{"c", 0, 30, 0, 30, 80, 100, 40, 50, 3, 3},
		{"c", 0, 30, 0, 30, 100, 140, 50, 70, 2, 3},
		{"c", 0, 30, 0, 30, 140, 181, 70, 90, 1, 3},
		}
	},
	{"2p", 	{
		{"p", 0, 3, 0, 3,  0, 181, 0, 90, 1, 2},
		{"p", 3, 6, 3, 6,  0, 181, 0, 90, 2, 2},
		{"p", 6, 9, 6, 9,  0, 181, 0, 90, 3, 2},
		{"p", 9, 12, 9, 12,  0, 181, 0, 90, 4, 2},
		{"p", 12, 15, 12, 15,  0, 181, 0, 90, 5, 2},
		{"p", 15, 30, 15, 30,  0, 181, 0, 90, 6, 2},
		}
	},
	{"3p", 	{
		{"p", 0, 4, 0, 4,  0, 181, 0, 90, 1, 3},
		{"p", 4, 9, 4, 9,  0, 181, 0, 90, 2, 3},
		{"p", 9, 15, 9, 15,  0, 181, 0, 90, 3, 3},
		{"p", 15, 30, 15, 30,  0, 181, 0, 90, 4, 3},
		}
	},

};

std::string findtype(ana_bins x){
	std::string fittype = "";
	if(x.cl ==0 && x.ch ==181) fittype = "GC";
	else fittype = "FF";
	return fittype;
}
std::pair<int, int> gettrainpt(int pl, int ph){
//	if(pl <= ph)	{
//		if(pl >=0 && ph <=4) return {0,4};
//		else if(pl >=4 && ph <=9) return {4,9};
//		else if(pl >=9 && ph <=12) return {9, 12};
//		else if(pl >=12 && ph <=30) return {12, 30};
//		else if(pl >=12 && ph>30 && ph <=50) return {12, 50};
//		else return {-1, -1};
//	}
//	else return {-1, -1};
	return {-1, -1};
};

std::vector<std::pair<int, int> >bin1spt = {{0,30},{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,8},{8,10},{10,12},{18,30},{12,18},{12,15},{15,30}};
std::vector<std::pair<int, int> >bin2spt = {{0,4},{4,9},{12,30},{0,30},{0,2},{2,4},{4,6},{6,9},{9,12},{12,15},{15,20},{12,20},{12,24},{20,50},{24,50},{30,50},{12,50}, {15, 50}};
std::vector<std::pair<int, int> >bin3spt = {{0,6}, {6,30}, {0,30},{0,4},{4,9},{9,12},{12,15},{15,50},{12,24},{24,50},{12,20},{20,50},{12,30},{30,50},{15,30}};

std::vector<double> VALI_V3_BDTTESTCUT = {0.8, 0.7, 0.5, 0.1, -0.1};
std::vector<double> VALI_V3_BDTTESTCUT2 = {0.0, 0.1, 0.2, 0.25, 0.3, 0.35, 0.4, 0.7};
std::vector<double> VALI_V3_BDTTESTCUT3 = {0.25, 0.2, 0.15, 0.1, 0.05, -0.1, -0.2};
std::vector<double> NOM_V2_BDTTESTCUT = {-0.9, -0.8, -0.7, -0.4, -0.3, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5};



#include "yield_eff_signif.h"
#endif
