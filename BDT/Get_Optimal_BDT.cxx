#include <iostream>
#include "bininfo.h"
#include "../.workdir.h"
#include "../upsilonAna.h"
#include "yield_eff_signif.h"
#include "TApplication.h"

std::pair<double,TH1D*> Get_Optimal_BDT(long ts, double ptMin, double ptMax, double rapMin, double rapMax, int cBinLow, int cBinHigh, double cutQVP, double ratio =0.16 , int train_state =3, string name_input_opt = "", string formula_significance= "S2", string the_opt="")
{
  
  std::string st_opt;
  if(strcmp(name_input_opt.c_str(),"")!=0) st_opt = "_"+name_input_opt;
  std::string output_fname = Form("%s/BDT/Significance_hist/HIST_train%dS_%ld_pt_%d-%d_rap_%d-%d_cbin_%d-%d_vp_%.4f_%s%s", workdir.Data(), train_state, ts, (int) ptMin, (int) ptMax, (int) (rapMin*10), (int) (rapMax*10), cBinLow, cBinHigh, cutQVP, formula_significance.c_str(), st_opt.c_str() );
  TFile* HISTFILE = nullptr;
  HISTFILE = new TFile(Form("%s.root",output_fname.c_str()), "update" );
  std::cout << static_cast<void*>(HISTFILE) << std::endl;

  TList* lok =nullptr;
  lok= HISTFILE->GetListOfKeys();
  if (!(lok->FindObject(Form("r_%.6f", ratio))==nullptr) || !(lok->FindObject(Form("r_%.6f%s", ratio, the_opt.c_str()))==nullptr) ){
    std::cout << "[INFO] Reading From HISTOFILE" << std::endl;
    string dirname = Form("r_%.6f", ratio);
    if ( the_opt.find("SYS") != std::string::npos) { dirname = dirname+""+ the_opt; }
    std::cout << dirname.c_str() << std::endl;
    double theSig = stod(HISTFILE->Get(Form("%s/max_sig", dirname.c_str()) )->GetTitle());
    TH1D*   theHist = (TH1D*) HISTFILE->Get(Form("%s/HISTO", dirname.c_str()) );
    TH1D* cloneHist = (TH1D*)  theHist->Clone();
    cloneHist->SetDirectory(0);
    HISTFILE->Close();
    return std::make_pair(theSig, cloneHist);
  }

  int Nbins = (int) (1.5/interval_score);
  std::cout<< "Nbins: " <<Nbins<< std::endl;
  std::cout << interval_score << "interval, " << Nbins << "NBINS!!!!!" << std::endl;
  string tag_BLIND = "";
  if(info_BDT(ts)[2].find("BLIND")!=std::string::npos) tag_BLIND = "BLIND";
  if(info_BDT(ts)[4].find("BLIND")!=std::string::npos) tag_BLIND = "BLIND";
  std::cout << tag_BLIND << std::endl;

  std::string name_input = Form("%s/BDT/BDTResult/BDTresultY3S_%ld_%s%s.root", workdir.Data(), ts, name_input_opt.c_str(), tag_BLIND.c_str());
  if(ts == 9999999991) name_input = Form("%s/BDT/BDTResult/BDTresultY3S_%ld_%s%s.root", workdir.Data(), 9999999999, name_input_opt.c_str(), tag_BLIND.c_str());
  std::string name_input_rd = Form("%s/BDT/roodatasets/OniaRooDataset_BDT%ld_OniaSkim_TrigS13_BDT.root", workdir.Data(), ts);
  std::cout << name_input << std::endl;
  std::cout << name_input_rd << std::endl;
  TFile* file_input = TFile::Open(name_input.c_str());
  TFile* file_input_rd = TFile::Open(name_input_rd.c_str());
  TFile* cache_out = new TFile(".cache.root","recreate");
  TChain* tree_train_raw = new TChain();
  RooDataSet* rd_data = (RooDataSet*) file_input_rd->Get(Form("dataset_Y%dSpt%dto%d", train_state, (int) ptMin, (int) ptMax));
  std::string treedir = "";
  if(ts >= 9999999990) treedir = Form("/data/Y%dSpt%dto%d", train_state, (int) ptMin, (int) ptMax);
  tree_train_raw->Add(Form("%s%s/dataset1/TrainTree", name_input.c_str(), treedir.c_str()));
  tree_train_raw->Add(Form("%s%s/dataset2/TrainTree", name_input.c_str(), treedir.c_str()));
  std::string theCut = Form("(mass<11.5 && mass>8.0) && (pt>%f) && (pt<%f) && (y>%f) && (y<%f) && (cBin>=%d) && (cBin<%d) && (QQVtxProb>%f)", ptMin, ptMax, rapMin, rapMax, cBinLow, cBinHigh, cutQVP );
  TChain* tree_train;
  rd_data = (RooDataSet*) rd_data->reduce(theCut.c_str());
  tree_train = (TChain*) tree_train_raw->CopyTree(theCut.c_str());
  std::cout << tree_train_raw->GetEntries() << ", "<< tree_train->GetEntries() << Form(" cl, ch : %d, %d ",cBinLow, cBinHigh) << std::endl;
  Float_t val_bdt;
  Int_t bool_classID;
  tree_train->SetBranchAddress("classID", &bool_classID);
  tree_train->SetBranchAddress(Form("BDT"), &val_bdt);
  std::cout << Nbins << "NBINS!!!!!" << std::endl;
  int ent_sig = tree_train->GetEntries("classID==0");
  int ent_bkg = tree_train->GetEntries("classID==1");
  std::cout << ent_sig << ", " << ent_bkg << std::endl;
  double sig_lim_bdt = 10;
  
  TH1::AddDirectory(kFALSE);
  auto get_BDTcut_from_ratio = [&](double ratio)
  {
    TH1D* hist_res = new TH1D("HISTO", "signifcance vs BDT", Nbins, -0.5, 1);
    double r = ratio;
  
//    std::cout << r*(double) ent_bkg << " vs " << ent_sig << std::endl;
//    bool cmpsz = (r*(double) ent_bkg < (double) ent_sig);
    int sig=0;
    int bkg=0;
//    int max_sig = (cmpsz) ? r*(double) ent_bkg : ent_sig ; 
//    int max_bkg = (cmpsz) ? ent_bkg : (1/r)*(double) ent_sig; 
    int tuple_pass_sig[Nbins];
    int tuple_pass_bkg[Nbins];
    for (int idx =0; idx <Nbins; idx++){ tuple_pass_sig[idx]=0; tuple_pass_bkg[idx]=0;}
    for ( int idx =0; idx < tree_train->GetEntries(); idx++){
      tree_train->GetEntry(idx);
      int counts =0;
      for( double x = -0.5; x < 1; x+=interval_score){
        if(bool_classID==0){sig+=1; if(val_bdt> x) {tuple_pass_sig[counts]+=1;}}
        if(bool_classID==1){bkg+=1; if(val_bdt> x) {tuple_pass_bkg[counts]+=1;}}
        counts++;
      }
    }
    double _signif[Nbins];
    double _signif_err[Nbins];
    double pass_sig=0;
    double pass_bkg=0;
    double zero_bin=0;
    double scale_factor = (double) ((double) ent_bkg/ (double) ent_sig)*ratio;
    for(int idx =0 ; idx <Nbins; idx++){
      pass_sig = ((double) tuple_pass_sig[idx])*(scale_factor);
      pass_bkg = tuple_pass_bkg[idx];
      Double_t err_sig = TMath::Sqrt(pass_sig);
      Double_t err_bkg = TMath::Sqrt(pass_bkg);
 //     std::cout << Form("passing sig, bkg : %.4f, %.4f, err: %.4f, %.4f",(double) tuple_pass_sig[idx], pass_bkg, err_sig, err_bkg) << std::endl;
//      std::cout << Form("passing sig, bkg : %.4f, %.4f, err: %.4f, %.4f",pass_sig, pass_bkg, err_sig, err_bkg) << std::endl;
     
      if( formula_significance=="S12"){
        _signif[idx] = 2*(TMath::Sqrt(pass_sig+pass_bkg)-TMath::Sqrt(pass_bkg));
        if ( pass_sig ==0 && pass_bkg ==0) {_signif_err[idx] =0; if(zero_bin ==0) zero_bin=idx;} 
	else _signif_err[idx] = 2*TMath::Sqrt(_signif[idx]/(2*TMath::Sqrt(pass_sig+pass_bkg) ) );
      }
      if( formula_significance=="S3"){
         _signif[idx] = (pass_sig+1)/(pass_bkg+1);
        if ( pass_sig ==0 && pass_bkg ==0) {_signif_err[idx] =0; if(zero_bin ==0) zero_bin=idx;} 
//        else _signif_err[idx] = (pass_sig+1)/(pass_bkg+1);
      }
      if( formula_significance=="S2") {
        if ( !(pass_sig ==0 && pass_bkg ==0)){std::cout << "filling" << std::endl; _signif[idx] = pass_sig/TMath::Sqrt(pass_sig+pass_bkg); }
        if ( pass_sig ==0 && pass_bkg ==0) {_signif_err[idx] =0; if(zero_bin ==0) zero_bin=idx;} 
        else _signif_err[idx] = ( TMath::Sqrt(TMath::Power(pass_sig,2)+ 4*pass_sig*pass_bkg)/(2*(pass_sig+ pass_bkg) ) ); 
	if (_signif_err[idx] > 5*_signif[idx]) _signif_err[idx] = 5*_signif[idx];
      }
      hist_res->SetBinContent(idx+1,_signif[idx]);
      hist_res->SetBinError(idx+1,  _signif_err[idx]);

      if( (rd_data->sumEntries(Form("BDT>%f", hist_res->GetBinCenter(idx+1) + hist_res->GetBinWidth(1)/2))<500) &&(sig_lim_bdt == 10 ) ){
	sig_lim_bdt = hist_res->GetBinCenter(idx+1) - hist_res->GetBinWidth(1)/2;
	std::cout << "\n\n\n\n\n FOUND BIN "<< sig_lim_bdt << "\n\n\n\n\n" ;
      }
      std::cout << "Efficiecy : " << ((double) tuple_pass_sig[idx] / ent_sig) << " sig_lim_bdt : " << sig_lim_bdt << std::endl;
    }
    TF1* sig_model;
//    if( formula_significance == "S12") sig_model = new TF1("Msignif", "[0]*(TMath::Sqrt([1]*TMath::Erf((-x-[2])/[4]) +TMath::Erf((-x-[3])/[5]) +[1]+1) - TMath::Sqrt(TMath::Erf((-x-[3])/[5]) +1 ) +[6]  )");
//    if( formula_significance == "S2") sig_model = new TF1("Msignif", "[0]*([1]*(TMath::Erf((-x-[2])/[4])+[6])/TMath::Sqrt([1]*(TMath::Erf((-x-[2])/[4]) +[7]) +TMath::Erf((-x-[3])/[5]) +1) )");
      sig_model = new TF1("Msignif","pol6",-0.5,interval_score*(zero_bin)-0.5);
    
    hist_res->Fit("Msignif","R","",-0.5,interval_score*(zero_bin)-0.5);
    hist_res->Draw();
    auto res = hist_res->GetFunction("Msignif");
    double max_signif_bdt= res->GetMaximumX(-0.5, 0.5);//  hist_res->GetBinCenter(hist_res->GetMaximumBin() );
    max_signif_bdt = min(max_signif_bdt, sig_lim_bdt);
    double max_signif_val = hist_res->GetMaximum();
    return std::make_pair(std::make_pair(max_signif_bdt, max_signif_val),hist_res );
  };

  
  auto bdt_res =  get_BDTcut_from_ratio(ratio);
  TH1D* hist_res = bdt_res.second;
  file_input->Close();

  TDirectory* dir_ratio;

  if(the_opt.find("SYS") != std::string::npos){
  dir_ratio = HISTFILE->mkdir(Form("r_%.6f%s", ratio,the_opt.c_str()), "");
  }
  else {
    dir_ratio = HISTFILE->mkdir(Form("r_%.6f", ratio), "");
  }
  HISTFILE->cd();
  dir_ratio->cd();
  hist_res->Write();
  TNamed* max_value = new TNamed("max_sig",Form("%.4f",bdt_res.first.first));
  max_value->Write();

  if(the_opt.find("SYS") == std::string::npos){
    HISTFILE->cd();
    TNamed* latest = new TNamed("latest", max_value->GetTitle() );
    latest->Write(0,TTree::kOverwrite);
  }
  HISTFILE->Close();
  cache_out->Close();

  Get_Optimal_BDT_HIST = hist_res;

  //TF1 *f1 = new TF1("poly3", "[0]*x^3+[1]*x^2+[2]*x+[3]",-0.3, 0.4);

  hist_res->Draw();
  return std::make_pair(bdt_res.first.first, hist_res);
};

