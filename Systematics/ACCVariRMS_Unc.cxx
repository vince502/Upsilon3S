#include "../plots/drawRAAplot.cxx"


double getACCVariRMSUnc(int pl, int ph, int cl, int ch, int state){
	TFile *f_acc_nom, *f_acc_sys;
	f_acc_nom = TFile::Open(Form("%s/Acceptance/AccRes_%dS_pt%.1f_%.1f_y-2.4_2.4_SimuPt3.5_ptW1.root", workdir.Data(), state, (double) pl, (double) ph ) );
	f_acc_sys = TFile::Open(Form("%s/Acceptance/AccRes_%dS_pt%.1f_%.1f_y-2.4_2.4_SimuPt3.5_ptW1_SYSPT.root", workdir.Data(), state, (double) pl, (double) ph ) );
	std::cout << Form("%s \n%s \n ", f_acc_nom->GetName(), f_acc_sys->GetName() ) ;
	TH1D *hacc_nom, *hacc_sys;
	hacc_nom = (TH1D*) f_acc_nom->Get("hGenRatio");
	TH1D* hacc_sys_NU = (TH1D*) f_acc_sys->Get("hGenRatio_NU");
	TH1D* hacc_sys_ND = (TH1D*) f_acc_sys->Get("hGenRatio_ND");
	TH1D* hacc_sys_UN = (TH1D*) f_acc_sys->Get("hGenRatio_UN");
	TH1D* hacc_sys_DN = (TH1D*) f_acc_sys->Get("hGenRatio_DN");
	double aNU = hacc_sys_NU->GetBinContent(1)- hacc_nom->GetBinContent(1);
	double aND = hacc_sys_ND->GetBinContent(1)- hacc_nom->GetBinContent(1);
	double aUN = hacc_sys_UN->GetBinContent(1)- hacc_nom->GetBinContent(1);
	double aDN = hacc_sys_DN->GetBinContent(1)- hacc_nom->GetBinContent(1);
	double acc_unc = TMath::Sqrt(0.25* ( aNU *aNU + aND * aND + aUN * aUN + aDN * aDN ) );
	f_acc_nom->Close();
	f_acc_sys->Close();
	return acc_unc;
};
double getACCVariRMSUnc(ana_bins k){
	double unc_sys = getACCVariRMSUnc(k.pl, k.ph, k.cl, k.ch, k.state);
	return unc_sys;
};

void ACCVariRMS_Unc(){
	TFile* output = new TFile("ACCQuad_unc.root","recreate");
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

	int counter =1;
	for( auto item : vc2){
		rc2s->SetBinContent(counter, getACCVariRMSUnc(item));
		counter++;
	}
	counter =1;
	for( auto item : vc3){
		rc3s->SetBinContent(counter, getACCVariRMSUnc(item));
		counter++;
	}
	counter =1;

	for( auto item : vp2){
		rp2s->SetBinContent(counter, getACCVariRMSUnc(item));
		counter++;
	}
	counter =1;
	
	for( auto item : vp3){
		rp3s->SetBinContent(counter, getACCVariRMSUnc(item));
		counter++;
	}
	output->cd();
	rc2s->Write();
	rc3s->Write();
	rp2s->Write();
	rp3s->Write();
	output->Close();
}

