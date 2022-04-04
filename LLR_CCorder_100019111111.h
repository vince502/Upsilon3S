#pragma once
#include"./BDT/bininfo.h"
#include <map>
#define GETBKGO
int getNomBkgO_100019111111(int state, int pl, int ph, int cl, int ch)
{
	if( (state == 2 && pl == 0 && ph == 30 && cl == 0 && ch == 10) ) return 3;
	if( (state == 2 && pl == 0 && ph == 30 && cl == 10 && ch == 20) ) return 1;
	if( (state == 2 && pl == 0 && ph == 30 && cl == 20 && ch == 40) ) return 4;
	if( (state == 2 && pl == 0 && ph == 30 && cl == 40 && ch == 60) ) return 4;
	if( (state == 2 && pl == 0 && ph == 30 && cl == 60 && ch == 80) ) return 1;
	if( (state == 2 && pl == 0 && ph == 30 && cl == 80 && ch == 100) ) return 1;
	if( (state == 2 && pl == 0 && ph == 30 && cl == 100 && ch == 120) ) return 1;
	if( (state == 2 && pl == 0 && ph == 30 && cl == 120 && ch == 140) ) return 2;
	if( (state == 2 && pl == 0 && ph == 30 && cl == 140 && ch == 181) ) return 1;
	if( (state == 2 && pl == 0 && ph == 3 && cl == 0 && ch == 181) ) return 4;
	if( (state == 2 && pl == 3 && ph == 6 && cl == 0 && ch == 181) ) return 3;
	if( (state == 2 && pl == 6 && ph == 9 && cl == 0 && ch == 181) ) return 2;
	if( (state == 2 && pl == 9 && ph == 15 && cl == 0 && ch == 181) ) return 1;
	if( (state == 2 && pl == 15 && ph == 30 && cl == 0 && ch == 181) ) return 1;
	if( (state == 2 && pl == 0 && ph == 30 && cl == 0 && ch == 181) ) return 4;
	if( (state == 3 && pl == 0 && ph == 30 && cl == 0 && ch == 60) ) return 3;
	if( (state == 3 && pl == 0 && ph == 30 && cl == 60 && ch == 100) ) return 1;
	if( (state == 3 && pl == 0 && ph == 30 && cl == 100 && ch == 140) ) return 2;
	if( (state == 3 && pl == 0 && ph == 30 && cl == 140 && ch == 181) ) return 1;
	if( (state == 3 && pl == 0 && ph == 4 && cl == 0 && ch == 181) ) return 4;
	if( (state == 3 && pl == 4 && ph == 9 && cl == 0 && ch == 181) ) return 1;
	if( (state == 3 && pl == 9 && ph == 15 && cl == 0 && ch == 181) ) return 1;
	if( (state == 3 && pl == 15 && ph == 30 && cl == 0 && ch == 181) ) return 1;
	if( (state == 3 && pl == 0 && ph == 30 && cl == 0 && ch == 181) ) return 4;
	else return -1;
};
#ifdef GETBKGO
#define GETBKGO2
int getNomBkgO_100019111111(ana_bins x){
	return getNomBkgO_100019111111(x.state, x.pl, x.ph, x.cl, x.ch);
};
#endif
