#include "../../glauberparams_PbPb5TeV.h"

bool closeTo(double i1, double i2){
        return ( fabs(i1-i2) < 1e-7) ? true : false;
}

std::pair<double, double> getCMSnpart(double inNpart){
//    if (closeTo(inNpart, 0.97059866))   return glp::Npart[{90,100}];
    if (closeTo(inNpart, 3.8095328))    return glp::Npart[{80,90}];
    if (closeTo(inNpart, 9.6677908))   return glp::Npart[{70,80}];
    if (closeTo(inNpart, 21.292762))   return glp::Npart[{60,70}];
    if (closeTo(inNpart, 41.050937))   return glp::Npart[{50,60}];
    if (closeTo(inNpart, 70.787143))   return glp::Npart[{40,50}];
    if (closeTo(inNpart, 112.39007))   return glp::Npart[{30,40}];
    if (closeTo(inNpart, 168.50284))   return glp::Npart[{20,30}];
    if (closeTo(inNpart, 243.53796))   return glp::Npart[{10,20}];
    if (closeTo(inNpart, 315.85912))   return glp::Npart[{5,10}];
    if (closeTo(inNpart, 374.98828))   return glp::Npart[{0,5}];
    else return std::make_pair(-1,-1);
};

std::vector<dQTraj2023> get_theory_QTraj2023_comp(string type){
	string name_file = fQTraj2023[type]; 
	std::cout << name_file << std::endl;
	ifstream textfile(name_file.c_str());
	string sbuf;
	//QTraj : ((range cbin or pT), raa_nom, raa_up, raa_down 
	std::vector< string> vbuf;
	std::vector<dQTraj2023> ttheory;
	bool firstline = true;
	while(getline(textfile, sbuf) ){
		std::cout << sbuf << std::endl;
		if(!firstline) vbuf = parser_symbol(sbuf, "\t"); //delimieter is a Tab
		dQTraj2023 dbuf;
		int raaIdx = 0;
		if( !firstline){
			for ( auto buf : vbuf){
//				if( strcmp(type.substr(0,1).c_str(), "c")== 0){
				if( type[0]- 'c'== 0 ){
					if(	type.find("32") != std::string::npos ){
						dbuf.npup = stod(vbuf[1]);
						dbuf.npdo = stod(vbuf[0]);
						raaIdx = 2;
					}
					else{
						dbuf.np =  stod(vbuf[0]);
						raaIdx = 1;
					}
				}
				else{ 
					dbuf.pl = stod(vbuf[0]);
					dbuf.ph = stod(vbuf[1]);
					raaIdx = 2;
				}
				dbuf.raa = stod(vbuf[raaIdx]);
				dbuf.raado = (stod(vbuf[raaIdx+1]) - dbuf.raa);
				dbuf.raaup = (stod(vbuf[raaIdx+1]) - dbuf.raa);

			}
			ttheory.push_back(dbuf);
		}
		firstline = false;
	}
	return ttheory;
};







