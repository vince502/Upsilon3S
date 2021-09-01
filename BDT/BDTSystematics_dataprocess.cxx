#include "BDTClassifierApplication_SYSHF.C"
#include "BDTClassifierApplication_SYSEFFTNP.C"
#include "BDTClassifierApplication_SYSEFFDNPT.C"
#include "makeRooDataset_fromBDT_SYS.C"
//void BDTNominalPostProcess(long ts);
void BDTSystematics_dataprocess(long ts=9999999999)
{
//  BDTClassifierApplication_SYSHF(9999999998, 3, 9, 0, true, 0, 30);
//  BDTClassifierApplication_SYSHF(9999999998, 3, 9, 0, true, 0, 6);
//  BDTClassifierApplication_SYSHF(9999999998, 3, 9, 0, true, 6, 30);
//  BDTClassifierApplication_SYSHF(9999999998, 2, 9, 0, true, 0, 30);
//  BDTClassifierApplication_SYSHF(9999999998, 2, 9, 0, true, 0, 4);
//  BDTClassifierApplication_SYSHF(9999999998, 2, 9, 0, true, 4, 9);
//  BDTClassifierApplication_SYSHF(9999999998, 2, 9, 0, true, 9, 30);
//
//  BDTClassifierApplication_SYSHF(9999999997, 3, 9, 0, true, 0, 30);
//  BDTClassifierApplication_SYSHF(9999999997, 3, 9, 0, true, 0, 6);
//  BDTClassifierApplication_SYSHF(9999999997, 3, 9, 0, true, 6, 30);
//  BDTClassifierApplication_SYSHF(9999999997, 2, 9, 0, true, 0, 30);
//  BDTClassifierApplication_SYSHF(9999999997, 2, 9, 0, true, 0, 4);
//  BDTClassifierApplication_SYSHF(9999999997, 2, 9, 0, true, 4, 9);
//  BDTClassifierApplication_SYSHF(9999999997, 2, 9, 0, true, 9, 30);
//
//  BDTClassifierApplication_SYSEFFTNP(ts, 3, 3, 1, true, 0, 30);
//  BDTClassifierApplication_SYSEFFTNP(ts, 3, 2, 1, true, 0, 30);
//
//  BDTClassifierApplication_SYSEFFTNP(ts, 3, 3, 1, true, 0, 6);
//  BDTClassifierApplication_SYSEFFTNP(ts, 3, 2, 1, true, 0, 6);
//
//  BDTClassifierApplication_SYSEFFTNP(ts, 3, 3, 1, true, 6, 30);
//  BDTClassifierApplication_SYSEFFTNP(ts, 3, 2, 1, true, 6, 30);
//
//  BDTClassifierApplication_SYSEFFTNP(ts, 2, 3, 1, true, 0, 30);
//  BDTClassifierApplication_SYSEFFTNP(ts, 2, 2, 1, true, 0, 30);
//
//  BDTClassifierApplication_SYSEFFTNP(ts, 2, 3, 1, true, 0, 4);
//  BDTClassifierApplication_SYSEFFTNP(ts, 2, 2, 1, true, 0, 4);
//
//  BDTClassifierApplication_SYSEFFTNP(ts, 2, 3, 1, true, 4, 9);
//  BDTClassifierApplication_SYSEFFTNP(ts, 2, 2, 1, true, 4, 9);
//
//  BDTClassifierApplication_SYSEFFTNP(ts, 2, 3, 1, true, 9, 30);
//  BDTClassifierApplication_SYSEFFTNP(ts, 2, 2, 1, true, 9, 30);

  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 3, 1, true, 0, 30,1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 2, 1, true, 0, 30,1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 3, 1, true, 0, 6,1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 2, 1, true, 0, 6,1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 3, 1, true, 6, 30,1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 2, 1, true, 6, 30,1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 3, 1, true, 0, 30,1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 2, 1, true, 0, 30,1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 3, 1, true, 0, 4,1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 2, 1, true, 0, 4,1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 3, 1, true, 4, 9,1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 2, 1, true, 4, 9,1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 3, 1, true, 9, 30,1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 2, 1, true, 9, 30,1);
///////////////////////////////////////////////////////////////////

  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 3, 1, true, 0, 30,-1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 2, 1, true, 0, 30,-1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 3, 1, true, 0, 6,-1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 2, 1, true, 0, 6,-1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 3, 1, true, 6, 30,-1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 3, 2, 1, true, 6, 30,-1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 3, 1, true, 0, 30,-1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 2, 1, true, 0, 30,-1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 3, 1, true, 0, 4,-1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 2, 1, true, 0, 4,-1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 3, 1, true, 4, 9,-1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 2, 1, true, 4, 9,-1);

  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 3, 1, true, 9, 30,-1);
  BDTClassifierApplication_SYSEFFDNPT(ts, 2, 2, 1, true, 9, 30,-1);

//  makeRooDataset_fromBDT_SYS(9999999998, true, 0, 3, 0, 30 , "SYSHFUP");
//  makeRooDataset_fromBDT_SYS(9999999998, true, 0, 3, 0, 6 ,"SYSHFUP");
//  makeRooDataset_fromBDT_SYS(9999999998, true, 0, 3, 6, 30 ,"SYSHFUP");
//  makeRooDataset_fromBDT_SYS(9999999998, true, 0, 2, 0, 30 ,"SYSHFUP");
//  makeRooDataset_fromBDT_SYS(9999999998, true, 0, 2, 0, 4 ,"SYSHFUP");
//  makeRooDataset_fromBDT_SYS(9999999998, true, 0, 2, 4, 9 ,"SYSHFUP");
//  makeRooDataset_fromBDT_SYS(9999999998, true, 0, 2, 9, 30 ,"SYSHFUP");
//
//  makeRooDataset_fromBDT_SYS(9999999997, true, 0, 3, 0, 30 ,"SYSHFDOWN");
//  makeRooDataset_fromBDT_SYS(9999999997, true, 0, 3, 0, 6 ,"SYSHFDOWN");
//  makeRooDataset_fromBDT_SYS(9999999997, true, 0, 3, 6, 30 ,"SYSHFDOWN");
//  makeRooDataset_fromBDT_SYS(9999999997, true, 0, 2, 0, 30 ,"SYSHFDOWN");
//  makeRooDataset_fromBDT_SYS(9999999997, true, 0, 2, 0, 4 ,"SYSHFDOWN");
//  makeRooDataset_fromBDT_SYS(9999999997, true, 0, 2, 4, 9 ,"SYSHFDOWN");
//  makeRooDataset_fromBDT_SYS(9999999997, true, 0, 2, 9, 30 ,"SYSHFDOWN");

}

