#pragma once

#include <cstdlib>
#include <fstream>
#include "../../fitter.h"


struct dCIMnCTEQ15{
	unsigned int idx = 0;
    double Npart = 0;
    double dr_val =0;
    double dr_max =0;
    double dr_min =0;
    double dr_rel_max = 0;
    double dr_rel_min = 0;

    double raa1s_val =0;
    double raa1s_max =0;
    double raa1s_min =0;
    double raa1s_max2 =0;
    double raa1s_min2 =0;

    double raa2s_val =0;
    double raa2s_max =0;
    double raa2s_min =0;
    double raa2s_max2 =0;
    double raa2s_min2 =0;

    double raa3s_val =0;
    double raa3s_max =0;
    double raa3s_min =0;
    double raa3s_max2 =0;
    double raa3s_min2 =0;
};

#include "./CIM_nCTEQ15/CIM_nCTEQ15.C"

struct dEPPS16{
	double Npart = -1;
	double pT 	= -1;
	double raa1s = 0;
	double raa2s = 0;
	double raa3s = 0;
	double raa1p = 0;
	double raa23s = 0;
	double raa3over2s = 0;
};

struct dQTraj{
	double pl = -1;
	double ph = -1;
	int cl = -1;
	int ch = -1;
	double raa = -1;
	double raaup = -1;
	double raado = -1;
};

struct dQTraj2023{
	double pl = -1;
	double ph = -1;
	int cl = -1;
	int ch = -1;
	double raa = -1;
	double raaup = -1;
	double raado = -1;
	double np = -1;
	double npup = -1;
	double npdo = -1;
};

struct dTransport{
	double Npart = -1;
	double valup = -1;
	double valdo = -1;
	double pt = -1;
};

struct dHeidelberg{
	int mod = 0;
	string cent_intv = "";
	double cent = -1.;
	double Npart = -1;
	double pt = -1;
	double raa1s = -1.;
	double raa2s = -1.;
	double raa3s = -1.;
};

