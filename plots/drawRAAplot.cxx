#include "../upsilonAna.cxx"
#include "../.workdir.h"
#include "../LLR_CCorder.h"


RooRealVar getDoubleRatioValue(std::pair <int, int>);
TH1D* getPbPbRAA(int state =3, double bdt_fix=-2);

// Double Ratio Finding Function
//////////////////////////////////////////////////////////////////////////////
RooRealVar getDoubleRatioValue(std::pair <int, int> cbpair, std::pair<double, double> ptpair = {0,30},std::string type = "CB3:CC2:GC", double bdtlow_val = -2, int state =3, int getPre = 0,long ts =9999999999, bool stdvcut = false){
   // 1625503068; //1623391157; //BLIND Nominal
  double val_bdt_nom = Get_BDT(ts, state, (int) ptpair.first, (int) ptpair.second, cbpair.first, cbpair.second);

  double ylim = 2.4;
  std::pair<double, double> bdtpair = {0.20,1.00}; //BLIND Nominal ?
  bdtpair.first = val_bdt_nom;
  if(bdtlow_val > -2 ) bdtpair.first = bdtlow_val;
  std::cout << val_bdt_nom << ", " << bdtpair.first << std::endl;

  binplotter* bp ;
  bp = new binplotter(type,ts, ylim, ptpair.first, ptpair.second, cbpair.first, cbpair.second, bdtpair.first, bdtpair.second, state, false);
  if (stdvcut){ bp->set_params(0.01); }

  RooRealVar _y = bp->get_yield(state);
  RooRealVar _yacc = upsi::getacceptance(ptpair.first, ptpair.second, (double) -1*ylim, ylim, 3.5, state);
  auto _yeff_pair = bp->get_eff(state);
  double _yeff = _yeff_pair.first;
  RooRealVar yAA, yPP ;
  yAA = RooRealVar(Form("corrY%dyield",state), Form("corrected %dS yield",state), _y.getVal()/(_yacc.getVal()*_yeff));
  std::cout <<"##Yield "<<state<<"S Corrected y/acc eff: "<< yAA.getVal() << ", Efficiency: " << _yeff << ", Acceptance: " << _yacc.getVal() << std::endl;
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

// Centrality RAA function
//////////////////////////////////////////////////////////////////////////////

TH1D* getPbPbRAA(int state =3, double bdt_fix = -2, int shift =0){
  Double_t* cbinthree = new Double_t[4]{0,40,100,181};
  Double_t* cbinthree_rev = new Double_t[4]{181,100,40,0};
  Double_t* centthree = new Double_t[4]{0,20,50,90};
  Double_t* centthree_rev = new Double_t[4]{90,50,20,0};

  Double_t* centnine = new Double_t[10]{0,5,10,20,30,40,50,60,70,90};
  Double_t* centnine_rev = new Double_t[10]{90,70,60,50,40,30,20,10,5,0};
  Double_t* cbinnine = new Double_t[10]{0,10,20,40,60,80,100,120,140,181};
  Double_t* cbinnine_rev = new Double_t[10]{181,140,120,100,80,60,40,20,10,0};

  Color_t theColor;
  theColor = kRed+2;
  if(state ==3) theColor = kGreen+2;
  if(state ==2) theColor = kBlue+2;

  TH1D* h1 = new TH1D(Form("RAAcent_%dS", state) , "PbPb 2 ratio cent", 35, 0, 420);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetOptTitle(kFALSE);
  if(state ==3){
    for(int idx =0; idx <3; ++idx){
      RooRealVar dr_bin;
      if(bdt_fix != -2) dr_bin = getDoubleRatioValue({cbinthree_rev[idx+1],cbinthree_rev[idx]},{0,30}, Form("CB3:CC%d:FF", getNomBkgO(state, 0, 30, cbinthree_rev[idx+1],cbinthree_rev[idx]) ), bdt_tmp_val2[idx+1], state );
      else dr_bin = getDoubleRatioValue({cbinthree_rev[idx+1],cbinthree_rev[idx]},{0,30}, Form("CB3:CC%d:FF", getNomBkgO(state, 0, 30, cbinthree_rev[idx+1],cbinthree_rev[idx]) ), bdt_fix, state );
      double npart = glp::Npart[{centthree_rev[idx+1],centthree_rev[idx]}].first;
      h1->SetBinContent(h1->FindBin(npart) + shift, dr_bin.getVal());
      h1->SetBinError(h1->FindBin(npart) + shift, dr_bin.getError());
    }
  }
  if(state ==2){
    for(int idx =0; idx <9; ++idx){
      RooRealVar dr_bin;
      if(bdt_fix != -2) dr_bin = getDoubleRatioValue({cbinnine_rev[idx+1],cbinnine_rev[idx]},{0,30}, Form("CB3:CC%d:FF", getNomBkgO(state, 0, 30, cbinnine_rev[idx+1],cbinnine_rev[idx]) ), bdt_tmp_val2[idx+1], state );
      else dr_bin = getDoubleRatioValue({cbinnine_rev[idx+1],cbinnine_rev[idx]},{0,30}, Form("CB3:CC%d:FF", getNomBkgO(state, 0, 30, cbinnine_rev[idx+1],cbinnine_rev[idx]) ), bdt_fix, state );
      double npart = glp::Npart[{centnine_rev[idx+1],centnine_rev[idx]}].first;
      h1->SetBinContent(h1->FindBin(npart) + shift, dr_bin.getVal());
      h1->SetBinError(h1->FindBin(npart) + shift, dr_bin.getError());
    }
  }
  h1->GetYaxis()->SetRangeUser(0,1.3);
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(theColor);
  h1->SetLineColor(theColor);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitle(Form("#Upsilon (%dS) R_{AA}", state) );
  h1->GetYaxis()->SetTitle("R_{AA}");
  h1->GetYaxis()->SetTitleOffset(1.1);
  h1->GetYaxis()->SetTitleSize(0.04);
  h1->GetXaxis()->SetTitle("N_{part}");
  h1->GetXaxis()->SetTitleOffset(1.2);
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->CenterTitle();
  return h1;
};

// Pt RAA function
//////////////////////////////////////////////////////////////////////////////
TH1D* getPbPbRAA_pt(int state =3, double bdt_fix = -2, int shift =0){
  TH1::SetDefaultSumw2();
  Double_t* ptbintwo = new Double_t[3]{0,6,30};
  Double_t* ptbintwo_rev = new Double_t[3]{30,6,0};
  Double_t* ptbinthree = new Double_t[4]{0,4,9,30};
  Double_t* ptbinthree_rev = new Double_t[4]{30,9,4,0};
  

  TH1D* h1;
  if(state ==3) h1 =new TH1D("h3pt" , "PbPb 2 ratio cent 2S",2,  ptbintwo);
  if(state ==2) h1 =new TH1D("h2pt" , "PbPb 2 ratio cent 3S",3,  ptbinthree);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetOptTitle(kFALSE);
  if(state == 3){
    for(int idx =0; idx <2; ++idx){
      std::cout << "take from value: " << bdt_tmp_val[idx+1] << std::endl;
      RooRealVar dr_bin;
      if(bdt_fix != -2) dr_bin= getDoubleRatioValue({0,181},{ptbintwo[idx],ptbintwo[idx+1]}, Form("CB3:CC%d:GC", getNomBkgO(state, ptbintwo[idx], ptbintwo[idx+1],0, 181) ), bdt_tmp_val[idx+1], state );
      else dr_bin= getDoubleRatioValue({0,181},{ptbintwo[idx],ptbintwo[idx+1]}, Form("CB3:CC%d:GC", getNomBkgO(state, ptbintwo[idx], ptbintwo[idx+1],0, 181) ), bdt_fix, state );
      h1->SetBinContent(h1->FindBin( (ptbintwo[idx]+ptbintwo[idx+1])/2), dr_bin.getVal());
      h1->SetBinError(h1->FindBin( (ptbintwo[idx]+ptbintwo[idx+1])/2), dr_bin.getError());
    }
  }
  if(state == 2){
    for(int idx =0; idx <3; ++idx){
      std::cout << "take from value: " << bdt_tmp_val[idx+1] << std::endl;
      RooRealVar dr_bin;
      if(bdt_fix != -2) dr_bin= getDoubleRatioValue({0,181},{ptbinthree[idx],ptbinthree[idx+1]}, Form("CB3:CC%d:GC", getNomBkgO(state, ptbinthree[idx], ptbinthree[idx+1],0, 181) ), bdt_tmp_val[idx+1], state );
      else dr_bin= getDoubleRatioValue({0,181},{ptbinthree[idx],ptbinthree[idx+1]}, Form("CB3:CC%d:GC", getNomBkgO(state, ptbinthree[idx], ptbinthree[idx+1],0, 181) ), bdt_fix, state );
      h1->SetBinContent(h1->FindBin( (ptbinthree[idx]+ptbinthree[idx+1])/2), dr_bin.getVal());
      h1->SetBinError(h1->FindBin( (ptbinthree[idx]+ptbinthree[idx+1])/2), dr_bin.getError());
    }
  }
  h1->GetYaxis()->SetRangeUser(0,1.3);
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kGreen+2);
  h1->SetLineColor(kGreen+2);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetTitle(Form("#Upsilon (%dS) R_{AA}", state) );
  h1->GetYaxis()->SetTitleOffset(1.1);
  h1->GetXaxis()->SetTitle("N_{part}");
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetTitleOffset(1.2);
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetTitleSize(0.04);
  return h1;
};

