#pragma once
#include"./BDT/bininfo.h"
#include <map>
#define GETBKGO
int getNomBkgO_20000000000(int state, int pl, int ph, int cl, int ch)
{
	if( (state == 3 && pl == 0 && ph == 30 && cl == 0 && ch == 181) ) return 3;
	else return -1;
};
#ifdef GETBKGO
#define GETBKGO2
int getNomBkgO_20000000000(ana_bins x){
	return getNomBkgO_20000000000(x.state, x.pl, x.ph, x.cl, x.ch);
};
#endif