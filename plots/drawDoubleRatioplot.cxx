#include "../upsilonAna.cxx"
#include "../.workdir.h"
#include "../LLR_CCorder.h"

RooRealVar getDoubleRatioValue(std::pair <int, int> cbpair, std::pair<double, double> ptpair = {0,30},std::string type = "CB3:CC2:GC", std::pair<double, double> bdtpair = {-0.1,1.00}, int state =3, int get_pre=0, long ts = 9999999999, bool eff_old= false);
std::pair<TH1D*, TH1D*> getPbPbDR(int shift1=0, int shift2=0);

void drawDoubleRatioplot(){
  TCanvas* c2 = new TCanvas("c2","",900,700);
  TCanvas* c3 = new TCanvas("c3","",900,700);
  TPad *p2_1, *p2_2, *p3_1, *p3_2;
  p2_1 = new TPad("p21", "", 0.05, 0.02,0.83,1);
  p2_1->SetRightMargin(0);
  p2_1->SetBottomMargin(0.02);
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
  auto dr_int = getDoubleRatioValue({0,181}, {0,30}, "CB3:CC2:DRFF", {-0.1, 1});
  TLatex* tl = new TLatex();
  tl->SetTextSize(0.04);
  tl->SetTextFont(42);
  tl->SetNDC();
  c2->cd();
  p2_1->Draw();
  p2_2->Draw();
  auto hPbPb2S = hPbPb.first;
  auto dr2S_int = getDoubleRatioValue({0,181}, {0,30}, "CB3:CC2:DRFF", {-0.1, 1},2);

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
  auto dr3S_int = getDoubleRatioValue({0,181}, {0,30}, "CB3:CC2:DRFF", {-0.1, 1},3);

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

//////////////////////////////////////////////////////////////////////////////
RooRealVar getDoubleRatioValue(std::pair <int, int> cbpair, std::pair<double, double> ptpair = {0,30},std::string type = "CB3:CC2:GC", std::pair<double, double> bdtpair = {-0.1,1.00}, int state =3,  int get_pre =0, long ts = 9999999999, bool eff_old = true){
  double val_bdt_nom = Get_BDT(ts, state, (int) ptpair.first, (int) ptpair.second, cbpair.first, cbpair.second);
  if(bdtpair.first ==-2){
    bdtpair.first = val_bdt_nom;
  }
  double ylim = 2.4;

  binplotter* bp ;
  bp = new binplotter(type,ts, ylim, ptpair.first, ptpair.second, cbpair.first, cbpair.second, bdtpair.first, bdtpair.second, state, false, eff_old);

  RooRealVar fracYNPbPb  = bp->get_frac(state);
  auto _Yaa_eff_pair = bp->get_eff(state);
  auto _Y1aa_eff_pair = bp->get_eff(1);
  double _Yaa_eff = _Yaa_eff_pair.first;
  double _Y1aa_eff = _Y1aa_eff_pair.first;
  RooRealVar _Yaa_acc = upsi::getacceptance(ptpair.first, ptpair.second, (double) -1*ylim, ylim, 3.5, state);
  RooRealVar _Y1aa_acc = upsi::getacceptance(ptpair.first, ptpair.second, (double) -1*ylim, ylim, 3.5, 1);
  fracYNPbPb.setVal(fracYNPbPb.getVal() *((_Y1aa_eff * _Y1aa_acc.getVal() ) / (_Yaa_eff * _Yaa_acc.getVal() )  ) );
  fracYNPbPb.setError(fracYNPbPb.getError() *((_Y1aa_eff * _Y1aa_acc.getVal() ) / (_Yaa_eff * _Yaa_acc.getVal() )  ));
  if(get_pre ==1) return fracYNPbPb;
  RooRealVar yNAA, yNPP, y1PP,  fracYNPP;
  TFile* file_pp = TFile::Open(Form("%s/fitresults_upsilon_fixParm1_seed2_DoubleCB_PP_DATA_pt0.0-30.0_y0.0-2.4_muPt4.0.root",hin16023.Data() ));
  TFile* file_pp_eff = TFile::Open(Form("%s/efficiency_ups%ds_useDataPtWeight1_tnp_trgId0_trkId0_muId-100_staId-100.root", hin16023.Data(), state ));
  TFile* file_pp_acc = TFile::Open(Form("%s/acceptance_wgt_norm_%dS.root", hin16023.Data(), state ));
  TFile* file_pp1_eff = TFile::Open(Form("%s/efficiency_ups1s_useDataPtWeight1_tnp_trgId0_trkId0_muId-100_staId-100.root", hin16023.Data() ));
  TFile* file_pp1_acc = TFile::Open(Form("%s/acceptance_wgt_norm_1S.root", hin16023.Data() ));

  TH1D *hYpp = (TH1D*) file_pp->Get("fitResults");
  TH1D *hApp, *hEpp, *h1App, *h1Epp;
  hApp = (TH1D*) file_pp_acc->Get(Form("hIntAccPP%dS",state));
  hEpp = (TH1D*) file_pp_eff->Get("hcentintEffPP");
  h1App = (TH1D*) file_pp1_acc->Get(Form("hIntAccPP1S"));
  h1Epp = (TH1D*) file_pp1_eff->Get("hcentintEffPP");
  double _Ypp_acc = hApp->GetBinContent(1);
  double _Ypp_eff = hEpp->GetBinContent(1);
  double _Y1pp_acc = h1App->GetBinContent(1);
  double _Y1pp_eff = h1Epp->GetBinContent(1);

  double _Y1pp = hYpp->GetBinContent(1);
  double _Y1pp_err = hYpp->GetBinError(1);
  double _corr;
  if(state ==2 ) _corr = 7.048e+04; 
  if(state ==3 ) _corr = -4.57e+04;
  double _YNpp = hYpp->GetBinContent(state);
  double _YNpp_err = hYpp->GetBinError(state);
//  double _Y3pp = hYpp->GetBinContent(3);
//  double _Y3pp_err = hYpp->GetBinError(3);
  y1PP = RooRealVar("Y1yieldPP", "1S yield pp", _Y1pp /(_Y1pp_acc* _Y1pp_eff) );
  yNPP = RooRealVar(Form("Y%dyieldPP",state), Form("%dS yield pp",state), _YNpp/(_Ypp_acc* _Ypp_eff));
//  y3PP = RooRealVar("Y3yieldPP", "3S yield pp", _Y3pp);
  y1PP.setError(_Y1pp_err/(_Y1pp_acc* _Y1pp_eff));
  yNPP.setError(_YNpp_err/(_Ypp_acc* _Ypp_eff));
//  y3PP.setError(_Y3pp_err);
  fracYNPP = RooRealVar(Form("fracY%dover1SPP",state), Form("%dS fraction",state), _YNpp/_Y1pp);
//  fracY3PP = RooRealVar("fracY3over1SPP", "3S fraction", _Y3pp/_Y1pp);
//  fracYNPP.setError((_YNpp/_Y1pp)*TMath::Sqrt(TMath::Power( _YNpp_err/_YNpp,2) + TMath::Power((_Y1pp_err/_Y1pp),2) - 2*( _corr / (_Y1pp * _YNpp) ) )); //PP statistical Error Aslo goes to Global
  fracYNPP.setError(0);
  std::cout << "Frac Y(nS) PP : " << Form("%.4f +- %.4f",fracYNPP.getVal(), fracYNPP.getError() ) << std::endl; 
//  fracY3PP.setError((1/_Y1pp)*TMath::Sqrt(TMath::Power( _Y1pp_err,2) + TMath::Power((_Y3pp/_Y1pp)*_Y3pp_err,2) ));
//  std::cout << "fracY3PP Val, Err: " << fracY3PP.getVal() <<", " << fracY3PP.getError() << std::endl;
  RooRealVar DRYN = RooRealVar(Form("%dSDoubleRatio",state), Form("%dS Double Ratio PbPb/pp",state), fracYNPbPb.getVal()/fracYNPP.getVal());
//  RooRealVar DRY3 = RooRealVar("3SDoubleRatio", "3S Double Ratio PbPb/pp" , fracY3PbPb.getVal()/fracY3PP.getVal());
  DRYN.setError((1/fracYNPP.getVal())*TMath::Sqrt(TMath::Power( fracYNPbPb.getError(),2) + TMath::Power((fracYNPbPb.getVal()/fracYNPP.getVal())*fracYNPP.getError(),2) ));
//  DRY3.setError((1/fracY3PP.getVal())*TMath::Sqrt(TMath::Power( fracY3PbPb.getError(),2) + TMath::Power((fracY3PbPb.getVal()/fracY3PP.getVal())*fracY3PP.getError(),2) ));
//  std::cout << "DRY3 Val, Error: " << DRY3.getVal() << ", " <<  DRY3.getError() << std::endl;
  return DRYN;
};
//////////////////////////////////////////////////////////////////////////////
std::pair<TH1D*, TH1D*> getPbPbDR(int shift1 = 0, int shift2 = 1){
  Double_t* cbinnine = new Double_t[10]{0,5,10,20,30,40,50,60,70,90};
  Double_t* cbinnine_rev = new Double_t[10]{90,70,60,50,40,30,20,10,5,0};
  Double_t* centnine = new Double_t[10]{0,10,20,40,60,80,100,120,140,181};
  Double_t* centnine_rev = new Double_t[10]{181,140,120,100,80,60,40,20,10,0};
  Double_t* cbinthree = new Double_t[4]{0,20,50,90};
  Double_t* cbinthree_rev = new Double_t[4]{90,50,20,0};
  Double_t* centthree = new Double_t[4]{0,40,100,181};
  Double_t* centthree_rev = new Double_t[4]{181,100,40,0};

  TH1D* h1 = new TH1D("h1" , "PbPb 2S double ratio cent", 420, 0, 420);
  TH1D* h2 = new TH1D("h2" , "PbPb 3S double ratio cent", 420, 0, 420);
  setTDRStyle();
  for(int idx =0; idx <9; ++idx){
    std::cout << cbinnine_rev[idx+1]*2 << " , " << cbinnine_rev[idx]*2 << std::endl;
    RooRealVar dr_bin = getDoubleRatioValue({centnine_rev[idx+1],centnine_rev[idx]},{0,30}, Form("CB3:CC%d:DRFF", getNomBkgO(2, 0, 30, centnine_rev[idx+1],centnine_rev[idx])),{-2.,1.0}, 2);
    double npart = glp::Npart[{cbinnine_rev[idx+1],cbinnine_rev[idx]}].first;
    h1->SetBinContent(h1->FindBin(npart)+ shift1, dr_bin.getVal());
    h1->SetBinError(h1->FindBin(npart) + shift1, dr_bin.getError());
  }
  
  for(int idx =0; idx <3; ++idx){
    RooRealVar dr_bin = getDoubleRatioValue({centthree_rev[idx+1],centthree_rev[idx]},{0,30}, Form("CB3:CC%d:DRFF",getNomBkgO(3, 0,30, centthree_rev[idx+1],centthree_rev[idx])), {-2., 1.0}, 3);
    double npart = glp::Npart[{cbinthree_rev[idx+1],cbinthree_rev[idx]}].first;
    h2->SetBinContent(h2->FindBin(npart) + shift2, dr_bin.getVal());
    h2->SetBinError(h2->FindBin(npart)+ shift2, dr_bin.getError());
  }
  h1->GetYaxis()->SetRangeUser(0,1.6);
  h1->SetMarkerStyle(kCircle);
  h1->SetMarkerColor(kBlue+2);
  h1->SetLineColor(kBlue+2);
  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetXaxis()->SetTitleOffset(1.1);
  h1->GetXaxis()->SetTitle("#LT N_{part} #GT");
  h1->GetYaxis()->SetTitle("(#Upsilon(nS)/#Upsilon(1S))_{PbPb} / #Upsilon(nS)/#Upsilon(1S))_{pp}");
  h1->GetXaxis()->CenterTitle();
  h1->GetYaxis()->CenterTitle();
  h1->GetYaxis()->SetTitleOffset(1.0);
  h1->GetXaxis()->SetTitleOffset(1.1);
  h1->GetYaxis()->SetTitleSize(0.05);
  h1->GetXaxis()->SetTitleSize(0.05);


  h2->GetYaxis()->SetRangeUser(0,1.6);
  h2->SetMarkerStyle(kCircle);
  h2->SetMarkerColor(kGreen+2);
  h2->SetLineColor(kGreen+2);
  h2->GetXaxis()->SetLabelSize(0.05);
  h2->GetXaxis()->SetTitleOffset(1.1);
  h2->GetXaxis()->SetTitle("N_{part}");
  h2->GetYaxis()->SetTitle("(#Upsilon(3S)/#Upsilon(1S))_{PbPb} / #Upsilon(3S)/#Upsilon(1S))_{pp}");
  h2->GetXaxis()->CenterTitle();
  h2->GetYaxis()->CenterTitle();
  h2->GetYaxis()->SetTitleOffset(1.2);
  h2->GetYaxis()->SetTitleSize(0.05);

  return std::make_pair(h1, h2);
};

