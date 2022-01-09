#include <iostream>
#include "bininfo.h"
#include "../.workdir.h"
#include "../upsilonAna.h"
#include "yield_eff_signif.h"
#include "TApplication.h"


std::pair<double,TGraph*> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, double ratio =0.16 , int train_state =3, int sig_state = 2, int bdtptMin =0, int bdtptMax = 30, string name_input_opt = "", string formula_significance= "S2", string the_opt="", bool save = true)
{
	//Header
	std::string st_opt;
	if(strcmp(name_input_opt.c_str(),"")!=0) st_opt = "_"+name_input_opt;
	std::string output_fname = Form("%s/BDT/Significance_hist/HIST_train%dS_for%dS_bdtpt_%d_%d_%ld_pt_%d-%d_rap_%d-%d_cbin_%d-%d_vp_%.4f_%s%s", workdir.Data(), train_state, sig_state, bdtptMin, bdtptMax, ts, (int) ptMin, (int) ptMax, (int) (rapMin*10), (int) (rapMax*10), cBinLow, cBinHigh, cutQVP, formula_significance.c_str(), st_opt.c_str() );
	TFile* HISTFILE = nullptr;
	HISTFILE = new TFile(Form("%s.root",output_fname.c_str()), "update" );
	std::cout << static_cast<void*>(HISTFILE) << std::endl;
	
	TList* lok =nullptr;
	lok= HISTFILE->GetListOfKeys();
	if (!(lok->FindObject(Form("r_%.6f", ratio))==nullptr) || !(lok->FindObject(Form("r_%.6f%s", ratio, the_opt.c_str()))==nullptr) ){
		std::cout << "[INFO] Reading From HISTOFILE, key : " << the_opt.c_str() << std::endl;
		string dirname = Form("r_%.6f", ratio);
		if ( the_opt.find("SYS") != std::string::npos) { dirname = dirname+""+ the_opt; }

		std::cout << dirname.c_str() << std::endl;
		double theSig = stod(HISTFILE->Get(Form("%s/max_sig", dirname.c_str()) )->GetTitle());
		TGraph*   theHist = (TGraph*) HISTFILE->Get(Form("%s/HISTO", dirname.c_str()) );
		TGraph* cloneHist = (TGraph*)  theHist->Clone();
//		cloneHist->SetDirectory(0);
		HISTFILE->Close();
		return std::make_pair(theSig, cloneHist);
	}

  
	string tag_BLIND = "BLIND";
	std::string name_input = Form("%s/BDT/BDTResult/BDTresultY3S_%ld_%s%s.root", workdir.Data(), ts, name_input_opt.c_str(), tag_BLIND.c_str());
	TFile* file_bdtres = TFile::Open(name_input.c_str());

	string name_h_effS_1 = Form("data/Y%dSpt%dto%d/dataset1/Method_BDT/BDT/MVA_BDT_effS",train_state, (int) ptMin, (int) ptMax);
	string name_h_effB_1 = Form("data/Y%dSpt%dto%d/dataset1/Method_BDT/BDT/MVA_BDT_effB",train_state, (int) ptMin, (int) ptMax);
	string name_h_effS_2 = Form("data/Y%dSpt%dto%d/dataset2/Method_BDT/BDT/MVA_BDT_effS",train_state, (int) ptMin, (int) ptMax);
	string name_h_effB_2 = Form("data/Y%dSpt%dto%d/dataset2/Method_BDT/BDT/MVA_BDT_effB",train_state, (int) ptMin, (int) ptMax);

	TH1D *h_effS, *h_effB;
	TH1D *h_effS_1, *h_effS_2, *h_effB_1, *h_effB_2;
	h_effS_1 = (TH1D*) file_bdtres->Get(name_h_effS_1.c_str());
	h_effB_1 = (TH1D*) file_bdtres->Get(name_h_effB_1.c_str());
	h_effS_2 = (TH1D*) file_bdtres->Get(name_h_effS_2.c_str());
	h_effB_2 = (TH1D*) file_bdtres->Get(name_h_effB_2.c_str());

	double h_eff_xmin = max(h_effS_1->GetXaxis()->GetXmin() , h_effS_2->GetXaxis()->GetXmin() ); 
	double h_eff_xmax = min(h_effS_1->GetXaxis()->GetXmax() , h_effS_2->GetXaxis()->GetXmax() ); 
	int nbins_tot = h_effS_1->GetNbinsX() + h_effS_2->GetNbinsX();

	TGraph* g_signif = new TGraph();
	double sig_lim_bdt1 = 2;
	double sig_lim_bdt2 = 2;
	double sample_rate = 0.1;
	int nPoints_sampled = 0;
	auto signif = [=](double sig, double bkg){
		return ((sig*ratio)/(TMath::Sqrt(sig*ratio + bkg)));
	};
	for(int idx =1; idx < h_effS_1->GetNbinsX() +1; idx ++){
		if((idx%(int) (1/sample_rate)==0)){
			nPoints_sampled ++;
			double effS_1 = h_effS_1->GetBinContent(idx);
			double bc_1 = h_effS_1->GetBinCenter(idx);
			double effS_2 = h_effS_2->GetBinContent(idx);
			double bc_2 = h_effS_2->GetBinCenter(idx);
//			std::cout << "[GOB] 1 graph x, y : " << bc_1 << ", " << signif(effS_1, h_effB_1->GetBinContent(idx)) << std::endl;
			g_signif->AddPoint((bc_1 + bc_2)/2, (signif(effS_1, h_effB_1->GetBinContent(idx)) + signif(effS_2, h_effB_2->GetBinContent(idx)))/2 );
			if((effS_1 +effS_2)/2 <0.1 && sig_lim_bdt1 > 1 ) sig_lim_bdt1 = ( h_effS_1->GetBinCenter(idx) + h_effS_2->GetBinCenter(idx) )/2;
//			std::cout << "[GOB] 2 graph x, y : " << bc_2 << ", " << signif(effS_2, h_effB_2->GetBinContent(idx)) << std::endl;
//			g_signif->AddPoint(bc_2,signif(effS_2, h_effB_2->GetBinContent(idx)));
//			if(effS_2 <0.1 && sig_lim_bdt2 > 1 ) sig_lim_bdt2 = h_effS_2->GetBinCenter(idx);
		}
	}
//	for(int idx =1; idx < h_effS_2->GetNbinsX() +1; idx ++){
//		double effS = h_effS_2->GetBinContent(idx);
//		double bc = h_effS_2->GetBinCenter(idx);
//
//	}

	TF1* sig_model = new TF1("Msignif","pol9",h_eff_xmin, h_eff_xmax);//interval_score*(zero_bin)-0.5);
	ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2", "Simplex");

	g_signif->Fit("Msignif","MFR","",h_eff_xmin, h_eff_xmax);//interval_score*(zero_bin)-0.5);
	g_signif->Draw();
	auto res = g_signif->GetFunction("Msignif");
	double max_signif_bdt= res->GetMaximumX(h_eff_xmin, h_eff_xmax);//interval_score*(zero_bin)-0.5);//  h_signif->GetBinCenter(h_signif->GetMaximumBin() );
	max_signif_bdt = min(max_signif_bdt, sig_lim_bdt1);
	max_signif_bdt = min(max_signif_bdt, sig_lim_bdt2);
	double max_signif_val = TMath::MaxElement(nPoints_sampled, g_signif->GetY() );
//	return std::make_pair(smax_signif_bdttd::make_pair(max_signif_bdt, max_signif_val), h_signif );


	//Footer	
	file_bdtres->Close();
	
	TDirectory* dir_ratio;
	
	if(the_opt.find("SYS") != std::string::npos){
	dir_ratio = HISTFILE->mkdir(Form("r_%.6f%s", ratio,the_opt.c_str()), "");
	}
	else {
	  dir_ratio = HISTFILE->mkdir(Form("r_%.6f", ratio), "");
	}
	
	HISTFILE->cd();
	dir_ratio->cd();
	g_signif->SetName("HISTO");
	g_signif->SetTitle("significance vs BDT");
	g_signif->Write();
	TNamed* max_value = new TNamed("max_sig",Form("%.4f",max_signif_bdt));
	max_value->Write();
	
	string BDTkey = "latest";
	if(the_opt.find("SYS") != std::string::npos) BDTkey += "_" + the_opt;
	HISTFILE->cd();
	TNamed* latest = new TNamed(BDTkey.c_str(), max_value->GetTitle() );
	latest->Write(0,TTree::kOverwrite);
	HISTFILE->Close();
//	cache_out->Close();
	
	Get_Optimal_BDT_HIST = g_signif;
	return std::make_pair(max_signif_bdt, g_signif);
}




