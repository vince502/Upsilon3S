#include "GOF_test.cxx"
#include "sys_wr_helper.cxx"

struct dst{
	RooNLLVar nll;
	RooProfileLL pll;
	RooRealVar var;
};

int npar_offset(string bkg){
	if( strcmp(bkg.c_str(), "EE")==0 ) return 6;
	if( strcmp(bkg.c_str(), "CC1")==0 ) return 2;
	if( strcmp(bkg.c_str(), "CC2")==0 ) return 4;
	if( strcmp(bkg.c_str(), "CC3")==0 ) return 6;
	if( strcmp(bkg.c_str(), "CC4")==0 ) return 8;
	else return 0;
};

#ifndef pj
#define pj std::pair< int, int >
#endif

//#include "../BDT/bininfo.h"

pj _BkgDiscreteProfile(ana_bins x = ana_bm_comb["3c"][0]){
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
	std::string type_sys2 = Form("CB3:%s:%s",	bkgtype_sys2.c_str(),  fittype.c_str());
	std::cout << type_sys1.c_str() << ", " << type_sys2.c_str() << std::endl;

	auto name_f_nom = GetFit(__FITRESLATEST, false, type_nom, ts, x.train_state, x.state, x.pl, x.ph, x.cl, x.ch, bl, 1., x.bpl, x.bph, 0.0, "");
	auto name_f_sys1 = GetFit(__FITRESLATEST, false, type_sys1, ts, x.train_state, x.state, x.pl, x.ph, x.cl, x.ch, bl, 1., x.bpl, x.bph, 0.0, "");
	auto name_f_sys2 = GetFit(__FITRESLATEST, false, type_sys2, ts, x.train_state, x.state, x.pl, x.ph, x.cl, x.ch, bl, 1., x.bpl, x.bph, 0.0, "");
	auto f_nom = TFile::Open(name_f_nom.c_str() );
	auto f_sys1 = TFile::Open(name_f_sys1.c_str() );
	auto f_sys2 = TFile::Open(name_f_sys2.c_str() );

	auto f_write = new TFile(Form("testOut_2UBProf_%ld.root", _TS), "recreate" );

	dst theres;
	std::pair<double, double> plt_range;
	auto get_profile = [&] (TFile* input, string pdf, string type){
		RooWorkspace* thews = (RooWorkspace*) input->Get("workspace");
		RooAbsPdf* thepdf = (RooAbsPdf*) thews->pdf("model");
		std::map<string, RooAbsPdf*> m_gc;
		RooArgSet* thearg = new RooArgSet();
		RooLinkedList* fitcmd = new RooLinkedList();

		RooCmdArg opt1 = RooFit::Save();
        fitcmd->Add(&opt1);
		RooCmdArg opt2;

        RooCmdArg opt4 = RooFit::Minimizer("Minuit","minimize");//"migradimproved");//);
//      RooCmdArg opt4 = RooFit::Minimizer("GSLMultiMin","steepestdescent");//"migradimproved");//);
        fitcmd->Add(&opt4);
        RooCmdArg opt5 = RooFit::NumCPU(40, 0);
        fitcmd->Add(&opt5);
        RooCmdArg opt6 = RooFit::Range(8, 14);
        fitcmd->Add(&opt6);
        RooCmdArg opt8 = RooFit::Extended(kTRUE);
        fitcmd->Add(&opt8);
        RooCmdArg opt10= RooFit::Hesse(kTRUE);//RooCmdArg::none();
        fitcmd->Add(&opt10);
		RooCmdArg opt11= RooFit::EvalErrorWall(kTRUE);//tRooCmdArg::none();
        fitcmd->Add(&opt11);
        RooCmdArg opt12= RooFit::Strategy(2);//tRooCmdArg::none();
        fitcmd->Add(&opt12);
        RooCmdArg opt13= RooFit::RecoverFromUndefinedRegions(3);//tRooCmdArg::none();
        fitcmd->Add(&opt13);
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
		RooAbsReal* thenll =  thepdf->createNLL( *((RooDataSet*) thews->data("reducedDS") ), *fitcmd); 
		RooMinimizer(*thenll).minimize("Minuit","minimize");
		RooMinimizer(*thenll).hesse();
		Double_t minNll = thenll->getVal();
	dbg(11);
//		RooMinimizer(*thenll).minos();
		RooRealVar* thevar = (RooRealVar*) thews->var("nSig3S");
		thevar->setRange(0, thevar->getVal() + thevar->getError() * 5);
		plt_range = {0, thevar->getVal() + thevar->getError() * 5};
		if( strcmp( pdf.c_str(), "nominal") ==0 ){ 
			RooRealVar* thevar_clone = new RooRealVar("nSig3S", "", thevar->getVal());
			thevar_clone->Write() ;
		}
		RooPlot* theframe1 = thevar->frame(50);

		RooAbsReal* thepll =  thenll->createProfile(*thevar);
//		std::cout 
		thepll->plotOn(theframe1, RooFit::Bins(1), RooFit::Precision(1) );
		theframe1->SetName(Form("frame_%s", pdf.c_str() ));
		f_write->cd();
		theframe1->Write();
		return std::make_pair(minNll + npar_offset(type), (RooCurve*) theframe1->getCurve());
	};
	auto res1= get_profile(f_nom, string("nominal"), "EE" );
	auto theres1 = res1.second;
	auto res2= get_profile(f_sys1, string("systematic"), "CC4" );
	auto theres2 = res2.second;
	auto Ceval1 =[&theres1, &res1, &res2, &theres2](double* x, double* p){
		return min(theres1->Eval(x[0]) , theres2->Eval(x[0]) + res2.first - res1.first);
	};
	TF1* the_envelop = new TF1("envelop", Ceval1, plt_range.first, plt_range.second,0);
	the_envelop->Write();
	 
	f_write->Close();
//	return std::make_pair(theres1, theres2);
	return std::make_pair(0,0);
};



//void _BkgDiscreteProfile(){
//    sys_wr_helper_2item(Form("bkgPDF_unc%s_2item_%ld.root", lx.R.c_str(), _TS), getBkgVariUnc_2item);
//    sys_wr_helper(Form("bkgPDF_unc%s_%ld.root", lx.R.c_str(), _TS), getBkgVariUnc);
//
//};
