void BDTCorYieldplot_train2_3S_8000000004_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Oct 29 16:57:52 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train2__1 = new TH1D("Y3S_train2__1","",15,0,15);
   Y3S_train2__1->SetBinContent(1,1);
   Y3S_train2__1->SetBinContent(5,1.055727);
   Y3S_train2__1->SetBinContent(6,5.363448);
   Y3S_train2__1->SetBinContent(7,5.483929);
   Y3S_train2__1->SetBinContent(8,1.182815);
   Y3S_train2__1->SetBinContent(9,1.149843);
   Y3S_train2__1->SetBinContent(10,1.009172);
   Y3S_train2__1->SetBinContent(11,0.9814345);
   Y3S_train2__1->SetBinContent(12,1.348745);
   Y3S_train2__1->SetBinContent(13,1.367633);
   Y3S_train2__1->SetBinContent(14,1.161284);
   Y3S_train2__1->SetBinContent(15,1.443152);
   Y3S_train2__1->SetBinError(1,0.4315022);
   Y3S_train2__1->SetBinError(5,0.63131);
   Y3S_train2__1->SetBinError(6,2.31434);
   Y3S_train2__1->SetBinError(7,2.366328);
   Y3S_train2__1->SetBinError(8,0.5870102);
   Y3S_train2__1->SetBinError(9,0.5662192);
   Y3S_train2__1->SetBinError(10,0.5110291);
   Y3S_train2__1->SetBinError(11,0.4996318);
   Y3S_train2__1->SetBinError(12,0.6430597);
   Y3S_train2__1->SetBinError(13,0.6624298);
   Y3S_train2__1->SetBinError(14,0.619603);
   Y3S_train2__1->SetBinError(15,0.7890639);
   Y3S_train2__1->SetEntries(12);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y3S_train2__1->SetLineColor(ci);
   Y3S_train2__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y3S_train2__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y3S_train2__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y3S_train2__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y3S_train2__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y3S_train2__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y3S_train2__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y3S_train2__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y3S_train2__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y3S_train2__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y3S_train2__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y3S_train2__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y3S_train2__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y3S_train2__1->GetXaxis()->SetBinLabel(15,"0.30");
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
