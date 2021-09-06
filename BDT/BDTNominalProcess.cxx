#include "BDTClassifier_BLIND.C"
#include "BDTClassifierApplication.C"
#include "BDTClassifierApplication_NOM.C"
#include "makeRooDataset_fromBDT_NOM.C"
#include "makeRooDataset_fromBDT.C"
//void BDTNominalPostProcess(long ts);

void _BDTNominalProcess(int step= 0, long ts= 00000000, double ptLow = 0, double ptHigh = 4 , int cBinLow =0 , int cBinHigh =181)
{
  ofstream log;
  if(step ==0 || step < 0)
    {
    std::cout << "Write down description for this run :";
    std::cin.getline(logbuf,2000);
    bool res; 
    res = BDTClassifier_BLIND_Function(0,1, ptLow, ptHigh, cBinLow, cBinHigh);
    if(!res){
      std::system(Form("rm ./.past_source/_BDT_Blind_Classifier_%ld.old",(long) _ts));
      return;
    }
    ts= _ts;
  }
  if(step>=0){
    BDTClassifierApplication(ts, 3, 1, true);
    BDTClassifierApplication(ts, 3, 0, true);
//    BDTNominalPostProcess(ts);
  }


}
//void BDTNominalPostProcess(long ts=9999999999)
void BDTNominalProcess(long ts=9999999996)
{
//  BDTClassifierApplication_NOM(ts, 3, 9, 0, true, 0, 30);
//  BDTClassifierApplication_NOM(ts, 3, 3, 1, true, 0, 30);
//  BDTClassifierApplication_NOM(ts, 3, 2, 1, true, 0, 30);
//  BDTClassifierApplication_NOM(ts, 3, 1, 1, true, 0, 30);
//
//  BDTClassifierApplication_NOM(ts, 3, 9, 0, true, 0, 6);
//  BDTClassifierApplication_NOM(ts, 3, 3, 1, true, 0, 6);
//  BDTClassifierApplication_NOM(ts, 3, 2, 1, true, 0, 6);
//  BDTClassifierApplication_NOM(ts, 3, 1, 1, true, 0, 6);
//
//  BDTClassifierApplication_NOM(ts, 3, 9, 0, true, 6, 30);
//  BDTClassifierApplication_NOM(ts, 3, 3, 1, true, 6, 30);
//  BDTClassifierApplication_NOM(ts, 3, 2, 1, true, 6, 30);
//  BDTClassifierApplication_NOM(ts, 3, 1, 1, true, 6, 30);
//
  BDTClassifierApplication_NOM(ts, 2, 9, 0, true, 0, 30);
  BDTClassifierApplication_NOM(ts, 2, 3, 1, true, 0, 30);
  BDTClassifierApplication_NOM(ts, 2, 2, 1, true, 0, 30);
  BDTClassifierApplication_NOM(ts, 2, 1, 1, true, 0, 30);
//
//  BDTClassifierApplication_NOM(ts, 2, 9, 0, true, 0, 4);
//  BDTClassifierApplication_NOM(ts, 2, 3, 1, true, 0, 4);
//  BDTClassifierApplication_NOM(ts, 2, 2, 1, true, 0, 4);
//  BDTClassifierApplication_NOM(ts, 2, 1, 1, true, 0, 4);
//
//  BDTClassifierApplication_NOM(ts, 2, 9, 0, true, 4, 9);
//  BDTClassifierApplication_NOM(ts, 2, 3, 1, true, 4, 9);
//  BDTClassifierApplication_NOM(ts, 2, 2, 1, true, 4, 9);
//  BDTClassifierApplication_NOM(ts, 2, 1, 1, true, 4, 9);
//
//  BDTClassifierApplication_NOM(ts, 2, 9, 0, true, 9, 30);
//  BDTClassifierApplication_NOM(ts, 2, 3, 1, true, 9, 30);
//  BDTClassifierApplication_NOM(ts, 2, 2, 1, true, 9, 30);
//  BDTClassifierApplication_NOM(ts, 2, 1, 1, true, 9, 30);

//  makeRooDataset_fromBDT_NOM(ts, true, 0, 3, 0, 30 );
//  makeRooDataset_fromBDT_NOM(ts, true, 1, 3, 0, 30 );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 3, 0, 30, "MC_1S" );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 3, 0, 30, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM(ts, true, 0, 3, 0, 6 );
//  makeRooDataset_fromBDT_NOM(ts, true, 1, 3, 0, 6 );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 3, 0, 6, "MC_1S" );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 3, 0, 6, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM(ts, true, 0, 3, 6, 30 );
//  makeRooDataset_fromBDT_NOM(ts, true, 1, 3, 6, 30 );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 3, 6, 30, "MC_1S" );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 3, 6, 30, "MC_2S" );
//
  makeRooDataset_fromBDT_NOM(ts, true, 0, 2, 0, 30 );
  makeRooDataset_fromBDT_NOM(ts, true, 1, 2, 0, 30 );
  makeRooDataset_fromBDT_NOM(ts, true, 2, 2, 0, 30, "MC_1S" );
  makeRooDataset_fromBDT_NOM(ts, true, 2, 2, 0, 30, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM(ts, true, 0, 2, 0, 4 );
//  makeRooDataset_fromBDT_NOM(ts, true, 1, 2, 0, 4 );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 2, 0, 4, "MC_1S" );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 2, 0, 4, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM(ts, true, 0, 2, 4, 9 );
//  makeRooDataset_fromBDT_NOM(ts, true, 1, 2, 4, 9 );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 2, 4, 9, "MC_1S" );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 2, 4, 9, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM(ts, true, 0, 2, 9, 30 );
//  makeRooDataset_fromBDT_NOM(ts, true, 1, 2, 9, 30 );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 2, 9, 30, "MC_1S" );
//  makeRooDataset_fromBDT_NOM(ts, true, 2, 2, 9, 30, "MC_2S" );

}

