void BDTCorYieldplot_train2_1S_8200000006_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 15 13:15:45 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train2__1 = new TH1D("Y1S_train2__1","",9,0,9);
   Y1S_train2__1->SetBinContent(1,1);
   Y1S_train2__1->SetBinContent(2,1.318748);
   Y1S_train2__1->SetBinContent(3,0.9747064);
   Y1S_train2__1->SetBinContent(4,0.9774047);
   Y1S_train2__1->SetBinContent(5,0.9453049);
   Y1S_train2__1->SetBinContent(6,0.8935449);
   Y1S_train2__1->SetBinContent(7,0.856019);
   Y1S_train2__1->SetBinContent(8,0.8425552);
   Y1S_train2__1->SetBinContent(9,0.7750534);
   Y1S_train2__1->SetBinError(1,0.02781476);
   Y1S_train2__1->SetBinError(2,0.04573999);
   Y1S_train2__1->SetBinError(3,0.03546171);
   Y1S_train2__1->SetBinError(4,0.03524317);
   Y1S_train2__1->SetBinError(5,0.03460836);
   Y1S_train2__1->SetBinError(6,0.03459502);
   Y1S_train2__1->SetBinError(7,0.03519023);
   Y1S_train2__1->SetBinError(8,0.04063626);
   Y1S_train2__1->SetBinError(9,0.05463311);
   Y1S_train2__1->SetMinimum(0.4);
   Y1S_train2__1->SetMaximum(2);
   Y1S_train2__1->SetEntries(9);

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
