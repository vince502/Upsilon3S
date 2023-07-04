void BDTCorYieldplot_train1_3S_8000000004_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Oct 29 17:05:45 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train1__1 = new TH1D("Y3S_train1__1","",15,0,15);
   Y3S_train1__1->SetBinContent(1,1);
   Y3S_train1__1->SetBinContent(2,0.9820395);
   Y3S_train1__1->SetBinContent(3,0.9820395);
   Y3S_train1__1->SetBinContent(4,0.9820395);
   Y3S_train1__1->SetBinContent(5,1.057037);
   Y3S_train1__1->SetBinContent(6,1.123498);
   Y3S_train1__1->SetBinContent(7,0.7863612);
   Y3S_train1__1->SetBinContent(8,0.6960138);
   Y3S_train1__1->SetBinContent(9,0.8682865);
   Y3S_train1__1->SetBinContent(10,1.061927);
   Y3S_train1__1->SetBinContent(11,1.099913);
   Y3S_train1__1->SetBinContent(12,1.391401);
   Y3S_train1__1->SetBinContent(13,1.12353);
   Y3S_train1__1->SetBinContent(14,0.9185306);
   Y3S_train1__1->SetBinContent(15,1.104624);
   Y3S_train1__1->SetBinError(1,0.4315022);
   Y3S_train1__1->SetBinError(2,0.6130183);
   Y3S_train1__1->SetBinError(3,0.6130183);
   Y3S_train1__1->SetBinError(4,0.6130183);
   Y3S_train1__1->SetBinError(5,0.6371261);
   Y3S_train1__1->SetBinError(6,0.6491393);
   Y3S_train1__1->SetBinError(7,0.4950476);
   Y3S_train1__1->SetBinError(8,0.4067366);
   Y3S_train1__1->SetBinError(9,0.4586402);
   Y3S_train1__1->SetBinError(10,0.5243535);
   Y3S_train1__1->SetBinError(11,0.5372365);
   Y3S_train1__1->SetBinError(12,0.6566865);
   Y3S_train1__1->SetBinError(13,0.5695513);
   Y3S_train1__1->SetBinError(14,0.5368042);
   Y3S_train1__1->SetBinError(15,0.7030031);
   Y3S_train1__1->SetEntries(15);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y3S_train1__1->SetLineColor(ci);
   Y3S_train1__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y3S_train1__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y3S_train1__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y3S_train1__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y3S_train1__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y3S_train1__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y3S_train1__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y3S_train1__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y3S_train1__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y3S_train1__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y3S_train1__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y3S_train1__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y3S_train1__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y3S_train1__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y3S_train1__1->GetXaxis()->SetLabelFont(42);
   Y3S_train1__1->GetXaxis()->SetTitleOffset(1);
   Y3S_train1__1->GetXaxis()->SetTitleFont(42);
   Y3S_train1__1->GetYaxis()->SetLabelFont(42);
   Y3S_train1__1->GetYaxis()->SetTitleFont(42);
   Y3S_train1__1->GetZaxis()->SetLabelFont(42);
   Y3S_train1__1->GetZaxis()->SetTitleOffset(1);
   Y3S_train1__1->GetZaxis()->SetTitleFont(42);
   Y3S_train1__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
