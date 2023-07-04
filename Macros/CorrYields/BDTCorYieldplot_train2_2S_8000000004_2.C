void BDTCorYieldplot_train2_2S_8000000004_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Oct 29 16:47:30 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train2__1 = new TH1D("Y2S_train2__1","",15,0,15);
   Y2S_train2__1->SetBinContent(1,1);
   Y2S_train2__1->SetBinContent(5,1.076138);
   Y2S_train2__1->SetBinContent(6,2.11953);
   Y2S_train2__1->SetBinContent(7,2.139581);
   Y2S_train2__1->SetBinContent(8,1.663439);
   Y2S_train2__1->SetBinContent(9,1.426299);
   Y2S_train2__1->SetBinContent(10,1.346845);
   Y2S_train2__1->SetBinContent(11,1.211094);
   Y2S_train2__1->SetBinContent(12,1.35649);
   Y2S_train2__1->SetBinContent(13,1.253758);
   Y2S_train2__1->SetBinContent(14,1.252102);
   Y2S_train2__1->SetBinContent(15,1.735721);
   Y2S_train2__1->SetBinError(1,0.2891212);
   Y2S_train2__1->SetBinError(5,0.4261243);
   Y2S_train2__1->SetBinError(6,0.6697359);
   Y2S_train2__1->SetBinError(7,0.6552427);
   Y2S_train2__1->SetBinError(8,0.5145741);
   Y2S_train2__1->SetBinError(9,0.4475714);
   Y2S_train2__1->SetBinError(10,0.4251325);
   Y2S_train2__1->SetBinError(11,0.389549);
   Y2S_train2__1->SetBinError(12,0.4300404);
   Y2S_train2__1->SetBinError(13,0.4102947);
   Y2S_train2__1->SetBinError(14,0.4370198);
   Y2S_train2__1->SetBinError(15,0.6088665);
   Y2S_train2__1->SetEntries(12);

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
