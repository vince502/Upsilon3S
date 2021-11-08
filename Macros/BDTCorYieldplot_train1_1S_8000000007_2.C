void BDTCorYieldplot_train1_1S_8000000007_2()
{
//=========Macro generated from canvas: c1/
//=========  (Fri Oct 29 21:13:31 2021) by ROOT version 6.24/06
   TCanvas *c1 = new TCanvas("c1", "",0,0,1000,600);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameBorderMode(0);
   
   TH1D *Y1S_train1__1 = new TH1D("Y1S_train1__1","",15,0,15);
   Y1S_train1__1->SetBinContent(1,1);
   Y1S_train1__1->SetBinContent(2,1.073629);
   Y1S_train1__1->SetBinContent(3,1.073629);
   Y1S_train1__1->SetBinContent(4,1.073629);
   Y1S_train1__1->SetBinContent(5,0.9982118);
   Y1S_train1__1->SetBinContent(6,0.9879045);
   Y1S_train1__1->SetBinContent(7,0.9911161);
   Y1S_train1__1->SetBinContent(8,0.9836101);
   Y1S_train1__1->SetBinContent(9,0.9590687);
   Y1S_train1__1->SetBinContent(10,0.9293536);
   Y1S_train1__1->SetBinContent(11,0.9030884);
   Y1S_train1__1->SetBinContent(12,0.8542461);
   Y1S_train1__1->SetBinContent(13,0.811404);
   Y1S_train1__1->SetBinContent(14,0.7290326);
   Y1S_train1__1->SetBinContent(15,0.7599073);
   Y1S_train1__1->SetBinError(1,0.02771479);
   Y1S_train1__1->SetBinError(2,0.04169532);
   Y1S_train1__1->SetBinError(3,0.04169532);
   Y1S_train1__1->SetBinError(4,0.04169532);
   Y1S_train1__1->SetBinError(5,0.03983115);
   Y1S_train1__1->SetBinError(6,0.0386757);
   Y1S_train1__1->SetBinError(7,0.03625777);
   Y1S_train1__1->SetBinError(8,0.03530945);
   Y1S_train1__1->SetBinError(9,0.03420957);
   Y1S_train1__1->SetBinError(10,0.03386557);
   Y1S_train1__1->SetBinError(11,0.0336291);
   Y1S_train1__1->SetBinError(12,0.03422381);
   Y1S_train1__1->SetBinError(13,0.03679874);
   Y1S_train1__1->SetBinError(14,0.04143107);
   Y1S_train1__1->SetBinError(15,0.05695916);
   Y1S_train1__1->SetEntries(15);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Y1S_train1__1->SetLineColor(ci);
   Y1S_train1__1->GetXaxis()->SetBinLabel(2,"-0.90");
   Y1S_train1__1->GetXaxis()->SetBinLabel(3,"-0.80");
   Y1S_train1__1->GetXaxis()->SetBinLabel(4,"-0.60");
   Y1S_train1__1->GetXaxis()->SetBinLabel(5,"-0.40");
   Y1S_train1__1->GetXaxis()->SetBinLabel(6,"-0.30");
   Y1S_train1__1->GetXaxis()->SetBinLabel(7,"-0.20");
   Y1S_train1__1->GetXaxis()->SetBinLabel(8,"-0.05");
   Y1S_train1__1->GetXaxis()->SetBinLabel(9,"0.00");
   Y1S_train1__1->GetXaxis()->SetBinLabel(10,"0.05");
   Y1S_train1__1->GetXaxis()->SetBinLabel(11,"0.10");
   Y1S_train1__1->GetXaxis()->SetBinLabel(12,"0.15");
   Y1S_train1__1->GetXaxis()->SetBinLabel(13,"0.20");
   Y1S_train1__1->GetXaxis()->SetBinLabel(14,"0.25");
   Y1S_train1__1->GetXaxis()->SetBinLabel(15,"0.30");
   Y1S_train1__1->GetXaxis()->SetLabelFont(42);
   Y1S_train1__1->GetXaxis()->SetTitleOffset(1);
   Y1S_train1__1->GetXaxis()->SetTitleFont(42);
   Y1S_train1__1->GetYaxis()->SetLabelFont(42);
   Y1S_train1__1->GetYaxis()->SetTitleFont(42);
   Y1S_train1__1->GetZaxis()->SetLabelFont(42);
   Y1S_train1__1->GetZaxis()->SetTitleOffset(1);
   Y1S_train1__1->GetZaxis()->SetTitleFont(42);
   Y1S_train1__1->Draw("pe");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
