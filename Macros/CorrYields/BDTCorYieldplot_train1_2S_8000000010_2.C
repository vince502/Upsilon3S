void BDTCorYieldplot_train1_2S_8000000010_2()
{
//=========Macro generated from canvas: c1/
//=========  (Sat Oct 30 01:15:43 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train1__1 = new TH1D("Y2S_train1__1","",15,0,15);
   Y2S_train1__1->SetBinContent(1,1);
   Y2S_train1__1->SetBinContent(2,1.038808);
   Y2S_train1__1->SetBinContent(3,1.038808);
   Y2S_train1__1->SetBinContent(4,1.038808);
   Y2S_train1__1->SetBinContent(5,1.974947);
   Y2S_train1__1->SetBinContent(6,1.085019);
   Y2S_train1__1->SetBinContent(7,1.216504);
   Y2S_train1__1->SetBinContent(8,1.106395);
   Y2S_train1__1->SetBinContent(9,0.9381639);
   Y2S_train1__1->SetBinContent(10,inf);
   Y2S_train1__1->SetBinContent(11,inf);
   Y2S_train1__1->SetBinContent(12,inf);
   Y2S_train1__1->SetBinContent(13,inf);
   Y2S_train1__1->SetBinContent(14,inf);
   Y2S_train1__1->SetBinContent(15,inf);
   Y2S_train1__1->SetBinError(1,0.2891212);
   Y2S_train1__1->SetBinError(2,0.4205542);
   Y2S_train1__1->SetBinError(3,0.4205542);
   Y2S_train1__1->SetBinError(4,0.4205542);
   Y2S_train1__1->SetBinError(5,0.6307557);
   Y2S_train1__1->SetBinError(6,0.4126367);
   Y2S_train1__1->SetBinError(7,0.4080768);
   Y2S_train1__1->SetBinError(8,0.3540353);
   Y2S_train1__1->SetBinError(9,0.3014317);
   Y2S_train1__1->SetBinError(10,-nan);
   Y2S_train1__1->SetBinError(11,-nan);
   Y2S_train1__1->SetBinError(12,-nan);
   Y2S_train1__1->SetBinError(13,-nan);
   Y2S_train1__1->SetBinError(14,-nan);
   Y2S_train1__1->SetBinError(15,-nan);
   Y2S_train1__1->SetEntries(15);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y2S_train1__1->SetLineColor(ci);
   Y2S_train1__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y2S_train1__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y2S_train1__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y2S_train1__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y2S_train1__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y2S_train1__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y2S_train1__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y2S_train1__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y2S_train1__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y2S_train1__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y2S_train1__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y2S_train1__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y2S_train1__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y2S_train1__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y2S_train1__1->GetXaxis()->SetLabelFont(42);
   Y2S_train1__1->GetXaxis()->SetTitleOffset(1);
   Y2S_train1__1->GetXaxis()->SetTitleFont(42);
   Y2S_train1__1->GetYaxis()->SetLabelFont(42);
   Y2S_train1__1->GetYaxis()->SetTitleFont(42);
   Y2S_train1__1->GetZaxis()->SetLabelFont(42);
   Y2S_train1__1->GetZaxis()->SetTitleOffset(1);
   Y2S_train1__1->GetZaxis()->SetTitleFont(42);
   Y2S_train1__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
