#include "../upsilonAna.cxx"
#include "../.workdir.h"

std::pair<RooRealVar, RooRealVar> getDoubleRatioValue(std::pair <int, int> cbpair, std::pair<double, double> ptpair = {0,30},std::string type = "CB3:CC2:GC", std::pair<double, double> bdtpair = {-0.1,1.00});
std::pair<TH1D*, TH1D*> getPbPbDR(int shift1=0, int shift2=0);

void drawDoubleRatioplot(){
  TCanvas* c2 = new TCanvas("c2","",900,700);
  TCanvas* c3 = new TCanvas("c3","",900,700);
  TPad *p2_1, *p2_2, *p3_1, *p3_2;
  p2_1 = new TPad("p21", "", 0.05, 0,0.83,1);
  p2_1->SetRightMargin(0);
  p2_2 = new TPad("p22", "", 0.83, 0,1,1);
  p2_2->SetLeftMargin(0);
  p3_1 = new TPad("p31", "", 0.05, 0,0.83,1);
  p3_1->SetRightMargin(0);
  p3_2 = new TPad("p32", "", 0.83, 0,1,1);
  p3_2->SetLeftMargin(0);

  TH1D* y2_int = new TH1D("y2int", "", 1,0,1);
  TH1D* y3_int = new TH1D("y3int", "", 1,0,1);
  y2_int->GetXaxis()->SetBinLabel(1, "Integrated");// Form("%.0f",glp::Npart[{0,90}].first) );
  y3_int->GetXaxis()->SetBinLabel(1, "Integrated"); //Form("%.0f",glp::Npart[{0,90}].first) );
  y2_int->GetYaxis()->SetTickSize(0);
  y2_int->GetYaxis()->SetLabelSize(0);
  y2_int->GetXaxis()->SetLabelSize(0.17);
  y2_int->GetYaxis()->SetLabelOffset(0);
  y2_int->GetYaxis()->SetRangeUser(0,1.6);
  y3_int->GetYaxis()->SetTickSize(0);
  y3_int->GetYaxis()->SetLabelSize(0);
  y3_int->GetXaxis()->SetLabelSize(0.17);
  y3_int->GetYaxis()->SetLabelOffset(0);
  y3_int->GetYaxis()->SetRangeUser(0,1.6);

  auto hPbPb = getPbPbDR();
  auto dr_int = getDoubleRatioValue({0,181}, {0,30}, "CB3:CC3:DRFF", {-0.1, 1});
  TLatex* tl = new TLatex();
  tl->SetTextSize(0.04);
  tl->SetTextFont(42);
  tl->SetNDC();
  c2->cd();
  p2_1->Draw();
  p2_2->Draw();
  auto hPbPb2S = hPbPb.first;
  auto dr2S_int = dr_int.first;

  p2_1->cd();
  TLine* lineone = new TLine();
  lineone->SetLineStyle(kDashed);
  lineone->DrawLineNDC(0,0.5,1,0.5);
  hPbPb2S->Draw();
  tl->DrawLatex( 0.2, 0.8,"p_{T} < 30 GeV/c");
  tl->DrawLatex( 0.2, 0.75, "|y| < 2.4");
  tl->DrawLatex( 0.2, 0.7, "p^{#mu}_{T} < 4 GeV/c");

  p2_2->cd();
  y2_int->SetBinContent(1, dr2S_int.getVal() );
  y2_int->SetBinError(1, dr2S_int.getError() );
  y2_int->SetMarkerStyle(kCircle);
  y2_int->SetMarkerColor(kBlue+2);
  y2_int->SetLineColor(kBlue+2);
  y2_int->Draw("");


  c2->Modified();

  c3->cd();
  p3_1->Draw();
  p3_2->Draw();
  auto hPbPb3S = hPbPb.second;
  auto dr3S_int = dr_int.second;

  p3_1->cd();
  hPbPb3S->Draw("");
  tl->DrawLatex( 0.2, 0.8,"p_{T} < 30 GeV/c");
  tl->DrawLatex( 0.2, 0.75, "|y| < 2.4");
  tl->DrawLatex( 0.2, 0.7, "p^{#mu}_{T} < 4 GeV/c");

  p3_2->cd();
  y3_int->SetBinContent(1, dr3S_int.getVal() );
  y3_int->SetBinError(1, dr3S_int.getError() );
  y3_int->SetMarkerStyle(kCircle);
  y3_int->SetMarkerColor(kGreen+2);
  y3_int->SetLineColor(kGreen+2);
  y3_int->Draw();

  c3->Modified();

  CMS_lumi_square(p2_1, 2, 33);
  CMS_lumi_square(p3_1, 2, 33);

  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_DoubleRatio_2S.pdf", workdir.Data() ));
  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_DoubleRatio_2S.C", workdir.Data() ));
  c3->SaveAs(Form("%s/plots/DoubleRatio/plot_DoubleRatio_3S.pdf", workdir.Data() ));
  c3->SaveAs(Form("%s/plots/DoubleRatio/plot_DoubleRatio_3S.C", workdir.Data() ));
};



