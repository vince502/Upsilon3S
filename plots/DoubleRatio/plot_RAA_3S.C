void plot_RAA_3S()
{
//=========Macro generated from canvas: c3/
//=========  (Mon Sep  6 15:33:08 2021) by ROOT version 6.22/06
   TCanvas *c3 = new TCanvas("c3", "",0,0,1000,700);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c3->Range(0,0,1,1);
   c3->SetFillColor(0);
   c3->SetBorderMode(0);
   c3->SetBorderSize(2);
   c3->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p31
   TPad *p31 = new TPad("p31", "",0,0,0.83,1);
   p31->Draw();
   p31->cd();
   p31->Range(-46.66667,-0.1625,420,1.4625);
   p31->SetFillColor(0);
   p31->SetBorderMode(0);
   p31->SetBorderSize(2);
   p31->SetRightMargin(0);
   p31->SetFrameBorderMode(0);
   p31->SetFrameBorderMode(0);
   
   TH1D *RAAcent_3S__6 = new TH1D("RAAcent_3S__6","PbPb 2 ratio cent",35,0,420);
   RAAcent_3S__6->SetBinContent(3,0.5134596);
   RAAcent_3S__6->SetBinContent(12,0.1292691);
   RAAcent_3S__6->SetBinContent(26,0.1274464);
   RAAcent_3S__6->SetBinError(3,0.1038328);
   RAAcent_3S__6->SetBinError(12,0.04274275);
   RAAcent_3S__6->SetBinError(26,0.03117786);
   RAAcent_3S__6->SetMinimum(0);
   RAAcent_3S__6->SetMaximum(1.3);
   RAAcent_3S__6->SetEntries(3);
   RAAcent_3S__6->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#009900");
   RAAcent_3S__6->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   RAAcent_3S__6->SetMarkerColor(ci);
   RAAcent_3S__6->SetMarkerStyle(4);
   RAAcent_3S__6->GetXaxis()->SetTitle("N_{part}");
   RAAcent_3S__6->GetXaxis()->CenterTitle(true);
   RAAcent_3S__6->GetXaxis()->SetLabelFont(42);
   RAAcent_3S__6->GetXaxis()->SetLabelSize(0.04);
   RAAcent_3S__6->GetXaxis()->SetTitleOffset(1.2);
   RAAcent_3S__6->GetXaxis()->SetTitleFont(42);
   RAAcent_3S__6->GetYaxis()->SetTitle("R_{AA}");
   RAAcent_3S__6->GetYaxis()->CenterTitle(true);
   RAAcent_3S__6->GetYaxis()->SetLabelFont(42);
   RAAcent_3S__6->GetYaxis()->SetTitleSize(0.04);
   RAAcent_3S__6->GetYaxis()->SetTitleOffset(1.1);
   RAAcent_3S__6->GetYaxis()->SetTitleFont(42);
   RAAcent_3S__6->GetZaxis()->SetLabelFont(42);
   RAAcent_3S__6->GetZaxis()->SetTitleOffset(1);
   RAAcent_3S__6->GetZaxis()->SetTitleFont(42);
   RAAcent_3S__6->Draw("");
   TLatex *   tex = new TLatex(0.2,0.8,"p^{#mu#mu}_{T} < 30 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.2,0.75,"|y| < 2.4");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.2,0.7,"p^{#mu}_{T} < 4 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.65,0.4,0.85,0.7,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("RAAcent_3S","#varUpsilon(3S)","pl");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(4);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
      tex = new TLatex(1,0.9196,"PbPb 1.6 nb^{-1} (5.02 TeV)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.0498);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.9495,0.868405,"CMS");
tex->SetNDC();
   tex->SetTextAlign(33);
   tex->SetTextFont(61);
   tex->SetTextSize(0.06225);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.9495,0.793705,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(33);
   tex->SetTextFont(52);
   tex->SetTextSize(0.04731);
   tex->SetLineWidth(2);
   tex->Draw();
   p31->Modified();
   c3->cd();
  
// ------------>Primitives in pad: p32
   TPad *p32 = new TPad("p32", "",0.83,0,1,1);
   p32->Draw();
   p32->cd();
   p32->Range(0,-0.1625,1.111111,1.4625);
   p32->SetFillColor(0);
   p32->SetBorderMode(0);
   p32->SetBorderSize(2);
   p32->SetLeftMargin(0);
   p32->SetFrameBorderMode(0);
   p32->SetFrameBorderMode(0);
   
   TH1D *y3int__7 = new TH1D("y3int__7","",3,0,1);
   y3int__7->SetBinContent(3,0.1104473);
   y3int__7->SetBinError(3,0.02608092);
   y3int__7->SetMinimum(0);
   y3int__7->SetMaximum(1.3);
   y3int__7->SetEntries(1);

   ci = TColor::GetColor("#009900");
   y3int__7->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   y3int__7->SetMarkerColor(ci);
   y3int__7->SetMarkerStyle(4);
   y3int__7->GetXaxis()->SetLabelFont(42);
   y3int__7->GetXaxis()->SetLabelSize(0.12);
   y3int__7->GetXaxis()->SetTitleOffset(1);
   y3int__7->GetXaxis()->SetTitleFont(42);
   y3int__7->GetYaxis()->SetLabelFont(42);
   y3int__7->GetYaxis()->SetLabelOffset(0);
   y3int__7->GetYaxis()->SetLabelSize(0);
   y3int__7->GetYaxis()->SetTitleFont(42);
   y3int__7->GetZaxis()->SetLabelFont(42);
   y3int__7->GetZaxis()->SetTitleOffset(1);
   y3int__7->GetZaxis()->SetTitleFont(42);
   y3int__7->Draw("");
   p32->Modified();
   c3->cd();
   c3->Modified();
   c3->cd();
   c3->SetSelected(c3);
}
