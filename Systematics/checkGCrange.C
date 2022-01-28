#include "sys_wr_helper.cxx"

#ifndef rr
#define rr std::map< string, RooRealVar>
#endif

rr checkGCrange_2item(ana_bins x){
	int pl, ph, cl, ch, state, bpl, bph;
	pl = x.pl; ph = x.ph; cl = x.cl; ch = x.ch; state = x.state; bpl = x.bpl; bph = x.bph;
	int train_state = x.train_state;
	string fittype = (strcmp(x.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	long ts = _TS;
	auto AICres = AICGOF_test(x);
	string bkgtype_nom = AICres[0].second;
//	string bkgtype_sys2 = (bkgtype_nom.find("CC") != std::string::npos) ? 
//	bkgtype_nom.substr(0,2) + Form("%d",stoi(bkgtype_nom.substr(2,1) )+1 ) : (bkgtype_sys1.find("CC") != std::string::npos) ?
//	bkgtype_sys1.substr(0,2) + Form("%d",stoi(bkgtype_sys1.substr(2,1) )+1 ) : AICres[2].second;

	std::string type_nom = 	Form("CB3:%s:%s",	bkgtype_nom.c_str(),  fittype.c_str());
	std::string type_sys1  =Form("CB3:%s:%sWIDE",	bkgtype_nom.c_str(),  fittype.c_str());
	std::string type_sys2 = Form("CB3:%s:%sWIDE3",	bkgtype_nom.c_str(),  fittype.c_str());

	binplotter *bp_nom, *bp_sys1, *bp_sys2;
	double bl_nom = Get_BDT(ts, train_state, state, bpl, bph, pl, ph, cl, ch);
	bp_nom  = new binplotter(type_nom , ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	bp_sys1 = new binplotter(type_sys1, ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	bp_sys2 = new binplotter(type_sys2, ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	RooRealVar raa_nom, raa_sys1, raa_sys2;
	if( !isDR ){
	raa_nom = bp_nom->get_yield(state);
	raa_sys1 = bp_sys1->get_yield(state);
	raa_sys2 = bp_sys2->get_yield(state);
	}
	if( isDR ){
	raa_nom  = bp_nom->return_23s_frac();
	raa_sys1 = bp_sys1->return_23s_frac();
	raa_sys2 = bp_sys2->return_23s_frac();
	}

	return (rr) { {"nom", raa_nom},{"WIDE", raa_sys1},{"WIDE2", raa_sys2}};
};
void checkGCrange(ana_bins x){
	rr res = checkGCrange_2item(x);
	TCanvas* c1 =new TCanvas();
	TH1D* hx = new TH1D("hx", "", 3, 0,1);
	hx->SetStats(0);
	hx->SetMarkerStyle(kFullCircle);
	hx->SetMarkerSize(1.4);
	hx->SetMarkerColor(kGreen+2);
	hx->SetLineColor(kGreen+2);
	hx->GetYaxis()->SetRangeUser(0.5, 1.5) ;
	hx->GetXaxis()->SetTickSize(0);
	hx->GetXaxis()->SetLabelSize(0.037);
	hx->GetXaxis()->SetBinLabel(1, "Nominal");
	hx->GetXaxis()->SetBinLabel(2, "#times 2");
	hx->GetXaxis()->SetBinLabel(3, "#times 3");
	hx->SetBinContent(1, 1 );
	hx->SetBinContent(2, res["WIDE"].getVal() / res["nom"].getVal());
	hx->SetBinContent(3, res["WIDE2"].getVal() / res["nom"].getVal());

	hx->SetBinError(1, res["nom"].getError()/ res["nom"].getVal() );
	hx->SetBinError(2, res["WIDE"].getError()/ res["nom"].getVal());
	hx->SetBinError(3, res["WIDE2"].getError()/ res["nom"].getVal());

	c1->cd();
	hx->Draw("pe");

	CMS_lumi_square(c1, 101, 33); 
	TLatex * tl = new TLatex();
	tl->SetTextSize(0.037);
	tl->SetTextFont(42);
	tl->SetTextAlign(31);
	tl->DrawLatex(0.94,0.60, "Variation of gaussian constraint width by scaling MC errors");
	tl->DrawLatex(0.94,0.55, "Fit yield and error scaled by nominal data");

	c1->Draw();
};

void checkGCrange(){
	checkGCrange(ana_bm["3c"][0]);
}

//void BkgVariUnc(){
//	sys_wr_helper(Form("checkGCrange.root", labDR.c_str()), checkGCrange);
//}

