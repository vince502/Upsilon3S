#pragma once
#include <stdarg.h>

//#include "./BDT/yield_eff_signif.cxx"
#include "./BDT/bininfo.h"

size_t getarrlen(string _args[] ={}){
	size_t x;
	for( auto item : *_args) x++;
	return x;
}

string getnobdtyield(int pl, int ph, int cl, int ch, int mcidx)
{
	string thestring="";
	if(mcidx ==0)
	{
		thestring = Form("Yield_3S_9999999999_FF_CB3_CC4_pt_%d-%d_rap_-24-24_cbin_%d-%d_MupT3p5_Trig_S13_SW0_BDT1_cut-1.0000-1.0000_vp0.0000.root", pl, ph, cl,ch );
		return thestring;
	}
	else
	{
		thestring = Form("Yield_9999999999_CB3_%dS_train%dS_pt_%d-%d_rap_-24-24_cBin_%d-%d_MupT3p5_S13_BDT_-1.0000-1.0000_vp_0.0000_MC_0.root", mcidx, mcidx, pl,ph,cl,ch );
		return thestring;
	}
};
string getnobdtyield(ana_bins ab, bool isMC)
{
	if(isMC) return getnobdtyield(ab.pl, ab.ph, ab.cl, ab.ch, ab.state);
	else return getnobdtyield(ab.pl, ab.ph, ab.cl, ab.ch, 0);
}

bool checkFile(string fname)
{
	TFile* thefile = TFile::Open(fname.c_str());
	if(!thefile) return false;
	else return true;
};
#if defined __CLING__

std::vector<string> _getfileany(string dir_target, string condition){
	TSystemDirectory wkdir("./", dir_target.c_str() );
	TList* _gf_flist = (TList*) wkdir.GetListOfFiles();
	std::vector<string> res;
	for( auto _gf_file : *_gf_flist ){
		string _gf_fname = _gf_file->GetName();
		if( _gf_fname.find(condition) != std::string::npos){
			res.push_back(_gf_fname);
		}
	}
	return res;
};
std::vector<string> getyieldfileany(string condition){
	return _getfileany(Form("%s/Yield", workdir.Data() ), condition );
};
std::vector<string> skim_search( std::vector<string> tar, std::string condition, bool rej = false){
	std::vector<string> v_swp;
	for( auto item : tar) {
		if (!rej){
			if(item.find(condition) != std::string::npos){
				v_swp.push_back(item);
			}
		}
		if (rej){
			if(item.find(condition) == std::string::npos){
				v_swp.push_back(item);
			}
		}
	}
	return v_swp;
};

std::vector<string> getfileany(string dir_target, string argset, string notinclude = ""){
	std::cout << "hi" << std::endl;
	auto filelist = _getfileany(dir_target, "");
	auto findlist = parser_symbol(argset,":");
	auto rejlist = parser_symbol(notinclude,":");
	for( auto item : findlist){
		std::cout << item << std::endl;
		filelist = skim_search(filelist, (string) item);
	}
	if(notinclude != ""){
		for( auto item : rejlist){
			std::cout << item << std::endl;
			filelist = skim_search(filelist, (string) item, true);
		}
	}
	return filelist;
};
#endif
