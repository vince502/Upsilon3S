#pragma once
#include "../BDT/bininfo.h"

const string plt_save_dir = Form("%s/plots/result/", workdir.Data() );

void plot_wr_helper(string fout, RooRealVar (*x)(ana_bins, long, bool, int, int), long ts, int ofstate= -1, int getPre = 0){
	
	TFile* output = new TFile( (plt_save_dir + fout).c_str(), "recreate");
	std::vector<ana_bins> vc2, vc3, vp2, vp3;
	vc2 = ana_bm["2c"];
    vc3 = ana_bm["3c"];
    vp2 = ana_bm["2p"];
    vp3 = ana_bm["3p"];

    TH1D *rc2s, *rc3s, *rp2s, *rp3s;
    rc2s = new TH1D("rc2S","",vc2.size(),0,vc2.size()-1); //include int. bin
    rc3s = new TH1D("rc3S","",vc3.size(),0,vc3.size()-1);  //include int. bin
    rp2s = new TH1D("rp2S","",vp2.size(),1,vp2.size());
    rp3s = new TH1D("rp3S","",vp3.size(),1,vp3.size());

	bool incl_ppstat_forthisbin;

    int counter =1;
    for( auto item : vc2){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin,ofstate, getPre);
		
        rc2s->SetBinContent(counter	,res.getVal());
        rc2s->SetBinError(counter	,res.getError());
        counter++;
    }
    counter =1;
    for( auto item : vc3){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin,ofstate, getPre);
        rc3s->SetBinContent(counter	,res.getVal());
        rc3s->SetBinError(counter	,res.getError());
        counter++;
    }
    counter =1;

    for( auto item : vp2){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin,ofstate, getPre);
        rp2s->SetBinContent(counter	,res.getVal());
        rp2s->SetBinError(counter	,res.getError());
        counter++;
    }
    counter =1;

    for( auto item : vp3){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin,ofstate, getPre);
        rp3s->SetBinContent(counter	,res.getVal());
        rp3s->SetBinError(counter	,res.getError());
        counter++;
    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
};

void plot_wr_helper(string fout, RooRealVar (*x)(ana_bins, long, bool), long ts){
	
	TFile* output = new TFile( (plt_save_dir + fout).c_str(), "recreate");
	std::vector<ana_bins> vc2, vc3, vp2, vp3;
	vc2 = ana_bm["2c"];
    vc3 = ana_bm["3c"];
    vp2 = ana_bm["2p"];
    vp3 = ana_bm["3p"];

    TH1D *rc2s, *rc3s, *rp2s, *rp3s;
    rc2s = new TH1D("rc2S","",vc2.size(),0,vc2.size()-1); //include int. bin
    rc3s = new TH1D("rc3S","",vc3.size(),0,vc3.size()-1);  //include int. bin
    rp2s = new TH1D("rp2S","",vp2.size(),1,vp2.size());
    rp3s = new TH1D("rp3S","",vp3.size(),1,vp3.size());

	bool incl_ppstat_forthisbin;

    int counter =1;
    for( auto item : vc2){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin);
		
        rc2s->SetBinContent(counter	,res.getVal());
        rc2s->SetBinError(counter	,res.getError());
        counter++;
    }
    counter =1;
    for( auto item : vc3){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin);
        rc3s->SetBinContent(counter	,res.getVal());
        rc3s->SetBinError(counter	,res.getError());
        counter++;
    }
    counter =1;

    for( auto item : vp2){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin);
        rp2s->SetBinContent(counter	,res.getVal());
        rp2s->SetBinError(counter	,res.getError());
        counter++;
    }
    counter =1;

    for( auto item : vp3){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin);
        rp3s->SetBinContent(counter	,res.getVal());
        rp3s->SetBinError(counter	,res.getError());
        counter++;
    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
};


