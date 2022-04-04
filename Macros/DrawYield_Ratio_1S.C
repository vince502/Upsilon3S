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


RooRealVar getRAAValue1S(bool inc_pp_stat, ana_bins ab, std::string type = "CB3:CC2:GC", double custom_bl  = -2, double custom_bh = 1, int getPre = 0,long ts =9999999999, bool stdvcut = false, bool eff_old = false){
	int cl, ch, pl, ph, state, train_state, bpl, bph;
	cl = ab.cl; ch = ab.ch;
	pl = ab.pl; ph = ab.ph;
	bpl = ab.bpl; bph = ab.bph;
	state = ab.state; train_state = ab.train_state;
	double val_bdt_nom = Get_BDT(ts, ab);
	double bdt_upper =custom_bh;
	std::cout << "[getDRV] val_bdt_nom : " << val_bdt_nom << std::endl;
	
	double ylim = 2.4;
	if(custom_bl >= -1 ) val_bdt_nom = custom_bl;
	
	binplotter* bp ;
	
	double app_cutQVP = (stdvcut) ? 0.01 : 0.0000;
	bp = new binplotter(type,ts, ylim, (double) pl, (double) ph, cl, ch, app_cutQVP, val_bdt_nom, bdt_upper, bpl, bph, train_state, state, false, eff_old);
	
	RooRealVar _y = bp->get_yield(1);
	if(getPre==2) return _y;
	RooRealVar _yacc = upsi::getacceptance(pl,ph, (double) -1*ylim, ylim, 3.5, state);
	auto _yeff_pair = bp->get_eff(1);
	double _yeff = _yeff_pair.first;
	RooRealVar yAA, yPP ;
	yAA = RooRealVar(Form("corrY%dyield",state), Form("corrected %dS yield",state), _y.getVal()/(_yacc.getVal()*_yeff));
	std::cout <<"##Yield "<<state<<"S Corrected y/acc eff: "<< yAA.getVal() << ", Efficiency: " << _yeff << ", Acceptance: " << _yacc.getVal() << std::endl;
	yAA.setError(_y.getError()/(_yacc.getVal()*_yeff ));
	std::cout << "\n\n\n YAA ERROR : " << yAA.getError() << "\n\n" << std::endl;
	if(getPre==1) return yAA;
	TFile* file_pp =TFile::Open(Form("/home/CMS/Analysis/Upsilon3S_pp2017Ref/Results/results_%dS.root",state));
	
	TH1D *h_cs_pp = (!(pl == 0 && ph == 30)) ? (TH1D*) file_pp->Get("hptData") : (TH1D*) file_pp->Get("hintData");
	
	double cs_pp, cs_err;
	if((pl == 0 && ph == 30 )){
	  cs_pp = h_cs_pp->GetBinContent(1);
	  cs_err = h_cs_pp->GetBinError(1);
	}
	else{
	  cs_pp = h_cs_pp->GetBinContent(ab.plot_idx);
	  cs_err = h_cs_pp->GetBinError(ab.plot_idx);
	}
	Double_t Nmb = 11968044281.;
	auto taa =glp::Taa[{ab.centl,ab.centh}];
	double lum_scale = 1 *TMath::Power(10,6);
	
	Double_t trig_presc = 1.0684;
	Double_t taa_Nmb = 4.8*(ph-pl)*taa.first*Nmb/(trig_presc);
	Double_t step_one = (lum_scale)/(taa_Nmb * cs_pp);
	Double_t step_one_err  = -(cs_err*lum_scale)/(taa_Nmb * cs_pp * cs_pp );
	Double_t step_two = step_one * (90./(ab.centh - ab.centl) );
	Double_t step_two_err = step_one_err * (90./(ab.centh - ab.centl));
	Double_t val_RAA = 4.*step_two*yAA.getVal();
	Double_t val_RAA_err;
	std::cout << "step 2 err and yAA err : " << 4* step_two_err*yAA.getVal() << ", " << 4*step_two * yAA.getError()/val_RAA << std::endl;
	if(inc_pp_stat) val_RAA_err = TMath::Sqrt(TMath::Power(4*step_two_err* yAA.getVal(),2) + TMath::Power(2*step_two * yAA.getError(),2)); 
	if(!inc_pp_stat) val_RAA_err = step_two * yAA.getError(); 
	std::cout << std::endl << std::endl << Form(" taa_Nmb: %.3f, cs_pp : %.9f,  step_one: %.16f, step_two %.16f ", taa_Nmb, cs_pp,  (double) step_one, (double) step_two) << std::endl << std::endl;
	std::cout << std::endl << std::endl << "Projected RAA : " << val_RAA << std::endl << std::endl;
	std::cout << "\n\n\n step 2 err and yAA err : " << 4* step_two_err*yAA.getVal() << ", " << step_two * yAA.getError() << "\n\n" << std::endl;
	
	RooRealVar val_return = RooRealVar("raa","", val_RAA);
	val_return.setError(val_RAA_err);
	
	return val_return;
};

//For BDT Validation
void DrawYield_Ratio_1S(ana_bins ab , long ts = _TS){
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
	auto nom = getRAAValue1S(false, ab, Form("CB3:EE:%s", fittype.c_str()) , bl, 1., 1, ts, false, false); 

	auto ref2 = getRAAValue1S(false, ab, "CB3:CC4:FF", -1, 1., 1, ts, true, false);
//	auto ref2 = getRAAValue1S(false, ab, Form("CB3:CC4:%s", fittype.c_str()) , -1, 1., 0, ts, false, false);

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
		try{	cval = getRAAValue1S(false, ab, typestr, bdtv, 1., 1, ts, false, false);
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

		
	c1->SaveAs(Form("./CorrYields/BDTCorYieldplot_train%d_%dS_pt%d_%d_cent%d_%d_%ld_2.C",ab.train_state,1, ab.pl, ab.ph, ab.centl, ab.centh,ts) );
	if( ts == _TS){
		c1->SaveAs(Form("./CorrYieldsPlot/BDTCorYieldplot_train%d_%dS_pt%d_%d_cent%d_%d.pdf",ab.train_state,1, ab.pl, ab.ph, ab.centl, ab.centh) );
	}
	else{
		c1->SaveAs(Form("./CorrYieldsPlot/BDTCorYieldplot_train%d_%dS_pt%d_%d_cent%d_%d_ts%ld.pdf",ab.train_state,1, ab.pl, ab.ph, ab.centl, ab.centh, ts) );
	}
	
	TFile* f_out= new TFile(Form("./CorrYields/BDTCorYield_plots_%ld.root",ts), "update");
	f_out->cd();
	hist->Write();
	f_out->Close();

};

void DrawYield_Ratio_1S(){
	for( auto abv : ana_bm_comb){
		for( auto ab : abv.second){

			if(ab.bintype == kCent) DrawYield_Ratio_1S(ab, _TS);
		}
	}
};
