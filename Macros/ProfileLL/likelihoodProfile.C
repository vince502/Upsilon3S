#include "../fitreslib.h"
#include "../BDT/bininfo.h"

void likelihoodProfile(){
//	long ts = 10000000016;
	long ts = 100019111111;
//	long ts = 20000000000;
	auto ab = ana_bm_comb["3c"][0];
	double bl = Get_BDT(ts, ab);
//	double bl = 0.2290;
	auto name_f_res = GetFit(__FITRESLATEST, false, "CB3:EE:GC", ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1., ab.bpl, ab.bph, 0.0, "");
	std::cout << Form("%s", name_f_res.c_str() ) << std::endl;
	auto f_res = TFile::Open(name_f_res.c_str() );
	RooWorkspace* wss = (RooWorkspace*) f_res->Get("workspace");
	RooAbsPdf* thepdf = (RooAbsPdf*) wss->pdf("model");
	RooAbsReal* thenll = thepdf->createNLL( *((RooDataSet*) wss->data("reducedDS") ), RooFit::NumCPU(38) );
//	RooMinimizer(*thenll).migrad();
	RooMinimizer(*thenll).minimize("Minuit","minmize");
	RooRealVar* thevar = (RooRealVar*) wss->var("nSig3S");
	thevar->setRange(-50,650);
	RooPlot* theframe = thevar->frame(140);
	thenll->plotOn(theframe,RooFit::ShiftToZero()) ;

	RooAbsReal* thepll = thenll->createProfile(*thevar);

	thepll->plotOn(theframe,RooFit::LineColor(kRed));


	TCanvas* c1 = new TCanvas("c1", "", 700, 600);
	c1->cd();
	theframe->GetXaxis()->SetRangeUser(0,600);
	theframe->GetYaxis()->SetRangeUser(-5, 20);
	theframe->Draw();
	c1->SaveAs(Form( "LikelihoodPrifole1_minimize_%ld.pdf", ts));
	TFile* output = new TFile(Form ( "LikelihoodProfile1_minimize_%ld.root", ts),"recreate");
	output->cd();
//	thenll->Write();
//	thepll->Write();
	theframe->Write();
	c1->Write();
	output->Close();
	f_res->Close();

}
