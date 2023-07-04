void BDTCorYieldplot_train3_3S_9999999999_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 22 18:17:51 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train3__1 = new TH1D("Y3S_train3__1","",13,0,13);
   Y3S_train3__1->SetBinContent(1,1);
   Y3S_train3__1->SetBinContent(2,0.8037225);
   Y3S_train3__1->SetBinContent(3,0.8570589);
   Y3S_train3__1->SetBinContent(4,0.7302817);
   Y3S_train3__1->SetBinContent(5,0.7227018);
   Y3S_train3__1->SetBinContent(6,0.5285431);
   Y3S_train3__1->SetBinContent(7,0.7407681);
   Y3S_train3__1->SetBinContent(8,0.8415549);
   Y3S_train3__1->SetBinContent(9,1.025737);
   Y3S_train3__1->SetBinContent(10,1.12327);
   Y3S_train3__1->SetBinContent(11,1.07991);
   Y3S_train3__1->SetBinContent(12,0.9871906);
   Y3S_train3__1->SetBinError(1,0.4605381);
   Y3S_train3__1->SetBinError(2,0.5297174);
   Y3S_train3__1->SetBinError(3,0.5340027);
   Y3S_train3__1->SetBinError(4,0.4819921);
   Y3S_train3__1->SetBinError(5,0.4643057);
   Y3S_train3__1->SetBinError(6,0.4005149);
   Y3S_train3__1->SetBinError(7,0.4555739);
   Y3S_train3__1->SetBinError(8,0.4884546);
   Y3S_train3__1->SetBinError(9,0.5555681);
   Y3S_train3__1->SetBinError(10,0.5930244);
   Y3S_train3__1->SetBinError(11,0.573594);
   Y3S_train3__1->SetBinError(12,0.534037);
   Y3S_train3__1->SetMinimum(0.4);
   Y3S_train3__1->SetMaximum(2);
   Y3S_train3__1->SetEntries(12);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y3S_train3__1->SetLineColor(ci);
   Y3S_train3__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y3S_train3__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y3S_train3__1->GetXaxis()->SetBinLabel(4,"-0.70");
   Y3S_train3__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y3S_train3__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y3S_train3__1->GetXaxis()->SetBinLabel(7,"-0.10");
   Y3S_train3__1->GetXaxis()->SetBinLabel(8,"0.00");
   Y3S_train3__1->GetXaxis()->SetBinLabel(9,"0.10");
   Y3S_train3__1->GetXaxis()->SetBinLabel(10,"0.20");
   Y3S_train3__1->GetXaxis()->SetBinLabel(11,"0.30");
   Y3S_train3__1->GetXaxis()->SetBinLabel(12,"0.40");
   Y3S_train3__1->GetXaxis()->SetBinLabel(13,"0.50");
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
