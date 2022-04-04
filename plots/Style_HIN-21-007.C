#include "Style_HIN-21-007.h"
bool isType(string cmp, string t){
	return (strcmp(t.c_str(), cmp.c_str())==0);
};
bool  FindIn(string t, string qry){
	auto res = t.find(qry);
	if(res == std::string::npos) return false;
	else return true;
};

string DR_y_title = "(#font[122]{N}_{#Upsilon(3S)}/#font[122]{N}_{#Upsilon(2S)})_{PbPb}#lower[0.3]{#scale[1.5]{#it{/}}}(#font[122]{N}_{#Upsilon(3S)}/#font[122]{N}_{#Upsilon(2S)})_{pp}";
//string DR_y_title = "#left(#font[122]{N}_{#Upsilon(3S)}/#font[122]{N}_{#Upsilon(2S)}#right)_{PbPb} / #left(#font[122]{N}_{#Upsilon(3S)}/#font[122]{N}_{#Upsilon(2S)}#right)_{pp}";

void readyPlot(TGraphAsymmErrors* gStat, TGraphAsymmErrors* gSyst=nullptr, string type=""){
	/*CA, PA: #S, DR: INT, CENT, PT*/
	GraphSetAttr x = map_GraphStyle[type];
	double ydown, yup;
	double p2scale = kGLBp2scale;
	if(gStat){
		gStat->SetLineColor(x.kLineColor);
		gStat->SetLineWidth(x.kLineWidth);
		gStat->SetLineStyle(x.kLineStyle);
		gStat->SetMarkerColor(x.kMarkerColor);
		gStat->SetMarkerSize(x.kMarkerSize);
		gStat->SetMarkerStyle(x.kMarkerStyle);
	}

	if(gSyst){
		gSyst->SetLineColor(x.kSystLineColor);
		gSyst->SetLineWidth(x.kSystLineWidth);
		gSyst->SetLineStyle(x.kSystLineStyle);
		gSyst->SetFillColorAlpha(x.kFillColor, x.kFillAlpha);
	}
	if( FindIn(type, "CENT")){
		if( !FindIn(type, "DR" ) ){yup = RAACENTYUP; ydown = RAACENTYDOWN;
			if(gStat){
			gStat->GetYaxis()->SetRangeUser(ydown, yup);
			gStat->GetXaxis()->SetTitle("#LT N_{part} #GT");
			gStat->GetXaxis()->SetTitleOffset(0.9);
			gStat->GetXaxis()->SetTitleSize(0.05);
			gStat->GetXaxis()->CenterTitle();
			gStat->GetYaxis()->SetTitle("R_{AA}");
			gStat->GetYaxis()->SetTitleOffset(0.9);
			gStat->GetYaxis()->SetTitleSize(0.05);
			gStat->GetYaxis()->CenterTitle();
			}
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetXaxis()->SetTitle("#LT N_{part} #GT");
			gSyst->GetXaxis()->SetTitleOffset(0.9);
			gSyst->GetXaxis()->SetTitleSize(0.05);
			gSyst->GetXaxis()->CenterTitle();
			gSyst->GetYaxis()->SetTitle("R_{AA}");
			gSyst->GetYaxis()->SetTitleOffset(0.9);
			gSyst->GetYaxis()->SetTitleSize(0.05);
			gSyst->GetYaxis()->CenterTitle();
			}
		}
		if( FindIn(type, "DR" ) ){yup = DRCENTYUP; ydown = DRCENTYDOWN;
			if(gStat){
			gStat->GetYaxis()->SetRangeUser(ydown, yup);
			gStat->GetXaxis()->SetLimits(0, 420);
			gStat->GetXaxis()->SetRangeUser(0, 420);
			gStat->GetXaxis()->SetTitle("#LT N_{part} #GT");
			gStat->GetXaxis()->SetTitleOffset(0.9);
			gStat->GetXaxis()->SetTitleSize(0.05);
			gStat->GetXaxis()->CenterTitle();
			gStat->GetYaxis()->SetTitle(DR_y_title.c_str());
			gStat->GetYaxis()->SetTitleOffset(1.3);
			gStat->GetYaxis()->SetTitleSize(0.05);
			gStat->GetYaxis()->CenterTitle();
			}
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetXaxis()->SetLimits(0, 420);
			gSyst->GetXaxis()->SetRangeUser(0, 420);
			gSyst->GetXaxis()->SetTitle("#LT N_{part} #GT");
			gSyst->GetXaxis()->SetTitleOffset(0.9);
			gSyst->GetXaxis()->SetTitleSize(0.05);
			gSyst->GetXaxis()->CenterTitle();
			gSyst->GetYaxis()->SetTitle(DR_y_title.c_str());
//			gSyst->GetYaxis()->SetTitle("(#Upsilon(3S)/#Upsilon(2S))_{PbPb} / (#Upsilon(3S)/#Upsilon(2S))_{pp}");
			gSyst->GetYaxis()->SetTitleOffset(1.3);
			gSyst->GetYaxis()->SetTitleSize(0.05);
			gSyst->GetYaxis()->CenterTitle();
			}
		}

	}
	if( FindIn(type, "INT")){

		if( FindIn(type, "DR" )	 ){yup = DRCENTYUP; ydown = DRCENTYDOWN;
			if(gStat){
			gStat->GetYaxis()->SetRangeUser(ydown, yup);
			gStat->GetYaxis()->SetTickLength( gStat->GetYaxis()->GetTickLength() * p2scale );
			gStat->GetXaxis()->SetRangeUser(1,4);
			gStat->GetXaxis()->SetLimits(1,4);
			gStat->GetXaxis()->SetTickSize(0);
			gStat->GetXaxis()->SetLabelSize(0);
			}
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetYaxis()->SetTickLength( gSyst->GetYaxis()->GetTickLength() * p2scale );
			gSyst->GetXaxis()->SetRangeUser(1,4);
			gSyst->GetXaxis()->SetLimits(1,4);
			gSyst->GetXaxis()->SetTickSize(0);
			gSyst->GetXaxis()->SetLabelSize(0);
			}
		}
		if( !FindIn(type, "DR" ) ){yup = RAACENTYUP; ydown = RAACENTYDOWN;
			if(gStat){
			gStat->GetYaxis()->SetRangeUser(ydown, yup);
			gStat->GetYaxis()->SetTickLength( gStat->GetYaxis()->GetTickLength() * p2scale );
			gStat->GetXaxis()->SetRangeUser(1,4);
			gStat->GetXaxis()->SetLimits(1,4);
			gStat->GetXaxis()->SetTickSize(0);
			gStat->GetXaxis()->SetLabelSize(0);
			}
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetYaxis()->SetTickLength( gSyst->GetYaxis()->GetTickLength() * p2scale );
			gSyst->GetXaxis()->SetRangeUser(1,4);
			gSyst->GetXaxis()->SetLimits(1,4);
			gSyst->GetXaxis()->SetTickSize(0);
			gSyst->GetXaxis()->SetLabelSize(0);
			}
		}

	}
	if( FindIn(type, "PT")){
		if( !FindIn(type, "DR" ) ){yup = RAACENTYUP; ydown = RAACENTYDOWN;
			if(gStat){
			gStat->GetYaxis()->SetRangeUser(ydown, yup);
			gStat->GetXaxis()->SetRangeUser(0, 30);
			gStat->GetXaxis()->SetTitle("p_{T} (GeV/c)");
			gStat->GetXaxis()->SetTitleOffset(0.9);
			gStat->GetXaxis()->SetTitleSize(0.05);
			gStat->GetXaxis()->CenterTitle();
			gStat->GetYaxis()->SetTitle("R_{AA}");
			gStat->GetYaxis()->SetTitleOffset(0.9);
			gStat->GetYaxis()->SetTitleSize(0.05);
			gStat->GetYaxis()->CenterTitle();
			}
	
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetXaxis()->SetRangeUser(0, 30);
			gSyst->GetXaxis()->SetTitle("p_{T} (GeV/c)");
			gSyst->GetXaxis()->SetTitleOffset(0.9);
			gSyst->GetXaxis()->SetTitleSize(0.05);
			gSyst->GetXaxis()->CenterTitle();
			gSyst->GetYaxis()->SetTitle("R_{AA}");
			gSyst->GetYaxis()->SetTitleOffset(0.9);
			gSyst->GetYaxis()->SetTitleSize(0.05);
			gSyst->GetYaxis()->CenterTitle();
			}
		}
		if( FindIn(type, "DR" )	 ){yup = DRPTYUP; ydown = DRPTYDOWN;
			if(gStat){
			gStat->GetYaxis()->SetRangeUser(ydown, yup);
			gStat->GetXaxis()->SetRangeUser(0, 30);
			gStat->GetXaxis()->SetTitle("p_{T} (GeV/c)");
			gStat->GetXaxis()->SetTitleOffset(0.9);
			gStat->GetXaxis()->SetTitleSize(0.05);
			gStat->GetXaxis()->CenterTitle();
			gStat->GetYaxis()->SetTitle(DR_y_title.c_str());
			gStat->GetYaxis()->SetTitleOffset(1.15);
			gStat->GetYaxis()->SetTitleSize(0.05);
			gStat->GetYaxis()->CenterTitle();
			}
	
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetXaxis()->SetRangeUser(0, 30);
			gSyst->GetXaxis()->SetTitle("p_{T} (GeV/c)");
			gSyst->GetXaxis()->SetTitleOffset(0.9);
			gSyst->GetXaxis()->SetTitleSize(0.05);
			gSyst->GetXaxis()->CenterTitle();
			gSyst->GetYaxis()->SetTitle(DR_y_title.c_str());
			gSyst->GetYaxis()->SetTitleOffset(1.15);
			gSyst->GetYaxis()->SetTitleSize(0.05);
			gSyst->GetYaxis()->CenterTitle();
			}
		}
	}


};
