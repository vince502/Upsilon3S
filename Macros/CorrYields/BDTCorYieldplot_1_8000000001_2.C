void BDTCorYieldplot_1_8000000001_2()
{
//=========Macro generated from canvas: c1/
//=========  (Thu Oct 28 11:13:01 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S__1 = new TH1D("Y1S__1","",13,0,13);
   Y1S__1->SetBinContent(1,41690.52);
   Y1S__1->SetBinContent(2,44756.2);
   Y1S__1->SetBinContent(3,44663.83);
   Y1S__1->SetBinContent(4,42640.63);
   Y1S__1->SetBinContent(5,41564.14);
   Y1S__1->SetBinContent(6,41294.19);
   Y1S__1->SetBinContent(7,39091.42);
   Y1S__1->SetBinContent(8,37117.98);
   Y1S__1->SetBinContent(9,36823.08);
   Y1S__1->SetBinContent(10,35714.81);
   Y1S__1->SetBinContent(11,34272.14);
   Y1S__1->SetBinError(1,1155.444);
   Y1S__1->SetBinError(2,1217.749);
   Y1S__1->SetBinError(3,1145.03);
   Y1S__1->SetBinError(4,1027.151);
   Y1S__1->SetBinError(5,966.1566);
   Y1S__1->SetBinError(6,951.5053);
   Y1S__1->SetBinError(7,947.1887);
   Y1S__1->SetBinError(8,995.3985);
   Y1S__1->SetBinError(9,1091.144);
   Y1S__1->SetBinError(10,1205.656);
   Y1S__1->SetBinError(11,1365.367);
   Y1S__1->SetEntries(11);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#cc0000");
   Y1S__1->SetLineColor(ci);

   ci = TColor::GetColor("#cc0000");
   Y1S__1->SetMarkerColor(ci);
   Y1S__1->GetXaxis()->SetLabelFont(42);
   Y1S__1->GetXaxis()->SetTitleOffset(1);
   Y1S__1->GetXaxis()->SetTitleFont(42);
   Y1S__1->GetYaxis()->SetLabelFont(42);
   Y1S__1->GetYaxis()->SetTitleFont(42);
   Y1S__1->GetZaxis()->SetLabelFont(42);
   Y1S__1->GetZaxis()->SetTitleOffset(1);
   Y1S__1->GetZaxis()->SetTitleFont(42);
   Y1S__1->Draw("pe");
   
   TLegend *leg = new TLegend(0.2,0.85,0.4,0.92,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Y1S","1S","le");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Y2S","2S","le");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("Y3S","3S","le");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
