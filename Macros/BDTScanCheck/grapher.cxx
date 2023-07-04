#pragma once
#include "wrapper.h"
#include "TVectorD.h"

TGraphAsymmErrors* fits_wrapper::createGraph( string correction = "none"){
	std::vector<double> vx, vy, vey;
	for(auto ep : datapoints){
		auto element = ep.second;
		if( element.isRangeInc && element.isGoodFit ){
			double val = element.yield.getVal() / element.correction;
			double err = element.yield.getError() / element.correction;
			vy.push_back(val);
			vx.push_back(ep.first);
			vey.push_back(err);
		}
	}
	int v_size = vx.size();
	return new TGraphAsymmErrors(v_size, &vx[0], &vy[0], nullptr, nullptr, &vey[0], &vey[0]);
};

void paintG(TGraphAsymmErrors* g, EColor color_m, EColor color_l, EMarkerStyle marker, double marker_size =1.4){
	g->SetMarkerStyle( marker );
	g->SetMarkerColor( color_m );
	g->SetLineColor( color_l );
	g->SetMarkerSize( marker_size );
};
