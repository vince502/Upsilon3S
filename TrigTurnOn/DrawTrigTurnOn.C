#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>

void DrawTrigTurnOn(){
 TFile* hfile = new TFile("MBTrigCentPlots_DiMu_2p9m_fullCut.root", "read");
 TH1D* h1 = (TH1D*) hfile->Get("h1");	//DoubleMuOpen Trigger
 TH1D* h2 = (TH1D*) hfile->Get("h2");	//DoubleMuOpenOS40100 Trigger
 TH1D* h3 = (TH1D*) hfile->Get("h3");	//DoubleMuOpen500100 Trigger

// h1->GetXaxis()->SetLimits(70,180); 
// h2->GetXaxis()->SetLimits(70,180); 
// h3->GetXaxis()->SetLimits(70,180); 

 TH1D* h2c = (TH1D*) h2->Clone();
 TH1D* h3c = (TH1D*) h3->Clone();

 h2c->Divide(h2, h1, 1, 1,"B"); 
 h3c->Divide(h3, h1, 1,1,"B");

 TCanvas* c1= new TCanvas("c1", "Trigger Centrality Distribution", 800,800);
 TCanvas* c2= new TCanvas("c2", "Trigger TurnOn", 800,800);

 c1->cd();
 c1->SetLogy();
 TLatex* tl1 = new TLatex();
 tl1->SetNDC();
 tl1->SetTextSize(0.02);
 tl1->DrawLatex(0.8,0.7,"HIDoubleMuOpen");
 h1->SetLineColor(kBlue);
 h2->SetLineColor(kRed);
 h3->SetLineColor(kMagenta);
 h1->Draw();h2->Draw("same");h3->Draw("same");

 c2->cd();
 h2c->SetLineColor(kBlue);
 h2c->SetLineStyle(1);
 h2c->SetMarkerStyle(kFullCircle);
 h2c->SetMarkerColor(kBlue);
 h3c->SetLineColor(kRed);
 h3c->SetLineStyle(1);
 h3c->SetMarkerStyle(kFullCircle);
 h3c->SetMarkerColor(kRed);

 //h2c->GetXaxis()->SetLimits(70,180); 
/// h3c->GetXaxis()->SetLimits(70,180); 
 h2c->GetXaxis()->SetRangeUser(70,180);
 h3c->GetXaxis()->SetRangeUser(70,180);

 h2c->Draw("ep");
 h3c->Draw("ep same");
 c1->SaveAs(".TrigTurnOnplots/TrigCentDist_DiMu_2p9m_fullCut.pdf");
 c2->SaveAs(".TrigTurnOnplots/TrigCentTurnOn_DiMu_2p9m_fullCut.pdf");
}
