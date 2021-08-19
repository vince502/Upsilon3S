void plot_test()
{
//=========Macro generated from canvas: c2/
//=========  (Thu Jul  8 15:28:11 2021) by ROOT version 6.22/06
   TCanvas *c2 = new TCanvas("c2", "",0,0,700,800);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c2->Range(-52.5,-0.125,472.5,1.125);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
   c2->SetFrameBorderMode(0);
   
   TH1D *h1__1 = new TH1D("h1__1","PbPb 2 ratio cent",35,0,420);
   h1__1->SetBinContent(3,0.4942414);
   h1__1->SetBinContent(12,0.1114016);
   h1__1->SetBinContent(26,0.0798362);
   h1__1->SetBinError(3,0.1023207);
   h1__1->SetBinError(12,0.04071923);
   h1__1->SetBinError(26,0.03397091);
   h1__1->SetMinimum(0);
   h1__1->SetMaximum(1);
   h1__1->SetEntries(3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h1__1->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h1__1->SetMarkerColor(ci);
   h1__1->SetMarkerStyle(4);
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetLabelSize(0.04);
   h1__1->GetXaxis()->SetTitleOffset(1);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetTitle("R_{AA}");
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetTitleSize(0.05);
   h1__1->GetYaxis()->SetTitleOffset(1.2);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("pe");
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
