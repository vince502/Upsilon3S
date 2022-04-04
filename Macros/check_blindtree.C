#include "../.workdir.h"

void check_blindtree(){
	TFile* f_1 =  TFile::Open(Form("%s/%s", store.Data(), ONIABDTDATAB_LATEST.c_str()));
	TFile* f_2 = TFile::Open(Form("%s/testBlind_Quat_v2_2.root", store.Data()));

	TFile* f_1_hi =  TFile::Open(Form("%s/OutputSkim_isMC0_m814_v211025_ForBLIND.root", store.Data()));
	TFile* f_1_lo =  TFile::Open(Form("%s/OutputSkim_isMC0_v211025_m68_ForBLIND.root", store.Data()));
	TTree* t1_1 = (TTree*) f_1->Get("tree2");
	TTree* t1_2 = (TTree*) f_1->Get("tree3");
	TTree* t2_1 = (TTree*) f_2->Get("tree2");
	TTree* t2_2 = (TTree*) f_2->Get("tree3");

	TTree* t1_1_lo = (TTree*) f_1_lo->Get("tree2");
	TTree* t1_2_lo = (TTree*) f_1_lo->Get("tree3");
	TTree* t1_1_hi = (TTree*) f_1_hi->Get("tree2");
	TTree* t1_2_hi = (TTree*) f_1_hi->Get("tree3");

	int ent1_1, ent2_1;
	int ent1_2, ent2_2;

	int ent1_1_lo, ent1_2_lo;
	int ent1_1_hi, ent1_2_hi;
	ent1_1 = t1_1->GetEntries();
	ent1_2 = t1_2->GetEntries();
	ent2_1 = t2_1->GetEntries();
	ent2_2 = t2_2->GetEntries();

	ent1_1_lo = t1_1_lo->GetEntries();
	ent1_2_lo = t1_2_lo->GetEntries();
	ent1_1_hi = t1_1_lo->GetEntries();
	ent1_2_hi = t1_2_lo->GetEntries();

	std::cout << ent1_1_lo << std::endl;
	std::cout << ent1_1_hi << std::endl;

	std::cout << ent1_2_lo << std::endl;
	std::cout << ent1_2_hi << std::endl;


	std::cout << ent1_1 << std::endl;
	std::cout << ent1_2 << std::endl;

	std::cout << t1_1->GetEntries("mass<8")<< std::endl;
	std::cout << t1_2->GetEntries("mass<8")<< std::endl;

	double mass1_1_lo;
	double mass1_1_hi;
	double mass1_1;
	t1_1_lo->SetBranchAddress("mass", &mass1_1_lo);
	t1_1_hi->SetBranchAddress("mass", &mass1_1_hi);
	t1_1->SetBranchAddress("mass", &mass1_1);
	for( auto idx : ROOT::TSeqI(ent1_1_lo)){
		t1_1_hi->GetEntry(idx);
		t1_1   ->GetEntry(idx + ent1_1_lo);
		std::cout << "MASS : t1 " << mass1_1 << ", t1_lo " << mass1_1_hi << std::endl;
		
	}



//	double mass1, mass2;




}
