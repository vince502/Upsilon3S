THttpServer* serv= new THttpServer("http:8082");
TCanvas* c1, *c2;

void checkDataEfficiency(int pl = 15, int ph =30, int bpl =0, int bph= 30){
	gStyle->SetEndErrorSize(0);
	TFile* fhandle, *fhandle2, *fhandle3, *fhandle4, *fhandle5;
	//TFile* fmc3 = TFile::Open("/home/vince402/Upsilon3S/BDT/EffCalc/mc_eff_BDT_3S_train_3S_bdtpt0_30_100019111111_y-2.4_2.4_SiMuPt3.5_mass9.6_11.0_vp_0.0000_ID.root");
	//TFile* fmc2 = TFile::Open("/home/vince402/Upsilon3S/BDT/EffCalc/mc_eff_BDT_2S_train_3S_bdtpt0_30_100019111111_y-2.4_2.4_SiMuPt3.5_mass9.3_10.7_vp_0.0000_ID.root");
	TFile* fmc3 = TFile::Open(Form("/home/vince402/Upsilon3S/BDT/EffCalc/mc_eff_BDT_3S_train_3S_bdtpt%d_%d_100019111111_y-2.4_2.4_SiMuPt3.5_mass9.6_11.0_vp_0.0000_ID.root", bpl, bph));
	TFile* fmc2 = TFile::Open(Form("/home/vince402/Upsilon3S/BDT/EffCalc/mc_eff_BDT_2S_train_3S_bdtpt%d_%d_100019111111_y-2.4_2.4_SiMuPt3.5_mass9.3_10.7_vp_0.0000_ID.root", bpl, bph));
	TH3D* hreco3 = (TH3D*) fmc3->Get("hreco");
	TH3D* hreco2 = (TH3D*) fmc2->Get("hreco");

	double scale2s= 0;
	double scale3s =0;

	TGraphAsymmErrors *g2s, *g3s;
	TGraphAsymmErrors *g2s2, *g3s2;
	TGraphAsymmErrors *g2s3, *g3s3;
	TGraphAsymmErrors *g2s4, *g3s4;
	TGraphAsymmErrors *g2s5, *g3s5;
	TGraphAsymmErrors *g2s_eff, *g3s_eff;
	g2s = new TGraphAsymmErrors();
	g3s = new TGraphAsymmErrors();
	g2s2 = new TGraphAsymmErrors();
	g3s2 = new TGraphAsymmErrors();
	g2s3 = new TGraphAsymmErrors();
	g3s3 = new TGraphAsymmErrors();
	g2s4 = new TGraphAsymmErrors();
	g3s4 = new TGraphAsymmErrors();
	g2s5 = new TGraphAsymmErrors();
	g3s5 = new TGraphAsymmErrors();
	g2s_eff = new TGraphAsymmErrors();
	g3s_eff = new TGraphAsymmErrors();

	int pltidx = 0;
	double effscale = 1.1;
	double bdtscore;
	auto fillpoint = [&hreco3, &hreco2, &bdtscore, &pltidx, pl, ph, bpl, bph](TFile* f, TGraphAsymmErrors* g2s, TGraphAsymmErrors* g3s, int idx){
		auto fres = (RooFitResult*) f->Get("fitresult_model_gc_reducedDS");
		auto fpars = fres->floatParsFinal();
		RooRealVar *y3s, *y2s;
		y2s = (RooRealVar*)  &fpars[fpars.index("nSig2S")];
		y3s = (RooRealVar*)  &fpars[fpars.index("nSig3S")];
		double integral3 = hreco3->Integral( (int)(( bdtscore + 1.0000)* 10000) + 1, 20000, pl+1, ph, 1, 36);
		double integral2 = hreco2->Integral( (int)(( bdtscore + 1.0000)* 10000) + 1, 20000, pl+1, ph, 1, 36);
		g2s->AddPoint( bdtscore, y2s->getVal()/ integral2);
		g3s->AddPoint( bdtscore, y3s->getVal()/ integral3);
		g2s->SetPointError(pltidx, 0,0, y2s->getError() / integral2, y2s->getError()/ integral2);
		g3s->SetPointError(pltidx, 0,0, y3s->getError() / integral3, y2s->getError()/ integral3);
	};
	auto fillgraph = [&](int idx){
		fhandle  = TFile::Open(Form("/home/vince402/Upsilon3S/Yield/Yield_3S_Sig3S_200019111111_GCscan_CB3_EE_pt_%d-%d_rap_-24-24_cbin_0-181_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-1.0000_bdtpt_%d_%d_vp0.0000.root",pl, ph, bdtscore, bpl, bph));
		fhandle2 = TFile::Open(Form("/home/vince402/Upsilon3S/Yield/Yield_3S_Sig3S_200019111111_GCscan_CB2G_EE_pt_%d-%d_rap_-24-24_cbin_0-181_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-1.0000_bdtpt_%d_%d_vp0.0000.root",pl, ph, bdtscore, bpl, bph));
		fhandle3 = TFile::Open(Form("/home/vince402/Upsilon3S/Yield/Yield_3S_Sig3S_200019111111_GCscan_CB3_EX_pt_%d-%d_rap_-24-24_cbin_0-181_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-1.0000_bdtpt_%d_%d_vp0.0000.root",pl, ph, bdtscore, bpl, bph));
		fhandle4 = TFile::Open(Form("/home/vince402/Upsilon3S/Yield/Yield_3S_Sig3S_200019111111_GCscan_CB3_CC1_pt_%d-%d_rap_-24-24_cbin_0-181_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-1.0000_bdtpt_%d_%d_vp0.0000.root",pl, ph, bdtscore, bpl, bph));
		fhandle5 = TFile::Open(Form("/home/vince402/Upsilon3S/Yield/Yield_3S_Sig3S_200019111111_GCscan_CB3_CC2_pt_%d-%d_rap_-24-24_cbin_0-181_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-1.0000_bdtpt_%d_%d_vp0.0000.root",pl, ph, bdtscore, bpl, bph));

		fillpoint(fhandle, g2s, g3s, idx);
		fhandle->Close();
		fillpoint(fhandle2, g2s2, g3s2, idx);
		fhandle2->Close();
		fillpoint(fhandle3, g2s3, g3s3, idx);
		fhandle3->Close();
		fillpoint(fhandle4, g2s4, g3s4, idx);
		fhandle4->Close();
		fillpoint(fhandle5, g2s5, g3s5, idx);
		fhandle5->Close();
	};

	for( auto idx : ROOT::TSeqI(200/5) ){
		bdtscore = 0.05 * ((double) idx) -1 ;
		if( (idx %50) == 0 ) std::cout << "counting idx : "<< idx << std::endl;
		if(bdtscore == -1 ) continue;
		if(bdtscore > 0.90 ) break;
		fillgraph(idx);

//		std::cout << integral2 << std::endl;
//		if(scale2s ==0 ) scale2s = integral2;
//		if(scale3s ==0 ) scale3s = integral3;
//
////		g3s_eff->AddPoint( bdtscore, effscale* 850.*(integral3/scale3s));
////		g2s_eff->AddPoint( bdtscore, effscale* 3000.*(integral2/scale2s));
//		g3s_eff->AddPoint( bdtscore, effscale* 300.*(integral3/scale3s));
//		g2s_eff->AddPoint( bdtscore, effscale* 1000.*(integral2/scale2s));
		
		pltidx++;
	}
	std::cout << "Getting BDT train efficiency" << std::endl;

	std::string name_input = Form("/home/vince402/Upsilon3S/BDT/BDTResult/BDTresultY3S_100019111111_BLIND.root");
	TFile* file_bdtres = TFile::Open(name_input.c_str());
	string name_h_effS_1 = Form("data/Y%dSpt%dto%d/dataset1/Method_BDT/BDT/MVA_BDT_effS", 3, bpl, bph);
	TH1D* h_effS_1 = (TH1D*) file_bdtres->Get(name_h_effS_1.c_str());
	h_effS_1->Scale( 3000);

	g2s->SetMarkerSize(2);
	g3s->SetMarkerSize(2);
	g2s->SetMarkerStyle(kFullCircle);
	g3s->SetMarkerStyle(kFullCircle);

	g2s2->SetMarkerSize(2);
	g3s2->SetMarkerSize(2);
	g2s2->SetMarkerColor(kRed+2);
	g3s2->SetMarkerColor(kRed+2);
	g2s2->SetMarkerStyle(kFullSquare);
	g3s2->SetMarkerStyle(kFullSquare);

	g2s3->SetMarkerSize(2);
	g3s3->SetMarkerSize(2);
	g2s3->SetMarkerColor(kBlue);
	g3s3->SetMarkerColor(kBlue);
	g2s3->SetMarkerStyle(kFullSquare);
	g3s3->SetMarkerStyle(kFullSquare);

	g2s4->SetMarkerSize(2);
	g3s4->SetMarkerSize(2);
	g2s4->SetMarkerColor(kTeal+3);
	g3s4->SetMarkerColor(kTeal+3);
	g2s4->SetMarkerStyle(kFullSquare);
	g3s4->SetMarkerStyle(kFullSquare);

	g2s5->SetMarkerSize(2);
	g3s5->SetMarkerSize(2);
	g2s5->SetMarkerColor(kYellow+3);
	g3s5->SetMarkerColor(kYellow+3);
	g2s5->SetMarkerStyle(kFullSquare);
	g3s5->SetMarkerStyle(kFullSquare);
	c1= new TCanvas();

	c1->cd();
	g2s->Draw("APE");
	g2s2->Draw("PE");
	g2s3->Draw("PE");
	g2s4->Draw("PE");
	g2s5->Draw("PE");
//	g2s_eff->Draw("L");
//	h_effS_1->Draw("same");

	
	c2= new TCanvas();

	c2->cd();
	g3s->Draw("APE");
	g3s2->Draw("PE");
	g3s3->Draw("PE");
	g3s4->Draw("PE");
	g3s5->Draw("PE");
//	g3s_eff->Draw("L");
}
