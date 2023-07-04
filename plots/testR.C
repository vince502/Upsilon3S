void testR()
{
//=========Macro generated from canvas: c2/
//=========  (Fri Sep 10 20:13:05 2021) by ROOT version 6.22/06
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
   p21->Range(-46.66667,-0.1625,420,1.4625);
   p21->SetFillColor(0);
   p21->SetBorderMode(0);
   p21->SetBorderSize(2);
   p21->SetTickx(1);
   p21->SetTicky(1);
   p21->SetRightMargin(0);
   p21->SetFrameBorderMode(0);
   p21->SetFrameBorderMode(0);
   
   TH1D *RAAcent_2S__1 = new TH1D("RAAcent_2S__1","",420,0,420);
   RAAcent_2S__1->SetBinContent(12,1.000763);
   RAAcent_2S__1->SetBinContent(32,0.4692493);
   RAAcent_2S__1->SetBinContent(55,0.2684407);
   RAAcent_2S__1->SetBinContent(88,0.1481288);
   RAAcent_2S__1->SetBinContent(132,0.1710891);
   RAAcent_2S__1->SetBinContent(189,0.1268126);
   RAAcent_2S__1->SetBinContent(263,0.07571438);
   RAAcent_2S__1->SetBinContent(332,0.06814327);
   RAAcent_2S__1->SetBinContent(383,0.04742893);
   RAAcent_2S__1->SetBinError(12,0.1930153);
   RAAcent_2S__1->SetBinError(32,0.1055491);
   RAAcent_2S__1->SetBinError(55,0.0723821);
   RAAcent_2S__1->SetBinError(88,0.05559569);
   RAAcent_2S__1->SetBinError(132,0.04550774);
   RAAcent_2S__1->SetBinError(189,0.03673264);
   RAAcent_2S__1->SetBinError(263,0.0316515);
   RAAcent_2S__1->SetBinError(332,0.04112928);
   RAAcent_2S__1->SetBinError(383,0.03699921);
   RAAcent_2S__1->SetMinimum(0);
   RAAcent_2S__1->SetMaximum(1.3);
   RAAcent_2S__1->SetEntries(9);
   RAAcent_2S__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
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
   RAAcent_2S__1->Draw("");
   
   TH1D *RAAcent_3S__2 = new TH1D("RAAcent_3S__2","PbPb 2 ratio cent",420,0,420);
   RAAcent_3S__2->SetBinContent(28,0.5134596);
   RAAcent_3S__2->SetBinContent(136,0.1292691);
   RAAcent_3S__2->SetBinContent(310,0.1274464);
   RAAcent_3S__2->SetBinError(28,0.1038328);
   RAAcent_3S__2->SetBinError(136,0.04274275);
   RAAcent_3S__2->SetBinError(310,0.03117786);
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
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#660000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#660000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph_RAAcent_1S30013001 = new TH1F("Graph_Graph_RAAcent_1S30013001","",100,0,422.73);
   Graph_Graph_RAAcent_1S30013001->SetMinimum(0);
   Graph_Graph_RAAcent_1S30013001->SetMaximum(1.3);
   Graph_Graph_RAAcent_1S30013001->SetDirectory(0);
   Graph_Graph_RAAcent_1S30013001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_RAAcent_1S30013001->SetLineColor(ci);
   Graph_Graph_RAAcent_1S30013001->GetXaxis()->SetLabelFont(42);
   Graph_Graph_RAAcent_1S30013001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_RAAcent_1S30013001->GetXaxis()->SetTitleFont(42);
   Graph_Graph_RAAcent_1S30013001->GetYaxis()->SetLabelFont(42);
   Graph_Graph_RAAcent_1S30013001->GetYaxis()->SetTitleFont(42);
   Graph_Graph_RAAcent_1S30013001->GetZaxis()->SetLabelFont(42);
   Graph_Graph_RAAcent_1S30013001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_RAAcent_1S30013001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph_RAAcent_1S30013001);
   
   grae->Draw("pe");
   
   Double_t _fx3002[9] = {
   11.5,
   31.5,
   54.5,
   87.5,
   131.5,
   188.5,
   262.5,
   331.5,
   382.5};
   Double_t _fy3002[9] = {
   1.000763,
   0.4692493,
   0.2684407,
   0.1481288,
   0.1710891,
   0.1268126,
   0.07571438,
   0.06814327,
   0.04742893};
   Double_t _felx3002[9] = {
   7,
   3,
   7,
   7,
   7,
   7,
   7,
   7,
   7};
   Double_t _fely3002[9] = {
   0.1447512,
   0.05023149,
   0.04235552,
   0.06763008,
   0.020579,
   0.02995798,
   0.01663963,
   0.04002937,
   0.01513566};
   Double_t _fehx3002[9] = {
   7,
   3,
   7,
   7,
   7,
   7,
   7,
   7,
   7};
   Double_t _fehy3002[9] = {
   0.1447512,
   0.05023149,
   0.04235552,
   0.06763008,
   0.020579,
   0.02995798,
   0.01663963,
   0.04002937,
   0.01513566};
   grae = new TGraphAsymmErrors(9,_fx3002,_fy3002,_felx3002,_fehx3002,_fely3002,_fehy3002);
   grae->SetName("");
   grae->SetTitle("");

   ci = 1179;
   color = new TColor(ci, 0, 0, 1, " ", 0.5);
   grae->SetFillColor(ci);
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);
   
   TH1F *Graph_Graph3002 = new TH1F("Graph_Graph3002","",100,0,428);
   Graph_Graph3002->SetMinimum(0);
   Graph_Graph3002->SetMaximum(1.3);
   Graph_Graph3002->SetDirectory(0);
   Graph_Graph3002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3002->SetLineColor(ci);
   Graph_Graph3002->GetXaxis()->SetLabelFont(42);
   Graph_Graph3002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3002->GetXaxis()->SetTitleFont(42);
   Graph_Graph3002->GetYaxis()->SetLabelFont(42);
   Graph_Graph3002->GetYaxis()->SetTitleFont(42);
   Graph_Graph3002->GetZaxis()->SetLabelFont(42);
   Graph_Graph3002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3002);
   
   grae->Draw("5");
   
   Double_t _fx3003[3] = {
   27.5,
   135.5,
   309.5};
   Double_t _fy3003[3] = {
   0.5134596,
   0.1292691,
   0.1274464};
   Double_t _felx3003[3] = {
   3,
   7,
   7};
   Double_t _fely3003[3] = {
   0.07289495,
   0.01830737,
   0.03040063};
   Double_t _fehx3003[3] = {
   3,
   7,
   7};
   Double_t _fehy3003[3] = {
   0.07289495,
   0.01830737,
   0.03040063};
   grae = new TGraphAsymmErrors(3,_fx3003,_fy3003,_felx3003,_fehx3003,_fely3003,_fehy3003);
   grae->SetName("");
   grae->SetTitle("");

   ci = 1180;
   color = new TColor(ci, 0, 0.4, 0, " ", 0.5);
   grae->SetFillColor(ci);
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#006600");
   grae->SetLineColor(ci);
   
   TH1F *Graph_Graph3003 = new TH1F("Graph_Graph3003","",100,0,345.7);
   Graph_Graph3003->SetMinimum(0);
   Graph_Graph3003->SetMaximum(1.3);
   Graph_Graph3003->SetDirectory(0);
   Graph_Graph3003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3003->SetLineColor(ci);
   Graph_Graph3003->GetXaxis()->SetLabelFont(42);
   Graph_Graph3003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3003->GetXaxis()->SetTitleFont(42);
   Graph_Graph3003->GetYaxis()->SetLabelFont(42);
   Graph_Graph3003->GetYaxis()->SetTitleFont(42);
   Graph_Graph3003->GetZaxis()->SetLabelFont(42);
   Graph_Graph3003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3003);
   
   grae->Draw("5");
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
      tex = new TLatex(1,0.9196,"PbPb (1/4) of 1.6 nb^{-1}, pp 28.0 pb^{-1} (5.02 TeV)");
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
   p22->Range(0,-0.15,4.444444,1.35);
   p22->SetFillColor(0);
   p22->SetBorderMode(0);
   p22->SetBorderSize(2);
   p22->SetTickx(1);
   p22->SetTicky(1);
   p22->SetLeftMargin(0);
   p22->SetFrameBorderMode(0);
   p22->SetFrameBorderMode(0);
   
   Double_t _fx3004[1] = {
   1};
   Double_t _fy3004[1] = {
   0.376};
   Double_t _felx3004[1] = {
   0};
   Double_t _fely3004[1] = {
   0.03733631};
   Double_t _fehx3004[1] = {
   0};
   Double_t _fehy3004[1] = {
   0.03733631};
   grae = new TGraphAsymmErrors(1,_fx3004,_fy3004,_felx3004,_fehx3004,_fely3004,_fehy3004);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#990000");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#990000");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3004 = new TH1F("Graph_Graph3004","",100,0,4);
   Graph_Graph3004->SetMinimum(0);
   Graph_Graph3004->SetMaximum(1.2);
   Graph_Graph3004->SetDirectory(0);
   Graph_Graph3004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3004->SetLineColor(ci);
   Graph_Graph3004->GetXaxis()->SetTitle("int.");
   Graph_Graph3004->GetXaxis()->SetRange(1,100);
   Graph_Graph3004->GetXaxis()->CenterTitle(true);
   Graph_Graph3004->GetXaxis()->SetLabelFont(42);
   Graph_Graph3004->GetXaxis()->SetLabelSize(0);
   Graph_Graph3004->GetXaxis()->SetTitleSize(0.1708824);
   Graph_Graph3004->GetXaxis()->SetTickLength(0);
   Graph_Graph3004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3004->GetXaxis()->SetTitleFont(42);
   Graph_Graph3004->GetYaxis()->SetLabelFont(42);
   Graph_Graph3004->GetYaxis()->SetTitleFont(42);
   Graph_Graph3004->GetZaxis()->SetLabelFont(42);
   Graph_Graph3004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3004);
   
   grae->Draw("ape");
   
   Double_t _fx3005[1] = {
   2};
   Double_t _fy3005[1] = {
   0.09773845};
   Double_t _felx3005[1] = {
   0};
   Double_t _fely3005[1] = {
   0.01682987};
   Double_t _fehx3005[1] = {
   0};
   Double_t _fehy3005[1] = {
   0.01682987};
   grae = new TGraphAsymmErrors(1,_fx3005,_fy3005,_felx3005,_fehx3005,_fely3005,_fehy3005);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000ff");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(4);
   
   TH1F *Graph_Graph3005 = new TH1F("Graph_Graph3005","",100,1.9,3.1);
   Graph_Graph3005->SetMinimum(0);
   Graph_Graph3005->SetMaximum(1.3);
   Graph_Graph3005->SetDirectory(0);
   Graph_Graph3005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3005->SetLineColor(ci);
   Graph_Graph3005->GetXaxis()->SetLabelFont(42);
   Graph_Graph3005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3005->GetXaxis()->SetTitleFont(42);
   Graph_Graph3005->GetYaxis()->SetLabelFont(42);
   Graph_Graph3005->GetYaxis()->SetTitleFont(42);
   Graph_Graph3005->GetZaxis()->SetLabelFont(42);
   Graph_Graph3005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3005->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3005);
   
   grae->Draw("pe");
   
   Double_t _fx3006[1] = {
   3};
   Double_t _fy3006[1] = {
   0.1104473};
   Double_t _felx3006[1] = {
   0};
   Double_t _fely3006[1] = {
   0.02608092};
   Double_t _fehx3006[1] = {
   0};
   Double_t _fehy3006[1] = {
   0.02608092};
   grae = new TGraphAsymmErrors(1,_fx3006,_fy3006,_felx3006,_fehx3006,_fely3006,_fehy3006);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#009900");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(4);
   
   TH1F *Graph_Graph3006 = new TH1F("Graph_Graph3006","",100,2.9,4.1);
   Graph_Graph3006->SetMinimum(0);
   Graph_Graph3006->SetMaximum(1.3);
   Graph_Graph3006->SetDirectory(0);
   Graph_Graph3006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3006->SetLineColor(ci);
   Graph_Graph3006->GetXaxis()->SetLabelFont(42);
   Graph_Graph3006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3006->GetXaxis()->SetTitleFont(42);
   Graph_Graph3006->GetYaxis()->SetLabelFont(42);
   Graph_Graph3006->GetYaxis()->SetTitleFont(42);
   Graph_Graph3006->GetZaxis()->SetLabelFont(42);
   Graph_Graph3006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3006->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3006);
   
   grae->Draw("pe");
   
   Double_t _fx3007[1] = {
   2};
   Double_t _fy3007[1] = {
   0.09773845};
   Double_t _felx3007[1] = {
   0.2};
   Double_t _fely3007[1] = {
   0.01352779};
   Double_t _fehx3007[1] = {
   0.2};
   Double_t _fehy3007[1] = {
   0.01352779};
   grae = new TGraphAsymmErrors(1,_fx3007,_fy3007,_felx3007,_fehx3007,_fely3007,_fehy3007);
   grae->SetName("");
   grae->SetTitle("");

   ci = 1181;
   color = new TColor(ci, 0, 0, 1, " ", 0.5);
   grae->SetFillColor(ci);
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   grae->SetLineColor(ci);
   
   TH1F *Graph_Graph3007 = new TH1F("Graph_Graph3007","",100,1.76,2.24);
   Graph_Graph3007->SetMinimum(0);
   Graph_Graph3007->SetMaximum(1.3);
   Graph_Graph3007->SetDirectory(0);
   Graph_Graph3007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3007->SetLineColor(ci);
   Graph_Graph3007->GetXaxis()->SetLabelFont(42);
   Graph_Graph3007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3007->GetXaxis()->SetTitleFont(42);
   Graph_Graph3007->GetYaxis()->SetLabelFont(42);
   Graph_Graph3007->GetYaxis()->SetTitleFont(42);
   Graph_Graph3007->GetZaxis()->SetLabelFont(42);
   Graph_Graph3007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3007->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3007);
   
   grae->Draw("5");
   
   Double_t _fx3008[1] = {
   3};
   Double_t _fy3008[1] = {
   0.1104473};
   Double_t _felx3008[1] = {
   0.2};
   Double_t _fely3008[1] = {
   0.0175583};
   Double_t _fehx3008[1] = {
   0.2};
   Double_t _fehy3008[1] = {
   0.0175583};
   grae = new TGraphAsymmErrors(1,_fx3008,_fy3008,_felx3008,_fehx3008,_fely3008,_fehy3008);
   grae->SetName("");
   grae->SetTitle("");

   ci = 1182;
   color = new TColor(ci, 0, 0.4, 0, " ", 0.5);
   grae->SetFillColor(ci);
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#006600");
   grae->SetLineColor(ci);
   
   TH1F *Graph_Graph3008 = new TH1F("Graph_Graph3008","",100,2.76,3.24);
   Graph_Graph3008->SetMinimum(0);
   Graph_Graph3008->SetMaximum(1.3);
   Graph_Graph3008->SetDirectory(0);
   Graph_Graph3008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3008->SetLineColor(ci);
   Graph_Graph3008->GetXaxis()->SetLabelFont(42);
   Graph_Graph3008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3008->GetXaxis()->SetTitleFont(42);
   Graph_Graph3008->GetYaxis()->SetLabelFont(42);
   Graph_Graph3008->GetYaxis()->SetTitleFont(42);
   Graph_Graph3008->GetZaxis()->SetLabelFont(42);
   Graph_Graph3008->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3008->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3008);
   
   grae->Draw("5");
   p22->Modified();
   c2->cd();
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