// Draw Centrality & Int. RAA Plot
//////////////////////////////////////////////////////////////////////////////
void drawRAAplot(){
//  TCanvas* c2 = new TCanvas("c2","",700,800);
//
//  c2->cd();
//  c2->Draw();
//  auto hPbPb = getPbPbRAA();
//  hPbPb->Draw("pe");
//  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_test.pdf", workdir.Data() ));
//  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_test.cxx", workdir.Data() ));
//  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_test_bdt0.2_1.0.cxx", workdir.Data() ));
  TCanvas* c2 = new TCanvas("c2","",1000,700);
  TCanvas* c3 = new TCanvas("c3","",1000,700);


  TPad *p2_1, *p2_2, *p3_1, *p3_2;
  p2_1 = new TPad("p21", "", 0.00, 0,0.83,1);
  p2_1->SetRightMargin(0);
  p2_2 = new TPad("p22", "", 0.83, 0,1,1);
  p2_2->SetLeftMargin(0);
  p3_1 = new TPad("p31", "", 0.00, 0,0.83,1);
  p3_1->SetRightMargin(0);
  p3_2 = new TPad("p32", "", 0.83, 0,1,1);
  p3_2->SetLeftMargin(0);
  p2_1->SetTicks();
  p2_2->SetTicks();

  TH1D* y1_int = new TH1D("y1int", "", 3,0,1);
  TH1D* y2_int = new TH1D("y2int", "", 3,0,1);
  TH1D* y3_int = new TH1D("y3int", "", 3,0,1);
  y1_int->GetXaxis()->SetBinLabel(2, "Int.");// Form("%.0f",glp::Npart[{0,90}].first) );
//  y2_int->GetXaxis()->SetBinLabel(2, "Integrated");// Form("%.0f",glp::Npart[{0,90}].first) );
//  y3_int->GetXaxis()->SetBinLabel(3, "Integrated"); //Form("%.0f",glp::Npart[{0,90}].first) );
  y1_int->GetYaxis()->SetLabelSize(0);
  y1_int->GetXaxis()->SetLabelSize(0.12);

  y1_int->GetYaxis()->SetLabelOffset(0);
  y1_int->GetYaxis()->SetRangeUser(0,1.3);
  y2_int->GetYaxis()->SetLabelSize(0);
  y2_int->GetXaxis()->SetLabelSize(0.12);
  y2_int->GetYaxis()->SetLabelOffset(0);
  y2_int->GetYaxis()->SetRangeUser(0,1.3);
  y3_int->GetYaxis()->SetLabelSize(0);
  y3_int->GetXaxis()->SetLabelSize(0.12);
  y3_int->GetYaxis()->SetLabelOffset(0);
  y3_int->GetYaxis()->SetRangeUser(0,1.3);

  auto raa2_int = getDoubleRatioValue({0,181}, {0,30},Form("CB3:CC%d:GC", getNomBkgO(2, 0, 30,0, 181) ), -2, 2);
  auto raa3_int = getDoubleRatioValue({0,181}, {0,30},Form("CB3:CC%d:GC", getNomBkgO(3, 0, 30,0, 181) ), -2, 3);
//  auto hPbPb1S = getPbPbRAA(1, -0.1, 2);
  auto hPbPb2S = getPbPbRAA(2, -2, 0);
  auto hPbPb3S = getPbPbRAA(3, -2, 0 );
  TGraphAsymmErrors* gr1S = new TGraphAsymmErrors(10); 
  gr1S->SetName("RAAcent_1S");
  gr1S->SetPoint(0,8.3000002, 0.79200000);
  gr1S->SetPoint(1,30.600000, 0.92199999);
  gr1S->SetPoint(2, 53.900002, 0.60900003);
  gr1S->SetPoint(3, 87.000000, 0.52399999);
  gr1S->SetPoint(4, 131.39999, 0.48500001);
  gr1S->SetPoint(5, 189.20000, 0.40200001);
  gr1S->SetPoint(6, 264.20001, 0.32400000);
  gr1S->SetPoint(7, 333.29999, 0.32100001);
  gr1S->SetPoint(8, 384.29999, 0.31900001);

  gr1S->SetPointError(0, 0, 0, 0.13100000, 0.13100000);
  gr1S->SetPointError(1, 0, 0, 0.088000000, 0.088000000);
  gr1S->SetPointError(2, 0, 0, 0.052999999, 0.052999999);
  gr1S->SetPointError(3, 0, 0, 0.035999998, 0.035999998);
  gr1S->SetPointError(4, 0, 0, 0.027000001, 0.027000001);
  gr1S->SetPointError(5, 0, 0, 0.039000001, 0.039000001);
  gr1S->SetPointError(6, 0, 0, 0.017000001, 0.017000001);
  gr1S->SetPointError(7, 0, 0, 0.021000000, 0.021000000);
  gr1S->SetPointError(8, 0, 0, 0.018999999, 0.018999999);
  gr1S->SetMarkerStyle(kFullCircle);
  gr1S->GetYaxis()->SetRangeUser(0, 1.3);
  gr1S->SetMarkerSize(1);
  gr1S->SetLineColor(kRed+3);
  gr1S->SetMarkerColor(kRed+3);

  TLegend* leg = new TLegend(0.65, 0.4, 0.85, 0.7);
  leg->AddEntry(gr1S, "#varUpsilon(1S) HIN-16-023", "pl");
  leg->AddEntry(hPbPb2S, "#varUpsilon(2S)", "pl");
  leg->AddEntry(hPbPb3S, "#varUpsilon(3S)", "pl");
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  TLegend* leg2 = new TLegend(0.65, 0.4, 0.85, 0.7);
  leg2->AddEntry(hPbPb3S, "#varUpsilon(3S)", "pl");
  leg2->SetBorderSize(0);
  leg2->SetTextFont(42);
  leg2->SetTextSize(0.04);
  gStyle->SetEndErrorSize(0);

  y1_int->SetBinContent(1, 0.376 );
  y1_int->SetBinError(1, TMath::Sqrt(0.013*0.013 + 0.035*0.035) );
  y2_int->SetBinContent(2, raa2_int.getVal() );
  y2_int->SetBinError(2, raa2_int.getError() );
  y3_int->SetBinContent(3, raa3_int.getVal() );
  y3_int->SetBinError(3, raa3_int.getError() );
  y1_int->SetMarkerStyle(kFullCircle);
  y1_int->SetMarkerColor(kRed+2);
  y1_int->SetLineColor(kRed+2);
  y2_int->SetMarkerStyle(kCircle);
  y2_int->SetMarkerColor(kBlue+2);
  y2_int->SetLineColor(kBlue+2);
  y3_int->SetMarkerStyle(kCircle);
  y3_int->SetMarkerColor(kGreen+2);
  y3_int->SetLineColor(kGreen+2);
  TLatex* tl = new TLatex();
  tl->SetTextSize(0.04);
  tl->SetTextFont(42);
  tl->SetNDC();
  c2->cd();
  p2_1->Draw();
  p2_2->Draw();

  p2_1->cd();
  TLine* lineone = new TLine();
  lineone->SetLineStyle(kDashed);
  lineone->DrawLineNDC(0,0.5,1,0.5);
  gr1S->Draw("APE");
  hPbPb2S->Draw("same");
  hPbPb3S->Draw("same");
  tl->DrawLatex( 0.2, 0.8,"p^{#mu#mu}_{T} < 30 GeV/c");
  tl->DrawLatex( 0.2, 0.75, "|y| < 2.4");
  tl->DrawLatex( 0.2, 0.7, "p^{#mu}_{T} > 3.5 GeV/c");
  leg->Draw();

  p2_2->cd();
  y1_int->Draw("");
  y2_int->Draw("same");
  y3_int->Draw("same");
  c2->Modified();

  c3->cd();
  p3_1->Draw();
  p3_2->Draw();

  p3_1->cd();
  hPbPb3S->Draw("");
  tl->DrawLatex( 0.2, 0.8,"p^{#mu#mu}_{T} < 30 GeV/c");
  tl->DrawLatex( 0.2, 0.75, "|y| < 2.4");
  tl->DrawLatex( 0.2, 0.7, "p^{#mu}_{T} < 4 GeV/c");
  leg2->Draw();

  p3_2->cd();
  y3_int->Draw();

  CMS_lumi_square(p2_1, 2, 33);
  CMS_lumi_square(p3_1, 2, 33);

  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_RAA_nS.pdf", workdir.Data() ));
  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_RAA_nS.C", workdir.Data() ));
  c3->SaveAs(Form("%s/plots/DoubleRatio/plot_RAA_3S.pdf", workdir.Data() ));
  c3->SaveAs(Form("%s/plots/DoubleRatio/plot_RAA_3S.C", workdir.Data() ));
  
  TFile* output = new TFile("resultRAA_nS_centrality.root", "recreate");
  output->cd();
  y1_int->Write();
  y2_int->Write();
  y3_int->Write();
  hPbPb2S->Write();
  hPbPb3S->Write();
  gr1S->Write();
  output->Close();


};