std::pair<std::map<string, TGraphAsymmErrors*>, TGraphAsymmErrors*> get_theory_QTraj2023(int mode = kTCent, int state =2, bool inclJump = true){

	gStyle->SetLineStyleString(11, "[12 8]");
	std::map<string, TGraphAsymmErrors*> map_curve;
	string type;
	if( mode == kTCent) type ="c";
	if( mode == kTPt) type ="p";
	auto res_center = get_theory_QTraj2023_comp(Form("%s%ds%s",type.c_str(), state, (inclJump) ? "" : "nj"));
	size_t vsize = res_center.size();
	TGraphAsymmErrors* g_center	=new TGraphAsymmErrors();	g_center->SetName("g_nom");
	TGraphAsymmErrors* g_cm		=new TGraphAsymmErrors();	g_cm->SetName("g_up");
	TGraphAsymmErrors* g_cp		=new TGraphAsymmErrors();	g_cp->SetName("g_do");
	map_curve.insert({"nominal", g_center});
	map_curve.insert({"errup", g_cp});
	map_curve.insert({"errdo", g_cm});
	TGraphAsymmErrors* g_band = new TGraphAsymmErrors();
	g_band->SetName(Form("gtheoryQTraj%dS", state));
	double xl, xh, x;
	for( auto idx : ROOT::TSeqI(vsize) ){
		dQTraj2023 ddata = res_center[idx];
		if( mode ==kTCent) {
			if(state ==32){
				xl = ddata.npdo;
				xh = ddata.npup;
				x = ( xl + xh  ) / 2.;
				double xx = 20;
				xl = (xx > x - xl) ? x - xl : xx;
				xh = (xx > xh -x ) ? xh -x : xx;
				if( x > 250 && x < 300 ){x = glp::Npart[{0,30}].first; xl = glp::Npart[{0,30}].second * 8; xh = glp::Npart[{ 0,30}].second * 8;}
				if( x > 80 && x < 150 ){ x = glp::Npart[{30,50}].first; xl = glp::Npart[{30,50}].second * 8; xh = glp::Npart[{30,50}].second * 8;}
				if( x > 20 && x < 60 ){  x = glp::Npart[{50,70}].first; xl = glp::Npart[{50,70}].second * 8;  xh = glp::Npart[{50,70}].second * 8;}
				if( x > 0 && x < 30 ){ x = glp::Npart[{70,90}].first; xl = glp::Npart[{70,90}].second * 8; xh = glp::Npart[{70,90}].second * 8;}
			}
			else{
				x = getCMSnpart(ddata.np).first;
				xl = 10.;
				xh = 10.;
				if( x < 40) { xl = 6; xh =6;}
				if( x < 30) { xl = 5; xh =5;}
				if( x < 15) { xl = 4; xh =4;}
                if(ddata.np > 405) continue;
			}
		}
		if( mode ==kTPt) {
			xl = ddata.pl;
			xh = ddata.ph;
			x = ( xl + xh  ) / 2.;
			xl = x - xl;
			xh = xh - x;
		}
		std::cout << "xl, xh " << xl << ", " << xh << std::endl;
		g_center->AddPoint( x, ddata.raa);
		g_cp->AddPoint( x, ddata.raa + ddata.raaup);
		g_cm->AddPoint( x, ddata.raa - ddata.raado);
		g_center->	SetPointError( idx, xl, xh, 0, 0);
		g_cp->		SetPointError( idx, xl, xh, 0, 0);	
		g_cm->		SetPointError( idx, xl, xh, 0, 0);	
		g_band->AddPoint( x, ddata.raa);
		g_band->SetPointError( idx, xl, xh, ddata.raado, ddata.raaup);
	}
	return std::make_pair(map_curve, g_band); 

};






