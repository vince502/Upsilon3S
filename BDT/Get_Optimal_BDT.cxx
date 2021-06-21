#include <iostream>
#include "bininfo.h"
#include "../.workdir.h"
#include "../upsilonAna.h"
#include "yield_eff_signif.h"

std::pair<double,double> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, double ratio= 0.16, string name_input_opt = "", string formula_significance= "S12")
{

  int Nbins = (int) (1.5/interval_score);
  std::cout<< "Nbins: " <<Nbins<< std::endl;
  std::cout << interval_score << "interval, " << Nbins << "NBINS!!!!!" << std::endl;
  string tag_BLIND = "";
  if(info_BDT(ts)[2].find("BLIND")!=std::string::npos) tag_BLIND = "BLIND";
  if(info_BDT(ts)[4].find("BLIND")!=std::string::npos) tag_BLIND = "BLIND";

  std::cout << tag_BLIND << std::endl;
  std::string name_input = Form("%s/BDT/BDTResult/BDTresultY3S_%ld_%s%s.root", workdir.Data(), ts, name_input_opt.c_str(), tag_BLIND.c_str());
  std::cout << name_input << std::endl;

  TFile* file_input = TFile::Open(name_input.c_str());
  TFile* file_output = new TFile("output.root","recreate");
  TTree* tree_train_raw = (TTree*) file_input->Get("dataset/TrainTree");
  std::string theCut = Form("(mass<11.5 && mass>8.0) && (pt>%f) && (pt<%f) && (y>%f) && (y<%f) && (cBin>%d) && (cBin<%d) && (QQVtxProb>%f)", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP );
  TTree* tree_train = tree_train_raw->CopyTree(theCut.c_str());
  std::cout << tree_train_raw->GetEntries() << ", "<< tree_train->GetEntries() << Form(" cl, ch : %d, %d ",cBinLow, cBinHigh) << std::endl;
  Float_t val_bdt;
  Int_t bool_classID;
  tree_train->SetBranchAddress("classID", &bool_classID);
  tree_train->SetBranchAddress(Form("BDT_train_%ld",ts), &val_bdt);
  std::cout << Nbins << "NBINS!!!!!" << std::endl;
  int ent_sig = tree_train->GetEntries("classID==0");
  int ent_bkg = tree_train->GetEntries("classID==1");
  std::cout << ent_sig << ", " << ent_bkg << std::endl;
  
  auto get_BDTcut_from_ratio = [&](double ratio)
  {
    TH1D* hist_res = new TH1D(Form("base_hist_res %ld, [%.1f,%.1f][%.1f,%.1f][%d,%d]",ts, ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh), "signifcance vs BDT", Nbins, -0.5, 1);
    double r = ratio;
  
    bool cmpsz = (r*(double) ent_bkg < (double) ent_sig);
    int sig=0;
    int bkg=0;
    int max_sig = (cmpsz) ? r*(double) ent_bkg : ent_sig ; 
    int max_bkg = (cmpsz) ? ent_bkg : (1/r)*(double) ent_sig; 
    int tuple_pass_sig[Nbins];
    int tuple_pass_bkg[Nbins];
    for (int idx =0; idx <Nbins; idx++){ tuple_pass_sig[idx]=0; tuple_pass_bkg[idx]=0;}
    for ( int idx =0; idx < tree_train->GetEntries(); idx++){
      tree_train->GetEntry(idx);
      if( (sig > max_sig ) && (bkg > max_bkg) ) break;
      int counts =0;
      for( double x = -0.5; x < 1; x+=interval_score){
        if( (sig < max_sig) && (bool_classID==0)){sig+=1; if(val_bdt> x) {tuple_pass_sig[counts]+=1;}}
        if( (bkg < max_bkg) && (bool_classID==1)){bkg+=1; if(val_bdt> x) {tuple_pass_bkg[counts]+=1;}}
        counts++;
      }
    }
    double _signif[Nbins];
    double _signif_err[Nbins];
    int pass_sig=0;
    int pass_bkg=0;
    int zero_bin=0;
    for(int idx =0 ; idx <Nbins; idx++){
      pass_sig = tuple_pass_sig[idx];
      pass_bkg = tuple_pass_bkg[idx];
      Double_t err_sig = TMath::Sqrt(pass_sig);
      Double_t err_bkg = TMath::Sqrt(pass_bkg);
      std::cout << Form("passing sig, bkg : %d, %d, err: %.4f, %.4f",pass_sig, pass_bkg, err_sig, err_bkg) << std::endl;
     
      if( formula_significance=="S12"){
        _signif[idx] = 2*(TMath::Sqrt(pass_sig+pass_bkg)-TMath::Sqrt(pass_bkg));
        if ( pass_sig ==0 && pass_bkg ==0) {_signif_err[idx] =0; if(zero_bin ==0) zero_bin=idx;} 
        else _signif_err[idx] = 2*(TMath::Sqrt(pass_sig+pass_bkg)-TMath::Sqrt(pass_bkg));
      }
      if( formula_significance=="S3"){
         _signif[idx] = (pass_sig+1)/(pass_bkg+1);
        if ( pass_sig ==0 && pass_bkg ==0) {_signif_err[idx] =0; if(zero_bin ==0) zero_bin=idx;} 
//        else _signif_err[idx] = (pass_sig+1)/(pass_bkg+1);
      }
      if( formula_significance=="S2") {
        if ( !(pass_sig ==0 && pass_bkg ==0)){std::cout << "filling" << std::endl; _signif[idx] = pass_sig/TMath::Sqrt(pass_sig+pass_bkg); }
        if ( pass_sig ==0 && pass_bkg ==0) {_signif_err[idx] =0; if(zero_bin ==0) zero_bin=idx;} 
	else _signif_err[idx] =0;
//        else _signif_err[idx] = (err_sig*err_bkg)/(2*pass_sig+ 2*pass_bkg); 
      }
      hist_res->SetBinContent(idx+1,_signif[idx]);
      hist_res->SetBinError(idx+1, _signif_err[idx]);
    }
    hist_res->Fit("pol5","R","",-0.5,interval_score*(zero_bin)-0.5);
    hist_res->Draw();
    auto res = hist_res->GetFunction("pol5");
    double max_signif_bdt_fromfit = res->GetMaximumX(-0.3, 0.5); 
    double max_signif_val = hist_res->GetMaximum();
    return std::make_pair(std::make_pair(max_signif_bdt_fromfit, max_signif_val),hist_res);
  };

  
  auto bdt_res =  get_BDTcut_from_ratio(ratio);
  TH1D* hist_res = bdt_res.second;

  Get_Optimal_BDT_HIST = hist_res;
  TFile* output;
  output = new TFile(Form("%s/BDT/test_OPT_BDT_method2.root",workdir.Data()),"update");
  output->cd();

  //TF1 *f1 = new TF1("poly3", "[0]*x^3+[1]*x^2+[2]*x+[3]",-0.3, 0.4);

  hist_res->Draw();
  output->Close();
  return bdt_res.first;
};
TH1D* func_hist_optimal_BDT(){
  return Get_Optimal_BDT_HIST;
};

