void BDTCorYieldplot_train2_1S_8200000018_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 15 20:12:03 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train2__1 = new TH1D("Y1S_train2__1","",9,0,9);
   Y1S_train2__1->SetBinContent(1,1);
   Y1S_train2__1->SetBinError(1,0.02781476);
   Y1S_train2__1->SetEntries(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y1S_train2__1->SetLineColor(ci);
   Y1S_train2__1->GetXaxis()->SetBinLabel(2,"-0.20");
   Y1S_train2__1->GetXaxis()->SetBinLabel(3,"-0.10");
   Y1S_train2__1->GetXaxis()->SetBinLabel(4,"0.00");
   Y1S_train2__1->GetXaxis()->SetBinLabel(5,"0.05");
   Y1S_train2__1->GetXaxis()->SetBinLabel(6,"0.10");
   Y1S_train2__1->GetXaxis()->SetBinLabel(7,"0.15");
   Y1S_train2__1->GetXaxis()->SetBinLabel(8,"0.20");
   Y1S_train2__1->GetXaxis()->SetBinLabel(9,"0.25");
   Y1S_train2__1->GetXaxis()->SetLabelFont(42);
   Y1S_train2__1->GetXaxis()->SetTitleOffset(1);
   Y1S_train2__1->GetXaxis()->SetTitleFont(42);
   Y1S_train2__1->GetYaxis()->SetLabelFont(42);
   Y1S_train2__1->GetYaxis()->SetTitleFont(42);
   Y1S_train2__1->GetZaxis()->SetLabelFont(42);
   Y1S_train2__1->GetZaxis()->SetTitleOffset(1);
   Y1S_train2__1->GetZaxis()->SetTitleFont(42);
   Y1S_train2__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
