#include "../CMS_lumi_square.C"

TFile* fin = TFile::Open("result/resultRAA_2100019111111_raw_v3.root");
THttpServer* serv= new THttpServer("http:8081");
TCanvas* c1 =new TCanvas() ;


void fit_linear_ptRaa(){
	c1->SetRightMargin(0.08);
	gStyle->SetEndErrorSize(0);
	auto g2s = (TGraphAsymmErrors*) fin->Get("vanila/g_p2s");
	auto g3s = (TGraphAsymmErrors*) fin->Get("vanila/g_p3s");

	TF1* f2s_pol0 = new TF1("f2s_pol0", "pol0", 0, 30);
	TF1* f2s_pol1 = new TF1("f2s_pol1", "pol1", 0, 30);
	TF1* f3s_pol0 = new TF1("f3s_pol0", "pol0", 0, 30);
	TF1* f3s_pol1 = new TF1("f3s_pol1", "pol1", 0, 30);
	
	f2s_pol0->SetLineColor(kRed);
	f2s_pol1->SetLineColor(kBlue);
	f3s_pol0->SetLineColor(kRed);
	f3s_pol1->SetLineColor(kBlue);

	f2s_pol0->SetLineStyle(1);
	f2s_pol1->SetLineStyle(1);
	f3s_pol0->SetLineStyle(2);
	f3s_pol1->SetLineStyle(2);

	g2s->Fit(f2s_pol0);
	g2s->Fit(f2s_pol1);
	g3s->Fit(f3s_pol0);
	g3s->Fit(f3s_pol1);

	TLatex* tl = new TLatex();
	tl->SetTextSize(0.035);
	tl->SetTextFont(42);
	
	TLegend* leg = new TLegend(0.25 ,0.42, 0.80, 0.61);
	leg->SetTextSize(0.035);
	leg->SetTextFont(42);
	leg->SetBorderSize(0);
	leg->SetNColumns(2);
	leg->AddEntry(g2s, "#Upsilon(2S)", "pe");
	leg->AddEntry(g3s, "#Upsilon(3S)", "pe");
	leg->AddEntry(f2s_pol0, "constant fit", "l");
	leg->AddEntry(f3s_pol0, "constant fit", "l");
	leg->AddEntry(f2s_pol1, "linear fit", "l");
	leg->AddEntry(f3s_pol1, "linear fit", "l");
//	leg->AddEntry((TObject*)0, "", "");

	c1->cd();
	g2s->GetYaxis()->SetRangeUser(0,0.5);
	g2s->Draw("APE");
	g3s->Draw("PE");

	tl->DrawLatex( 2.5, 0.44 , "|#it{y}| < 2.4");
	tl->DrawLatex( 2.5, 0.40 , "Cent. 0-90 %");

	f2s_pol0->Draw("same");
	f3s_pol0->Draw("same");

//	tl->DrawLatex(12,0.325, Form("#color[4]{Y3S y = %.3f x + %.3f, #chi^{2}/ndf = %.1f/%d}",f3s_pol1->GetParameter(0) ,f3s_pol1->GetParameter(1),f3s_pol1->GetChisquare(),f3s_pol1->GetNDF() ));
//	tl->DrawLatex(12,0.30, Form("#color[2]{Y3S y = %.3f, #chi^{2}/ndf = %.1f/%d}",f3s_pol0->GetParameter(0), f3s_pol0->GetChisquare(),f3s_pol0->GetNDF() ));
//
//	tl->DrawLatex(12,0.255, Form("#color[4]{Y2S y = %.3f x + %.3f, #chi^{2}/ndf = %.1f/%d}",f2s_pol1->GetParameter(0) ,f2s_pol1->GetParameter(1),f2s_pol1->GetChisquare(),f2s_pol1->GetNDF() ));
//	tl->DrawLatex(12,0.23, Form("#color[2]{Y2S y = %.3f, #chi^{2}/ndf = %.1f/%d}",f2s_pol0->GetParameter(0), f2s_pol0->GetChisquare(),f2s_pol0->GetNDF() ));
	leg->Draw();

	
	CMS_lumi_square(c1, 2, 33);
	c1->SaveAs("~/Upsilon3S/checkout/fitRAA_pt_pol_v2.pdf");
}
