void BDTCorYieldplot_train3_2S_8000000012_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Nov 12 21:15:53 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train3__1 = new TH1D("Y2S_train3__1","",20,0,20);
   Y2S_train3__1->SetBinContent(1,1);
   Y2S_train3__1->SetBinContent(8,1.389837);
   Y2S_train3__1->SetBinContent(9,1.326315);
   Y2S_train3__1->SetBinContent(10,1.3521);
   Y2S_train3__1->SetBinContent(11,1.398088);
   Y2S_train3__1->SetBinContent(12,1.387245);
   Y2S_train3__1->SetBinContent(13,1.391373);
   Y2S_train3__1->SetBinContent(14,1.388877);
   Y2S_train3__1->SetBinContent(15,1.348157);
   Y2S_train3__1->SetBinContent(16,1.2883);
   Y2S_train3__1->SetBinContent(17,1.313063);
   Y2S_train3__1->SetBinContent(18,1.282529);
   Y2S_train3__1->SetBinContent(19,1.311447);
   Y2S_train3__1->SetBinContent(20,1.478924);
   Y2S_train3__1->SetBinContent(21,1.486241);
   Y2S_train3__1->SetBinError(1,0.2855421);
   Y2S_train3__1->SetBinError(8,0.4364222);
   Y2S_train3__1->SetBinError(9,0.4185716);
   Y2S_train3__1->SetBinError(10,0.425116);
   Y2S_train3__1->SetBinError(11,0.4375033);
   Y2S_train3__1->SetBinError(12,0.4337239);
   Y2S_train3__1->SetBinError(13,0.4346403);
   Y2S_train3__1->SetBinError(14,0.4330771);
   Y2S_train3__1->SetBinError(15,0.4221508);
   Y2S_train3__1->SetBinError(16,0.4060794);
   Y2S_train3__1->SetBinError(17,0.4127259);
   Y2S_train3__1->SetBinError(18,0.4070702);
   Y2S_train3__1->SetBinError(19,0.4172426);
   Y2S_train3__1->SetBinError(20,0.4734151);
   Y2S_train3__1->SetBinError(21,0.5347093);
   Y2S_train3__1->SetMinimum(0.4);
   Y2S_train3__1->SetMaximum(2);
   Y2S_train3__1->SetEntries(15);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y2S_train3__1->SetLineColor(ci);
   Y2S_train3__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y2S_train3__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y2S_train3__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y2S_train3__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y2S_train3__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y2S_train3__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y2S_train3__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y2S_train3__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y2S_train3__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y2S_train3__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y2S_train3__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y2S_train3__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y2S_train3__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y2S_train3__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y2S_train3__1->GetXaxis()->SetBinLabel(16,"0.40");
   Y2S_train3__1->GetXaxis()->SetBinLabel(17,"0.50");
   Y2S_train3__1->GetXaxis()->SetBinLabel(18,"0.60");
   Y2S_train3__1->GetXaxis()->SetBinLabel(19,"0.70");
   Y2S_train3__1->GetXaxis()->SetBinLabel(20,"0.80");
   Y2S_train3__1->GetXaxis()->SetLabelFont(42);
   Y2S_train3__1->GetXaxis()->SetTitleOffset(1);
   Y2S_train3__1->GetXaxis()->SetTitleFont(42);
   Y2S_train3__1->GetYaxis()->SetLabelFont(42);
   Y2S_train3__1->GetYaxis()->SetTitleFont(42);
   Y2S_train3__1->GetZaxis()->SetLabelFont(42);
   Y2S_train3__1->GetZaxis()->SetTitleOffset(1);
   Y2S_train3__1->GetZaxis()->SetTitleFont(42);
   Y2S_train3__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
