void BDTCorYieldplot_train2_3S_8000000028_2()
{
//=========Macro generated from canvas: c1/
//=========  (Sun Nov 14 10:27:48 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train2__1 = new TH1D("Y3S_train2__1","",9,0,9);
   Y3S_train2__1->SetBinContent(1,1);
   Y3S_train2__1->SetBinContent(2,1.23983);
   Y3S_train2__1->SetBinContent(3,1.088895);
   Y3S_train2__1->SetBinContent(4,0.8787965);
   Y3S_train2__1->SetBinContent(5,0.8894711);
   Y3S_train2__1->SetBinContent(6,0.8432941);
   Y3S_train2__1->SetBinContent(7,0.6230602);
   Y3S_train2__1->SetBinContent(8,0.9924537);
   Y3S_train2__1->SetBinContent(9,0.992844);
   Y3S_train2__1->SetBinError(1,0.4605381);
   Y3S_train2__1->SetBinError(2,0.6492733);
   Y3S_train2__1->SetBinError(3,0.5892156);
   Y3S_train2__1->SetBinError(4,0.5048199);
   Y3S_train2__1->SetBinError(5,0.5087052);
   Y3S_train2__1->SetBinError(6,0.4912594);
   Y3S_train2__1->SetBinError(7,0.4095338);
   Y3S_train2__1->SetBinError(8,0.5534652);
   Y3S_train2__1->SetBinError(9,0.5619999);
   Y3S_train2__1->SetMinimum(0.4);
   Y3S_train2__1->SetMaximum(2);
   Y3S_train2__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y3S_train2__1->SetLineColor(ci);
   Y3S_train2__1->GetXaxis()->SetBinLabel(2,"-0.10");
   Y3S_train2__1->GetXaxis()->SetBinLabel(3,"0.00");
   Y3S_train2__1->GetXaxis()->SetBinLabel(4,"0.10");
   Y3S_train2__1->GetXaxis()->SetBinLabel(5,"0.20");
   Y3S_train2__1->GetXaxis()->SetBinLabel(6,"0.30");
   Y3S_train2__1->GetXaxis()->SetBinLabel(7,"0.50");
   Y3S_train2__1->GetXaxis()->SetBinLabel(8,"0.70");
   Y3S_train2__1->GetXaxis()->SetBinLabel(9,"0.80");
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
