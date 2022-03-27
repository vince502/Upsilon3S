#pragma once
#include "../BDT/bininfo.h"

#ifndef _SAVEDIR_
#define _SAVEDIR_
const string save_dir = Form("%s/Systematics/data/", workdir.Data() );
#endif

void sys_wr_helper(string fout, double (*x)(ana_bins)){
	
	TFile* output = new TFile( (save_dir + fout).c_str(), "recreate");
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
        rc2s->SetBinContent(counter, (*x)(item));
        counter++;
    }
    counter =1;
    for( auto item : vc3){
        rc3s->SetBinContent(counter, (*x)(item));
        counter++;
    }
    counter =1;

    for( auto item : vp2){
        rp2s->SetBinContent(counter, (*x)(item));
        counter++;
    }
    counter =1;

    for( auto item : vp3){
        rp3s->SetBinContent(counter, (*x)(item));
        counter++;
    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
};

void sys_wr_helper(string fout, RooRealVar (*x)(ana_bins)){
	
	TFile* output = new TFile( (save_dir + fout).c_str(), "recreate");
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
        rc2s->SetBinContent(counter, ((*x)(item)).getVal());
        rc2s->SetBinError(counter, ((*x)(item)).getError());
        counter++;
    }
    counter =1;
    for( auto item : vc3){
        rc3s->SetBinContent(counter, ((*x)(item)).getVal());
        rc3s->SetBinError(counter, ((*x)(item)).getError());
        counter++;
    }
    counter =1;

    for( auto item : vp2){
        rp2s->SetBinContent(counter, ((*x)(item)).getVal());
        rp2s->SetBinError(counter, ((*x)(item)).getError());
        counter++;
    }
    counter =1;

    for( auto item : vp3){
        rp3s->SetBinContent(counter, ((*x)(item)).getVal());
        rp3s->SetBinError(counter, ((*x)(item)).getError());
        counter++;
    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
};
#define pp std::pair<std::pair<double, string>, std::pair<double, string> >

void sys_wr_helper_2item(string fout, pp (*x)(ana_bins)){
	TFile* output = new TFile((save_dir + fout).c_str(), "recreate");
	std::vector<ana_bins> vc2, vc3, vp2, vp3;
	vc2 = ana_bm["2c"];
    vc3 = ana_bm["3c"];
    vp2 = ana_bm["2p"];
    vp3 = ana_bm["3p"];

    TH1D *rc2s, *rc3s, *rp2s, *rp3s;
    rc2s = new TH1D("rc2S","",vc2.size()*2,0,vc2.size()-1); //include int. bin
    rc3s = new TH1D("rc3S","",vc3.size()*2,0,vc3.size()-1);  //include int. bin
    rp2s = new TH1D("rp2S","",vp2.size()*2,1,vp2.size());
    rp3s = new TH1D("rp3S","",vp3.size()*2,1,vp3.size());



    int counter =1;
    for( auto item : vc2){
		const pp bc = (*x)(item);
        rc2s->SetBinContent(counter,   bc.first.first);
        rc2s->SetBinContent(counter+1, bc.second.first);
		rc2s->GetXaxis()->SetBinLabel(counter+0, bc.first.second.c_str());
		rc2s->GetXaxis()->SetBinLabel(counter+1, bc.second.second.c_str());
        counter+=2;
    }
    counter =1;
    for( auto item : vc3){
		const pp bc = (*x)(item);
        rc3s->SetBinContent(counter, bc.first.first);
        rc3s->SetBinContent(counter+1, bc.second.first);
		rc3s->GetXaxis()->SetBinLabel(counter+0, bc.first.second.c_str());
		rc3s->GetXaxis()->SetBinLabel(counter+1, bc.second.second.c_str());
        counter+=2;
    }
    counter =1;

    for( auto item : vp2){
		const pp bc = (*x)(item);
        rp2s->SetBinContent(counter, bc.first.first);
        rp2s->SetBinContent(counter+1, bc.second.first);
		rp2s->GetXaxis()->SetBinLabel(counter+0, bc.first.second.c_str());
		rp2s->GetXaxis()->SetBinLabel(counter+1, bc.second.second.c_str());
        counter+=2;
    }
    counter =1;

    for( auto item : vp3){
		const pp bc = (*x)(item);
        rp3s->SetBinContent(counter, bc.first.first);
        rp3s->SetBinContent(counter+1, bc.second.first);
		rp3s->GetXaxis()->SetBinLabel(counter+0, bc.first.second.c_str());
		rp3s->GetXaxis()->SetBinLabel(counter+1, bc.second.second.c_str());
        counter+=2;
    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
}
