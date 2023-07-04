void BDTCorYieldplot_train2_2S_8200000006_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 15 13:15:53 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train2__1 = new TH1D("Y2S_train2__1","",9,0,9);
   Y2S_train2__1->SetBinContent(1,1);
   Y2S_train2__1->SetBinContent(2,2.210703);
   Y2S_train2__1->SetBinContent(3,1.314046);
   Y2S_train2__1->SetBinContent(4,1.21598);
   Y2S_train2__1->SetBinContent(5,1.192469);
   Y2S_train2__1->SetBinContent(6,1.243931);
   Y2S_train2__1->SetBinContent(7,1.354091);
   Y2S_train2__1->SetBinContent(8,1.907531);
   Y2S_train2__1->SetBinContent(9,2.267532);
   Y2S_train2__1->SetBinError(1,0.2892203);
   Y2S_train2__1->SetBinError(2,0.6787121);
   Y2S_train2__1->SetBinError(3,0.4244736);
   Y2S_train2__1->SetBinError(4,0.3903233);
   Y2S_train2__1->SetBinError(5,0.3815078);
   Y2S_train2__1->SetBinError(6,0.3961315);
   Y2S_train2__1->SetBinError(7,0.4258492);
   Y2S_train2__1->SetBinError(8,0.5933097);
   Y2S_train2__1->SetBinError(9,0.7408245);
   Y2S_train2__1->SetMinimum(0.4);
   Y2S_train2__1->SetMaximum(2);
   Y2S_train2__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y2S_train2__1->SetLineColor(ci);
   Y2S_train2__1->GetXaxis()->SetBinLabel(2,"-0.20");
   Y2S_train2__1->GetXaxis()->SetBinLabel(3,"-0.10");
   Y2S_train2__1->GetXaxis()->SetBinLabel(4,"0.00");
   Y2S_train2__1->GetXaxis()->SetBinLabel(5,"0.05");
   Y2S_train2__1->GetXaxis()->SetBinLabel(6,"0.10");
   Y2S_train2__1->GetXaxis()->SetBinLabel(7,"0.15");
   Y2S_train2__1->GetXaxis()->SetBinLabel(8,"0.20");
   Y2S_train2__1->GetXaxis()->SetBinLabel(9,"0.25");
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
