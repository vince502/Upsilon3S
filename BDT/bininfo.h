#ifndef BININFO_H
#define BININFO_H
#include <vector>
#include <map>
#include "../tdrstyle.C"
#include "../CMS_lumi_square.C"
#include "../.workdir.h"
#include "../fitter.h"
#include "yield_eff_signif.h"
static TH1D* Get_Optimal_BDT_HIST; 
const double interval_score = 0.05;

std::string MuIDHybridSoft2018 = "nPixWMea1>0&&nPixWMea2>0&&nTrkWMea1>5&&nTrkWMea2>5&&fabs(dxy1)<0.3&&fabs(dxy2)<0.3&&fabs(dz1)<20&&fabs(dz2)<20";

std::map<long, std::map<int, std::vector<std::pair<double,double> > > >bdtbinsec =
{
	{1618900984, 
		{
			{ 3, {{-1.0, -0},{0, 0.34},{0.34, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.2},{0.2, 0.34},{0.34, 1.0}}
			}
		}
	},
	{1619007178, 
		{
			{ 3, {{-1.0, -0},{0, 0.3},{0.3, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.2},{0.2, 0.3},{0.3, 1.0}}
			}
		}
	},
	{1619021800, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1618912058, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1618913300, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1620628282, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1620630542, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1620631235, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1621568219, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1621564724, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1622517421, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1621574030, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1621570122, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
	{1621574976, 
		{
			{ 3, {{-1.0, -0},{0, 0.2},{0.2, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.1},{0.1, 0.2},{0.2, 1.0}}
			}
		}
	},
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
	{1618913300, {8, 11.5} },
	{1618930830, {8, 11.5} },
	{1618912058, {8, 11.5} },
	{1618913300, {8, 11.5} },
	{1619007268, {8, 11.5} },
	{1619021800, {8, 11.5} },
	{1619742556, {8, 11.5} },
	{1619743777, {8, 11.0} },
	{1620628282, {8, 11.0} },
	{1619007178, {8, 11.5} },
	{1621564724, {8, 11.5} },
	{1621570122, {8, 11.5} },
	{1621574030, {8, 11.5} },
	{1621574976, {8, 11.5} },
	{1621568219, {8, 11.5} },
	{1620631235, {8, 11.5} },
	{1622517421, {8, 11.5} },
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
double Get_BDT(long ts, int state, int ptMin, int ptMax, int cBinLow, int cBinHigh, double vcut =0.00, double rap = 2.4, int signif_ = 2){
  string name_file = Form("%s/BDT/Significance_hist/HIST_train%dS_%ld_pt_%d-%d_rap_-%d-%d_cbin_%d-%d_vp_%.4f_S%d.root", workdir.Data(), state, ts, ptMin, ptMax, (int) (rap*10), (int) (rap*10), cBinLow, cBinHigh, vcut, signif_);
  TFile* input_file = TFile::Open(name_file.c_str());
  TNamed* key = (TNamed*) input_file->Get("latest");
  input_file->Close();
  return stod(key->GetTitle());
}

std::pair<double,TH1D*> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, double ratio =0.16, int train_state =3, string name_input_opt = "", string formula_significance= "S2", string the_opt ="", bool save = true);
std::pair<double,TH1D*> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, RooRealVar r_ratio, int train_state =3, string name_input_opt = "", string formula_significance= "S2");

RooRealVar get_eff_acc(std::string type, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int state1 =1, int state2 = 3, bool eff_old = false);

TH1D* func_hist_optimal_BDT();

//#if !defined(YIELD_EFF_SIGNIF_H)
struct ana_bins{
  int pl, ph, cl, ch, state;
};
//#endif

std::map<std::string, std::vector<ana_bins> > ana_bm ={
	{"2c", 	{
		{0, 30,  0, 10, 2},
		{0, 30, 10, 20, 2},
		{0, 30, 20, 40, 2},
		{0, 30, 40, 60, 2},
		{0, 30, 60, 80, 2},
		{0, 30, 80, 100, 2},
		{0, 30, 100, 120, 2},
		{0, 30, 120, 140, 2},
		{0, 30, 140, 181, 2},
		{0, 30, 0, 181, 2},
		}
	},
	{"3c", 	{
		{0, 30,  0, 40, 3},
		{0, 30, 40, 100, 3},
		{0, 30, 100, 181, 3},
		{0, 30, 0, 181, 3},
		}
	},
	{"2p", 	{
		{0, 4,  0, 181, 2},
		{4, 9,  0, 181, 2},
		{9, 30,  0, 181, 2},
		}
	},
	{"3p", 	{
		{0, 6,  0, 181, 3},
		{6, 30,  0, 181, 3},
		}
	},

};

std::string findtype(ana_bins x){
	std::string fittype = "";
	if(x.cl ==0 && x.ch ==181) fittype = "GC";
	else fittype = "FF";
	return fittype;
}


#endif
