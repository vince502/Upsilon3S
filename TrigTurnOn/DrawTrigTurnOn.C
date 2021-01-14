#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>

void DrawTrigTurnOn(const string fname = "MBTrigCentPlots_DiMu_2p9m_fullCut"){
 TFile* hfile = new TFile(Form("%s.root",fname.c_str()), "read");
 TH1D* h1 = (TH1D*) hfile->Get("h1");	//DoubleMuOpen Trigger
 TH1D* h2 = (TH1D*) hfile->Get("h2");	//DoubleMuOpenOS40100 Trigger
 TH1D* h3 = (TH1D*) hfile->Get("h3");	//DoubleMuOpen500100 Trigger

 TH1D* h2c = (TH1D*) h2->Clone();
 TH1D* h3c = (TH1D*) h3->Clone();

 h2c->Divide(h2, h1, 1, 1,"B"); 
 h3c->Divide(h3, h1, 1,1,"B");

 TCanvas* c1= new TCanvas("c1", "Trigger Centrality Distribution", 800,800);
 TCanvas* c2= new TCanvas("c2", "Trigger TurnOn", 800,800);
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);

 c1->cd();
 c1->SetLogy();
 h1->SetLineColor(kBlue);
 h2->SetLineColor(kRed);
 h3->SetLineColor(kMagenta);
 TLegend* leg1 = new TLegend(0.7,0.7,0.92,0.9);
 leg1->AddEntry(h1,"HIL1DoubleMuOpen","l"); 
 leg1->AddEntry(h2,"HIL1DoubleMuOpenOS40100","l"); 
 leg1->AddEntry(h3,"HIL1DoubleMuOpen50100","l"); 
 TLatex* tl1 = new TLatex();
 tl1->SetNDC();
 tl1->SetTextSize(0.035);
 h1->GetYaxis()->SetTitle("cBin");
 h1->Draw();h2->Draw("same");h3->Draw("same");
 leg1->Draw();
 tl1->DrawLatex(0.25,0.92,"Dimuon Trigger Centrality Distribution");
 c1->Draw();

 c2->cd();
 h2c->SetLineColor(kBlue);
 h2c->SetLineStyle(1);
 h2c->SetMarkerStyle(kFullCircle);
 h2c->SetMarkerColor(kBlue);
 h3c->SetLineColor(kRed);
 h3c->SetLineStyle(1);
 h3c->SetMarkerStyle(kFullCircle);
 h3c->SetMarkerColor(kRed);
 h2c->GetXaxis()->SetRangeUser(70,180);
 h3c->GetXaxis()->SetRangeUser(70,180);
 h2c->GetYaxis()->SetTitle("ratio");
 h2c->GetXaxis()->SetTitle("cBin");
 TLegend* leg2 = new TLegend(0.35,0.2,0.82,0.4);
 leg2->AddEntry(h2c, "Ratio of DBMuOpenOS40100 to DBMuOpen");
 leg2->AddEntry(h3c, "Ratio of DBMuOpen50100 to DBMuOpen");
 leg2->SetTextSize(0.02);
 TLatex* tl2 = new TLatex();
 tl2->SetNDC();
 tl2->SetTextSize(0.035);
 h2c->Draw("ep");
 h3c->Draw("ep same");
 leg2->Draw();
 tl2->DrawLatex(0.25,0.92,"Dimuon Trigger TurnOn Curve");
 c2->Draw();
 string ncfg = fname.c_str();
 ncfg = ncfg.erase(0,16);
 c1->SaveAs(Form("./TrigTurnOnplots/TrigCentDist_%s.pdf",ncfg.c_str()));
 c2->SaveAs(Form("./TrigTurnOnplots/TrigCentTurnOn_%s.pdf",ncfg.c_str()));
}
