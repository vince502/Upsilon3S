#ifndef BININFO_H
#define BININFO_H
#include <vector>
#include <map>
#include "../.workdir.h"
#include "../fitter.h"
#include "yield_eff_signif.h"
static TH1D* Get_Optimal_BDT_HIST; 
const double interval_score = 0.1;

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

  std::fstream input;
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
	input.open(Form("%s/BDT/BDT_description.log",workdir.Data()));
	std::map<long, std::string> dictmap;
	std::string stringbuf;
	while (input.peek() != EOF){
	  std::getline(input, stringbuf);
	  long inputts;
	  try{
	    stol( stringbuf.substr(0,10));
	    inputts = stol(stringbuf.substr(0,10));
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
	try{
	  return parser_symbol(dictmap[ts], "::");
	}
	catch(...){
	  std::vector<std::string> null_pair = {{""}};
	  return null_pair;
	}

};

std::pair<double,double> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, double ratio =0.16, string name_input_opt = "", string formula_significance= "S12");

RooRealVar get_eff_acc(std::string type, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int state1 =1, int state2 = 3);

TH1D* func_hist_optimal_BDT();

#endif
