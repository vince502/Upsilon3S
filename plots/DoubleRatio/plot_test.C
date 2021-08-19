void plot_test()
{
//=========Macro generated from canvas: c2/
//=========  (Thu Jul  8 14:01:53 2021) by ROOT version 6.22/06
   TCanvas *c2 = new TCanvas("c2", "",392,1463,700,800);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   c2->Range(-52.5,-0.1875,472.5,1.6875);
   c2->SetFillColor(0);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameBorderMode(0);
   c2->SetFrameBorderMode(0);
   
   TH1D *h1__1 = new TH1D("h1__1","PbPb 2S double ratio cent",70,0,420);
   h1__1->SetBinContent(2,1.139979);
   h1__1->SetBinContent(6,0.7642237);
   h1__1->SetBinContent(10,0.5294456);
   h1__1->SetBinContent(15,0.5053544);
   h1__1->SetBinContent(22,0.4045037);
   h1__1->SetBinContent(32,0.2954005);
   h1__1->SetBinContent(44,0.3406909);
   h1__1->SetBinContent(56,0.3577565);
   h1__1->SetBinContent(64,0.1295841);
   h1__1->SetBinError(2,0.3062552);
   h1__1->SetBinError(6,0.2283113);
   h1__1->SetBinError(10,0.1633794);
   h1__1->SetBinError(15,0.1458999);
   h1__1->SetBinError(22,0.1134817);
   h1__1->SetBinError(32,0.1132465);
   h1__1->SetBinError(44,0.1140112);
   h1__1->SetBinError(56,0.1462783);
   h1__1->SetBinError(64,0.1693555);
   h1__1->SetMinimum(0);
   h1__1->SetMaximum(1.5);
   h1__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#990000");
   h1__1->SetLineColor(ci);

   ci = TColor::GetColor("#990000");
   h1__1->SetMarkerColor(ci);
   h1__1->SetMarkerStyle(4);
   h1__1->GetXaxis()->SetTitle("N_{part}");
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetLabelSize(0.04);
   h1__1->GetXaxis()->SetTitleOffset(1);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetTitle("R_{AA}");
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetTitleSize(0.05);
   h1__1->GetYaxis()->SetTitleOffset(1.2);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("pe");
   c2->Modified();
   c2->cd();
   c2->SetSelected(c2);
}
