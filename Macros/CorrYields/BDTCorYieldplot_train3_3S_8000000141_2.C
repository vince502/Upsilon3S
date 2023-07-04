void BDTCorYieldplot_train3_3S_8000000141_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Nov 12 21:39:35 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y3S_train3__1 = new TH1D("Y3S_train3__1","",20,0,20);
   Y3S_train3__1->SetBinContent(1,1);
   Y3S_train3__1->SetBinContent(3,0.974057);
   Y3S_train3__1->SetBinContent(6,1.147958);
   Y3S_train3__1->SetBinContent(10,1.145118);
   Y3S_train3__1->SetBinContent(13,1.1135);
   Y3S_train3__1->SetBinContent(16,0.8415799);
   Y3S_train3__1->SetBinContent(17,0.7200159);
   Y3S_train3__1->SetBinContent(18,0.7472282);
   Y3S_train3__1->SetBinContent(19,0.6988063);
   Y3S_train3__1->SetBinContent(20,0.9791487);
   Y3S_train3__1->SetBinContent(21,0.6902868);
   Y3S_train3__1->SetBinError(1,0.4537244);
   Y3S_train3__1->SetBinError(3,0.5712164);
   Y3S_train3__1->SetBinError(6,0.6159717);
   Y3S_train3__1->SetBinError(10,0.6033797);
   Y3S_train3__1->SetBinError(13,0.5876927);
   Y3S_train3__1->SetBinError(16,0.484723);
   Y3S_train3__1->SetBinError(17,0.4426843);
   Y3S_train3__1->SetBinError(18,0.4507149);
   Y3S_train3__1->SetBinError(19,0.4413735);
   Y3S_train3__1->SetBinError(20,0.5552078);
   Y3S_train3__1->SetBinError(21,0.4997445);
   Y3S_train3__1->SetMinimum(0.4);
   Y3S_train3__1->SetMaximum(2);
   Y3S_train3__1->SetEntries(11);

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
