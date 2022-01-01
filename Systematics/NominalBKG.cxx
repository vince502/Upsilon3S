#include "../BDT/bininfo.h"
#include "GOF_test.cxx"


void NominalBKG(){
	TFile* output = new TFile("NominalBKG.root", "recreate");
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
		auto res = AICGOF_test(item);
		rc2s->GetXaxis()->SetBinLabel(counter, res[0].second.c_str());
        rc2s->SetBinContent(counter, 0);
        counter++;
    }
    counter =1;
    for( auto item : vc3){
		auto res = AICGOF_test(item);
		rc3s->GetXaxis()->SetBinLabel(counter, res[0].second.c_str());
        rc3s->SetBinContent(counter, 0);
        counter++;
    }
    counter =1;

    for( auto item : vp2){
		auto res = AICGOF_test(item);
		rp2s->GetXaxis()->SetBinLabel(counter, res[0].second.c_str());
        rp2s->SetBinContent(counter, 0);
        counter++;
    }
    counter =1;

    for( auto item : vp3){
		auto res = AICGOF_test(item);
		rp3s->GetXaxis()->SetBinLabel(counter, res[0].second.c_str());
        rp3s->SetBinContent(counter, 0);
        counter++;
    }
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();
}
