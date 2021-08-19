void plot_test_bdt0.2_1.0()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri May 21 14:01:55 2021) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,700,500);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(-11.25,0.03064713,101.25,0.464025);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   Double_t xAxis1[4] = {0, 20, 50, 90}; 
   
   TH1D *h1__1 = new TH1D("h1__1","PbPb 2 ratio cent",3, xAxis1);
   h1__1->SetBinContent(1,0.1985836);
   h1__1->SetBinContent(2,0.1233794);
   h1__1->SetBinContent(3,0.3381126);
   h1__1->SetBinError(1,0.02207021);
   h1__1->SetBinError(2,0.03367105);
   h1__1->SetBinError(3,0.066065);
   h1__1->SetEntries(3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h1__1->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h1__1->SetMarkerColor(ci);
   h1__1->SetMarkerStyle(4);
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetTitleOffset(1);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
