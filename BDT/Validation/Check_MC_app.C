#include "../bininfo.h"

Check_MC_app(){
	long ts =1635139612;
	TFile* f1, f2;
	f1 = TFile::Open(Form("%s/BDT/BDTAppliedData/BDTApp_%ld_MC.root", workdir.Data(), ts) );
	f2 = TFile::Open(Form("%s/BDT/BDResult/BDTresultY3S_%ld_BLIND.root", workdir.Data(), ts);

	TTree* t1 = (TTree*) f1->Get("tree");

	TTree* t2_1tr = (TTree*) f2->Get("data/Y3Spt0to30/dataset1/TrainTree");
	TTree* t2_1te = (TTree*) f2->Get("data/Y3Spt0to30/dataset1/TestTree");
	TTree* t2_2tr = (TTree*) f2->Get("data/Y3Spt0to30/dataset2/TrainTree");
	TTree* t2_2te = (TTree*) f2->Get("data/Y3Spt0to30/dataset2/TestTree");

	double  dmass, dBDT;
	float fmass, fBDT;
	int classID, treeID;
	
	t1->SetBranchAddress("mass", &dmass);
	t1->SetBranchAddress("BDTY3spt0to30", &dBDT);

	t2_1tr->SetBranchAddress("
}
