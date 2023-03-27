#pragma once

const float projectionStat(int scenario, int mode){
	if( mode == 2015){
		if( scenario == 1 ) return 1. - (71./100.);
		if( scenario == 2 ) return 1. - (75./100.);
		if( scenario == 3 ) return 1. - (78./100.);
		if( scenario == 4 ) return 1. - (80./100.);
		else return 1.;
	}
	if( mode == 2018){
		if( scenario == 1 ) return 1. - (37.5/100.);
		if( scenario == 2 ) return 1. - (50./100.);
		if( scenario == 3 ) return 1. - (55./100.);
		if( scenario == 4 ) return 1. - (60./100.);
		else return 1.;
	}
	else return 1.;
};

const float projectionSyst(int scenario, int mode){
	if( mode == 2015){
		if( scenario == 1 ) return 1. - (47./100.);
		if( scenario == 2 ) return 1. - (51./100.);
		if( scenario == 3 ) return 1. - (52./100.);
		if( scenario == 4 ) return 1. - (53./100.);
		else return 1.;
	}
	if( mode == 2018){
		if( scenario == 1 ) return 1. - (25./100.);
		if( scenario == 2 ) return 1. - (33./100.);
		if( scenario == 3 ) return 1. - (35./100.);
		if( scenario == 4 ) return 1. - (40./100.);
		else return 1.;
	}
	else return 1.;
};
