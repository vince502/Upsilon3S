void res_cent_RAA_0702()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Jul  2 15:41:07 2021) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "c1",10,32,700,500);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1->Range(-52.5,-0.125,472.5,1.125);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *h1__9 = new TH1D("h1__9","PbPb 2 ratio cent",35,0,420);
   h1__9->SetBinContent(3,0.4667366);
   h1__9->SetBinContent(12,0.1094803);
   h1__9->SetBinContent(26,0.07846126);
   h1__9->SetBinError(3,0.1000449);
   h1__9->SetBinError(12,0.0398662);
   h1__9->SetBinError(26,0.03338586);
   h1__9->SetMinimum(0);
   h1__9->SetMaximum(1);
   h1__9->SetEntries(3);
   h1__9->SetDirectory(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h1__9->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h1__9->SetMarkerColor(ci);
   h1__9->SetMarkerStyle(4);
   h1__9->GetXaxis()->SetTitle("N_{part}");
   h1__9->GetXaxis()->SetLabelFont(42);
   h1__9->GetXaxis()->SetLabelSize(0.04);
   h1__9->GetXaxis()->SetTitleOffset(1.2);
   h1__9->GetXaxis()->SetTitleFont(42);
   h1__9->GetYaxis()->SetTitle("R_{AA}");
   h1__9->GetYaxis()->SetLabelFont(42);
   h1__9->GetYaxis()->SetTitleSize(0.05);
   h1__9->GetYaxis()->SetTitleOffset(0.9);
   h1__9->GetYaxis()->SetTitleFont(42);
   h1__9->GetZaxis()->SetLabelFont(42);
   h1__9->GetZaxis()->SetTitleOffset(1);
   h1__9->GetZaxis()->SetTitleFont(42);
   h1__9->Draw("");
  
// ------------>Primitives in pad: pp2
   TPad *pp2 = new TPad("pp2", "",0.8,0,1,1);
   pp2->Draw();
   pp2->cd();
   pp2->Range(0,-0.125,33.33333,1.125);
   pp2->SetFillColor(0);
   pp2->SetBorderMode(0);
   pp2->SetBorderSize(2);
   pp2->SetLeftMargin(0);
   pp2->SetFrameBorderMode(0);
   pp2->SetFrameBorderMode(0);
   
   TH1D *h1__10 = new TH1D("h1__10","",1,0,30);
   h1__10->SetBinContent(1,0.1113504);
   h1__10->SetBinError(1,0.02378865);
   h1__10->SetMinimum(0);
   h1__10->SetMaximum(1);
   h1__10->SetEntries(1);
   h1__10->SetStats(0);

   ci = TColor::GetColor("#000099");
   h1__10->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h1__10->SetMarkerColor(ci);
   h1__10->SetMarkerStyle(4);
   h1__10->GetXaxis()->SetBinLabel(1,"Int.");
   h1__10->GetXaxis()->SetLabelFont(42);
   h1__10->GetXaxis()->SetLabelSize(0.18);
   h1__10->GetXaxis()->SetTickLength(0);
   h1__10->GetXaxis()->SetTitleOffset(1);
   h1__10->GetXaxis()->SetTitleFont(42);
   h1__10->GetYaxis()->SetLabelFont(42);
   h1__10->GetYaxis()->SetLabelSize(0);
   h1__10->GetYaxis()->SetTickLength(0.08);
   h1__10->GetYaxis()->SetTitleFont(42);
   h1__10->GetZaxis()->SetLabelFont(42);
   h1__10->GetZaxis()->SetTitleOffset(1);
   h1__10->GetZaxis()->SetTitleFont(42);
   h1__10->Draw("");
   pp2->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
