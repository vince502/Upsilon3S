
std::vector<dTransport> get_theory_Transport_comp(string type){
	string name_file = fTransport[type]; 
	std::cout << name_file << std::endl;
	auto get = [&](){
		ifstream textfile(name_file.c_str());
		string sbuf;
		//QTraj : ((range cbin or pT), raa_nom, raa_up, raa_down 
		std::vector< string> vbuf;
		std::vector<dTransport> ttheory;
		int idxDo, idxUp;
		idxDo = 2;
		idxUp = 1;
		if( type.find("re") != std::string::npos){
			if( type.find("1") != std::string::npos){
				idxDo = 2;
				idxUp = 1;
			}
			else if( type.find("2") != std::string::npos){
				idxDo = 4;
				idxUp = 3;
			}
			else if( type.find("3") != std::string::npos){
				idxDo = 6;
				idxUp = 5;
			}
		}
		while(getline(textfile, sbuf) ){
			std::cout << sbuf << std::endl;
			vbuf = parser_symbol(sbuf, " "); //delimieter is a White space
			for( auto &buf : vbuf){
				//if buf is empty, remove it
				if( buf.empty()){
					vbuf.erase(std::remove(vbuf.begin(), vbuf.end(), buf), vbuf.end());
				}
			}
			dTransport dbuf;
			for ( auto buf : vbuf){
				if( type.find("c") != std::string::npos){
					dbuf.Npart = stod(vbuf[0]);
				}
				else{ 
					dbuf.pt = stod(vbuf[0]);
				}
				dbuf.valdo = stod(vbuf[ idxDo]);
				dbuf.valup = stod(vbuf[ idxUp]);
			}
			ttheory.push_back(dbuf);
		}
		return ttheory;
	};
	auto ttheory = get();
	if( type.find("re") != std::string::npos && type.find("p") != std::string::npos){
		name_file = fTransport[type+"_"];
	}
	auto ttheory2 = get();
	//subtract ttheory valdo, valup with ttheory2 valdo, valup
	if( type.find("re") != std::string::npos && type.find("p") != std::string::npos){
		for( int i = 0; i < ttheory.size(); i++){
			ttheory[i].valdo -= ttheory2[i].valdo;
			ttheory[i].valup -= ttheory2[i].valup;
		}
	}
	return ttheory;
};


std::pair<std::map<string, TGraphAsymmErrors*>, TGraphAsymmErrors*> get_theory_Transport(int mode = kTCent, int state =2, bool exclReg = false){
	std::map<string, TGraphAsymmErrors*> map_curve;
	string type;
	if( mode == kTCent) type ="c";
	if( mode == kTPt) type ="p";
	type = Form("%s%ds",type.c_str(), state );
	if( exclReg ) type = Form("%s%s",type.c_str(), "re" );
	std::cout << type.c_str() << std::endl;
	auto res_center = get_theory_Transport_comp(type);
	size_t vsize = res_center.size();
	TGraphAsymmErrors* g_cm		=new TGraphAsymmErrors();	g_cm->SetName("g_up");
	TGraphAsymmErrors* g_cp		=new TGraphAsymmErrors();	g_cp->SetName("g_do");
	map_curve.insert({"valup", g_cp});
	map_curve.insert({"valdo", g_cm});
	TGraphAsymmErrors* g_band = new TGraphAsymmErrors();
	g_band->SetName(Form("gtheoryTransport%dS", state));
	double mm, x;
	for( auto idx : ROOT::TSeqI(vsize) ){
		dTransport ddata = res_center[idx];
		if( mode ==kTCent) {
			x = ddata.Npart;
		}
		if( mode ==kTPt) {
			x = ddata.pt;
		}
		mm = (ddata.valup + ddata.valdo) / 2;

		g_cp->AddPoint( x, ddata.valup);
		g_cm->AddPoint( x, ddata.valdo);
		g_band->AddPoint( x, mm);
		g_band->SetPointError( idx, 0, 0, fabs( mm - ddata.valdo), fabs(mm - ddata.valup));
	}
	return std::make_pair(map_curve, g_band); 

};

