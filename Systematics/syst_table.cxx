#include "../BDT/bininfo.h"
#define _TS 200019111111

void syst_table(){
	TFile* f_syst =  TFile::Open(Form("./data/total_systematics_RAA_%ld.root", _TS) );
	TDirectoryFile* f_hist = (TDirectoryFile*) f_syst->Get("syst_comp");
	
	
	auto getSyst = [&](string crit, int idx){
		std::cout << "CRIT: " << crit.c_str() << std::endl;
		std::vector<double> syst_val;
		for( int i =0 ; i<8; i++){
			syst_val.push_back(100.*((TH1D*) f_hist->Get(Form("h_r%ss_b%d",crit.c_str(),i )))->GetBinContent((idx-1)*8 +i+1));
			std::cout <<  ((TH1D*) f_hist->Get(Form("h_r%ss_b%d",crit.c_str(),i )))->GetTitle() << ": "<<syst_val[i] << std::endl;
		}
		syst_val.push_back( 100.* ((TH1D*) f_hist->Get(Form("hsys_tot_%sS", crit.c_str() )))->GetBinContent(idx));
		return  syst_val;
	};

	ofstream texout;
	texout.open(Form("syst_table_%ld.tex", _TS ));
	texout << Form(" \\begin{table}[htb]\n	\\centering\n	\\begin{tabular}{c||cccccccc|c}\n		Bin	\\\\\\hline\n");
	
	double minsb[9] = {100,100,100,100,100,100,100,100,100};
	double maxsb[9] = {0,0,0,0,0,0,0,0,0};
	double minsc[9] = {100,100,100,100,100,100,100,100,100};
	double maxsc[9] = {0,0,0,0,0,0,0,0,0};
	auto getRow = [&](ana_bins ab){
	  string s_state;
	  if(ab.state == 2) s_state = "b";
	  if(ab.state == 3) s_state = "c";
	  string line = Form("			\\PgU%s, \\pt %d--%d \\GeVc, %d--%d \\%% &" ,s_state.c_str(), ab.pl, ab.ph, ab.centl, ab.centh);
	  if( strcmp(ab.bin_attr.c_str(), "i") == 0 ) ab.bin_attr = "c";
	  auto nums = getSyst(Form("%s%d", ab.bin_attr.c_str(),ab.state) ,ab.plot_idx);
	  if(ab.state ==2){
	 	 for(int j= 0 ; j<9; j++){
	 	 	minsb[j] = std::min(minsb[j], nums[j]);
	  		maxsb[j] = std::max(maxsb[j], nums[j]);
	 	 }
	  }
	  if(ab.state ==3){
	 	 for(int j= 0 ; j<9; j++){
	 	 	minsc[j] = std::min(minsc[j], nums[j]);
	  		maxsc[j] = std::max(maxsc[j], nums[j]);
	 	 }
	  }
	  line = line + Form("%.4f & %.4f & %.4f & %.4f & %.4f & %.4f & %.4f & %.4f & %.4f\\\\\n", nums[0], nums[1], nums[2], nums[3], nums[4], nums[5], nums[6], nums[7], nums[8]  ) ;
	  return line;
	};
	for( auto x : ana_bm_comb ){
		for( auto abx : x.second ){
			texout << getRow(abx);	
		}
	}
	texout << Form("	\\end{tabular}\n\\end{table}") ;
	texout.close();
	std::cout << Form("BDT variation & Acceptance correction & Background PDF variation & Centrality calibration variation & Efficiency correction (d\\pt) & Efficiency correction (T\\&P) & Signal PDF Parameter variation & Signal PDF variation & Total uncertainty") << std::endl;
	std::cout << Form(" %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f", minsb[0], minsb[1], minsb[2], minsb[3], minsb[4], minsb[5], minsb[6], minsb[7], minsb[8]) << std::endl;
	std::cout << Form(" %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f", maxsb[0], maxsb[1], maxsb[2], maxsb[3], maxsb[4], maxsb[5], maxsb[6], maxsb[7], maxsb[8]) << std::endl;
	std::cout << Form("------------------------------------------------------------")<< std::endl;
	std::cout << Form(" %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f", minsc[0], minsc[1], minsc[2], minsc[3], minsc[4], minsc[5], minsc[6], minsc[7], minsc[8]) << std::endl;
	  std::cout << Form(" %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f, %.4f", maxsc[0], maxsc[1], maxsc[2], maxsc[3], maxsc[4], maxsc[5], maxsc[6], maxsc[7], maxsc[8]) << std::endl;
}
