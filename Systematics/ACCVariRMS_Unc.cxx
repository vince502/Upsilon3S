#include "sys_wr_helper.cxx"

double getACCVariRMSUnc(ana_bins x){
	int pl = x.pl; int ph = x.ph; int state = x.state;
	TFile *f_acc_nom, *f_acc_sys;
	f_acc_nom = TFile::Open(Form("%s/Acceptance/AccRes_%dS_y-2.4_2.4_SimuPt3.5_ptW1.root", workdir.Data(), state ));
//	f_acc_nom = TFile::Open(Form("%s/Acceptance/AccRes_%dS_pt%.1f_%.1f_y-2.4_2.4_SimuPt3.5_ptW1.root", workdir.Data(), state, (double) pl, (double) ph ) );
//	f_acc_sys = TFile::Open(Form("%s/Acceptance/AccRes_%dS_pt%.1f_%.1f_y-2.4_2.4_SimuPt3.5_ptW1_SYSPT.root", workdir.Data(), state, (double) pl, (double) ph ) );
//	std::cout << Form("%s \n%s \n ", f_acc_nom->GetName(), f_acc_sys->GetName() ) ;
	TH1D *hacc_nom, *hacc_sys;
	hacc_nom = (TH1D*) f_acc_nom->Get("hGenRatio");
	TH1D* hacc_sys_NU = (TH1D*) f_acc_nom->Get("hGenRatio_NU");
	TH1D* hacc_sys_ND = (TH1D*) f_acc_nom->Get("hGenRatio_ND");
	TH1D* hacc_sys_UN = (TH1D*) f_acc_nom->Get("hGenRatio_UN");
	TH1D* hacc_sys_DN = (TH1D*) f_acc_nom->Get("hGenRatio_DN");
	double aNU = (hacc_sys_NU->Integral(pl+1, ph)- hacc_nom->Integral(pl+1, ph)) / (ph-pl);
	double aND = (hacc_sys_ND->Integral(pl+1, ph)- hacc_nom->Integral(pl+1, ph)) / (ph-pl);
	double aUN = (hacc_sys_UN->Integral(pl+1, ph)- hacc_nom->Integral(pl+1, ph)) / (ph-pl);
	double aDN = (hacc_sys_DN->Integral(pl+1, ph)- hacc_nom->Integral(pl+1, ph)) / (ph-pl);
//	double aNU = hacc_sys_NU->GetBinContent(1)- hacc_nom->GetBinContent(1);
//	double aND = hacc_sys_ND->GetBinContent(1)- hacc_nom->GetBinContent(1);
//	double aUN = hacc_sys_UN->GetBinContent(1)- hacc_nom->GetBinContent(1);
//	double aDN = hacc_sys_DN->GetBinContent(1)- hacc_nom->GetBinContent(1);
	double acc_unc = TMath::Sqrt(0.25* ( aNU *aNU + aND * aND + aUN * aUN + aDN * aDN ) );
	f_acc_nom->Close();
//	f_acc_sys->Close();
	return acc_unc;
};

void ACCVariRMS_Unc(){
	sys_wr_helper("ACCQuad_unc.root", getACCVariRMSUnc);
	TFile* output = new TFile("ACCQuad_unc.root","recreate");
}

