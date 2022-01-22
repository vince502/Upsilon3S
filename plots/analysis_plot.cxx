//#define _TS 9999999999
#define _TS 10000000016
#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#   include "../LLR_CCorder_9999999999.h"
#   define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
#   include "../LLR_CCorder_10000000016.h"
#   define getNomBkgO getNomBkgO_10000000016
#endif

#if _TS == 10000000003 && __has_include("../LLR_CCorder_10000000003.h")
#   include "../LLR_CCorder_10000000003.h"
#   define getNomBkgO getNomBkgO_10000000003
#endif

#if _TS != 9999999999
#	define ana_bm ana_bm_comb
#endif
#include "../BDT/bininfo.h"
#include "../BDT/BDTtraindiff.cxx"
#include "../glauberparams_PbPb5TeV.h"

TGraphAsymmErrors analysis_plot(TFile* hf){
	TH1D* hp3s = (TH1D*) hf->Get("rp3S");
	TH1D* hp2s = (TH1D*) hf->Get("rp2S");
	TH1D* hc3s = (TH1D*) hf->Get("rc3S");
	TH1D* hc2s = (TH1D*) hf->Get("rc2S");
	TGraphAsymmErrors g_p3s;
	TGraphAsymmErrors g_p2s;
	TGraphAsymmErrors g_c3s;
	TGraphAsymmErrors g_c2s;
	TGraphAsymmErrors g_i3s;
	TGraphAsymmErrors g_i2s;
	
	auto fillgraph = [&](TH1D& hist, TGraphAsymmErrors& grap, string abt){
		auto vab = ana_bm[abt.c_str()];
		std::sort(vab.begin(), vab.end(), [](ana_bins &x, ana_bins &y){
			return x.plot_idx < y.plot_idx;}
		);
		for( auto idx : ROOT::TSeqI(1,vab.size()+1,1)){
			auto ab = vab[idx-1];
			std::cout << Form(" idx-1 pl, ph, cl, ch : %d  %d %d %d %d", idx-1, ab.pl, ab.ph, ab.cl, ab.ch) << std::endl;
			if(ab.bintype == kInt){ std::cout << "skipping integrated bin" << std::endl; continue;}
			int plt_idx = ab.plot_idx;
			std::pair<double, double> point_x;
			std::pair<double, double> point_y;
			if(ab.bintype == kCent){
				point_x = glp::Npart[{ab.centl, ab.centh}];
				point_y = {hist.GetBinContent( (vab.size()+1) - idx), hist.GetBinError( (vab.size() +1) - idx)};
			}
			if(ab.bintype == kPt){
				point_x = {((double)( ab.pl + ab.ph ))/2., ((double)(ab.ph-ab.pl))/2. };
				point_y = {hist.GetBinContent( idx ), hist.GetBinError( idx )};
			}
			grap.AddPoint(point_x.first, point_y.first);
			grap.SetPointError(idx-1, point_x.second, point_x.second, point_y.second, point_y.second);
		}
	};
	g_i2s.AddPoint(2, hc2s->GetBinContent(1)) ;
	g_i2s.SetPointError(0, 0,0, hc2s->GetBinError(1), hc2s->GetBinError(1) ) ;
	g_i3s.AddPoint(3, hc3s->GetBinContent(1)) ;
	g_i3s.SetPointError(0, 0,0, hc3s->GetBinError(1), hc3s->GetBinError(1) ) ;

	fillgraph(*hc2s, g_c2s, "2c");
	fillgraph(*hc3s, g_c3s, "3c");
	fillgraph(*hp2s, g_p2s, "2p");
	fillgraph(*hp3s, g_p3s, "3p");

	TCanvas* c1 = new TCanvas("c1","", 2400,900);
	TPad* p1_L = new TPad("p1L", "", 0.00, 0., 0.83,1.);
	TPad* p1_R = new TPad("p1R", "", 0.83, 0., 1., 1.);

	double p2scale = (0.83/ (1. - 0.83) ) ;

	p1_L->SetRightMargin(0);
	p1_R->SetLeftMargin(0);

	c1->Divide(2,1);
	c1->cd(1);
	p1_L->Draw();
	p1_R->Draw();

/////////////////////////////////GRAPH ATTR///////////////////////////////////
	g_c2s.SetLineColor(kBlue);
	g_p2s.SetLineColor(kBlue);
	g_i2s.SetLineColor(kBlue);
	g_c2s.SetMarkerColor(kBlue);
	g_p2s.SetMarkerColor(kBlue);
	g_i2s.SetMarkerColor(kBlue);
	g_c3s.SetLineColor(kGreen+2);
	g_p3s.SetLineColor(kGreen+2);
	g_i3s.SetLineColor(kGreen+2);
	g_c3s.SetMarkerColor(kGreen+2);
	g_p3s.SetMarkerColor(kGreen+2);
	g_i3s.SetMarkerColor(kGreen+2);

	g_c2s.SetMarkerStyle(kFullSquare);
	g_p2s.SetMarkerStyle(kFullSquare);
	g_i2s.SetMarkerStyle(kFullSquare);
	g_c2s.SetMarkerSize(1.6);
	g_p2s.SetMarkerSize(1.6);
	g_i2s.SetMarkerSize(1.6);

	g_c3s.SetMarkerStyle(kFullCircle);
	g_p3s.SetMarkerStyle(kFullCircle);
	g_i3s.SetMarkerStyle(kFullCircle);
	g_c3s.SetMarkerSize(1.6);
	g_p3s.SetMarkerSize(1.6);
	g_i3s.SetMarkerSize(1.6);
///////////////////////////////////////////////////////////////////////////////
	gStyle->SetEndErrorSize(0);

	double yup = 1.3;
	double ydown = 0.0;

	TLine* lineone = new TLine();
	lineone->SetLineStyle(kDashed);
	lineone->SetLineWidth(1);

	p1_L->cd();
	g_c2s.GetYaxis()->SetRangeUser(ydown, yup);
	g_c2s.GetXaxis()->SetTitle("#LT N_{part} #GT");
	g_c2s.GetXaxis()->SetTitleOffset(1.1);
	g_c2s.GetXaxis()->CenterTitle();
	g_c2s.GetYaxis()->SetTitle("R_{AA}");
	g_c2s.GetYaxis()->CenterTitle();
	g_c2s.Draw("APE");
	g_c3s.Draw("PE ");
	lineone->DrawLine(0, 1, 420, 1);
	p1_L->Update();
	p1_L->Draw();

	p1_R->cd();
	g_i2s.GetYaxis()->SetRangeUser(ydown, yup);
	g_i2s.GetYaxis()->SetTickLength( g_i2s.GetYaxis()->GetTickLength() * p2scale );
	g_i2s.GetXaxis()->SetRangeUser(1,4);
	g_i2s.GetXaxis()->SetLimits(1,4);
	g_i2s.GetXaxis()->SetTickSize(0);
	g_i2s.GetXaxis()->SetLabelSize(0);
	g_i2s.Draw("APE");
	g_i3s.Draw("PE");
	lineone->DrawLine(1,1,4,1);
	p1_R->Update();
	p1_R->Draw();


	c1->cd(2);
	g_p2s.GetYaxis()->SetRangeUser(ydown, yup);
	g_p2s.GetXaxis()->SetRangeUser(0, 30);
	g_p2s.GetXaxis()->SetTitle("p_{T} (GeV/c)");
	g_p2s.GetXaxis()->SetTitleOffset(1.1);
	g_p2s.GetXaxis()->CenterTitle();
	g_p2s.GetYaxis()->SetTitle("R_{AA}");
	g_p2s.GetYaxis()->CenterTitle();
	g_p2s.Draw("APE");
	g_p3s.Draw("PE");
	lineone->DrawLine(0, 1, 30, 1);
	
	c1->Modified();
	c1->Update();
	c1->SaveAs("testDraw_99.pdf");
	return g_p2s;

};


TGraphAsymmErrors analysis_plot(){
	return analysis_plot(TFile::Open("./result/RAA_10000000016.root"));
};
