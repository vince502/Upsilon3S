void BDTCorYieldplot_train3_1S_8000000013_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Nov 12 21:24:02 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train3__1 = new TH1D("Y1S_train3__1","",20,0,20);
   Y1S_train3__1->SetBinContent(1,1);
   Y1S_train3__1->SetBinContent(3,0.9768052);
   Y1S_train3__1->SetBinContent(6,0.9617968);
   Y1S_train3__1->SetBinContent(10,0.98109);
   Y1S_train3__1->SetBinContent(13,0.9839352);
   Y1S_train3__1->SetBinContent(16,0.9654631);
   Y1S_train3__1->SetBinContent(17,0.9536587);
   Y1S_train3__1->SetBinContent(18,0.9791412);
   Y1S_train3__1->SetBinContent(19,0.9616939);
   Y1S_train3__1->SetBinContent(20,0.9310937);
   Y1S_train3__1->SetBinContent(21,0.9287523);
   Y1S_train3__1->SetBinError(1,0.02781529);
   Y1S_train3__1->SetBinError(3,0.03898311);
   Y1S_train3__1->SetBinError(6,0.03808509);
   Y1S_train3__1->SetBinError(10,0.03622442);
   Y1S_train3__1->SetBinError(13,0.03728829);
   Y1S_train3__1->SetBinError(16,0.03740199);
   Y1S_train3__1->SetBinError(17,0.03681095);
   Y1S_train3__1->SetBinError(18,0.03715901);
   Y1S_train3__1->SetBinError(19,0.03835731);
   Y1S_train3__1->SetBinError(20,0.03871419);
   Y1S_train3__1->SetBinError(21,0.04479058);
   Y1S_train3__1->SetMinimum(0.4);
   Y1S_train3__1->SetMaximum(2);
   Y1S_train3__1->SetEntries(11);

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
