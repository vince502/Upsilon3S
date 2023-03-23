#include "../BDT/bininfo.h"

void systematic_ups_DR_v2()
{

	std::map<TString, TFile*> m_sys;
	if( (long) _TS == 10000000016 ){
		m_sys= {
	  					{"signal parameter", new TFile("./data/sigPAR_unc_DR.root", "open")},
	  					{"signal pdf", new TFile("./data/sigPDF_unc_DR.root", "open")},
	  					{"background pdf", new TFile("./data/bkgPDF_unc_DR.root", "open")},
//	  					{"acceptance dpt", new TFile("./data/ACCQuad_unc.root", "open")},
//	  					{"efficiency dpt", new TFile("./data/effDPTQuad_unc.root", "open")},
//	  					{"efficiency tnp", new TFile("./data/effTNP_unc.root", "open")},
	  					{"centrality calibration", new TFile("./data/CENT_unc_DR.root", "open")},
	  					{"BDT variation", new TFile("./data/BDT_Diff_unc_DR.root", "open")},
	  					{"Correction ratio", new TFile("./data/Correction_unc_DR.root", "open")},
		};
	}
	else{
		m_sys= {
		  					{"signal parameter", new TFile(Form("./data/sigPAR_unc_DR_%ld.root", _TS), "open")},
		  					{"signal pdf", new TFile(Form("./data/sigPDF_unc_DR_%ld.root", _TS), "open")},
		  					{"background pdf", new TFile(Form("./data/bkgPDF_unc_DR_%ld.root", _TS), "open")},
//	  					{"acceptance dpt", new TFile("./data/ACCQuad_unc_DR.root", "open")},
//	  					{"efficiency dpt", new TFile(Form("./data/effDPTQuad_unc_DR_%ld.root", _TS), "open")},
//	  					{"efficiency tnp", new TFile("./data/effTNP_unc_DR.root", "open")},
		  					{"centrality calibration", new TFile(Form("./data/CENT_unc_DR_%ld.root", _TS), "open")},
		  					{"BDT variation", new TFile(Form("./data/BDT_Diff_unc_DR_%ld.root", _TS), "open")},
	  						{"Correction ratio", new TFile(Form("./data/Correction_unc_DR_%ld.root", _TS), "open")},
		};
	}
	for(auto x : m_sys) { std::cout << x.first.Data() << ", File: " << x.second->GetName()<< std::endl;} //Check File Open
		dbg();
	gStyle->SetHistLineColor(kGray+1);
	gStyle->SetOptStat(0);
		dbg();
//	TH1D* h_rc2s = new TH1D("hsys_tot_c2S", "",ana_bm["2c"].size(), 0, ana_bm["2c"].size()-1);
	TH1D* h_rc3s = new TH1D("hsys_tot_c3S", "",ana_bm["3c"].size(), 0, ana_bm["3c"].size()-1);
//	TH1D* h_rp2s = new TH1D("hsys_tot_p2S", "",ana_bm["2p"].size(), 1, ana_bm["2p"].size());
	TH1D* h_rp3s = new TH1D("hsys_tot_p3S", "",ana_bm["3p"].size(), 1, ana_bm["3p"].size());
	std::map<std::pair<TString, TString> , TH1D*> m_hists;
		dbg();
	TFile* output = new TFile(Form("./data/total_systematics_DR_%ld.root", _TS), "recreate");
	output->cd();
	const int num_sys = m_sys.size();
	TString names[num_sys];
	int xc_n= 0;
		dbg();
	for(auto obj : m_sys){
		names[xc_n] =  obj.first;
		xc_n ++;
		if(obj.second->IsOpen()){
	//		m_hists[{obj.first, "rc2S"}] = (TH1D*) ( (TH1D*) (obj.second->Get("rc2S")))->Clone();
			m_hists[{obj.first, "rc3S"}] = (TH1D*) ( (TH1D*) (obj.second->Get("rc3S")))->Clone();
	//		m_hists[{obj.first, "rp2S"}] = (TH1D*) ( (TH1D*) (obj.second->Get("rp2S")))->Clone();
			m_hists[{obj.first, "rp3S"}] = (TH1D*) ( (TH1D*) (obj.second->Get("rp3S")))->Clone();
			
	//		m_hists[{obj.first, "rc2S"}]->SetDirectory(0);
			m_hists[{obj.first, "rc3S"}]->SetDirectory(0);
	//		m_hists[{obj.first, "rp2S"}]->SetDirectory(0);
			m_hists[{obj.first, "rp3S"}]->SetDirectory(0);
	
			std::cout <<
	//		m_hists[{obj.first, "rc2S"}]->GetNbinsX() <<
			m_hists[{obj.first, "rc3S"}]->GetNbinsX() <<
	//		m_hists[{obj.first, "rp2S"}]->GetNbinsX() <<
			m_hists[{obj.first, "rp3S"}]->GetNbinsX() <<
			std::endl;
		}

	}

	dbg();
	


//	TH1D* h_rc2s_b[num_sys];
	TH1D* h_rc3s_b[num_sys];
//	TH1D* h_rp2s_b[num_sys];
	TH1D* h_rp3s_b[num_sys];
	for(int i =0; i< num_sys; i++){
//		h_rc2s_b[i] = new TH1D(Form("h_rc2s_b%d",i),"",ana_bm["2c"].size()*num_sys, 0, ana_bm["2c"].size()-1);
		h_rc3s_b[i] = new TH1D(Form("h_rc3s_b%d",i),"",ana_bm["3c"].size()*num_sys, 0, ana_bm["3c"].size()-1);
//        h_rp2s_b[i] = new TH1D(Form("h_rp2s_b%d",i),"",ana_bm["2p"].size()*num_sys, 1, ana_bm["2p"].size());
        h_rp3s_b[i] = new TH1D(Form("h_rp3s_b%d",i),"",ana_bm["3p"].size()*num_sys, 1, ana_bm["3p"].size());
	}
						
	std::vector<ana_bins> vc2, vc3, vp2, vp3;
	vc2 = ana_bm["2c"];
	vc3 = ana_bm["3c"];
	vp2 = ana_bm["2p"];
	vp3 = ana_bm["3p"];

	int counter =1;
	int smallcounter = 1;
//	for( auto item : vc2){
//		double total_unc = 0 ;
//		for( auto obj : m_sys){
//			std::cout << Form("[INFO] Object \"%s\" on bin \'%s\', pt [%d, %d] cbin [%d, %d]'", obj.first.Data(), "rc2S", item.pl, item.ph, item.cl, item.ch)<< std::endl;
//			double unc = m_hists[{obj.first, "rc2S"}]->GetBinContent(counter);
//			std::cout << unc << std::endl;
//			h_rc2s_b[smallcounter-1]->SetBinContent(num_sys*(counter-1)+smallcounter, fabs(unc));
//			if(strcmp(h_rc2s_b[smallcounter-1]->GetTitle(),"")==0) h_rc2s_b[smallcounter-1]->SetTitle(Form("%s", obj.first.Data() ));;
//			total_unc = TMath::Sqrt( TMath::Power(total_unc, 2) + unc * unc);
//			smallcounter ++;	
//		}
//		smallcounter =1;
//		h_rc2s->SetBinContent(counter, total_unc);
//		counter++;
//	}
	std::cout << "---------- [Next Plot] ---------" << std::endl;
	counter =1;

	for( auto item : vc3){
		double total_unc = 0 ;
		for( auto obj : m_sys){
			std::cout << Form("[INFO] Object \"%s\" on bin \'%s\', pt [%d, %d] cbin [%d, %d]'", obj.first.Data(), "rc3S", item.pl, item.ph, item.cl, item.ch)<< std::endl;
			double unc = 0;
			if(m_hists[{obj.first, "rc3S"}]) unc = m_hists[{obj.first, "rc3S"}]->GetBinContent(counter);
//			double unc = m_hists[{obj.first, "rc3S"}]->GetBinContent(counter);
			std::cout << unc << std::endl;
			h_rc3s_b[smallcounter-1]->SetBinContent(num_sys*(counter-1)+smallcounter, fabs(unc));
			if(strcmp(h_rc3s_b[smallcounter-1]->GetTitle(),"")==0) h_rc3s_b[smallcounter-1]->SetTitle(Form("%s", obj.first.Data() ));;
			total_unc = TMath::Sqrt( TMath::Power(total_unc, 2) + unc * unc);
			smallcounter ++;	
		}
		smallcounter =1;
		h_rc3s->SetBinContent(counter, total_unc);
		counter++;
	}
	std::cout << "---------- [Next Plot] ---------" << std::endl;
	counter =1;

//	for( auto item : vp2){
//		double total_unc = 0 ;
//		for( auto obj : m_sys){
//			std::cout << Form("[INFO] Object \"%s\" on bin \'%s\', pt [%d, %d] cbin [%d, %d]'", obj.first.Data(), "rp2S", item.pl, item.ph, item.cl, item.ch)<< std::endl;
//			std::cout << m_hists[{obj.first, "rp2S"}]->GetName() << std::endl;
//			double unc = m_hists[{obj.first, "rp2S"}]->GetBinContent(counter);
//			std::cout << unc << std::endl;
//			h_rp2s_b[smallcounter-1]->SetBinContent(num_sys*(counter-1)+smallcounter, fabs(unc));
//			if(strcmp(h_rp2s_b[smallcounter-1]->GetTitle(),"") ==0) h_rp2s_b[smallcounter-1]->SetTitle(Form("%s", obj.first.Data() ));;
//			total_unc = TMath::Sqrt( TMath::Power(total_unc, 2) + unc * unc);
//			smallcounter ++;	
//		}
//		smallcounter =1;
//		h_rp2s->SetBinContent(counter, total_unc);
//		counter++;
//	}
	std::cout << "---------- [Next Plot] ---------" << std::endl;
	counter =1;
	
	for( auto item : vp3){
		double total_unc = 0 ;
		for( auto obj : m_sys){
			std::cout << Form("[INFO] Object \"%s\" on bin \'%s\', pt [%d, %d] cbin [%d, %d]'", obj.first.Data(), "rp3S", item.pl, item.ph, item.cl, item.ch)<< std::endl;
			double unc = 0;
			if(m_hists[{obj.first, "rp3S"}]) unc = m_hists[{obj.first, "rp3S"}]->GetBinContent(counter);
			//double unc = m_hists[{obj.first, "rp3S"}]->GetBinContent(counter);
			std::cout << unc << std::endl;
			h_rp3s_b[smallcounter-1]->SetBinContent(num_sys*(counter-1)+smallcounter, fabs(unc));
			if(strcmp(h_rp3s_b[smallcounter-1]->GetTitle(),"") ==0) h_rp3s_b[smallcounter-1]->SetTitle(Form("%s", obj.first.Data() ));;
			total_unc = TMath::Sqrt( TMath::Power(total_unc, 2) + unc * unc);
			smallcounter ++;	
		}
		smallcounter =1;
		h_rp3s->SetBinContent(counter, total_unc);
		counter++;
	}
	std::cout << "[DONE]" << std::endl;

	TCanvas *c1, *c2, *c3, *c4;
//	c1= new TCanvas("c_rc2s", "", 1000,800);
	c2= new TCanvas("c_rc3s", "", 1000,800);
//	c3= new TCanvas("c_rp2s", "", 1000,800);
	c4= new TCanvas("c_rp3s", "", 1000,800);


	int colors[8] = {kRed, kOrange+8, kYellow-7, kGreen+1, kCyan-4, kAzure-3, kViolet-6, kMagenta-4};
	int up = 1;
	double down = 1e-5;

//	c1->cd();
	TLine *l_bin = new TLine();
	l_bin->SetLineStyle(kDashed);
	l_bin->SetLineColor(kBlack);
	l_bin->SetLineWidth(1);
	double l_x;

//	c1->SetLogy();
//	h_rc2s->GetYaxis()->SetRangeUser(down,up);
//	h_rc2s->SetFillColor(kGray);
//	h_rc2s->SetLineColor(kBlack);
//	h_rc2s->GetXaxis()->SetLabelSize(0);
//	h_rc2s->GetXaxis()->SetBinLabel(1, "int.");
//	h_rc2s->GetXaxis()->SetBinLabel(2 , "0-5 %");
//	h_rc2s->GetXaxis()->SetBinLabel(3 , "5-10 %");
//	h_rc2s->GetXaxis()->SetBinLabel(4 , "10-20 %");
//	h_rc2s->GetXaxis()->SetBinLabel(5 , "20-30 %");
//	h_rc2s->GetXaxis()->SetBinLabel(6 , "30-40 %");
//	h_rc2s->GetXaxis()->SetBinLabel(7 , "40-50 %");
//	h_rc2s->GetXaxis()->SetBinLabel(8 , "50-60 %");
//	h_rc2s->GetXaxis()->SetBinLabel(9 , "60-70 %");
//	h_rc2s->GetXaxis()->SetBinLabel(10 , "70-90 %");
//
//	h_rc2s->GetXaxis()->SetTickSize(0);
//	h_rc2s->SetLineWidth(2);
//	h_rc2s->Draw();

//	for(int i=0; i<8; i++){
//		h_rc2s_b[i]->SetFillColor(colors[i]);
//		h_rc2s_b[i]->GetXaxis()->SetLabelSize(0);
//		h_rc2s_b[i]->Draw("same");
//		l_x = h_rc2s->GetBinCenter(i+1) + h_rc2s->GetBinWidth(i+1)/2;
//		l_bin->DrawLine(l_x,0, l_x, h_rc2s->GetBinContent(i+1)) ;
//	}
//		l_x = h_rc2s->GetBinCenter(9) + h_rc2s->GetBinWidth(9)/2;
//		l_bin->DrawLine(l_x,0, l_x, h_rc2s->GetBinContent(9)) ;

//	TLegend* leg = new TLegend(0.7, 0.7,0.89, 0.89);
//	for(int i =0; i< num_sys; i++){
//		leg->AddEntry(h_rc2s_b[i]->GetName(),names[i], "f");
//	}
//	leg->SetBorderSize(0);
//	leg->Draw("same");
	
	c2->cd();
//	c2->SetLogy();
	h_rc3s->GetYaxis()->SetRangeUser(down, up);
	h_rc3s->GetYaxis()->CenterTitle();
	h_rc3s->GetYaxis()->SetTitle("Relative uncertainty");
	h_rc3s->SetFillColor(kGray);
	h_rc3s->SetLineColor(kBlack);
	h_rc3s->SetLineWidth(2);
	h_rc3s->GetXaxis()->SetBinLabel(1 , "int.");
	h_rc3s->GetXaxis()->SetBinLabel(2 , "0-30 %");
	h_rc3s->GetXaxis()->SetBinLabel(3 , "30-50 %");
	h_rc3s->GetXaxis()->SetBinLabel(4 , "50-70 %");
	h_rc3s->GetXaxis()->SetBinLabel(5 , "70-90 %");
//	h_rc3s->GetXaxis()->SetLabelSize(0);
	h_rc3s->GetXaxis()->SetTickSize(0);
	h_rc3s->Draw();

	for(int i=0; i<num_sys; i++){
		h_rc3s_b[i]->SetFillColor(colors[i]);
		h_rc3s_b[i]->GetXaxis()->SetLabelSize(0);
		h_rc3s_b[i]->Draw("same");
		l_x = h_rc3s->GetBinCenter(i+1) + h_rc3s->GetBinWidth(i+1)/2;
		l_bin->DrawLine(l_x,0, l_x, h_rc3s->GetBinContent(i+1)) ;
	}
	TLegend* leg = new TLegend(0.7, 0.7,0.89, 0.89);
	for(int i =0; i< num_sys; i++){
		leg->AddEntry(h_rc3s_b[i]->GetName(),names[i], "f");
	}
	leg->SetBorderSize(0);
	leg->Draw("same");
	
//	c3->cd();
//	c3->SetLogy();
//	h_rp2s->GetYaxis()->SetRangeUser(down, up);
//	h_rp2s->SetFillColor(kGray);
//	h_rp2s->SetLineColor(kGray+2);
//	h_rp2s->SetLineColor(kBlack);
//	h_rp2s->SetLineWidth(2);
//	h_rp2s->GetXaxis()->SetBinLabel(1 , "0-3 GeV/c");
//	h_rp2s->GetXaxis()->SetBinLabel(2 , "3-6 GeV/c");
//	h_rp2s->GetXaxis()->SetBinLabel(3 , "6-9 GeV/c");
//	h_rp2s->GetXaxis()->SetBinLabel(4 , "9-15 GeV/c");
//	h_rp2s->GetXaxis()->SetBinLabel(5 , "15-30 GeV/c");
//	h_rp2s->GetXaxis()->SetLabelSize(0);
//	h_rp2s->Draw();
//	for(int i=0; i<8; i++){
//		h_rp2s_b[i]->SetFillColor(colors[i]);
//		h_rp2s_b[i]->GetXaxis()->SetLabelSize(0);
//		h_rp2s_b[i]->Draw("same");
//		l_x = h_rp2s->GetBinCenter(i+1) + h_rp2s->GetBinWidth(i+1)/2;
//		l_bin->DrawLine(l_x,0, l_x, h_rp2s->GetBinContent(i+1)) ;
//	}
//	leg->Draw("same");
	
	c4->cd();
//	c4->SetLogy();
	h_rp3s->GetYaxis()->SetRangeUser(down, up);
	h_rp3s->GetYaxis()->CenterTitle();
	h_rp3s->GetYaxis()->SetTitle("Relative uncertainty");
	h_rp3s->SetFillColor(kGray);
	h_rp3s->SetLineColor(kBlack);
	h_rp3s->SetLineWidth(2);
//	h_rp3s->GetXaxis()->SetLabelSize(0);
	h_rp3s->GetXaxis()->SetBinLabel(1 , "0-4 GeV/c");
	h_rp3s->GetXaxis()->SetBinLabel(2 , "4-9 GeV/c");
	h_rp3s->GetXaxis()->SetBinLabel(3 , "9-15 GeV/c");
	h_rp3s->GetXaxis()->SetBinLabel(4 , "15-30 GeV/c");
	h_rp3s->Draw();
	for(int i=0; i<num_sys; i++){
		h_rp3s_b[i]->SetFillColor(colors[i]);
		h_rp3s_b[i]->GetXaxis()->SetLabelSize(0);
		h_rp3s_b[i]->Draw("same");
		l_x = h_rp3s->GetBinCenter(i+1) + h_rp3s->GetBinWidth(i+1)/2;
		l_bin->DrawLine(l_x,0, l_x, h_rp3s->GetBinContent(i+1)) ;
	}
	leg->Draw("same");

	CMS_lumi_square(c2, 2, 11);
	CMS_lumi_square(c4, 2, 11);
	
	output->cd();
//	c1->SaveAs(Form("../checkout/tscol/total_uncDR_2Scent_%ld_v2.pdf", _TS));
	c2->SaveAs(Form("../checkout/tscol/total_uncDR_3Scent_%ld_v2.pdf", _TS));
//	c3->SaveAs(Form("../checkout/tscol/total_uncDR_2Spt_%ld_v2.pdf", _TS));
	c4->SaveAs(Form("../checkout/tscol/total_uncDR_3Spt_%ld_v2.pdf", _TS));
//	c1->Write();
	c2->Write();
//	c3->Write();
	c4->Write();
	TDirectoryFile* hd = new TDirectoryFile("syst_comp","");
	hd->cd();
//	for(TH1D* hist : h_rc2s_b){
//		hist->Write();
//	}
	for(TH1D* hist : h_rc3s_b){
		hist->Write();
	}
//	for(TH1D* hist : h_rp2s_b){
//		hist->Write();
//	}
	for(TH1D* hist : h_rp3s_b){
		hist->Write();
	}

//	h_rc2s->Write();
	h_rc3s->Write();
//	h_rp2s->Write();
	h_rp3s->Write();
	output->Close();
}
