#include "../BDT/bininfo.h"

std::pair<string, string> get_histnames(ana_bins x){
	long ts = _TS;
	double bl = Get_BDT(ts_alias(ts), x);
	double ml, mh;
	if( x.state == 2){ml = 9.3; mh = 10.7;}
	if( x.state == 3){ml = 9.6; mh = 11.0;}
//	std::string histNameNOM = Form("BDT_%dS_train%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_fix", x.state, x.state, 9999999999, bl, 1., (double) x.pl, (double) x.ph, -2.4, 2.4, 3.5, ml, mh, x.cl, x.ch, 0., true, true);
//	std::string histNameNOM = GetEffDen(__FITRESLATEST, x.state, ml, mh);
	std::string histNameNOM = GetEffNum(__FITRESLATEST, ts_alias(ts), x.train_state, x.state, x.bpl, x.bph, -2.4, 2.4, 3.5, ml, mh, x.cl, x.ch, 0.00, true, true);
	//std::string histNameSYS = Form("BDT_%dS_train%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_SYSTNP", x.state, x.train_state, 10000000016, bl, 1., (double) x.pl, (double) x.ph, -2.4, 2.4, 3.5, ml, mh, x.cl, x.ch, 0., true, true); //previous version
	std::string histNameSYS = Form("BDT_%dS_train%dS_%ld_bdt_%.4f-%.4f_pt%.1f_%.1f_y%.1f_%.1f_SiMuPt%.1f_mass%.1f_%.1f_cent%d_%d_vp_%.4f_isTnP%d_isPtWeight%d_ID_SYSTNP", x.state, x.train_state, 100019111111, bl, 1., (double) x.pl, (double) x.ph, -2.4, 2.4, 3.5, ml, mh, x.cl, x.ch, 0., true, true);
	return (std::pair<string, string>){histNameNOM, histNameSYS};
};

