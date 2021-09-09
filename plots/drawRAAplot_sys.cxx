#include "../BDT/bininfo.h"
#include "drawRAAplot.cxx"

void drawRAAplot_sys()
{
  	gStyle->SetErrorX(0.00001);
	gStyle->SetOptStat(kFALSE);
	gStyle->SetOptTitle(kFALSE);
	TFile* f_sys = TFile::Open(Form("%s/Systematics/total_systematic.root", workdir.Data() ));
	TFile* f_craa = TFile::Open(Form("%s/plots/resultRAA_nS_centrality.root", workdir.Data() ));
	TFile* f_praa = TFile::Open(Form("%s/plots/resultRAA_nS_pt.root", workdir.Data() ));

	TCanvas* c2 = new TCanvas("c2","",1000,700);
	TCanvas* c3 = new TCanvas("c3","",1000,700);
	TCanvas* c4 = new TCanvas("c4","",1000,700);

	TPad *p2_1, *p2_2, *p3_1, *p3_2;
	p2_1 = new TPad("p21", "", 0.00, 0,0.83,1);
	p2_1->SetRightMargin(0);
	p2_2 = new TPad("p22", "", 0.83, 0,1,1);
	p2_2->SetLeftMargin(0);
	p3_1 = new TPad("p31", "", 0.00, 0,0.83,1);
	p3_1->SetRightMargin(0);
	p3_2= new TPad("p32", "", 0.83, 0,1,1);
	p3_2->SetLeftMargin(0);
	p2_1->SetTicks();
	p2_2->SetTicks();

	TGraphAsymmErrors* g_y1cent = (TGraphAsymmErrors*) f_craa->Get("RAAcent_1S");

	TH1D* h_y2cent = (TH1D*) f_craa->Get("RAAcent_2S");
	TH1D* h_y3cent = (TH1D*) f_craa->Get("RAAcent_3S");
	TH1D* h_y1int = (TH1D*) f_craa->Get("y1int");
	TH1D* h_y2int = (TH1D*) f_craa->Get("y2int");
	TH1D* h_y3int = (TH1D*) f_craa->Get("y3int");
	TH1D* h_y2pt  = (TH1D*) f_praa->Get("h2pt");
	TH1D* h_y3pt  = (TH1D*) f_praa->Get("h3pt");

	TH1D* he_y2cent = (TH1D*) f_sys->Get("hsys_tot_c2S");
	TH1D* he_y3cent = (TH1D*) f_sys->Get("hsys_tot_c3S");
	TH1D* he_y2pt =   (TH1D*) f_sys->Get("hsys_tot_p2S");
	TH1D* he_y3pt =   (TH1D*) f_sys->Get("hsys_tot_p3S");

	TGraphMultiErrors *ge_y2cent, *ge_y3cent, *ge_y2int, *ge_y3int, *ge_y2pt, *ge_y3pt;
	ge_y2cent = new TGraphMultiErrors(h_y2cent);
	ge_y3cent = new TGraphMultiErrors(h_y3cent);
	ge_y2int = new TGraphMultiErrors(h_y2int);
	ge_y3int = new TGraphMultiErrors(h_y3int);
	ge_y2pt = new TGraphMultiErrors(h_y2pt);
	ge_y3pt = new TGraphMultiErrors(h_y3pt);

	TGraphMultiErrors* tga[6] = {ge_y2cent, ge_y3cent, ge_y2int, ge_y3int, ge_y2pt, ge_y3pt};
	std::vector<int> x;
	std::vector<double> v_err;
	for( auto t : tga){
	 	x={};
		int bins = t->GetN();
		for( int j = 0; j < bins; j++){
			if(t->GetPointY(j) ==0) { x.push_back(j);  }
			else v_err.push_back(t->GetErrorYhigh(j));
		}

		std::vector<int>::reverse_iterator reit;
		for(reit = x.rbegin(); reit != x.rend(); reit++){	
			t->RemovePoint(*reit);
		}
		int count = 0;
		for(auto item : v_err){
		  	std::cout << item << " is item" << std::endl;
			t->SetPointError(count, 3, 3, item, item);
			count++;
		}
		v_err = {};
		std::cout << "----------------" << std::endl;
	}	
	ge_y2int->SetPointEX(0,0.1,0.1);
	ge_y3int->SetPointEX(0,0.1,0.1);

	double *es_c2s = new double[9]; 
	double *es_c3s = new double[3]; 
	double *es_p2s = new double[3]; 
	double *es_p3s = new double[2]; 
	double *es_i2s = new double[1]; 
	double *es_i3s = new double[1];

	for(int i = 0; i<9; i++){
	  	double err_frac = he_y2cent->GetBinContent(i+1);
		double raa = ge_y2cent->GetPointY(i);
		es_c2s[i] = raa*err_frac;
	}
	for(int i = 0; i<3; i++){
	  	double err_frac = he_y3cent->GetBinContent(i+1);
		double raa = ge_y3cent->GetPointY(i);
		es_c3s[i] = raa*err_frac;
	}
	for(int i = 0; i<1; i++){
	  	double err_frac = he_y2cent->GetBinContent(10);
		double raa = ge_y2int->GetPointY(i);
		es_i2s[i] = raa*err_frac;
	}
	for(int i = 0; i<1; i++){
	  	double err_frac = he_y3cent->GetBinContent(4);
		double raa = ge_y3int->GetPointY(i);
		es_i3s[i] = raa*err_frac;
	}
	for(int i = 0; i<3; i++){
	  	double err_frac = he_y2pt->GetBinContent(i+1);
		double raa = ge_y2pt->GetPointY(i);
		es_p2s[i] = raa*err_frac;
	}
	for(int i = 0; i<2; i++){
	  	double err_frac = he_y3pt->GetBinContent(i+1);
		double raa = ge_y3pt->GetPointY(i);
		es_p3s[i] = raa*err_frac;
	}
	
	ge_y2cent ->AddYError(9, es_c2s, es_c2s);
	ge_y3cent ->AddYError(3, es_c3s, es_c3s);
	ge_y2int  ->AddYError(1, es_i2s, es_i2s); 
	ge_y3int  ->AddYError(1, es_i3s, es_i3s); 
	ge_y2pt   ->AddYError(3, es_p2s, es_p2s);
	ge_y3pt   ->AddYError(2, es_p3s, es_p3s); 

	std::cout <<"GET "  <<  ge_y2cent->GetEYhigh(1)[0] <<", "<< ge_y2cent->GetEYhigh(1)[1]<< std::endl ;

	ge_y2cent ->GetAttFill(1)->SetFillStyle(0);
	ge_y3cent ->GetAttFill(1)->SetFillStyle(0);
	ge_y2int  ->GetAttFill(1)->SetFillStyle(0); 
	ge_y3int  ->GetAttFill(1)->SetFillStyle(0); 
	ge_y2pt   ->GetAttFill(1)->SetFillStyle(0);
	ge_y3pt   ->GetAttFill(1)->SetFillStyle(0); 

	ge_y2cent ->SetMarkerSize(0);
	ge_y3cent ->SetMarkerSize(0);
	ge_y2int  ->SetMarkerSize(0); 
	ge_y3int  ->SetMarkerSize(0); 
	ge_y2pt   ->SetMarkerSize(0);
	ge_y3pt   ->SetMarkerSize(0); 

	ge_y2cent ->GetAttLine(1)->SetLineColor(kBlue);
	ge_y3cent ->GetAttLine(1)->SetLineColor(kRed);
	ge_y2int  ->GetAttLine(1)->SetLineColor(kBlue); 
	ge_y3int  ->GetAttLine(1)->SetLineColor(kRed); 
	ge_y2pt   ->GetAttLine(1)->SetLineColor(kRed);
	ge_y3pt   ->GetAttLine(1)->SetLineColor(kRed); 

	ge_y2cent ->GetAttLine(0)->SetLineColor(kBlue);
	ge_y3cent ->GetAttLine(0)->SetLineColor(kRed);
	ge_y2int  ->GetAttLine(0)->SetLineColor(kBlue); 
	ge_y3int  ->GetAttLine(0)->SetLineColor(kRed); 
	ge_y2pt   ->GetAttLine(0)->SetLineColor(kRed);
	ge_y3pt   ->GetAttLine(0)->SetLineColor(kRed); 

	ge_y2cent ->GetAttFill(1)->SetFillColorAlpha(kBlue, 0.1);
	ge_y3cent ->GetAttFill(1)->SetFillColorAlpha(kRed, 0.1);
	ge_y2int  ->GetAttFill(1)->SetFillColorAlpha(kBlue, 0.1); 
	ge_y3int  ->GetAttFill(1)->SetFillColorAlpha(kRed, 0.1); 
	ge_y2pt   ->GetAttFill(1)->SetFillColorAlpha(kRed, 0.1);
	ge_y3pt   ->GetAttFill(1)->SetFillColorAlpha(kRed, 0.1); 

	TLegend* leg = new TLegend(0.65, 0.4, 0.85, 0.7);
	leg->AddEntry(g_y1cent, "#varUpsilon(1S) HIN-16-023", "pl");
	leg->AddEntry(h_y2cent, "#varUpsilon(2S)", "pl");
	leg->AddEntry(h_y3cent, "#varUpsilon(3S)", "pl");
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetTextSize(0.04);
	TLegend* leg2 = new TLegend(0.65, 0.4, 0.85, 0.7);
	leg2->AddEntry(h_y3cent, "#varUpsilon(3S)", "pl");
	leg2->SetBorderSize(0);
	leg2->SetTextFont(42);
	leg2->SetTextSize(0.04);
//	gStyle->SetEndErrorSize(0);

	c2->cd();
	p2_1->Draw();
	p2_2->Draw();

	p2_1->cd();
	TLine* lineone = new TLine();
	lineone->SetLineStyle(kDashed);
	lineone->DrawLineNDC(0, 0.5, 1, 0.5);
	g_y1cent->SetTitle("");

//	g_y1cent->Draw("aps ");
	ge_y2cent->Draw("a p s; ; 5 s=0.3");
	ge_y3cent->Draw("p s ; ;5 s=0.3 same");
	p2_1->Update();



	TLatex* tl = new TLatex();
	tl->SetTextSize(0.04);
	tl->SetTextFont(42);
	tl->SetNDC();
	tl->DrawLatex( 0.2, 0.8,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 0.2, 0.75, "|y| < 2.4");
	tl->DrawLatex( 0.2, 0.7, "p^{#mu}_{T} > 3.5 GeV/c");
	leg->Draw();
	p2_1->Draw();

	p2_2->cd();
	h_y1int->SetStats(0);
	h_y1int->Draw();
	ge_y2int->Draw("p s ; ; 5 same");
	ge_y3int->Draw("p s ; ; 5  same");
	p2_2->Draw();



	CMS_lumi_square(p2_1, 2, 33);
	c2->Modified();
	c2->Update();

	c4->cd();
	ge_y2cent->Draw("a p s; ; 5");
	ge_y3cent->Draw("p s ; ;5 same");
	c4->Modified();


	c3->cd();
	tl->SetTextSize(0.04);
	tl->SetTextFont(42);
	tl->SetNDC();
//	gStyle->SetErrorX(0.);
	
	TLegend* legx = new TLegend(0.65, 0.4, 0.85, 0.7);
	lineone->SetLineStyle(kDashed);
	lineone->DrawLineNDC(0,0.5,1,0.5);
	legx->AddEntry(h_y2pt, "#varUpsilon(2S)", "pl");
	legx->AddEntry(h_y3pt, "#varUpsilon(3S)", "pl");
	legx->SetBorderSize(0);
	legx->SetTextFont(42);
	legx->SetTextSize(0.04);
	ge_y2pt->Draw("a p s; ; 5  ");
	ge_y3pt->Draw(" p s; ; 5  same");
	legx->Draw();
	tl->DrawLatex( 0.2, 0.8,"p^{#mu#mu}_{T} < 30 GeV/c");
	tl->DrawLatex( 0.2, 0.75, "|y| < 2.4");
	tl->DrawLatex( 0.2, 0.7, "p^{#mu}_{T} > 3.5 GeV/c");
	
	
	CMS_lumi_square(c3, 2, 33);
	c3->Modified();
	c3->Update();


	TFile* output = new TFile("resultRAA_nS_centrality_withSystematics.root", "recreate");
	output->cd();
	c2->Write();
	c3->Write();
	c4->Write();
	output->Close();

}
