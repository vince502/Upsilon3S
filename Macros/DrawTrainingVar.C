#include "../.workdir.h"

void DrawTrainingVar(long ts = 10000000016){

	auto fbdt = TFile::Open(Form("%s/BDT/BDTResult/BDTresultY3S_%ld_BLIND.root", workdir.Data(), ts));
	std::map< string, TH1F* > histS;
	std::map< string, TH1F* > histB;
	string _hist_dir1 = "data/Y3Spt0to30/dataset1";
	string _hist_dir2 = "data/Y3Spt0to30/dataset2";
	string input_trans = "InputVariables_Gauss_Deco";
	string name_hist = "";
	for ( auto var : {"ctau3D", "ctau", "QQVtxProb", "QQdca", "cosAlpha", "cosAlpha3D"} ){		
		string name_histS1 = Form("%s/%s/%s__Signal_Gauss_Deco", _hist_dir1.c_str(), input_trans.c_str(), var);
		string name_histB1 = Form("%s/%s/%s__Background_Gauss_Deco", _hist_dir1.c_str(), input_trans.c_str(), var);
		string name_histS2 = Form("%s/%s/%s__Signal_Gauss_Deco", _hist_dir2.c_str(), input_trans.c_str(), var);
		string name_histB2 = Form("%s/%s/%s__Background_Gauss_Deco", _hist_dir2.c_str(), input_trans.c_str(), var);
		TH1F* histS1 = (TH1F*) fbdt->Get(name_histS1.c_str());
		histS1->Scale(1/histS1->GetSum());
		histS1->SetStats(0);
		histS1->SetMarkerStyle(kFullCircle);
		histS1->SetMarkerColor(kBlue);
		histS1->SetLineColor(kBlue);
		TH1F* histB1 = (TH1F*) fbdt->Get(name_histB1.c_str());
		histB1->Scale(1/histB1->GetSum());
		histB1->SetStats(0);
		histB1->SetMarkerStyle(kFullSquare);
		histB1->SetMarkerColor(kRed);
		histB1->SetLineColor(kRed);
		TH1F* histS2 = (TH1F*) fbdt->Get(name_histS2.c_str());
		TH1F* histB2 = (TH1F*) fbdt->Get(name_histB2.c_str());


		histS.emplace( var, histS1);
		histB.emplace( var, histB1);
	}
	TCanvas* c1 = new TCanvas("c1", "", 1600,1800);
	c1->Divide(2,3);
//	TPad* p11 = new TPad("p11", "", 0, 0, 0.5, 1);
//	TPad* p12 = new TPad("p12", "", 0, 0, 0.5, 1);
	int idx = 1;
	TLegend* leg = new TLegend(0.7,0.65,0.85,0.85);
	leg->AddEntry(histS["QQdca"], "MC", "ple");
	leg->AddEntry(histB["QQdca"], "data", "ple");
	for ( const auto var : {"ctau3D", "ctau", "QQVtxProb", "QQdca", "cosAlpha", "cosAlpha3D"} ){
		c1->cd(idx);

		histS[var]->Draw("pe");
		histB[var]->Draw("same");


		leg->Draw();
		idx++;

	}
	c1->Draw();

}
