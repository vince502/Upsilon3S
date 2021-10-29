void BDTCorYieldplot_train2_1S_8000000004_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Oct 29 16:44:06 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train2__1 = new TH1D("Y1S_train2__1","",15,0,15);
   Y1S_train2__1->SetBinContent(1,1);
   Y1S_train2__1->SetBinContent(5,1.007578);
   Y1S_train2__1->SetBinContent(6,1.083517);
   Y1S_train2__1->SetBinContent(7,1.077475);
   Y1S_train2__1->SetBinContent(8,0.9894711);
   Y1S_train2__1->SetBinContent(9,0.9680426);
   Y1S_train2__1->SetBinContent(10,0.9506737);
   Y1S_train2__1->SetBinContent(11,0.9165104);
   Y1S_train2__1->SetBinContent(12,0.8918455);
   Y1S_train2__1->SetBinContent(13,0.8467163);
   Y1S_train2__1->SetBinContent(14,0.7775749);
   Y1S_train2__1->SetBinContent(15,0.765917);
   Y1S_train2__1->SetBinError(1,0.02771479);
   Y1S_train2__1->SetBinError(5,0.04029363);
   Y1S_train2__1->SetBinError(6,0.04260889);
   Y1S_train2__1->SetBinError(7,0.03898298);
   Y1S_train2__1->SetBinError(8,0.03553239);
   Y1S_train2__1->SetBinError(9,0.03511451);
   Y1S_train2__1->SetBinError(10,0.03509594);
   Y1S_train2__1->SetBinError(11,0.03502677);
   Y1S_train2__1->SetBinError(12,0.03538485);
   Y1S_train2__1->SetBinError(13,0.0374474);
   Y1S_train2__1->SetBinError(14,0.04327715);
   Y1S_train2__1->SetBinError(15,0.05742308);
   Y1S_train2__1->SetEntries(12);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y1S_train2__1->SetLineColor(ci);
   Y1S_train2__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y1S_train2__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y1S_train2__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y1S_train2__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y1S_train2__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y1S_train2__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y1S_train2__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y1S_train2__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y1S_train2__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y1S_train2__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y1S_train2__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y1S_train2__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y1S_train2__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y1S_train2__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y1S_train2__1->GetXaxis()->SetLabelFont(42);
   Y1S_train2__1->GetXaxis()->SetTitleOffset(1);
   Y1S_train2__1->GetXaxis()->SetTitleFont(42);
   Y1S_train2__1->GetYaxis()->SetLabelFont(42);
   Y1S_train2__1->GetYaxis()->SetTitleFont(42);
   Y1S_train2__1->GetZaxis()->SetLabelFont(42);
   Y1S_train2__1->GetZaxis()->SetTitleOffset(1);
   Y1S_train2__1->GetZaxis()->SetTitleFont(42);
   Y1S_train2__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