std::map<string, string> fEPPS16{
	{"Ncc", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_Npart_cc.txt"},
	{"Nc-", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_Npart_c-.txt"},
	{"Nc+", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_Npart_c+.txt"},
	{"N-c", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_Npart_-c.txt"},
	{"N+c", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_Npart_+c.txt"},
	
	{"pcc", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_pT_cc.txt"},
	{"pc-", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_pT_c-.txt"},
	{"pc+", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_pT_c+.txt"},
	{"p-c", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_pT_-c.txt"},
	{"p+c", "/home/vince402/Upsilon3S/plots/theory/EPPS16/for5020Plot_Raa_pT_+c.txt"},
};

std::map<string, string> fQTraj{
	{"c1s",  "/home/vince402/Upsilon3S/plots/theory/QTraj/raa1s-centrality-1sbins.tsv"},
	{"c2s",  "/home/vince402/Upsilon3S/plots/theory/QTraj/raa2s-centrality-2sbins.tsv"},
	{"c3s",  "/home/vince402/Upsilon3S/plots/theory/QTraj/raa3s-centrality-3sbins.tsv"},
	{"c32s", "/home/vince402/Upsilon3S/plots/theory/QTraj/3s2sratio-centrality-3sbins.tsv"},
	{"p1s",  "/home/vince402/Upsilon3S/plots/theory/QTraj/raa1s-pt-1sbins.tsv"},
	{"p2s",  "/home/vince402/Upsilon3S/plots/theory/QTraj/raa2s-pt-2sbins.tsv"},
	{"p3s",  "/home/vince402/Upsilon3S/plots/theory/QTraj/raa3s-pt-3sbins.tsv"},
	{"p32s", "/home/vince402/Upsilon3S/plots/theory/QTraj/3s2sratio-pt-3sbins.tsv"},
};

std::map<string, string> fQTraj2023{
	{"c1s",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-1s-npart.tsv"},
	{"c2s",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-2s-npart.tsv"},
	{"c3s",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-3s-npart.tsv"},
	{"c32s", "/home/vince402/Upsilon3S/plots/theory/QTraj2023/ratio-3s2s-npart.tsv"},
	{"c1snj",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-1s-nojumps-npart.tsv"},
	{"c2snj",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-2s-nojumps-npart.tsv"},
	{"c3snj",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-3s-nojumps-npart.tsv"},
	{"c32snj", "/home/vince402/Upsilon3S/plots/theory/QTraj2023/ratio-3s2s-nojumps-npart.tsv"},
	{"p1s",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-1s-pt.tsv"},
	{"p2s",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-2s-pt.tsv"},
	{"p3s",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-3s-pt.tsv"},
	{"p32s", "/home/vince402/Upsilon3S/plots/theory/QTraj2023/ratio-3s2s-pt.tsv"},
	{"p1snj",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-1s-nojumps-pt.tsv"},
	{"p2snj",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-2s-nojumps-pt.tsv"},
	{"p3snj",  "/home/vince402/Upsilon3S/plots/theory/QTraj2023/raa-3s-nojumps-pt.tsv"},
	{"p32snj", "/home/vince402/Upsilon3S/plots/theory/QTraj2023/ratio-3s2s-nojumps-pt.tsv"},
};

std::map<string, string> fTransport{
	{"p32s", "/home/vince402/Upsilon3S/plots/theory/Transport/DR3So2SpT.dat"},
	{"c32s", "/home/vince402/Upsilon3S/plots/theory/Transport/DR3So2SNpart.dat"},
	{"p1s", "/home/vince402/Upsilon3S/plots/theory/Transport/pt_1S.txt"},
	{"p2s", "/home/vince402/Upsilon3S/plots/theory/Transport/pt_2S.txt"},
	{"p3s", "/home/vince402/Upsilon3S/plots/theory/Transport/pt_3S.txt"},
	{"c1s", "/home/vince402/Upsilon3S/plots/theory/Transport/cent_1S.txt"},
	{"c2s", "/home/vince402/Upsilon3S/plots/theory/Transport/cent_2S.txt"},
	{"c3s", "/home/vince402/Upsilon3S/plots/theory/Transport/cent_3S.txt"},
	{"c1sre", "/home/vince402/Upsilon3S/plots/theory/Transport/cent_regExcl.txt"},
	{"c2sre", "/home/vince402/Upsilon3S/plots/theory/Transport/cent_regExcl.txt"},
	{"c3sre", "/home/vince402/Upsilon3S/plots/theory/Transport/cent_regExcl.txt"},
	{"p1sre", "/home/vince402/Upsilon3S/plots/theory/Transport/pt_regIncl.txt"},
	{"p2sre", "/home/vince402/Upsilon3S/plots/theory/Transport/pt_regIncl.txt"},
	{"p3sre", "/home/vince402/Upsilon3S/plots/theory/Transport/pt_regIncl.txt"},
	{"p1sre_", "/home/vince402/Upsilon3S/plots/theory/Transport/pt_regComp.txt"},
	{"p2sre_", "/home/vince402/Upsilon3S/plots/theory/Transport/pt_regComp.txt"},
	{"p3sre_", "/home/vince402/Upsilon3S/plots/theory/Transport/pt_regComp.txt"},
};

std::map<string, string> fHeidelberg{
	{"nobin", "/home/vince402/Upsilon3S/plots/theory/Heidelberg/PRC95-NoBins.txt"},
	{"c", "/home/vince402/Upsilon3S/plots/theory/Heidelberg/PRC95-RAA-c.txt"},
	{"pt", "/home/vince402/Upsilon3S/plots/theory/Heidelberg/PRC95-RAA-pT.txt"},
};

double ptBinWidth_EPPS16(double ptc){
	if(ptc == 1.0 ) return 1.0;
	if(ptc == 3.0 ) return 1.0;
	if(ptc == 5.0 ) return 1.0;
	if(ptc == 7.5 ) return 1.5;
	if(ptc == 10.5 ) return 1.5;
	if(ptc == 21.0 ) return 9.0;
	else return -1;
	
};

enum projection {
	kTPt  =  1,
	kTCent = 2
};
