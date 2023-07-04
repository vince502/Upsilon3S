void BDTCorYieldplot_train3_2S_8200000006_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 15 13:15:27 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train3__1 = new TH1D("Y2S_train3__1","",9,0,9);
   Y2S_train3__1->SetBinContent(1,1);
   Y2S_train3__1->SetBinContent(2,1.407343);
   Y2S_train3__1->SetBinContent(3,1.471069);
   Y2S_train3__1->SetBinContent(4,1.562585);
   Y2S_train3__1->SetBinContent(5,1.67445);
   Y2S_train3__1->SetBinContent(6,1.496391);
   Y2S_train3__1->SetBinContent(7,1.540057);
   Y2S_train3__1->SetBinContent(8,1.65388);
   Y2S_train3__1->SetBinContent(9,1.586173);
   Y2S_train3__1->SetBinError(1,0.2892203);
   Y2S_train3__1->SetBinError(2,0.4545414);
   Y2S_train3__1->SetBinError(3,0.4626118);
   Y2S_train3__1->SetBinError(4,0.4815815);
   Y2S_train3__1->SetBinError(5,0.5112146);
   Y2S_train3__1->SetBinError(6,0.4625476);
   Y2S_train3__1->SetBinError(7,0.4791092);
   Y2S_train3__1->SetBinError(8,0.5230074);
   Y2S_train3__1->SetBinError(9,0.5388689);
   Y2S_train3__1->SetMinimum(0.4);
   Y2S_train3__1->SetMaximum(2);
   Y2S_train3__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y2S_train3__1->SetLineColor(ci);
   Y2S_train3__1->GetXaxis()->SetBinLabel(2,"-0.20");
   Y2S_train3__1->GetXaxis()->SetBinLabel(3,"-0.10");
   Y2S_train3__1->GetXaxis()->SetBinLabel(4,"0.00");
   Y2S_train3__1->GetXaxis()->SetBinLabel(5,"0.05");
   Y2S_train3__1->GetXaxis()->SetBinLabel(6,"0.10");
   Y2S_train3__1->GetXaxis()->SetBinLabel(7,"0.15");
   Y2S_train3__1->GetXaxis()->SetBinLabel(8,"0.20");
   Y2S_train3__1->GetXaxis()->SetBinLabel(9,"0.25");
   Y2S_train3__1->GetXaxis()->SetLabelFont(42);
   Y2S_train3__1->GetXaxis()->SetTitleOffset(1);
   Y2S_train3__1->GetXaxis()->SetTitleFont(42);
   Y2S_train3__1->GetYaxis()->SetLabelFont(42);
   Y2S_train3__1->GetYaxis()->SetTitleFont(42);
   Y2S_train3__1->GetZaxis()->SetLabelFont(42);
   Y2S_train3__1->GetZaxis()->SetTitleOffset(1);
   Y2S_train3__1->GetZaxis()->SetTitleFont(42);
   Y2S_train3__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
