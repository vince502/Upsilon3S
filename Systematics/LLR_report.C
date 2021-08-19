#include "LLR_bkgPDF.cxx"
#include <fstream>

std::string findtype(int pl, int ph, int cl, int ch, int ccorder);
void LLR_report()
{
  	long ts = 9999999999;
	ofstream report;
	report.open("LLR_Result_UPSILON_ChebyChev_poly.txt", std::ios_base::out);
	report << "Likelihood Ratio test for Upsilon 2S and 3S for ChevyChev Background PDF ordrering" << std::endl;
	int table_cent_2S[10] = {0, 10, 20, 40, 60, 80, 100, 120, 140, 181};
	int table_cent_3S[4] = {0, 40, 100, 181};
	int table_pt_2S[4] = {0, 4, 9, 30};
	int table_pt_3S[3] = {0, 6, 30};

	int pl, ph, cl, ch;
	double pvalue;
	double pvalue_t[10];
	auto run_report = [&] (int state) {
		vector<int> N1over= {};
		vector<int> N2over= {};
		vector<int> N3over= {};
		vector<int> N4over= {};//only one element N=5;
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,1), findtype(pl,ph,cl,ch,2), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[0] = pvalue;
		report << Form("p(H0: N=1), 2 : %2.2f %% \n", pvalue * 100); 
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,1), findtype(pl,ph,cl,ch,3), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[1] = pvalue;
		report << Form("p(H0: N=1), 3: %2.2f %% \n", pvalue * 100); 
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,1), findtype(pl,ph,cl,ch,4), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[2] = pvalue;
		report << Form("p(H0: N=1), 4: %2.2f %% \n", pvalue * 100); 
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,1), findtype(pl,ph,cl,ch,5), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[3] = pvalue;
		report << Form("p(H0: N=1), 5: %2.2f %% \n", pvalue * 100); 
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,2), findtype(pl,ph,cl,ch,3), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[4] = pvalue;
		report << Form("p(H0: N=2), 3 : %2.2f %% \n", pvalue * 100); 
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,2), findtype(pl,ph,cl,ch,4), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[5] = pvalue;
		report << Form("p(H0: N=2), 4 : %2.2f %% \n", pvalue * 100); 
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,2), findtype(pl,ph,cl,ch,5), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[6] = pvalue;
		report << Form("p(H0: N=2), 5 : %2.2f %% \n", pvalue * 100); 
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,3), findtype(pl,ph,cl,ch,4), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[7] = pvalue;
		report << Form("p(H0: N=3), 4 : %2.2f %% \n", pvalue * 100); 
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,3), findtype(pl,ph,cl,ch,5), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[8] = pvalue;
		report << Form("p(H0: N=3), 5 : %2.2f %% \n", pvalue * 100); 
		pvalue = LLR_bkgPDF(findtype(pl,ph,cl,ch,4), findtype(pl,ph,cl,ch,5), ts, (double) pl, (double) ph, cl, ch, state);
		pvalue_t[9] = pvalue;
		report << Form("p(H0: N=4), 5 : %2.2f %% \n", pvalue * 100); 
		for(int idx = 0; idx <4; idx++){
			if (pvalue_t[idx]<0.05) N1over.push_back(idx+2);
		}
		for(int idx = 4; idx <7; idx++){
			if (pvalue_t[idx]<0.05) N2over.push_back(idx-1);
		}
		for(int idx = 5; idx <9; idx++){
			if (pvalue_t[idx]<0.05) N3over.push_back(idx-1);
		}
		if (pvalue_t[9]<0.05) N4over.push_back(5);

	  
	};
	
	report << "===================================== \n";
	report << "LLR test for 2S \n";
	report << "===================================== \n\n";
	for(int idx =0; idx<9; idx++){
	  	report << "Centrality Bins, fit with FF \n";
		cl = table_cent_2S[idx];
		ch = table_cent_2S[idx+1];
		pl = 0;
		ph = 30;
		report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", cl, ch, pl, ph) ;
		run_report(2);
		report << "\n";
	}
	report << "===================================== \n";
	for(int idx =0; idx<3; idx++){
	  	report << "pT Bins, fit with GC \n";
		pl = table_pt_2S[idx];
		ph = table_pt_2S[idx+1];
		cl = 0;
		ch = 181;
		report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", cl, ch, pl, ph) ;
		run_report(2);
		report << "\n";
	}
	report << "===================================== \n";
	report << "Integrated Bin, fit with GC \n";
	cl =0;
	ch = 181;
	pl = 0 ;
	ph = 30;
	report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", cl, ch, pl, ph) ;
	run_report(2);
	report << "\n\n===================================== \n";

	report << "LLR test for 3S \n";
	report << "===================================== \n\n";
	for(int idx =0; idx<3; idx++){
	  	report << "Centrality Bins, fit with FF \n";
		cl = table_cent_3S[idx];
		ch = table_cent_3S[idx+1];
		pl = 0;
		ph = 30;
		report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c\n", cl, ch, pl, ph) ;
		run_report(3);
		report << "\n";
	}
	report << "===================================== \n";
	for(int idx =0; idx<2; idx++){
	  	report << "pT Bins, fit with GC \n";
		pl = table_pt_3S[idx];
		ph = table_pt_3S[idx+1];
		cl = 0;
		ch = 181;
		report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", cl, ch, pl, ph) ;
		run_report(3);
		report << "\n";
	}
	report << "===================================== \n";
	report << "Integrated Bin, fit with GC \n";
	cl =0;
	ch = 181;
	pl = 0 ;
	ph = 30;
	report << Form("cBin %d ~ %d, pT %d ~ %d GeV/c \n", cl, ch, pl, ph) ;
	run_report(3);
	report << "===================================== ";
	report.close();
		
		
};

std::string findtype(int pl, int ph, int cl, int ch, int ccorder){
	std::string base = "CB3:CC";
	std::string fittype = "";
	if( cl ==0 && ch == 181) fittype = "GC";
	else fittype = "FF";
	return Form("%s%d:%s", base.c_str(), ccorder, fittype.c_str());
};
