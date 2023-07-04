void BDTCorYieldplot_train3_3S_8200000017_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 15 20:56:03 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train3__1 = new TH1D("Y3S_train3__1","",4,0,4);
   Y3S_train3__1->SetBinContent(1,1);
   Y3S_train3__1->SetBinContent(2,1.158973);
   Y3S_train3__1->SetBinContent(3,1.327514);
   Y3S_train3__1->SetBinContent(4,1.449609);
   Y3S_train3__1->SetBinError(1,0.4605381);
   Y3S_train3__1->SetBinError(2,0.5895028);
   Y3S_train3__1->SetBinError(3,0.6654116);
   Y3S_train3__1->SetBinError(4,0.7372121);
   Y3S_train3__1->SetMinimum(0.4);
   Y3S_train3__1->SetMaximum(2);
   Y3S_train3__1->SetEntries(4);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y3S_train3__1->SetLineColor(ci);
   Y3S_train3__1->GetXaxis()->SetBinLabel(2,"0.50");
   Y3S_train3__1->GetXaxis()->SetBinLabel(3,"0.70");
   Y3S_train3__1->GetXaxis()->SetBinLabel(4,"0.80");
   Y3S_train3__1->GetXaxis()->SetLabelFont(42);
   Y3S_train3__1->GetXaxis()->SetTitleOffset(1);
   Y3S_train3__1->GetXaxis()->SetTitleFont(42);
   Y3S_train3__1->GetYaxis()->SetLabelFont(42);
   Y3S_train3__1->GetYaxis()->SetTitleFont(42);
   Y3S_train3__1->GetZaxis()->SetLabelFont(42);
   Y3S_train3__1->GetZaxis()->SetTitleOffset(1);
   Y3S_train3__1->GetZaxis()->SetTitleFont(42);
   Y3S_train3__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