//Function to get BDT ratio //
RooRealVar get_eff_acc(std::string type, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int state1 =1, int state2 =3){

  RooRealVar acc1, acc2, eff1, eff2, nbkg;
  acc1  = upsi::getacceptance(pl, ph, (-1)*ylim, ylim, 3.5, state1);
  acc2  = upsi::getacceptance(pl, ph, (-1)*ylim, ylim, 3.5, state2);
  binplotter bp = binplotter(type, ts, ylim,pl, ph, cl, ch, blow, bhigh, false);
  bp.get_yield();
  nbkg = bp.get_bkg();
  dbg();
  RooRealVar yield3S = bp.yield3S;
  dbg();
  auto effp1 = bp.get_eff(state2);
  dbg();
  auto effp2 = bp.get_eff(state2);
  eff2= RooRealVar(Form("eff%d",state2), "", effp2.first);
  eff2.setError(effp2.second);
  /*NEEDED : GET YIELD 1S in that region */
  eff1= RooRealVar(Form("eff%d",state1), "", effp1.first);
  eff1.setError(effp1.second);

  double ratio_acceff = ((eff2.getVal()*acc2.getVal())/(eff1.getVal()*acc1.getVal()));
  double ratio_val = yield3S.getVal()/nbkg.getVal();
  std::cout << "YIELD: " << nbkg.getVal() << ", "<< yield3S.getVal() << std::endl;
  std::cout << "EFF: " << eff1.getVal() << ", "<< eff2.getVal() << std::endl;
  std::cout << "ACC: " << acc1.getVal() << ", "<< acc2.getVal() << std::endl;
  std::cout << "RESULT: " <<ratio_acceff << ", "<< ratio_val << std::endl;
  std::cout << "ERRORS: " << "\n";
  std::cout << "YIELD: " << nbkg.getError() << ", "<< yield3S.getError() << std::endl;
  std::cout << "EFF: " << eff1.getError() << ", "<< eff2.getError() << std::endl;
  std::cout << "ACC: " << acc1.getError() << ", "<< acc2.getError() << std::endl;

  RooRealVar res_var = RooRealVar("result","",ratio_acceff*ratio_val);
  res_var.setError( res_var.getVal()*TMath::Sqrt( TMath::Power(acc1.getError()/acc1.getVal(),2) + TMath::Power(acc2.getError()/acc2.getVal(),2) + TMath::Power(eff1.getError()/eff1.getVal(),2) + TMath::Power(eff2.getError()/eff2.getVal(),2) + TMath::Power(nbkg.getError()/nbkg.getVal(),2) + TMath::Power(yield3S.getError()/yield3S.getVal(),2) ) ); 
  return res_var;
  
};
