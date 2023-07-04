void BDTCorYieldplot_train1_3S_8000000011_2()
{
//=========Macro generated from canvas: c1/
//=========  (Sat Oct 30 12:57:56 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train1__1 = new TH1D("Y3S_train1__1","",15,0,15);
   Y3S_train1__1->SetBinContent(1,1);
   Y3S_train1__1->SetBinContent(4,0.9678884);
   Y3S_train1__1->SetBinContent(5,1.120527);
   Y3S_train1__1->SetBinContent(6,0.9107248);
   Y3S_train1__1->SetBinContent(7,0.7375503);
   Y3S_train1__1->SetBinContent(8,0.763653);
   Y3S_train1__1->SetBinContent(9,0.6194909);
   Y3S_train1__1->SetBinContent(10,inf);
   Y3S_train1__1->SetBinContent(11,inf);
   Y3S_train1__1->SetBinContent(12,inf);
   Y3S_train1__1->SetBinContent(13,inf);
   Y3S_train1__1->SetBinContent(14,inf);
   Y3S_train1__1->SetBinContent(15,inf);
   Y3S_train1__1->SetBinError(1,0.4315022);
   Y3S_train1__1->SetBinError(4,0.6281039);
   Y3S_train1__1->SetBinError(5,0.6500784);
   Y3S_train1__1->SetBinError(6,0.5702782);
   Y3S_train1__1->SetBinError(7,0.4616129);
   Y3S_train1__1->SetBinError(8,0.4071277);
   Y3S_train1__1->SetBinError(9,0.3359697);
   Y3S_train1__1->SetBinError(10,-nan);
   Y3S_train1__1->SetBinError(11,-nan);
   Y3S_train1__1->SetBinError(12,-nan);
   Y3S_train1__1->SetBinError(13,-nan);
   Y3S_train1__1->SetBinError(14,-nan);
   Y3S_train1__1->SetBinError(15,-nan);
   Y3S_train1__1->SetMinimum(0.4);
   Y3S_train1__1->SetMaximum(2);
   Y3S_train1__1->SetEntries(13);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y3S_train1__1->SetLineColor(ci);
   Y3S_train1__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y3S_train1__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y3S_train1__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y3S_train1__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y3S_train1__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y3S_train1__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y3S_train1__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y3S_train1__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y3S_train1__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y3S_train1__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y3S_train1__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y3S_train1__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y3S_train1__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y3S_train1__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y3S_train1__1->GetXaxis()->SetLabelFont(42);
   Y3S_train1__1->GetXaxis()->SetTitleOffset(1);
   Y3S_train1__1->GetXaxis()->SetTitleFont(42);
   Y3S_train1__1->GetYaxis()->SetLabelFont(42);
   Y3S_train1__1->GetYaxis()->SetTitleFont(42);
   Y3S_train1__1->GetZaxis()->SetLabelFont(42);
   Y3S_train1__1->GetZaxis()->SetTitleOffset(1);
   Y3S_train1__1->GetZaxis()->SetTitleFont(42);
   Y3S_train1__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
