#include "Graphix.h"
#include "../.workdir.h"
#include "Style_HIN-21-007.C"
#include "../CMS_lumi_square.C"

void ViewTrainDiff(bool isDR = false, const char* sym = "c"){
    auto getG = [](long ts, bool dr, string namegraph){
      string dir = (string) workdir + "/plots/result";
      std::cout << Form("%s", dir.c_str()) << std::endl;
      string fname = (!dr) ? Form("%s/resultRAA_%ld_raw_v3.root", dir.c_str(), ts) : Form("%s/resultDR_%ld_raw_v3.root", dir.c_str(), ts);
      TFile* f = TFile::Open(Form("%s",fname.c_str()));
      auto g = (TGraphAsymmErrors*) f->Get(Form("vanila/%s", namegraph.c_str()));
      if( g == nullptr ) std::cout << "Could not get " << namegraph.c_str() << std::endl;
      auto gx = Graphix<TGraphAsymmErrors>(g);
      f->Close();
      return gx;
    };

    std::map<string, Graphix<TGraphAsymmErrors> > vG;
	TFile* f_noBDT = TFile::Open("~/Upsilon3S/plots/result/RAA_noBDT_CC4.root");
	TH1D* h_2p_noBDT = new TH1D("res_noBDT_h2p", "", 5, (Double_t[6]) {0.,3.,6,9.,15.,30.} ); 
	TH1D* h_3p_noBDT = new TH1D("res_noBDT_h3p", "", 4, (Double_t[5]) {0.,4.,9,15.,30.} ); 
	auto h2p = (TH1D*) f_noBDT->Get("rp2S");
	auto h3p = (TH1D*) f_noBDT->Get("rp3S");
	for( auto idx : ROOT::TSeqI( 5 ) ){
		h_2p_noBDT->SetBinContent(idx+1, h2p->GetBinContent(idx+1) );
		h_2p_noBDT->SetBinError(idx+1, h2p->GetBinError(idx+1) );
	}
	for( auto idx : ROOT::TSeqI( 4 ) ){
		h_3p_noBDT->SetBinContent(idx+1, h3p->GetBinContent(idx+1) );
		h_3p_noBDT->SetBinError(idx+1, h3p->GetBinError(idx+1) );
	}
	if( !isDR ){
		const char* sty = (strcmp(sym, "c") == 0) ? "CENT" : "PT";
		const double shift_val = ( strcmp(sym, "c") ==0 ) ? 1 : 0.0;
		std::cout << Form("4000_%s2s, %s", sym, sty ) << std::endl;
	    vG[Form("2000_%s2s", sym)]  = getG(200019111111, 0, Form("g_%s2s", sym)	);
	    vG[Form("2000_%s3s", sym)]  = getG(200019111111, 0, Form("g_%s3s", sym)	);
	    vG[Form("4000_%s2s", sym)]  = getG(400019111111, 0, Form("g_%s2s", sym)	);
	    vG[Form("4000_%s3s", sym)]  = getG(400019111111, 0, Form("g_%s3s", sym)	);
	    vG[Form("21000_%s2s", sym)]  = getG(2100019111111, 0, Form("g_%s2s", sym)	);
	    vG[Form("21000_%s3s", sym)]  = getG(2100019111111, 0, Form("g_%s3s", sym)	);
	
	    vG[Form("2000_%s2s_sys", sym)]  = getG(200019111111, 0, Form("g_%s2s_sys", sym))	;
	    vG[Form("2000_%s3s_sys", sym)]  = getG(200019111111, 0, Form("g_%s3s_sys", sym))	;
	    vG[Form("4000_%s2s_sys", sym)]  = getG(400019111111, 0, Form("g_%s2s_sys", sym))	;
	    vG[Form("4000_%s3s_sys", sym)]  = getG(400019111111, 0, Form("g_%s3s_sys", sym))	;
	    vG[Form("21000_%s2s_sys", sym)]  = getG(2100019111111, 0, Form("g_%s2s_sys", sym));
	    vG[Form("21000_%s3s_sys", sym)]  = getG(2100019111111, 0, Form("g_%s3s_sys", sym));
		std::cout << vG[Form("4000_%s2s", sym)].getObject()->GetName() << std::endl;
		std::cout << vG[Form("4000_%s2s_sys", sym)].getObject()->GetName() << std::endl;
		vG[Form("4000_%s2s", sym)].shiftBins(shift_val, false);
		vG[Form("4000_%s3s", sym)].shiftBins(shift_val, false);
		vG[Form("4000_%s2s_sys", sym)].shiftBins(shift_val, false);
		vG[Form("4000_%s3s_sys", sym)].shiftBins(shift_val, false);
		vG[Form("21000_%s2s", sym)].shiftBins(shift_val*2, false);
		vG[Form("21000_%s3s", sym)].shiftBins(shift_val*2, false);
		vG[Form("21000_%s2s_sys", sym)].shiftBins(shift_val*2, false);
		vG[Form("21000_%s3s_sys", sym)].shiftBins(shift_val*2, false);
	
		readyPlot(vG[Form("2000_%s2s", sym)] .getObject(),    vG[Form("2000_%s2s_sys", sym)] .getObject(), Form("CA2S%s", sty));  
		readyPlot(vG[Form("2000_%s3s", sym)] .getObject(),    vG[Form("2000_%s3s_sys", sym)] .getObject(), Form("CA3S%s", sty));
		readyPlot(vG[Form("4000_%s2s", sym)] .getObject(),    vG[Form("4000_%s2s_sys", sym)] .getObject(), Form("A2A2S%s", sty));  
		readyPlot(vG[Form("4000_%s3s", sym)] .getObject(),    vG[Form("4000_%s3s_sys", sym)] .getObject(), Form("A2A3S%s", sty));
		readyPlot(vG[Form("21000_%s2s", sym)].getObject(),    vG[Form("21000_%s2s_sys", sym)].getObject(), Form("AA2S%s", sty), 0);
		readyPlot(vG[Form("21000_%s3s", sym)].getObject(),    vG[Form("21000_%s3s_sys", sym)].getObject(), Form("AA3S%s", sty), 0);

		h_2p_noBDT->SetMarkerStyle(kCircle);
		h_2p_noBDT->SetMarkerSize(2);
		h_2p_noBDT->SetMarkerColor(kAzure + 1);
		
		h_2p_noBDT->SetLineWidth(1);
		h_2p_noBDT->SetFillColorAlpha(kAzure, 0.5);
		h_2p_noBDT->SetFillStyle(3345);
		h_2p_noBDT->GetYaxis()->SetRangeUser(-0.1,0.8);
//		h_2p_noBDT->GetYaxis()->SetLimit(-0.1,0.8);
		h_3p_noBDT->SetMarkerStyle(kCircle);
		h_3p_noBDT->SetMarkerSize(2);
		h_3p_noBDT->SetMarkerColor(kSpring - 2);
		h_3p_noBDT->SetLineWidth(1);
		h_3p_noBDT->SetFillColorAlpha(kSpring- 3, 0.5);
		h_3p_noBDT->SetFillStyle(3354);
		h_3p_noBDT->GetYaxis()->SetRangeUser(-0.1,0.8);
//		h_3p_noBDT->GetYaxis()->SetLimit(-0.1,0.8);
	
	    TCanvas* c1 =new TCanvas("c1", "", 1920, 1080);
	    c1->cd();
		TLegend* leg = new TLegend(0.6, 0.53, 0.87, 0.85);
		TLegend* leg2 = new TLegend(0.6, 0.53, 0.87, 0.85);
		TLegend* leg3 = new TLegend(0.6, 0.40, 0.87, 0.53);
		leg->SetBorderSize(0);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.021);
		leg->SetTextFont(42);
		leg2->SetBorderSize(0);
		leg2->SetFillStyle(0);
		leg2->SetTextSize(0.021);
		leg2->SetTextFont(42);

	    leg->AddEntry(vG[Form("2000_%s2s", sym)].getObject(),"Nominal 2S", "lp");
	    leg->AddEntry(vG[Form("2000_%s3s", sym)].getObject(),"Nominal 3S", "lp");
	    leg->AddEntry(vG[Form("4000_%s2s", sym)].getObject(),"Full data p_{T} differential training 2S", "lp");
	    leg->AddEntry(vG[Form("4000_%s3s", sym)].getObject(),"Full data p_{T} differential training 3S", "lp");
		if( strcmp( sym, "p") == 0){
	    leg->AddEntry(vG[Form("21000_%s2s", sym)].getObject(), "Integrated training set 2S", "lp");
	    leg->AddEntry(vG[Form("21000_%s3s", sym)].getObject(), "Integrated training set 2S", "lp");
		}

	    leg2->AddEntry(vG[Form("2000_%s2s_sys", sym)].getObject(),"Nominal 2S", "f");
	    leg2->AddEntry(vG[Form("2000_%s3s_sys", sym)].getObject(),"Nominal 3S", "f");
	    leg2->AddEntry(vG[Form("4000_%s2s_sys", sym)].getObject(),"Full data p_{T} differential training 2S", "f");
	    leg2->AddEntry(vG[Form("4000_%s3s_sys", sym)].getObject(),"Full data p_{T} differential training 3S", "f");
		if( strcmp( sym, "p") == 0){
	    leg2->AddEntry(vG[Form("21000_%s2s_sys", sym)].getObject(), "Integrated training set 2S", "f");
	    leg2->AddEntry(vG[Form("21000_%s3s_sys", sym)].getObject(), "Integrated training set 2S", "f");
		leg3->AddEntry(h_2p_noBDT, "Selection w/o BDT selection stat. error only, 2S", "pf");
		leg3->AddEntry(h_3p_noBDT, "Selection w/o BDT selection stat. error only, 3S", "pf");
		}

	    vG[Form("2000_%s2s_sys", sym)].getObject()->GetYaxis()->SetRangeUser(-0.1, 0.9);
	
	    vG[Form("2000_%s2s_sys", sym)].getObject()->Draw("A5");
	    vG[Form("2000_%s3s_sys", sym)].getObject()->Draw("5");
	    vG[Form("4000_%s2s_sys", sym)].getObject()->Draw("5");
	    vG[Form("4000_%s3s_sys", sym)].getObject()->Draw("5");
		if( strcmp( sym, "p") == 0){
	    vG[Form("21000_%s2s_sys", sym)].getObject()->Draw("5");
	    vG[Form("21000_%s3s_sys", sym)].getObject()->Draw("5");
		}
	    vG[Form("2000_%s2s", sym)].getObject()->Draw("PE");
	    vG[Form("2000_%s3s", sym)].getObject()->Draw("PE");
	    vG[Form("4000_%s2s", sym)].getObject()->Draw("PE");
	    vG[Form("4000_%s3s", sym)].getObject()->Draw("PE");
		if( strcmp( sym, "p") == 0){
	    vG[Form("21000_%s2s", sym)].getObject()->Draw("PE");
	    vG[Form("21000_%s3s", sym)].getObject()->Draw("PE");
		h_2p_noBDT->Draw("LE2 same");
		h_3p_noBDT->Draw("LE2 same");
		}
		leg->Draw("same");
		leg2->Draw("same");
		if( strcmp( sym, "p") == 0){
			leg3->Draw("same");
		}
	
	
		c1->SaveAs(Form("%s/checkout/tscol/TrainDiffResult_2000-21000_%s_v2.pdf", workdir.Data(), sty));
	}
	if( isDR ){
	    vG["2000_p23s"]  = getG(200019111111, 1, "g_p23s");
	    vG["4000_p23s"]  = getG(400019111111, 1, "g_p23s");
	    vG["21000_p23s"]  = getG(2100019111111, 1, "g_p23s");
	
	    vG["2000_p23s_sys"]  = getG(200019111111, 1, "g_p23s_sys");
	    vG["4000_p23s_sys"]  = getG(400019111111, 1, "g_p23s_sys");
	    vG["21000_p23s_sys"]  = getG(2100019111111, 1, "g_p23s_sys");
		vG["4000_p23s"].shiftBins(0.5, false);
		vG["4000_p23s_sys"].shiftBins(0.5, false);
		vG["21000_p23s"].shiftBins(0.5 *2, false);
		vG["21000_p23s_sys"].shiftBins(0.5 *2, false);
	
		readyPlot(vG["2000_p23s"] .getObject(),    vG["2000_p23s_sys"] .getObject(), Form("CA3SPT"));  
		readyPlot(vG["4000_p23s"] .getObject(),    vG["4000_p23s_sys"] .getObject(), Form("A2A2SPT"));  
		readyPlot(vG["21000_p23s"].getObject(),    vG["21000_p23s_sys"].getObject(), Form("AA3SPT"));
	
	    TCanvas* c1 =new TCanvas("c1", "", 1920, 1080);
	    c1->cd();
		TLegend* leg = new TLegend(0.6, 0.7, 0.87, 0.86);
		TLegend* leg2 = new TLegend(0.6, 0.7, 0.87, 0.86);
		leg->SetBorderSize(0);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.021);
		leg->SetTextFont(42);
		leg2->SetBorderSize(0);
		leg2->SetFillStyle(0);
		leg2->SetTextSize(0.021);
		leg2->SetTextFont(42);
	    leg->AddEntry(vG["2000_p23s"].getObject(),"Nominal 3S/2S", "lp");
	    leg->AddEntry(vG["4000_p23s"].getObject(),"Full data p_{T} differential training 3S/2S", "lp");
	    leg->AddEntry(vG["21000_p23s"].getObject(), "Integrated training set 3S/2S", "lp");

	    leg2->AddEntry(vG["2000_p23s_sys"].getObject(),"Nominal 3S/2S", "f");
	    leg2->AddEntry(vG["4000_p23s_sys"].getObject(),"Full data p_{T} differential training 3S/2S", "f");
	    leg2->AddEntry(vG["21000_p23s_sys"].getObject(), "Integrated training set 3S/2S", "f");
	    vG["2000_p23s_sys"].getObject()->Draw("A5");
	    vG["4000_p23s_sys"].getObject()->Draw("5");
	    vG["21000_p23s_sys"].getObject()->Draw("5");
	    vG["2000_p23s"].getObject()->Draw("PE");
	    vG["4000_p23s"].getObject()->Draw("PE");
	    vG["21000_p23s"].getObject()->Draw("PE");
		leg->Draw("same");
		leg2->Draw("same");
	
	
		c1->SaveAs(Form("%s/checkout/tscol/TrainDiffResult_DR_2000-21000_v2.pdf", workdir.Data()));
	}

}
