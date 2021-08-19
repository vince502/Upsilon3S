void intbin_yxe_bdt()
{
//=========Macro generated from canvas: c1/c1
//=========  (Mon Jul  5 18:55:26 2021) by ROOT version 6.22/06
   TCanvas *c1 = new TCanvas("c1", "c1",915,176,943,569);
   gStyle->SetOptStat(0);
   c1->Range(-1.26125,-312.0908,1.25125,2808.817);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameBorderMode(0);
   
   TH1D *h1__1 = new TH1D("h1__1","",200,-1,1);
   h1__1->SetBinContent(1,1674.344);
   h1__1->SetBinContent(81,1381.609);
   h1__1->SetBinContent(91,1370.233);
   h1__1->SetBinContent(111,1661.621);
   h1__1->SetBinContent(121,1671.156);
   h1__1->SetBinError(1,703.4903);
   h1__1->SetBinError(81,582.7709);
   h1__1->SetBinError(91,495.2765);
   h1__1->SetBinError(111,405.9099);
   h1__1->SetBinError(121,443.9426);
   h1__1->SetEntries(5);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h1__1->SetLineColor(ci);
   h1__1->SetLineWidth(3);
   h1__1->SetMarkerStyle(29);
   h1__1->SetMarkerSize(3);
   h1__1->GetXaxis()->SetTitle("BDT");
   h1__1->GetXaxis()->SetRange(0,200);
   h1__1->GetXaxis()->SetLabelFont(42);
   h1__1->GetXaxis()->SetTitleOffset(1);
   h1__1->GetXaxis()->SetTitleFont(42);
   h1__1->GetYaxis()->SetTitle("Y #times #varepsilon");
   h1__1->GetYaxis()->SetLabelFont(42);
   h1__1->GetYaxis()->SetTitleFont(42);
   h1__1->GetZaxis()->SetLabelFont(42);
   h1__1->GetZaxis()->SetTitleOffset(1);
   h1__1->GetZaxis()->SetTitleFont(42);
   h1__1->Draw("ep");
   TLatex *   tex = new TLatex(0.65,0.15,"Integrated Bin");
tex->SetNDC();
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.65,0.15,"Integrated Bin");
tex->SetNDC();
   tex->SetLineWidth(2);
   tex->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
