void BDTCorYieldplot_train2_3S_8200000006_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 15 13:16:02 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train2__1 = new TH1D("Y3S_train2__1","",9,0,9);
   Y3S_train2__1->SetBinContent(1,1);
   Y3S_train2__1->SetBinContent(2,2.400747);
   Y3S_train2__1->SetBinContent(3,0.9102322);
   Y3S_train2__1->SetBinContent(4,0.9644454);
   Y3S_train2__1->SetBinContent(5,0.9305964);
   Y3S_train2__1->SetBinContent(6,0.9071779);
   Y3S_train2__1->SetBinContent(7,1.216268);
   Y3S_train2__1->SetBinContent(8,2.009361);
   Y3S_train2__1->SetBinContent(9,1.612927);
   Y3S_train2__1->SetBinError(1,0.4605381);
   Y3S_train2__1->SetBinError(2,1.179923);
   Y3S_train2__1->SetBinError(3,0.5254464);
   Y3S_train2__1->SetBinError(4,0.52375);
   Y3S_train2__1->SetBinError(5,0.5062394);
   Y3S_train2__1->SetBinError(6,0.4973913);
   Y3S_train2__1->SetBinError(7,0.6298457);
   Y3S_train2__1->SetBinError(8,0.9853958);
   Y3S_train2__1->SetBinError(9,0.8750834);
   Y3S_train2__1->SetMinimum(0.4);
   Y3S_train2__1->SetMaximum(2);
   Y3S_train2__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y3S_train2__1->SetLineColor(ci);
   Y3S_train2__1->GetXaxis()->SetBinLabel(2,"-0.20");
   Y3S_train2__1->GetXaxis()->SetBinLabel(3,"-0.10");
   Y3S_train2__1->GetXaxis()->SetBinLabel(4,"0.00");
   Y3S_train2__1->GetXaxis()->SetBinLabel(5,"0.05");
   Y3S_train2__1->GetXaxis()->SetBinLabel(6,"0.10");
   Y3S_train2__1->GetXaxis()->SetBinLabel(7,"0.15");
   Y3S_train2__1->GetXaxis()->SetBinLabel(8,"0.20");
   Y3S_train2__1->GetXaxis()->SetBinLabel(9,"0.25");
   Y3S_train2__1->GetXaxis()->SetLabelFont(42);
   Y3S_train2__1->GetXaxis()->SetTitleOffset(1);
   Y3S_train2__1->GetXaxis()->SetTitleFont(42);
   Y3S_train2__1->GetYaxis()->SetLabelFont(42);
   Y3S_train2__1->GetYaxis()->SetTitleFont(42);
   Y3S_train2__1->GetZaxis()->SetLabelFont(42);
   Y3S_train2__1->GetZaxis()->SetTitleOffset(1);
   Y3S_train2__1->GetZaxis()->SetTitleFont(42);
   Y3S_train2__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
