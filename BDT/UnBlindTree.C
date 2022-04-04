#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "../.workdir.h"

void UnBlindTree(){
  TFile* fo = new TFile(Form("%s/%s", store.Data(), "OutputSkim_isMC0_HFNom_NewMass_211019.root"),"READ");
  TFile* fn = new TFile(Form("%s/test220214.root", store.Data()) ,"recreate");
//  TFile* fo = new TFile(Form("%s/%s", store.Data(), ONIABDTDATA_LATEST.c_str()),"READ");
//  TFile* fn = new TFile(Form("%s/OutputSkim_isMC0_v211019_ForBLIND.root", store.Data()) ,"recreate");
//  TFile* fo = new TFile(Form("%s/%s", hfdir.Data(), SYS_HFUPDATA_RAW.c_str()),"READ");
//  TFile* fn = new TFile(Form("%s/%s", hfdir.Data(), SYS_HFUPDATA.c_str()) ,"recreate");
  TTree* t0 = (TTree*) fo->Get("tree");
  TObjArray* l1 = t0->GetListOfBranches();
  int nl = l1->GetSize();
  Double_t* dvar[nl];
  Int_t* ivar[nl];
  for(int idx=0; idx<nl; idx++){
    TString varname = l1->At(idx)->GetName();
    if(strcmp(&varname[varname.Sizeof()-2],"D")==0) t0->SetBranchAddress(varname.Data(),&dvar[idx]);
    if(strcmp(&varname[varname.Sizeof()-2],"I")==0) t0->SetBranchAddress(varname.Data(),&ivar[idx]);
    if(strcmp(&varname[varname.Sizeof()-2],"O")==0) continue;
  }
  fn->cd();
  TTree* t1 = t0->CloneTree(0);
  t1->SetName("tree1");t1->SetTitle("tree1");
  TTree* t2 = t0->CloneTree(0);
  t2->SetName("tree2");t2->SetTitle("tree2");
  TTree* t3 = t0->CloneTree(0);
  t3->SetName("tree3");t3->SetTitle("tree3");
  TTree* t4 = t0->CloneTree(0);
  t4->SetName("tree4");t4->SetTitle("tree4");
  TTree* t5 = t0->CloneTree(0);
  t5->SetName("tree5");t5->SetTitle("tree5");
  TTree* t6 = t0->CloneTree(0);
  t6->SetName("tree6");t6->SetTitle("tree6");

  int nevt = t0->GetEntries();

  for(int i = 1; i <= nevt; i++){
    t0->GetEntry(i);
    if((i%1000)==0) std::cout << "Processing Event : " << i << std::endl;
    int tn = 0;
    if(i%4==1) t1->Fill();
    if(i%4==2){
      t1->Fill();
      if(((i-2)/4)%2==0) t2->Fill();
      if(((i-2)/4)%2==1) t3->Fill();
    }
    if(i%4==3){
      t1->Fill();
      if(((i-3)/4)%2==0) t4->Fill();
      if(((i-3)/4)%2==1) t5->Fill();
    }
    if(i%4==0) t6->Fill();
//    if(i%4==tn) {t5->Fill(); (tn==0) ? tn =1 : tn++;} 
  }
  fn->Write();
  fn->Close();
  fo->Close();
  
}
