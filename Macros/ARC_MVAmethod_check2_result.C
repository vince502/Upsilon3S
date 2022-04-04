void ARC_MVAmethod_check2_result()
{
//=========Macro generated from canvas: c1/
//=========  (Thu Mar 10 04:02:28 2022) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",556,1478,800,600);
   c1->Range(-0.6375,-0.14375,5.7375,0.29375);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   Double_t _fx3001[1] = {
   0.2};
   Double_t _fy3001[1] = {
   0.1153971};
   Double_t _felx3001[1] = {
   0};
   Double_t _fely3001[1] = {
   0.01400833};
   Double_t _fehx3001[1] = {
   0};
   Double_t _fehy3001[1] = {
   0.01400833};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(1,_fx3001,_fy3001,_felx3001,_fehx3001,_fely3001,_fehy3001);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3001 = new TH1F("Graph_Graph3001","",100,0,5.1);
   Graph_Graph3001->SetMinimum(-0.1);
   Graph_Graph3001->SetMaximum(0.25);
   Graph_Graph3001->SetDirectory(0);
   Graph_Graph3001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph3001->SetLineColor(ci);
   Graph_Graph3001->GetXaxis()->SetRange(1,100);
   Graph_Graph3001->GetXaxis()->SetLabelFont(42);
   Graph_Graph3001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3001->GetXaxis()->SetTitleFont(42);
   Graph_Graph3001->GetYaxis()->SetLabelFont(42);
   Graph_Graph3001->GetYaxis()->SetTitleFont(42);
   Graph_Graph3001->GetZaxis()->SetLabelFont(42);
   Graph_Graph3001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3001);
   
   grae->Draw("ape");
   
   Double_t _fx3002[1] = {
   0.35};
   Double_t _fy3002[1] = {
   0.08619745};
   Double_t _felx3002[1] = {
   0};
   Double_t _fely3002[1] = {
   0.01354719};
   Double_t _fehx3002[1] = {
   0};
   Double_t _fehy3002[1] = {
   0.01354719};
   grae = new TGraphAsymmErrors(1,_fx3002,_fy3002,_felx3002,_fehx3002,_fely3002,_fehy3002);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#993333");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#993333");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3002 = new TH1F("Graph_Graph3002","",100,0.25,1.45);
   Graph_Graph3002->SetMinimum(0.06994082);
   Graph_Graph3002->SetMaximum(0.1024541);
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
   
   grae->Draw("pe");
   
   Double_t _fx3003[1] = {
   0.5};
   Double_t _fy3003[1] = {
   0.04852348};
   Double_t _felx3003[1] = {
   0};
   Double_t _fely3003[1] = {
   0.01344439};
   Double_t _fehx3003[1] = {
   0};
   Double_t _fehy3003[1] = {
   0.01344439};
   grae = new TGraphAsymmErrors(1,_fx3003,_fy3003,_felx3003,_fehx3003,_fely3003,_fehy3003);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6633");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff6633");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3003 = new TH1F("Graph_Graph3003","",100,0.4,1.6);
   Graph_Graph3003->SetMinimum(0.03239021);
   Graph_Graph3003->SetMaximum(0.06465675);
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
   
   grae->Draw("pe");
   
   Double_t _fx3004[1] = {
   0.65};
   Double_t _fy3004[1] = {
   0.04851527};
   Double_t _felx3004[1] = {
   0};
   Double_t _fely3004[1] = {
   0.01322069};
   Double_t _fehx3004[1] = {
   0};
   Double_t _fehy3004[1] = {
   0.01322069};
   grae = new TGraphAsymmErrors(1,_fx3004,_fy3004,_felx3004,_fehx3004,_fely3004,_fehy3004);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#33ffcc");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#33ffcc");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3004 = new TH1F("Graph_Graph3004","",100,0.55,1.75);
   Graph_Graph3004->SetMinimum(0.03265044);
   Graph_Graph3004->SetMaximum(0.0643801);
   Graph_Graph3004->SetDirectory(0);
   Graph_Graph3004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3004->SetLineColor(ci);
   Graph_Graph3004->GetXaxis()->SetLabelFont(42);
   Graph_Graph3004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3004->GetXaxis()->SetTitleFont(42);
   Graph_Graph3004->GetYaxis()->SetLabelFont(42);
   Graph_Graph3004->GetYaxis()->SetTitleFont(42);
   Graph_Graph3004->GetZaxis()->SetLabelFont(42);
   Graph_Graph3004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3004->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3004);
   
   grae->Draw("pe");
   
   Double_t _fx3005[1] = {
   0.8};
   Double_t _fy3005[1] = {
   0.08043177};
   Double_t _felx3005[1] = {
   0};
   Double_t _fely3005[1] = {
   0.01416926};
   Double_t _fehx3005[1] = {
   0};
   Double_t _fehy3005[1] = {
   0.01416926};
   grae = new TGraphAsymmErrors(1,_fx3005,_fy3005,_felx3005,_fehx3005,_fely3005,_fehy3005);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3005 = new TH1F("Graph_Graph3005","",100,0.7,1.9);
   Graph_Graph3005->SetMinimum(0.06342866);
   Graph_Graph3005->SetMaximum(0.09743489);
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
   1.05};
   Double_t _fy3006[1] = {
   0.09397314};
   Double_t _felx3006[1] = {
   0};
   Double_t _fely3006[1] = {
   0.01404407};
   Double_t _fehx3006[1] = {
   0};
   Double_t _fehy3006[1] = {
   0.01404407};
   grae = new TGraphAsymmErrors(1,_fx3006,_fy3006,_felx3006,_fehx3006,_fely3006,_fehy3006);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3006 = new TH1F("Graph_Graph3006","",100,0.95,2.15);
   Graph_Graph3006->SetMinimum(0.07712025);
   Graph_Graph3006->SetMaximum(0.110826);
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
   1.2};
   Double_t _fy3007[1] = {
   0.05226915};
   Double_t _felx3007[1] = {
   0};
   Double_t _fely3007[1] = {
   0.01401922};
   Double_t _fehx3007[1] = {
   0};
   Double_t _fehy3007[1] = {
   0.01401922};
   grae = new TGraphAsymmErrors(1,_fx3007,_fy3007,_felx3007,_fehx3007,_fely3007,_fehy3007);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#993333");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#993333");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3007 = new TH1F("Graph_Graph3007","",100,1.1,2.3);
   Graph_Graph3007->SetMinimum(0.03544608);
   Graph_Graph3007->SetMaximum(0.06909221);
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
   
   grae->Draw("pe");
   
   Double_t _fx3008[1] = {
   1.35};
   Double_t _fy3008[1] = {
   0.06880121};
   Double_t _felx3008[1] = {
   0};
   Double_t _fely3008[1] = {
   0.01382026};
   Double_t _fehx3008[1] = {
   0};
   Double_t _fehy3008[1] = {
   0.01382026};
   grae = new TGraphAsymmErrors(1,_fx3008,_fy3008,_felx3008,_fehx3008,_fely3008,_fehy3008);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3008 = new TH1F("Graph_Graph3008","",100,1.25,2.45);
   Graph_Graph3008->SetMinimum(0.05221689);
   Graph_Graph3008->SetMaximum(0.08538552);
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
   
   grae->Draw("pe");
   
   Double_t _fx3009[1] = {
   1.5};
   Double_t _fy3009[1] = {
   0.1078914};
   Double_t _felx3009[1] = {
   0};
   Double_t _fely3009[1] = {
   0.02024233};
   Double_t _fehx3009[1] = {
   0};
   Double_t _fehy3009[1] = {
   0.02024233};
   grae = new TGraphAsymmErrors(1,_fx3009,_fy3009,_felx3009,_fehx3009,_fely3009,_fehy3009);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3009 = new TH1F("Graph_Graph3009","",100,1.4,2.6);
   Graph_Graph3009->SetMinimum(0.08360061);
   Graph_Graph3009->SetMaximum(0.1321822);
   Graph_Graph3009->SetDirectory(0);
   Graph_Graph3009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3009->SetLineColor(ci);
   Graph_Graph3009->GetXaxis()->SetLabelFont(42);
   Graph_Graph3009->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3009->GetXaxis()->SetTitleFont(42);
   Graph_Graph3009->GetYaxis()->SetLabelFont(42);
   Graph_Graph3009->GetYaxis()->SetTitleFont(42);
   Graph_Graph3009->GetZaxis()->SetLabelFont(42);
   Graph_Graph3009->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3009->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3009);
   
   grae->Draw("pe");
   
   Double_t _fx3010[1] = {
   1.85};
   Double_t _fy3010[1] = {
   0.05630289};
   Double_t _felx3010[1] = {
   0};
   Double_t _fely3010[1] = {
   0.02018377};
   Double_t _fehx3010[1] = {
   0};
   Double_t _fehy3010[1] = {
   0.02018377};
   grae = new TGraphAsymmErrors(1,_fx3010,_fy3010,_felx3010,_fehx3010,_fely3010,_fehy3010);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#993333");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#993333");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3010 = new TH1F("Graph_Graph3010","",100,1.75,2.95);
   Graph_Graph3010->SetMinimum(0.03208236);
   Graph_Graph3010->SetMaximum(0.08052341);
   Graph_Graph3010->SetDirectory(0);
   Graph_Graph3010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3010->SetLineColor(ci);
   Graph_Graph3010->GetXaxis()->SetLabelFont(42);
   Graph_Graph3010->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3010->GetXaxis()->SetTitleFont(42);
   Graph_Graph3010->GetYaxis()->SetLabelFont(42);
   Graph_Graph3010->GetYaxis()->SetTitleFont(42);
   Graph_Graph3010->GetZaxis()->SetLabelFont(42);
   Graph_Graph3010->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3010->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3010);
   
   grae->Draw("pe");
   
   Double_t _fx3011[1] = {
   2};
   Double_t _fy3011[1] = {
   0.0526497};
   Double_t _felx3011[1] = {
   0};
   Double_t _fely3011[1] = {
   0.01975333};
   Double_t _fehx3011[1] = {
   0};
   Double_t _fehy3011[1] = {
   0.01975333};
   grae = new TGraphAsymmErrors(1,_fx3011,_fy3011,_felx3011,_fehx3011,_fely3011,_fehy3011);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#ff6633");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ff6633");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3011 = new TH1F("Graph_Graph3011","",100,1.9,3.1);
   Graph_Graph3011->SetMinimum(0.0289457);
   Graph_Graph3011->SetMaximum(0.07635369);
   Graph_Graph3011->SetDirectory(0);
   Graph_Graph3011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3011->SetLineColor(ci);
   Graph_Graph3011->GetXaxis()->SetLabelFont(42);
   Graph_Graph3011->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3011->GetXaxis()->SetTitleFont(42);
   Graph_Graph3011->GetYaxis()->SetLabelFont(42);
   Graph_Graph3011->GetYaxis()->SetTitleFont(42);
   Graph_Graph3011->GetZaxis()->SetLabelFont(42);
   Graph_Graph3011->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3011->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3011);
   
   grae->Draw("pe");
   
   Double_t _fx3012[1] = {
   2.15};
   Double_t _fy3012[1] = {
   -0.01834731};
   Double_t _felx3012[1] = {
   0};
   Double_t _fely3012[1] = {
   0.01996466};
   Double_t _fehx3012[1] = {
   0};
   Double_t _fehy3012[1] = {
   0.01996466};
   grae = new TGraphAsymmErrors(1,_fx3012,_fy3012,_felx3012,_fehx3012,_fely3012,_fehy3012);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#33ffcc");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#33ffcc");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3012 = new TH1F("Graph_Graph3012","",100,2.05,3.25);
   Graph_Graph3012->SetMinimum(-0.0423049);
   Graph_Graph3012->SetMaximum(0.005610285);
   Graph_Graph3012->SetDirectory(0);
   Graph_Graph3012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3012->SetLineColor(ci);
   Graph_Graph3012->GetXaxis()->SetLabelFont(42);
   Graph_Graph3012->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3012->GetXaxis()->SetTitleFont(42);
   Graph_Graph3012->GetYaxis()->SetLabelFont(42);
   Graph_Graph3012->GetYaxis()->SetTitleFont(42);
   Graph_Graph3012->GetZaxis()->SetLabelFont(42);
   Graph_Graph3012->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3012->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3012);
   
   grae->Draw("pe");
   
   Double_t _fx3013[1] = {
   2.3};
   Double_t _fy3013[1] = {
   0.05564783};
   Double_t _felx3013[1] = {
   0};
   Double_t _fely3013[1] = {
   0.02181662};
   Double_t _fehx3013[1] = {
   0};
   Double_t _fehy3013[1] = {
   0.02181662};
   grae = new TGraphAsymmErrors(1,_fx3013,_fy3013,_felx3013,_fehx3013,_fely3013,_fehy3013);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#0000cc");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#0000cc");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3013 = new TH1F("Graph_Graph3013","",100,2.2,3.4);
   Graph_Graph3013->SetMinimum(0.02946789);
   Graph_Graph3013->SetMaximum(0.08182777);
   Graph_Graph3013->SetDirectory(0);
   Graph_Graph3013->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3013->SetLineColor(ci);
   Graph_Graph3013->GetXaxis()->SetLabelFont(42);
   Graph_Graph3013->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3013->GetXaxis()->SetTitleFont(42);
   Graph_Graph3013->GetYaxis()->SetLabelFont(42);
   Graph_Graph3013->GetYaxis()->SetTitleFont(42);
   Graph_Graph3013->GetZaxis()->SetLabelFont(42);
   Graph_Graph3013->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3013->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3013);
   
   grae->Draw("pe");
   
   TLegend *leg = new TLegend(0.5,0.25,0.9,0.75,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","Left to right #rightarrow descending order","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","nominal BDT, dataset1 blind","pe");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","nominal BDT, dataset2 blind","pe");

   ci = TColor::GetColor("#993333");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#993333");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","nominal BDT, dataset3 blind","pe");

   ci = TColor::GetColor("#ff6633");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff6633");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","nominal BDT, dataset4 blind","pe");

   ci = TColor::GetColor("#33ffcc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#33ffcc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","nominal BDT, Full data","pe");

   ci = TColor::GetColor("#0000cc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","alterante train, nominal BDT, dataset1 blind","pe");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","alterante train, nominal BDT, dataset2 blind","pe");

   ci = TColor::GetColor("#993333");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#993333");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","alterante train, nominal BDT, Full","pe");

   ci = TColor::GetColor("#0000cc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","no BDT, dataset1 blind","pe");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","no BDT, dataset1 blind","pe");

   ci = TColor::GetColor("#993333");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#993333");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","no BDT, dataset1 blind","pe");

   ci = TColor::GetColor("#ff6633");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff6633");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","no BDT, dataset1 blind","pe");

   ci = TColor::GetColor("#33ffcc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#33ffcc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","no BDT, Full","pe");

   ci = TColor::GetColor("#0000cc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#0000cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