void draw_theory_Transport(TPad* p1, TLegend* leg, int mode, int state, bool indent = false, bool exclReg = false, bool onlyCenter= false){
	bool excltmp = exclReg; 
	if(state == 32 ) excltmp = false;
	auto res = get_theory_Transport(mode, state, excltmp);
	std::cout << "Got Data" << std::endl;
	auto gband= res.second;
	auto gcp = res.first["valup"];
	auto gcm = res.first["valdo"];
	if( state == 32 && exclReg == true){
		auto res2 = get_theory_Transport(mode, 2, true);
		auto res3 = get_theory_Transport(mode, 3, true);
		auto gb2 = res2.second;
		auto gb3 = res3.second;
		auto gcp2 = res2.first["valup"];
		auto gcp3 = res3.first["valup"];
		auto gcm2 = res2.first["valdo"];
		auto gcm3 = res3.first["valdo"];
		auto divV = [](TGraphAsymmErrors* a, TGraphAsymmErrors* b, bool propE = false){
			int np;
			TGraphAsymmErrors* res = new TGraphAsymmErrors();
			if( a->GetN() == b->GetN() ) np = a->GetN();
			else{ std::cout << "Number of points not matching!" << std::endl;}
			for( auto idx : ROOT::TSeqI(np) ){
				res->AddPoint( a->GetPointX(idx), a->GetPointY(idx) / b->GetPointY(idx) );
				if(propE){
					double eu = TMath::Sqrt(pow(a->GetErrorYhigh(idx)/b->GetPointY(idx),2) + pow(b->GetErrorYhigh(idx)/a->GetPointY(idx),2));
					double ed = TMath::Sqrt(pow(a->GetErrorYlow(idx)/b->GetPointY(idx),2) + pow(b->GetErrorYlow(idx)/a->GetPointY(idx),2));
					res->SetPointError(idx, 0., 0., ed, eu);
				}
			}
			return res;
		};
		auto setBand = [](TGraphAsymmErrors* t, TGraphAsymmErrors* a, TGraphAsymmErrors* b){
			int np;
			if( a->GetN() == b->GetN() ) np = a->GetN();
			else{ std::cout << "Number of points not matching!" << std::endl;}
			for( auto idx : ROOT::TSeqI(np) ){
					t->SetPointEYhigh( idx, a->GetPointY(idx) - t->GetPointY(idx)   );
					t->SetPointEYlow( idx, t->GetPointY(idx) - b->GetPointY(idx) );
			}
			return;
		};
		gband = divV(gb3, gb2, true);
		gcp = divV(gcp3, gcm2);
		gcm = divV(gcm3, gcp2);
		setBand(gband, gcp, gcm);
		
	}
	p1->cd();

	unsigned int fills = 3335;
	unsigned int regFill = 1001;
	double alph = 1.;
	double alphReg = 0.7;
//	gStyle->SetHatchesSpacing(1);
//	gStyle->SetHatchesLineWidth(1);

//	gband->SetMarkerStyle(kFullCircle);

	gband->SetLineStyle(1);
	gcm->  SetLineStyle(1);
	gcp->  SetLineStyle(1);

	gband->SetLineWidth(2);
	gcm->  SetLineWidth(2);
	gcp->  SetLineWidth(2);

	if(state == 1){
	gband->SetFillColorAlpha(kPink -2 , alph);
	gband->SetFillStyle(fills);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(1.7);
	gband->SetMarkerColor(kBlue- 7);
	gband->SetLineColorAlpha(kRed -3, alph );
	gcm->		SetLineColor(kRed -3);
	gcp->		SetLineColor(kRed -3);
		if(exclReg) gband->SetFillColorAlpha(kOrange +8 , alphReg);
		if(exclReg) gband->SetLineColorAlpha(kOrange +8 , alph);
		if(exclReg) gband->SetFillStyle(regFill);
		if(exclReg) gcm->		SetLineColor(kOrange -3);
		if(exclReg) gcp->		SetLineColor(kOrange -3);
	}

	if(state == 2){
	fills = 3345;
	gband->SetFillColorAlpha(kViolet+7 , alph);
	gband->SetFillStyle(fills);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(1.7);
	gband->SetMarkerColor(kBlue- 7);
	gband->SetLineColorAlpha(kBlue +1, alph );
	gcm->		SetLineColor(kBlue +1 );
	gcp->		SetLineColor(kBlue +1 );
		if(exclReg) gband->SetFillColorAlpha(kAzure -6 , alphReg);
		if(exclReg) gband->SetLineColorAlpha(kAzure -3 , alph);
		if(exclReg) gband->SetFillStyle(regFill);
		if(exclReg) gcm->		SetLineColor(kAzure -3);
		if(exclReg) gcp->		SetLineColor(kAzure -3);
	}

	if(state == 3){
	fills = 3354;
	gband->SetFillColorAlpha(kTeal-5, alph);
	gband->SetFillStyle(fills);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(1.7);
	gband->SetMarkerColor(kTeal+ 5);
	gband->SetLineColor(kTeal+5);
	gcm->		SetLineColor(kTeal+5);
	gcp->		SetLineColor(kTeal+5);
		if(exclReg) gband->SetFillColorAlpha(kSpring -7, alphReg);
		if(exclReg) gband->SetLineColorAlpha(kSpring -7, alph);
		if(exclReg) gband->SetFillStyle(regFill);
		if(exclReg) gcm->		SetLineColor(kSpring +7);
		if(exclReg) gcp->		SetLineColor(kSpring +7);
	}

	if(state == 32){
	fills = 3335;
	gband->SetFillColorAlpha(kRed-7, alph);
	gband->SetFillStyle(fills);
	gband->SetLineColor(kRed-0);
	gband->SetLineWidth(2);
	gband->SetLineStyle(kSolid);
	gband->SetMarkerStyle(22);
	gband->SetMarkerSize(2.2);
	gband->SetMarkerColorAlpha(kRed-4, alph);
	gcm->		  SetLineColor(kRed-4);
	gcp->		  SetLineColor(kRed-4);
	short ll = 2;
	if( mode == kTCent ) ll = 2;
	gcm->		  SetLineWidth(ll);
	gcp->		  SetLineWidth(ll);
		if(exclReg) alphReg = 0.32 ;
		if(exclReg) gband->SetFillColorAlpha(kAzure -2 , alphReg);
		if(exclReg) gband->SetLineColorAlpha(kAzure -6 , alph);
		if(exclReg) gband->SetFillStyle(regFill);
		if(exclReg) gcm->		SetLineColor(kAzure -6);
		if(exclReg) gcp->		SetLineColor(kAzure -6);
	}

	std::string legStyle = "";
	if(onlyCenter){
		gband->Draw("LX");
		legStyle = "l";
	}
	if(!onlyCenter){
		gband->Draw("3");
		if(exclReg) gband->SetLineWidth(0);
		if(!exclReg) gcp->Draw("L");
		if(!exclReg) gcm->Draw("L");
		legStyle = "f";
	}
	if(state !=32){
		leg->SetHeader("#scale[1.1]{#bf{TAMU}}");
		
		if(!exclReg) leg->AddEntry(gband, Form("#Upsilon(%dS)", state), legStyle.c_str());
		if( exclReg) leg->AddEntry(gband, Form("#Upsilon(%dS)", state), legStyle.c_str());
	}
	else{ 
//		if(exclReg){
//			if( mode == kTPt){
//				if(indent)  leg->AddEntry(gband, "TAMU w/o regen.", "f");
//				if(!indent) leg->AddEntry(gband, "TAMU w/o regen.", "f");
//			}
//			if( mode == kTCent){
//				if(indent)  leg->AddEntry(gband, "TAMU w/o regen.", "l");
//				if(!indent) leg->AddEntry(gband, "TAMU w/o regen.", "l");
//			}
//		}
		if(true){
			if( mode == kTPt){
				if(indent)  leg->AddEntry(gband, "TAMU", legStyle.c_str());
				if(!indent) leg->AddEntry(gband, "TAMU", legStyle.c_str());
			}
			if( mode == kTCent){
				if(indent)  leg->AddEntry(gband, "TAMU", "l");
				if(!indent) leg->AddEntry(gband, "TAMU", "l");
			}
		}
	}

	p1->Update();
};