
std::vector<dHeidelberg> get_theory_Heidelberg_comp(string type){
	string name_file = fHeidelberg[type]; 
//	std::cout << name_file << std::endl;
	ifstream textfile(name_file.c_str());
	string sbuf;
	//Heidelberg : (Npart or pT), RAA1S, RAA2S, RAA3S, RAA1P, RAA23S RAA3S/RAA2S
	std::vector< string> vbuf;
	std::vector<dHeidelberg> ttheory;
	bool skipline = true;
	int val_mod = 0;
	while(getline(textfile, sbuf) ){
		if( val_mod !=1 && sbuf.find("Preliminary suppression factors") != std::string::npos) val_mod = 1;
		if( val_mod !=2 && sbuf.find("Final suppression factors") != std::string::npos) val_mod = 2;
//		std::cout << sbuf << std::endl;
		if( strcmp(sbuf.substr(0,1).c_str(), "#") == 0 || strcmp(sbuf.substr(0,1).c_str(), "\r") == 0 ) skipline = true;
		else skipline = false;
		if(!skipline){
			//remove white spaces in front of the line
			sbuf.erase(0, sbuf.find_first_not_of(" "));
			vbuf = parser_symbol2(sbuf); //delimieter is a Tab
		} 
		dHeidelberg dbuf;
		if( !skipline){
				dbuf.mod = val_mod;
				dbuf.cent_intv = vbuf[0];
				dbuf.Npart = stod(vbuf[1]);
				dbuf.pt = (strcmp(vbuf[2].c_str(), "<pT>") ==0) ? 100 : stod(vbuf[2]);
				dbuf.raa1s = (val_mod ==1 ) ? stod(vbuf[3]) : stod(vbuf[3]);
				dbuf.raa2s = (val_mod ==1 ) ? stod(vbuf[5]) : stod(vbuf[4]);
				dbuf.raa3s = (val_mod ==1 ) ? stod(vbuf[7]) : stod(vbuf[5]);
//			}
			ttheory.push_back(dbuf);
		}
	}
	return ttheory;
};


//change get_theory_Transport to get_theory_Heidelberg

std::pair<std::map<string, TGraphAsymmErrors*>, TGraphAsymmErrors*> get_theory_Heidelberg(int mode = kTCent, int state =2){
	std::map<string, TGraphAsymmErrors*> map_curve;
	string type;
	if( mode == kTCent) type ="c";
	if( mode == kTPt) type ="p";
	std::cout << type.c_str() << std::endl;
	auto res_center = get_theory_Heidelberg_comp(Form("nobin"));
	size_t vsize = res_center.size();
	TGraphAsymmErrors* g_band = nullptr;
	TGraphAsymmErrors* g_pre		=new TGraphAsymmErrors();	g_pre->SetName("g_pre");
	TGraphAsymmErrors* g_fin		=new TGraphAsymmErrors();	g_fin->SetName("g_fin");
	map_curve.insert({"valpre", g_pre});
	map_curve.insert({"valfin", g_fin});
	double x;
	for( auto idx : ROOT::TSeqI(vsize) ){
		dHeidelberg ddata = res_center[idx];
		if( mode ==kTCent && ddata.pt == 100. && strcmp(ddata.cent_intv.c_str(),"0-100%") != 0) {
			x = ddata.Npart;
			if(ddata.mod == 1 && state == 1) g_pre->AddPoint( x, ddata.raa1s);
			if(ddata.mod == 1 && state == 2) g_pre->AddPoint( x, ddata.raa2s);
			if(ddata.mod == 1 && state == 3) g_pre->AddPoint( x, ddata.raa3s);
			if(ddata.mod == 1 && state == 32) g_pre->AddPoint( x, ddata.raa3s / ddata.raa2s);
			if(ddata.mod == 2 && state == 1) g_fin->AddPoint( x, ddata.raa1s);
			if(ddata.mod == 2 && state == 2) g_fin->AddPoint( x, ddata.raa2s);
			if(ddata.mod == 2 && state == 3) g_fin->AddPoint( x, ddata.raa3s);
			if(ddata.mod == 2 && state == 32) g_fin->AddPoint( x, ddata.raa3s / ddata.raa2s);
		}
		if( mode ==kTPt && strcmp(ddata.cent_intv.c_str(),"0-100%") == 0 && ddata.pt !=100) {
			x = ddata.pt;
			if(ddata.mod == 1 && state == 1) g_pre->AddPoint( x, ddata.raa1s);
			if(ddata.mod == 1 && state == 2) g_pre->AddPoint( x, ddata.raa2s);
			if(ddata.mod == 1 && state == 3) g_pre->AddPoint( x, ddata.raa3s);
			if(ddata.mod == 1 && state == 32) g_pre->AddPoint( x, ddata.raa3s / ddata.raa2s);
			if(ddata.mod == 2 && state == 1) g_fin->AddPoint( x, ddata.raa1s);
			if(ddata.mod == 2 && state == 2) g_fin->AddPoint( x, ddata.raa2s);
			if(ddata.mod == 2 && state == 3) g_fin->AddPoint( x, ddata.raa3s);
			if(ddata.mod == 2 && state == 32) g_fin->AddPoint( x, ddata.raa3s / ddata.raa2s);
		}
	}
	return std::make_pair(map_curve, g_band); 
};


void draw_theory_Heidelberg(TPad* p1, TLegend* leg, int mode, int state, bool indent = false){
	auto res = get_theory_Heidelberg(mode,state);
	auto gpre = res.first["valpre"];
	auto gfin = res.first["valfin"];
	p1->cd();

	unsigned int fills = 3335;
	double alph = 1.;
//	gStyle->SetHatchesSpacing(1);
//	gStyle->SetHatchesLineWidth(1);

//	gband->SetMarkerStyle(kFullCircle);

	gfin->  SetLineStyle(1);
	gpre->  SetLineStyle(2);

	gfin->  SetLineWidth(2);
	gpre->  SetLineWidth(2);

	if(state == 1){
	gfin->		SetLineColor(kRed -3);
	gpre->		SetLineColor(kRed -3);
	}

	if(state == 2){
	gfin->		SetLineColor(kBlue +1 );
	gpre->		SetLineColor(kBlue +1 );
	}

	if(state == 3){
	gfin->		SetLineColor(kTeal+5);
	gpre->		SetLineColor(kTeal+5);
	}

	if(state == 32){
	gfin->		  SetLineColor(kRed+2);
	gpre->		  SetLineColor(kRed+2);
	short ll = 2;
	if( mode == kTCent ) ll = 2;
	gfin->		  SetLineWidth(ll);
	gpre->		  SetLineWidth(ll);
	}

//	gpre->Draw("C");
	gfin->Draw("C");
	if(state !=32){
		leg->SetHeader("#scale[1.1]{#bf{Heidelberg}}");
		leg->AddEntry(gfin, Form("#Upsilon(%dS)", state), "l");
	}
	else{ 
		if( mode == kTPt){
			if(indent)  leg->AddEntry(gfin, "Heidelberg", "l");
			if(!indent) leg->AddEntry(gfin, "Heidelberg", "l");
		}
		if( mode == kTCent){
			if(indent)  leg->AddEntry(gfin, "Heidelberg", "l");
			if(!indent) leg->AddEntry(gfin, "Heidelberg", "l");
		}
	}

	p1->Update();
};