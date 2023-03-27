
std::vector<dEPPS16> get_theory_EPPS16_comp(string type){
	string name_file = fEPPS16[type]; 
	ifstream textfile(name_file.c_str());
	string sbuf;
	
	//EPPS16 : (Npart or pT), RAA1S, RAA2S, RAA3S, RAA1P, RAA23S RAA3S/RAA2S
	std::vector< string> vbuf;
	std::vector<dEPPS16> ttheory;
	string bintype;
	bool firstline = true;
	while(getline(textfile, sbuf) ){
		vbuf = parser_symbol(sbuf, " ");
		dEPPS16 dbuf;
		if(firstline){
			bintype =vbuf[0];
		}
		if( !firstline){
			for ( auto buf : vbuf){
				if( strcmp(bintype.c_str(), "Npart")== 0){
					dbuf.Npart = stod(vbuf[0]);
				}
				else{ dbuf.pT = stod(vbuf[0]);}
				dbuf.raa1s = stod(vbuf[1]);
				dbuf.raa2s = stod(vbuf[2]);
				dbuf.raa3s = stod(vbuf[3]);
				dbuf.raa1p = stod(vbuf[4]);
				dbuf.raa23s = stod(vbuf[5]);
				dbuf.raa3over2s = stod(vbuf[6]);

			}
			ttheory.push_back(dbuf);
		}
		if(firstline){
			firstline = false;
		}
	}
	return ttheory;
};


