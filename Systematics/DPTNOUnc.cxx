#include "../plots/drawRAAplot.cxx"
#include "GOF_test.cxx"
#include "sys_wr_helper.cxx"

double getDPTVariUnc(aba_bins x){
	int pl, ph, cl, ch, tran_state, state, bpl, bph;
	long ts = 9999999999;
	if( ts == 9999999999 ) train_state = state;
	string fittype = (strcmp(x.bin_attr.c_str(),"c")==0) ? "FF" : "GC";
	auto AICres = AICGOF_test(x);
	string bkgNom = AICres[0].second;
	std::string type_nom = Form("CB3:%s:%s",	bkgNom.c_str(), fittype.c_str());
	binplotter* bp  = new binplotter(type_nom, ts,  2.4, pl, ph, cl, ch, 0, bl_nom, 1, bpl, bph, train_state, state, false, false);
	dbg();
	double eff_nom = bp->get_eff(state).first;
	double eff_sys_no = bp->get_eff_sysdpt(state, "NO").first;
	std::cout << "[SYSTEMATIC] Efficiency nom, no: " <<Form(" %.4f, %.4f%%",eff_nom, eff_sys_no )<< std::endl; 
	double dpt_unc = ( eff_sys_no - eff_nom ) / eff_nom;
	return dpt_unc;
};

void DPTNOUnc(){
	sys_wr_helper("effNODPT_unc.root", getDPTVariUnc);
}

