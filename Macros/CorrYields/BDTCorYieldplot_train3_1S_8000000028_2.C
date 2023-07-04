void BDTCorYieldplot_train3_1S_8000000028_2()
{
//=========Macro generated from canvas: c1/
//=========  (Sun Nov 14 14:23:22 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train3__1 = new TH1D("Y1S_train3__1","",9,0,9);
   Y1S_train3__1->SetBinContent(1,1);
   Y1S_train3__1->SetBinContent(2,0.9652842);
   Y1S_train3__1->SetBinContent(3,0.9574465);
   Y1S_train3__1->SetBinContent(4,0.9507932);
   Y1S_train3__1->SetBinContent(5,0.9425779);
   Y1S_train3__1->SetBinContent(6,0.9319526);
   Y1S_train3__1->SetBinContent(7,0.9014916);
   Y1S_train3__1->SetBinContent(8,0.8521728);
   Y1S_train3__1->SetBinContent(9,0.8489851);
   Y1S_train3__1->SetBinError(1,0.02781476);
   Y1S_train3__1->SetBinError(2,0.03630312);
   Y1S_train3__1->SetBinError(3,0.03601909);
   Y1S_train3__1->SetBinError(4,0.03533409);
   Y1S_train3__1->SetBinError(5,0.03577411);
   Y1S_train3__1->SetBinError(6,0.03567365);
   Y1S_train3__1->SetBinError(7,0.03501173);
   Y1S_train3__1->SetBinError(8,0.03541512);
   Y1S_train3__1->SetBinError(9,0.03732349);
   Y1S_train3__1->SetMinimum(0.4);
   Y1S_train3__1->SetMaximum(2);
   Y1S_train3__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y1S_train3__1->SetLineColor(ci);
   Y1S_train3__1->GetXaxis()->SetBinLabel(2,"-0.10");
   Y1S_train3__1->GetXaxis()->SetBinLabel(3,"0.00");
   Y1S_train3__1->GetXaxis()->SetBinLabel(4,"0.10");
   Y1S_train3__1->GetXaxis()->SetBinLabel(5,"0.20");
   Y1S_train3__1->GetXaxis()->SetBinLabel(6,"0.30");
   Y1S_train3__1->GetXaxis()->SetBinLabel(7,"0.50");
   Y1S_train3__1->GetXaxis()->SetBinLabel(8,"0.70");
   Y1S_train3__1->GetXaxis()->SetBinLabel(9,"0.80");
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
