#include "../.workdir.h"
#include "../CMS_lumi_square.C"

void DrawSideRegionAux(){
//	ROOT::EnableImplicitMT();
	TFile* fd 	= TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_10000000016.root",workdir.Data()) );
	TFile* fmc3 = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_10000000016_MC.root",workdir.Data()) );
	TFile* fmc2 = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_10000000016_MC_2S.root",workdir.Data()) );

	TTree* td = (TTree*) fd->Get("tree");
	TTree* tmc3 = (TTree*) fmc3->Get("tree");
	TTree* tmc2 = (TTree*) fmc2->Get("tree");

	//
	double mass;
	double dxy1, dxy2, dz1, dz2, pt1, pt2;
	double dipt, y;
	double qvp;
	double phi1, phi2, eta1, eta2;
	int ntrk1, ntrk2, npix1, npix2;
	std::map<string, double> objs;
	auto setthistree = [&](TTree* t){
		t->SetBranchAddress("mass", &mass);
		t->SetBranchAddress("pt", &dipt);
		t->SetBranchAddress("y", &y);
		t->SetBranchAddress("QQVtxProb", &qvp);
		t->SetBranchAddress("dxy1", &dxy1);
		t->SetBranchAddress("dxy2", &dxy2);

		t->SetBranchAddress("dz1", &dz1);
		t->SetBranchAddress("dz2", &dz2);

		t->SetBranchAddress("pt1", &pt1);
		t->SetBranchAddress("pt2", &pt2);

		t->SetBranchAddress("phi1", &phi1);
		t->SetBranchAddress("phi2", &phi2);
		t->SetBranchAddress("eta1", &eta1);
		t->SetBranchAddress("eta2", &eta2);

		t->SetBranchAddress("nTrkWMea1", &ntrk1);
		t->SetBranchAddress("nTrkWMea2", &ntrk2);

		t->SetBranchAddress("nPixWMea1", &npix1);
		t->SetBranchAddress("nPixWMea2", &npix2);
		return;
	};

	auto isHBSMu = [&](){
		if( dxy1 < 0.3 && dxy2 < 0.3 && dz1 < 20 && dz2 < 20 && pt1 >3.5 && pt2 > 3.5 && ntrk1 > 5 && ntrk2 > 5 && npix1 > 0 && npix2 > 0 ) return true;
		else return false;
	};
	

	auto getVarHist = [&](TTree *t, std::map<string, TH1D* > vhp ){
		setthistree(t);
		auto blist = t->GetListOfBranches();
		for(auto item : vhp){
		if(blist->FindObject(item.first.c_str() ) ) t->SetBranchAddress(item.first.c_str(), &objs[item.first]);
		}
		long nidx = t->GetEntries();
		for( auto idx : ROOT::TSeqL(nidx) ) {
			if( (idx % 10000 ) ==0 ) std::cout << "event : "<< idx << std::endl;
			t->GetEntry(idx);
			if ( isHBSMu() ){
				for(auto item : vhp){
					if( strcmp(item.first.c_str() , "deta") ==0 )  objs[item.first] = fabs(eta1 - eta2);
					if( strcmp(item.first.c_str() , "dipt") ==0 )  objs[item.first] = dipt;
					if( strcmp(item.first.c_str() , "diy") ==0 )   objs[item.first] = y;
					if( strcmp(item.first.c_str() , "dphi") ==0 ){ objs[item.first] = min( fabs(phi1 - phi2), 2*TMath::Pi() - fabs(phi1-phi2) );}//std::cout << objs[item.first] << "   " << std::endl; }
					if( strcmp(item.first.c_str() , "dR") ==0 ){ objs[item.first] = TMath::Sqrt( TMath::Power( fabs(eta1 - eta2), 2 ) + TMath::Power(min( fabs(phi1 - phi2), 2*TMath::Pi() - fabs(phi1 - phi2) ), 2 ));  }
					if (string(item.second->GetName()).find("dat") != std::string::npos){
						if (string(item.second->GetName()).find("left") != std::string::npos){
				//			if(mass <8.6) item.second->Fill(objs[item.first]);
						}
//						else if (string(item.second->GetName()).find("right") != std::string::npos){
				//			if(mass >10.7) item.second->Fill(objs[item.first]);
//						}
						else{
//							if(mass >8 && mass <14) item.second->Fill(objs[item.first]);

							if(qvp > 0.01 && ((mass >8 && mass<8.6)|| (mass> 10.7 && mass <14) )){
								if( strcmp(item.first.c_str() , "mueta") ==0 ){ objs[item.first] = eta1;item.second->Fill(objs[item.first]); objs[item.first] = eta2;item.second->Fill(objs[item.first]);}
								if( strcmp(item.first.c_str() , "mupt") ==0 ){  objs[item.first] = pt1;item.second->Fill(objs[item.first]);objs[item.first] = pt2;item.second->Fill(objs[item.first]);}
								else item.second->Fill(objs[item.first]);
							}
						}
					}
//					else item.second->Fill(objs[item.first]);
				}
			}
		}
	return;
	};

	std::map<string, TH1D* > hist_dat_full;
//	std::map<string, TH1D* > hist_dat_left;
//	std::map<string, TH1D* > hist_dat_right;
//	std::map<string, TH1D* > hist_mc2;
//	std::map<string, TH1D* > hist_mc3;

	string theobj=  "";

	theobj = "ctau";		hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 100, -1,  1 );
	theobj = "ctau3D";		hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 100, -1,  1 );
	theobj = "cosAlpha";	hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 100, -1,  1 );
	theobj = "cosAlpha3D";	hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 100, -1,  1 );
	theobj = "dR";		hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 100,  0, 2*TMath::Pi() );
	theobj = "deta";		hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 100,  0, TMath::Pi() );
	theobj = "dphi";		hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 100,  0, TMath::Pi() );

	theobj = "mupt";		hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 300,  0, 30 );
	theobj = "mueta";		hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 100,  -2.4, 2.4 );
	theobj = "dipt";		hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 300,  0, 30);
	theobj = "diy";			hist_dat_full[theobj] =  new TH1D(Form("h_%s_dat_full",theobj.c_str()), "", 100,  -2.4, 2.4 );

