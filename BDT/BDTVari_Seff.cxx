#pragma once
#include "bininfo.h"

//std::pair<double,TGraph*> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, double ratio =0.16 , int train_state =3, int sig_state = 2, int bdtptMin =0, int bdtptMax = 30, string name_input_opt = "", string formula_significance= "S2", string the_opt="", bool save = true)

std::pair<double, double> BDTVari_Seff(long ts, ana_bins ab, double frac = 0.1){
	double nom_bdt = Get_BDT(ts, ab);
	
	string tag_BLIND = "BLIND";
	std::string name_input = Form("%s/BDT/BDTResult/BDTresultY3S_%ld_%s.root", workdir.Data(), ts, tag_BLIND.c_str());
	
	TFile* f_BDT = TFile::Open(name_input.c_str() );
	string name_h_effS_1 = Form("data/Y%dSpt%dto%d/dataset1/Method_BDT/BDT/MVA_BDT_effS",ab.train_state, ab.bpl, ab.bph);
	string name_h_effS_2 = Form("data/Y%dSpt%dto%d/dataset2/Method_BDT/BDT/MVA_BDT_effS",ab.train_state, ab.bpl, ab.bph);

	TH1D *h_effS_1, *h_effS_2;
    h_effS_1 = (TH1D*) f_BDT->Get(name_h_effS_1.c_str());
    h_effS_2 = (TH1D*) f_BDT->Get(name_h_effS_2.c_str());
	h_effS_1->SetDirectory(0);
	h_effS_2->SetDirectory(0);

	f_BDT->Close();
	
	double nom_eff = (h_effS_1->GetBinContent(h_effS_1->FindBin(nom_bdt) ) + h_effS_2->GetBinContent(h_effS_2->FindBin(nom_bdt) ) )/2.; 

	double bdt_low, bdt_high;

	double sample_rate = 0.1;
	int nPoints_sampled = 0;
	for(int idx =1; idx < h_effS_1->GetNbinsX() +1; idx ++){
		if((idx%(int) (1/sample_rate)==0)){
			nPoints_sampled ++;
			double effS_1 = h_effS_1->GetBinContent(idx);
			double bc_1 = h_effS_1->GetBinCenter(idx);
			double effS_2 = h_effS_2->GetBinContent(idx);
			double bc_2 = h_effS_2->GetBinCenter(idx);
			double avg_eff = (effS_1 + effS_2)/2;
			if( avg_eff > nom_eff + frac ) bdt_low = ( bc_1 + bc_2 )/2. ;
			if( avg_eff > nom_eff - frac ) bdt_high = ( bc_1 + bc_2 )/2. ;
			if( avg_eff < nom_eff - frac -0.05 ) break;
		}
	}


	return std::pair<double, double>(bdt_low, bdt_high);
}