//Function to get BDT ratio //
RooRealVar get_eff_acc(std::string type, std::string type2, long ts, long ts2, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int bdtptMin= 0, int bdtptMax =30, int train_state = 3, int state1 =1, int state2 =3, bool eff_old = true){
  RooRealVar eff22, eff21, eff1, eff2, nbkg;

  binplotter* bp = new binplotter(type, ts, ylim,pl, ph, cl, ch, blow, bhigh, bdtptMin, bdtptMax, train_state, train_state, false, eff_old);
  binplotter* bp2 = new binplotter(type2, ts2, ylim,pl, ph, cl, ch, 0.01, -1, bhigh, bdtptMin, bdtptMax, train_state, train_state, false, eff_old);
  std::cout << bp->res->GetName() << std::endl;
  bp->dump();
  bp2->dump();
  bp->get_yield();
  nbkg = bp2->get_bkg();
  auto frac_nS = bp->get_frac(state2);
  RooRealVar yield1S = bp2->get_yield(state1);
  auto effp1 = bp->get_eff(state1);
  auto effp2 = bp->get_eff(state2);
  auto eff2p1 = bp2->get_eff(state1);
  auto eff2p2 = bp2->get_eff(state2);
  eff2= RooRealVar(Form("eff%d",state2), "", effp2.first);
  eff2.setError(effp2.second);
  eff1= RooRealVar(Form("eff%d",state1), "", effp1.first);
  eff1.setError(effp1.second);
  eff22= RooRealVar(Form("eff%d",state2), "", eff2p2.first);
  eff22.setError(eff2p2.second);
  eff21= RooRealVar(Form("eff%d",state1), "", eff2p1.first);
  eff21.setError(eff2p1.second);

  double ratio_acceff = ((eff1.getVal()*eff22.getVal())/(eff2.getVal()*eff21.getVal()));
  double ratio_val = (frac_nS.getVal() * yield1S.getVal())/nbkg.getVal();
  double ratio_err = ratio_val * TMath::Sqrt( TMath::Power( frac_nS.getError()/ frac_nS.getVal(),2) + TMath::Power( yield1S.getError()/ yield1S.getVal(),2) + TMath::Power( nbkg.getError()/ nbkg.getVal(), 2) );
  std::cout << "YIELD: " << nbkg.getVal() << ", "<< yield1S.getVal()*frac_nS.getVal() << std::endl;
  std::cout << "EFF: " << eff1.getVal() << ", "<< eff2.getVal() << std::endl;
  std::cout << "ACC: " << eff22.getVal() << ", "<< eff21.getVal() << std::endl;
  std::cout << "RESULT: " <<ratio_acceff << ", "<< ratio_val << std::endl;

  RooRealVar res_var = RooRealVar("result","",ratio_acceff*ratio_val);
  res_var.setError(ratio_err);// res_var.getVal()*TMath::Sqrt( TMath::Power(eff22.getError()/eff22.getVal(),2) + TMath::Power(eff21.getError()/eff21.getVal(),2) + TMath::Power(eff1.getError()/eff1.getVal(),2) + TMath::Power(eff2.getError()/eff2.getVal(),2) + TMath::Power(nbkg.getError()/nbkg.getVal(),2) + TMath::Power(yield3S.getError()/yield3S.getVal(),2) ) ); 
  return res_var;
  
};




