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
//#include "./BDT/bininfo.h"
#include "fit_model.h"

struct Y1Sfitvar{
  Double_t alp=0., frac=0., x1s=0., sigma=0., n=0.;
};

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
//	delete dataset;
//	delete iDS;
//	delete fDS;
//	if(fin) fin->Close();
//	if(fout) fout->Close();
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
	works = new RooWorkspace("workspace");
	works->import(*dataset);
	vArg = new RooArgSet();
	for(auto arg : list_arg){
		vArg->add(*(works->var( arg.c_str() ) ));
	}
	iDS = (RooDataSet*) dataset->reduce(*vArg);
	fDS =  (RooDataSet*) iDS->reduce(RooArgSet(*(works->var(fitvar.c_str()))), dsCut.c_str());
	fDS->SetName("reducedDS");
	works->import(*fDS);
	std::cout << Range_fit_low << ", " << Range_fit_high << std::endl;
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
std::vector<std::string> parser_symbol(std::string type,std::string delim = ":"){
  if(type.find(delim) == std::string::npos) return std::vector<std::string>{type.c_str()};
  std::vector<size_t> positions;
  size_t pos = type.find(delim,0);
  while(pos != std::string::npos){
    positions.push_back(pos);
    pos = type.find(delim, pos+1);
  }
  std::vector<std::string> result_parse;
  size_t front =0;
  for (size_t pos : positions){
    result_parse.push_back(type.substr(front,pos-front));
    front = pos +delim.length();
  }
  result_parse.push_back(type.substr(front));

  return result_parse;

};

//parser with output same as parser_symbol, with parsing string in characters between white spaces(use string::first_not_of), and return vector of string
std::vector<std::string> parser_symbol2(std::string type,std::string delim = ":"){
  std::vector<std::string> result_parse;
  while( type.find(" ") != std::string::npos ){
  size_t endword = type.find_first_of(" ");
  result_parse.push_back(type.substr(0,endword));
  type.erase(0, type.find_first_not_of(" ",endword));
  };
  result_parse.push_back(type);
  return result_parse;
};



#endif