//	theobj = "ctau";		hist_dat_left[theobj] =  new TH1D(Form("h_%s_dat_left",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "ctau3D";		hist_dat_left[theobj] =  new TH1D(Form("h_%s_dat_left",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "cosAlpha";	hist_dat_left[theobj] =  new TH1D(Form("h_%s_dat_left",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "cosAlpha3D";	hist_dat_left[theobj] =  new TH1D(Form("h_%s_dat_left",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "QQdca";		hist_dat_left[theobj] =  new TH1D(Form("h_%s_dat_left",theobj.c_str()), "", 100,  0,  1 );
//	theobj = "QQVtxProb";	hist_dat_left[theobj] =  new TH1D(Form("h_%s_dat_left",theobj.c_str()), "", 100,  0, 0.5);
//
//	theobj = "ctau";		hist_dat_right[theobj] =  new TH1D(Form("h_%s_dat_right",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "ctau3D";		hist_dat_right[theobj] =  new TH1D(Form("h_%s_dat_right",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "cosAlpha";	hist_dat_right[theobj] =  new TH1D(Form("h_%s_dat_right",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "cosAlpha3D";	hist_dat_right[theobj] =  new TH1D(Form("h_%s_dat_right",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "QQdca";		hist_dat_right[theobj] =  new TH1D(Form("h_%s_dat_right",theobj.c_str()), "", 100,  0,  1 );
//	theobj = "QQVtxProb";	hist_dat_right[theobj] =  new TH1D(Form("h_%s_dat_right",theobj.c_str()), "", 100,  0, 0.5);
//
//	theobj = "ctau";		hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "ctau3D";		hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "cosAlpha";	hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "cosAlpha3D";	hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "QQdca";		hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100,  0,  1 );
//	theobj = "QQVtxProb";	hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100,  0, 0.5);
//
//	theobj = "ctau";		hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "ctau3D";		hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "cosAlpha";	hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "cosAlpha3D";	hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100, -1,  1 );
//	theobj = "QQdca";		hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100,  0,  1 );
//	theobj = "QQVtxProb";	hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100,  0, 0.5);


	getVarHist(td, hist_dat_full);
