void res_pt_RAA_0702()
{
//=========Macro generated from canvas: c1_n8/c1_n8
//=========  (Fri Jul  2 15:32:50 2021) by ROOT version 6.22/06
   TCanvas *c1_n8 = new TCanvas("c1_n8", "c1_n8",47,593,700,500);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c1_n8->Range(-3.75,-0.125,33.75,1.125);
   c1_n8->SetFillColor(0);
   c1_n8->SetBorderMode(0);
   c1_n8->SetBorderSize(2);
   c1_n8->SetFrameBorderMode(0);
   c1_n8->SetFrameBorderMode(0);
   
   TH1D *h1__6 = new TH1D("h1__6","PbPb 2 ratio cent",10,0,30);
   h1__6->SetBinContent(2,0.09588443);
   h1__6->SetBinContent(7,0.1044769);
   h1__6->SetBinError(2,0.04908685);
   h1__6->SetBinError(7,0.02307131);
   h1__6->SetMinimum(0);
   h1__6->SetMaximum(1);
   h1__6->SetEntries(2);
   h1__6->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#0000ff");
   h1__6->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h1__6->SetMarkerColor(ci);
   h1__6->SetMarkerStyle(4);
   h1__6->GetXaxis()->SetTitle("N_{part}");
   h1__6->GetXaxis()->SetLabelFont(42);
   h1__6->GetXaxis()->SetLabelSize(0.04);
   h1__6->GetXaxis()->SetTitleOffset(1.2);
   h1__6->GetXaxis()->SetTitleFont(42);
   h1__6->GetYaxis()->SetTitle("R_{AA}");
   h1__6->GetYaxis()->SetLabelFont(42);
   h1__6->GetYaxis()->SetTitleSize(0.05);
   h1__6->GetYaxis()->SetTitleOffset(0.9);
   h1__6->GetYaxis()->SetTitleFont(42);
   h1__6->GetZaxis()->SetLabelFont(42);
   h1__6->GetZaxis()->SetTitleOffset(1);
   h1__6->GetZaxis()->SetTitleFont(42);
   h1__6->Draw("");
  
// ------------>Primitives in pad: c1_n8_1
   TPad *c1_n8_1 = new TPad("c1_n8_1", "c1_n8_1",0.01,0.01,0.49,0.99);
   c1_n8_1->Draw();
   c1_n8_1->cd();
   c1_n8_1->Range(0,0,1,1);
   c1_n8_1->SetFillColor(0);
   c1_n8_1->SetBorderMode(0);
   c1_n8_1->SetBorderSize(2);
   c1_n8_1->SetFrameBorderMode(0);
   c1_n8_1->Modified();
   c1_n8->cd();
  
// ------------>Primitives in pad: c1_n8_2
   TPad *c1_n8_2 = new TPad("c1_n8_2", "c1_n8_2",0.51,0.01,0.99,0.99);
   c1_n8_2->Draw();
   c1_n8_2->cd();
   c1_n8_2->Range(0,0,1,1);
   c1_n8_2->SetFillColor(0);
   c1_n8_2->SetBorderMode(0);
   c1_n8_2->SetBorderSize(2);
   c1_n8_2->SetFrameBorderMode(0);
   c1_n8_2->Modified();
   c1_n8->cd();
  
// ------------>Primitives in pad: c1_n8_1
   TPad *c1_n8_1 = new TPad("c1_n8_1", "c1_n8_1",0.01,0.01,0.99,0.99);
   c1_n8_1->Draw();
   c1_n8_1->cd();
   c1_n8_1->Range(0,0,1,1);
   c1_n8_1->SetFillColor(0);
   c1_n8_1->SetBorderMode(0);
   c1_n8_1->SetBorderSize(2);
   c1_n8_1->SetFrameBorderMode(0);
   c1_n8_1->Modified();
   c1_n8->cd();
  
// ------------>Primitives in pad: p2
   TPad *p2 = new TPad("p2", "",0.8,0,1,1);
   p2->Draw();
   p2->cd();
   p2->Range(0,-0.125,33.33333,1.125);
   p2->SetFillColor(0);
   p2->SetBorderMode(0);
   p2->SetBorderSize(2);
   p2->SetLeftMargin(0);
   p2->SetFrameBorderMode(0);
   p2->SetFrameBorderMode(0);
   
   TH1D *h1__7 = new TH1D("h1__7","",1,0,30);
   h1__7->SetBinContent(1,0.1113504);
   h1__7->SetBinError(1,0.02378865);
   h1__7->SetMinimum(0);
   h1__7->SetMaximum(1);
   h1__7->SetEntries(1);
   h1__7->SetStats(0);

   ci = TColor::GetColor("#000099");
   h1__7->SetLineColor(ci);
   h1__7->SetMarkerStyle(4);
   h1__7->SetMarkerSize(0.8);
   h1__7->GetXaxis()->SetBinLabel(1,"Int.");
   h1__7->GetXaxis()->SetLabelFont(42);
   h1__7->GetXaxis()->SetLabelSize(0.18);
   h1__7->GetXaxis()->SetTickLength(0);
   h1__7->GetXaxis()->SetTitleOffset(1);
   h1__7->GetXaxis()->SetTitleFont(42);
   h1__7->GetYaxis()->SetLabelFont(42);
   h1__7->GetYaxis()->SetLabelSize(0);
   h1__7->GetYaxis()->SetTickLength(0.08);
   h1__7->GetYaxis()->SetTitleFont(42);
   h1__7->GetZaxis()->SetLabelFont(42);
   h1__7->GetZaxis()->SetTitleOffset(1);
   h1__7->GetZaxis()->SetTitleFont(42);
   h1__7->Draw("");
   p2->Modified();
   c1_n8->cd();
  
// ------------>Primitives in pad: p1
   TPad *p1 = new TPad("p1", "",0,0,0.8,1);
   p1->Draw();
   p1->cd();
   p1->Range(-3.333333,-0.125,30,1.125);
   p1->SetFillColor(0);
   p1->SetBorderMode(0);
   p1->SetBorderSize(2);
   p1->SetRightMargin(0);
   p1->SetFrameBorderMode(0);
   p1->SetFrameBorderMode(0);
   
   TH1D *h1__8 = new TH1D("h1__8","PbPb 2 ratio cent",10,0,30);
   h1__8->SetBinContent(2,0.09588443);
   h1__8->SetBinContent(7,0.1044769);
   h1__8->SetBinError(2,0.04908685);
   h1__8->SetBinError(7,0.02307131);
   h1__8->SetMinimum(0);
   h1__8->SetMaximum(1);
   h1__8->SetEntries(2);
   h1__8->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   h1__8->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   h1__8->SetMarkerColor(ci);
   h1__8->SetMarkerStyle(4);
   h1__8->GetXaxis()->SetTitle("N_{part}");
   h1__8->GetXaxis()->SetLabelFont(42);
   h1__8->GetXaxis()->SetLabelSize(0.04);
   h1__8->GetXaxis()->SetTitleOffset(1.2);
   h1__8->GetXaxis()->SetTitleFont(42);
   h1__8->GetYaxis()->SetTitle("R_{AA}");
   h1__8->GetYaxis()->SetLabelFont(42);
   h1__8->GetYaxis()->SetTitleSize(0.05);
   h1__8->GetYaxis()->SetTitleOffset(0.9);
   h1__8->GetYaxis()->SetTitleFont(42);
   h1__8->GetZaxis()->SetLabelFont(42);
   h1__8->GetZaxis()->SetTitleOffset(1);
   h1__8->GetZaxis()->SetTitleFont(42);
   h1__8->Draw("");
   p1->Modified();
   c1_n8->cd();
   c1_n8->Modified();
   c1_n8->cd();
   c1_n8->SetSelected(c1_n8);
}
