#include "../CMS_lumi_square.C"

TFile* fin = TFile::Open("resultDR_200019111111_raw_v3.root");
THttpServer* serv= new THttpServer("http:8081");
TCanvas* c1 =new TCanvas() ;

void fit_linear_ptDR(){
	gStyle->SetOptFit(kFALSE);
	auto g3s = (TGraphAsymmErrors*) fin->Get("vanila/g_p23s");
	g3s->GetYaxis()->SetTitleOffset(1.05);

	TF1* f3s_pol0 = new TF1("f3s_pol0", "pol0", 0, 30);
	TF1* f3s_pol1 = new TF1("f3s_pol1", "pol1", 0, 30);
	
	f3s_pol0->SetLineColor(kRed);
	f3s_pol1->SetLineColor(kBlue);

	f3s_pol0->SetLineStyle(2);
	f3s_pol1->SetLineStyle(2);
	TLatex* tl = new TLatex();
	tl->SetTextSize(0.035);
	tl->SetTextFont(42);



	auto fitres1 = g3s->Fit(f3s_pol0);
	auto fitres2 = g3s->Fit(f3s_pol1);

	c1->cd();
	g3s->GetYaxis()->SetRangeUser(0,1.2);
	g3s->Draw("APE");
	f3s_pol0->Draw("same");
	f3s_pol1->Draw("same");

	tl->DrawLatex(2,1.0, Form("#color[4]{y = %.5f x + %.5f, #chi^{2}/ndf = %.1f/%d}",f3s_pol1->GetParameter(0) ,f3s_pol1->GetParameter(1),f3s_pol1->GetChisquare(),f3s_pol1->GetNDF() ));
	tl->DrawLatex(2,0.9, Form("#color[2]{y = %.5f, #chi^{2}/ndf = %.1f/%d}",f3s_pol0->GetParameter(0), f3s_pol0->GetChisquare(),f3s_pol0->GetNDF() ));

	CMS_lumi_square(c1, 2, 33);	
	c1->SaveAs("~/Upsilon3S/checkout/fitDR_pt_pol.pdf");
}
