void BDTCorYieldplot_train3_2S_8000000141_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Nov 12 21:39:10 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train3__1 = new TH1D("Y2S_train3__1","",20,0,20);
   Y2S_train3__1->SetBinContent(1,1);
   Y2S_train3__1->SetBinContent(3,0.9685518);
   Y2S_train3__1->SetBinContent(6,1.066896);
   Y2S_train3__1->SetBinContent(10,1.103588);
   Y2S_train3__1->SetBinContent(13,1.036878);
   Y2S_train3__1->SetBinContent(16,0.9220043);
   Y2S_train3__1->SetBinContent(17,0.9074546);
   Y2S_train3__1->SetBinContent(18,0.8733476);
   Y2S_train3__1->SetBinContent(19,0.9354244);
   Y2S_train3__1->SetBinContent(20,0.9981193);
   Y2S_train3__1->SetBinContent(21,0.8428181);
   Y2S_train3__1->SetBinError(1,0.2855421);
   Y2S_train3__1->SetBinError(3,0.3628452);
   Y2S_train3__1->SetBinError(6,0.3726891);
   Y2S_train3__1->SetBinError(10,0.3638753);
   Y2S_train3__1->SetBinError(13,0.3463627);
   Y2S_train3__1->SetBinError(16,0.3179616);
   Y2S_train3__1->SetBinError(17,0.3148867);
   Y2S_train3__1->SetBinError(18,0.306005);
   Y2S_train3__1->SetBinError(19,0.3253591);
   Y2S_train3__1->SetBinError(20,0.3482351);
   Y2S_train3__1->SetBinError(21,0.3342008);
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
