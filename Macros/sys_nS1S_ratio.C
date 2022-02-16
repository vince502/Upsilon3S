#include "../.workdir.h"
#include "../CMS_lumi_square.C"

void sys_nS1S_ratio(){
	TFile* f_ns = TFile::Open( Form("%s/Systematics/data/bkgPDF_unc.root", workdir.Data()) ) ;
	TFile* f_1s = TFile::Open( Form("%s/Systematics/data/total_systematics_RAA_AUX1SBKG.root", workdir.Data()) ) ;

	std::map<string , TH1D* > m_ns = {
		{"c2s", (TH1D*) f_ns->Get("rc2S")},
		{"c3s", (TH1D*) f_ns->Get("rc3S")},
		{"p2s", (TH1D*) f_ns->Get("rp2S")},
		{"p3s", (TH1D*) f_ns->Get("rp3S")},
	};
	std::map<string , TH1D* > m_1s = {
		{"c2s", (TH1D*) f_1s->Get("syst_comp/hsys_tot_c2S")},
		{"c3s", (TH1D*) f_1s->Get("syst_comp/hsys_tot_c3S")},
		{"p2s", (TH1D*) f_1s->Get("syst_comp/hsys_tot_p2S")},
		{"p3s", (TH1D*) f_1s->Get("syst_comp/hsys_tot_p3S")},
	};

	TH1D* r_hc2s = (TH1D*) m_1s["c2s"]->Clone("hr_c2s");
	TH1D* r_hc3s = (TH1D*) m_1s["c3s"]->Clone("hr_c3s");
	TH1D* r_hp2s = (TH1D*) m_1s["p2s"]->Clone("hr_p2s");
	TH1D* r_hp3s = (TH1D*) m_1s["p3s"]->Clone("hr_p3s");

	TH1D* n_hc2s = (TH1D*) m_1s["c2s"]->Clone("hn_c2s");
	TH1D* n_hc3s = (TH1D*) m_1s["c3s"]->Clone("hn_c3s");
	TH1D* n_hp2s = (TH1D*) m_1s["p2s"]->Clone("hn_p2s");
	TH1D* n_hp3s = (TH1D*) m_1s["p3s"]->Clone("hn_p3s");
	
	std::cout << 1/n_hc2s->GetMaximum()<< std::endl;
	std::cout << 1/m_ns["c2s"]->GetMaximum()<< std::endl;

	n_hc2s->Scale(1 / n_hc2s->GetBinContent(n_hc2s->GetMaximumBin() ) );
	n_hc3s->Scale(1 / n_hc3s->GetBinContent(n_hc3s->GetMaximumBin() ) );
	n_hp2s->Scale(1 / n_hp2s->GetBinContent(n_hp2s->GetMaximumBin() ) );
	n_hp3s->Scale(1 / n_hp3s->GetBinContent(n_hp3s->GetMaximumBin() ) );

	m_ns["c2s"]->Scale(1 / m_ns["c2s"]->GetBinContent( m_ns["c2s"]->GetMaximumBin() ) );
	m_ns["c3s"]->Scale(1 / m_ns["c3s"]->GetBinContent( m_ns["c3s"]->GetMaximumBin() ) );
	m_ns["p2s"]->Scale(1 / m_ns["p2s"]->GetBinContent( m_ns["p2s"]->GetMaximumBin() ) );
	m_ns["p3s"]->Scale(1 / m_ns["p3s"]->GetBinContent( m_ns["p3s"]->GetMaximumBin() ) );

	n_hc2s->SetFillColorAlpha(kRed+3,0.5);
	n_hc3s->SetFillColorAlpha(kRed+3,0.5);
	n_hp2s->SetFillColorAlpha(kRed+3,0.5);
	n_hp3s->SetFillColorAlpha(kRed+3,0.5);

	n_hc2s->GetYaxis()->SetRangeUser(0,1.3);
	n_hc3s->GetYaxis()->SetRangeUser(0,1.3);
	n_hp2s->GetYaxis()->SetRangeUser(0,1.3);
	n_hp3s->GetYaxis()->SetRangeUser(0,1.3);

	m_ns["c2s"]->SetLineWidth(2);
	m_ns["c3s"]->SetLineWidth(2);
	m_ns["p2s"]->SetLineWidth(2);
	m_ns["p3s"]->SetLineWidth(2);

	m_ns["c2s"]->SetFillColorAlpha(kBlue-2, 0.5);
	m_ns["c3s"]->SetFillColorAlpha(kBlue-2, 0.5);
	m_ns["p2s"]->SetFillColorAlpha(kBlue-2, 0.5);
	m_ns["p3s"]->SetFillColorAlpha(kBlue-2, 0.5);


	r_hc2s->Divide(m_ns["c2s"]);
	r_hc3s->Divide(m_ns["c3s"]);
	r_hp2s->Divide(m_ns["p2s"]);
	r_hp3s->Divide(m_ns["p3s"]);

	TCanvas* c1 =new TCanvas("c1", "", 1600, 1400);
	c1->Divide(2,2);
	c1->cd(1);
	r_hc2s->Draw("hist");
	c1->cd(2);
	r_hc3s->Draw("hist");
	c1->cd(3);
	r_hp2s->Draw("hist");
	c1->cd(4);
	r_hp3s->Draw("hist");


	TLegend* leg = new TLegend(0.75, 0.6, 0.87, 0.72);
	leg->AddEntry(n_hc2s, "1S unc.", "lf");
	leg->AddEntry(m_ns["c2s"], "nS unc.", "lf");
	leg->SetBorderSize(0);
	TLatex* tl = new TLatex();
	tl->SetTextSize(0.045);
	tl->SetTextFont(42);
	TCanvas* c2 =new TCanvas("c2", "", 1600, 1400);
	c2->Divide(2,2);
	c2->cd(1);
	n_hc2s->Draw("hist");
	m_ns["c2s"]->Draw("hist,same");
	tl->DrawLatexNDC(0.21, 0.8, "2S Centrality");
	leg->Draw();
	c2->cd(2);
	n_hc3s->Draw("hist");
	m_ns["c3s"]->Draw("hist,same");
	tl->DrawLatexNDC(0.21, 0.8, "3S Centrality");
	leg->Draw();
	c2->cd(3);
	n_hp2s->Draw("hist");
	m_ns["p2s"]->Draw("hist,same");
	tl->DrawLatexNDC(0.21, 0.8, "2S p_{T}");
	leg->Draw();
	c2->cd(4);
	n_hp3s->Draw("hist");
	m_ns["p3s"]->Draw("hist,same");
	tl->DrawLatexNDC(0.21, 0.8, "3S p_{T}");
	leg->Draw();

	CMS_lumi_square((TPad*) c2->GetPad(1), 31, 33) ;
	CMS_lumi_square((TPad*) c2->GetPad(2), 31, 33) ;
	CMS_lumi_square((TPad*) c2->GetPad(3), 31, 33) ;
	CMS_lumi_square((TPad*) c2->GetPad(4), 31, 33) ;

	c1->SaveAs("../checkout/syst_nS1S_ratio.pdf");
	c2->SaveAs("../checkout/syst_nS1S_scaled.pdf");
}
