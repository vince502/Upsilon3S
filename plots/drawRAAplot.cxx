#include "../upsilonAna.h"
#include "../.workdir.h"

RooRealVar getDoubleRatioValue(std::pair <int, int>);
TH1D getPbPbRAA();

void drawRAAplot(){
  TCanvas* c2 = new TCanvas("c2","",700,800);

  c2->cd();
  c2->Draw();
  auto hPbPb = getPbPbRAA();
  std::cout << hPbPb.GetTitle() << std::endl;
  std::cout << hPbPb.GetBinContent(1) << std::endl;
  std::cout << hPbPb.GetBinContent(2) << std::endl;
  std::cout << hPbPb.GetBinContent(3) << std::endl;
  hPbPb.Draw("pe");
  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_test.pdf", workdir.Data() ));
  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_test.cxx", workdir.Data() ));
//  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_test_bdt0.2_1.0.cxx", workdir.Data() ));
};
RooRealVar getDoubleRatioValue(std::pair <int, int> cbpair, std::pair<double, double> ptpair = {0,30},std::string type = "CB3:CC2:GC"){
  long ts = 1623391157; //BLIND Nominal

  double ylim = 2.4;
  std::pair<double, double> bdtpair = {0.20,1.00}; //BLIND Nominal ?

  binplotter* bp ;
  bp = new binplotter(type,ts, ylim, ptpair.first, ptpair.second, cbpair.first, cbpair.second, bdtpair.first, bdtpair.second );
  bp->set_params("_CC2", 0.00);

  RooRealVar _y3 = bp->get_yield();
  RooRealVar _y3acc = upsi::getacceptance(ptpair.first, ptpair.second, (double) -1*ylim, ylim, 3.5);
  auto _y3eff_pair = bp->get_eff();
  double _y3eff = _y3eff_pair.first;
  RooRealVar y3AA, y3PP ;
  y3AA = RooRealVar("corrY3yield", "corrected 3S yield", _y3.getVal()/(_y3acc.getVal()*_y3eff));
  y3AA.setError(_y3.getError()/(_y3acc.getVal()*_y3eff ));
  TFile* file_pp = TFile::Open(Form("%s/fitresults_upsilon_fixParm1_seed2_DoubleCB_PP_DATA_pt0.0-30.0_y0.0-2.4_muPt4.0.root",hin16023.Data() ));
  TFile* file_pp_eff = TFile::Open(Form("%s/efficiency_ups3s_useDataPtWeight1_tnp_trgId0_trkId0_muId-100_staId-100.root", hin16023.Data() ));
  TFile* file_pp_acc = TFile::Open(Form("%s/acceptance_wgt_norm_3S.root", hin16023.Data() ));

  TH1D *hYpp = (TH1D*) file_pp->Get("fitResults");
  TH1D *hApp, *hEpp;
  hApp = (TH1D*) file_pp_acc->Get("hIntAccPP3S");
  hEpp = (TH1D*) file_pp_eff->Get("hcentintEffPP");

  double _Y3pp = hYpp->GetBinContent(3);
  double _Y3pp_err = hYpp->GetBinError(3);
  double _Y3pp_acc = hApp->GetBinContent(1);
  double _Y3pp_eff = hEpp->GetBinContent(1);
  y3PP = RooRealVar("corrY3yieldPP", "corrected 3S yield pp", _Y3pp/(_Y3pp_eff*_Y3pp_acc));
  y3PP.setError(_Y3pp_err/(_Y3pp_eff*_Y3pp_acc));
  Double_t cs_pp = 28*TMath::Power(10,9);
  Double_t Nmb = 11968044281.;
  auto taa =glp::Taa[{(int) (cbpair.first/2), (int) (cbpair.second/2)}];

  Double_t taa_Nmb = taa.first*Nmb/1.05;
  Double_t step_one = (cs_pp)/(taa_Nmb);
  Double_t step_two = step_one * (180./(cbpair.second - cbpair.first) );
  Double_t val_RAA = 4.*step_two*y3AA.getVal()/y3PP.getVal();

  std::cout << std::endl << std::endl << "RAAAAA : " << val_RAA << std::endl << std::endl;
  Double_t err_RAA = 4*step_two*((1/y3PP.getVal())*(y3AA.getError()- (y3AA.getVal()/y3PP.getVal())*y3PP.getError())); 

  RooRealVar val_return = RooRealVar("raa","", val_RAA);
  val_return.setError(err_RAA);

  return val_return;
};

TH1D getPbPbRAA(){
  Double_t* cbinthree = new Double_t[4]{0,20,50,90};
  Double_t* cbinthree_rev = new Double_t[4]{90,50,20,0};
  

  TH1D* h1 = new TH1D("h1" , "PbPb 2 ratio cent", 35, 0, 420);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetOptTitle(kFALSE);
  for(int idx =0; idx <3; ++idx){
    RooRealVar dr_bin = getDoubleRatioValue({cbinthree_rev[idx+1]*2,cbinthree_rev[idx]*2},{0,30}, "CB3:CC2:FF");
    double npart = glp::Npart[{cbinthree_rev[idx+1],cbinthree_rev[idx]}].first;
    h1->SetBinContent(h1->FindBin(npart), dr_bin.getVal());
    h1->SetBinError(h1->FindBin(npart), dr_bin.getError());
  }
  h1->GetYaxis()->SetRangeUser(0,1);
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kBlue);
  h1->SetLineColor(kBlue);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitle("N_{part}");
  h1->GetYaxis()->SetTitle("R_{AA}");
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->GetYaxis()->SetTitleSize(0.05);
  return *h1;
};

TH1D getPbPbRAA_pt(){
  Double_t* ptbintwo = new Double_t[3]{0,6,30};
  Double_t* ptbintwo_rev = new Double_t[3]{30,6,0};
  

  TH1D* h1 = new TH1D("h1" , "PbPb 2 ratio cent", 10, 0, 30);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetOptTitle(kFALSE);
  for(int idx =0; idx <2; ++idx){
    RooRealVar dr_bin = getDoubleRatioValue({0,180},{ptbintwo[idx],ptbintwo[idx+1]}, "CB3:CC2:GC");
    h1->SetBinContent(h1->FindBin( (ptbintwo[idx]+ptbintwo[idx+1])/2), dr_bin.getVal());
    h1->SetBinError(h1->FindBin( (ptbintwo[idx]+ptbintwo[idx+1])/2), dr_bin.getError());
  }
  h1->GetYaxis()->SetRangeUser(0,1);
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kBlue);
  h1->SetLineColor(kBlue);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitle("N_{part}");
  h1->GetYaxis()->SetTitle("R_{AA}");
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->GetYaxis()->SetTitleSize(0.05);
  return *h1;
};
