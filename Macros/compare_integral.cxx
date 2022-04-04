#include "RooFit.h"
RooWorkspace* ws_b;
RooWorkspace* ws_f;
RooAbsPdf* pdf_b;
RooAbsPdf* pdf_f;
RooRealVar* m_b;
RooRealVar* m_f;
RooAbsReal* int_b;
RooAbsReal* int_f;
RooDataSet* dat_b;
RooDataSet* dat_f;
TH1* hdat_b;
TH1* hdat_f;
TLatex* tl;
string tt1 = "PDFs and data are each normalized to one in the full range";
string tt2 = "y = (blind - full)/(full)";
TLegend* leg;
TCanvas* c1 = new TCanvas();

TGraphAsymmErrors *g, *g2;
auto serv = new THttpServer("http:8081");

auto def_result = [] (double val1, double val2, double ref1, double ref2){
	return std::make_pair(( (val1/ref1) - (val2/ref2) )/ (val2 / ref2) , TMath::Sqrt( sqrt(val1)*sqrt(val1) + (sqrt(val2) *(val1*val1 - 2* val1* val2)/ (val2*val2) )) *fabs( ref2 /(ref1 *val1)));
};


auto doint = [](RooAbsPdf* pdf, RooRealVar* var, double low, double high){
	var->setRange("evalrng",low,high);
	return pdf->createIntegral(RooArgSet(*var),RooFit::Range("evalrng"));
};

auto diff = [](double low, double high, RooAbsPdf* _pdf_b = pdf_b, RooAbsPdf* _pdf_f = pdf_f, RooRealVar* _m_b = m_b, RooRealVar* _m_f = m_f){
	auto res_b = doint(_pdf_b, _m_b, low, high);
	auto res_f = doint(_pdf_f, _m_f, low, high);
	double nom_b = res_b->getVal();
	double nom_f = res_f->getVal();
	auto res_b_ref = doint(_pdf_b, _m_b, 8, 14);
	auto res_f_ref = doint(_pdf_f, _m_f, 8, 14);
	double val_b = nom_b / res_b_ref->getVal();
	double val_f = nom_f / res_f_ref->getVal();
//	std::cout << nom_b << std::endl;
//	std::cout << nom_f << std::endl;
//	std::cout << res_b_ref->getVal() << std::endl;
//	std::cout << res_f_ref->getVal() << std::endl;
	return def_result(val_f, val_b, 1., 1.);
	
};

auto histdiff = [](double low, double high, RooDataSet* _dat_b = dat_b, RooDataSet* _dat_f = dat_f){
	double tot_b = _dat_b->sumEntries(Form("mass>%.4f&&mass<%.4f",8., 14.)) ;
	double tot_f = _dat_f->sumEntries(Form("mass>%.4f&&mass<%.4f",8., 14.)) ;
	double ent_b = _dat_b->sumEntries(Form("mass>%.4f&&mass<%.4f",low, high)) ;
	double ent_f = _dat_f->sumEntries(Form("mass>%.4f&&mass<%.4f",low, high)) ;
	double nom_b = ent_b / tot_b;
	double nom_f = ent_f / tot_f;
//	doubl the err = 
//	std::cout << thediff<< std::endl;
	return def_result(ent_f, ent_b, tot_f, tot_b);
};


void compare_integral(){
	auto fb =   TFile::Open("/home/vince402/shared/Upsilon3S_PostPreApp/Yield_nominal/blind/fit_data_3S_pt_0_30_cent_0_90.root");
	auto ff =   TFile::Open("/home/vince402/shared/Upsilon3S_PostPreApp/Yield_nominal/unblind/fit_data_3S_pt_0_30_cent_0_90.root");

	ws_b = (RooWorkspace*) fb->Get("workspace");
	ws_f = (RooWorkspace*) ff->Get("workspace");
	m_b = (RooRealVar*) ws_b->var("mass");
	m_f = (RooRealVar*) ws_f->var("mass");
	pdf_b = (RooAbsPdf*) ws_b->pdf("model_gc");
	pdf_f = (RooAbsPdf*) ws_f->pdf("model_gc");
	pdf_b->fixAddCoefNormalization(RooArgSet(*m_b));
	pdf_f->fixAddCoefNormalization(RooArgSet(*m_f));
	dat_b = (RooDataSet*) ws_b->data("reducedDS");
	dat_f = (RooDataSet*) ws_f->data("reducedDS");

	double width = 0.1;
	int bins = (int) (14.- 8.)/width;

	

	g =  new TGraphAsymmErrors();
	g2 = new TGraphAsymmErrors();
	for(auto idx : ROOT::TSeqI(bins)){
		auto diff1 = diff(8 + width * idx, 8+ width*(1+idx));
		auto diff2 = histdiff(8 + width * idx, 8+ width*(1+idx));
		g->AddPoint(8+width*(idx + 0.5), diff1.first); 
		g2->AddPoint(8+width*(idx + 0.5), diff2.first);
		g ->SetPointError(idx, 0.5 * width, 0.5* width, diff1.second, diff1.second); 
		g2->SetPointError(idx, 0.5 * width, 0.5* width, diff2.second, diff2.second);
	}
	g->SetMarkerStyle(kFullCircle);
	g->SetMarkerSize(1.4);
	g->SetMarkerColor(kRed);

	g2->SetMarkerStyle(kFullSquare);
	g2->SetMarkerSize(1.4);
	g2->SetMarkerColor(kBlack);

	leg =new TLegend(0.17, 0.6, 0.35, 0.92);
	leg->AddEntry(g, "PDF ratio", "p");
	leg->AddEntry(g2, "Data ratio", "p");

	tl = new TLatex();
	tl->SetTextFont(42);
	tl->SetTextSize(0.032);
	c1->cd();
	g2->GetYaxis()->SetLimits(-0.08, 0.16);
	g2->GetYaxis()->SetRangeUser(-0.08, 0.16);
	g2->Draw("APLE");
	g->Draw("P");
	leg->Draw();



}
