void BDTCorYieldplot_train3_3S_8000000145_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Nov 12 20:09:13 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train3__1 = new TH1D("Y3S_train3__1","",20,0,20);
   Y3S_train3__1->SetBinContent(1,1);
   Y3S_train3__1->SetBinContent(6,1.461925);
   Y3S_train3__1->SetBinContent(10,2.02632);
   Y3S_train3__1->SetBinContent(13,1.987285);
   Y3S_train3__1->SetBinContent(16,2.329769);
   Y3S_train3__1->SetBinContent(17,2.753363);
   Y3S_train3__1->SetBinContent(18,2.931681);
   Y3S_train3__1->SetBinContent(19,2.958592);
   Y3S_train3__1->SetBinContent(20,2.787565);
   Y3S_train3__1->SetBinContent(21,3.1113);
   Y3S_train3__1->SetBinError(1,0.6212195);
   Y3S_train3__1->SetBinError(6,1.05862);
   Y3S_train3__1->SetBinError(10,1.365082);
   Y3S_train3__1->SetBinError(13,1.339886);
   Y3S_train3__1->SetBinError(16,1.543002);
   Y3S_train3__1->SetBinError(17,1.793942);
   Y3S_train3__1->SetBinError(18,1.909885);
   Y3S_train3__1->SetBinError(19,1.934324);
   Y3S_train3__1->SetBinError(20,1.856684);
   Y3S_train3__1->SetBinError(21,2.146927);
   Y3S_train3__1->SetMinimum(0.4);
   Y3S_train3__1->SetMaximum(2);
   Y3S_train3__1->SetEntries(10);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y3S_train3__1->SetLineColor(ci);
   Y3S_train3__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y3S_train3__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y3S_train3__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y3S_train3__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y3S_train3__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y3S_train3__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y3S_train3__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y3S_train3__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y3S_train3__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y3S_train3__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y3S_train3__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y3S_train3__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y3S_train3__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y3S_train3__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y3S_train3__1->GetXaxis()->SetBinLabel(16,"0.40");
   Y3S_train3__1->GetXaxis()->SetBinLabel(17,"0.50");
   Y3S_train3__1->GetXaxis()->SetBinLabel(18,"0.60");
   Y3S_train3__1->GetXaxis()->SetBinLabel(19,"0.70");
   Y3S_train3__1->GetXaxis()->SetBinLabel(20,"0.80");
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
