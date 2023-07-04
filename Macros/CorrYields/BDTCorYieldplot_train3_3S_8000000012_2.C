void BDTCorYieldplot_train3_3S_8000000012_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Nov 12 21:14:43 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train3__1 = new TH1D("Y3S_train3__1","",20,0,20);
   Y3S_train3__1->SetBinContent(1,1);
   Y3S_train3__1->SetBinContent(8,1.093139);
   Y3S_train3__1->SetBinContent(9,1.134491);
   Y3S_train3__1->SetBinContent(10,1.124446);
   Y3S_train3__1->SetBinContent(11,1.105884);
   Y3S_train3__1->SetBinContent(12,1.062876);
   Y3S_train3__1->SetBinContent(13,1.009586);
   Y3S_train3__1->SetBinContent(14,1.023558);
   Y3S_train3__1->SetBinContent(15,0.9846868);
   Y3S_train3__1->SetBinContent(16,1.1825);
   Y3S_train3__1->SetBinContent(17,1.252791);
   Y3S_train3__1->SetBinContent(18,1.249332);
   Y3S_train3__1->SetBinContent(19,1.270237);
   Y3S_train3__1->SetBinContent(20,1.50023);
   Y3S_train3__1->SetBinContent(21,1.618073);
   Y3S_train3__1->SetBinError(1,0.4537244);
   Y3S_train3__1->SetBinError(8,0.5785619);
   Y3S_train3__1->SetBinError(9,0.5925933);
   Y3S_train3__1->SetBinError(10,0.5877377);
   Y3S_train3__1->SetBinError(11,0.5796446);
   Y3S_train3__1->SetBinError(12,0.5613861);
   Y3S_train3__1->SetBinError(13,0.5397968);
   Y3S_train3__1->SetBinError(14,0.542214);
   Y3S_train3__1->SetBinError(15,0.5267473);
   Y3S_train3__1->SetBinError(16,0.6053335);
   Y3S_train3__1->SetBinError(17,0.6343489);
   Y3S_train3__1->SetBinError(18,0.6368997);
   Y3S_train3__1->SetBinError(19,0.6501378);
   Y3S_train3__1->SetBinError(20,0.7642475);
   Y3S_train3__1->SetBinError(21,0.9007585);
   Y3S_train3__1->SetMinimum(0.4);
   Y3S_train3__1->SetMaximum(2);
   Y3S_train3__1->SetEntries(15);

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
