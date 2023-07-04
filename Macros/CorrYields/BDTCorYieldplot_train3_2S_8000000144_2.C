void BDTCorYieldplot_train3_2S_8000000144_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Nov 12 21:46:17 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train3__1 = new TH1D("Y2S_train3__1","",21,0,21);
   Y2S_train3__1->SetBinContent(1,1);
   Y2S_train3__1->SetBinContent(3,1.129541);
   Y2S_train3__1->SetBinContent(6,1.151129);
   Y2S_train3__1->SetBinContent(10,1.374282);
   Y2S_train3__1->SetBinContent(13,1.366043);
   Y2S_train3__1->SetBinContent(16,1.47702);
   Y2S_train3__1->SetBinContent(17,1.571123);
   Y2S_train3__1->SetBinContent(18,1.470245);
   Y2S_train3__1->SetBinContent(19,1.196456);
   Y2S_train3__1->SetBinContent(20,1.231246);
   Y2S_train3__1->SetBinContent(21,1.495312);
   Y2S_train3__1->SetBinError(1,0.2855421);
   Y2S_train3__1->SetBinError(3,0.4089654);
   Y2S_train3__1->SetBinError(6,0.3947567);
   Y2S_train3__1->SetBinError(10,0.4348736);
   Y2S_train3__1->SetBinError(13,0.43229);
   Y2S_train3__1->SetBinError(16,0.4612387);
   Y2S_train3__1->SetBinError(17,0.4793492);
   Y2S_train3__1->SetBinError(18,0.4602497);
   Y2S_train3__1->SetBinError(19,0.3857154);
   Y2S_train3__1->SetBinError(20,0.4089919);
   Y2S_train3__1->SetBinError(21,0.5065233);
   Y2S_train3__1->SetMinimum(0.4);
   Y2S_train3__1->SetMaximum(2);
   Y2S_train3__1->SetEntries(11);

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
   Y2S_train3__1->GetXaxis()->SetBinLabel(21,"0.90");
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
