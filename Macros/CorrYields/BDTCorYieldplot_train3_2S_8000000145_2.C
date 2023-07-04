void BDTCorYieldplot_train3_2S_8000000145_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Nov 12 20:12:51 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train3__1 = new TH1D("Y2S_train3__1","",20,0,20);
   Y2S_train3__1->SetBinContent(1,1);
   Y2S_train3__1->SetBinContent(10,4.586376);
   Y2S_train3__1->SetBinContent(13,4.641115);
   Y2S_train3__1->SetBinContent(16,4.443426);
   Y2S_train3__1->SetBinContent(17,4.389392);
   Y2S_train3__1->SetBinContent(18,4.319256);
   Y2S_train3__1->SetBinContent(19,4.461448);
   Y2S_train3__1->SetBinContent(20,3.659576);
   Y2S_train3__1->SetBinContent(21,4.590153);
   Y2S_train3__1->SetBinError(1,0.6870447);
   Y2S_train3__1->SetBinError(10,3.203127);
   Y2S_train3__1->SetBinError(13,3.238876);
   Y2S_train3__1->SetBinError(16,3.107394);
   Y2S_train3__1->SetBinError(17,3.070415);
   Y2S_train3__1->SetBinError(18,3.031501);
   Y2S_train3__1->SetBinError(19,3.132188);
   Y2S_train3__1->SetBinError(20,2.613071);
   Y2S_train3__1->SetBinError(21,3.313985);
   Y2S_train3__1->SetMinimum(0.4);
   Y2S_train3__1->SetMaximum(2);
   Y2S_train3__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y2S_train3__1->SetLineColor(ci);
   Y2S_train3__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y2S_train3__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y2S_train3__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y2S_train3__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y2S_train3__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y2S_train3__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y2S_train3__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y2S_train3__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y2S_train3__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y2S_train3__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y2S_train3__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y2S_train3__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y2S_train3__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y2S_train3__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y2S_train3__1->GetXaxis()->SetBinLabel(16,"0.40");
   Y2S_train3__1->GetXaxis()->SetBinLabel(17,"0.50");
   Y2S_train3__1->GetXaxis()->SetBinLabel(18,"0.60");
   Y2S_train3__1->GetXaxis()->SetBinLabel(19,"0.70");
   Y2S_train3__1->GetXaxis()->SetBinLabel(20,"0.80");
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
