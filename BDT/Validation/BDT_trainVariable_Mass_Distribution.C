#include "../bininfo.h"

void BDT_trainVariable_Mass_Distribution(long ts,int state, int pl =0, int ph = 30 )
{
	TFile* f_data = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_%ld.root", workdir.Data(), ts));
	TFile* f_mc1s = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_%ld_MC_1S.root", workdir.Data(), ts));
	TFile* f_mc2s = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_%ld_MC_2S.root", workdir.Data(), ts));
	TFile* f_mc3s = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_%ld_MC.root", workdir.Data(), ts));
	
	TTree* t_data = (TTree*) f_data->Get("tree");
	TTree* t_mc1s = (TTree*) f_mc1s->Get("tree");
	TTree* t_mc2s = (TTree*) f_mc2s->Get("tree");
	TTree* t_mc3s = (TTree*) f_mc3s->Get("tree");

	auto GetVarHist = [&](TTree* t1, TTree* t2, string varandtype){
		string var = varandtype.substr(0,varandtype.length()-2);
		string vartype = varandtype.substr(varandtype.length()-1);
		int i_var_t1, i_var_t2;
		double bdt_t1, bdt_t2, d_var_t1, d_var_t2;
		t1->SetBranchAddress(Form("BDTY%dSpt0to30",state), &bdt_t1 );
		t2->SetBranchAddress(Form("BDTY%dSpt0to30",state), &bdt_t2 );
		if(strcmp(vartype.c_str(),"I")==0){
		t1->SetBranchAddress(var.c_str(), &i_var_t1 );
		t2->SetBranchAddress(var.c_str(), &i_var_t2 );
		}
		if(strcmp(vartype.c_str(),"D")==0){
		t1->SetBranchAddress(var.c_str(), &d_var_t1 );
		t2->SetBranchAddress(var.c_str(), &d_var_t2 );
		}
		int nE_t1, nE_t2;
		nE_t1 = t1->GetEntries();
		nE_t2 = t2->GetEntries();
		TH2D h1(Form("var_%s_t1",var.c_str()),"",40,-1,0.6, 1000,-1,1);
		TH2D h2(Form("var_%s_t2",var.c_str()),"",40,-1,0.6, 1000,-1,1);
		for(int idx=0; idx < nE_t1; idx++){
			t1->GetEntry(idx);
			if(strcmp(vartype.c_str(),"I")==0){
				h1.Fill(bdt_t1,i_var_t1 );
			}
			if(strcmp(vartype.c_str(),"D")==0){
				h1.Fill(bdt_t1,d_var_t1 );
			}
		}
		for(int idx=0; idx < nE_t2; idx++){
			t2->GetEntry(idx);
			if(strcmp(vartype.c_str(),"I")==0){
				h2.Fill(bdt_t2,i_var_t2 );
			}
			if(strcmp(vartype.c_str(),"D")==0){
				h2.Fill(bdt_t2,d_var_t2 );
			}

		}
		return std::pair<TH2D,TH2D>(h1,h2);	
	};
	std::vector<std::pair<TH2D,TH2D >> vhist;
	for(string thevar : {"ctau/D", "ctau3D/D", "QQVtxProb/D", "cosAlpha3D/D", "cosAlpha/D", "QQMassErr/D", "QQdca/D" }){
		vhist.push_back(GetVarHist(t_data, t_mc1s, thevar.c_str() ) );
		std::cout << "Filling "<< thevar.c_str() << std::endl;
	}
	TFile* f_out = new TFile(Form("VarPlots_%ld.root",ts), "update" );
	f_out->cd();
	TDirectoryFile* f_dir = new TDirectoryFile("dataMC1S","");
	f_dir->Write();
	f_dir->cd();
	for( auto hists : vhist){
		hists.first.Write();
		hists.second.Write();
	}
	f_out->Close();
}
