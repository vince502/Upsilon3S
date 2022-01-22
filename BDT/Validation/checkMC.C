#include "../../.workdir.h"
#define MHIST std::map<string, TH1D*>

std::pair<MHIST, MHIST> checkMC(){
	TFile* m2 = TFile::Open((store +"/"+ONIABDTMC_LATEST).Data());
	TFile* m3 = TFile::Open((store +"/"+ONIABDTMC2S_LATEST).Data());

	TTree* t2 = (TTree*) m2->Get("tree");
	TTree* t3 = (TTree*) m3->Get("tree");
	MHIST var2s;
	MHIST var3s;
	
	var2s = {
		{"QQMassErr",	new TH1D("h2s_qqme",		"",100,0,0.5)},
		{"QQVtxProb",	new TH1D("h2s_qqvp",		"",1000,0,1)},
		{"QQdca",		new TH1D("h2s_qqdca",		"",1000,0,10)},
		{"cosAlpha",	new TH1D("h2s_cos",			"",200,-1,1)},
		{"cosAlpha3D",	new TH1D("h2s_cos3D",		"",200,-1,1)},
		{"ctau",		new TH1D("h2s_ctau",		"",2000,-0.3,0.3)},
		{"ctau3D",		new TH1D("h2s_ctau3D",		"",2000,-0.3,0.3)},

	};
	var3s = {
		{"QQMassErr",	new TH1D("h3s_qqme",		"",100,0,0.5)},
		{"QQVtxProb",	new TH1D("h3s_qqvp",		"",1000,0,1)},
		{"QQdca",		new TH1D("h3s_qqdca",		"",1000,0,10)},
		{"cosAlpha",	new TH1D("h3s_cos",			"",200,-1,1)},
		{"cosAlpha3D",	new TH1D("h3s_cos3D",		"",200,-1,1)},
		{"ctau",		new TH1D("h3s_ctau",		"",2000,-0.3,0.3)},
		{"ctau3D",		new TH1D("h3s_ctau3D",		"",2000,-0.3,0.3)},

	};

	double qm, qv, qd, ca, ca3, ct,ct3;
	t2->SetBranchAddress("QQMassErr", &qm);
	t2->SetBranchAddress("QQVtxProb", &qv );
	t2->SetBranchAddress("QQdca", &qd );
	t2->SetBranchAddress("cosAlpha", &ca );
	t2->SetBranchAddress("cosAlpha3D", &ca3 );
	t2->SetBranchAddress("ctau", &ct );
	t2->SetBranchAddress("ctau3D", &ct3 );
	t3->SetBranchAddress("QQMassErr", &qm);
	t3->SetBranchAddress("QQVtxProb", &qv );
	t3->SetBranchAddress("QQdca", &qd );
	t3->SetBranchAddress("cosAlpha", &ca );
	t3->SetBranchAddress("cosAlpha3D", &ca3 );
	t3->SetBranchAddress("ctau", &ct );
	t3->SetBranchAddress("ctau3D", &ct3 );

	int n2s = t2->GetEntries();
	int n3s = t3->GetEntries();
	for( int idx=0; idx < n2s; idx++){
		if((idx%10000)==0) std::cout << idx << std::endl;
		t2->GetEntry(idx);
		var2s["QQMassErr"]->Fill(qm);
		var2s["QQVtxProb"]->Fill(qv);
		var2s["QQdca"]->Fill(qd);
		var2s["cosAlpha"]->Fill(ca);
		var2s["cosAlpha3D"]->Fill(ca3);
		var2s["ctau"]->Fill(ct);
		var2s["ctau3D"]->Fill(ct3);
	}
	for( int idx=0; idx < n3s; idx++){
		if((idx%10000)==0) std::cout << idx << std::endl;
		t3->GetEntry(idx);
		var3s["QQMassErr"]->Fill(qm);
		var3s["QQVtxProb"]->Fill(qv);
		var3s["QQdca"]->Fill(qd);
		var3s["cosAlpha"]->Fill(ca);
		var3s["cosAlpha3D"]->Fill(ca3);
		var3s["ctau"]->Fill(ct);
		var3s["ctau3D"]->Fill(ct3);
	}

	return std::pair<MHIST, MHIST> {var2s, var3s};

//	TCanvas* c1 = new TCanvas("c1", "");
//	c1->Close();
}
