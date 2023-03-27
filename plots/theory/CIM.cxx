
std::pair<std::map<string, TGraphAsymmErrors*>, TGraphAsymmErrors*> get_theory_CIMnCTEQ15(int mode = kTCent, int state =32){
	std::map<string, TGraphAsymmErrors*> map_curve;
	string type;
	if( mode == kTCent) type ="c";
	if( mode == kTPt) return {{{"nan", nullptr }}, nullptr};
	TGraphAsymmErrors* g_center	=new TGraphAsymmErrors();	g_center->SetName("g_nom");
	TGraphAsymmErrors* g_cm		=new TGraphAsymmErrors();	g_cm->SetName("g_up");
	TGraphAsymmErrors* g_cp		=new TGraphAsymmErrors();	g_cp->SetName("g_do");
	map_curve.insert({"nominal", g_center});
	map_curve.insert({"errup", g_cp});
	map_curve.insert({"errdo", g_cm});
	double xl, xh, x;
	std::vector<dCIMnCTEQ15> vCIMnCTEQ15 = get_CIMnCTEQ15();
	for( auto data : vCIMnCTEQ15 ){
		std::cout << Form("Data[CIMnCTEQ15] Npart, val, min, max: %.1f %.3f %.3f %.3f", data.Npart, data.dr_val, data.dr_min, data.dr_max) <<std::endl; 
		if(state == 1){
		g_center->AddPoint(data.Npart, data.raa1s_val);
		double errup = quadsum( data.raa1s_val - data.raa1s_min, data.raa1s_val - data.raa1s_min2);
		double errdo = quadsum( data.raa1s_val - data.raa1s_max, data.raa1s_val - data.raa1s_max2);
		g_center->SetPointError(data.idx, 0,0, errup, errdo);
		g_cm->AddPoint(data.Npart, data.raa1s_min);
		g_cp->AddPoint(data.Npart, data.raa1s_max);
		}
		if(state == 2){
		g_center->AddPoint(data.Npart, data.raa2s_val);
		double errup = quadsum( data.raa2s_val - data.raa2s_min, data.raa2s_val - data.raa2s_min2);
		double errdo = quadsum( data.raa2s_val - data.raa2s_max, data.raa2s_val - data.raa2s_max2);
		g_center->SetPointError(data.idx, 0,0, errup, errdo);
		g_cm->AddPoint(data.Npart, data.raa2s_min);
		g_cp->AddPoint(data.Npart, data.raa2s_max);
		}
		if(state == 3){
		g_center->AddPoint(data.Npart, data.raa3s_val);
		double errup = quadsum( data.raa3s_val - data.raa3s_min, data.raa3s_val - data.raa3s_min2);
		double errdo = quadsum( data.raa3s_val - data.raa3s_max, data.raa3s_val - data.raa3s_max2);
		g_center->SetPointError(data.idx, 0,0, errup, errdo);
		g_cm->AddPoint(data.Npart, data.raa3s_min);
		g_cp->AddPoint(data.Npart, data.raa3s_max);
		}
		if(state == 32){
		g_center->AddPoint(data.Npart, data.dr_val);
		g_center->SetPointError(data.idx, 0,0, data.dr_val - data.dr_min, data.dr_max - data.dr_val);
		g_cm->AddPoint(data.Npart, data.dr_min);
		g_cp->AddPoint(data.Npart, data.dr_max);
		}
	}
	return std::make_pair(map_curve, nullptr); 

};



void draw_theory_CIMnCTEQ15(TPad* p1, TLegend* leg, int mode, int state=32, bool indent = false){
	auto res = get_theory_CIMnCTEQ15(mode,state);
	auto gcc = res.first["nominal"];
	auto gcp = res.first["errup"];
	auto gcm = res.first["errdo"];
	p1->cd();

	unsigned int fills = 3144;
	double alph = 0.65;
//	gStyle->SetHatchesSpacing(0.3);
//	gStyle->SetHatchesLineWidth(1);

	gcc->SetMarkerStyle(kFullCircle);

	gcc->SetLineStyle(1);
	gcc->  SetLineStyle(1);
	gcm->  SetLineStyle(1);
	gcp->  SetLineStyle(1);

	gcc->SetLineWidth(2);
	gcc->  SetLineWidth(2);
	gcm->  SetLineWidth(2);
	gcp->  SetLineWidth(2);

	if(state == 1){

	gcc->SetFillColorAlpha(kRed - 7 , alph);
	gcc->SetFillStyle(fills);
	gcc->SetMarkerStyle(22);
	gcc->SetMarkerSize(1.7);
	gcc->SetMarkerColor(kBlue- 7);
	gcc->  SetLineColorAlpha(kPink -3, alph );
	gcm->		SetLineColor(kPink -3 );
	gcp->		SetLineColor(kPink -3 );
	}

	if(state == 2){
	fills = 3145;
	gcc->SetFillColorAlpha(kViolet+7 , alph);
	gcc->SetFillStyle(fills);
	gcc->SetMarkerStyle(22);
	gcc->SetMarkerSize(1.7);
	gcc->SetMarkerColor(kBlue- 7);
	gcc->SetLineColorAlpha(kBlue +1, alph );
	gcm->		SetLineColor(kBlue +1 );
	gcp->		SetLineColor(kBlue +1 );
	}

	if(state == 3){
	fills = 3154;
	gcc->SetFillColorAlpha(kTeal-5, alph);
	gcc->SetFillStyle(fills);
	gcc->SetMarkerStyle(22);
	gcc->SetMarkerSize(1.7);
	gcc->SetMarkerColor(kTeal+ 5);
	gcc->SetLineColorAlpha(kTeal+5, alph);
	gcm->		SetLineColor(kTeal+5);
	gcp->		SetLineColor(kTeal+5);
	}

	if(state == 32){
	gcc->SetFillColorAlpha(kPink + 1, alph);
	gcc->SetFillStyle(fills);
	gcc->SetLineColor(kOrange+7);
	gcc->SetLineWidth(2);
	gcc->SetLineStyle(kDashed);
	gcc->SetMarkerStyle(22);
	gcc->SetMarkerSize(2.2);
	gcc->SetMarkerColorAlpha(kMagenta -3 , alph);
	gcc->		  SetLineColor(kMagenta-3);
	gcm->		  SetLineColor(kOrange-3);
	gcp->		  SetLineColor(kOrange-3);
	}
	
	gcc->Draw("3L");
//	gcc->Draw("E");
//	gcp->Draw("L");
//	gcm->Draw("L");
	if(state != 32){
		leg->SetHeader("#scale[1.1]{#bf{CIM + nCTEQ15}}", "lf");
		leg->AddEntry(gcc,Form("#Upsilon(%dS)",state), "lf");
	}
	else{
		if(indent)  leg->AddEntry(gcc, "#splitline{CIM}{ + nCTEQ15}", "lf");
		if(!indent) leg->AddEntry(gcc, "CIM + nCTEQ15", "lf");
	}
	p1->Update();
}