//#if defined quadsum
std::pair<std::map<string, TGraphAsymmErrors*>, TGraphAsymmErrors*> get_theory_EPPS16(int mode = kTCent, int state =2){
	std::map<string, TGraphAsymmErrors*> map_curve;
	string type;
	if( mode == kTCent) type ="N";
	if( mode == kTPt) type ="p";
	auto res_center = get_theory_EPPS16_comp(Form("%scc",type.c_str() ));
	auto res_cp = 	  get_theory_EPPS16_comp(Form("%s+c",type.c_str() ));
	auto res_cm = 	  get_theory_EPPS16_comp(Form("%s-c",type.c_str() ));
	auto res_pc = 	  get_theory_EPPS16_comp(Form("%sc+",type.c_str() ));
	auto res_mc = 	  get_theory_EPPS16_comp(Form("%sc-",type.c_str() ));
	size_t vsize = res_center.size();
	TGraphAsymmErrors* g_center	=new TGraphAsymmErrors();	g_center->SetName("gcc");
	TGraphAsymmErrors* g_cm		=new TGraphAsymmErrors();	g_cm->SetName("gc-");
	TGraphAsymmErrors* g_cp		=new TGraphAsymmErrors();	g_cp->SetName("gc+");
	map_curve.insert({"nPDF0", g_center});
	map_curve.insert({"nPDF+", g_cp});
	map_curve.insert({"nPDF-", g_cm});
	TGraphAsymmErrors* g_theory = new TGraphAsymmErrors();
	g_theory->SetName("gtheoryEPPS16");
	for( auto idx : ROOT::TSeqI(vsize) ){
		dEPPS16 dcc = res_center[idx];
		dEPPS16 dcp = res_cp[idx];
		dEPPS16 dcm = res_cm[idx];
		dEPPS16 dpc = res_pc[idx];
		dEPPS16 dmc = res_mc[idx];
		if( mode == kTCent){
			if( state == 1){
				g_center->AddPoint( dcc.Npart, dcc.raa1s);
				g_cp->AddPoint( dcp.Npart, dcp.raa1s);
				g_cm->AddPoint( dcm.Npart, dcm.raa1s);
				g_theory->AddPoint( dcc.Npart, dcc.raa1s);
				double qu = quadsum(dcc.raa1s - dmc.raa1s, dcc.raa1s - dcm.raa1s);
				double qd = quadsum(dcc.raa1s - dmc.raa1s, dcc.raa1s -dcm.raa1s);
//				g_theory->SetPointError( idx, 0,0, dcc.raa1s - dmc.raa1s, dpc.raa1s - dcc.raa1s);
				g_theory->SetPointError( idx, 0,0, qd, qu);
			}
			if( state == 2){
				g_center->AddPoint( dcc.Npart, dcc.raa2s);
				g_cp->AddPoint( dcp.Npart, dcp.raa2s);
				g_cm->AddPoint( dcm.Npart, dcm.raa2s);
				g_theory->AddPoint( dcc.Npart, dcc.raa2s);
				double qu = quadsum(dcc.raa2s - dmc.raa2s, dcc.raa2s - dcm.raa2s);
				double qd = quadsum(dcc.raa2s - dmc.raa2s, dcc.raa2s -dcm.raa2s);
//				g_theory->SetPointError( idx, 0,0, dcc.raa2s - dmc.raa2s, dpc.raa2s - dcc.raa2s);
				g_theory->SetPointError( idx, 0,0, qd, qu);
			}
			if( state == 3){
				g_center->AddPoint( dcc.Npart, dcc.raa3s);
				g_cp->AddPoint( dcp.Npart, dcp.raa3s);
				g_cm->AddPoint( dcm.Npart, dcm.raa3s);
				g_theory->AddPoint( dcc.Npart, dcc.raa3s);
				double qu = quadsum(dcc.raa3s - dmc.raa3s, dcc.raa3s - dcm.raa3s);
				double qd = quadsum(dcc.raa3s - dmc.raa3s, dcc.raa3s -dcm.raa3s);
//				g_theory->SetPointError( idx, 0,0, dcc.raa3s - dmc.raa3s, dpc.raa3s - dcc.raa3s);
				g_theory->SetPointError( idx, 0,0, qd, qu);
			}
			if( state == 4){
				g_center->AddPoint( dcc.Npart, dcc.raa3over2s);
				g_cp->AddPoint( dcp.Npart, dcp.raa3over2s);
				g_cm->AddPoint( dcm.Npart, dcm.raa3over2s);
				g_theory->AddPoint( dcc.Npart, dcc.raa3over2s);
				double qu = quadsum(dcc.raa3over2s - dmc.raa3over2s, dcc.raa3over2s - dcm.raa3over2s);
				double qd = quadsum(dcc.raa3over2s - dmc.raa3over2s, dcc.raa3over2s -dcm.raa3over2s);
//				g_theory->SetPointError( idx, 0,0, dcc.raa3over2s - dmc.raa3over2s, dpc.raa3over2s - dcc.raa3over2s);
				g_theory->SetPointError( idx, 0,0, qd, qu);
			}
		}
		if( mode == kTPt){
			double binW = ptBinWidth_EPPS16(dcc.pT);
			if( state == 1){
				g_center->AddPoint( dcc.pT, dcc.raa1s);
				g_cp->AddPoint( dcp.pT, dcp.raa1s);
				g_cm->AddPoint( dcm.pT, dcm.raa1s);
				g_center->	SetPointError( idx, binW, binW, 0, 0);
				g_cp->		SetPointError( idx, binW, binW, 0, 0);
				g_cm->		SetPointError( idx, binW, binW, 0, 0);
				g_theory->AddPoint( dcc.pT, dcc.raa1s);
				double qu = quadsum(dcc.raa1s - dmc.raa1s, dcc.raa1s - dcm.raa1s);
				double qd = quadsum(dcc.raa1s - dmc.raa1s, dcc.raa1s -dcm.raa1s);
//				g_theory->SetPointError( idx, binW,binW, dcc.raa1s - dmc.raa1s, dpc.raa1s - dcc.raa1s);
				g_theory->SetPointError( idx, binW,binW, qd, qu);
			}
			if( state == 2){
				g_center->AddPoint( dcc.pT, dcc.raa2s);
				g_cp->AddPoint( dcp.pT, dcp.raa2s);
				g_cm->AddPoint( dcm.pT, dcm.raa2s);
				g_center->	SetPointError( idx, binW, binW, 0, 0);
				g_cp->		SetPointError( idx, binW, binW, 0, 0);
				g_cm->		SetPointError( idx, binW, binW, 0, 0);
				g_theory->AddPoint( dcc.pT, dcc.raa2s);
				double qu = quadsum(dcc.raa2s - dmc.raa2s, dcc.raa2s - dcm.raa2s);
				double qd = quadsum(dcc.raa2s - dmc.raa2s, dcc.raa2s -dcm.raa2s);
//				g_theory->SetPointError( idx, binW,binW, dcc.raa2s - dmc.raa2s, dpc.raa2s - dcc.raa2s);
				g_theory->SetPointError( idx, binW,binW, qd, qu);
			}
			if( state == 3){
				g_center->AddPoint( dcc.pT, dcc.raa3s);
				g_cp->AddPoint( dcp.pT, dcp.raa3s);
				g_cm->AddPoint( dcm.pT, dcm.raa3s);
				g_center->	SetPointError( idx, binW, binW, 0, 0);
				g_cp->		SetPointError( idx, binW, binW, 0, 0);
				g_cm->		SetPointError( idx, binW, binW, 0, 0);
				g_theory->AddPoint( dcc.pT, dcc.raa3s);
				double qu = quadsum(dcc.raa3s - dmc.raa3s, dcc.raa3s - dcm.raa3s);
				double qd = quadsum(dcc.raa3s - dmc.raa3s, dcc.raa3s -dcm.raa3s);
//				g_theory->SetPointError( idx, binW,binW, dcc.raa3s - dmc.raa3s, dpc.raa3s - dcc.raa3s);
				g_theory->SetPointError( idx, binW,binW, qd, qu);
			}
			if( state == 4){
				g_center->AddPoint( dcc.pT, dcc.raa3over2s);
				g_cp->AddPoint( dcp.pT, dcp.raa3over2s);
				g_cm->AddPoint( dcm.pT, dcm.raa3over2s);
				g_center->	SetPointError( idx, binW, binW, 0, 0);
				g_cp->		SetPointError( idx, binW, binW, 0, 0);
				g_cm->		SetPointError( idx, binW, binW, 0, 0);
				g_theory->AddPoint( dcc.pT, dcc.raa3over2s);
				double qu = quadsum(dcc.raa3over2s - dmc.raa3over2s, dcc.raa3over2s - dcm.raa3over2s);
				double qd = quadsum(dcc.raa3over2s - dmc.raa3over2s, dcc.raa3over2s -dcm.raa3over2s);
//				g_theory->SetPointError( idx, binW,binW, dcc.raa3over2s - dmc.raa3over2s, dpc.raa3over2s - dcc.raa3over2s);
				g_theory->SetPointError( idx, binW,binW, qd, qu);
			}
		}

	}
	return std::make_pair(map_curve, g_theory); 

};


