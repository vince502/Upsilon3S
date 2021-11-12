#include "../plots/drawRAAplot.cxx"

//For BDT Validation
void DrawYield_Ratio(long ts, int yield_state, int train_state){
	TH1D* hist = new TH1D(Form("Y%dS_train%d",yield_state, train_state),"",20, 0,20);
	
	TCanvas* c1 = new TCanvas("c1","",1000,600);
	c1->cd();
		int counter1 = 2;
		string typestr;
		auto ref = getDoubleRatioValue(false, {0,181},{0,30}, "CB3:CC4:FF", -1,0, 30, yield_state, 1, 9999999999, false, false, 3);
		hist->SetBinContent(1,1);
		hist->SetBinError(1,ref.getError()/ref.getVal());
		for(double bdtv : {-0.9, -0.8 ,-0.6,-0.4, -0.3, -0.2,-0.05,0.0,0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9} )
		{
			std::cout << "BDTV VALUE: " << bdtv << std::endl;
			hist->GetXaxis()->SetBinLabel(counter1,Form("%.2f",bdtv));
			if(bdtv<-0.21) typestr="CB3:CC4:GC";
			if(bdtv>=-0.21) typestr="CB3:CC3:GC";
			RooRealVar cval;
			try{	cval = getDoubleRatioValue(false, {0,181},{0,30}, typestr, bdtv, 0, 30, yield_state, 1, ts, false, false, train_state);
			double theval = cval.getVal();
			double theerr = cval.getError();
			hist->SetBinContent(counter1, theval/ref.getVal());
			hist->SetBinError(counter1, (theval/ref.getVal())*TMath::Sqrt(TMath::Power(theerr/theval,2) + TMath::Power(ref.getError()/ref.getVal(),2)));
			hist->GetYaxis()->SetRangeUser(0.4,2);
			}
			catch(...){ std::cout << "No bin BDT("<< bdtv <<")"<<std::endl;}
			counter1++;
		}
		hist->Draw("pe");
	c1->SaveAs(Form("./CorrYields/BDTCorYieldplot_train%d_%dS_%ld_2.C",train_state,yield_state,ts) );
	TFile* f_out= new TFile(Form("./CorrYields/BDTCorYield_plots_%ld.root",ts), "update");
	f_out->cd();
	hist->Write();
	f_out->Close();

}
