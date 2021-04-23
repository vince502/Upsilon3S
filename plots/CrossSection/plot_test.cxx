void plot_test()
{
//=========Macro generated from canvas: c1/Cross Section plot
//=========  (Thu Apr 22 18:08:15 2021) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "Cross Section plot",0,0,800,700);
   c1->Range(-3.75,-4.609487,33.75,-2.359858);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   Double_t xAxis1[5] = {0, 4, 9, 12, 30}; 
   
   TH1D *h1__1 = new TH1D("h1__1","CS hist",4, xAxis1);
   h1__1->SetBinContent(1,0.0008592235);
   h1__1->SetBinContent(2,0.001010787);
   h1__1->SetBinContent(3,0.0004354643);
   h1__1->SetBinContent(4,8.250984e-05);
   h1__1->SetBinError(1,0.000203737);
   h1__1->SetBinError(2,0.0003620847);
   h1__1->SetBinError(3,0.0008066075);
   h1__1->SetBinError(4,0.0001536001);
   h1__1->SetEntries(4);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("h1");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 4      ");
   ptstats_LaTex = ptstats->AddText("Mean  =  6.111");
   ptstats_LaTex = ptstats->AddText("Std Dev   =  4.161");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   h1__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h1__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1__1->SetLineColor(ci);
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetTitleOffset(1);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.4146231,0.94,0.5853769,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("CS hist");
   pt->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
