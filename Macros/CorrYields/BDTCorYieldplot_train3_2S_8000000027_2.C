void BDTCorYieldplot_train3_2S_8000000027_2()
{
//=========Macro generated from canvas: c1/
//=========  (Sun Nov 14 14:25:32 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y2S_train3__1 = new TH1D("Y2S_train3__1","",9,0,9);
   Y2S_train3__1->SetBinContent(1,1);
   Y2S_train3__1->SetBinContent(2,1.502786);
   Y2S_train3__1->SetBinContent(3,1.474957);
   Y2S_train3__1->SetBinContent(4,1.44577);
   Y2S_train3__1->SetBinContent(5,1.41869);
   Y2S_train3__1->SetBinContent(6,1.388003);
   Y2S_train3__1->SetBinContent(7,1.36109);
   Y2S_train3__1->SetBinContent(8,1.224903);
   Y2S_train3__1->SetBinContent(9,1.007779);
   Y2S_train3__1->SetBinError(1,0.2892203);
   Y2S_train3__1->SetBinError(2,0.4721087);
   Y2S_train3__1->SetBinError(3,0.4631325);
   Y2S_train3__1->SetBinError(4,0.4544114);
   Y2S_train3__1->SetBinError(5,0.4471392);
   Y2S_train3__1->SetBinError(6,0.4388773);
   Y2S_train3__1->SetBinError(7,0.4326277);
   Y2S_train3__1->SetBinError(8,0.4018807);
   Y2S_train3__1->SetBinError(9,0.3559549);
   Y2S_train3__1->SetMinimum(0.4);
   Y2S_train3__1->SetMaximum(2);
   Y2S_train3__1->SetEntries(9);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y2S_train3__1->SetLineColor(ci);
   Y2S_train3__1->GetXaxis()->SetBinLabel(2,"-0.10");
   Y2S_train3__1->GetXaxis()->SetBinLabel(3,"0.00");
   Y2S_train3__1->GetXaxis()->SetBinLabel(4,"0.10");
   Y2S_train3__1->GetXaxis()->SetBinLabel(5,"0.20");
   Y2S_train3__1->GetXaxis()->SetBinLabel(6,"0.30");
   Y2S_train3__1->GetXaxis()->SetBinLabel(7,"0.50");
   Y2S_train3__1->GetXaxis()->SetBinLabel(8,"0.70");
   Y2S_train3__1->GetXaxis()->SetBinLabel(9,"0.80");
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