std::pair<RooRealVar, RooRealVar> getDoubleRatioValue(std::pair <int, int> cbpair, std::pair<double, double> ptpair = {0,30},std::string type = "CB3:CC2:GC", std::pair<double, double> bdtpair = {-0.1,1.00}){
  long ts = 1625139244; //BLIND Nominal

  double ylim = 2.4;

  binplotter* bp ;
  bp = new binplotter(type,ts, ylim, ptpair.first, ptpair.second, cbpair.first, cbpair.second, bdtpair.first, bdtpair.second, false);

  //RooRealVar _y3 = bp->get_yield();
  const auto frac_pair = bp->get_frac();
  RooRealVar fracY2PbPb = frac_pair.first;
  RooRealVar fracY3PbPb = frac_pair.second;
  std::cout << "fracY3PbPb Val, Error: " << fracY3PbPb.getVal() <<", " << fracY3PbPb.getError() << std::endl;
  //RooRealVar _y3acc = upsi::getacceptance(ptpair.first, ptpair.second, (double) -1*ylim, ylim, 3.5);
  //auto _y3eff_pair = bp->get_eff();
  //double _y3eff = _y3eff_pair.first;
  RooRealVar y3AA, y3PP, y1PP, y2PP, fracY2PP, fracY3PP;
  //y3AA = RooRealVar("corrY3yield", "corrected 3S yield", _y3.getVal()/(_y3acc.getVal()*_y3eff));
  //y3AA.setError(_y3.getError()/(_y3acc.getVal()*_y3eff ));
  TFile* file_pp = TFile::Open(Form("%s/fitresults_upsilon_fixParm1_seed2_DoubleCB_PP_DATA_pt0.0-30.0_y0.0-2.4_muPt4.0.root",hin16023.Data() ));
  TFile* file_pp_eff = TFile::Open(Form("%s/efficiency_ups3s_useDataPtWeight1_tnp_trgId0_trkId0_muId-100_staId-100.root", hin16023.Data() ));
  TFile* file_pp_acc = TFile::Open(Form("%s/acceptance_wgt_norm_3S.root", hin16023.Data() ));

  TH1D *hYpp = (TH1D*) file_pp->Get("fitResults");
  //TH1D *hApp, *hEpp;
  //hApp = (TH1D*) file_pp_acc->Get("hIntAccPP3S");
  //hEpp = (TH1D*) file_pp_eff->Get("hcentintEffPP");

  double _Y1pp = hYpp->GetBinContent(1);
  double _Y1pp_err = hYpp->GetBinError(1);
  double _Y2pp = hYpp->GetBinContent(2);
  double _Y2pp_err = hYpp->GetBinError(2);
  double _Y3pp = hYpp->GetBinContent(3);
  double _Y3pp_err = hYpp->GetBinError(3);
  //double _Y3pp_acc = hApp->GetBinContent(1);
  //double _Y3pp_eff = hEpp->GetBinContent(1);
  y1PP = RooRealVar("Y1yieldPP", "1S yield pp", _Y1pp);
  y2PP = RooRealVar("Y2yieldPP", "2S yield pp", _Y2pp);
  y3PP = RooRealVar("Y3yieldPP", "3S yield pp", _Y3pp);
  y1PP.setError(_Y1pp_err);
  y2PP.setError(_Y2pp_err);
  y3PP.setError(_Y3pp_err);
  fracY2PP = RooRealVar("fracY2over1SPP", "2S fraction", _Y2pp/_Y1pp);
  fracY3PP = RooRealVar("fracY3over1SPP", "3S fraction", _Y3pp/_Y1pp);
  fracY2PP.setError((1/_Y1pp)*TMath::Sqrt(TMath::Power( _Y1pp_err,2) + TMath::Power((_Y2pp/_Y1pp)*_Y2pp_err,2) ));
  fracY3PP.setError((1/_Y1pp)*TMath::Sqrt(TMath::Power( _Y1pp_err,2) + TMath::Power((_Y3pp/_Y1pp)*_Y3pp_err,2) ));
  std::cout << "fracY3PP Val, Err: " << fracY3PP.getVal() <<", " << fracY3PP.getError() << std::endl;
  RooRealVar DRY2 = RooRealVar("2SDoubleRatio", "2S Double Ratio PbPb/pp" , fracY2PbPb.getVal()/fracY2PP.getVal());
  RooRealVar DRY3 = RooRealVar("3SDoubleRatio", "3S Double Ratio PbPb/pp" , fracY3PbPb.getVal()/fracY3PP.getVal());
  DRY2.setError((1/fracY2PP.getVal())*TMath::Sqrt(TMath::Power( fracY2PbPb.getError(),2) + TMath::Power((fracY2PbPb.getVal()/fracY2PP.getVal())*fracY2PP.getError(),2) ));
  DRY3.setError((1/fracY3PP.getVal())*TMath::Sqrt(TMath::Power( fracY3PbPb.getError(),2) + TMath::Power((fracY3PbPb.getVal()/fracY3PP.getVal())*fracY3PP.getError(),2) ));
  std::cout << "DRY3 Val, Error: " << DRY3.getVal() << ", " <<  DRY3.getError() << std::endl;
//  Double_t cs_pp = 28*TMath::Power(10,9);
//  Double_t Nmb = 11968044281.;
//  auto taa =glp::Taa[{(int) (cbpair.first/2), (int) (cbpair.second/2)}];

//  Double_t taa_Nmb = taa.first*Nmb/1.05;
//  Double_t step_one = (cs_pp)/(taa_Nmb);
//  Double_t step_two = step_one * (180./(cbpair.second - cbpair.first) );
//  Double_t val_RAA = 4.*step_two*y3AA.getVal()/y3PP.getVal();

//  Double_t err_RAA = 4*step_two*((1/y3PP.getVal())*(y3AA.getError()- (y3AA.getVal()/y3PP.getVal())*y3PP.getError())); 

//  RooRealVar val_return = RooRealVar("raa","", val_RAA);
//  val_return.setError(err_RAA);

  return std::make_pair(DRY2, DRY3);
};

