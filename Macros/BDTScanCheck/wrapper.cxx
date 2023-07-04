#include "wrapper.h"
#include "grapher.cxx"

//fits_wrapper::fits_wrapper(){};

fits_wrapper::~fits_wrapper(){};

fits_wrapper::fits_wrapper(long ts, ana_bins x, string type, std::vector<double> initRange = {}) {
	def_ts = ts; def_ab = x; def_type = type;
	setIntervalAny(initRange);
};

fits_wrapper::fits_wrapper(fits_wrapper_pset pset) : fits_wrapper(pset.ts, pset.ab, pset.type, pset.bins){
};

fits_wrapper::fits_wrapper( const fits_wrapper &other){
	return fits_wrapper::copy(other);
};

fits_wrapper fits_wrapper::copy(const fits_wrapper &original){
	fits_wrapper x = fits_wrapper();
	for( auto elements : original.datapoints ){
		x.datapoints[elements.first] = elements.second;
	}
	return x;
};

void fits_wrapper::merge(fits_wrapper &wr_to, const fits_wrapper &wr_from){
	for( auto elements : wr_from.datapoints ){
		wr_to.datapoints[elements.first] = elements.second;
	}
};

int fits_wrapper::setIntervalEqual(double from, double to, int numInterval, bool cleanUp = false){
	double step = (to - from ) / ( (double) numInterval);
	std::vector<double> _vInterval;
	for ( double idx = from ; idx < to ; idx += step ){
		_vInterval.push_back(idx);	
	}
	return setIntervalAny(_vInterval);
};

int fits_wrapper::setIntervalAny(std::vector<double> vInterval, bool cleanUp = false){
	for ( auto element : datapoints ){
		element.second.isRangeInc = false;
		if( cleanUp ){ element.second = fits_wrapper_content(); }
	}
	int count = 0;
	for ( auto idx : vInterval ){
		datapoints[idx].isRangeInc = true;
		count ++;
	}
	return count;
};

bool fits_wrapper::eval(double score, bool evalCorr = true){ 
	datapoints[score].isRangeInc = true;
	datapoints[score].type = def_type;
	datapoints[score].ts = def_ts;
	datapoints[score].ab = def_ab;
	if( datapoints[score].bp ){ std::cout << "Deleting existing binplotter\n"; delete datapoints[score].bp;}
	datapoints[score].bp = new binplotter(datapoints[score].ts, datapoints[score].ab, datapoints[score].type, score);
	datapoints[score].fitres = datapoints[score].bp->res;
	datapoints[score].isGoodFit = checkFit(datapoints[score].fitres);
	if(evalCorr && datapoints[score].isGoodFit)	datapoints[score].correction = datapoints[score].bp->get_eff(datapoints[score].ab.state, false).first;
	else datapoints[score].correction = 1;
//	datapoints[score].correction = ( corrtype == "none" ) ? 1 :  datapoints[score].bp->get_eff(datapoints[score].ab.state, (corrtype == "num") ? true : false).first;
	if ( datapoints[score].isGoodFit ){
		datapoints[score].yield = datapoints[score].bp->get_yield( datapoints[score].ab.state );
	}
	else{ std::cout << "Fit not well done, check to refit the data" << std::endl; delete datapoints[score].bp; return false;}
	delete datapoints[score].bp;
	return true;
};

int fits_wrapper::eval( std::vector<double> x = {}, bool evalCorr = true){
//	for( auto element : datapoints) {}
	int count = 0;
	if (x.empty() ){
		for ( auto pair_score : datapoints ){
			std::cout << "bdt : " << pair_score.first << std::endl;
			if( datapoints[pair_score.first].isRangeInc ) eval(pair_score.first, evalCorr);
			count ++;
		}
	}
	else{
		for ( auto score : x ){
			if( datapoints[score].isRangeInc ) eval(score);
			count ++;
		}
	}
	return count;
};


void fits_wrapper::setElementPrimitive(double score){
	datapoints[score].ts = def_ts;
	datapoints[score].ab = def_ab;
	datapoints[score].type = def_type;
	return;
}

std::pair<double, fits_wrapper_content> fits_wrapper::getContent( int idx ){
	if ( idx > datapoints.size() -1 ){ 
		std::cerr << "Index larger than datapoints \n"; 
		auto _null = fits_wrapper_content();
		return std::make_pair(-999., _null);
	}
	auto it = datapoints.begin();
	std::advance(it, idx);
	return *it;
}

std::pair<double, fits_wrapper_content> fits_wrapper::getContent( double score ){
	return std::make_pair(score, datapoints.at(score));
}

bool fits_wrapper::checkFit(double bcut){
	return this->checkFit( datapoints[bcut].fitres);
};

bool fits_wrapper::checkFit(int idx){
	double bcut = this->getContent(idx).first;
	return this->checkFit( datapoints[bcut].fitres);
};

bool fits_wrapper::checkFit(RooFitResult* res){
	if( res->status() !=0 ) return false;
	if( (fabs(res->edm() / res->minNll()) > 1e-3) || (res->edm() == 0) || (res->minNll() >=0) ) return false;  
	return true;
};

void fits_wrapper::printGlobalAttributes(){
	std::cout << Form("$def_ts : %ld, $def_ab : %d $def_type %s", def_ts, def_ab.state, def_type.c_str()) << std::endl;
}

bool fits_wrapper::checkInRange( double score ){
	return datapoints[score].isRangeInc;
};

void fits_wrapper::setCorrection(string type){
	corrtype = type;
};

