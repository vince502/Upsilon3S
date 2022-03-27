#pragma once
#include "bininfo.h" 

std::pair<double, double> BDTtraindiff(
	long ts, double ptMin, double ptMax, double rapMin, double rapMax,
	int cBinLow, int cBinHigh, double cutQVP, double ratio =0.16 , 
	int train_state =3, int sig_state = 2, int bdtptMin =0, int bdtptMax = 30, 
	string name_input_opt = "", string formula_significance= "S2", string the_opt="", bool save = true
){

	//Header
	std::string st_opt;
	if(strcmp(name_input_opt.c_str(),"")!=0) st_opt = "_"+name_input_opt;
	std::string output_fname = Form("%s/BDT/Significance_hist/HIST_train%dS_for%dS_bdtpt_%d_%d_%ld_pt_%d-%d_rap_%d-%d_cbin_%d-%d_vp_%.4f_%s%s", workdir.Data(), train_state, sig_state, bdtptMin, bdtptMax, ts_alias(ts), (int) ptMin, (int) ptMax, (int) (rapMin*10), (int) (rapMax*10), cBinLow, cBinHigh, cutQVP, formula_significance.c_str(), st_opt.c_str() );
	TFile* HISTFILE = nullptr;
	HISTFILE = new TFile(Form("%s.root",output_fname.c_str()), "update" );
	std::cout << static_cast<void*>(HISTFILE) << std::endl;
	
	TList* lok =nullptr;
	lok= HISTFILE->GetListOfKeys();
	if (!(lok->FindObject(Form("r_%.6f", ratio))==nullptr) || !(lok->FindObject(Form("r_%.6f%s", ratio, the_opt.c_str()))==nullptr) ){
		std::cout << "[INFO] Reading From HISTOFILE, key : " << the_opt.c_str() << std::endl;
		string dirname = Form("r_%.6f", ratio);
		if ( the_opt.find("SYS") != std::string::npos) { dirname = dirname+""+ the_opt; }

		std::cout << dirname.c_str() << std::endl;
		TGraph*   theHist1 = (TGraph*) HISTFILE->Get(Form("%s/TR1_HISTO", dirname.c_str()) );
		TGraph*   theHist2 = (TGraph*) HISTFILE->Get(Form("%s/TR2_HISTO", dirname.c_str()) );
		TGraph* cloneHist1 = (TGraph*)  theHist1->Clone();
		TGraph* cloneHist2 = (TGraph*)  theHist2->Clone();
		auto findmax  = [&ts](TGraph* g){
			if(ts_alias(ts) == 100019111111){
				auto res = g->GetFunction("Msignif");
				return std::make_pair(res->GetMaximumX(-0.1, 0.45), res->GetMaximum(-0.1,0.45));
			}
			Double_t x,y;
			Double_t max_x, max_y;
			max_y = -1;
			int npoints = g->GetN();
			for( auto idx : ROOT::TSeqI(npoints)){
				g->GetPoint(idx, x, y);
				if( y > max_y ){
					max_y = y;
					max_x = x;
				}
			}
			double ref_y = TMath::MaxElement(npoints, g->GetY());
			if( fabs( ref_y - max_y ) > 0.001) std::cout << "Max Significance does not match between 2 functions, check if there is any other maxima in the graph" << std::endl;
			return std::pair<double, double>(max_x, max_y);
		};

		auto findres1 = findmax(theHist1);
		auto findres2 = findmax(theHist2);
//		cloneHist->SetDirectory(0);
		HISTFILE->Close();
		return std::make_pair(findres1.first, findres2.first);
	}
	else{
		std::cout << "No hisogram found" << std::endl;
		return std::pair<double, double>(-999,-999);
		
	}
}
