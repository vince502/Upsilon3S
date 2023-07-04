void BDTCorYieldplot_train2_2S_8100000003_2()
{
//=========Macro generated from canvas: c1/
//=========  (Sat Oct 30 07:34:05 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train2__1 = new TH1D("Y2S_train2__1","",15,0,15);
   Y2S_train2__1->SetBinContent(1,1);
   Y2S_train2__1->SetBinContent(14,-inf);
   Y2S_train2__1->SetBinContent(15,-inf);
   Y2S_train2__1->SetBinError(1,0.2891212);
   Y2S_train2__1->SetBinError(14,-nan);
   Y2S_train2__1->SetBinError(15,-nan);
   Y2S_train2__1->SetMinimum(0.4);
   Y2S_train2__1->SetMaximum(2);
   Y2S_train2__1->SetEntries(3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y2S_train2__1->SetLineColor(ci);
   Y2S_train2__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y2S_train2__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y2S_train2__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y2S_train2__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y2S_train2__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y2S_train2__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y2S_train2__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y2S_train2__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y2S_train2__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y2S_train2__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y2S_train2__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y2S_train2__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y2S_train2__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y2S_train2__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y2S_train2__1->GetXaxis()->SetLabelFont(42);
   Y2S_train2__1->GetXaxis()->SetTitleOffset(1);
   Y2S_train2__1->GetXaxis()->SetTitleFont(42);
   Y2S_train2__1->GetYaxis()->SetLabelFont(42);
   Y2S_train2__1->GetYaxis()->SetTitleFont(42);
   Y2S_train2__1->GetZaxis()->SetLabelFont(42);
   Y2S_train2__1->GetZaxis()->SetTitleOffset(1);
   Y2S_train2__1->GetZaxis()->SetTitleFont(42);
   Y2S_train2__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