std::pair<TH1D*, TH1D*> getPbPbDR(int shift1 = 0, int shift2 = 1){
  Double_t* cbinnine = new Double_t[10]{0,5,10,20,30,40,50,60,70,90};
  Double_t* cbinnine_rev = new Double_t[10]{90,70,60,50,40,30,20,10,5,0};
  Double_t* centnine = new Double_t[10]{0,10,20,40,60,80,100,120,140,181};
  Double_t* centnine_rev = new Double_t[10]{181,140,120,100,80,60,40,20,10,0};
  Double_t* cbinthree = new Double_t[4]{0,20,50,90};
  Double_t* cbinthree_rev = new Double_t[4]{90,50,20,0};
  Double_t* centthree = new Double_t[4]{0,40,100,181};
  Double_t* centthree_rev = new Double_t[4]{181,100,40,0};

  TH1D* h1 = new TH1D("h1" , "PbPb 2S double ratio cent", 70, 0, 420);
  TH1D* h2 = new TH1D("h2" , "PbPb 3S double ratio cent", 70, 0, 420);
  setTDRStyle();
  for(int idx =0; idx <9; ++idx){
    std::cout << cbinnine_rev[idx+1]*2 << " , " << cbinnine_rev[idx]*2 << std::endl;
    std::pair<RooRealVar, RooRealVar> dr_bin = getDoubleRatioValue({centnine_rev[idx+1],centnine_rev[idx]},{0,30}, "CB3:CC3:DRFF" );
    double npart = glp::Npart[{cbinnine_rev[idx+1],cbinnine_rev[idx]}].first;
    h1->SetBinContent(h1->FindBin(npart)+ shift1, dr_bin.first.getVal());
    h1->SetBinError(h1->FindBin(npart) + shift1, dr_bin.first.getError());
  }
  
  for(int idx =0; idx <3; ++idx){
    std::pair<RooRealVar, RooRealVar> dr_bin = getDoubleRatioValue({centthree_rev[idx+1],centthree_rev[idx]},{0,30}, "CB3:CC3:DRFF");
    double npart = glp::Npart[{cbinthree_rev[idx+1],cbinthree_rev[idx]}].first;
    h2->SetBinContent(h2->FindBin(npart) + shift2, dr_bin.second.getVal());
    h2->SetBinError(h2->FindBin(npart)+ shift2, dr_bin.second.getError());
  }
  h1->GetYaxis()->SetRangeUser(0,1.6);
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kBlue+2);
  h1->SetLineColor(kBlue+2);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitleOffset(1.1);
  h1->GetXaxis()->SetTitle("N_{part}");
  h1->GetYaxis()->SetTitle("(#Upsilon(2S)/#Upsilon(1S))_{PbPb} / #Upsilon(2S)/#Upsilon(1S))_{pp}");
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->GetYaxis()->SetTitleSize(0.04);


  h2->GetYaxis()->SetRangeUser(0,1.6);
  h2->SetMarkerStyle(kCircle);
  h2->SetMarkerColor(kGreen+2);
  h2->SetLineColor(kGreen+2);
  h2->GetXaxis()->SetLabelSize(0.04);
  h2->GetXaxis()->SetTitleOffset(1.1);
  h2->GetXaxis()->SetTitle("N_{part}");
  h2->GetYaxis()->SetTitle("(#Upsilon(3S)/#Upsilon(1S))_{PbPb} / #Upsilon(3S)/#Upsilon(1S))_{pp}");
  h2->GetXaxis()->CenterTitle();
  h2->GetYaxis()->CenterTitle();
  h2->GetYaxis()->SetTitleOffset(1.2);
  h2->GetYaxis()->SetTitleSize(0.04);



  return std::make_pair(h1, h2);
};

