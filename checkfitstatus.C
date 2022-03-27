#include "fitreslib.h"
#include "./BDT/bininfo.h"

//void checkfitstatus(long ts = 100019111111){
//	for( auto abv : ana_bm_comb ){
//		for(auto ab : abv.second){
//			if(ab.bintype == kCent) continue;
//			double bl = Get_BDT(ts_alias(ts) , ab);
//
//			auto name_f_res = GetFit(__FITRESLATEST, true, "CB3", ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1., ab.bpl, ab.bph, 0.0, "");
//			auto f_res = TFile::Open(name_f_res.c_str() );
//			if( !f_res ){ 
//				continue;
//			}
//			system(Form("cp %s ./Yield/bkup_tmp/", name_f_res.c_str()));
//		}
//	}
//}

//void checkfitstatus(long ts = 100019111111){
//	string report;
//	for( auto abv : ana_bm_comb ){
//		for(auto ab : abv.second){
//			if(ab.bintype == kCent) continue;
//			double bl = Get_BDT(ts_alias(ts), ab);
//
//			auto name_f_res = GetFit(__FITRESLATEST, true, "CB3", ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1., ab.bpl, ab.bph, 0.0, "");
//			auto f_res = TFile::Open(name_f_res.c_str() );
//			if( !f_res ){ 
////				std::cout << Form("[Check MC Status] status NULL for bin %d pT %d - %d, cent %d - %d",  ab.state, ab.pl, ab.ph, ab.centl, ab.centh) << std::endl;
//				report += Form("[Check MC Status] status %d for bin %d pT %d - %d, cent %d - %d\n", -1, ab.state, ab.pl, ab.ph, ab.centl, ab.centh);
//				report += Form("BDT Score : %.4f\n", bl);
//				continue;
//			}
//			auto fit_res = (RooFitResult*) f_res->Get("fitresult_model_reducedDS");
//			auto Nstatus = fit_res->status();
////			std::cout << Form("[Check MC Status] status %d for bin %d pT %d - %d, cent %d - %d", Nstatus, ab.state, ab.pl, ab.ph, ab.centl, ab.centh) << std::endl;
//			report += Form("[Check MC Status] status %d for bin %d pT %d - %d, cent %d - %d\n", Nstatus, ab.state, ab.pl, ab.ph, ab.centl, ab.centh);
//			report += Form("BDT Score : %.4f\n", bl);
//		}
//	}
//	std::cout << report << std::endl;
//}


void checkfitstatus(long ts = 200019111111){
	string report;
	for( auto abv : ana_bm_comb ){
		for(auto ab : abv.second){
			double bl = Get_BDT(ts_alias(ts), ab);
			if( ab.bintype != kCent){
				for( auto type : (std::vector<string>) {"CC1", "CC2", "CC3", "CC4", "CC5", "CC6", "EE"} ){
					auto name_f_res = GetFit(__FITRESLATEST, false, Form("CB3:%s:GC",type.c_str()), ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1., ab.bpl, ab.bph, 0.0, "");
					std::cout << name_f_res << std::endl;
					auto f_res = TFile::Open(name_f_res.c_str() );
					if( !f_res  || f_res->IsZombie()){ 
						report += Form("[Check Data Status] status NULL for bin %d pT %d - %d, cent %d - %d\n",  ab.state, ab.pl, ab.ph, ab.centl, ab.centh);
						continue;
					}
					auto fit_res = (RooFitResult*) f_res->Get("fitresult_model_gc_reducedDS");
					auto Nstatus = fit_res->status();
					report += Form("[Check Data Status] status %d for bin %d pT %d - %d, cent %d - %d bkg %s\n", Nstatus, ab.state, ab.pl, ab.ph, ab.centl, ab.centh, type.c_str()) ;
				}
			}
			if( ab.bintype == kCent){
				continue;
				for( auto type : (std::vector<string>) {"CC1", "CC2", "CC3", "CC4", "CC5", "CC6", "EE"} ){
					auto name_f_res = GetFit(__FITRESLATEST, false, Form("CB3:%s:FF",type.c_str()), ts, ab.train_state, ab.state, ab.pl, ab.ph, ab.cl, ab.ch, bl, 1., ab.bpl, ab.bph, 0.0, "");
					auto f_res = TFile::Open(name_f_res.c_str() );
					if( !f_res || f_res->IsZombie() ){ 
						report+= Form("[Check Data Status] status NULL for bin %d pT %d - %d, cent %d - %d\n",  ab.state, ab.pl, ab.ph, ab.centl, ab.centh);
						continue;
					}
					auto fit_res = (RooFitResult*) f_res->Get("fitresult_model_reducedDS");
					auto Nstatus = fit_res->status();
					report += Form("[Check Data Status] status %d for bin %d pT %d - %d, cent %d - %d bkg %s\n", Nstatus, ab.state, ab.pl, ab.ph, ab.centl, ab.centh, type.c_str());
				}
			}
		}
	}
	std::cout << report << std::endl;
}
