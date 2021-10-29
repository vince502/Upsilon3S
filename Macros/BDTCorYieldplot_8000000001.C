void BDTCorYieldplot_8000000001()
{
//=========Macro generated from canvas: c1/
//=========  (Wed Oct 27 15:16:40 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S__1 = new TH1D("Y3S__1","",13,0,13);
   Y3S__1->SetBinContent(1,1591.697);
   Y3S__1->SetBinContent(2,1591.698);
   Y3S__1->SetBinContent(3,2099.408);
   Y3S__1->SetBinContent(4,5004.851);
   Y3S__1->SetBinContent(5,1963.097);
   Y3S__1->SetBinContent(6,1778.732);
   Y3S__1->SetBinContent(7,1981.708);
   Y3S__1->SetBinContent(8,2168.545);
   Y3S__1->SetBinContent(9,2133.382);
   Y3S__1->SetBinContent(10,1803.798);
   Y3S__1->SetBinContent(11,1845.567);
   Y3S__1->SetBinContent(12,2076.092);
   Y3S__1->SetBinError(1,686.8206);
   Y3S__1->SetBinError(2,716.0673);
   Y3S__1->SetBinError(3,659.7419);
   Y3S__1->SetBinError(4,763.0474);
   Y3S__1->SetBinError(5,498.885);
   Y3S__1->SetBinError(6,465.9857);
   Y3S__1->SetBinError(7,453.4735);
   Y3S__1->SetBinError(8,447.8931);
   Y3S__1->SetBinError(9,451.028);
   Y3S__1->SetBinError(10,462.1391);
   Y3S__1->SetBinError(11,493.267);
   Y3S__1->SetBinError(12,567.4501);
   Y3S__1->SetEntries(12);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#660000");
   Y3S__1->SetLineColor(ci);

   ci = TColor::GetColor("#660000");
   Y3S__1->SetMarkerColor(ci);
   Y3S__1->GetXaxis()->SetLabelFont(42);
   Y3S__1->GetXaxis()->SetTitleOffset(1);
   Y3S__1->GetXaxis()->SetTitleFont(42);
   Y3S__1->GetYaxis()->SetLabelFont(42);
   Y3S__1->GetYaxis()->SetTitleFont(42);
   Y3S__1->GetZaxis()->SetLabelFont(42);
   Y3S__1->GetZaxis()->SetTitleOffset(1);
   Y3S__1->GetZaxis()->SetTitleFont(42);
   Y3S__1->Draw(" pe");
   
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
