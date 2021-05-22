#include "../upsilonAna.h"
#include "../.workdir.h"

RooRealVar getDoubleRatioValue(std::pair <int, int>);
TH1D getPbPbDoubleRatio();

void drawDoubleRatioplot(){
  TCanvas* c1 = new TCanvas();
  c1->cd();
  TH1D hPbPb = getPbPbDoubleRatio();
  hPbPb.Draw();
  c1->SaveAs(Form("%s/plots/DoubleRatio/plot_test_bdt0.2_1.0.pdf", workdir.Data() ));
  c1->SaveAs(Form("%s/plots/DoubleRatio/plot_test_bdt0.2_1.0.cxx", workdir.Data() ));
  c1->Close();
};
RooRealVar getDoubleRatioValue(std::pair <int, int> cbpair){
  long ts = 1621568219;// 1619021800; //BLIND Nominal
  std::pair<double, double> ptpair = {0,30};
  std::pair<double, double> bdtpair = {0.20,1.00}; //BLIND Nominal ?
  double ylim = 2.4;

  binplotter* bp ;
  bp = new binplotter(ts, ylim, ptpair.first, ptpair.second, cbpair.first, cbpair.second, bdtpair.first, bdtpair.second );
  bp->set_params("_CC3", 0.00);

  bp->get_yield();
  RooRealVar y1, y2, r12;
  y1 = bp->yield1S;
  y2 = bp->yield2S;
  r12 = RooRealVar("r12", "y1/y2 ratio", y2.getVal()/y1.getVal());
  r12.setError(TMath::Sqrt(TMath::Power( y2.getError()*(1/y1.getVal()) ,2) + TMath::Power(y1.getError()*(y2.getVal()/TMath::Power(y1.getVal(),2)),2)));

  return r12;
};

TH1D getPbPbDoubleRatio(){
  Double_t* cbinthree = new Double_t[4]{0,20,50,90};

  TH1D* h1 = new TH1D("h1" , "PbPb 2 ratio cent", 3, cbinthree);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetOptTitle(kFALSE);
  for(int idx =0; idx <3; ++idx){
    RooRealVar dr_bin = getDoubleRatioValue({cbinthree[idx]*2,cbinthree[idx+1]*2});
    h1->SetBinContent(idx+1, dr_bin.getVal());
    h1->SetBinError(idx+1, dr_bin.getError());
  }
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kBlue);
  h1->SetLineColor(kBlue);
  return *h1;
};
