void BDTCorYieldplot_train3_1S_8200000017_2()
{
//=========Macro generated from canvas: c1/
//=========  (Mon Nov 15 20:57:04 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train3__1 = new TH1D("Y1S_train3__1","",4,0,4);
   Y1S_train3__1->SetBinContent(1,1);
   Y1S_train3__1->SetBinContent(2,0.9232544);
   Y1S_train3__1->SetBinContent(3,0.8569718);
   Y1S_train3__1->SetBinContent(4,0.8318374);
   Y1S_train3__1->SetBinError(1,0.02781476);
   Y1S_train3__1->SetBinError(2,0.03548558);
   Y1S_train3__1->SetBinError(3,0.03579255);
   Y1S_train3__1->SetBinError(4,0.04053825);
   Y1S_train3__1->SetMinimum(0.4);
   Y1S_train3__1->SetMaximum(2);
   Y1S_train3__1->SetEntries(4);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y1S_train3__1->SetLineColor(ci);
   Y1S_train3__1->GetXaxis()->SetBinLabel(2,"0.50");
   Y1S_train3__1->GetXaxis()->SetBinLabel(3,"0.70");
   Y1S_train3__1->GetXaxis()->SetBinLabel(4,"0.80");
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