//Function to get BDT ratio //
RooRealVar get_eff_acc(std::string type, std::string type2, long ts, double ylim, int pl, int ph, int cl, int ch, double blow, double bhigh, int train_state = 3, int state1 =1, int state2 =3, bool eff_old = true){

  RooRealVar eff22, eff21, eff1, eff2, nbkg;

  binplotter bp = binplotter(type, ts, ylim,pl, ph, cl, ch, blow, bhigh, train_state, false, eff_old);
  binplotter bp2 = binplotter(type2, ts, ylim,pl, ph, cl, ch, -1, bhigh, train_state, false, eff_old);
  bp.get_yield();
  nbkg = bp2.get_bkg();
  auto frac_pair = bp.get_frac();
  RooRealVar frac_nS;
  if(state2 ==2 ){ frac_nS = frac_pair.first;}
  if(state2 ==3 ){ frac_nS = frac_pair.second;}
  RooRealVar yield1S = bp2.get_yield(state1);
  auto effp1 = bp.get_eff(state1);
  auto effp2 = bp.get_eff(state2);
  auto eff2p1 = bp2.get_eff(state1);
  auto eff2p2 = bp2.get_eff(state2);
  eff2= RooRealVar(Form("eff%d",state2), "", effp2.first);
  eff2.setError(effp2.second);
  eff1= RooRealVar(Form("eff%d",state1), "", effp1.first);
  eff1.setError(effp1.second);
  eff22= RooRealVar(Form("eff%d",state2), "", eff2p2.first);
  eff22.setError(eff2p2.second);
  eff21= RooRealVar(Form("eff%d",state1), "", eff2p1.first);
  eff21.setError(eff2p1.second);

  double ratio_acceff = ((eff1.getVal()*eff22.getVal())/(eff2.getVal()*eff21.getVal()));
  double ratio_val = (frac_nS.getVal() * yield1S.getVal())/nbkg.getVal();
  double ratio_err = ratio_val * TMath::Sqrt( TMath::Power( frac_nS.getError()/ frac_nS.getVal(),2) + TMath::Power( yield1S.getError()/ yield1S.getVal(),2) + TMath::Power( nbkg.getError()/ nbkg.getVal(), 2) );
  std::cout << "YIELD: " << nbkg.getVal() << ", "<< yield1S.getVal()*frac_nS.getVal() << std::endl;
  std::cout << "EFF: " << eff1.getVal() << ", "<< eff2.getVal() << std::endl;
  std::cout << "ACC: " << eff22.getVal() << ", "<< eff21.getVal() << std::endl;
  std::cout << "RESULT: " <<ratio_acceff << ", "<< ratio_val << std::endl;

  RooRealVar res_var = RooRealVar("result","",ratio_acceff*ratio_val);
  res_var.setError(ratio_err);// res_var.getVal()*TMath::Sqrt( TMath::Power(eff22.getError()/eff22.getVal(),2) + TMath::Power(eff21.getError()/eff21.getVal(),2) + TMath::Power(eff1.getError()/eff1.getVal(),2) + TMath::Power(eff2.getError()/eff2.getVal(),2) + TMath::Power(nbkg.getError()/nbkg.getVal(),2) + TMath::Power(yield3S.getError()/yield3S.getVal(),2) ) ); 
  return res_var;
  
};
