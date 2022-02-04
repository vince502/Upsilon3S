#define _TS 10000000016

#if _TS == 9999999999 && __has_include("../LLR_CCorder_9999999999.h")
#   include "../LLR_CCorder_9999999999.h"
#   define getNomBkgO getNomBkgO_9999999999
#endif

#if _TS == 10000000016 && __has_include("../LLR_CCorder_10000000016.h")
#   include "../LLR_CCorder_10000000016.h"
#   define getNomBkgO getNomBkgO_10000000016
#endif

#if _TS == 10000000003 && __has_include("../LLR_CCorder_10000000003.h")
#   include "../LLR_CCorder_10000000003.h"
#   define getNomBkgO getNomBkgO_10000000003
#endif

#if _TS != 9999999999
#   define ana_bm ana_bm_comb
#endif

#include "../BDT/bininfo.h"
#include "../plots/measurement.cxx"


//For BDT Validation
void DrawYield_Ratio(ana_bins ab , long ts = _TS){
	gStyle->SetEndErrorSize(0);
	std::vector<double> use_bins = {-0.8,-0.6, -0.4,-0.2,0.0, 0.2, 0.4, 0.6, 0.8};
	int NBDTbins = use_bins.size() +2;
	TH1D* hist = new TH1D(Form("Y%dS_train%d",ab.state, ab.train_state) ,"" ,NBDTbins , use_bins.front() - ( (double)NBDTbins - (double) use_bins.size() )*(use_bins.back() - use_bins.front())/((double) use_bins.size()-1.), use_bins.back());
	auto hist_norm = (TH1D*) hist->Clone("hist_norm");
	hist->SetStats(0);
	hist_norm->SetStats(0);
	
	TCanvas* c1 = new TCanvas("c1","",1800,600);
	c1->Divide(2);
	c1->cd(1);
	int counter1 = NBDTbins +1 - use_bins.size();
	string typestr;
	
	double bl = Get_BDT(ts, ab);
	std::cout <<"bl : " <<  bl << std::endl;
	string fittype  = (ab.bintype == kCent) ? "FF" : "GC" ;
	auto nom = getRAAValue(false, ab, Form("CB3:EE:%s", fittype.c_str()) , bl, 1., 0, ts, false, false); 

	auto ref2 = getRAAValue(false, ab, "CB3:CC4:FF", -1, 1., 0, ts, true, false);
//	auto ref2 = getRAAValue(false, ab, Form("CB3:CC4:%s", fittype.c_str()) , -1, 1., 0, ts, false, false);

	hist->SetBinContent(1,nom.getVal());
	hist->SetBinError(1,2*nom.getError());
	hist->SetBinContent(2,ref2.getVal());
	hist->SetBinError(2,2*ref2.getError());
//	hist->SetBinContent(3,ref.getVal());
//	hist->SetBinError(3,2*ref.getError());
	hist_norm->SetBinContent(1,1);
	hist_norm->SetBinError(1,2*nom.getError()/ nom.getVal());
	hist_norm->SetBinContent(2,ref2.getVal() / nom.getVal());
	hist_norm->SetBinError(2,(ref2.getVal()/nom.getVal())*TMath::Sqrt(TMath::Power(2*ref2.getError()/ref2.getVal(),2) + TMath::Power(2*nom.getError()/nom.getVal(),2)));//2*ref2.getError()/ ref2.getVal()
//	hist_norm->SetBinContent(3,ref.getVal() / nom.getVal());
//	hist_norm->SetBinError(3,(ref.getVal()/nom.getVal())*TMath::Sqrt(TMath::Power(2*ref.getError()/ref.getVal(),2) + TMath::Power(2*nom.getError()/nom.getVal(),2)));//2*ref.getError()/ ref.getVal()
	hist->GetXaxis()->SetBinLabel(1,"Nominal");
	hist_norm->GetXaxis()->SetBinLabel(1,"Nominal");
	hist->GetXaxis()->SetBinLabel(2,"-1.0");
	hist_norm->GetXaxis()->SetBinLabel(2,"-1.0");
//	hist->GetXaxis()->SetBinLabel(3,"No BDT cut");
//	hist_norm->GetXaxis()->SetBinLabel(3,"No BDT cut");

//	for(double bdtv : {-0.9, -0.8 ,-0.6,-0.4, -0.3, -0.2,-0.05,0.0,0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9} )
	for(double bdtv : use_bins )
	{
		std::cout << "BDTV VALUE: " << bdtv << std::endl;
		hist->GetXaxis()->SetBinLabel(counter1,Form("%.2f",bdtv));
		hist_norm->GetXaxis()->SetBinLabel(counter1,Form("%.2f",bdtv));
		string fittype = (ab.bintype == kCent) ? "FF" : "GC"; 
		typestr=Form("CB3:CC4:%sbdtup",fittype.c_str() );
		RooRealVar cval;
		try{	cval = getRAAValue(false, ab, typestr, bdtv, 1., 0, ts, false, false);
		double theval = cval.getVal();
		double theerr = cval.getError();
		if( fabs(theval) ==TMath::Infinity() ) { std::cout << "INF! " << std::endl;  theval = 1;}
		if( fabs(theerr) ==TMath::Infinity() ) { std::cout << "INF! " << std::endl; theerr = 1; }
		hist->SetBinContent(counter1, theval);
		hist->SetBinError(counter1,2*theerr);// (theval/ref.getVal())*TMath::Sqrt(TMath::Power(theerr/theval,2) + TMath::Power(ref.getError()/ref.getVal(),2)));

		hist_norm->SetBinContent(counter1, theval/ nom.getVal());
		hist_norm->SetBinError(counter1, (theval/nom.getVal())*TMath::Sqrt(TMath::Power(2*theerr/theval,2) + TMath::Power(2*nom.getError()/nom.getVal(),2)));

		}
		catch(...){ std::cout << "No bin BDT("<< bdtv <<")"<<std::endl;}
		counter1++;
	}
	hist->GetYaxis()->SetRangeUser(nom.getVal() - 10* nom.getError(),nom.getVal() + 9* nom.getError());
	hist->GetYaxis()->SetTitle("R_{AA}");
	hist->GetYaxis()->CenterTitle();
	hist_norm->GetYaxis()->SetRangeUser(0, 2.7);
	hist->Draw("pe");
	TLatex* tl = new TLatex();
	tl->SetTextSize(0.037);
	tl->SetTextFont(52);
	TLine* linenom = new TLine();
	linenom->SetLineStyle(kDashed);
	linenom->SetLineWidth(2);
	TMarker* p_one = new TMarker(bl, nom.getVal(), kFullCircle );
	p_one->SetMarkerSize(1.3);
	p_one->SetMarkerColor(kRed);

	linenom->DrawLine(bl, nom.getVal() - 10* nom.getError(), bl, nom.getVal() + 9* nom.getError());
	p_one->Draw();
	tl->DrawLatexNDC(0.15, 0.83, "R_{AA} without pp error, not projected yield");
	CMS_lumi_square((TPad*) c1->GetPad(1), 102, 33) ;
	c1->cd(2);
	hist_norm->GetYaxis()->SetTitle("R_{AA}");
	hist_norm->GetYaxis()->CenterTitle();
	hist_norm->Draw("pe");
	linenom->DrawLine(bl, 0, bl, 2.7);
	auto p_unit = (TMarker*) p_one->Clone();
	p_unit->SetY(1);
	p_unit->Draw();

	tl->DrawLatexNDC(0.15, 0.83, "nomalized R_{AA} without pp error, not projected yield");
	CMS_lumi_square((TPad*) c1->GetPad(2), 102, 33) ;

		
	c1->SaveAs(Form("./CorrYields/BDTCorYieldplot_train%d_%dS_pt%d_%d_cent%d_%d_%ld_2.C",ab.train_state,ab.state, ab.pl, ab.ph, ab.centl, ab.centh,ts) );
	c1->SaveAs(Form("./CorrYieldsPlot/BDTCorYieldplot_train%d_%dS_pt%d_%d_cent%d_%d.pdf",ab.train_state,ab.state, ab.pl, ab.ph, ab.centl, ab.centh) );
	
	TFile* f_out= new TFile(Form("./CorrYields/BDTCorYield_plots_%ld.root",ts), "update");
	f_out->cd();
	hist->Write();
	f_out->Close();

};

void DrawYield_Ratio(){
	for( auto abv : ana_bm_comb){
		for( auto ab : abv.second){

			if(ab.bintype == kCent) DrawYield_Ratio(ab, _TS);
		}
	}
};
