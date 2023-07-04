void BDTCorYieldplot_train3_3S_8200000002_2()
{
//=========Macro generated from canvas: c1/
//=========  (Sun Nov 14 20:12:46 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train3__1 = new TH1D("Y3S_train3__1","",9,0,9);
   Y3S_train3__1->SetBinContent(1,1);
   Y3S_train3__1->SetBinContent(2,0.8968763);
   Y3S_train3__1->SetBinContent(3,0.9892394);
   Y3S_train3__1->SetBinContent(4,0.9407269);
   Y3S_train3__1->SetBinContent(5,1.004575);
   Y3S_train3__1->SetBinContent(6,0.9557655);
   Y3S_train3__1->SetBinContent(7,0.8562115);
   Y3S_train3__1->SetBinContent(8,1.000819);
   Y3S_train3__1->SetBinContent(9,1.019775);
   Y3S_train3__1->SetBinError(1,0.4605381);
   Y3S_train3__1->SetBinError(2,0.5087256);
   Y3S_train3__1->SetBinError(3,0.5453709);
   Y3S_train3__1->SetBinError(4,0.517887);
   Y3S_train3__1->SetBinError(5,0.5416117);
   Y3S_train3__1->SetBinError(6,0.5203602);
   Y3S_train3__1->SetBinError(7,0.4797101);
   Y3S_train3__1->SetBinError(8,0.5430622);
   Y3S_train3__1->SetBinError(9,0.5562667);
   Y3S_train3__1->SetMinimum(0.4);
   Y3S_train3__1->SetMaximum(2);
   Y3S_train3__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y3S_train3__1->SetLineColor(ci);
   Y3S_train3__1->GetXaxis()->SetBinLabel(2,"-0.10");
   Y3S_train3__1->GetXaxis()->SetBinLabel(3,"0.00");
   Y3S_train3__1->GetXaxis()->SetBinLabel(4,"0.10");
   Y3S_train3__1->GetXaxis()->SetBinLabel(5,"0.20");
   Y3S_train3__1->GetXaxis()->SetBinLabel(6,"0.30");
   Y3S_train3__1->GetXaxis()->SetBinLabel(7,"0.50");
   Y3S_train3__1->GetXaxis()->SetBinLabel(8,"0.70");
   Y3S_train3__1->GetXaxis()->SetBinLabel(9,"0.80");
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
