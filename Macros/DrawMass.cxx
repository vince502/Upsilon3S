#include "../.workdir.h"
#include "../CMS_lumi_square.C"
#include "../tdrstyle.C"
#include "TROOT.h"
#include <iostream>
#include "RooFit.h"
#include "../fitter.h"

void DrawMass(long ts=0, double pl = 0, double ph =30, int clow = 0, int chigh = 181 ){
  std::string type 			= "CB3:CC2:GC"	;
  ts					=  1625139244;// 1625558168; // Past nominal 1623391157; //71622626134;//	1621574976;//	//	1622517421;
  long ts_2				= 1625558633; //1625503068	;
  double rapMin				= -2.4		;
  double rapMax				= 2.4		;
  TString MupT				= "3p5"		;
  std::string Trig			= "S13"		;
  int state				= 3		;
  bool fixvar				= false		;
  bool swflag				= false		;
  double cutQVP				= 0.00		;
  bool isBDT 				= true		;

  auto getPlot = [&] (std::string _type, double _pl, double _ph, int _clow, int _chigh, double _bcut)  {
    auto parsed = parser_symbol(type);
    std::string sig_func = parsed[0];
    std::string bkg_func = parsed[1];
    std::string fitdir = parsed[2];
    std::string name_fitmodel = "_"+bkg_func;

    //Get Yield File
    std::string input_yield_fname  = Form("%s/Yield/Yield_%ld_%s%s_pt_%d-%d_rap_-%d-%d_%dbin_cbin_%d-%d_MupT%s_Trig_%s_SW%d_BDT%d_cut%.4f-%.4f_vp%.4f.root" ,workdir.Data(), ts, fitdir.c_str(), name_fitmodel.c_str(), (int) pl, (int) ph, (int) (rapMax*(10.)), (int) (rapMax*(10.)), 70, clow, chigh, MupT.Data(), Trig.c_str(), (int) swflag, (int) isBDT, _bcut, 1.0000, cutQVP );
    TFile* file_yield = TFile::Open(Form("%s", input_yield_fname.c_str()) );
    std::cout << file_yield->GetName() << std::endl;
    //Get Workspace
    RooWorkspace* wss = (RooWorkspace*) file_yield->Get("workspace");
    //Get Dataset
    RooDataSet* rds = (RooDataSet*) wss->data("reducedDS");
    //Initialize RooPlot
    RooPlot* plot_m = wss->var("mass")->frame(70);
    //Draw raw mass on RooPlot
    rds->plotOn(plot_m);
    //Configure
    //
    return plot_m;
  };
 
  setTDRStyle();
  TCanvas* c1 = new TCanvas("c1","",1000,800);
  c1->cd();
  TLegend* leg = new TLegend(0.7, 0.6, 0.85, 0.85);

  std::vector<double> bin_bdt 	= {-1.0, -0.2, -0.1, 0.0859, 0.2};
  std::vector<Color_t> bin_color = {kBlack, kBlue, kMagenta, kRed, kGreen};

  for( int idx = 0; idx < bin_bdt.size(); idx++){
    double bdt = bin_bdt[idx];
    Color_t lcolor = bin_color[idx];
    if( idx ==0){
      std::cout << "doing -1 " << std::endl;
      auto res = getPlot("CB3:EE:GC", pl, ph, clow, chigh, bdt);
      res->getAttLine()->SetLineColor(lcolor);
      res->getAttMarker()->SetMarkerColor(lcolor);
      leg->AddEntry(res, Form("Mass Dist of BDT [%.1f, 1.0]", bdt) );
      res->Draw();
    }
    else{
      auto res = getPlot(type, pl, ph, clow, chigh, bdt);
      res->getAttLine()->SetLineColor(lcolor);
      res->getAttMarker()->SetMarkerColor(lcolor);
      leg->AddEntry(res, Form("Mass Dist of BDT [%.1f, 1.0]", bdt) );
      res->Draw("same");
    }

  }
  leg->Draw("same");
  c1->SaveAs("massbyBin.C");
}
