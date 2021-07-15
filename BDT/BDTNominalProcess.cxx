#include "BDTClassifier_BLIND.C"
#include "BDTClassifierApplication.C"
#include "makeRooDataset_fromBDT.C"
void BDTNominalPostProcess(long ts);

void BDTNominalProcess(int step= 0, long ts= 00000000, double ptLow = 0, double ptHigh = 4 , int cBinLow =0 , int cBinHigh =181)
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
    BDTNominalPostProcess(ts);
  }


}
void BDTNominalPostProcess(long ts)
{
  BDTClassifierApplication(ts, 1, 1, true);
  BDTClassifierApplication(ts, 2, 1, true);

  makeRooDataset_fromBDT(ts, true, 0 );
  makeRooDataset_fromBDT(ts, true, 1 );
  makeRooDataset_fromBDT(ts, true, 2, "MC_1S" );
  makeRooDataset_fromBDT(ts, true, 2, "MC_2S" );
}