RooRealVar get_eff_acc(std::string type, std::string type2, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int bdtptMin= 0, int bdtptMax =30, int train_state = 3 ,int state1 =1, int state2 =3, bool eff_old = true){
	return	get_eff_acc(type, type2, ts, ts, ylim, pl, ph, cl, ch, blow, bhigh,bdtptMin, bdtptMax,  train_state, state1, state2, eff_old);
};
RooRealVar get_eff_acc(std::string type, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh,  int bdtptMin= 0, int bdtptMax =30,int train_state = 3,int state1 =1, int state2 =3, bool eff_old = true){
	return	get_eff_acc(type, "CB3:CC4:FF", ts, 9999999999, ylim, pl, ph, cl, ch, blow, bhigh, bdtptMin, bdtptMax, train_state, state1, state2, eff_old);
};





//Function to get BDT ratio //
RooRealVar get_eff_acc_v2(std::string type, std::string type2, long ts, long ts2, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int bdtptMin= 0, int bdtptMax =30, int train_state = 3, int state1 =1, int state2 =3, bool eff_old = true){
  RooRealVar eff22, eff21, eff1, eff2, nbkg;

//  binplotter* bp = new binplotter(type, ts, ylim,pl, ph, cl, ch, blow, bhigh, bdtptMin, bdtptMax, train_state, train_state, false, eff_old);
  binplotter* bp2 = new binplotter(type2, ts2, ylim,pl, ph, cl, ch, 0.01, -1, bhigh, bdtptMin, bdtptMax, train_state, train_state, false, eff_old);
  bp2->get_yield();
  nbkg = bp2->get_bkg();
  RooWorkspace* wsp = (RooWorkspace*) bp2->file1->Get("workspace");
  auto ccpdf = (TF1*) wsp->pdf("CCBkg")->asTF(*(wsp->var("mass")));
  double bkg_under_sig_ratio = ccpdf->Integral(8.8,10.7)/ccpdf->Integral(8,14);
  std::cout << "[get_eff_acc_v2] bkg tot: " <<  ccpdf->Integral(8,14) <<", bkg under sig: " << ccpdf->Integral(8.8,10.7) << std::endl;
  std::cout << "[get_eff_acc_v2] bkg ratio " <<  bkg_under_sig_ratio << std::endl;
  double nSigTot = bp2->yield3S.getVal() + bp2->yield2S.getVal() + bp2->yield1S.getVal(); 
  double nSigTotErr = TMath::Sqrt(bp2->yield3S.getError() * bp2->yield3S.getError() + bp2->yield2S.getError() * bp2->yield2S.getError() + bp2->yield1S.getError()* bp2->yield1S.getError()); 
  
  double ratio_val = nSigTot/(nbkg.getVal()*bkg_under_sig_ratio);
  double ratio_err = ratio_val * TMath::Sqrt( (nSigTotErr/nSigTot)*(nSigTotErr/nSigTot) + (nbkg.getError()/nbkg.getVal())*(nbkg.getError()/nbkg.getVal())); 

  RooRealVar res_var = RooRealVar("result","",ratio_val);
  res_var.setError(ratio_err); 
  return res_var;
};
RooRealVar get_eff_acc_v2(std::string type, std::string type2, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int bdtptMin= 0, int bdtptMax =30, int train_state = 3 ,int state1 =1, int state2 =3, bool eff_old = true){
	return	get_eff_acc_v2(type, type2, ts, ts, ylim, pl, ph, cl, ch, blow, bhigh,bdtptMin, bdtptMax,  train_state, state1, state2, eff_old);
};
RooRealVar get_eff_acc_v2(std::string type, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh,  int bdtptMin= 0, int bdtptMax =30,int train_state = 3,int state1 =1, int state2 =3, bool eff_old = true){
	return	get_eff_acc_v2(type, "CB3:CC4:FF", ts, 9999999999, ylim, pl, ph, cl, ch, blow, bhigh, bdtptMin, bdtptMax, train_state, state1, state2, eff_old);
};

