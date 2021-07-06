#include "../upsilonAna.cxx"
#include "../.workdir.h"

RooRealVar getDoubleRatioValue(std::pair <int, int>);
TH1D getPbPbRAA(int state =3, double bdt_fix=-2);

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

//////////////////////////////////////////////////////////////////////////////
RooRealVar getDoubleRatioValue(std::pair <int, int> cbpair, std::pair<double, double> ptpair = {0,30},std::string type = "CB3:CC2:GC", double bdtlow_val = 0.2, int state =3, int getPre = 0){
  long ts =1625139244; // 1625503068; //1623391157; //BLIND Nominal

  double ylim = 2.4;
  std::pair<double, double> bdtpair = {0.20,1.00}; //BLIND Nominal ?
  bdtpair.first = bdtlow_val;
  std::cout << bdtlow_val << ", " << bdtpair.first << std::endl;

  binplotter* bp ;
  bp = new binplotter(type,ts, ylim, ptpair.first, ptpair.second, cbpair.first, cbpair.second, bdtpair.first, bdtpair.second, false);
//  bp->set_params("_CC2", 0.00);

  RooRealVar _y = bp->get_yield(state);
  RooRealVar _yacc = upsi::getacceptance(ptpair.first, ptpair.second, (double) -1*ylim, ylim, 3.5, state);
  auto _yeff_pair = bp->get_eff(state);
  double _yeff = _yeff_pair.first;
  RooRealVar yAA, yPP ;
  yAA = RooRealVar(Form("corrY%dyield",state), Form("corrected %dS yield",state), _y.getVal()/(_yacc.getVal()*_yeff));
  std::cout <<"##Yield "<<state<<"S Corrected y/acc eff: "<< yAA.getVal() << std::endl;
  yAA.setError(_y.getError()/(_yacc.getVal()*_yeff ));
  if(getPre==1) return yAA;
  TFile* file_pp = TFile::Open(Form("%s/fitresults_upsilon_fixParm1_seed2_DoubleCB_PP_DATA_pt%.1f-%.1f_y0.0-2.4_muPt4.0.root",hin16023.Data(), ptpair.first, ptpair.second ));
  TFile* file_pp_eff = TFile::Open(Form("%s/efficiency_ups%ds_useDataPtWeight1_tnp_trgId0_trkId0_muId-100_staId-100.root", hin16023.Data(), state ));
  TFile* file_pp_acc = TFile::Open(Form("%s/acceptance_wgt_norm_%dS.root", hin16023.Data(), state ));

  TH1D *hYpp = (TH1D*) file_pp->Get("fitResults");
  TH1D *hApp, *hEpp, *hEpp_pt;
  hApp = (TH1D*) file_pp_acc->Get(Form("hIntAccPP%dS",state));
  hEpp = (TH1D*) file_pp_eff->Get("hcentintEffPP");
  hEpp_pt = (TH1D*) file_pp_eff->Get("hptEffPP");

  double _Ypp = hYpp->GetBinContent(state);
  double _Ypp_err = hYpp->GetBinError(state);
  double _Ypp_acc = hApp->GetBinContent(1);
  double _Ypp_eff = hEpp->GetBinContent(1);
  if(!(ptpair.first ==0 && ptpair.second ==30 )){
    _Ypp_eff = hEpp_pt->GetBinContent(hEpp_pt->FindBin((ptpair.first+ptpair.second)/2));
  }
  yPP = RooRealVar(Form("corrY%dyieldPP", state) , Form("corrected %dS yield pp", state), _Ypp/(_Ypp_eff*_Ypp_acc));
  yPP.setError(_Ypp_err/(_Ypp_eff*_Ypp_acc));
  Double_t cs_pp = 28*TMath::Power(10,9);
  Double_t Nmb = 11968044281.;
  auto taa =glp::Taa[{(int) (cbpair.first/2), (int) (cbpair.second/2)}];
 
  Double_t tirg_presc = 1.0684;
  Double_t taa_Nmb = taa.first*Nmb/tirg_presc;
  Double_t step_one = (cs_pp)/(taa_Nmb);
  Double_t step_two = step_one * (180./(cbpair.second - cbpair.first) );
  Double_t val_RAA = 4.*step_two*yAA.getVal()/yPP.getVal();

  std::cout << std::endl << std::endl << "RAAAAA : " << val_RAA << std::endl << std::endl;
  Double_t err_RAA = 4*step_two*((1/yPP.getVal())*(yAA.getError()- (yAA.getVal()/yPP.getVal())*yPP.getError())); 

  RooRealVar val_return = RooRealVar("raa","", val_RAA);
  val_return.setError(err_RAA);

  return val_return;
};

TH1D getPbPbRAA(int state =3, double bdt_fix = -2){
  Double_t* cbinthree = new Double_t[4]{0,40,100,181};
  Double_t* cbinthree_rev = new Double_t[4]{181,100,40,0};
  Double_t* centthree = new Double_t[4]{0,20,50,90};
  Double_t* centthree_rev = new Double_t[4]{90,50,20,0};
  

  TH1D* h1 = new TH1D("h1" , "PbPb 2 ratio cent", 35, 0, 420);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetOptTitle(kFALSE);
  for(int idx =0; idx <3; ++idx){
    RooRealVar dr_bin;
    if(bdt_fix < -1) dr_bin = getDoubleRatioValue({cbinthree_rev[idx+1],cbinthree_rev[idx]},{0,30}, "CB3:CC2:FF", bdt_tmp_val2[idx+1], state );
    else dr_bin = getDoubleRatioValue({cbinthree_rev[idx+1],cbinthree_rev[idx]},{0,30}, "CB3:CC2:FF", bdt_fix, state );
    double npart = glp::Npart[{centthree_rev[idx+1],centthree_rev[idx]}].first;
    h1->SetBinContent(h1->FindBin(npart), dr_bin.getVal());
    h1->SetBinError(h1->FindBin(npart), dr_bin.getError());
  }
  h1->GetYaxis()->SetRangeUser(0,1);
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kBlue);
  h1->SetLineColor(kBlue);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitle(Form("#Upsilon (%dS) R_{AA}", state) );
  h1->GetYaxis()->SetTitle("R_{AA}");
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->GetYaxis()->SetTitleSize(0.05);
  return *h1;
};

TH1D getPbPbRAA_pt(int state =3){
  Double_t* ptbintwo = new Double_t[3]{0,6,30};
  Double_t* ptbintwo_rev = new Double_t[3]{30,6,0};
  

  TH1D* h1 = new TH1D("h1" , "PbPb 2 ratio cent", 10, 0, 30);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetOptTitle(kFALSE);
  for(int idx =0; idx <2; ++idx){
    std::cout << "take from value: " << bdt_tmp_val[idx+1] << std::endl;
    RooRealVar dr_bin = getDoubleRatioValue({0,181},{ptbintwo[idx],ptbintwo[idx+1]}, "CB3:CC2:GC", bdt_tmp_val[idx+1], state );
    h1->SetBinContent(h1->FindBin( (ptbintwo[idx]+ptbintwo[idx+1])/2), dr_bin.getVal());
    h1->SetBinError(h1->FindBin( (ptbintwo[idx]+ptbintwo[idx+1])/2), dr_bin.getError());
  }
  h1->GetYaxis()->SetRangeUser(0,1);
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kBlue);
  h1->SetLineColor(kBlue);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitle("N_{part}");
  h1->GetYaxis()->SetTitle(Form("#Upsilon (%dS) R_{AA}", state) );
  h1->GetYaxis()->SetTitleOffset(1.2);
  h1->GetYaxis()->SetTitleSize(0.05);
  return *h1;
};