void TNPUnc(){
	long ts = _TS;
	 
	TFile* output = new TFile(Form("./data/effTNP_unc_%ld.root",ts_alias(ts)),"recreate");
	TH1D *rc2s, *rc3s, *rp2s, *rp3s;
	rc2s = new TH1D("rc2S","",10,0,9); //include int. bin
	rc3s = new TH1D("rc3S","",4,0,3);  //include int. bin
	rp2s = new TH1D("rp2S","",3,1,3);
	rp3s = new TH1D("rp3S","",2,1,2);

	std::vector<ana_bins> vc2, vc3, vp2, vp3;
	vc2 = ana_bm["2c"];
	vc3 = ana_bm["3c"];
	vp2 = ana_bm["2p"];
	vp3 = ana_bm["3p"];
	std::vector< std::pair< TH1D*, std::vector<ana_bins> > > abh = {{rc2s ,vc2}, {rc3s, vc3}, {rp2s, vp2}, {rp3s, vp3} };

	auto get_input_config = [&] (int cvr, int mod)
	{
		TString _input_config, _idstr, _trkstr, _trgstr;
		if( cvr == 1 ){ _trkstr = "Nom"; _trgstr = "Nom"; _idstr = Form("%s",mode_str[mod-1].c_str()); }
		if( cvr == 2 ){ _idstr = "Nom"; _trgstr = "Nom"; _trkstr = Form("%s",mode_str[mod-1].c_str()); }
		if( cvr == 3 ){ _idstr = "Nom"; _trkstr = "Nom"; _trgstr = Form("%s",mode_str[mod-1].c_str()); }
		_input_config = Form("id%s_trk%s_trg%s",_idstr.Data(), _trkstr.Data(), _trgstr.Data()); 
		return _input_config;
	};


	for( auto abv : abh ){
		int counter = 1;
		for( ana_bins ab : abv.second){
			auto name_pair = get_histnames(ab);
		  	TFile *f_hreco_ref, *f_hreco;
			f_hreco_ref = TFile::Open(Form("%s", name_pair.first.c_str() ) );
			std::cout << name_pair.first.c_str() << std::endl;
			std::cout << name_pair.second.c_str() << std::endl;

			f_hreco = TFile::Open(Form("%s/BDT/EffCalc/TNP/mc_eff_%s.root", workdir.Data(), name_pair.second.c_str() ) );

			TH3D* hreco_ref;
			std::map<TString, TH1D*> map_hreco_tnp;
			hreco_ref = (TH3D*) f_hreco_ref->Get("hreco");
			double bdtlow = Get_BDT(ts_alias(ts), ab);	
			std::cout << Form("Bin : %d - %d, %d - %d, %d - %d",(int) ( (bdtlow + 1.0000) * 10000), 20000, ab.pl, ab.ph, (ab.cl/5) +1, (ab.ch/5) ) << std::endl;
			double COUNT_REF = hreco_ref->Integral((int) ((bdtlow + 1.0000) * 10000), 20000, ab.pl + 1 , ab.ph, (ab.cl/5) +1 , (ab.ch/5) );
			double ERR_CVAR[3] = {0,0,0};
			for( int cv : {1,2,3}){
			  	double COUNT_TAG, COUNT_STAT, COUNT_SYS;
				for( int md : {1,2,3,4,5}){
					TString the_string = get_input_config(cv, md);
					TH1D* clone_hreco = (TH1D*) ((TH1D*) f_hreco->Get(Form("hreco_%s",the_string.Data())))->Clone();	
					clone_hreco->SetDirectory(0);

					map_hreco_tnp[the_string] = clone_hreco;

					if(md == 1) COUNT_TAG = map_hreco_tnp[the_string]->GetSum();
				}
				std::vector<std::pair<int,int> > udp = {{2,3}, {4,5}};
				for( auto mdp : udp){
					double COUNT_UP, COUNT_DOWN;
					TString cfg_up, cfg_down;
					cfg_up = get_input_config(cv, mdp.first);
					cfg_down = get_input_config(cv, mdp.second);
					COUNT_UP = map_hreco_tnp[cfg_up]->GetSum();
					COUNT_DOWN = map_hreco_tnp[cfg_down]->GetSum();
					double _this = ( (fabs(COUNT_UP - COUNT_REF) - fabs(COUNT_DOWN - COUNT_REF)) >0) ? COUNT_UP : COUNT_DOWN;
					if( mdp.first == 2) COUNT_STAT = _this;
					if( mdp.first == 4) COUNT_SYS = _this;
				}
				std::cout <<"COUNT_REF " << COUNT_REF <<  ", COUNT_TAG " << COUNT_TAG - COUNT_REF << ", COUNT_STAT " << COUNT_STAT - COUNT_REF << ", COUNT_SYS " << COUNT_SYS - COUNT_REF << std::endl;
				ERR_CVAR[cv-1] = TMath::Sqrt( TMath::Power(COUNT_TAG -COUNT_REF, 2) + TMath::Power(COUNT_STAT- COUNT_REF, 2) + TMath::Power(COUNT_SYS - COUNT_REF, 2) );
				std::cout << "ER_CVAR[cv-1] " << ERR_CVAR[cv-1] << std::endl;
			}
			f_hreco->Close();
			f_hreco_ref->Close();
			double COUNT_TNP = TMath::Sqrt( TMath::Power(ERR_CVAR[0], 2) + TMath::Power(ERR_CVAR[1], 2) + TMath::Power(ERR_CVAR[2], 2) ); 
			
//			std::cout << Form("Efficiency for ref, TNP : %.5f, %.5f", COUNT_REF, COUNT_TNP ) << std::endl;
			
			double tnpUnc = (COUNT_TNP )/ COUNT_REF;
			abv.first->SetBinContent(counter, tnpUnc);
			counter +=1;
		}

	}
	output->cd();
	rc2s->Write();
	rc3s->Write();
	rp2s->Write();
	rp3s->Write();
	output->Close();
}