void draw_theory_QTraj2023(TPad* p1, TLegend* leg, int mode, int state, bool inclJump = true, bool indent = false){
	auto res = get_theory_QTraj2023(mode,state, inclJump);
	auto gband= res.second;
	auto gcc = res.first["nominal"];
	auto gcp = res.first["errup"];
	auto gcm = res.first["errdo"];
	p1->cd();

	unsigned int fills = 3144;
	unsigned int regFill = 1001;
	double alph = 0.65;
	double linealph = 1.;
	double alphReg = 0.4;
	string drawOptCenter = "LX";
	string drawOptBand = "3";
	if( mode ==kPt ){
		alph = 0.5;
	}
//	gStyle->SetHatchesSpacing(0.3);
//	gStyle->SetHatchesLineWidth(1);

	gband->SetMarkerStyle(kFullCircle);

	gband->SetLineStyle(1);
	gcc->  SetLineStyle(1);
	gcm->  SetLineStyle(1);
	gcp->  SetLineStyle(1);

	gband->SetLineWidth(2);
	gcc->  SetLineWidth(2);
	gcm->  SetLineWidth(2);
	gcp->  SetLineWidth(2);

	if(state == 1){
	gband->SetFillColorAlpha(kPink -2 , alph);
	gband->SetFillStyle(fills);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(1.7);
	gband->SetMarkerColor(kBlue- 7);
	gband->SetLineColorAlpha(kRed -3, linealph );
	gcc->		SetLineColor(kRed -3);
	gcm->		SetLineColor(kRed -3);
	gcp->		SetLineColor(kRed -3);
		if(!inclJump){
			gband->SetFillColorAlpha(kOrange +8 , alph);
			gband->SetLineColorAlpha(kOrange +8 , linealph);
			gband->SetFillStyle(fills);
			gcc->		SetLineColor(kOrange -3);
			gcc->		SetLineWidth(3);
			gcm->		SetLineColor(kOrange -3);
			gcp->		SetLineColor(kOrange -3);
			gband->SetLineStyle(11);
			gcc->SetLineStyle(11);
		}
	}

	if(state == 2){
	fills = 3145;
	gband->SetFillColorAlpha(kViolet+7 , alph);
	gband->SetFillStyle(fills);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(1.7);
	gband->SetMarkerColor(kBlue- 7);
	gband->SetLineColorAlpha(kBlue +1,linealph );
	gcc->		SetLineColor(kBlue +1 );
	gcm->		SetLineColor(kBlue +1 );
	gcp->		SetLineColor(kBlue +1 );
		if(!inclJump){
			gband->SetFillColorAlpha(kAzure -6 , alph);
			gband->SetLineColorAlpha(kAzure -3 , linealph);
			gband->SetFillStyle(fills);
			gcc->		SetLineColor(kAzure -3);
			gcc->		SetLineWidth(3);
			gcm->		SetLineColor(kAzure -3);
			gcp->		SetLineColor(kAzure -3);
			gband->SetLineStyle(11);
			gcc->SetLineStyle(11);
		}
	}

	if(state == 3){
	fills = 3154;
	gband->SetFillColorAlpha(kSpring-5, alph);
	gband->SetFillStyle(fills);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(1.7);
	gband->SetMarkerColor(kOrange -2);
	gband->SetLineColor(kGreen +1);
	gcc->		SetLineColor(kGreen +1);
	gcm->		SetLineColor(kGreen +1);
	gcp->		SetLineColor(kGreen +1);
		if(!inclJump){
			gband->SetFillColorAlpha(kSpring -5 , alph);
			gband->SetLineColorAlpha(kGreen +3 , linealph);
			gcc->       SetLineColor(kGreen +3);
			gband->SetFillStyle(fills);
			gcc->		SetLineWidth(3);
			gcm->		SetLineColor(kSpring +0);
			gcp->		SetLineColor(kSpring +0);
			gband->SetLineStyle(11);
			gcc->SetLineStyle(11);
		}
	}

	if(state == 32){
	gband->SetFillColorAlpha(kOrange+6, alph);
	gband->SetFillStyle(fills);
	gband->SetLineWidth(2);
	gband->SetLineStyle(kDashed);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(2.2);
	gband->SetMarkerColorAlpha(kOrange+7, alph);
	gband->SetLineColor(kOrange+10);
	gcc->SetLineStyle(kDashed);
	gcc->		  SetLineColor(kOrange+10);
	gcm->		  SetLineColor(kOrange-3);
	gcp->		  SetLineColor(kOrange-3);
		if(!inclJump){
			gband->SetFillStyle(fills);
			gband->SetFillColorAlpha(kAzure -4, alph);
			gband->		  SetLineColor(kAzure -3);
			gcc->		  SetLineColor(kAzure -3);
			gcm->		  SetLineColor(kAzure -3);
			gcp->		  SetLineColor(kAzure -3);
		}
	}
	if(mode == kPt){
		gband->SetFillStyle(1001);
		drawOptCenter = "E";
		drawOptBand = "2";
	}
	if( (!inclJump) || (mode ==kTCent)){
		gband->SetFillStyle(1001);
		drawOptCenter = "E";
		drawOptBand = "2";
	}

	if(!((!inclJump) && state != 32 ))gband->Draw(drawOptBand.c_str());
	gcc->Draw(drawOptCenter.c_str());
//	gcp->Draw("E");
//	gcm->Draw("E");
	if(state !=32){
		leg->SetHeader("#scale[1.1]{#bf{OQS + pNRQCD}}");
		if(!((!inclJump) && state != 32 ))leg->AddEntry(gband, Form("#Upsilon(%dS)", state), "fl");
        else leg->AddEntry(gcc, Form("#Upsilon(%dS)", state), "l");
	}
	else{ 
		if(indent)  leg->AddEntry(gband, "#splitline{OQS}{ + pNRQCD}", "lf");
		if(!indent) leg->AddEntry(gband, "OQS + pNRQCD", "lf");
	}

	p1->Update();
}