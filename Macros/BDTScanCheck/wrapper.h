#pragma once
#include "../../BDT/yield_eff_signif.cxx"

struct fits_wrapper_content{
	binplotter* bp; RooFitResult* fitres;  RooRealVar yield; long ts; ana_bins ab; string type; string corrtpye; double correction; bool isGoodFit; bool isRangeInc = false;
};
struct fits_wrapper_reduced{
	RooRealVar yield; double correction; bool isGoodFit; bool isRangeInc;
};

struct fits_wrapper_pset{
	long ts; ana_bins ab; string type; std::vector<double> bins;
};

ClassImp(fits_wrapper);

class fits_wrapper{
	public :
		fits_wrapper(){};
		~fits_wrapper();
		fits_wrapper(long ts, ana_bins x, string type, std::vector<double> initRange = {});
		fits_wrapper(fits_wrapper_pset pset);
		fits_wrapper(const fits_wrapper &other);
		fits_wrapper copy(const fits_wrapper &original);
		void merge(fits_wrapper &wr_to, const fits_wrapper &wr_from);
		int setIntervalEqual(double from, double to, int numInterval, bool cleanUp = false);
		int setIntervalAny(std::vector<double> vInterval, bool cleanUp = false);
		bool eval(double score, bool evalCorr = true);
		int eval(std::vector<double> x = {}, bool evalCorr = true);
		TGraphAsymmErrors* createGraph( string correction  = "none");
		std::pair<double, fits_wrapper_content> getContent( int idx );
		std::pair<double, fits_wrapper_content> getContent( double score );

		bool checkFit(double bcut);
		bool checkFit(int idx);
		void printGlobalAttributes();

	protected :
		void setCorrection(string type);
		void setElementPrimitive(double score);
		bool comp(std::pair<double, fits_wrapper_content> a, std::pair<double, fits_wrapper_content> b){ return a.first < b.first; }
		bool checkFit(RooFitResult* res);
		bool checkInRange( double score );
		string corrtype = "none";

	private :
		std::map< double, fits_wrapper_content > datapoints;
		long def_ts;
		ana_bins def_ab;
		string def_type;		
};
//binplotter(long _ts, ana_bins _x, string _type, double _bcut){
