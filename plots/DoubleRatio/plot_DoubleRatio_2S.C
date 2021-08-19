void plot_DoubleRatio_2S()
{
//=========Macro generated from canvas: c2/
//=========  (Thu Aug  5 18:29:57 2021) by ROOT version 6.22/06
   TCanvas *c2 = new TCanvas("c2", "",392,1463,900,700);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c2->Range(0,0,1,1);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p21
   TPad *p21 = new TPad("p21", "",0.05,0,0.83,1);
   p21->Draw();
   p21->cd();
   p21->Range(-46.66667,-0.2,420,1.8);
   p21->SetFillColor(0);
   p21->SetBorderMode(0);
   p21->SetBorderSize(2);
   p21->SetRightMargin(0);
   p21->SetFrameBorderMode(0);
   p21->SetFrameBorderMode(0);
   
   TH1D *h1__1 = new TH1D("h1__1","PbPb 2S double ratio cent",70,0,420);
   h1__1->SetBinContent(2,1.419948);
   h1__1->SetBinContent(6,0.8058873);
   h1__1->SetBinContent(10,0.5725678);
   h1__1->SetBinContent(15,0.09481222);
   h1__1->SetBinContent(22,0.5058599);
   h1__1->SetBinContent(32,0.3026347);
   h1__1->SetBinContent(44,0.3015798);
   h1__1->SetBinContent(56,0.1507403);
   h1__1->SetBinContent(64,0.3775108);
   h1__1->SetBinError(2,0.376643);
   h1__1->SetBinError(6,0.2474721);
   h1__1->SetBinError(10,0.2087344);
   h1__1->SetBinError(15,0.1761485);
   h1__1->SetBinError(22,0.1220454);
   h1__1->SetBinError(32,0.1405931);
   h1__1->SetBinError(44,0.1275729);
   h1__1->SetBinError(56,0.1388797);
   h1__1->SetBinError(64,0.2675847);
   h1__1->SetMinimum(0);
   h1__1->SetMaximum(1.6);
   h1__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1__1->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   h1__1->SetMarkerColor(ci);
   h1__1->SetMarkerStyle(4);
   h1__1->GetXaxis()->SetTitle("N_{part}");
   h1__1->GetXaxis()->CenterTitle(true);
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetLabelSize(0.04);
   h1__1->GetXaxis()->SetTitleOffset(1.1);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetTitle("(#Upsilon(2S)/#Upsilon(1S))_{PbPb} / #Upsilon(2S)/#Upsilon(1S))_{pp}");
   h1__1->GetYaxis()->CenterTitle(true);
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetTitleSize(0.04);
   h1__1->GetYaxis()->SetTitleOffset(1.2);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("");
   TLatex *   tex = new TLatex(0.2,0.8,"p_{T} < 30 GeV/c");
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
      tex = new TLatex(0.9495,0.793705,"Internal");
tex->SetNDC();
   tex->SetTextAlign(33);
   tex->SetTextFont(52);
   tex->SetTextSize(0.04731);
   tex->SetLineWidth(2);
   tex->Draw();
   p21->Modified();
   c2->cd();
  
// ------------>Primitives in pad: p22
   TPad *p22 = new TPad("p22", "",0.83,0,1,1);
   p22->Draw();
   p22->cd();
   p22->Range(0,-0.2,1.111111,1.8);
   p22->SetFillColor(0);
   p22->SetBorderMode(0);
   p22->SetBorderSize(2);
   p22->SetLeftMargin(0);
   p22->SetFrameBorderMode(0);
   p22->SetFrameBorderMode(0);
   
   TH1D *y2int__2 = new TH1D("y2int__2","",1,0,1);
   y2int__2->SetBinContent(1,0.2872997);
   y2int__2->SetBinError(1,0.05882154);
   y2int__2->SetMinimum(0);
   y2int__2->SetMaximum(1.6);
   y2int__2->SetEntries(1);

   ci = TColor::GetColor("#000099");
   y2int__2->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   y2int__2->SetMarkerColor(ci);
   y2int__2->SetMarkerStyle(4);
   y2int__2->GetXaxis()->SetBinLabel(1,"Integrated");
   y2int__2->GetXaxis()->SetLabelFont(42);
   y2int__2->GetXaxis()->SetLabelSize(0.17);
   y2int__2->GetXaxis()->SetTitleOffset(1);
   y2int__2->GetXaxis()->SetTitleFont(42);
   y2int__2->GetYaxis()->SetLabelFont(42);
   y2int__2->GetYaxis()->SetLabelOffset(0);
   y2int__2->GetYaxis()->SetLabelSize(0);
   y2int__2->GetYaxis()->SetTickLength(0);
   y2int__2->GetYaxis()->SetTitleFont(42);
   y2int__2->GetZaxis()->SetLabelFont(42);
   y2int__2->GetZaxis()->SetTitleOffset(1);
   y2int__2->GetZaxis()->SetTitleFont(42);
   y2int__2->Draw("");
   p22->Modified();
   c2->cd();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
