#include "../fitter.h"
#include "../CMS_lumi_square.h"
#include "../CMS_lumi_square.C"

auto serv= new THttpServer("http:8081");
TCanvas* c1 = new TCanvas("c1", "", 800, 800);

void drawRaa_vs_binding(){
   Int_t palette[5];
   palette[0] = kOrange+7;
   palette[1] = kGreen +3;
   palette[2] = kBlue+2;
   palette[3] = kMagenta+1;
   palette[4] = kRed-3;
   gStyle->SetPalette(5,palette);

	int psize = 5;
	int _markers[10]= {20, 21, 22, 23, 29, 33, 34, 39, 41, 43};
	double _bindingE[] = {2* 1.8648 - 3.686, 2* 5.2797 - 10.355, 2* 5.2797 - 10.023, 2* 1.8648 - 3.096, 2* 5.2797 - 9.460};
	double _raa[] 	  =  {0.193,	0.050, 			0.076, 			0.219, 		0.319, 			0.319};
	double _raa_err[] =  {0.145, 	0.016, 			0.018, 			0.005, 		0.019, 			0.019};
	double _raa_sys1[] = {0.063, 	0.011, 			0.004, 			0.015, 		0.020, 			0.020};
	double _raa_sys2[] = {0.063, 	0.011, 			0.004, 			0.014, 		0.019, 			0.019};
	string _id[] 	  = {"#psi(2S)", "#Upsilon(3S)", "#Upsilon(2S)", "J/#psi#kern[1.2]{  }", "#Upsilon(1S)"};
//	string _id_tag[]  = {"#splitline{1.6 < |y| < 2.4}{3 < p_{T} < 30}", "#splitline{|y| < 2.4}{p_{T} < 30 GeV/c} ", "#splitline{|y| < 2.4}{p_{T} < 30 GeV/c}", "#splitline{|y| < 2.4}{6.5 < p_{T} < 30 GeV/c}", "#splitline{|y| < 2.4}{p_{T} < 30 GeV/c}"};
	string _id_tag[]  = {"1.6 < |#it{y}| < 2.4, 3 < #it{p}_{T} < 30 GeV/c", "|#it{y}| < 2.4, #it{p}_{T} < 30 GeV/c", "|#it{y}| < 2.4, #it{p}_{T} < 30 GeV/c", "|#it{y}| < 2.4, 6.5 < #it{p}_{T} < 30 GeV/c", "|#it{y}| < 2.4, #it{p}_{T} < 30 GeV/c"};
	string _id_cent[] 	  = {"0-20%", "0-30%", "0-5%", "0-5%", "0-5%"};
//	gStyle->SetPalette(kCool);
	gStyle->SetEndErrorSize(0);
	gStyle->SetNumberContours(psize);

	TLatex* tl = new TLatex();
	tl->SetTextFont(42);
	tl->SetTextSize(0.024);
	tl->SetTextAlign(11);
	auto set_graph = [&](TGraphAsymmErrors* g, int idx){
		g->AddPoint(_bindingE[idx], _raa[idx]);
		g->SetPointError(0, 0, 0, _raa_err[idx], _raa_err[idx]);
		g->SetMarkerSize(2.00);
		g->SetMarkerColor(gStyle->GetColorPalette((255/ psize) * idx + 10 ));
		g->SetLineColor(gStyle->GetColorPalette((255/ psize) * idx +10 ));
		g->SetMarkerStyle(_markers[idx]);
		g->SetFillColorAlpha(gStyle->GetColorPalette((255/ psize) * idx + 10 + 5 ), 0.2);
		g->SetDrawOption("PE PMC");
		tl->DrawLatex(_bindingE[idx] -0.01 , _raa[idx] + _raa_err[idx]+ 0.03, _id[idx].c_str() );
	};
	auto set_graph_syst = [&](TGraphAsymmErrors* g, int idx){
		g->AddPoint(_bindingE[idx], _raa[idx]);
		g->SetPointError(0, 0.015, 0.015, _raa_sys1[idx], _raa_sys2[idx]);
		g->SetMarkerSize(2.25);
		g->SetLineColor(gStyle->GetColorPalette((255/ psize) * idx ));
		g->SetLineWidth(1);
		g->SetMarkerStyle(_markers[idx]);
		g->SetFillColorAlpha(gStyle->GetColorPalette((255/ psize) * idx + 10 + 5 ), 0.2);
//		g->SetFillColorAlpha(kGray+1, 0.2);
	};
	std::vector<TGraphAsymmErrors*> vg;
	std::vector<TGraphAsymmErrors*> vg_syst;

	TGraph* nullGraph = new TGraph();

	c1->cd();
	c1->SetTopMargin(0.1);
	c1->SetLeftMargin(0.13);
	c1->SetTicks();
	nullGraph->AddPoint(0.0,0.0);
	nullGraph->AddPoint(1.2,1.2);
	nullGraph->GetXaxis()->SetLimits(0.,1.3);
	nullGraph->GetXaxis()->SetRangeUser(0.,1.3);
	nullGraph->GetXaxis()->CenterTitle();
	nullGraph->GetXaxis()->SetTitle("Binding Energy (GeV)");
	nullGraph->GetXaxis()->SetTitleOffset(1.2);
	nullGraph->GetYaxis()->CenterTitle();
	nullGraph->GetYaxis()->SetTitle("#it{R}_{AA}");

	nullGraph->GetYaxis()->SetLimits(0.,1.3);
	nullGraph->GetYaxis()->SetRangeUser(0.,1.3);
	nullGraph->SetMarkerSize(0);
	nullGraph->Draw("AP");
	TLegend* leg = new TLegend(0.2, 0.42, 0.72, 0.71);
	leg->SetTextSize(0.020);
	leg->SetTextFont(42);
	for(auto idx : ROOT::TSeqI(psize) ){
		vg.push_back( new TGraphAsymmErrors());
		vg_syst.push_back( new TGraphAsymmErrors());
		set_graph(vg[idx], idx);
		set_graph_syst(vg_syst[idx], idx);
		vg[idx]->GetXaxis()->SetLimits(0.,1.3);
		vg[idx]->GetXaxis()->SetRangeUser(0.,1.3);

		vg[idx]->GetYaxis()->SetLimits(0.,1.3);
		vg[idx]->GetYaxis()->SetRangeUser(0.,1.3);
		vg_syst[idx]->Draw("5");
		vg[idx]->Draw("PE");
		leg->AddEntry(vg[idx], Form("%s %s, %s", _id[idx].c_str(), _id_cent[idx].c_str(), _id_tag[idx].c_str()), "plf");
	}
	leg->SetBorderSize(0);
	leg->SetEntrySeparation(0.14);
	leg->SetColumnSeparation(0.14);

	leg->Draw();
	TLine* lineone = new TLine(0., 1., 1.3, 1.);
	lineone->SetLineStyle(kDashed);
	lineone->SetLineWidth(1);
	lineone->SetLineColor(kBlack);
	lineone->Draw();
	tl->SetTextSize(0.042);
	tl->SetTextAlign(12);
	tl->DrawLatex(0.07, 1.2, "PbPb #sqrt{s_{NN}} = 5.02 TeV");
	CMS_lumi_square(c1, 0, 33, 2);

	c1->SaveAs("../checkout/raa_vs_bindingE.pdf");
}
