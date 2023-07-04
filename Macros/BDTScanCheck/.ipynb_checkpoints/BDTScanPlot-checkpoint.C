#include "wrapper.cxx"
#include <iostream>
#include <future>
#include <thread>

THttpServer* serv = new THttpServer("localhost:8082");
TCanvas* c1 =new TCanvas();
void BDTScanPlot(){
	ROOT::EnableThreadSafety();
	auto ax = ana_bm["3c"][0];

	string type = "CB3:EE:GCscan";
	long ts = 200019111111;

	type = "CB3:CC4:GCscan";
	std::vector<string> vtypes = {"CB3:EE:GCscan", "CB3:CC4:GCscan"};
	std::vector<double> vrange;  
	for ( double idx =  -0.9; idx < 1.; idx +=0.4 ){
		vrange.push_back( idx );
	}
	auto x = fits_wrapper_pset{ 200019111111, ax, "CB3:EE:GC",  std::vector<double> {0.2620}};
	auto x2 = fits_wrapper_pset{ 400019111111, ax,  "CB3:EE:GC", std::vector<double>  {0.2363}};
//	auto x  = fits_wrapper_pset{ 400019111111, ax, "CB3:EE:GCscan", vrange};
//	auto x2 = fits_wrapper_pset{ 200019111111, ax, "CB3:CC4:GCscan", vrange};
//	auto x3 = fits_wrapper_pset{ 200019111111, ax, "CB3:CC5:GCscan", vrange};
//	std::vector<fits_wrapper_pset> vx = {x, x2, x3};
	std::vector<fits_wrapper_pset> vx = {x, x2};
	gStyle->SetEndErrorSize(0);
	auto todo = [=](int idx){
//		auto f = fits_wrapper(ts, ax, vtypes[idx]);
		auto f = fits_wrapper(vx[idx]);
//		f.setIntervalAny(vrange);
		f.eval();
		return f.createGraph();
	};
	

	// Create the pool of workers
	ROOT::TProcessExecutor workers(vx.size());
	// Fill the pool with work
	auto res = workers.Map(todo, ROOT::TSeqI(vx.size()));
	string DrawOpt;
	bool bfirst = true;
	int color_it = 1;
	double ymin= TMath::Infinity();
	double ymax = 0;
	for( auto g : res ){
		 ymin =std::min( g->GetYaxis()->GetXmin(), ymin);
		 ymax = std::max( g->GetYaxis()->GetXmax(), ymax);
	}
	ymin = 0.9* ymin;
	ymax = 1.1* ymax;
	for( auto g : res ){
		if( bfirst ){
			bfirst = false; 
			g->GetYaxis()->SetRangeUser(ymin, ymax);
			g->GetXaxis()->SetLimits(-1,1);
			g->GetXaxis()->SetRangeUser(-1,1);
			DrawOpt = "APE";
		}
		else DrawOpt = "PE";
		paintG(g, (EColor) color_it, (EColor) color_it, kFullCircle);
		g->Draw(DrawOpt.c_str());
		color_it ++ ;
	}
//	auto g= res[0];
//	auto g2 = res[1];
//	c1->cd();
//	paintG(g, kBlue, kBlue, kFullCircle);
//	paintG(g2, kRed, kRed, kFullCircle);
//	g->GetYaxis()->SetRangeUser(0,10000);
//	g->GetXaxis()->SetLimits(-1,1);
//	g->GetXaxis()->SetRangeUser(-1,1);
//	g->Draw("APE");
//	g2->Draw("PE");

	c1->SaveAs("test.pdf");

}
