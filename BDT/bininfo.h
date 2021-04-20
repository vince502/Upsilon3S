#ifndef BININFO_H
#define BININFO_H

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
	{1618900983, 
		{
			{ 3, {{-1.0, -0},{0, 0.34},{0.34, 1.0}}
			},
			{ 5, {{-1.0, -0.2},{-0.2, 0.0},{0.0, 0.2},{0.2, 0.34},{0.34, 1.0}}
			}
		}
	}
};


//STANDARD ID FIT RESULT YIELD, EFFICIENCY MAP
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

#endif
