void plot_DoubleRatio_3S()
{
//=========Macro generated from canvas: c3/
//=========  (Thu Aug  5 18:29:59 2021) by ROOT version 6.22/06
   TCanvas *c3 = new TCanvas("c3", "",392,1463,900,700);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c3->Range(0,0,1,1);
   c3->SetFillColor(0);
   c3->SetBorderMode(0);
   c3->SetBorderSize(2);
   c3->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p31
   TPad *p31 = new TPad("p31", "",0.05,0,0.83,1);
   p31->Draw();
   p31->cd();
   p31->Range(-46.66667,-0.2,420,1.8);
   p31->SetFillColor(0);
   p31->SetBorderMode(0);
   p31->SetBorderSize(2);
   p31->SetRightMargin(0);
   p31->SetFrameBorderMode(0);
   p31->SetFrameBorderMode(0);
   
   TH1D *h2__3 = new TH1D("h2__3","PbPb 3S double ratio cent",70,0,420);
   h2__3->SetBinContent(5,1.133067);
   h2__3->SetBinContent(23,0.3494875);
   h2__3->SetBinContent(52,0.3711624);
   h2__3->SetBinError(5,0.2528735);
   h2__3->SetBinError(23,0.1182116);
   h2__3->SetBinError(52,0.1344513);
   h2__3->SetMinimum(0);
   h2__3->SetMaximum(1.6);
   h2__3->SetEntries(3);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#009900");
   h2__3->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   h2__3->SetMarkerColor(ci);
   h2__3->SetMarkerStyle(4);
   h2__3->GetXaxis()->SetTitle("N_{part}");
   h2__3->GetXaxis()->CenterTitle(true);
   h2__3->GetXaxis()->SetLabelFont(42);
   h2__3->GetXaxis()->SetLabelSize(0.04);
   h2__3->GetXaxis()->SetTitleOffset(1.1);
   h2__3->GetXaxis()->SetTitleFont(42);
   h2__3->GetYaxis()->SetTitle("(#Upsilon(3S)/#Upsilon(1S))_{PbPb} / #Upsilon(3S)/#Upsilon(1S))_{pp}");
   h2__3->GetYaxis()->CenterTitle(true);
   h2__3->GetYaxis()->SetLabelFont(42);
   h2__3->GetYaxis()->SetTitleSize(0.04);
   h2__3->GetYaxis()->SetTitleOffset(1.2);
   h2__3->GetYaxis()->SetTitleFont(42);
   h2__3->GetZaxis()->SetLabelFont(42);
   h2__3->GetZaxis()->SetTitleOffset(1);
   h2__3->GetZaxis()->SetTitleFont(42);
   h2__3->Draw("");
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
   p31->Modified();
   c3->cd();
  
// ------------>Primitives in pad: p32
   TPad *p32 = new TPad("p32", "",0.83,0,1,1);
   p32->Draw();
   p32->cd();
   p32->Range(0,-0.2,1.111111,1.8);
   p32->SetFillColor(0);
   p32->SetBorderMode(0);
   p32->SetBorderSize(2);
   p32->SetLeftMargin(0);
   p32->SetFrameBorderMode(0);
   p32->SetFrameBorderMode(0);
   
   TH1D *y3int__4 = new TH1D("y3int__4","",1,0,1);
   y3int__4->SetBinContent(1,0.3802665);
   y3int__4->SetBinError(1,0.08990653);
   y3int__4->SetMinimum(0);
   y3int__4->SetMaximum(1.6);
   y3int__4->SetEntries(1);

   ci = TColor::GetColor("#009900");
   y3int__4->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   y3int__4->SetMarkerColor(ci);
   y3int__4->SetMarkerStyle(4);
   y3int__4->GetXaxis()->SetBinLabel(1,"Integrated");
   y3int__4->GetXaxis()->SetLabelFont(42);
   y3int__4->GetXaxis()->SetLabelSize(0.17);
   y3int__4->GetXaxis()->SetTitleOffset(1);
   y3int__4->GetXaxis()->SetTitleFont(42);
   y3int__4->GetYaxis()->SetLabelFont(42);
   y3int__4->GetYaxis()->SetLabelOffset(0);
   y3int__4->GetYaxis()->SetLabelSize(0);
   y3int__4->GetYaxis()->SetTickLength(0);
   y3int__4->GetYaxis()->SetTitleFont(42);
   y3int__4->GetZaxis()->SetLabelFont(42);
   y3int__4->GetZaxis()->SetTitleOffset(1);
   y3int__4->GetZaxis()->SetTitleFont(42);
   y3int__4->Draw("");
   p32->Modified();
   c3->cd();
   c3->Modified();
   c3->cd();
   c3->SetSelected(c3);
}
