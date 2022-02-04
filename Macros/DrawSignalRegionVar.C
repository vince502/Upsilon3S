#include "../.workdir.h"
#include "../CMS_lumi_square.C"

void DrawSignalRegionVar(){
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
	int ntrk1, ntrk2, npix1, npix2;
	std::map<string, double> objs;
	auto setthistree = [&](TTree* t){
		t->SetBranchAddress("mass", &mass);
		t->SetBranchAddress("dxy1", &dxy1);
		t->SetBranchAddress("dxy2", &dxy2);

		t->SetBranchAddress("dz1", &dz1);
		t->SetBranchAddress("dz2", &dz2);

		t->SetBranchAddress("pt1", &pt1);
		t->SetBranchAddress("pt2", &pt2);

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
		for(auto item : vhp){
		t->SetBranchAddress(item.first.c_str(), &objs[item.first]);
		}
		long nidx = t->GetEntries();
		for( auto idx : ROOT::TSeqL(nidx) ) {
			if( (idx % 10000 ) ==0 ) std::cout << "event : "<< idx << std::endl;
			t->GetEntry(idx);
			if ( isHBSMu() ){
				for(auto item : vhp){
					if( mass < 10.7 && mass > 8.6) item.second->Fill(objs[item.first]);
				}
			}
		}
	return;
	};

	std::map<string, TH1D* > hist_dat;
	std::map<string, TH1D* > hist_mc2;
	std::map<string, TH1D* > hist_mc3;

	string theobj=  "";

	theobj = "ctau";		hist_dat[theobj] =  new TH1D(Form("h_%s_dat",theobj.c_str()), "", 100, -1,  1 );
	theobj = "ctau3D";		hist_dat[theobj] =  new TH1D(Form("h_%s_dat",theobj.c_str()), "", 100, -1,  1 );
	theobj = "cosAlpha";	hist_dat[theobj] =  new TH1D(Form("h_%s_dat",theobj.c_str()), "", 100, -1,  1 );
	theobj = "cosAlpha3D";	hist_dat[theobj] =  new TH1D(Form("h_%s_dat",theobj.c_str()), "", 100, -1,  1 );
	theobj = "QQdca";		hist_dat[theobj] =  new TH1D(Form("h_%s_dat",theobj.c_str()), "", 100,  0,  1 );
	theobj = "QQVtxProb";	hist_dat[theobj] =  new TH1D(Form("h_%s_dat",theobj.c_str()), "", 100,  0, 0.5);

	theobj = "ctau";		hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100, -1,  1 );
	theobj = "ctau3D";		hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100, -1,  1 );
	theobj = "cosAlpha";	hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100, -1,  1 );
	theobj = "cosAlpha3D";	hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100, -1,  1 );
	theobj = "QQdca";		hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100,  0,  1 );
	theobj = "QQVtxProb";	hist_mc2[theobj] =  new TH1D(Form("h_%s_mc2",theobj.c_str()), "", 100,  0, 0.5);

	theobj = "ctau";		hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100, -1,  1 );
	theobj = "ctau3D";		hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100, -1,  1 );
	theobj = "cosAlpha";	hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100, -1,  1 );
	theobj = "cosAlpha3D";	hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100, -1,  1 );
	theobj = "QQdca";		hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100,  0,  1 );
	theobj = "QQVtxProb";	hist_mc3[theobj] =  new TH1D(Form("h_%s_mc3",theobj.c_str()), "", 100,  0, 0.5);

	getVarHist(td, hist_dat);
	getVarHist(tmc2, hist_mc2);
	getVarHist(tmc3, hist_mc3);

	double glb_markerS = 0.8;
	for( auto item : hist_dat){
		item.second->Scale(1/item.second->GetSum()); 
		item.second->SetStats(0);
		item.second->SetMarkerStyle(kFullCircle);
		item.second->SetMarkerSize(glb_markerS);
		int col = kRed+2;
		item.second->SetMarkerColor(col);
		item.second->SetLineColor(col);
	}
	for( auto item : hist_mc2){
		item.second->Scale(1/item.second->GetSum()) ;
		item.second->SetStats(0);
		item.second->SetMarkerStyle(kFullSquare);
		item.second->SetMarkerSize(glb_markerS);
		int col = kBlue;
		item.second->SetMarkerColor(col);
		item.second->SetLineColor(col);
	}
	for( auto item : hist_mc3){
		item.second->Scale(1/item.second->GetSum()) ;
		item.second->SetStats(0);
		item.second->SetMarkerStyle(kFullSquare);
		item.second->SetMarkerSize(glb_markerS);
		int col = kGreen+2;
		item.second->SetMarkerColor(col);
		item.second->SetLineColor(col);
	}

	TCanvas* c1 =new TCanvas("c1", "", 600, 600);
	for(auto var : {"ctau", "ctau3D", "cosAlpha", "cosAlpha3D", "QQdca", "QQVtxProb"}) {
		TLegend* leg =new TLegend(0.6, 0.5, 0.75, 0.7);
		hist_dat[string(var)]->Draw("pl");
		hist_mc2[string(var)]->Draw("same");
		hist_mc3[string(var)]->Draw("same");
		leg->SetHeader(string(var).c_str()) ;
		leg->AddEntry(hist_dat[string(var)], "Data", "pl");
		leg->AddEntry(hist_mc2[string(var)], "MC (2S)", "pl");
		leg->AddEntry(hist_mc3[string(var)], "MC (3S)", "pl");
		leg->SetBorderSize(0);
		leg->Draw();
		CMS_lumi_square(c1, 31, 33);
		c1->SaveAs(Form("./VarDist/Variable_dist_%s.pdf" , var ) );
		c1->Clear();
		leg->Clear();
	}
	system("cp -r ./VarDist ../checkout");

}
