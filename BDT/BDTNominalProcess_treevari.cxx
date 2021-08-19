#include "BDTClassifier_BLIND.C"
//#include "BDTClassifierApplication.C"
#include "BDTClassApp_NOM_treevari.C"
#include "makeRooDataset_fromBDT_NOM_treevari.C"
//#include "makeRooDataset_fromBDT.C"
//void BDTNominalPostProcess(long ts);

void BDTNominalProcess_treevari(long ts=9999999999, long ts2=9999999991)
{
//  ROOT::EnableImplicitMT();
//  std::vector<std::thread> jobs;
//  std::vector<std::thread> jobs1;
//  std::vector<std::thread> jobs2;
//  std::vector<std::thread> jobs3;
//  std::vector<std::thread> jobs4;
//  std::vector<std::thread> jobs5;
//  std::vector<std::thread> jobs6;
//  jobs.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 3, 0, true, 0, 30));
//  jobs.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 1, 1, true, 0, 30));
//  jobs.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 2, 1, true, 0, 30));
//  jobs.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 3, 1, true, 0, 30));
//  for(auto &th : jobs) {
//    th.join();
//  }
//
//  jobs1.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 3, 0, true, 0, 6));
//  jobs1.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 1, 1, true, 0, 6));
//  jobs1.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 2, 1, true, 0, 6));
//  jobs1.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 3, 1, true, 0, 6));
//  for(auto &th : jobs1) {
//    th.join();
//  }
//  
//
//  jobs2.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 3, 0, true, 6, 30));
//  jobs2.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 1, 1, true, 6, 30));
//  jobs2.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 2, 1, true, 6, 30));
//  jobs2.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 3, 3, 1, true, 6, 30));
//  for(auto &th : jobs2) {
//    th.join();
//  }
//
//  jobs3.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 2, 0, true, 0, 30));
//  jobs3.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 1, 1, true, 0, 30));
//  jobs3.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 2, 1, true, 0, 30));
//  jobs3.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 3, 1, true, 0, 30));
//  for(auto &th : jobs3) {
//    th.join();
//  }
//
//  jobs4.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 2, 0, true, 0, 4));
//  jobs4.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 1, 1, true, 0, 4));
//  jobs4.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 2, 1, true, 0, 4));
//  jobs4.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 3, 1, true, 0, 4));
//  for(auto &th : jobs4) {
//    th.join();
//  }
//
//  jobs5.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 2, 0, true, 4, 9));
//  jobs5.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 1, 1, true, 4, 9));
//  jobs5.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 2, 1, true, 4, 9));
//  jobs5.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 3, 1, true, 4, 9));
//  for(auto &th : jobs5) {
//    th.join();
//  }
//
//  jobs6.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 2, 0, true, 9, 30));
//  jobs6.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 1, 1, true, 9, 30));
//  jobs6.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 2, 1, true, 9, 30));
//  jobs6.push_back(std::thread(BDTClassApp_NOM_treevari,ts, ts2, 2, 3, 1, true, 9, 30));
//  for(auto &th : jobs6) {
//    th.join();
//  }
  

//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 0, 3, 0, 30 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 3, 0, 30 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 3, 0, 30, "MC_1S" );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 3, 0, 30, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 0, 3, 0, 6 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 3, 0, 6 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 3, 0, 6, "MC_1S" );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 3, 0, 6, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 0, 3, 6, 30 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 3, 6, 30 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 3, 6, 30, "MC_1S" );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 3, 6, 30, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 0, 2, 0, 30 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 0, 30 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 0, 30, "MC_1S" );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 0, 30, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 0, 2, 0, 4 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 0, 4 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 0, 4, "MC_1S" );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 0, 4, "MC_2S" );
//
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 0, 2, 4, 9 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 4, 9 );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 4, 9, "MC_1S" );
//  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 4, 9, "MC_2S" );

  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 0, 2, 9, 30 );
  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 9, 30 );
  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 9, 30, "MC_1S" );
  makeRooDataset_fromBDT_NOM_treevari(ts2, true, 1, 2, 9, 30, "MC_2S" );

}