RooRealVar get_eff_acc_v3(std::string type, std::string type2, long ts, long ts2, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int bdtptMin= 0, int bdtptMax =30, int train_state = 3, int state1 =1, int state2 =3, bool eff_old = true){
  RooRealVar eff22, eff21, eff1, eff2, nbkg;

//  binplotter* bp = new binplotter(type, ts, ylim,pl, ph, cl, ch, blow, bhigh, bdtptMin, bdtptMax, train_state, train_state, false, eff_old);
  binplotter* bp2 = new binplotter(type2, ts2, ylim,pl, ph, cl, ch, 0.01, -1, bhigh, bdtptMin, bdtptMax, train_state, train_state, false, eff_old);
  bp2->get_yield();
  nbkg = bp2->get_bkg();
  double nSigTot = bp2->yield3S.getVal() + bp2->yield2S.getVal(); 
  double nSigTotErr = TMath::Sqrt(bp2->yield3S.getError() * bp2->yield3S.getError() + bp2->yield2S.getError() * bp2->yield2S.getError() ); 
  
  double ratio_val = nSigTot/nbkg.getVal();
  double ratio_err = ratio_val * TMath::Sqrt( (nSigTotErr/nSigTot)*(nSigTotErr/nSigTot) + (nbkg.getError()/nbkg.getVal())*(nbkg.getError()/nbkg.getVal())); 

  RooRealVar res_var = RooRealVar("result","",ratio_val);
  res_var.setError(ratio_err); 
  return res_var;
};
RooRealVar get_eff_acc_v3(std::string type, std::string type2, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int bdtptMin= 0, int bdtptMax =30, int train_state = 3 ,int state1 =1, int state2 =3, bool eff_old = true){
	return	get_eff_acc_v3(type, type2, ts, ts, ylim, pl, ph, cl, ch, blow, bhigh,bdtptMin, bdtptMax,  train_state, state1, state2, eff_old);
};
RooRealVar get_eff_acc_v3(std::string type, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh,  int bdtptMin= 0, int bdtptMax =30,int train_state = 3,int state1 =1, int state2 =3, bool eff_old = true){
	return	get_eff_acc_v3(type, "CB3:CC4:FF", ts, 9999999999, ylim, pl, ph, cl, ch, blow, bhigh, bdtptMin, bdtptMax, train_state, state1, state2, eff_old);
};