//TH1D getPbPbRAA_pt(){
//  Double_t* ptbintwo = new Double_t[3]{0,6,30};
//  Double_t* ptbintwo_rev = new Double_t[3]{30,6,0};
//  
//
//  TH1D* h1 = new TH1D("h1" , "PbPb 2 ratio cent", 10, 0, 30);
//  gStyle->SetOptStat(kFALSE);
//  gStyle->SetOptTitle(kFALSE);
//  for(int idx =0; idx <2; ++idx){
//    std::pair<RooRealVar, RooRealVar> dr_bin = getDoubleRatioValue({0,180},{ptbintwo[idx],ptbintwo[idx+1]}, "CB3:CC2:GC");
//    h1->SetBinContent(h1->FindBin( (ptbintwo[idx]+ptbintwo[idx+1])/2), dr_bin.getVal());
//    h1->SetBinError(h1->FindBin( (ptbintwo[idx]+ptbintwo[idx+1])/2), dr_bin.getError());
//  }
//  h1->GetYaxis()->SetRangeUser(0,1);
//  h1->SetMarkerStyle(kCircle);
//  h1->SetMarkerColor(kBlue);
//  h1->SetLineColor(kBlue);
//  h1->GetXaxis()->SetLabelSize(0.04);
//  h1->GetXaxis()->SetTitle("N_{part}");
//  h1->GetYaxis()->SetTitle("R_{AA}");
//  h1->GetYaxis()->SetTitleOffset(1.2);
//  h1->GetYaxis()->SetTitleSize(0.05);
//  return *h1;
//};
