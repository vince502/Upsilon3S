#ifndef FITTER_H
#define FITTER_H

#include <TFile.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TPaveText.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TParameter.h>
#include <TSystem.h>
#include <RooRealVar.h>
#include <RooArgSet.h>
#include <RooDataSet.h>
#include <RooWorkspace.h>
#include <RooPlot.h>
#include <RooHist.h>
#include <RooGaussian.h>
#include <RooCBShape.h>
#include <RooChebychev.h>
#include <RooPolynomial.h>
#include <RooExponential.h>
#include <RooGenericPdf.h>
#include <RooAddPdf.h>
#include <RooFitResult.h>
#include <RooFormulaVar.h>
#include "Headers/Style_Upv2.h"
#include "Headers/Upsilon.h"
#include ".workdir.h"
#include "./BDT/bininfo.h"
#include "fit_model.h"

class massfitter
{
	  public :
	  	massfitter();
		massfitter(std::string file_input, std::string file_output);
		~massfitter();
		void ws_init(std::string name_ds, std::vector<std::string> list_arg, std::string fitvar = "mass");

		RooDataSet* dataset,* iDS,* fDS;
		RooWorkspace* works;
		RooArgSet* vArg;
		std::string dsCut= "";
		std::string TFit_sig, TFit_bkg;
		std::string name_ds;
		std::vector<std::string> list_arg;
		double Range_fit_low, Range_fit_high;

		TFile* fin, * fout;
	private :
		std::string _file_input, _file_output;
};

massfitter::massfitter(){
};
massfitter::~massfitter(){
};

massfitter::massfitter(std::string file_input, std::string file_output){
	_file_input = file_input;
	_file_output = file_output;
	fin = new TFile(file_input.c_str(), "READ");
	fout = new TFile(file_output.c_str(), "recreate");
};

void massfitter::ws_init(std::string name_ds, std::vector<std::string> list_arg, std::string fitvar = "mass"){
  	if(list_arg.begin()==list_arg.end()) throw "No workspace elements?";
	dataset = (RooDataSet*) fin->Get(name_ds.c_str());
	std::cout << fin->GetTitle() << std::endl;
	works = new RooWorkspace("workspace");
	works->import(*dataset);
	vArg = new RooArgSet();
	for(auto arg : list_arg){
		vArg->add(*(works->var( arg.c_str() ) ));
	}
	iDS = (RooDataSet*) dataset->reduce(*vArg);
	fDS =  (RooDataSet*) iDS->reduce(RooArgSet(*(works->var(fitvar.c_str())), dsCut.c_str()));
	fDS->SetName("reducedDS");
	works->import(*fDS);
	works->var(fitvar.c_str())->setRange(Range_fit_low, Range_fit_high);
	works->var(fitvar.c_str())->Print();
};

double single_LepPtCut(TString pTstr)
{
  double LepPtCut;
  if(pTstr == "0") LepPtCut = 0;
  else if(pTstr == "0p5") LepPtCut = 0.5;
  else if(pTstr == "1") LepPtCut = 1.0;
  else if(pTstr == "1p5") LepPtCut = 1.5;
  else if(pTstr == "2") LepPtCut = 2.0;
  else if(pTstr == "2p5") LepPtCut = 2.5;
  else if(pTstr == "3") LepPtCut = 3.0;
  else if(pTstr == "3p5") LepPtCut = 3.5;
  else if(pTstr == "4") LepPtCut = 4.0;
  else
  {
          cout << "There is no such muon pT cut value" << endl;
          return -1 ;
 }
 return LepPtCut;
};
void dbg(int x=0){
    std::string indx = (x==0) ? "" : Form("%d",x);
      std::cout << "-------------------------_____DEBUG"<<indx<<"_____----------------------------" << std::endl;
};

#endif
