#pragma once
#include "../BDT/bininfo.h"

const string plt_save_dir = Form("%s/plots/result/", workdir.Data() );

void plot_wr_helper(string fout, RooRealVar (*x)(ana_bins, long), long ts){
	
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



    int counter =1;
    for( auto item : vc2){
        rc2s->SetBinContent(counter, (*x)(item, ts).getVal());
        rc2s->SetBinError(counter, (*x)(item, ts).getError());
        counter++;
    }
    counter =1;
    for( auto item : vc3){
        rc3s->SetBinContent(counter, (*x)(item, ts).getVal());
        rc3s->SetBinError(counter, (*x)(item, ts).getError());
        counter++;
    }
    counter =1;

    for( auto item : vp2){
        rp2s->SetBinContent(counter, (*x)(item, ts).getVal());
        rp2s->SetBinError(counter, (*x)(item, ts).getError());
        counter++;
    }
    counter =1;

    for( auto item : vp3){
        rp3s->SetBinContent(counter, (*x)(item, ts).getVal());
        rp3s->SetBinError(counter, (*x)(item, ts).getError());
        counter++;
    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
};
