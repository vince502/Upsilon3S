void plot_RAA_nS()
{
//=========Macro generated from canvas: c2/
//=========  (Mon Sep  6 15:33:08 2021) by ROOT version 6.22/06
   TCanvas *c2 = new TCanvas("c2", "",0,0,1000,700);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c2->Range(0,0,1,1);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: p21
   TPad *p21 = new TPad("p21", "",0,0,0.83,1);
   p21->Draw();
   p21->cd();
   p21->Range(-46.97,-0.1625,422.73,1.4625);
   p21->SetFillColor(0);
   p21->SetBorderMode(0);
   p21->SetBorderSize(2);
   p21->SetTickx(1);
   p21->SetTicky(1);
   p21->SetRightMargin(0);
   p21->SetFrameBorderMode(0);
   p21->SetFrameBorderMode(0);
   
   Double_t RAAcent_1S_fx3001[10] = {
   8.3,
   30.6,
   53.9,
   87,
   131.4,
   189.2,
   264.2,
   333.3,
   384.3,
   0};
   Double_t RAAcent_1S_fy3001[10] = {
   0.792,
   0.922,
   0.609,
   0.524,
   0.485,
   0.402,
   0.324,
   0.321,
   0.319,
   0};
   Double_t RAAcent_1S_felx3001[10] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t RAAcent_1S_fely3001[10] = {
   0.131,
   0.088,
   0.053,
   0.036,
   0.027,
   0.039,
   0.017,
   0.021,
   0.019,
   0};
   Double_t RAAcent_1S_fehx3001[10] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t RAAcent_1S_fehy3001[10] = {
   0.131,
   0.088,
   0.053,
   0.036,
   0.027,
   0.039,
   0.017,
   0.021,
   0.019,
   0};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(10,RAAcent_1S_fx3001,RAAcent_1S_fy3001,RAAcent_1S_felx3001,RAAcent_1S_fehx3001,RAAcent_1S_fely3001,RAAcent_1S_fehy3001);
   grae->SetName("RAAcent_1S");
   grae->SetTitle("Graph");
   grae->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#660000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#660000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_RAAcent_1S3001 = new TH1F("Graph_RAAcent_1S3001","Graph",100,0,422.73);
   Graph_RAAcent_1S3001->SetMinimum(0);
   Graph_RAAcent_1S3001->SetMaximum(1.3);
   Graph_RAAcent_1S3001->SetDirectory(0);
   Graph_RAAcent_1S3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_RAAcent_1S3001->SetLineColor(ci);
   Graph_RAAcent_1S3001->GetXaxis()->SetLabelFont(42);
   Graph_RAAcent_1S3001->GetXaxis()->SetTitleOffset(1);
   Graph_RAAcent_1S3001->GetXaxis()->SetTitleFont(42);
   Graph_RAAcent_1S3001->GetYaxis()->SetLabelFont(42);
   Graph_RAAcent_1S3001->GetYaxis()->SetTitleFont(42);
   Graph_RAAcent_1S3001->GetZaxis()->SetLabelFont(42);
   Graph_RAAcent_1S3001->GetZaxis()->SetTitleOffset(1);
   Graph_RAAcent_1S3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_RAAcent_1S3001);
   
   grae->Draw("ape");
   
   TH1D *RAAcent_2S__1 = new TH1D("RAAcent_2S__1","PbPb 2 ratio cent",35,0,420);
   RAAcent_2S__1->SetBinContent(1,1.000763);
   RAAcent_2S__1->SetBinContent(3,0.4692493);
   RAAcent_2S__1->SetBinContent(5,0.2684407);
   RAAcent_2S__1->SetBinContent(8,0.1481288);
   RAAcent_2S__1->SetBinContent(11,0.1710891);
   RAAcent_2S__1->SetBinContent(16,0.1268126);
   RAAcent_2S__1->SetBinContent(22,0.07571438);
   RAAcent_2S__1->SetBinContent(28,0.06814327);
   RAAcent_2S__1->SetBinContent(32,0.04742893);
   RAAcent_2S__1->SetBinError(1,0.1930153);
   RAAcent_2S__1->SetBinError(3,0.1055491);
   RAAcent_2S__1->SetBinError(5,0.0723821);
   RAAcent_2S__1->SetBinError(8,0.05559569);
   RAAcent_2S__1->SetBinError(11,0.04550774);
   RAAcent_2S__1->SetBinError(16,0.03673264);
   RAAcent_2S__1->SetBinError(22,0.0316515);
   RAAcent_2S__1->SetBinError(28,0.04112928);
   RAAcent_2S__1->SetBinError(32,0.03699921);
   RAAcent_2S__1->SetMinimum(0);
   RAAcent_2S__1->SetMaximum(1.3);
   RAAcent_2S__1->SetEntries(9);

   ci = TColor::GetColor("#000099");
   RAAcent_2S__1->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   RAAcent_2S__1->SetMarkerColor(ci);
   RAAcent_2S__1->SetMarkerStyle(4);
   RAAcent_2S__1->GetXaxis()->SetTitle("N_{part}");
   RAAcent_2S__1->GetXaxis()->CenterTitle(true);
   RAAcent_2S__1->GetXaxis()->SetLabelFont(42);
   RAAcent_2S__1->GetXaxis()->SetLabelSize(0.04);
   RAAcent_2S__1->GetXaxis()->SetTitleOffset(1.2);
   RAAcent_2S__1->GetXaxis()->SetTitleFont(42);
   RAAcent_2S__1->GetYaxis()->SetTitle("R_{AA}");
   RAAcent_2S__1->GetYaxis()->CenterTitle(true);
   RAAcent_2S__1->GetYaxis()->SetLabelFont(42);
   RAAcent_2S__1->GetYaxis()->SetTitleSize(0.04);
   RAAcent_2S__1->GetYaxis()->SetTitleOffset(1.1);
   RAAcent_2S__1->GetYaxis()->SetTitleFont(42);
   RAAcent_2S__1->GetZaxis()->SetLabelFont(42);
   RAAcent_2S__1->GetZaxis()->SetTitleOffset(1);
   RAAcent_2S__1->GetZaxis()->SetTitleFont(42);
   RAAcent_2S__1->Draw("same");
   
   TH1D *RAAcent_3S__2 = new TH1D("RAAcent_3S__2","PbPb 2 ratio cent",35,0,420);
   RAAcent_3S__2->SetBinContent(3,0.5134596);
   RAAcent_3S__2->SetBinContent(12,0.1292691);
   RAAcent_3S__2->SetBinContent(26,0.1274464);
   RAAcent_3S__2->SetBinError(3,0.1038328);
   RAAcent_3S__2->SetBinError(12,0.04274275);
   RAAcent_3S__2->SetBinError(26,0.03117786);
   RAAcent_3S__2->SetMinimum(0);
   RAAcent_3S__2->SetMaximum(1.3);
   RAAcent_3S__2->SetEntries(3);
   RAAcent_3S__2->SetStats(0);

   ci = TColor::GetColor("#009900");
   RAAcent_3S__2->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   RAAcent_3S__2->SetMarkerColor(ci);
   RAAcent_3S__2->SetMarkerStyle(4);
   RAAcent_3S__2->GetXaxis()->SetTitle("N_{part}");
   RAAcent_3S__2->GetXaxis()->CenterTitle(true);
   RAAcent_3S__2->GetXaxis()->SetLabelFont(42);
   RAAcent_3S__2->GetXaxis()->SetLabelSize(0.04);
   RAAcent_3S__2->GetXaxis()->SetTitleOffset(1.2);
   RAAcent_3S__2->GetXaxis()->SetTitleFont(42);
   RAAcent_3S__2->GetYaxis()->SetTitle("R_{AA}");
   RAAcent_3S__2->GetYaxis()->CenterTitle(true);
   RAAcent_3S__2->GetYaxis()->SetLabelFont(42);
   RAAcent_3S__2->GetYaxis()->SetTitleSize(0.04);
   RAAcent_3S__2->GetYaxis()->SetTitleOffset(1.1);
   RAAcent_3S__2->GetYaxis()->SetTitleFont(42);
   RAAcent_3S__2->GetZaxis()->SetLabelFont(42);
   RAAcent_3S__2->GetZaxis()->SetTitleOffset(1);
   RAAcent_3S__2->GetZaxis()->SetTitleFont(42);
   RAAcent_3S__2->Draw("same");
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
   
   TLegend *leg = new TLegend(0.65,0.4,0.85,0.7,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("RAAcent_1S","#varUpsilon(1S) HIN-16-023","pl");

   ci = TColor::GetColor("#660000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#660000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("RAAcent_2S","#varUpsilon(2S)","pl");

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000099");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(4);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("RAAcent_3S","#varUpsilon(3S)","pl");

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
   p21->Modified();
   c2->cd();
  
// ------------>Primitives in pad: p22
   TPad *p22 = new TPad("p22", "",0.83,0,1,1);
   p22->Draw();
   p22->cd();
   p22->Range(0,-0.1625,1.111111,1.4625);
   p22->SetFillColor(0);
   p22->SetBorderMode(0);
   p22->SetBorderSize(2);
   p22->SetTickx(1);
   p22->SetTicky(1);
   p22->SetLeftMargin(0);
   p22->SetFrameBorderMode(0);
   p22->SetFrameBorderMode(0);
   
   TH1D *y1int__3 = new TH1D("y1int__3","",3,0,1);
   y1int__3->SetBinContent(1,0.376);
   y1int__3->SetBinError(1,0.03733631);
   y1int__3->SetMinimum(0);
   y1int__3->SetMaximum(1.3);
   y1int__3->SetEntries(1);

   ci = TColor::GetColor("#990000");
   y1int__3->SetLineColor(ci);

   ci = TColor::GetColor("#990000");
   y1int__3->SetMarkerColor(ci);
   y1int__3->SetMarkerStyle(20);
   y1int__3->GetXaxis()->SetBinLabel(2,"Int.");
   y1int__3->GetXaxis()->SetLabelFont(42);
   y1int__3->GetXaxis()->SetLabelSize(0.12);
   y1int__3->GetXaxis()->SetTitleOffset(1);
   y1int__3->GetXaxis()->SetTitleFont(42);
   y1int__3->GetYaxis()->SetLabelFont(42);
   y1int__3->GetYaxis()->SetLabelOffset(0);
   y1int__3->GetYaxis()->SetLabelSize(0);
   y1int__3->GetYaxis()->SetTitleFont(42);
   y1int__3->GetZaxis()->SetLabelFont(42);
   y1int__3->GetZaxis()->SetTitleOffset(1);
   y1int__3->GetZaxis()->SetTitleFont(42);
   y1int__3->Draw("");
   
   TH1D *y2int__4 = new TH1D("y2int__4","",3,0,1);
   y2int__4->SetBinContent(2,0.09773845);
   y2int__4->SetBinError(2,0.01682987);
   y2int__4->SetMinimum(0);
   y2int__4->SetMaximum(1.3);
   y2int__4->SetEntries(1);

   ci = TColor::GetColor("#000099");
   y2int__4->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   y2int__4->SetMarkerColor(ci);
   y2int__4->SetMarkerStyle(4);
   y2int__4->GetXaxis()->SetLabelFont(42);
   y2int__4->GetXaxis()->SetLabelSize(0.12);
   y2int__4->GetXaxis()->SetTitleOffset(1);
   y2int__4->GetXaxis()->SetTitleFont(42);
   y2int__4->GetYaxis()->SetLabelFont(42);
   y2int__4->GetYaxis()->SetLabelOffset(0);
   y2int__4->GetYaxis()->SetLabelSize(0);
   y2int__4->GetYaxis()->SetTitleFont(42);
   y2int__4->GetZaxis()->SetLabelFont(42);
   y2int__4->GetZaxis()->SetTitleOffset(1);
   y2int__4->GetZaxis()->SetTitleFont(42);
   y2int__4->Draw("same");
   
   TH1D *y3int__5 = new TH1D("y3int__5","",3,0,1);
   y3int__5->SetBinContent(3,0.1104473);
   y3int__5->SetBinError(3,0.02608092);
   y3int__5->SetMinimum(0);
   y3int__5->SetMaximum(1.3);
   y3int__5->SetEntries(1);

   ci = TColor::GetColor("#009900");
   y3int__5->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   y3int__5->SetMarkerColor(ci);
   y3int__5->SetMarkerStyle(4);
   y3int__5->GetXaxis()->SetLabelFont(42);
   y3int__5->GetXaxis()->SetLabelSize(0.12);
   y3int__5->GetXaxis()->SetTitleOffset(1);
   y3int__5->GetXaxis()->SetTitleFont(42);
   y3int__5->GetYaxis()->SetLabelFont(42);
   y3int__5->GetYaxis()->SetLabelOffset(0);
   y3int__5->GetYaxis()->SetLabelSize(0);
   y3int__5->GetYaxis()->SetTitleFont(42);
   y3int__5->GetZaxis()->SetLabelFont(42);
   y3int__5->GetZaxis()->SetTitleOffset(1);
   y3int__5->GetZaxis()->SetTitleFont(42);
   y3int__5->Draw("same");
   p22->Modified();
   c2->cd();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
