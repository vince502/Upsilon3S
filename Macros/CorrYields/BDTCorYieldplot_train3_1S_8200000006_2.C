void BDTCorYieldplot_train3_1S_8200000006_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 15 13:15:19 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train3__1 = new TH1D("Y1S_train3__1","",9,0,9);
   Y1S_train3__1->SetBinContent(1,1);
   Y1S_train3__1->SetBinContent(2,0.9959986);
   Y1S_train3__1->SetBinContent(3,1.021065);
   Y1S_train3__1->SetBinContent(4,1.023622);
   Y1S_train3__1->SetBinContent(5,0.9923898);
   Y1S_train3__1->SetBinContent(6,0.9340628);
   Y1S_train3__1->SetBinContent(7,0.8807347);
   Y1S_train3__1->SetBinContent(8,0.8285627);
   Y1S_train3__1->SetBinContent(9,0.6664189);
   Y1S_train3__1->SetBinError(1,0.02781476);
   Y1S_train3__1->SetBinError(2,0.03647876);
   Y1S_train3__1->SetBinError(3,0.03630032);
   Y1S_train3__1->SetBinError(4,0.03614706);
   Y1S_train3__1->SetBinError(5,0.035764);
   Y1S_train3__1->SetBinError(6,0.03506966);
   Y1S_train3__1->SetBinError(7,0.03632354);
   Y1S_train3__1->SetBinError(8,0.04053164);
   Y1S_train3__1->SetBinError(9,0.04921111);
   Y1S_train3__1->SetMinimum(0.4);
   Y1S_train3__1->SetMaximum(2);
   Y1S_train3__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y1S_train3__1->SetLineColor(ci);
   Y1S_train3__1->GetXaxis()->SetBinLabel(2,"-0.20");
   Y1S_train3__1->GetXaxis()->SetBinLabel(3,"-0.10");
   Y1S_train3__1->GetXaxis()->SetBinLabel(4,"0.00");
   Y1S_train3__1->GetXaxis()->SetBinLabel(5,"0.05");
   Y1S_train3__1->GetXaxis()->SetBinLabel(6,"0.10");
   Y1S_train3__1->GetXaxis()->SetBinLabel(7,"0.15");
   Y1S_train3__1->GetXaxis()->SetBinLabel(8,"0.20");
   Y1S_train3__1->GetXaxis()->SetBinLabel(9,"0.25");
   Y1S_train3__1->GetXaxis()->SetLabelFont(42);
   Y1S_train3__1->GetXaxis()->SetTitleOffset(1);
   Y1S_train3__1->GetXaxis()->SetTitleFont(42);
   Y1S_train3__1->GetYaxis()->SetLabelFont(42);
   Y1S_train3__1->GetYaxis()->SetTitleFont(42);
   Y1S_train3__1->GetZaxis()->SetLabelFont(42);
   Y1S_train3__1->GetZaxis()->SetTitleOffset(1);
   Y1S_train3__1->GetZaxis()->SetTitleFont(42);
   Y1S_train3__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
