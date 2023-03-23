#include "Style_HIN-21-007.h"
bool isType(string cmp, string t){
	return (strcmp(t.c_str(), cmp.c_str())==0);
};
bool  FindIn(string t, string qry){
	auto res = t.find(qry);
	if(res == std::string::npos) return false;
	else return true;
};

string DR_y_title = "(#font[122]{N}_{#Upsilon(3S)}/#font[122]{N}_{#Upsilon(2S)})_{PbPb}#lower[0.3]{#scale[1.5]{#it{/}}}(#font[122]{N}_{#Upsilon(3S)}/#font[122]{N}_{#Upsilon(2S)})_{pp}"; //Nominal
//string DR_y_title = "#it{DR}_{32}";//#scale[1.5]{#it{/}}2}";
//string DR_y_title = "#left(#font[122]{N}_{#Upsilon(3S)}/#font[122]{N}_{#Upsilon(2S)}#right)_{PbPb} / #left(#font[122]{N}_{#Upsilon(3S)}/#font[122]{N}_{#Upsilon(2S)}#right)_{pp}";

double labOff = 0.0085;
double titleSz = 0.05;
double labelSz  = 0.043;

void readyPlot(TGraphAsymmErrors* gStat, TGraphAsymmErrors* gSyst=nullptr, string type="", int offset = 0){
	/*CA, PA: #S, DR: INT, CENT, PT*/
	GraphSetAttr x = map_GraphStyle[type];
	if( offset <0 ){
		for( auto idx : ROOT::TSeqI(abs(offset))){
			break;
		}
	}
	if( offset >0 ){
		for( auto idx : ROOT::TSeqI(abs(offset))){
			++x;
		}
	}
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
			gStat->GetXaxis()->SetTitle("#LT#it{N}_{part}#GT");
			gStat->GetXaxis()->SetTitleOffset(1.0);
			gStat->GetXaxis()->SetTitleSize(titleSz);
			gStat->GetXaxis()->SetLabelSize(labelSz);
			gStat->GetXaxis()->CenterTitle();
			gStat->GetYaxis()->SetTitle("#it{R}_{AA}");
			gStat->GetYaxis()->SetTitleOffset(1.1);
			gStat->GetYaxis()->SetLabelOffset(labOff);
			gStat->GetYaxis()->SetLabelSize(labelSz);
			gStat->GetYaxis()->SetTitleSize(titleSz);
			gStat->GetYaxis()->CenterTitle();
			}
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetXaxis()->SetTitle("#LT#it{N}_{part}#GT");
			gSyst->GetXaxis()->SetTitleOffset(1.0);
			gSyst->GetXaxis()->SetTitleSize(titleSz);
			gSyst->GetXaxis()->CenterTitle();
			gSyst->GetYaxis()->SetTitle("#it{R}_{AA}");
			gSyst->GetYaxis()->SetTitleOffset(1.9);
			gStat->GetYaxis()->SetLabelOffset(labOff);
			gSyst->GetYaxis()->SetTitleSize(titleSz);
			gSyst->GetYaxis()->CenterTitle();
			gStat->GetXaxis()->SetLabelSize(labelSz);
			gStat->GetYaxis()->SetLabelSize(labelSz);
			}
		}
		if( FindIn(type, "DR" ) ){yup = DRCENTYUP; ydown = DRCENTYDOWN;
			if(gStat){
			gStat->GetYaxis()->SetRangeUser(ydown, yup);
			gStat->GetXaxis()->SetLimits(0, 420);
			gStat->GetXaxis()->SetRangeUser(0, 420);
			gStat->GetXaxis()->SetTitle("#LT#it{N}_{part}#GT");
			gStat->GetXaxis()->SetTitleOffset(1.0);
			gStat->GetXaxis()->SetTitleSize(titleSz);
			gStat->GetXaxis()->CenterTitle();
			gStat->GetYaxis()->SetTitle(DR_y_title.c_str());
			// gStat->GetYaxis()->SetTitleOffset(1.15);
			gStat->GetYaxis()->SetTitleOffset(1.4);
			gStat->GetYaxis()->SetLabelOffset(labOff);
			gStat->GetYaxis()->SetTitleSize(titleSz);
			gStat->GetYaxis()->CenterTitle();
			gStat->GetXaxis()->SetLabelSize(labelSz);
			gStat->GetYaxis()->SetLabelSize(labelSz);
			}
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetXaxis()->SetLimits(0, 420);
			gSyst->GetXaxis()->SetRangeUser(0, 420);
			gSyst->GetXaxis()->SetTitle("#LT#it{N}_{part}#GT");
			gSyst->GetXaxis()->SetTitleOffset(1.0);
			gStat->GetYaxis()->SetLabelOffset(labOff);
			gSyst->GetXaxis()->SetTitleSize(titleSz);
			gSyst->GetXaxis()->CenterTitle();
			gSyst->GetYaxis()->SetTitle(DR_y_title.c_str());
//			gSyst->GetYaxis()->SetTitle("(#Upsilon(3S)/#Upsilon(2S))_{PbPb} / (#Upsilon(3S)/#Upsilon(2S))_{pp}");
			// gSyst->GetYaxis()->SetTitleOffset(1.15);
			gSyst->GetYaxis()->SetTitleOffset(1.40);
			gSyst->GetYaxis()->SetTitleSize(titleSz);
			gSyst->GetYaxis()->CenterTitle();
			gStat->GetXaxis()->SetLabelSize(labelSz);
			gStat->GetYaxis()->SetLabelSize(labelSz);
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
			gStat->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
			gStat->GetXaxis()->SetTitleOffset(1.0);
			gStat->GetXaxis()->SetTitleSize(titleSz);
			gStat->GetXaxis()->CenterTitle();
			gStat->GetYaxis()->SetTitle("#it{R}_{AA}");
			gStat->GetYaxis()->SetTitleOffset(0.9);
			gStat->GetYaxis()->SetLabelOffset(labOff);
			gStat->GetYaxis()->SetTitleSize(titleSz);
			gStat->GetYaxis()->CenterTitle();
			gStat->GetXaxis()->SetLabelSize(labelSz);
			gStat->GetYaxis()->SetLabelSize(labelSz);
			}
	
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetXaxis()->SetRangeUser(0, 30);
			gSyst->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
			gSyst->GetXaxis()->SetTitleOffset(1.0);
			gSyst->GetXaxis()->SetTitleSize(titleSz);
			gSyst->GetXaxis()->CenterTitle();
			gSyst->GetYaxis()->SetTitle("#it{R}_{AA}");
			gSyst->GetYaxis()->SetTitleOffset(0.9);
			gStat->GetYaxis()->SetLabelOffset(labOff);
			gSyst->GetYaxis()->SetTitleSize(titleSz);
			gSyst->GetYaxis()->CenterTitle();
			gStat->GetXaxis()->SetLabelSize(labelSz);
			gStat->GetYaxis()->SetLabelSize(labelSz);
			}
		}
		if( FindIn(type, "DR" )	 ){yup = DRPTYUP; ydown = DRPTYDOWN;
			if(gStat){
			gStat->GetYaxis()->SetRangeUser(ydown, yup);
			gStat->GetXaxis()->SetRangeUser(0, 30);
			gStat->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
			gStat->GetXaxis()->SetTitleOffset(1.0);
			gStat->GetXaxis()->SetTitleSize(titleSz);
			gStat->GetXaxis()->CenterTitle();
			gStat->GetYaxis()->SetTitle(DR_y_title.c_str());
			// gStat->GetYaxis()->SetTitleOffset(1.15);
			gStat->GetYaxis()->SetTitleOffset(1.30);
			gStat->GetYaxis()->SetLabelOffset(labOff);
			gStat->GetYaxis()->SetTitleSize(titleSz);
			gStat->GetYaxis()->CenterTitle();
			gStat->GetXaxis()->SetLabelSize(labelSz);
			gStat->GetYaxis()->SetLabelSize(labelSz);
			}
	
			if(gSyst){
			gSyst->GetYaxis()->SetRangeUser(ydown, yup);
			gSyst->GetXaxis()->SetRangeUser(0, 30);
			gSyst->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
			gSyst->GetXaxis()->SetTitleOffset(1.0);
			gSyst->GetXaxis()->SetTitleSize(titleSz);
			gSyst->GetXaxis()->CenterTitle();
			gSyst->GetYaxis()->SetTitle(DR_y_title.c_str());
			// gSyst->GetYaxis()->SetTitleOffset(1.15);
			gSyst->GetYaxis()->SetTitleOffset(1.30);
			gStat->GetYaxis()->SetLabelOffset(labOff);
			gSyst->GetYaxis()->SetTitleSize(titleSz);
			gSyst->GetYaxis()->CenterTitle();
			gStat->GetXaxis()->SetLabelSize(labelSz);
			gStat->GetYaxis()->SetLabelSize(labelSz);
			}
		}
	}


};