//	getVarHist(td, hist_dat_left);
//	getVarHist(td, hist_dat_right);
//	getVarHist(tmc2, hist_mc2);
//	getVarHist(tmc3, hist_mc3);

	double glb_markerS = 0.8;
	for( auto item : hist_dat_full){
		item.second->Scale(1/item.second->GetSum()); 
		item.second->SetStats(0);
		item.second->SetMarkerStyle(kFullCircle);
		item.second->SetMarkerSize(glb_markerS);
		int col = kRed+2;
		item.second->SetMarkerColor(col);
		item.second->SetLineColor(col);
	}
//
//	for( auto item : hist_dat_left){
//		item.second->Scale(1/item.second->GetSum()); 
//		item.second->SetStats(0);
//		item.second->SetMarkerStyle(kFullCircle);
//		item.second->SetMarkerSize(glb_markerS);
//		int col = kOrange+4;
//		item.second->SetMarkerColor(col);
//		item.second->SetLineColor(col);
//	}
//
//	for( auto item : hist_dat_right){
//		item.second->Scale(1/item.second->GetSum()); 
//		item.second->SetStats(0);
//		item.second->SetMarkerStyle(kFullCircle);
//		item.second->SetMarkerSize(glb_markerS);
//		int col = kMagenta+1;
//		item.second->SetMarkerColor(col);
//		item.second->SetLineColor(col);
//	}
//	for( auto item : hist_mc2){
//		item.second->Scale(1/item.second->GetSum()) ;
//		item.second->SetStats(0);
//		item.second->SetMarkerStyle(kFullSquare);
//		item.second->SetMarkerSize(glb_markerS);
//		int col = kBlue;
//		item.second->SetMarkerColor(col);
//		item.second->SetLineColor(col);
//	}
//	for( auto item : hist_mc3){
//		item.second->Scale(1/item.second->GetSum()) ;
//		item.second->SetStats(0);
//		item.second->SetMarkerStyle(kFullSquare);
//		item.second->SetMarkerSize(glb_markerS);
//		int col = kGreen+2;
//		item.second->SetMarkerColor(col);
//		item.second->SetLineColor(col);
//	}

	auto getRatioDist = [](TH1D* test, TH1D* base, TGraph* h_ratio){
		int nBins = test->GetNbinsX();
		for( auto idx : ROOT::TSeqI(nBins)){
			double ratio = test->GetBinContent(idx+1) / base->GetBinContent(idx+1) ;
			std::cout << "Ratio : " <<  ratio << std::endl;
			h_ratio->SetPoint(idx, test->GetBinCenter(idx+1), ratio);
		}
		return void();
	};

	TCanvas* c1 =new TCanvas("c1", "", 600, 700);
	TFile* f_out = new TFile("dataPbPb_m8-14_vardist.root", "recreate");


	for(auto var : {"ctau", "ctau3D", "cosAlpha", "cosAlpha3D", "deta", "dphi", "dR", "mupt", "mueta", "dipt", "diy"}) {
//		TPad* p1 =new TPad("p1", "", 0,0.2,1.,1.);
//		p1->SetBottomMargin(0);
//		TPad* p2 =new TPad("p2", "", 0,0.0,1.,0.2);
//		p2->SetTopMargin(0.01);
//		p2->SetBottomMargin(0.15);
		c1->cd();
//		p1->Draw();
//		p2->Draw();
//		p1->cd();
		TLegend* leg =new TLegend(0.67, 0.5, 0.83, 0.7);
		hist_dat_full[string(var)]->Draw();
//		hist_dat_left[string(var)]->Draw("same");
//		hist_dat_right[string(var)]->Draw("same");
//		hist_mc2[string(var)]->Draw("same");
//		hist_mc3[string(var)]->Draw("same");
		leg->SetHeader(string(var).c_str()) ;
		leg->AddEntry(hist_dat_full[string(var)], "Data full", "pl");
//		leg->AddEntry(hist_dat_left[string(var)], "Data low mass", "pl");
//		leg->AddEntry(hist_dat_right[string(var)], "Data high mass", "pl");
//		leg->AddEntry(hist_mc2[string(var)], "MC (2S)", "pl");
//		leg->AddEntry(hist_mc3[string(var)], "MC (3S)", "pl");
		leg->SetBorderSize(0);
		leg->Draw();

//		CMS_lumi_square(p1, 31, 33);
//		p2->cd();
//		TGraph* hist_ratio_dat_left = new TGraph();
//		getRatioDist(hist_dat_left[string(var)], hist_dat_full[string(var)],hist_ratio_dat_left);
//		TGraph* hist_ratio_dat_right = new TGraph();
//		getRatioDist(hist_dat_right[string(var)], hist_dat_full[string(var)],hist_ratio_dat_right);
////		TH1D* hist_ratio_mc2 	= getRatioDist(hist_dat_left[string(var)], hist_dat_full[string(var)]);
////		TH1D* hist_ratio_mc3 	= getRatioDist(hist_dat_left[string(var)], hist_dat_full[string(var)]);
////		hist_ratio_dat_left 	->SetStats(0);
////		hist_ratio_dat_right 	->SetStats(0);
//		std::cout << hist_ratio_dat_left->GetName() << std::endl;
//		hist_ratio_dat_left-> SetLineColor(hist_dat_left[string(var)]->GetLineColor());
//		hist_ratio_dat_right->SetLineColor(hist_dat_right[string(var)]->GetLineColor());
//		hist_ratio_dat_left-> SetMarkerColor(hist_dat_left[string(var)]->GetMarkerColor());
//		hist_ratio_dat_right->SetMarkerColor(hist_dat_right[string(var)]->GetMarkerColor());
//
//		hist_ratio_dat_left ->GetXaxis()->SetLimits(hist_dat_full[string(var)]->GetXaxis()->GetXmin(),hist_dat_full[string(var)]->GetXaxis()->GetXmax()      );
//		hist_ratio_dat_right->GetXaxis()->SetLimits(hist_dat_full[string(var)]->GetXaxis()->GetXmin(),hist_dat_full[string(var)]->GetXaxis()->GetXmax()      );
//
//		hist_ratio_dat_left ->SetMarkerStyle(kFullSquare);
//		hist_ratio_dat_right->SetMarkerStyle(kFullSquare);
//		hist_ratio_dat_left ->GetYaxis()->SetLabelSize(hist_ratio_dat_left->GetYaxis()->GetLabelSize()*4);
//		hist_ratio_dat_right->GetYaxis()->SetLabelSize(hist_ratio_dat_right->GetYaxis()->GetLabelSize()*4);
//		hist_ratio_dat_left ->GetXaxis()->SetLabelSize(hist_ratio_dat_left->GetXaxis()->GetLabelSize()*4);
//		hist_ratio_dat_right->GetXaxis()->SetLabelSize(hist_ratio_dat_right->GetXaxis()->GetLabelSize()*4);
//		hist_ratio_dat_left ->SetMarkerSize(0.5);
//		hist_ratio_dat_right->SetMarkerSize(0.5);
//		hist_ratio_dat_left->Draw("AP");
//		hist_ratio_dat_right->Draw("P");

		c1->SaveAs(Form("./DistExtra/Variable_dist_vtxcut_%s.pdf" , var ) );
//		c1->SaveAs(Form("./DistExtra/Variable_dist_%s.pdf" , var ) );
		c1->cd();
		c1->Clear();
		leg->Clear();
		f_out->cd();
		hist_dat_full[string(var)]->Write();
	}
	f_out->Write();
	f_out->Close();
	system("cp -r ./DistExtra ../checkout");

}
