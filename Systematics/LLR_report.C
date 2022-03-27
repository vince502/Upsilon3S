#include "../BDT/bininfo.h"

#define UB true

//#define _TS_LLRINTERNAL 100019111111
#define _TS_LLRINTERNAL 200019111111
//#define _TS_LLRINTERNAL 9999999999
#if _TS_LLRINTERNAL != 9999999999 && UB == false
#	define ana_bm ana_bm_comb
#endif

#if _TS_LLRINTERNAL != 9999999999 && UB == true
#	define ana_bm ana_bm_comb_ub
#endif

#include "LLR_bkgPDF.cxx"
#include <fstream>

bool vecfind(std::vector<int> v_, int t){
	return (bool) (std::find(v_.begin(), v_.end(), t) !=v_.end());
};

std::string findtype(int pl, int ph, int cl, int ch, int ccorder);
std::string findtype(ana_bins x, int ccorder);
void LLR_report()
{
  	long ts = _TS_LLRINTERNAL;
	ofstream report, value_header, texout;
	report.open(Form("LLR_Result_UPSILON_ChebyChev_poly_%ld.txt", ts), std::ios_base::out);
	report << "Likelihood Ratio test for Upsilon 2S and 3S for ChevyChev Background PDF ordrering" << std::endl;
	value_header.open(Form("../LLR_CCorder_%ld.h",ts), std::ios_base::out);
	value_header << "#pragma once\n#include\"./BDT/bininfo.h\"\n#include <map>\n#define GETBKGO\nint getNomBkgO_"<< ts<<"(int state, int pl, int ph, int cl, int ch)\n{\n";
	texout.open(Form("LLR_result_%ld.tex",ts));
	texout << "\\subsection{Likelihood-ratio test}\n";

	int pl, ph, cl, ch, centl, centh;
	ana_bins ab;
	double pvalue;
	double pvalue_t[7][7] = {{0}};
	auto run_report = [&] (int state) {
		pl = ab.pl;
		ph = ab.ph;
		cl = ab.cl;
		ch = ab.ch;
		centl = ab.centl;
		centh = ab.centh;
		string stringdump_head, stringdump_body;

	  	pvalue = 1;
		vector<int> N1over= {};
		vector<int> N2over= {};
		vector<int> N3over= {};
		vector<int> N4over= {};;
		vector<int> N5over= {};//only one element N=6;
		std::pair<double, std::pair<double, double> > reg;
		double NLLs[6] = {0,0,0,0,0,0};
		reg = LLR_bkgPDF(findtype(ab,1), findtype(ab,2), ts, ab);
		pvalue_t[1][2] = reg.first;
		NLLs[0] = reg.second.first;
		NLLs[1] = reg.second.second;
		std::cout << Form("NLL : %f", NLLs[0]) << std::endl;
		report << Form("p(H0: N=1), 2 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,1), findtype(ab,3), ts, ab);
		pvalue_t[1][3] = reg.first;
		NLLs[2] = reg.second.second;

		std::cout << Form("NLL : %f", NLLs[1]) << std::endl;
		report << Form("p(H0: N=1), 3: %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,1), findtype(ab,4), ts, ab);
		pvalue_t[1][4] = reg.first;
		NLLs[3] = reg.second.second;

		std::cout << Form("NLL : %f", NLLs[2]) << std::endl;
		report << Form("p(H0: N=1), 4: %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,1), findtype(ab,5), ts, ab);
		pvalue_t[1][5] = reg.first;
		NLLs[4] = reg.second.second;

		std::cout << Form("NLL : %f", NLLs[3]) << std::endl;
		report << Form("p(H0: N=1), 5: %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,1), findtype(ab,6), ts, ab);
		pvalue_t[1][6] = reg.first;
		NLLs[5] = reg.second.second;
		std::cout << Form("NLL : %f", NLLs[4]) << std::endl;
		std::cout << Form("NLL : %f", NLLs[5]) << std::endl;
		report << Form("p(H0: N=1), 6: %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,2), findtype(ab,3), ts, ab);
		pvalue_t[2][3] = reg.first;
		report << Form("p(H0: N=2), 3 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,2), findtype(ab,4), ts, ab);
		pvalue_t[2][4] = reg.first;
		report << Form("p(H0: N=2), 4 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,2), findtype(ab,5), ts, ab);
		pvalue_t[2][5] = reg.first;
		report << Form("p(H0: N=2), 5 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,2), findtype(ab,6), ts, ab);
		pvalue_t[2][6] = reg.first;
		report << Form("p(H0: N=2), 6 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,3), findtype(ab,4), ts, ab);
		pvalue_t[3][4] = reg.first;
		report << Form("p(H0: N=3), 4 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,3), findtype(ab,5), ts, ab);
		pvalue_t[3][5] = reg.first;
		report << Form("p(H0: N=3), 5 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,3), findtype(ab,6), ts, ab);
		pvalue_t[3][6] = reg.first;
		report << Form("p(H0: N=3), 6 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,4), findtype(ab,5), ts, ab);
		pvalue_t[4][5] = reg.first;
		report << Form("p(H0: N=4), 5 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,4), findtype(ab,6), ts, ab);
		pvalue_t[4][6] = reg.first;
		report << Form("p(H0: N=4), 6 : %2.2f %% \n", reg.first * 100); 
		std::cout << "\n P-Value(%) : " << reg.first << "\n\n";
		reg = LLR_bkgPDF(findtype(ab,5), findtype(ab,6), ts, ab);
		pvalue_t[5][6] = reg.first;
		report << Form("p(H0: N=5), 6 : %2.2f %% \n", reg.first * 100); 
		auto eligible = [&] (int st1, int st2) {
			int large = std::max(st1, st2);
			int small = std::min(st1, st2);
			if(pvalue_t[small][large] > 0.05) return small;
			if(pvalue_t[small][large] <= 0.05) return large;
			else return -1;
		};
	 	int selected_deg =0;
		for(int idx1 =1; idx1 < 6; idx1++){
			if(idx1 ==1) continue;
			if(eligible(1,idx1) != 1) N1over.push_back(idx1);
		}
		if((N1over.empty() || !(vecfind(N1over, 2)|| vecfind(N1over,3) || vecfind(N1over,4)|| vecfind(N1over, 5)))&& selected_deg == 0) selected_deg =1;
		for(int idx1 =1; idx1 < 6; idx1++){
			if(idx1 ==2) continue;
			if(eligible(2,idx1) != 2) N2over.push_back(idx1);
		}
		if((N2over.empty() || !(vecfind(N2over, 3)|| vecfind(N2over,4) || vecfind(N2over,5)))&& selected_deg == 0) selected_deg =2;
		for(int idx1 =1; idx1 < 6; idx1++){
			if(idx1 ==3) continue;
			if(eligible(3,idx1) != 3) N3over.push_back(idx1);
		}
		if((N3over.empty() || !(vecfind(N3over, 4)|| vecfind(N3over,5)))&& selected_deg == 0) selected_deg =3;
		for(int idx1 =1; idx1 < 6; idx1++){
			if(idx1 ==4) continue;
			if(eligible(4,idx1) != 4) N4over.push_back(idx1);
		}
		if((N4over.empty() || !(vecfind(N4over, 5)|| vecfind(N4over,6)))&& selected_deg == 0) selected_deg =4;
		for(int idx1 =1; idx1 < 6; idx1++){
			if(idx1 ==5) continue;
			if(eligible(5,idx1) != 5) N5over.push_back(idx1);
		}
		if((N5over.empty() || !(vecfind(N5over, 6)|| vecfind(N5over,6)))&& selected_deg == 0) selected_deg =5;
		if( selected_deg == 0) selected_deg =6;

	report << Form(" X %d %d %d %d %d \n",(int) (std::find(N1over.begin(), N1over.end(),2)!=N1over.end())*2,(int) (std::find(N1over.begin(), N1over.end(),3)!=N1over.end())*3, (int) (std::find(N1over.begin(), N1over.end(),4)!=N1over.end())*4,(int) (std::find(N1over.begin(), N1over.end(),5)!=N1over.end())*5, (int) (vecfind(N1over, 6)*6));
	report << Form(" X X %d %d %d %d \n",(int) (std::find(N2over.begin(), N2over.end(),3)!=N2over.end())*3,(int) (std::find(N2over.begin(), N2over.end(),4)!=N2over.end())*4,(int) (std::find(N2over.begin(), N2over.end(),5)!=N2over.end())*5, (int) (vecfind(N2over, 6)*6));
	report << Form(" X X X %d %d %d \n",(int) (std::find(N3over.begin(), N3over.end(),4)!=N3over.end())*4, (int) (std::find(N3over.begin(), N3over.end(),5)!=N3over.end())*5, (int) (vecfind(N3over, 6)*6));
	report << Form(" X X X X %d %d \n",(int) (std::find(N4over.begin(), N4over.end(),5)!=N4over.end())*5, (int) (vecfind(N4over, 6)*6));
	report << Form(" X X X X X %d \n",(int) ((int) (vecfind(N5over, 6)*6)));
	report << Form(" X X X X X X \n");
	report << "Selected N = " << selected_deg << "\n\n";
	value_header << Form("	if( (state == %d && pl == %d && ph == %d && cl == %d && ch == %d) ) return %d;\n", state, pl,ph,cl,ch, selected_deg) ;
		string hl_O1, hl_O2, hl_O3, hl_O4, hl_O5;	
		hl_O1 = ""; hl_O2 = ""; hl_O3 = ""; hl_O4 = ""; hl_O5 = "";
		if( selected_deg == 1 ) hl_O1 = ">{\\columncolor[gray]{0.8}}";
		if( selected_deg == 2 ) hl_O2 = ">{\\columncolor[gray]{0.8}}";
		if( selected_deg == 3 ) hl_O3 = ">{\\columncolor[gray]{0.8}}";
		if( selected_deg == 4 ) hl_O4 = ">{\\columncolor[gray]{0.8}}";
		if( selected_deg == 5 ) hl_O5 = ">{\\columncolor[gray]{0.8}}";
		stringdump_head = "\\begin{table}[htb]\n	\\begin{center}\n	\\caption{" + string(Form("Result %dS, Centrality [%d, %d] \\%%, $p_{T}$ [%d, %d] \\GeV\n", state, centl, centh, pl, ph)) + string(Form("}\n{\\footnotesize\\renewcommand{\\arraystretch}{1.4}\n		\\begin{tabular}{cc||%sc%sc%sc%sc}\n			N & NLL & p(H0: N = 1) & p(H0: N = 2) & p(H0: N = 3) & p(H0: N = 4)\\\\ \n		\\hline\n",hl_O1.c_str(), hl_O2.c_str(), hl_O3.c_str(), hl_O4.c_str() ));
	texout << stringdump_head;
	texout << Form(		"1 & %.2f & & & &\\\\\n", NLLs[0]);
	texout << Form(		"2 & %.2f & %.1f\\% & & &\\\\\n", NLLs[1], pvalue_t[1][2]*100);
	texout << Form(		"3 & %.2f & %.1f\\% & %.1f\\% & &\\\\\n", NLLs[2], pvalue_t[1][3]*100, pvalue_t[2][3]*100);
	texout << Form(		"4 & %.2f & %.1f\\% & %.1f\\% & %.1f\\% &\\\\\n", NLLs[3], pvalue_t[1][4]*100, pvalue_t[2][4]*100, pvalue_t[3][4]*100);
	texout << Form(		"5 & %.2f & %.1f\\% & %.1f\\% & %.1f\\% & %.1f\\%\\\\\n", NLLs[4], pvalue_t[1][5]*100, pvalue_t[2][5]*100, pvalue_t[3][5]*100, pvalue_t[4][5]*100);
	texout << Form(		"6 & %.2f & %.1f\\% & %.1f\\% & %.1f\\% & %.1f\\% \\\\\n", NLLs[5], pvalue_t[1][6]*100, pvalue_t[2][6]*100, pvalue_t[3][6]*100, pvalue_t[4][6]*100);
	texout << "	\\end{tabular}\n		\\label{tab:lab}\n	}\n	\\end{center}\\end{table}\n\n";

//		stringdump_head = "\\begin{table}[htb]\n	\\begin{center}\n	\\caption{" + string(Form("Result %dS, Centrality [%d, %d] \\%%, $p_{T}$ [%d, %d] \\GeV\n", state, centl, centh, pl, ph)) + string(Form("}\n{\\footnotesize\\renewcommand{\\arraystretch}{1.4}\n		\\begin{tabular}{cc||%sc%sc%sc%sc%sc}\n			N & NLL & p(H0: N = 1) & p(H0: N = 2) & p(H0: N = 3) & p(H0: N = 4) & p(H0: N = 5)\\\\ \n		\\hline\n",hl_O1.c_str(), hl_O2.c_str(), hl_O3.c_str(), hl_O4.c_str(), hl_O5.c_str() ));
//	texout << stringdump_head;
//	texout << Form(		"1 & %.2f & & & & &\\\\\n", NLLs[0]);
//	texout << Form(		"2 & %.2f & %.1f\\% & & & &\\\\\n", NLLs[1], pvalue_t[1][2]*100);
//	texout << Form(		"3 & %.2f & %.1f\\% & %.1f\\% & & &\\\\\n", NLLs[2], pvalue_t[1][3]*100, pvalue_t[2][3]*100);
//	texout << Form(		"4 & %.2f & %.1f\\% & %.1f\\% & %.1f\\% & &\\\\\n", NLLs[3], pvalue_t[1][4]*100, pvalue_t[2][4]*100, pvalue_t[3][4]*100);
//	texout << Form(		"5 & %.2f & %.1f\\% & %.1f\\% & %.1f\\% & %.1f\\% &\\\\\n", NLLs[4], pvalue_t[1][5]*100, pvalue_t[2][5]*100, pvalue_t[3][5]*100, pvalue_t[4][5]*100);
//	texout << Form(		"6 & %.2f & %.1f\\% & %.1f\\% & %.1f\\% & %.1f\\% & %.1f\\% \\\\\n", NLLs[5], pvalue_t[1][6]*100, pvalue_t[2][6]*100, pvalue_t[3][6]*100, pvalue_t[4][6]*100, pvalue_t[5][6]*100);
//	texout << "	\\end{tabular}\n		\\label{tab:lab}\n	}\n	\\end{center}\\end{table}\n\n";



	};
	
	report << "===================================== \n";
	report << "LLR test for 2S \n";
	report << "===================================== \n\n";
	for( auto x : ana_bm["2c"]){ 
	  	report << "Centrality Bins, fit with FF \n";
		report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", x.cl, x.ch, x.pl, x.ph) ;
		if( strcmp(x.bin_attr.c_str(),"i")==0 ) continue;
		ab = x;
		run_report(2);
		report << "\n";
	}
	report << "===================================== \n";
	for( auto x : ana_bm["2p"]){ 
	  	report << "Centrality Bins, fit with FF \n";
		report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", x.cl, x.ch, x.pl, x.ph) ;
		ab = x;
		run_report(2);
		report << "\n";
	}
	report << "===================================== \n";
	report << "Integrated Bin, fit with GC \n";
	ab = ana_bm["2c"].front();
	report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", ab.cl, ab.ch, ab.pl, ab.ph) ;
	run_report(2);
	report << "\n\n===================================== \n";

	report << "LLR test for 3S \n";
	report << "===================================== \n\n";
	for( auto x : ana_bm["3c"]){ 
	  	report << "Centrality Bins, fit with FF \n";
		report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", x.cl, x.ch, x.pl, x.ph) ;
		if( strcmp(x.bin_attr.c_str(),"i")==0 ) continue;
		ab = x;
		run_report(3);
		report << "\n";
	}
	report << "===================================== \n";
	for( auto x : ana_bm["3p"]){ 
	  	report << "Centrality Bins, fit with FF \n";
		report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", x.cl, x.ch, x.pl, x.ph) ;
		ab = x;
		run_report(3);
		report << "\n";
	}
	report << "===================================== \n";
	report << "Integrated Bin, fit with GC \n";
	ab = ana_bm["3c"].front();
	report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", ab.cl, ab.ch, ab.pl, ab.ph) ;
	run_report(3);
	report << "===================================== ";
	report.close();
	value_header << "	else return -1;\n};\n#ifdef GETBKGO\n#define GETBKGO2\nint getNomBkgO_"<<ts<<"(ana_bins x){\n	return getNomBkgO_"<<ts<<"(x.state, x.pl, x.ph, x.cl, x.ch);\n};\n#endif";
	value_header.close();
	texout.close();
		
};

std::string findtype(int pl, int ph, int cl, int ch, int ccorder){
	std::string base = "CB3:CC";
	std::string fittype = "";
	if( cl ==0 && ch == 181) fittype = "GC";
	else fittype = "FF";
	return Form("%s%d:%s", base.c_str(), ccorder, fittype.c_str());
};
std::string findtype(ana_bins x, int ccorder){
	return findtype(x.pl, x.ph, x.cl, x.ch, ccorder);
}
