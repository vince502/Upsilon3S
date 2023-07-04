#include "../BDT/bininfo.h"
#include "../BDT/BDTtraindiff.cxx"
#include "../glauberparams_PbPb5TeV.h"
#include <iostream>
#include <fstream>


void analysis_plots_crossSection(){

	TFile* f = TFile::Open("/home/vince402/Upsilon3S/plots/result/RAA_2100019111111_1S_result_2Sbin.root");
	TFile* f2 = TFile::Open("/home/vince402/Upsilon3S/plots/result/RAA_2100019111111_1S_result_2Sbin_2Snominal.root");

	auto rp = (TH1D*) f->Get("rp2S"); // This is correct in 23 Jun 2023, as it is written in plot_wr_helper.cxx, drawPlot_v2.cxx
	auto rc = (TH1D*) f->Get("rc2S"); // Same, using 2S bin for 1S measurement

	auto rp2 = (TH1D*) f2->Get("rp2S"); // This is correct in 23 Jun 2023, as it is written in plot_wr_helper.cxx, drawPlot_v2.cxx
	auto rc2 = (TH1D*) f2->Get("rc2S"); // Same, using 2S bin for 1S measurement

	double binpt[6] = {0., 3., 6., 9., 15., 30.};
//	double bincent[9] = {0., 3., 6., 9., 15., 30.};
	TH1D* hpt = new TH1D("hpt", "", 5, binpt);
	TH1D* hpt2 = new TH1D("hpt2", "", 5, binpt);

	for( auto idx : ROOT::TSeqI(5) ){
		hpt->SetBinContent(idx+1, rp->GetBinContent(idx+1));
		hpt->SetBinError(idx+1, rp->GetBinError(idx+1));
		hpt2->SetBinContent(idx+1, rp2->GetBinContent(idx+1));
		hpt2->SetBinError(idx+1, rp2->GetBinError(idx+1));
	}

	double binptref[7] = {0., 2., 4., 6., 9., 12., 30.};
	TH1D* hpt_16023= new TH1D("hptref", "", 6, binptref );
	hpt_16023->SetBinContent(1, 0.0307);
	hpt_16023->SetBinContent(2, 0.0699);
	hpt_16023->SetBinContent(3, 0.0684);
	hpt_16023->SetBinContent(4, 0.0374);
	hpt_16023->SetBinContent(5, 0.0163);
	hpt_16023->SetBinContent(6, 0.0020);

	auto _quadsum = [](double a, double b){
		return TMath::Sqrt(a*a + b*b);
	};

	hpt_16023->SetBinError(1, _quadsum(0.0026 , 0.0116 ) );
	hpt_16023->SetBinError(2, _quadsum(0.0052 , 0.0053 ) );
	hpt_16023->SetBinError(3, _quadsum(0.0056 , 0.0047 ) );
	hpt_16023->SetBinError(4, _quadsum(0.0025 , 0.0021 ) );
	hpt_16023->SetBinError(5, _quadsum(0.0013 , 0.0017 ) );
	hpt_16023->SetBinError(6, _quadsum(0.0001 , 0.0001 ) );

	setTDRStyle();
	TCanvas* c1 = new TCanvas("c1", "", 800, 700) ;
	TPad* p1 = new TPad("p1", "", 0.,0., 1.,1.);
	c1->cd();
	p1->Draw();
	p1->cd();

	hpt->SetMarkerStyle(kFullSquare);
	hpt->SetMarkerColor(kRed);
	hpt->SetLineColor(kRed);

	hpt2->SetMarkerStyle(kFullStar);
	hpt2->SetMarkerColor(kGreen-3);
	hpt2->SetLineColor(kGreen-3);

	hpt_16023->SetMarkerStyle(kFullCircle);
	hpt_16023->SetMarkerColor(kBlue);
	hpt_16023->SetLineColor(kBlue);

	TLegend* leg = new TLegend(0.52, 0.40, 0.89, 0.63);

	leg->SetTextFont(42);
	leg->SetTextSize(0.036);
	leg->SetBorderSize(0);
	leg->AddEntry(hpt, "PbPb 2018", "lpe");
	leg->AddEntry(hpt2, "PbPb 2018 2S Selection", "lpe");
	leg->AddEntry(hpt_16023, "PbPb 2015", "lpe");

	hpt->GetYaxis()->SetTitle("B#times(1#lower[0.2]{#kern[0.2]{#scale[1.5]{#it{/}}}}#it{T}_{#kern[-0.2]{AA}})#times d^{2}#font[122]{N}#lower[0.2]{#kern[0.2]{#scale[1.5]{#it{/}}}}d#it{y}d#it{p}_{T} (nb / GeV)");
	hpt->GetXaxis()->SetTitle("#it{p}_{T} (GeV)");
	hpt->GetYaxis()->SetRangeUser(0., 0.08);
	hpt->Draw("PE");
	hpt2->Draw("same PE");
	hpt_16023->Draw("same PE");

	leg->Draw("same");

	CMS_lumi_square(p1, 2, 33, 2);
	c1->Modified();
	c1->Update();
	c1->SaveAs("../checkout/CrossSection_1S_wComp_review.pdf");

}
