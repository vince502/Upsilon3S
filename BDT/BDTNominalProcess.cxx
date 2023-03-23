#include "BDTClassifierApplication_NOM.C"
#include "makeRooDataset_fromBDT_NOM.C"

//void BDTClassifierApplication_NOM(long ts= 9999999999, int train_state =2, int target_state = 2, bool isMC = 0, bool isbbb = true, int ptLow =0, int ptHigh = 30)
//void makeRooDataset_fromBDT_NOM(long ts, bool cutID, bool isMC, int train_state = 3, int ptLow =0 , int ptHigh =30, std::string aux_opt = "nan")
void BDTNominalProcess(long train_ts = 9 ,long ts=1635139612, int mode =0, std::vector<std::pair<int,int>> ptpairs = {{0,30}}, string dataset = ONIABDTDATAB_LATEST)
{
	for( auto ptpair : ptpairs ){
		if(  mode ==0){
			BDTClassifierApplication_NOM(train_ts, ts, 3, 9, 0, true, ptpair.first, ptpair.second, dataset);
			makeRooDataset_fromBDT_NOM(ts, true, false, 3,  ptpair.first, ptpair.second);
			BDTClassifierApplication_NOM(train_ts, ts, 3, 3, 1, true, ptpair.first, ptpair.second, dataset);
			makeRooDataset_fromBDT_NOM(ts, true, true, 3,   ptpair.first, ptpair.second, "nan");
//			BDTClassifierApplication_NOM(train_ts, ts, 3, 2, 1, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, true, 3,   ptpair.first, ptpair.second, "MC_2S");
//			BDTClassifierApplication_NOM(train_ts, ts, 3, 1, 1, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, true, 3,   ptpair.first, ptpair.second, "MC_1S");

		}
		if(mode ==1){
//			BDTClassifierApplication_NOM(ts, 2, 9, 0, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, false, 2,  ptpair.first, ptpair.second );
//			BDTClassifierApplication_NOM(ts, 2, 2, 1, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, true, 2,   ptpair.first, ptpair.second, "MC_2S");
//			BDTClassifierApplication_NOM(ts, 2, 3, 1, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, true, 2,   ptpair.first, ptpair.second, "nan");
//			BDTClassifierApplication_NOM(ts, 2, 1, 1, true, ptpair.first, ptpair.second);
//			makeRooDataset_fromBDT_NOM(ts, true, true, 2,   ptpair.first, ptpair.second, "MC_1S");

		}
		if(mode ==2){
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
}

