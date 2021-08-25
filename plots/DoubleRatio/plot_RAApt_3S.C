void plot_RAApt_3S()
{
//=========Macro generated from canvas: c2/
//=========  (Fri Aug 20 01:43:18 2021) by ROOT version 6.22/06
   TCanvas *c2 = new TCanvas("c2", "",392,1463,1000,700);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c2->Range(-3.75,-0.1625,33.75,1.4625);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
   c2->SetFrameBorderMode(0);
   Double_t xAxis1[3] = {0, 6, 30}; 
   
   TH1D *h1pt__1 = new TH1D("h1pt__1","PbPb 2 ratio cent",2, xAxis1);
   h1pt__1->SetBinContent(1,0.0877282);
   h1pt__1->SetBinContent(2,0.07902583);
   h1pt__1->SetBinError(1,0.05229863);
   h1pt__1->SetBinError(2,0.02047334);
   h1pt__1->SetMinimum(0);
   h1pt__1->SetMaximum(1.3);
   h1pt__1->SetEntries(2);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#009900");
   h1pt__1->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   h1pt__1->SetMarkerColor(ci);
   h1pt__1->SetMarkerStyle(4);
   h1pt__1->GetXaxis()->SetTitle("N_{part}");
   h1pt__1->GetXaxis()->CenterTitle(true);
   h1pt__1->GetXaxis()->SetLabelFont(42);
   h1pt__1->GetXaxis()->SetLabelSize(0.04);
   h1pt__1->GetXaxis()->SetTitleOffset(1.2);
   h1pt__1->GetXaxis()->SetTitleFont(42);
   h1pt__1->GetYaxis()->SetTitle("#Upsilon (3S) R_{AA}");
   h1pt__1->GetYaxis()->CenterTitle(true);
   h1pt__1->GetYaxis()->SetLabelFont(42);
   h1pt__1->GetYaxis()->SetTitleSize(0.04);
   h1pt__1->GetYaxis()->SetTitleOffset(1.1);
   h1pt__1->GetYaxis()->SetTitleFont(42);
   h1pt__1->GetZaxis()->SetLabelFont(42);
   h1pt__1->GetZaxis()->SetTitleOffset(1);
   h1pt__1->GetZaxis()->SetTitleFont(42);
   h1pt__1->Draw("");
   Double_t xAxis2[4] = {0, 4, 9, 30}; 
   
   TH1D *h1pt__2 = new TH1D("h1pt__2","PbPb 2 ratio cent",3, xAxis2);
   h1pt__2->SetBinContent(1,0.07567129);
   h1pt__2->SetBinContent(2,0.1718375);
   h1pt__2->SetBinContent(3,0.07656519);
   h1pt__2->SetBinError(1,0.03288872);
   h1pt__2->SetBinError(2,0.02836988);
   h1pt__2->SetBinError(3,0.01190895);
   h1pt__2->SetMinimum(0);
   h1pt__2->SetMaximum(1.3);
   h1pt__2->SetEntries(3);
   h1pt__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   h1pt__2->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   h1pt__2->SetMarkerColor(ci);
   h1pt__2->SetMarkerStyle(4);
   h1pt__2->GetXaxis()->SetTitle("N_{part}");
   h1pt__2->GetXaxis()->CenterTitle(true);
   h1pt__2->GetXaxis()->SetLabelFont(42);
   h1pt__2->GetXaxis()->SetLabelSize(0.04);
   h1pt__2->GetXaxis()->SetTitleOffset(1.2);
   h1pt__2->GetXaxis()->SetTitleFont(42);
   h1pt__2->GetYaxis()->SetTitle("#Upsilon (2S) R_{AA}");
   h1pt__2->GetYaxis()->CenterTitle(true);
   h1pt__2->GetYaxis()->SetLabelFont(42);
   h1pt__2->GetYaxis()->SetTitleSize(0.04);
   h1pt__2->GetYaxis()->SetTitleOffset(1.1);
   h1pt__2->GetYaxis()->SetTitleFont(42);
   h1pt__2->GetZaxis()->SetLabelFont(42);
   h1pt__2->GetZaxis()->SetTitleOffset(1);
   h1pt__2->GetZaxis()->SetTitleFont(42);
   h1pt__2->Draw("same");
   
   TLegend *leg = new TLegend(0.65,0.4,0.85,0.7,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h1pt","#varUpsilon(2S)","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000099");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(4);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h1pt","#varUpsilon(3S)","pl");

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
