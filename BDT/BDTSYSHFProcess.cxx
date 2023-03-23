//#define NOMINAL_TS 10000000016
//#define NOMINAL_TS 200019111111
#define NOMINAL_TS 400019111111
#include "BDTClassifierApplication_SYSHF2.C"
#include "makeRooDataset_fromBDT_NOM.C"


//void BDTClassifierApplication_NOM(long ts= 9999999999, int train_state =2, int target_state = 2, bool isMC = 0, bool isbbb = true, int ptLow =0, int ptHigh = 30)
//void makeRooDataset_fromBDT_NOM(long ts, bool cutID, bool isMC, int train_state = 3, int ptLow =0 , int ptHigh =30, std::string aux_opt = "nan")
void BDTSYSHFProcess_function(long ts=1635139612, int mode =0, std::vector<std::pair<int,int>> ptpairs = {{0,30}})
{
	for( auto ptpair : ptpairs ){
		if(  mode ==0){
			BDTClassifierApplication_SYSHF2(ts, 3, 9, 0, true, ptpair.first, ptpair.second);
			makeRooDataset_fromBDT_NOM(ts, true, false, 3,  ptpair.first, ptpair.second );
//			BDTClassifierApplication_SYSHF2(ts, 2, 9, 0, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, false, 3,  ptpair.first, ptpair.second );
		}
//		if(mode ==0){
//			BDTClassifierApplication_SYSHF2(ts, 2, 9, 0, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, false, 2,  ptpair.first, ptpair.second );
//		}
		if(mode ==1){
//			BDTClassifierApplication_NOM(ts, 1, 9, 0, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, false, 1,  ptpair.first, ptpair.second );
//			BDTClassifierApplication_NOM(ts, 1, 1, 1, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, true, 1,   ptpair.first, ptpair.second, "MC_1S");
//			BDTClassifierApplication_NOM(ts, 1, 2, 1, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, true, 1,   ptpair.first, ptpair.second, "MC_2S");
//			BDTClassifierApplication_NOM(ts, 1, 3, 1, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, true, 1,   ptpair.first, ptpair.second, "nan");
		}
	}
};

void BDTSYSHFProcess(int sys_step ){
	ROOT::EnableImplicitMT(16);
//	long ts_up = 9999999998;
//	long ts_do = 9999999997;

	long ts_up = (NOMINAL_TS * 10000) + 2;
	long ts_do = (NOMINAL_TS * 10000) + 1;

	std::vector<std::pair<int,int>> ptp = {
		{	0,30	},
		{	0,3	},
		{	0,4	},
		{	3,6	},
		{	6,9	},
		{	4,9	},
		{	9,15	},
		{	15,30	},
	};
	if( sys_step == 1 || sys_step == 0 ) BDTSYSHFProcess_function(ts_up,0, ptp);
	if( sys_step == -1 || sys_step == 0 ) BDTSYSHFProcess_function(ts_do,0, ptp);
};



