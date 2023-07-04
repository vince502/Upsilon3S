void BDTCorYieldplot_train3_1S_8000000145_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Nov 12 20:10:43 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train3__1 = new TH1D("Y1S_train3__1","",20,0,20);
   Y1S_train3__1->SetBinContent(1,1);
   Y1S_train3__1->SetBinContent(13,2.077229);
   Y1S_train3__1->SetBinContent(16,2.073215);
   Y1S_train3__1->SetBinContent(17,2.043166);
   Y1S_train3__1->SetBinContent(18,2.023765);
   Y1S_train3__1->SetBinContent(19,1.977068);
   Y1S_train3__1->SetBinContent(20,1.922);
   Y1S_train3__1->SetBinContent(21,1.94409);
   Y1S_train3__1->SetBinError(1,0.04469167);
   Y1S_train3__1->SetBinError(13,0.1064397);
   Y1S_train3__1->SetBinError(16,0.1080464);
   Y1S_train3__1->SetBinError(17,0.1071472);
   Y1S_train3__1->SetBinError(18,0.108925);
   Y1S_train3__1->SetBinError(19,0.1087792);
   Y1S_train3__1->SetBinError(20,0.1125785);
   Y1S_train3__1->SetBinError(21,0.1390022);
   Y1S_train3__1->SetMinimum(0.4);
   Y1S_train3__1->SetMaximum(2);
   Y1S_train3__1->SetEntries(8);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y1S_train3__1->SetLineColor(ci);
   Y1S_train3__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y1S_train3__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y1S_train3__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y1S_train3__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y1S_train3__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y1S_train3__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y1S_train3__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y1S_train3__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y1S_train3__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y1S_train3__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y1S_train3__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y1S_train3__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y1S_train3__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y1S_train3__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y1S_train3__1->GetXaxis()->SetBinLabel(16,"0.40");
   Y1S_train3__1->GetXaxis()->SetBinLabel(17,"0.50");
   Y1S_train3__1->GetXaxis()->SetBinLabel(18,"0.60");
   Y1S_train3__1->GetXaxis()->SetBinLabel(19,"0.70");
   Y1S_train3__1->GetXaxis()->SetBinLabel(20,"0.80");
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
