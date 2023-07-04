void BDTCorYieldplot_train1_1S_8000000011_2()
{
//=========Macro generated from canvas: c1/
//=========  (Sat Oct 30 12:57:50 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train1__1 = new TH1D("Y1S_train1__1","",15,0,15);
   Y1S_train1__1->SetBinContent(1,1);
   Y1S_train1__1->SetBinContent(4,1.002703);
   Y1S_train1__1->SetBinContent(5,1.003066);
   Y1S_train1__1->SetBinContent(6,0.9957829);
   Y1S_train1__1->SetBinContent(7,1.007978);
   Y1S_train1__1->SetBinContent(8,0.9988235);
   Y1S_train1__1->SetBinContent(9,0.9794438);
   Y1S_train1__1->SetBinContent(10,0.943391);
   Y1S_train1__1->SetBinContent(11,0.9321431);
   Y1S_train1__1->SetBinContent(12,0.8864938);
   Y1S_train1__1->SetBinContent(13,0.8398954);
   Y1S_train1__1->SetBinContent(14,0.7648376);
   Y1S_train1__1->SetBinContent(15,0.8145517);
   Y1S_train1__1->SetBinError(1,0.02771479);
   Y1S_train1__1->SetBinError(4,0.04082587);
   Y1S_train1__1->SetBinError(5,0.04041522);
   Y1S_train1__1->SetBinError(6,0.039195);
   Y1S_train1__1->SetBinError(7,0.03675823);
   Y1S_train1__1->SetBinError(8,0.03521797);
   Y1S_train1__1->SetBinError(9,0.03483768);
   Y1S_train1__1->SetBinError(10,0.03411904);
   Y1S_train1__1->SetBinError(11,0.03449837);
   Y1S_train1__1->SetBinError(12,0.03510621);
   Y1S_train1__1->SetBinError(13,0.03707991);
   Y1S_train1__1->SetBinError(14,0.04283422);
   Y1S_train1__1->SetBinError(15,0.06031397);
   Y1S_train1__1->SetMinimum(0.4);
   Y1S_train1__1->SetMaximum(2);
   Y1S_train1__1->SetEntries(13);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y1S_train1__1->SetLineColor(ci);
   Y1S_train1__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y1S_train1__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y1S_train1__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y1S_train1__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y1S_train1__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y1S_train1__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y1S_train1__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y1S_train1__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y1S_train1__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y1S_train1__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y1S_train1__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y1S_train1__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y1S_train1__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y1S_train1__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y1S_train1__1->GetXaxis()->SetLabelFont(42);
   Y1S_train1__1->GetXaxis()->SetTitleOffset(1);
   Y1S_train1__1->GetXaxis()->SetTitleFont(42);
   Y1S_train1__1->GetYaxis()->SetLabelFont(42);
   Y1S_train1__1->GetYaxis()->SetTitleFont(42);
   Y1S_train1__1->GetZaxis()->SetLabelFont(42);
   Y1S_train1__1->GetZaxis()->SetTitleOffset(1);
   Y1S_train1__1->GetZaxis()->SetTitleFont(42);
   Y1S_train1__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
