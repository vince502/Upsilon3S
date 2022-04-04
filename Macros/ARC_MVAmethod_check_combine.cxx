#include "../BDT/bininfo.h"
#define _TS 1
int getNomBkgO(ana_bins ab){return 0;}
#include "../plots/measurement.cxx"

void ARC_MVAmethod_check_combine(){
	TFile* f1s = TFile::Open("corryield_1S.root");
	TFile* f2s = TFile::Open("corryield_2S.root");
	TFile* f3s = TFile::Open("corryield_3S.root");

	std::vector<TGraphAsymmErrors*> g1s;
	std::vector<TGraphAsymmErrors*> g2s;
	std::vector<TGraphAsymmErrors*> g3s;
	auto attach_g =[&f1s, &f2s, &f3s](TFile* f, std::vector<TGraphAsymmErrors*> &x, int ds){
		for(auto idx : ROOT::TSeqI(13) ){
			x.push_back((TGraphAsymmErrors*) f->Get(Form("%dS_g%d",ds,idx+1))); 
		}
	};
	attach_g(f1s, g1s, 1);
	attach_g(f2s, g2s, 2);
	attach_g(f3s, g3s, 3);


	TCanvas* c1 = new TCanvas("c1","",800, 600);
	c1->cd();
	TLegend* leg = new TLegend(0.5,0.25,0.90,0.75);
	leg->SetHeader("Left to right #rightarrow descending order");
	leg->AddEntry(g1s[0], "nominal train, dataset1 blind", "pe");
	leg->AddEntry(g1s[1], "nominal train, dataset2 blind", "pe");
	leg->AddEntry(g1s[2], "nominal train, dataset3 blind", "pe");
	leg->AddEntry(g1s[3], "nominal train, dataset4 blind", "pe");
	leg->AddEntry(g1s[4], "nominal train, Full data", "pe");
	leg->AddEntry(g1s[5], "alterante train, nominal BDT, dataset1 blind", "pe");
	leg->AddEntry(g1s[6], "alterante train, nominal BDT, dataset2 blind", "pe");
	leg->AddEntry(g1s[7], "alterante train, nominal BDT, Full", "pe");
	leg->AddEntry(g1s[8], "no BDT, dataset1 blind", "pe");
	leg->AddEntry(g1s[9],"no BDT, dataset2 blind", "pe");
	leg->AddEntry(g1s[10],"no BDT, dataset3 blind", "pe");
	leg->AddEntry(g1s[11],"no BDT, dataset4 blind", "pe");
	leg->AddEntry(g1s[12],"no BDT, Full", "pe");
	leg->SetBorderSize(0);

	TLegend* leg2 = new TLegend(0.5,0.12,0.90,0.22);
	leg2->AddEntry(g1s[0], "#Upsilon(1S)", "p");
	leg2->AddEntry(g2s[0], "#Upsilon(2S)", "p");
	leg2->AddEntry(g3s[0], "#Upsilon(3S)", "p");
	leg2->SetBorderSize(0);

	TLine* line_cut = new TLine();
	line_cut->SetLineWidth(2);
	line_cut->SetLineColor(kBlack);
	line_cut->SetLineStyle(2);

	double val_g1s_ref =  g1s[4]->GetPointY(0) / 4;
	double val_g2s_ref =  g2s[4]->GetPointY(0) / 3;
	double val_g3s_ref =  g3s[4]->GetPointY(0) / 1;

	g1s[0]->SetMarkerStyle(kFullCircle);
	g1s[0]->SetMarkerSize(g1s[0]->GetMarkerSize()*1.5);
	g1s[0]->SetPointY(0, g1s[0]->GetPointY(0) / val_g1s_ref);
	g1s[0]->SetPointEYhigh(0, g1s[0]->GetErrorYhigh(0) / val_g1s_ref);
	g1s[0]-> SetPointEYlow(0, g1s[0]->GetErrorYlow(0) / val_g1s_ref);
	g1s[0]->GetXaxis()->	SetLimits(0, 5.1);
	g1s[0]->GetXaxis()->SetRangeUser( 0, 5.1);
	g1s[0]->GetYaxis()->	SetLimits(-1, 5);
	g1s[0]->GetYaxis()->SetRangeUser( -1, 5);

	g1s[0]->Draw("APE");
	line_cut->DrawLine(0.925, -1, 0.925, 5);
	line_cut->DrawLine(1.475, -1, 1.475, 5);
	line_cut->DrawLine(2.425, -1, 2.425, 5);

	line_cut->DrawLine(0, 1, 2.425, 1);
	line_cut->DrawLine(0, 3, 2.425, 3);
	line_cut->DrawLine(0, 4, 5.1, 4);

	line_cut->SetLineColorAlpha(kRed +1, 0.7);
	line_cut->DrawLine(0.8, -1, 0.8, 5);

	for(auto g : g1s){
		if( g->IsEqual(g1s[0]) ) {std::cout << "g1" << std::endl; continue;}
		g->SetMarkerStyle(kFullCircle);
		g->SetMarkerSize(g->GetMarkerSize()*1.5);
		g->SetPointY(0, g->GetPointY(0) / val_g1s_ref);
		g->SetPointEYhigh(0, g->GetErrorYhigh(0) / val_g1s_ref);
		g-> SetPointEYlow(0, g->GetErrorYlow(0) / val_g1s_ref);
		g->Draw("PE");
	}
	for(auto g : g2s){
		g->SetMarkerStyle(kFullSquare);
		g->SetMarkerSize(g->GetMarkerSize()*1.5);
		g->SetPointY(0, g->GetPointY(0) / val_g2s_ref);
		g->SetPointEYhigh(0, g->GetErrorYhigh(0) / val_g2s_ref);
		g-> SetPointEYlow(0, g->GetErrorYlow(0) / val_g2s_ref);
		g->Draw("PE");
	}
	for(auto g : g3s){
		g->SetMarkerStyle(kFullStar);
		g->SetMarkerSize(g->GetMarkerSize()*1.5);
		g->SetPointY(0, g->GetPointY(0) / val_g3s_ref);
		g->SetPointEYhigh(0, g->GetErrorYhigh(0) / val_g3s_ref);
		g-> SetPointEYlow(0, g->GetErrorYlow(0) / val_g3s_ref);
		g->Draw("PE");
	}


	leg->Draw();
	leg2->Draw();
	c1->SaveAs("~/Upsilon3S/checkout/raw_yield_corr_combine.png");
	c1->SaveAs("~/Upsilon3S/checkout/raw_yield_corr_combine.pdf");
}
