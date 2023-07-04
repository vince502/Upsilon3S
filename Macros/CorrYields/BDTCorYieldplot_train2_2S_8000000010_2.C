void BDTCorYieldplot_train2_2S_8000000010_2()
{
//=========Macro generated from canvas: c1/
//=========  (Sat Oct 30 03:35:42 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train2__1 = new TH1D("Y2S_train2__1","",15,0,15);
   Y2S_train2__1->SetBinContent(1,1);
   Y2S_train2__1->SetBinContent(5,2.023439);
   Y2S_train2__1->SetBinContent(6,1.159888);
   Y2S_train2__1->SetBinContent(7,1.35842);
   Y2S_train2__1->SetBinContent(8,1.434365);
   Y2S_train2__1->SetBinContent(9,1.347217);
   Y2S_train2__1->SetBinContent(10,1.44177);
   Y2S_train2__1->SetBinContent(11,0.3047648);
   Y2S_train2__1->SetBinContent(12,1.288909);
   Y2S_train2__1->SetBinContent(13,1.562469);
   Y2S_train2__1->SetBinContent(14,1.219649);
   Y2S_train2__1->SetBinContent(15,1.434751);
   Y2S_train2__1->SetBinError(1,0.2891212);
   Y2S_train2__1->SetBinError(5,0.6420371);
   Y2S_train2__1->SetBinError(6,0.4326151);
   Y2S_train2__1->SetBinError(7,0.4463739);
   Y2S_train2__1->SetBinError(8,0.4530491);
   Y2S_train2__1->SetBinError(9,0.4277655);
   Y2S_train2__1->SetBinError(10,0.4500148);
   Y2S_train2__1->SetBinError(11,10.05762);
   Y2S_train2__1->SetBinError(12,0.4119555);
   Y2S_train2__1->SetBinError(13,0.4972831);
   Y2S_train2__1->SetBinError(14,0.437977);
   Y2S_train2__1->SetBinError(15,0.5677194);
   Y2S_train2__1->SetMinimum(0.4);
   Y2S_train2__1->SetMaximum(2);
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
