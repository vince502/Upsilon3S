#include "../bininfo.h"

TString BDTDistribution_int_onebin(int _state, int _pl, int _ph, int mode, long ts = 9999999999)
{
	TFile* f_res = TFile::Open(Form("%s/BDT/BDTResult/BDTresultY3S_%ld_BLIND.root", workdir.Data(), ts ));
	TFile* f_data = TFile::Open(Form("%s/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT.root", workdir.Data(), ts ));
	auto bdtdir = [&](int state, int pl, int ph)
	{
		string s_dir = Form("data/Y%dSpt%dto%d",state,pl,ph);
		return s_dir;
	};
	TTree *t_train, *t_test, *t_data;
	int dataset_index1 =0 ;
	int dataset_index2 =0 ;
	if(mode ==1 ) {dataset_index1 =1; dataset_index2 = 1;}
	if(mode ==2 ) {dataset_index1 =1; dataset_index2 = 2;}
	if(mode ==3 ) {dataset_index1 =2; dataset_index2 = 1;}
	if(mode ==4 ) {dataset_index1 =2; dataset_index2 = 2;}
	t_train = (TTree*) f_res->Get(Form("%s/dataset%d/TrainTree",bdtdir(_state, _pl, _ph).c_str(), dataset_index1));
	t_test  = (TTree*) f_res->Get(Form("%s/dataset%d/TestTree" ,bdtdir(_state, _pl, _ph).c_str(), dataset_index2));
	t_data = (TTree*) ( (RooDataSet*)f_data->Get(Form("dataset_Y%dSpt%dto%d", _state, _pl, _ph)))->GetClonedTree();
	int nBins = 40;
	TH1D* hist_s_tr_pre = new TH1D("h_s_tr_pre", "", nBins, -0.6, 0.6);
	TH1D* hist_b_tr_pre = new TH1D("h_b_tr_pre", "", nBins, -0.6, 0.6);
	TH1D* hist_s_te_pre = new TH1D("h_s_te_pre", "", nBins, -0.6, 0.6);
	TH1D* hist_b_te_pre = new TH1D("h_b_te_pre", "", nBins, -0.6, 0.6);
	TH1D* hist_dat_pre = new TH1D("h_dat_pre", "", nBins, -0.6, 0.6);
	TH1D* hist_s_tr = new TH1D("h_s_tr", "", nBins, -0.6, 0.6);
	TH1D* hist_b_tr = new TH1D("h_b_tr", "", nBins, -0.6, 0.6);
	TH1D* hist_s_te = new TH1D("h_s_te", "", nBins, -0.6, 0.6);
	TH1D* hist_b_te = new TH1D("h_b_te", "", nBins, -0.6, 0.6);
	TH1D* hist_dat = new TH1D("h_dat", "", nBins, -0.6, 0.6);
	float bdt_tr, bdt_te;
	double bdt_data;
	t_train->SetBranchAddress("BDT", &bdt_tr);
	t_test->SetBranchAddress("BDT", &bdt_te);
	t_data->SetBranchAddress(Form("BDT"), &bdt_data );
	int nEtr, nEte, id_tr, id_te;
	int nData;
	t_train->SetBranchAddress("classID", &id_tr);
	t_test->SetBranchAddress("classID", &id_te);

	nEtr = t_train->GetEntries();
	nEte = t_test->GetEntries();
	nData = t_data->GetEntries();
	int nbkg = t_train->GetEntries("classID==1");
	int nsig = t_train->GetEntries("classID==0");

	std::cout <<"Start running loop"<< std::endl;
	for(int idx=0; idx < nEtr; idx++)
	{
		t_train->GetEntry(idx);
		if(id_tr == 0)
		{
			hist_s_tr_pre->Fill(bdt_tr);
		}
		if(id_tr == 1)
		{
			hist_b_tr_pre->Fill(bdt_tr);
		}
	}
	std::cout <<"Start running second loop"<< std::endl;
	
	for(int idx=0; idx < nEte; idx++)
	{
		t_test->GetEntry(idx);
		if(id_te == 0)
		{
			hist_s_te_pre->Fill(bdt_te);
		}
		if(id_te == 1)
		{
			hist_b_te_pre->Fill(bdt_te);
		}
	}
	for(int idx=0; idx < nData; idx++)
	{
		t_data->GetEntry(idx);
		hist_dat_pre->Fill(bdt_data);
	}
	std::cout <<"End running loops"<< std::endl;
	for(int xbin=0; xbin<40; xbin++){
		double kbin = -0.6 + ( (double) xbin/40);
		double valint;
		valint = hist_s_tr_pre->Integral(xbin, 40);
		hist_s_tr->SetBinContent(xbin,valint);
		std::cout << xbin << ", "<<  valint << std::endl;
		valint = hist_b_tr_pre->Integral(xbin, 40);
		hist_b_tr->SetBinContent(xbin,valint);
		valint = hist_s_te_pre->Integral(xbin, 40);
		hist_s_te->SetBinContent(xbin,valint);
		valint = hist_b_te_pre->Integral(xbin, 40);
		hist_b_te->SetBinContent(xbin,valint);
		valint = hist_dat_pre->Integral(xbin, 40);
		hist_dat->SetBinContent(xbin,valint);
	}

	hist_s_tr->Scale(nBins/hist_s_tr->GetBinContent(1));
	hist_b_tr->Scale(nBins/hist_b_tr->GetBinContent(1));
	hist_s_te->Scale(nBins/hist_s_te->GetBinContent(1));
	hist_b_te->Scale(nBins/hist_b_te->GetBinContent(1));
	hist_dat->Scale(nBins/hist_dat->GetBinContent(1));
	TH1D* hist_dif = (TH1D*) hist_dat->Clone();
	double bkg_frac= 1- (double) (7372+621+375)/151679;
	hist_dif->Add(hist_b_te, -bkg_frac);
	hist_dif->Scale(nBins/hist_dif->GetBinContent(1));
	TCanvas* c1 = new TCanvas("c1","", 800, 700);
	hist_s_tr->SetMarkerColor(kBlue);
	hist_s_te->SetMarkerColor(kBlue);
	hist_b_tr->SetMarkerColor(kRed);
	hist_b_te->SetMarkerColor(kRed);
	hist_dat->SetMarkerColor(kTeal);
	hist_dif->SetMarkerColor(kMagenta);

	hist_s_tr->SetMarkerStyle(kFullCircle);
	hist_b_tr->SetMarkerStyle(kFullCircle);
	hist_s_te->SetMarkerStyle(kStar);
	hist_b_te->SetMarkerStyle(kStar);
	hist_dat->SetMarkerStyle(kFullSquare);
	hist_dat->SetMarkerStyle(kFullSquare);

	hist_s_tr->SetLineColor(kBlue);
	hist_s_te->SetLineColor(kBlue);
	hist_b_tr->SetLineColor(kRed);
	hist_b_te->SetLineColor(kRed);
	hist_dat->SetLineColor(kTeal);
	hist_dif->SetLineColor(kMagenta);
	Double_t signal_KS_res, bkg_KS_res;
	Double_t signal_Chi2_res, bkg_Chi2_res;
	signal_KS_res = hist_s_tr->KolmogorovTest(hist_s_te);
	bkg_KS_res = hist_b_tr->KolmogorovTest(hist_b_te);
	signal_Chi2_res = 	hist_s_tr->Chi2Test(hist_s_te, "WW");
	bkg_Chi2_res = 		hist_b_tr->Chi2Test(hist_b_te, "WW");

	TString return_var = Form("Y(%dS) pT [%d, %d] mode %d : Chi2 test : signal (background) = %.4f (%.4f)\n                            Kolmogorov-Smirnov test : signal (background) probability = %.4f (%.4f), #Bkg = %d, $Sig = %d\n",_state, _pl, _ph, mode, signal_Chi2_res, bkg_Chi2_res, signal_KS_res, bkg_KS_res, nbkg, nsig);
	std::cout << return_var.Data();
	if(signal_KS_res >0.5 && bkg_KS_res > 0.5) 
	{
		return_var += "Good training \n";
	}
	
	hist_dif->Draw("pe");
	hist_s_tr->Draw("same,pe");
	hist_b_tr->Draw("same,pe");

	hist_s_te->Draw("same,l");
	hist_b_te->Draw("same,l");
	hist_dat->Draw("same,pe");

	gSystem->mkdir(Form("%s/BDT/Validation/Plots/%ld", workdir.Data(), ts));
	c1->SaveAs(Form("%s/BDT/Validation/Plots/%ld/Int_Y%dS_pt_%d_%d_BDTDistplot_m%d.C", workdir.Data(),ts, _state, _pl, _ph, mode));
	f_res->Close();
	return return_var; 

};

void BDTDistribution_integral(long ts)
{
	ofstream x(Form("bdt_intdist%ld.log",ts), ios::out);
	for(int i =1; i<5; i++){
		for( auto ptpair : bin1spt){x << BDTDistribution_int_onebin(1,ptpair.first,ptpair.second, i, ts).Data(); }
		for( auto ptpair : bin2spt){x << BDTDistribution_int_onebin(2,ptpair.first,ptpair.second, i, ts).Data(); }
		for( auto ptpair : bin3spt){x << BDTDistribution_int_onebin(3,ptpair.first,ptpair.second, i, ts).Data(); }
	}
	x.close();
}
