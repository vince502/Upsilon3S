void BDTCorYieldplot_2_8000000001()
{
//=========Macro generated from canvas: c1/
//=========  (Thu Oct 28 11:10:41 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S__1 = new TH1D("Y2S__1","",13,0,13);
   Y2S__1->SetBinContent(1,2909.745);
   Y2S__1->SetBinContent(2,3085.424);
   Y2S__1->SetBinContent(3,3521.447);
   Y2S__1->SetBinContent(4,7791.076);
   Y2S__1->SetBinContent(5,4106.966);
   Y2S__1->SetBinContent(6,4405.386);
   Y2S__1->SetBinContent(7,4215.351);
   Y2S__1->SetBinContent(8,3899.108);
   Y2S__1->SetBinContent(9,3595.572);
   Y2S__1->SetBinContent(10,3390.57);
   Y2S__1->SetBinContent(11,4154.308);
   Y2S__1->SetBinError(1,841.2689);
   Y2S__1->SetBinError(2,878.089);
   Y2S__1->SetBinError(3,818.0054);
   Y2S__1->SetBinError(4,846.5911);
   Y2S__1->SetBinError(5,569.9418);
   Y2S__1->SetBinError(6,543.0893);
   Y2S__1->SetBinError(7,521.7508);
   Y2S__1->SetBinError(8,528.7773);
   Y2S__1->SetBinError(9,539.3086);
   Y2S__1->SetBinError(10,574.0332);
   Y2S__1->SetBinError(11,685.0822);
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
