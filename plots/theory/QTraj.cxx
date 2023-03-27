
std::vector<dQTraj> get_theory_QTraj_comp(string type){
	string name_file = fQTraj[type]; 
	std::cout << name_file << std::endl;
	ifstream textfile(name_file.c_str());
	string sbuf;
	//QTraj : ((range cbin or pT), raa_nom, raa_up, raa_down 
	std::vector< string> vbuf;
	std::vector<dQTraj> ttheory;
	bool firstline = true;
	while(getline(textfile, sbuf) ){
		std::cout << sbuf << std::endl;
		if(!firstline) vbuf = parser_symbol(sbuf, "\t"); //delimieter is a Tab
		dQTraj dbuf;
		if( !firstline){
			for ( auto buf : vbuf){
//				if( strcmp(type.substr(0,1).c_str(), "c")== 0){
				if( type[0]- 'c'== 0){
					dbuf.cl = (int) stod(vbuf[0]);
					dbuf.ch = (int) stod(vbuf[1]);
				}
				else{ 
					dbuf.pl = stod(vbuf[0]);
					dbuf.ph = stod(vbuf[1]);
				}
				dbuf.raa = stod(vbuf[2]);
				dbuf.raado = stod(vbuf[3]);
				dbuf.raaup = stod(vbuf[4]);

			}
			ttheory.push_back(dbuf);
		}
		firstline = false;
	}
	return ttheory;
};


std::pair<std::map<string, TGraphAsymmErrors*>, TGraphAsymmErrors*> get_theory_QTraj(int mode = kTCent, int state =2){
	std::map<string, TGraphAsymmErrors*> map_curve;
	string type;
	if( mode == kTCent) type ="c";
	if( mode == kTPt) type ="p";
	auto res_center = get_theory_QTraj_comp(Form("%s%ds",type.c_str(), state ));
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
		dQTraj ddata = res_center[idx];
		if( mode ==kTCent) {
			x = glp::Npart[{ddata.cl, ddata.ch}].first;
			xl = glp::Npart[{ddata.cl, ddata.ch}].second * 8  ;
			xh = xl;

		}
		std::cout << "X : " << x << std::endl;
		if( mode ==kTPt) {
			xl = ddata.pl;
			xh = ddata.ph;
			x = ( xl + xh  ) / 2.;
			xl = x - xl;
			xh = xh - x;
		}
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


void draw_theory_QTraj(TPad* p1, TLegend* leg, int mode, int state, bool indent = false){
	auto res = get_theory_QTraj(mode,state);
	auto gband= res.second;
	auto gcc = res.first["nominal"];
	auto gcp = res.first["errup"];
	auto gcm = res.first["errdo"];
	p1->cd();

	unsigned int fills = 3144;
	double alph = 0.65;
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
	gband->SetLineColorAlpha(kRed -3, alph );
	gcc->		SetLineColor(kRed -3);
	gcm->		SetLineColor(kRed -3);
	gcp->		SetLineColor(kRed -3);
	}

	if(state == 2){
	fills = 3145;
	gband->SetFillColorAlpha(kViolet+7 , alph);
	gband->SetFillStyle(fills);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(1.7);
	gband->SetMarkerColor(kBlue- 7);
	gband->SetLineColorAlpha(kBlue +1, alph );
	gcc->		SetLineColor(kBlue +1 );
	gcm->		SetLineColor(kBlue +1 );
	gcp->		SetLineColor(kBlue +1 );
	}

	if(state == 3){
	fills = 3154;
	gband->SetFillColorAlpha(kTeal-5, alph);
	gband->SetFillStyle(fills);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(1.7);
	gband->SetMarkerColor(kTeal+ 5);
	gband->SetLineColor(kTeal+5);
	gcc->		SetLineColor(kTeal+5);
	gcm->		SetLineColor(kTeal+5);
	gcp->		SetLineColor(kTeal+5);
	}

	if(state == 32){
	gband->SetFillColorAlpha(kOrange+6, alph);
	gband->SetFillStyle(fills);
	gband->SetLineColor(kOrange+7);
	gband->SetLineWidth(2);
	gband->SetLineStyle(kDashed);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(2.2);
	gband->SetMarkerColorAlpha(kOrange+7, alph);
	gcc->		  SetLineColor(kOrange+7);
	gcm->		  SetLineColor(kOrange-3);
	gcp->		  SetLineColor(kOrange-3);
	}

	gband->Draw("5");
	gcc->Draw("E");
//	gcp->Draw("E");
//	gcm->Draw("E");
	if(state !=32){
		leg->SetHeader("#scale[1.1]{#bf{OQS + pNRQCD}}");
		leg->AddEntry(gband, Form("#Upsilon(%dS)", state), "lf");
	}
	else{ 
		if(indent)  leg->AddEntry(gband, "#splitline{OQS}{ + pNRQCD}", "lf");
		if(!indent) leg->AddEntry(gband, "OQS + pNRQCD", "lf");
	}

	p1->Update();
}