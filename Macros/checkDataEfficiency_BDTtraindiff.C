THttpServer* serv= new THttpServer("http:8082");
TCanvas* c1, *c2;

void checkDataEfficiency_BDTtraindiff(){
	gStyle->SetEndErrorSize(0);
	TFile* fhandle;
	TFile* fmc3 = TFile::Open("/home/vince402/Upsilon3S/BDT/EffCalc/mc_eff_BDT_3S_train_3S_bdtpt0_30_100019111111_y-2.4_2.4_SiMuPt3.5_mass9.6_11.0_vp_0.0000_ID.root");
	TFile* fmc2 = TFile::Open("/home/vince402/Upsilon3S/BDT/EffCalc/mc_eff_BDT_2S_train_3S_bdtpt0_30_100019111111_y-2.4_2.4_SiMuPt3.5_mass9.3_10.7_vp_0.0000_ID.root");
	TH3D* hreco3 = (TH3D*) fmc3->Get("hreco");
	TH3D* hreco2 = (TH3D*) fmc2->Get("hreco");

	double scale2s= 0;
	double scale3s =0;

	TGraphAsymmErrors *g2s, *g3s;
	TGraphAsymmErrors *g2s_eff, *g3s_eff;
	g2s = new TGraphAsymmErrors();
	g3s = new TGraphAsymmErrors();
	g2s_eff = new TGraphAsymmErrors();
	g3s_eff = new TGraphAsymmErrors();
	double bdtscore;
	{
		fhandle = TFile::Open(Form("/home/vince402/Upsilon3S/Yield/Yield_3S_Sig3S_200019111111_GCscan_CB3_EE_pt_0-30_rap_-24-24_cbin_0-181_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-1.0000_bdtpt_0_30_vp0.0000.root", bdtscore));
		auto fres = (RooFitResult*) fhandle->Get("fitresult_model_gc_reducedDS");
		auto fpars = fres->floatParsFinal();
		RooRealVar *y3s, *y2s;
		y2s = (RooRealVar*)  &fpars[fpars.index("nSig2S")];
		y3s = (RooRealVar*)  &fpars[fpars.index("nSig3S")];
		g2s->AddPoint( bdtscore, y2s->getVal());
		g3s->AddPoint( bdtscore, y3s->getVal());
		g2s->SetPointError(0, 0,0, y2s->getError(), y2s->getError());
		g3s->SetPointError(0, 0,0, y3s->getError(), y2s->getError());
		fhandle->Close();
	}

	{
		fhandle = TFile::Open(Form("/home/vince402/Upsilon3S/Yield/Yield_3S_Sig3S_200019111111_GCscan_CB3_EE_pt_0-30_rap_-24-24_cbin_0-181_MupT3p5_Trig_S13_SW0_BDT1_cut%.4f-1.0000_bdtpt_0_30_vp0.0000.root", bdtscore));
		auto fres = (RooFitResult*) fhandle->Get("fitresult_model_gc_reducedDS");
		auto fpars = fres->floatParsFinal();
		RooRealVar *y3s, *y2s;
		y2s = (RooRealVar*)  &fpars[fpars.index("nSig2S")];
		y3s = (RooRealVar*)  &fpars[fpars.index("nSig3S")];
		g2s->AddPoint( bdtscore, y2s->getVal());
		g3s->AddPoint( bdtscore, y3s->getVal());
		g2s->SetPointError(1, 0,0, y2s->getError(), y2s->getError());
		g3s->SetPointError(1, 0,0, y3s->getError(), y2s->getError());
		fhandle->Close();
	}

	int pltidx = 0;
	double effscale = 1.1;
	for( auto idx : ROOT::TSeqI(20) ){
		if( (idx %50) == 0 ) std::cout << "counting idx : "<< idx << std::endl;
		double bdtscore = 0.1 * ((double) idx) -1 ;
		if(bdtscore == -1 ) continue;
		if(bdtscore > 0.57 ) continue;

		double integral3 = hreco3->Integral( (int)(( bdtscore + 1.0000)* 10000) + 1, 20000, 1, 30, 1, 36);
		double integral2 = hreco2->Integral( (int)(( bdtscore + 1.0000)* 10000) + 1, 20000, 1, 30, 1, 36);
//		std::cout << integral2 << std::endl;
		if(scale2s ==0 ) scale2s = integral2;
		if(scale3s ==0 ) scale3s = integral3;

		g3s_eff->AddPoint( bdtscore, effscale* 850.*(integral3/scale3s));
		g2s_eff->AddPoint( bdtscore, effscale* 3000.*(integral2/scale2s));
		
		pltidx++;
	}
	std::cout << "Getting BDT train efficiency" << std::endl;

	std::string name_input = Form("/home/vince402/Upsilon3S/BDT/BDTResult/BDTresultY3S_100019111111_BLIND.root");
	TFile* file_bdtres = TFile::Open(name_input.c_str());
	string name_h_effS_1 = Form("data/Y%dSpt%dto%d/dataset1/Method_BDT/BDT/MVA_BDT_effS", 3, 0, 30);
	TH1D* h_effS_1 = (TH1D*) file_bdtres->Get(name_h_effS_1.c_str());
	h_effS_1->Scale( 3000);

	g2s->SetMarkerSize(2);
	g3s->SetMarkerSize(2);
	g2s->SetMarkerStyle(kFullCircle);
	g3s->SetMarkerStyle(kFullCircle);
	c1= new TCanvas();

	c1->cd();
	g2s->Draw("APE");
	g2s_eff->Draw("L");
//	h_effS_1->Draw("same");

	
	c2= new TCanvas();

	c2->cd();
	g3s->Draw("APE");
	g3s_eff->Draw("L");
}
