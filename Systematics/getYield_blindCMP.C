#define _TS 200019111111
//#include "../LLR_CCorder_10000000016.h"
//#define getNomBkgO getNomBkgO_10000000016

#include "../LLR_CCorder_200019111111.h"
#define getNomBkgO getNomBkgO_200019111111

#define ana_bm ana_bm_comb_ub
#include "../Systematics/GOF_test.cxx"
#include "../BDT/yield_eff_signif.cxx"
#include "../upsilonAna.h"

#define Pmode 2
#define pp std::pair<RooRealVar, RooRealVar>
pp _getYieldblindCMP(ana_bins item){
	binplotter bp;
	binplotter bps1;
	binplotter bps2;
	std::string output;
	long ts = _TS;
	
			string fittype = (strcmp(item.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
			auto AICres = AICGOF_test(item);
			string bkgtype_nom = AICres[0].second;
			string type_nom = Form("CB3:%s:%s", bkgtype_nom.c_str(), fittype.c_str() );
			string type_bdtup = Form("CB3:%s:%sbdtup", bkgtype_nom.c_str(), fittype.c_str() );
			string type_bdtdo = Form("CB3:%s:%sbdtdown", bkgtype_nom.c_str(), fittype.c_str() );
			double bdt = Get_BDT(ts_alias(_TS), item);
    		auto getdiff = [=](){
    		    auto sb_ratio = get_eff_acc_v2(type_nom, ts, 2.4, (double) item.pl, (double) item.ph, item.cl, item.ch, bdt, 1.0, item.bpl, item.bph, item.train_state, 1, item.state, false);
    		    return Get_BDTTD(ts, item, sb_ratio.getVal());
    		};
    		auto res = getdiff();

			bp = binplotter(type_nom, _TS, 2.4, item.pl, item.ph, item.cl, item.ch, 0, bdt, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			bps1 = binplotter(type_nom, ts_alias(_TS), 2.4, item.pl, item.ph, item.cl, item.ch, 0, bdt, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
//			bps1 = binplotter(type_bdtup, _TS, 2.4, item.pl, item.ph, item.cl, item.ch, 0, res.second, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
//			bps2 = binplotter(type_bdtdo, _TS, 2.4, item.pl, item.ph, item.cl, item.ch, 0, res.first, 1, item.bpl, item.bph, item.train_state, item.state, false, false);
			RooRealVar yield = bp.get_yield(item.state);
			RooRealVar yieldsys1 = bps1.get_yield(item.state);
//			RooRealVar yieldsys2 = bps2.get_yield(item.state);
	return std::make_pair(yield, yieldsys1);
}

void getYield_blindCMP(){
	TCanvas* c1 =new TCanvas("c1", "", 1200,1000);
	c1->Divide(2,2);
    std::vector<ana_bins> vc2, vc3, vp2, vp3;
    vc2 = ana_bm["2c"];
    vc3 = ana_bm["3c"];
    vp2 = ana_bm["2p"];
    vp3 = ana_bm["3p"];

    TH1D *rc2s, *rc3s, *rp2s, *rp3s;
    TH1D *rc2s_ub, *rc3s_ub, *rp2s_ub, *rp3s_ub;
    rc2s = new TH1D("rc2S","",vc2.size(),0,vc2.size()-1); //include int. bin
    rc3s = new TH1D("rc3S","",vc3.size(),0,vc3.size()-1);  //include int. bin
    rp2s = new TH1D("rp2S","",vp2.size(),1,vp2.size());
    rp3s = new TH1D("rp3S","",vp3.size(),1,vp3.size());

	rc2s->SetLineColor(kRed);
	rc3s->SetLineColor(kRed);
	rp2s->SetLineColor(kRed);
	rp3s->SetLineColor(kRed);
	rc2s->SetMarkerColor(kRed);
	rc3s->SetMarkerColor(kRed);
	rp2s->SetMarkerColor(kRed);
	rp3s->SetMarkerColor(kRed);
	rc2s->SetLineWidth(4);
	rc3s->SetLineWidth(4);
	rp2s->SetLineWidth(4);
	rp3s->SetLineWidth(4);

    rc2s_ub = new TH1D("rc2S_ub","",vc2.size(),0,vc2.size()-1); //include int. bin
    rc3s_ub = new TH1D("rc3S_ub","",vc3.size(),0,vc3.size()-1);  //include int. bin
    rp2s_ub = new TH1D("rp2S_ub","",vp2.size(),1,vp2.size());
    rp3s_ub = new TH1D("rp3S_ub","",vp3.size(),1,vp3.size());

	rc2s_ub->SetLineColor(kGreen-2);
	rc3s_ub->SetLineColor(kGreen-2);
	rp2s_ub->SetLineColor(kGreen-2);
	rp3s_ub->SetLineColor(kGreen-2);
	rc2s_ub->SetMarkerColor(kGreen-2);
	rc3s_ub->SetMarkerColor(kGreen-2);
	rp2s_ub->SetMarkerColor(kGreen-2);
	rp3s_ub->SetMarkerColor(kGreen-2);

	rc2s_ub->SetLineWidth(2);
	rc3s_ub->SetLineWidth(2);
	rp2s_ub->SetLineWidth(2);
	rp3s_ub->SetLineWidth(2);



    int counter =1;
    for( auto item : vc2){
		auto res = _getYieldblindCMP(item);
        rc2s->SetBinContent(counter, res.second.getVal()*4);
        rc2s->SetBinError(counter, res.second.getError()*2);
        rc2s_ub->SetBinContent(counter, res.first.getVal());
        rc2s_ub->SetBinError(counter, res.first.getError());
        counter++;
    }
    counter =1;
    for( auto item : vc3){
		auto res = _getYieldblindCMP(item);
        rc3s->SetBinContent(counter, res.second.getVal()*4);
        rc3s->SetBinError(counter, res.second.getError()*2);
        rc3s_ub->SetBinContent(counter, res.first.getVal());
        rc3s_ub->SetBinError(counter, res.first.getError());
        counter++;
    }
    counter =1;

    for( auto item : vp2){
		auto res = _getYieldblindCMP(item);
        rp2s->SetBinContent(counter, res.second.getVal()*4);
        rp2s->SetBinError(counter, res.second.getError()*2);
        rp2s_ub->SetBinContent(counter, res.first.getVal());
        rp2s_ub->SetBinError(counter, res.first.getError());
        counter++;
    }
    counter =1;

    for( auto item : vp3){
		auto res = _getYieldblindCMP(item);
        rp3s->SetBinContent(counter, res.second.getVal()*4);
        rp3s->SetBinError(counter, res.second.getError()*2);
        rp3s_ub->SetBinContent(counter, res.first.getVal());
        rp3s_ub->SetBinError(counter, res.first.getError());
        counter++;
    }
	c1->cd(1);
	rc2s->GetYaxis()->SetRangeUser(0,2500);
	rc2s_ub->GetYaxis()->SetRangeUser(0,2500);
	rc2s->Draw("ple");
	rc2s_ub->Draw("same");
	c1->cd(2);
	rc3s->GetYaxis()->SetRangeUser(0,1400);
	rc3s_ub->GetYaxis()->SetRangeUser(0,1400);
	rc3s->Draw("ple");
	rc3s_ub->Draw("same");
	c1->cd(3);
	rp2s->GetYaxis()->SetRangeUser(200,900);
	rp2s_ub->GetYaxis()->SetRangeUser(200,900);
	rp2s->Draw("ple");
	rp2s_ub->Draw("same");
	c1->cd(4);
	rp3s->GetYaxis()->SetRangeUser(0,500);
	rp3s_ub->GetYaxis()->SetRangeUser(0,500);
	rp3s->Draw("ple");
	rp3s_ub->Draw("same");
	c1->SaveAs("~/Upsilon3S/checkout/yieldcompare.pdf");
    TFile* output = new TFile( "check.root", "recreate");
    output->cd();
    rc2s->Write();
    rc3s->Write();
    rp2s->Write();
    rp3s->Write();
    output->Close();

}