void plot_wr_helper(string fout, RooRealVar (*x)(ana_bins, long, bool, int), long ts, int sc){
	
	TFile* output = new TFile( (plt_save_dir + fout).c_str(), "recreate");
	std::vector<ana_bins> vc2, vc3, vp2, vp3;
	vc2 = ana_bm["2c"];
    vc3 = ana_bm["3c"];
    vp2 = ana_bm["2p"];
    vp3 = ana_bm["3p"];

    TH1D *rc2s, *rc3s, *rp2s, *rp3s;
    rc2s = new TH1D("rc2S","",vc2.size(),0,vc2.size()-1); //include int. bin
    rc3s = new TH1D("rc3S","",vc3.size(),0,vc3.size()-1);  //include int. bin
    rp2s = new TH1D("rp2S","",vp2.size(),1,vp2.size());
    rp3s = new TH1D("rp3S","",vp3.size(),1,vp3.size());

	bool incl_ppstat_forthisbin;
	std::cout << "DBG" << std::endl;

    int counter =1;
    for( auto item : vc2){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin, sc);
		
        rc2s->SetBinContent(counter	,res.getVal());
        rc2s->SetBinError(counter	,res.getError());
        counter++;
    }
    counter =1;
    for( auto item : vc3){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin, sc);
        rc3s->SetBinContent(counter	,res.getVal());
        rc3s->SetBinError(counter	,res.getError());
        counter++;
    }
    counter =1;

    for( auto item : vp2){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin, sc);
        rp2s->SetBinContent(counter	,res.getVal());
        rp2s->SetBinError(counter	,res.getError());
        counter++;
    }
    counter =1;

    for( auto item : vp3){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin, sc);
        rp3s->SetBinContent(counter	,res.getVal());
        rp3s->SetBinError(counter	,res.getError());
        counter++;
    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
};
//RAA OF SAME 0-30 GEV TRAINING APPLIED TO PT BINS
void plot_wr_helper_aux(string fout, RooRealVar (*x)(ana_bins, long, bool, int, int), long ts){
	
	TFile* output = new TFile( (plt_save_dir + fout).c_str(), "recreate");
	std::vector<ana_bins> vc2, vc3, vp2, vp3;
	vc2 = ana_bm["2c"];
    vc3 = ana_bm["3c"];
    vp2 = ana_bm["2p"];
    vp3 = ana_bm["3p"];

    TH1D *rc2s, *rc3s, *rp2s, *rp3s;
    rc2s = new TH1D("rc2S","",vc2.size(),0,vc2.size()-1); //include int. bin
    rc3s = new TH1D("rc3S","",vc3.size(),0,vc3.size()-1);  //include int. bin
    rp2s = new TH1D("rp2S","",vp2.size(),1,vp2.size());
    rp3s = new TH1D("rp3S","",vp3.size(),1,vp3.size());

	bool incl_ppstat_forthisbin;

    int counter =1;
//    for( auto item : vc2){
//		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
//		auto res = (*x)(item, ts, incl_ppstat_forthisbin);
//		
//        rc2s->SetBinContent(counter	,res.getVal());
//        rc2s->SetBinError(counter	,res.getError());
//        counter++;
//    }
//    counter =1;
//    for( auto item : vc3){
//		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
//		auto res = (*x)(item, ts, incl_ppstat_forthisbin);
//        rc3s->SetBinContent(counter	,res.getVal());
//        rc3s->SetBinError(counter	,res.getError());
//        counter++;
//    }
//    counter =1;
//
//    for( auto item : vp2){
//		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
//		auto res = (*x)(item, ts, incl_ppstat_forthisbin);
//        rp2s->SetBinContent(counter	,res.getVal());
//        rp2s->SetBinError(counter	,res.getError());
//        counter++;
//    }
    counter =1;

    for( auto item : vp3){
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		item.bpl = 0;
		item.bph = 30;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin, -1, 0);
        rp3s->SetBinContent(counter	,res.getVal());
        rp3s->SetBinError(counter	,res.getError());
        counter++;
    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
};

//DIFFERENT PT TRAINING APPLIED TO INTEGRATED BIN
void plot_wr_helper_aux2(string fout, RooRealVar (*x)(ana_bins, long, bool, int, int), long ts){
	
	TFile* output = new TFile( (plt_save_dir + fout).c_str(), "recreate");
	std::vector<ana_bins> vc2, vc3, vp2, vp3;
	vc2 = ana_bm["2c"];
    vc3 = ana_bm["3c"];
    vp2 = ana_bm["2p"];
    vp3 = ana_bm["3p"];

    TH1D *rc2s, *rc3s, *rp2s, *rp3s;
    rc2s = new TH1D("rc2S","",vc2.size(),0,vc2.size()-1); //include int. bin
    rc3s = new TH1D("rc3S","",vc3.size(),0,vc3.size()-1);  //include int. bin
    rp2s = new TH1D("rp2S","",vp2.size(),1,vp2.size());
    rp3s = new TH1D("rp3S","",vp3.size(),1,vp3.size());

	bool incl_ppstat_forthisbin;

    int counter =1;
//    for( auto item : vc2){
//		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
//		auto res = (*x)(item, ts, incl_ppstat_forthisbin);
//		
//        rc2s->SetBinContent(counter	,res.getVal());
//        rc2s->SetBinError(counter	,res.getError());
//        counter++;
//    }
//    counter =1;
    for( auto pair : (std::vector<std::pair<int, int> >) {{0,4},{4,9},{9,15},{15,30}}){
		auto item = vc3[0];
		item.bpl = pair.first;
		item.bph = pair.second;
		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
		auto res = (*x)(item, ts, incl_ppstat_forthisbin, -1, 0);
        rc3s->SetBinContent(counter	,res.getVal());
        rc3s->SetBinError(counter	,res.getError());
        counter++;
    }
//    counter =1;
//
//    for( auto item : vp2){
//		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
//		auto res = (*x)(item, ts, incl_ppstat_forthisbin);
//        rp2s->SetBinContent(counter	,res.getVal());
//        rp2s->SetBinError(counter	,res.getError());
//        counter++;
//    }
//    counter =1;
//
//    for( auto item : vp3){
//		incl_ppstat_forthisbin = ( item.bintype != kCent) ? true : false;
//		item.bpl = 0;
//		item.bph = 30;
//		auto res = (*x)(item, ts, incl_ppstat_forthisbin, -1, 0);
//        rp3s->SetBinContent(counter	,res.getVal());
//        rp3s->SetBinError(counter	,res.getError());
//        counter++;
//    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
};
