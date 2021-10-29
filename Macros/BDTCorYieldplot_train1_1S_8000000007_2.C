void BDTCorYieldplot_train1_1S_8000000007_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Oct 29 15:51:13 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train1__1 = new TH1D("Y1S_train1__1","",15,0,15);
   Y1S_train1__1->SetBinContent(1,1);
   Y1S_train1__1->SetBinContent(7,0.9911335);
   Y1S_train1__1->SetBinContent(8,0.9837647);
   Y1S_train1__1->SetBinContent(9,0.9593071);
   Y1S_train1__1->SetBinContent(10,0.9296541);
   Y1S_train1__1->SetBinContent(11,0.9035667);
   Y1S_train1__1->SetBinContent(12,0.8549254);
   Y1S_train1__1->SetBinContent(13,0.8122554);
   Y1S_train1__1->SetBinContent(14,0.7302914);
   Y1S_train1__1->SetBinContent(15,0.761529);
   Y1S_train1__1->SetBinError(1,0.02771479);
   Y1S_train1__1->SetBinError(7,0.03625841);
   Y1S_train1__1->SetBinError(8,0.035315);
   Y1S_train1__1->SetBinError(9,0.03421807);
   Y1S_train1__1->SetBinError(10,0.03387652);
   Y1S_train1__1->SetBinError(11,0.03364691);
   Y1S_train1__1->SetBinError(12,0.03425103);
   Y1S_train1__1->SetBinError(13,0.03683736);
   Y1S_train1__1->SetBinError(14,0.0415026);
   Y1S_train1__1->SetBinError(15,0.05708072);
   Y1S_train1__1->SetEntries(10);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y1S_train1__1->SetLineColor(ci);
   Y1S_train1__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y1S_train1__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y1S_train1__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y1S_train1__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y1S_train1__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y1S_train1__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y1S_train1__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y1S_train1__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y1S_train1__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y1S_train1__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y1S_train1__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y1S_train1__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y1S_train1__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y1S_train1__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y1S_train1__1->GetXaxis()->SetLabelFont(42);
   Y1S_train1__1->GetXaxis()->SetTitleOffset(1);
   Y1S_train1__1->GetXaxis()->SetTitleFont(42);
   Y1S_train1__1->GetYaxis()->SetLabelFont(42);
   Y1S_train1__1->GetYaxis()->SetTitleFont(42);
   Y1S_train1__1->GetZaxis()->SetLabelFont(42);
   Y1S_train1__1->GetZaxis()->SetTitleOffset(1);
   Y1S_train1__1->GetZaxis()->SetTitleFont(42);
   Y1S_train1__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
