#include "GOF_test.cxx"
#include "sys_wr_helper.cxx"

//struct dst{
//	RooNLLVar nll;
//	RooProfileLL pll;
//	RooRealVar var;
//};
//
//int npar_offset(string bkg){
//	if( strcmp(bkg.c_str(), "EE")==0 ) return 6;
//	if( strcmp(bkg.c_str(), "CC1")==0 ) return 2;
//	if( strcmp(bkg.c_str(), "CC2")==0 ) return 4;
//	if( strcmp(bkg.c_str(), "CC3")==0 ) return 6;
//	if( strcmp(bkg.c_str(), "CC4")==0 ) return 8;
//	else return 0;
//};
//
//void setG(TGraph* g, Color_t c){// ELineStyle l = (unsigned int)  2, EMarkerStyle m = (unsigned int) 20){
//	g->SetLineColor(c);
//	g->SetMarkerColor(c);
//	g->SetMarkerStyle(20);
//	g->SetLineStyle(2);
//};

#ifndef pj
#define pj std::pair< int, int >
#endif

//#include "../BDT/bininfo.h"

pj _DiscreteProfile_2POI(ana_bins x = ana_bm_comb["3c"][0]){
	int pl, ph, cl, ch, state, bpl, bph;
	pl = x.pl; ph = x.ph; cl = x.cl; ch = x.ch; state = x.state; bpl = x.bpl; bph = x.bph;
	int train_state = x.train_state;
	string fittype = (strcmp(x.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	long ts = _TS;
	auto AICres = AICGOF_test(x);
	double bl = Get_BDT(ts_alias(ts), train_state, state, bpl, bph, pl, ph, cl, ch);
	string bkgtype_nom = AICres[0].second;
	string bkgtype_sys1 = AICres[1].second;
	string bkgtype_sys2 = AICres[2].second;

	std::string type_nom = 	Form("CB3:%s:%s",	bkgtype_nom.c_str(),  fittype.c_str());
	std::string type_sys1  =Form("CB3:%s:%s",	bkgtype_sys1.c_str(),  fittype.c_str());
	std::string type_sys2 = Form("CB3:%s:%s",	bkgtype_nom.c_str(),  string( fittype+ "XMCNP").c_str());
	std::string type_sys3 = Form("CB2G:%s:%s",	bkgtype_nom.c_str(),  fittype.c_str());
	std::cout << type_sys1.c_str() << ", " << type_sys2.c_str() << std::endl;

	auto name_f_nom = GetFit(__FITRESLATEST, false, type_nom, ts, x.train_state, x.state, x.pl, x.ph, x.cl, x.ch, bl, 1., x.bpl, x.bph, 0.0, "");
	auto name_f_sys1 = GetFit(__FITRESLATEST, false, type_sys1, ts, x.train_state, x.state, x.pl, x.ph, x.cl, x.ch, bl, 1., x.bpl, x.bph, 0.0, "");
	auto name_f_sys2 = GetFit(__FITRESLATEST, false, type_sys2, ts, x.train_state, x.state, x.pl, x.ph, x.cl, x.ch, bl, 1., x.bpl, x.bph, 0.0, "");
	auto name_f_sys3 = GetFit(__FITRESLATEST, false, type_sys3, ts, x.train_state, x.state, x.pl, x.ph, x.cl, x.ch, bl, 1., x.bpl, x.bph, 0.0, "");
	auto f_nom = TFile::Open(name_f_nom.c_str() );
	auto f_sys1 = TFile::Open(name_f_sys1.c_str() );
	auto f_sys2 = TFile::Open(name_f_sys2.c_str() );
	auto f_sys3 = TFile::Open(name_f_sys3.c_str() );

	auto f_write = new TFile(Form("result_discreteProfile/%ld/FullProfile_Prof_%dS_pt%d-%d_cBin%d-%d_%ld%s.root",_TS, x.state, x.pl, x.ph, x.cl, x.ch, _TS, labDR.c_str()), "recreate" );

	dst theres;
	std::pair<double, double> plt_range;
	auto get_profile = [&] (TFile* input, string pdf, string type){
		RooWorkspace* thews = (RooWorkspace*) input->Get("workspace");
		RooAbsPdf* thepdf = (RooAbsPdf*) thews->pdf("model");
		std::map<string, RooAbsPdf*> m_gc;
		RooArgSet* thearg = new RooArgSet();
		RooLinkedList* fitcmd = new RooLinkedList();

//		RooCmdArg opt1 = RooFit::Save();
//        fitcmd->Add(&opt1);
		RooCmdArg opt2;

   //     RooCmdArg opt4 = RooFit::Minimizer("Minuit","minimize");//"migradimproved");//);
//      RooCmdArg opt4 = RooFit::Minimizer("GSLMultiMin","steepestdescent");//"migradimproved");//);
//        fitcmd->Add(&opt4);
        RooCmdArg opt5 = RooFit::NumCPU(40, 0);
        fitcmd->Add(&opt5);
        RooCmdArg opt6 = RooFit::Range(8, 14);
        fitcmd->Add(&opt6);
        RooCmdArg opt8 = RooFit::Extended(kTRUE);
        fitcmd->Add(&opt8);
//        RooCmdArg opt10= RooFit::Hesse(kTRUE);//RooCmdArg::none();
//        fitcmd->Add(&opt10);
//		RooCmdArg opt11= RooFit::EvalErrorWall(kTRUE);//tRooCmdArg::none();
//        fitcmd->Add(&opt11);
//        RooCmdArg opt12= RooFit::Strategy(2);//tRooCmdArg::none();
//        fitcmd->Add(&opt12);
//        RooCmdArg opt13= RooFit::RecoverFromUndefinedRegions(3);//tRooCmdArg::none();
//        fitcmd->Add(&opt13);
        RooCmdArg opt14= RooFit::BatchMode(kTRUE);//tRooCmdArg::none();
        fitcmd->Add(&opt14);
		if( fittype.find("GC") !=std::string::npos ){
			m_gc["alpha_constraint"]	= (RooAbsPdf*) thews->pdf("alpha_constraint");
			m_gc["n_constraint"] 		= (RooAbsPdf*) thews->pdf("n_constraint");
			m_gc["frac_constraint"] 	= (RooAbsPdf*) thews->pdf("frac_constraint");
			m_gc["frac2_constraint"] 	= (RooAbsPdf*) thews->pdf("frac2_constraint");
			m_gc["xNS_constraint"] 		= (RooAbsPdf*) thews->pdf("xNS_constraint");
			m_gc["xNS_2_constraint"] 	= (RooAbsPdf*) thews->pdf("xNS_2_constraint");
			m_gc["sigmaNS_1_constraint"]= (RooAbsPdf*) thews->pdf("sigmaNS_1_constraint");

			thearg->add(*m_gc["alpha_constraint"]); 	
			thearg->add(*m_gc["n_constraint"]); 		
			thearg->add(*m_gc["frac_constraint"]); 	
			thearg->add(*m_gc["frac2_constraint"]); 	
			thearg->add(*m_gc["xNS_constraint"]); 		
			thearg->add(*m_gc["xNS_2_constraint"]); 	
			thearg->add(*m_gc["sigmaNS_1_constraint"]);

			opt2 = RooFit::Constrain(*thearg);
        	fitcmd->Add(&opt2);
		}
		RooNLLVar* thenll = (RooNLLVar*) thepdf->createNLL( *((RooDataSet*) thews->data("reducedDS") ), *fitcmd); 
		RooMinimizer m(*thenll);
//		RooMinimizer(*thenll).minimize("Minuit","migradimproved");
		m.minimize("Minuit","migradimproved");
//		RooMinimizer(*thenll).migrad();
//		RooMinimizer(*thenll).hesse();
		Double_t minNll = thenll->getVal();
//		RooMinimizer(*thenll).minos();
		RooRealVar* thevar2 = (RooRealVar*) thews->var(Form("nSig2S"));
		RooRealVar* thevar3 = (RooRealVar*) thews->var(Form("nSig3S"));
		RooFormulaVar* thevarcomp = new RooFormulaVar("3Sover2S", "@0/@1", RooArgList(*thevar3, *thevar2)); 
//		thevar->setRange(0, thevar->getVal() + thevar->getError() * 3);
//		plt_range = {0, thevar->getVal() + thevar->getError() * 3};
//		if( strcmp( pdf.c_str(), "nominal") ==0 ){ 
//			RooRealVar* thevar_clone = new RooRealVar(Form("nSig%dS",x.state), "", thevar->getVal());
//			thevar_clone->Write() ;
//			thevar_clone->Clear();
//		}
//		RooPlot* theframe1 = thevar3->frame(40);
//		theframe1->addPlotable(thevar2->frame(40));
//		theframe1->addPlotable(thevar3->frame(40));

		RooArgSet set_poi;
//		set_poi.add(*thevarcomp);
		set_poi.add(*thevar2);
		set_poi.add(*thevar3);
//		RooAbsReal* thepll =  thenll->createProfile(set_poi);
		RooPlot* theframe1 = m.contour(*thevar2, *thevar3);
//		thevar3->setVal(843);
//		thevar2->setVal(2243);
//		std::cout << "[pll var] : " << thepll->getVal() << std::endl;
//		thepll->plotOn(theframe1,  RooFit::Precision(0.01) );
		theframe1->SetName(Form("frame_%s", pdf.c_str() ));
		f_write->cd();
		theframe1->Write();
		thearg->Clear();
		fitcmd->Clear();
		thenll->Clear();
//		thepll->Clear();
		RooCurve* retCurve = new RooCurve(); //(RooCurve*) (theframe1->getCurve())->Clone();
		theframe1->Clear();
		return std::make_pair(minNll + npar_offset(type), retCurve);
	};
	auto res1= get_profile(f_nom, string("nominal"), bkgtype_nom );
	auto theres1 = res1.second;
//	auto res2= get_profile(f_sys1, string("systematic1"), bkgtype_sys1 );
//	auto theres2 = res2.second;
//	auto res3= get_profile(f_sys2, string("systematic2"), bkgtype_nom );
//	auto theres3 = res3.second;
//	auto res4= get_profile(f_sys3, string("systematic3"), bkgtype_nom );
//	auto theres4 = res4.second;
//	auto Ceval1 =[&](double* x, double* p){
//		return min(
//			min ( 
//				min (2* theres1->Eval(x[0]) , 2* theres2->Eval(x[0]) + res2.first - res1.first),
//				2* theres3->Eval(x[0]) + res3.first - res1.first),
//			2* theres4->Eval(x[0]) + res4.first -res1.first);
//	};
//	TF1* the_envelop = new TF1("envelop", Ceval1, plt_range.first, plt_range.second,0);
//	TGraph* g_nom=  new TGraph(); g_nom->SetName("g_nom");
//	TGraph* g_env=  new TGraph(); g_env->SetName("g_env");
//	TGraph* g_sys1= new TGraph(); g_sys1->SetName("g_sys1");
//	TGraph* g_sys2= new TGraph(); g_sys2->SetName("g_sys2");
//	TGraph* g_sys3= new TGraph(); g_sys3->SetName("g_sys3");
//	for( double pt = plt_range.first; pt < plt_range.second; pt +=( plt_range.second - plt_range.first) /500){
//		g_env->AddPoint(pt, Ceval1(&pt, nullptr) );
//		g_nom->AddPoint(pt, 2* theres1->Eval(pt) );
//		g_sys1->AddPoint(pt, 2* theres2->Eval(pt) + res2.first - res1.first);
//		g_sys2->AddPoint(pt, 2* theres3->Eval(pt) + res3.first - res1.first);
//		g_sys3->AddPoint(pt, 2* theres4->Eval(pt) + res4.first - res1.first);
//	}
//	the_envelop->Write();
//	TCanvas* c1 = new TCanvas("c1", "", 600,700);
//	c1->cd(); 
//	g_env->GetXaxis()->SetLimits(0,800);
//	g_env->GetYaxis()->SetLimits(0,40);
//	g_env->GetXaxis()->SetRangeUser(0,800);
//	g_env->GetYaxis()->SetRangeUser(-5,40);
//	setG(g_env, kRed);
//	setG(g_nom, kOrange);
//	setG(g_sys1, kGreen);
//	setG(g_sys2, kBlue);
//	setG(g_sys3, kBlack);
//	g_env->Draw("AL");g_nom->Draw("L");g_sys1->Draw("L");g_sys2->Draw("L");g_sys3->Draw("L");
//	f_write->cd();
//	g_env->Write();
//	g_nom->Write();
//	g_sys1->Write();
//	g_sys2->Write();
//	g_sys3->Write();
//	c1->Write();
//	c1->Clear();
//
//	res1.second->Clear();
//	res2.second->Clear();
//	res3.second->Clear();
//	res4.second->Clear();
//
//	f_write->Close();
//	f_nom->Close();
//	f_sys1->Close();
//	f_sys2->Close();
//	f_sys3->Close();
//	return std::make_pair(theres1, theres2);
	return std::make_pair(0,0);
};



//void _DiscreteProfile(){
//    sys_wr_helper_2item(Form("bkgPDF_unc%s_2item_%ld.root", lx.R.c_str(), _TS), getBkgVariUnc_2item);
//    sys_wr_helper(Form("bkgPDF_unc%s_%ld.root", lx.R.c_str(), _TS), getBkgVariUnc);
//
//};
