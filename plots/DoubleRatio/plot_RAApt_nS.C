void plot_RAApt_nS()
{
//=========Macro generated from canvas: c2/
//=========  (Fri Oct  1 04:42:39 2021) by ROOT version 6.22/06
   TCanvas *c2 = new TCanvas("c2", "",0,0,700,700);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c2->Range(-3.75,-0.1625,33.75,1.4625);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
   c2->SetFrameBorderMode(0);
   Double_t xAxis1[3] = {0, 6, 30}; 
   
   TH1D *h3pt__1 = new TH1D("h3pt__1","PbPb 2 ratio cent 2S",2, xAxis1);
   h3pt__1->SetBinContent(1,0.07592996);
   h3pt__1->SetBinContent(2,0.07388216);
   h3pt__1->SetBinError(1,0.04842447);
   h3pt__1->SetBinError(2,0.03048804);
   h3pt__1->SetMinimum(0);
   h3pt__1->SetMaximum(1.3);
   h3pt__1->SetEntries(2);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#009900");
   h3pt__1->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   h3pt__1->SetMarkerColor(ci);
   h3pt__1->SetMarkerStyle(4);
   h3pt__1->GetXaxis()->SetTitle("p_{T}");
   h3pt__1->GetXaxis()->CenterTitle(true);
   h3pt__1->GetXaxis()->SetLabelFont(42);
   h3pt__1->GetXaxis()->SetLabelSize(0.04);
   h3pt__1->GetXaxis()->SetTitleSize(0.06);
   h3pt__1->GetXaxis()->SetTitleOffset(1.2);
   h3pt__1->GetXaxis()->SetTitleFont(42);
   h3pt__1->GetYaxis()->SetTitle("#Upsilon (3S) R_{AA}");
   h3pt__1->GetYaxis()->CenterTitle(true);
   h3pt__1->GetYaxis()->SetLabelFont(42);
   h3pt__1->GetYaxis()->SetTitleSize(0.06);
   h3pt__1->GetYaxis()->SetTitleOffset(1.1);
   h3pt__1->GetYaxis()->SetTitleFont(42);
   h3pt__1->GetZaxis()->SetLabelFont(42);
   h3pt__1->GetZaxis()->SetTitleOffset(1);
   h3pt__1->GetZaxis()->SetTitleFont(42);
   h3pt__1->Draw("");
   Double_t xAxis2[4] = {0, 4, 9, 30}; 
   
   TH1D *h2pt__2 = new TH1D("h2pt__2","PbPb 2 ratio cent 3S",3, xAxis2);
   h2pt__2->SetBinContent(1,0.06857919);
   h2pt__2->SetBinContent(2,0.1479398);
   h2pt__2->SetBinContent(3,0.08589855);
   h2pt__2->SetBinError(1,0.03250194);
   h2pt__2->SetBinError(2,0.03716405);
   h2pt__2->SetBinError(3,0.01921141);
   h2pt__2->SetMinimum(0);
   h2pt__2->SetMaximum(1.3);
   h2pt__2->SetEntries(3);
   h2pt__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   h2pt__2->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   h2pt__2->SetMarkerColor(ci);
   h2pt__2->SetMarkerStyle(4);
   h2pt__2->GetXaxis()->SetTitle("p_{T}");
   h2pt__2->GetXaxis()->CenterTitle(true);
   h2pt__2->GetXaxis()->SetLabelFont(42);
   h2pt__2->GetXaxis()->SetLabelSize(0.04);
   h2pt__2->GetXaxis()->SetTitleSize(0.06);
   h2pt__2->GetXaxis()->SetTitleOffset(1.2);
   h2pt__2->GetXaxis()->SetTitleFont(42);
   h2pt__2->GetYaxis()->SetTitle("#Upsilon (2S) R_{AA}");
   h2pt__2->GetYaxis()->CenterTitle(true);
   h2pt__2->GetYaxis()->SetLabelFont(42);
   h2pt__2->GetYaxis()->SetTitleSize(0.06);
   h2pt__2->GetYaxis()->SetTitleOffset(1.1);
   h2pt__2->GetYaxis()->SetTitleFont(42);
   h2pt__2->GetZaxis()->SetLabelFont(42);
   h2pt__2->GetZaxis()->SetTitleOffset(1);
   h2pt__2->GetZaxis()->SetTitleFont(42);
   h2pt__2->Draw("same");
   
   TLegend *leg = new TLegend(0.65,0.4,0.85,0.7,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h2pt","#varUpsilon(2S)","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000099");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(4);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h3pt","#varUpsilon(3S)","pl");

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
      tex = new TLatex(0.2,0.7,"p^{#mu}_{T} > 3.5 GeV/c");
tex->SetNDC();
   tex->SetTextFont(42);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.9,0.9196,"PbPb 1.6 nb^{-1} (5.02 TeV)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.0498);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.854,0.868405,"CMS");
tex->SetNDC();
   tex->SetTextAlign(33);
   tex->SetTextFont(61);
   tex->SetTextSize(0.06225);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.854,0.793705,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(33);
   tex->SetTextFont(52);
   tex->SetTextSize(0.04731);
   tex->SetLineWidth(2);
   tex->Draw();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
