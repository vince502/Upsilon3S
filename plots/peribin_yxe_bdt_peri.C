void peribin_yxe_bdt_peri()
{
//=========Macro generated from canvas: c1/c1
//=========  (Tue Jul  6 17:44:50 2021) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "c1",339,137,700,500);
   gStyle->SetOptStat(0);
   c1->Range(-1.5875,-212.5,1.2875,912.5);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *h1__1 = new TH1D("h1__1","",23,-1.3,1);
   h1__1->SetBinContent(4,124.2103);
   h1__1->SetBinContent(5,126.2151);
   h1__1->SetBinContent(6,126.2151);
   h1__1->SetBinContent(7,126.2151);
   h1__1->SetBinContent(8,126.2151);
   h1__1->SetBinContent(9,126.2151);
   h1__1->SetBinContent(10,126.2151);
   h1__1->SetBinContent(11,126.2151);
   h1__1->SetBinContent(12,129.1414);
   h1__1->SetBinContent(13,144.5247);
   h1__1->SetBinContent(15,281.3508);
   h1__1->SetBinContent(16,406.6697);
   h1__1->SetBinContent(17,-216.411);
   h1__1->SetBinError(4,99.74881);
   h1__1->SetBinError(5,99.60113);
   h1__1->SetBinError(6,99.60113);
   h1__1->SetBinError(7,99.60113);
   h1__1->SetBinError(8,99.60113);
   h1__1->SetBinError(9,99.60113);
   h1__1->SetBinError(10,99.60113);
   h1__1->SetBinError(11,99.60113);
   h1__1->SetBinError(12,99.70625);
   h1__1->SetBinError(13,79.30406);
   h1__1->SetBinError(15,74.11695);
   h1__1->SetBinError(16,78.1911);
   h1__1->SetBinError(17,13891.43);
   h1__1->SetMinimum(-100);
   h1__1->SetMaximum(800);
   h1__1->SetEntries(14);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1__1->SetLineColor(ci);
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
