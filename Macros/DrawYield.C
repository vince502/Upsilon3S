#include "../plots/drawRAAplot.cxx"

//For BDT Validation
void DrawYield(long ts, int state){
	TH1D* hist1s = new TH1D("Y1S","",13, 0,13);
	TH1D* hist2s = new TH1D("Y2S","",13, 0,13);
	TH1D* hist3s = new TH1D("Y3S","",13, 0,13);
	std::vector<TH1D*> vhist =  {hist1s, hist2s, hist3s};
	TCanvas* c1 = new TCanvas("c1","",1000,600);
	c1->cd();
		int counter1 = 2;
		string typestr;
		auto ref = getDoubleRatioValue(false, {0,181},{0,30}, "CB3:CC4:FF", -1, state, 1, 9999999999, false, false, 3);
		vhist[state-1]->SetBinContent(1,ref.getVal());
		vhist[state-1]->SetBinError(1,ref.getError());
		for(double bdtv : { -0.6, -0.3, -0.2,-0.05,0.0,/*0.05,*/ 0.1, 0.15, 0.2, 0.25, 0.3} )
		{
			if(bdtv<-0.2) typestr="CB3:CC4:GC";
			if(bdtv>=-0.2) typestr="CB3:CC3:GC";
			
			auto cval = getDoubleRatioValue(false, {0,181},{0,30}, typestr, bdtv, state, 1, ts, false, false, state);
			double theval = cval.getVal();
			double theerr = cval.getError();
			vhist[state-1]->SetBinContent(counter1, theval);
			vhist[state-1]->SetBinError(counter1, theerr);
			counter1++;
		}
		vhist[state-1]->SetLineColor(kRed+state);
		vhist[state-1]->SetMarkerColor(kRed+state);
		if(state ==1) vhist[state-1]->Draw("pe");
		if(state !=1) vhist[state-1]->Draw("same pe");
	TLegend* leg = new TLegend();
	leg->AddEntry(hist1s,"1S", "le");
	leg->AddEntry(hist2s,"2S", "le");
	leg->AddEntry(hist3s,"3S", "le");
	leg->SetX1NDC(0.20);
	leg->SetX2NDC(0.40);
	leg->SetY1NDC(0.85);
	leg->SetY2NDC(0.92);
	leg->Draw("same");
	c1->SaveAs(Form("BDTCorYieldplot_%d_%ld_2.C",state,ts) );
	

}
