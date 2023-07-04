void BDTCorYieldplot_train3_2S_9999999999_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 22 18:19:10 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train3__1 = new TH1D("Y2S_train3__1","",13,0,13);
   Y2S_train3__1->SetBinContent(1,1);
   Y2S_train3__1->SetBinContent(2,1.109376);
   Y2S_train3__1->SetBinContent(3,1.16341);
   Y2S_train3__1->SetBinContent(4,0.9567728);
   Y2S_train3__1->SetBinContent(5,1.063623);
   Y2S_train3__1->SetBinContent(6,1.081927);
   Y2S_train3__1->SetBinContent(7,1.078568);
   Y2S_train3__1->SetBinContent(8,1.069643);
   Y2S_train3__1->SetBinContent(9,1.105395);
   Y2S_train3__1->SetBinContent(10,1.130213);
   Y2S_train3__1->SetBinContent(11,1.254916);
   Y2S_train3__1->SetBinContent(12,1.204898);
   Y2S_train3__1->SetBinError(1,0.2892203);
   Y2S_train3__1->SetBinError(2,0.3964126);
   Y2S_train3__1->SetBinError(3,0.4018601);
   Y2S_train3__1->SetBinError(4,0.3475428);
   Y2S_train3__1->SetBinError(5,0.3634931);
   Y2S_train3__1->SetBinError(6,0.3663799);
   Y2S_train3__1->SetBinError(7,0.3612133);
   Y2S_train3__1->SetBinError(8,0.3575702);
   Y2S_train3__1->SetBinError(9,0.3649827);
   Y2S_train3__1->SetBinError(10,0.3703211);
   Y2S_train3__1->SetBinError(11,0.4021347);
   Y2S_train3__1->SetBinError(12,0.3882203);
   Y2S_train3__1->SetMinimum(0.4);
   Y2S_train3__1->SetMaximum(2);
   Y2S_train3__1->SetEntries(12);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y2S_train3__1->SetLineColor(ci);
   Y2S_train3__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y2S_train3__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y2S_train3__1->GetXaxis()->SetBinLabel(4,"-0.70");
   Y2S_train3__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y2S_train3__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y2S_train3__1->GetXaxis()->SetBinLabel(7,"-0.10");
   Y2S_train3__1->GetXaxis()->SetBinLabel(8,"0.00");
   Y2S_train3__1->GetXaxis()->SetBinLabel(9,"0.10");
   Y2S_train3__1->GetXaxis()->SetBinLabel(10,"0.20");
   Y2S_train3__1->GetXaxis()->SetBinLabel(11,"0.30");
   Y2S_train3__1->GetXaxis()->SetBinLabel(12,"0.40");
   Y2S_train3__1->GetXaxis()->SetBinLabel(13,"0.50");
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