void draw_theory_EPPS16(TPad* p1, TLegend* leg, int mode, int state, bool indent = false){
	auto res = get_theory_EPPS16(mode, state);
	auto gtheory= res.second;
	auto gcc = res.first["nPDF0"];
	auto gcp = res.first["nPDF+"];
	auto gcm = res.first["nPDF-"];
	p1->cd();

	gtheory->SetMarkerStyle(kFullCircle);

	gtheory->SetLineStyle(2);
	gcc->SetLineStyle(2);
	gcm->SetLineStyle(2);
	gcp->SetLineStyle(2);

	gtheory->SetLineWidth(2);
	gcc->SetLineWidth(2);
	gcm->SetLineWidth(2);
	gcp->SetLineWidth(2);

	unsigned int fills = 3172;
	double alph = 0.65;
//	gStyle->SetHatchesSpacing(0.3);
//	gStyle->SetHatchesLineWidth(1);

	if(state == 1){
//	gtheory->SetFillColorAlpha(kAzure-5, alph);
	gtheory->SetFillColorAlpha(kRed-9, alph);
	gtheory->SetFillStyle(fills);
	gtheory->SetLineColor(kRed -4);
	gcc->	 SetLineColor(kRed -4);
	gcm->	 SetLineColor(kRed -4);
	gcp->	 SetLineColor(kRed -4);
	}

	if(state == 2){
	fills = 3125;
//	gtheory->SetFillColorAlpha(kAzure-5, alph);
	gtheory->SetFillColorAlpha(kViolet+6, alph);
	gtheory->SetFillStyle(fills);
	gtheory->SetLineColor(kViolet+8);
	gcc->	 SetLineColor(kViolet+8);
	gcm->	 SetLineColor(kViolet+8);
	gcp->	 SetLineColor(kViolet+8);
	}

	if(state == 3){
	fills = 3152;
	gtheory->SetFillColorAlpha(kSpring-2, alph);
	gtheory->SetFillStyle(fills);
	gtheory->SetLineColor(kSpring-6);
	gcc->	 SetLineColor(kSpring-6);
	gcm->	 SetLineColor(kSpring-6);
	gcp->	 SetLineColor(kSpring-6);
	gcc->SetLineWidth(1);
	gcm->SetLineWidth(1);
	gcp->SetLineWidth(1);
	}

	if(state == 4){
	gtheory->SetFillColorAlpha(kBlue-9, alph);
	gtheory->SetLineColor(kBlue-4);
	gtheory->SetFillStyle(fills);
//	gtheory->SetLineWidth(0);
	gcc->SetLineColor(kBlue-4);
	gcm->SetLineColor(kBlue-4);
	gcp->SetLineColor(kBlue-4);
	gcc->SetLineWidth(1);
	gcm->SetLineWidth(1);
	gcp->SetLineWidth(1);
	}

	if( mode == kTCent){
	gtheory->Draw("3");
	gcc->Draw("L");
//	gcp->Draw("L");
//	gcm->Draw("L");
	}

	if( mode == kTPt){
	gtheory->Draw("2");
	gcc->Draw("E");
//	gcp->Draw("E");
//	gcm->Draw("E");
	}

	if(state !=4){
		leg->SetHeader("#scale[1.1]{#bf{Coupled Boltzmann}}");
		leg->AddEntry(&*gtheory, Form("#Upsilon(%dS)", state), "lf");
	}
	else {
		if(indent)  leg->AddEntry(&*gtheory, "#splitline{Coupled}{Boltzmann}", "lf");
		if(!indent) leg->AddEntry(&*gtheory, "Coupled Boltzmann", "lf");
	}
	p1->Update();
}