// Draw Pt RAA Plot
//////////////////////////////////////////////////////////////////////////////
void drawRAApt_plot(){
  gStyle->SetErrorX(0.);
//  TCanvas* c2 = new TCanvas("c2","",700,800);
//
//  c2->cd();
//  c2->Draw();
//  auto hPbPb = getPbPbRAA();
//  hPbPb->Draw("pe");
//  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_test.pdf", workdir.Data() ));
//  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_test.cxx", workdir.Data() ));
//  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_test_bdt0.2_1.0.cxx", workdir.Data() ));
  TCanvas* c2 = new TCanvas("c2","",1000,700);
  auto hPbPb3S = getPbPbRAA_pt(3);
  auto hPbPb2S = getPbPbRAA_pt(2);
//  TH1D* hPbPb2S = new TH1D("hPbPb2S" , "PbPb 2 ratio cent", 1, 0, 3);
//  auto raa2S_lowpt = getDoubleRatioValue({0,181},{0,4}, "CB3:CC2:GC", -0.1, 2, 0);
  TLatex* tl = new TLatex();
  tl->SetTextSize(0.04);
  tl->SetTextFont(42);
  tl->SetNDC();
  c2->cd();
  gStyle->SetErrorX(0.);

  TLine* lineone = new TLine();
  TLegend* leg = new TLegend(0.65, 0.4, 0.85, 0.7);
  lineone->SetLineStyle(kDashed);
  lineone->DrawLineNDC(0,0.5,1,0.5);

//  hPbPb2S->SetBinContent(hPbPb3S->FindBin(2), raa2S_lowpt.getVal());
//  hPbPb2S->SetBinError(hPbPb3S->FindBin(2), raa2S_lowpt.getError());
  hPbPb2S->SetMarkerStyle(kCircle);
  hPbPb2S->SetLineColor(kBlue+2);
  hPbPb2S->SetMarkerColor(kBlue+2);
  leg->AddEntry(hPbPb2S, "#varUpsilon(2S)", "pl");
  leg->AddEntry(hPbPb3S, "#varUpsilon(3S)", "pl");
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  hPbPb3S->Draw();
  hPbPb2S->Draw("same");
  leg->Draw();
  tl->DrawLatex( 0.2, 0.8,"p^{#mu#mu}_{T} < 30 GeV/c");
  tl->DrawLatex( 0.2, 0.75, "|y| < 2.4");
  tl->DrawLatex( 0.2, 0.7, "p^{#mu}_{T} > 3.5 GeV/c");


  CMS_lumi_square(c2, 2, 33);
  c2->Modified();
  c2->Update();

  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_RAApt_nS.pdf", workdir.Data() ));
  c2->SaveAs(Form("%s/plots/DoubleRatio/plot_RAApt_nS.C", workdir.Data() ));
  TFile* output = new TFile("resultRAA_nS_pt.root", "recreate");
  output->cd();
  hPbPb2S->Write();
  hPbPb3S->Write();
  output->Close();
};
