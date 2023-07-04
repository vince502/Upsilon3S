void BDTCorYieldplot_2_8000000001_2()
{
//=========Macro generated from canvas: c1/
//=========  (Thu Oct 28 11:13:11 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S__1 = new TH1D("Y2S__1","",13,0,13);
   Y2S__1->SetBinContent(1,2909.745);
   Y2S__1->SetBinContent(2,5499.294);
   Y2S__1->SetBinContent(3,5909.859);
   Y2S__1->SetBinContent(4,5767.656);
   Y2S__1->SetBinContent(5,3900.348);
   Y2S__1->SetBinContent(6,4567.196);
   Y2S__1->SetBinContent(7,4238.581);
   Y2S__1->SetBinContent(8,3574.441);
   Y2S__1->SetBinContent(9,3321.435);
   Y2S__1->SetBinContent(10,3180.399);
   Y2S__1->SetBinContent(11,3511.604);
   Y2S__1->SetBinError(1,841.2689);
   Y2S__1->SetBinError(2,803.1067);
   Y2S__1->SetBinError(3,784.771);
   Y2S__1->SetBinError(4,607.984);
   Y2S__1->SetBinError(5,566.7462);
   Y2S__1->SetBinError(6,547.9207);
   Y2S__1->SetBinError(7,517.3565);
   Y2S__1->SetBinError(8,517.0309);
   Y2S__1->SetBinError(9,534.4737);
   Y2S__1->SetBinError(10,571.4246);
   Y2S__1->SetBinError(11,656.0714);
   Y2S__1->SetEntries(11);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#990000");
   Y2S__1->SetLineColor(ci);

   ci = TColor::GetColor("#990000");
   Y2S__1->SetMarkerColor(ci);
   Y2S__1->GetXaxis()->SetLabelFont(42);
   Y2S__1->GetXaxis()->SetTitleOffset(1);
   Y2S__1->GetXaxis()->SetTitleFont(42);
   Y2S__1->GetYaxis()->SetLabelFont(42);
   Y2S__1->GetYaxis()->SetTitleFont(42);
   Y2S__1->GetZaxis()->SetLabelFont(42);
   Y2S__1->GetZaxis()->SetTitleOffset(1);
   Y2S__1->GetZaxis()->SetTitleFont(42);
   Y2S__1->Draw(" pe");
   
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
