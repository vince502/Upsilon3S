void raa_unc_2s_pt()
{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Aug 20 14:15:44 2021) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "c1",1213,213,700,500);
   c1->Range(-3.75,-0.4875,33.75,1.3875);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   Double_t xAxis1[4] = {0, 4, 9, 30}; 
   
   TH1D *hptAA__1__1 = new TH1D("hptAA__1__1","",3, xAxis1);
   hptAA__1__1->SetBinContent(1,1.095403);
   hptAA__1__1->SetBinContent(2,-0.2036949);
   hptAA__1__1->SetBinContent(3,-0.1089418);
   hptAA__1__1->SetMinimum(-0.3);
   hptAA__1__1->SetMaximum(1.2);
   hptAA__1__1->SetEntries(3);
   hptAA__1__1->SetDirectory(0);
   hptAA__1__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#990000");
   hptAA__1__1->SetLineColor(ci);
   hptAA__1__1->GetXaxis()->SetTitle("p_{T} GeV/c");
   hptAA__1__1->GetXaxis()->SetLabelFont(42);
   hptAA__1__1->GetXaxis()->SetTitleOffset(1);
   hptAA__1__1->GetXaxis()->SetTitleFont(42);
   hptAA__1__1->GetYaxis()->SetTitle("Uncertainty");
   hptAA__1__1->GetYaxis()->SetLabelFont(42);
   hptAA__1__1->GetYaxis()->SetTitleOffset(1);
   hptAA__1__1->GetYaxis()->SetTitleFont(42);
   hptAA__1__1->GetZaxis()->SetLabelFont(42);
   hptAA__1__1->GetZaxis()->SetTitleOffset(1);
   hptAA__1__1->GetZaxis()->SetTitleFont(42);
   hptAA__1__1->Draw("");
   Double_t xAxis2[4] = {0, 4, 9, 30}; 
   
   TH1D *hptAA__2__2 = new TH1D("hptAA__2__2","",3, xAxis2);
   hptAA__2__2->SetBinContent(1,0.07141409);
   hptAA__2__2->SetBinContent(2,-0.09678428);
   hptAA__2__2->SetBinContent(3,-0.1444918);
   hptAA__2__2->SetMinimum(-0.3);
   hptAA__2__2->SetMaximum(1.2);
   hptAA__2__2->SetEntries(6);
   hptAA__2__2->SetLineColor(4);
   hptAA__2__2->GetXaxis()->SetTitle("Uncertainty");
   hptAA__2__2->GetXaxis()->SetLabelFont(42);
   hptAA__2__2->GetXaxis()->SetTitleOffset(1);
   hptAA__2__2->GetXaxis()->SetTitleFont(42);
   hptAA__2__2->GetYaxis()->SetTitle("p_{T} (GeV/c)");
   hptAA__2__2->GetYaxis()->SetLabelFont(42);
   hptAA__2__2->GetYaxis()->SetTitleOffset(1);
   hptAA__2__2->GetYaxis()->SetTitleFont(42);
   hptAA__2__2->GetZaxis()->SetLabelFont(42);
   hptAA__2__2->GetZaxis()->SetTitleOffset(1);
   hptAA__2__2->GetZaxis()->SetTitleFont(42);
   hptAA__2__2->Draw("same");
   
   TLegend *leg = new TLegend(0.6,0.3191489,0.8,0.4691489,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","HIN-16-023","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#990000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","this analysis","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.6,0.3191489,0.8,0.4691489,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","HIN-16-023","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#990000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","this analysis","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.6,0.3191489,0.8,0.4691489,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","HIN-16-023","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#990000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","this analysis","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.6,0.3191489,0.8,0.4691489,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("NULL","HIN-16-023","lpf");
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#990000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("NULL","this analysis","lpf");
   entry->SetFillStyle(1001);
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   TLine *line = new TLine(0,0,30,0);
   line->SetLineColorAlpha(2,0.1);
   line->SetLineStyle(2);
   line->SetLineWidth(3);
   line->Draw();
   line->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
