#include "../../fitreslib.h"
#include "../../BDT/bininfo.h"

void likelihoodProfileUB(){
//	long ts = 10000000016;
//	long ts = 20000000000;
	long ts = 200019111111;
	auto ab = ana_bm_comb["3c"][0];
//	double bl = Get_BDT(ts, ab);
	double bl = 0.2620;
	auto name_f_res = GetFit(__FITRESLATEST, false, "CB3:EE:GC", ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1., ab.bpl, ab.bph, 0.0, "");
	auto f_res = TFile::Open(name_f_res.c_str() );
	RooWorkspace* wss = (RooWorkspace*) f_res->Get("workspace");
	RooAbsPdf* thepdf = (RooAbsPdf*) wss->pdf("model");
	RooAbsReal* thenll = thepdf->createNLL( *((RooDataSet*) wss->data("reducedDS") ), RooFit::NumCPU(38), RooFit::BatchMode(kTRUE) );
	RooMinimizer(*thenll).minimize("Minuit", "minimize");
	RooMinimizer(*thenll).hesse();
	RooMinimizer(*thenll).minos();
	RooRealVar* thevar = (RooRealVar*) wss->var("nSig3S");
	thevar->setRange(-50,1700);
	RooPlot* theframe = thevar->frame(140);
	thenll->plotOn(theframe,RooFit::ShiftToZero()) ;

	RooAbsReal* thepll = thenll->createProfile(*thevar);

	thepll->plotOn(theframe,RooFit::LineColor(kRed));


	TCanvas* c1 = new TCanvas("c1", "", 700, 600);
	c1->cd();
	theframe->Draw();
	theframe->GetXaxis()->SetRangeUser(0,1700);
	theframe->GetYaxis()->SetRangeUser(-5, 70);
	c1->SaveAs(Form("LikelihoodPrifoleUB%ld_minimize_v2.pdf", ts) );
	TFile* output = new TFile(Form("LikelihoodProfileUB%ld_minimize_v2.root",ts),"recreate");
	output->cd();
//	thenll->Write();
//	thepll->Write();
	theframe->Write();
	c1->Write();
	output->Close();
	f_res->Close();

}
