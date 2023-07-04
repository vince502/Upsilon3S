#include "Graphix.h"
#include "Style_HIN-21-007.C"
#include "../CMS_lumi_square.C"

void MergeGraphix(){

//	TFile* f_raa_sc1 = TFile::Open("resultRAA_200019111111_raw_v3_Scenario-1.root");
//	TFile* f_raa_sc2 = TFile::Open("resultRAA_200019111111_raw_v3_Scenario-2.root");
//	TFile* f_raa_sc3 = TFile::Open("resultRAA_200019111111_raw_v3_Scenario-3.root");
//	TFile* f_raa_sc4 = TFile::Open("resultRAA_200019111111_raw_v3_Scenario-4.root");
//
//	TFile* f_dr_sc1 = TFile::Open("resultDR_200019111111_raw_v3_Scenario-1.root");
//	TFile* f_dr_sc2 = TFile::Open("resultDR_200019111111_raw_v3_Scenario-2.root");
//	TFile* f_dr_sc3 = TFile::Open("resultDR_200019111111_raw_v3_Scenario-3.root");
//	TFile* f_dr_sc4 = TFile::Open("resultDR_200019111111_raw_v3_Scenario-4.root");

	auto getG = [](int sc, bool dr, string namegraph){
		string dir = "./result";
		string fname = (dr) ? Form("%s/resultDR_200019111111_raw_v3_Scenario-%d.root", dir.c_str(), sc) : Form("%s/resultRAA_w1s_200019111111_raw_v3_Scenario-%d.root", dir.c_str(), sc);
		TFile* f = TFile::Open(fname.c_str());
		auto g = (TGraphAsymmErrors*) f->Get(Form("vanila/%s", namegraph.c_str()));
		if (g == nullptr) std::cout<< "Could not get " << namegraph.c_str() << std::endl;
		auto gx  =	Graphix<TGraphAsymmErrors>(g);
		f->Close();
		return gx;
	};
	const string btype = "p";
	const string Btype = "P";
	const string stype = "PT";
	std::map<string, Graphix<TGraphAsymmErrors> > vG;
	vG[Form("0r1%s", btype.c_str())] = getG(0, 0 , Form("g_%s1s", btype.c_str()));
	vG[Form("0r2%s", btype.c_str())] = getG(0, 0 , Form("g_%s2s", btype.c_str()));
	vG[Form("0r3%s", btype.c_str())] = getG(0, 0 , Form("g_%s3s", btype.c_str()));
	vG[Form("0r23%s", btype.c_str())] = getG(0, 1 , Form("g_%s23s", btype.c_str()));
	vG[Form("1r1%s", btype.c_str())] = getG(1, 0 , Form("g_%s1s", btype.c_str()));
	vG[Form("1r2%s", btype.c_str())] = getG(1, 0 , Form("g_%s2s", btype.c_str()));
	vG[Form("1r3%s", btype.c_str())] = getG(1, 0 , Form("g_%s3s", btype.c_str()));
	vG[Form("1r23%s", btype.c_str())] = getG(1, 1 , Form("g_%s23s", btype.c_str()));
	vG[Form("2r1%s", btype.c_str())] = getG(2, 0 , Form("g_%s1s", btype.c_str()));
	vG[Form("2r2%s", btype.c_str())] = getG(2, 0 , Form("g_%s2s", btype.c_str()));
	vG[Form("2r3%s", btype.c_str())] = getG(2, 0 , Form("g_%s3s", btype.c_str()));
	vG[Form("2r23%s", btype.c_str())] = getG(2, 1 , Form("g_%s23s", btype.c_str()));
	vG[Form("3r1%s", btype.c_str())] = getG(3, 0 , Form("g_%s1s", btype.c_str()));
	vG[Form("3r2%s", btype.c_str())] = getG(3, 0 , Form("g_%s2s", btype.c_str()));
	vG[Form("3r3%s", btype.c_str())] = getG(3, 0 , Form("g_%s3s", btype.c_str()));
	vG[Form("3r23%s", btype.c_str())] = getG(3, 1 , Form("g_%s23s", btype.c_str()));
	vG[Form("4r1%s", btype.c_str())] = getG(4, 0 , Form("g_%s1s", btype.c_str()));
	vG[Form("4r2%s", btype.c_str())] = getG(4, 0 , Form("g_%s2s", btype.c_str()));
	vG[Form("4r3%s", btype.c_str())] = getG(4, 0 , Form("g_%s3s", btype.c_str()));
	vG[Form("4r23%s", btype.c_str())] = getG(4, 1 , Form("g_%s23s", btype.c_str()));

	vG[Form("0r1%ssys", btype.c_str())] = getG(0, 0 , Form("g_%s1s_sys", btype.c_str()));
	vG[Form("0r2%ssys", btype.c_str())] = getG(0, 0 , Form("g_%s2s_sys", btype.c_str()));
	vG[Form("0r3%ssys", btype.c_str())] = getG(0, 0 , Form("g_%s3s_sys", btype.c_str()));
	vG[Form("0r23%ssys", btype.c_str())] = getG(0, 1 , Form("g_%s23s_sys", btype.c_str()));
	vG[Form("1r1%ssys", btype.c_str())] = getG(1, 0 , Form("g_%s1s_sys", btype.c_str()));
	vG[Form("1r2%ssys", btype.c_str())] = getG(1, 0 , Form("g_%s2s_sys", btype.c_str()));
	vG[Form("1r3%ssys", btype.c_str())] = getG(1, 0 , Form("g_%s3s_sys", btype.c_str()));
	vG[Form("1r23%ssys", btype.c_str())] = getG(1, 1 , Form("g_%s23s_sys", btype.c_str()));
	vG[Form("2r1%ssys", btype.c_str())] = getG(2, 0 , Form("g_%s1s_sys", btype.c_str()));
	vG[Form("2r2%ssys", btype.c_str())] = getG(2, 0 , Form("g_%s2s_sys", btype.c_str()));
	vG[Form("2r3%ssys", btype.c_str())] = getG(2, 0 , Form("g_%s3s_sys", btype.c_str()));
	vG[Form("2r23%ssys", btype.c_str())] = getG(2, 1 , Form("g_%s23s_sys", btype.c_str()));
	vG[Form("3r1%ssys", btype.c_str())] = getG(3, 0 , Form("g_%s1s_sys", btype.c_str()));
	vG[Form("3r2%ssys", btype.c_str())] = getG(3, 0 , Form("g_%s2s_sys", btype.c_str()));
	vG[Form("3r3%ssys", btype.c_str())] = getG(3, 0 , Form("g_%s3s_sys", btype.c_str()));
	vG[Form("3r23%ssys", btype.c_str())] = getG(3, 1 , Form("g_%s23s_sys", btype.c_str()));
	vG[Form("4r1%ssys", btype.c_str())] = getG(4, 0 , Form("g_%s1s_sys", btype.c_str()));
	vG[Form("4r2%ssys", btype.c_str())] = getG(4, 0 , Form("g_%s2s_sys", btype.c_str()));
	vG[Form("4r3%ssys", btype.c_str())] = getG(4, 0 , Form("g_%s3s_sys", btype.c_str()));
	vG[Form("4r23%ssys", btype.c_str())] = getG(4, 1 , Form("g_%s23s_sys", btype.c_str()));

	vG[Form("0r1%ssys", btype.c_str())].shiftBins(0);
	vG[Form("0r2%ssys", btype.c_str())].shiftBins(0);
	vG[Form("0r3%ssys", btype.c_str())].shiftBins(0);
	vG[Form("0r23%ssys", btype.c_str())].shiftBins(0);
	vG[Form("0r1%s", btype.c_str())].shiftBins(0); 
	vG[Form("0r2%s", btype.c_str())].shiftBins(0);
	vG[Form("0r3%s", btype.c_str())].shiftBins(0);
	vG[Form("0r23%s", btype.c_str())].shiftBins(0);

	vG[Form("1r1%ssys", btype.c_str())].shiftBins(0.2);
	vG[Form("1r2%ssys", btype.c_str())].shiftBins(0.2);
	vG[Form("1r3%ssys", btype.c_str())].shiftBins(0.2);
	vG[Form("1r23%ssys", btype.c_str())].shiftBins(0.2);
	vG[Form("1r1%s", btype.c_str())].shiftBins(0.2); 
	vG[Form("1r2%s", btype.c_str())].shiftBins(0.2);
	vG[Form("1r3%s", btype.c_str())].shiftBins(0.2);
	vG[Form("1r23%s", btype.c_str())].shiftBins(0.2);

	vG[Form("2r1%ssys", btype.c_str())].shiftBins(0.4);
	vG[Form("2r2%ssys", btype.c_str())].shiftBins(0.4);
	vG[Form("2r3%ssys", btype.c_str())].shiftBins(0.4);
	vG[Form("2r23%ssys", btype.c_str())].shiftBins(0.4);
	vG[Form("2r1%s", btype.c_str())].shiftBins(0.4); 
	vG[Form("2r2%s", btype.c_str())].shiftBins(0.4);
	vG[Form("2r3%s", btype.c_str())].shiftBins(0.4);
	vG[Form("2r23%s", btype.c_str())].shiftBins(0.4);

	vG[Form("3r1%ssys", btype.c_str())].shiftBins(0.6);
	vG[Form("3r2%ssys", btype.c_str())].shiftBins(0.6);
	vG[Form("3r3%ssys", btype.c_str())].shiftBins(0.6);
	vG[Form("3r23%ssys", btype.c_str())].shiftBins(0.6);
	vG[Form("3r1%s", btype.c_str())].shiftBins(0.6); 
	vG[Form("3r2%s", btype.c_str())].shiftBins(0.6);
	vG[Form("3r3%s", btype.c_str())].shiftBins(0.6);
	vG[Form("3r23%s", btype.c_str())].shiftBins(0.6);

	vG[Form("4r1%ssys", btype.c_str())].shiftBins(0.8);
	vG[Form("4r2%ssys", btype.c_str())].shiftBins(0.8);
	vG[Form("4r3%ssys", btype.c_str())].shiftBins(0.8);
	vG[Form("4r23%ssys", btype.c_str())].shiftBins(0.8);
	vG[Form("4r1%s", btype.c_str())].shiftBins(0.8); 
	vG[Form("4r2%s", btype.c_str())].shiftBins(0.8);
	vG[Form("4r3%s", btype.c_str())].shiftBins(0.8);
	vG[Form("4r23%s", btype.c_str())].shiftBins(0.8);

	readyPlot(vG[Form("0r1%s", btype.c_str())].getObject(),  vG[Form("0r1%ssys", btype.c_str())].getObject(), Form("PA1S%s", stype.c_str())); 
	readyPlot(vG[Form("0r2%s", btype.c_str())].getObject(),  vG[Form("0r2%ssys", btype.c_str())].getObject(), Form("CA2S%s", stype.c_str()));
	readyPlot(vG[Form("0r3%s", btype.c_str())].getObject(),  vG[Form("0r3%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));
	readyPlot(vG[Form("0r23%s", btype.c_str())].getObject(),  vG[Form("0r23%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));
	readyPlot(vG[Form("1r1%s", btype.c_str())].getObject(),  vG[Form("1r1%ssys", btype.c_str())].getObject(), Form("PA1S%s", stype.c_str())); 
	readyPlot(vG[Form("1r2%s", btype.c_str())].getObject(),  vG[Form("1r2%ssys", btype.c_str())].getObject(), Form("CA2S%s", stype.c_str()));
	readyPlot(vG[Form("1r3%s", btype.c_str())].getObject(),  vG[Form("1r3%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));
	readyPlot(vG[Form("1r23%s", btype.c_str())].getObject(),  vG[Form("1r23%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));
	readyPlot(vG[Form("2r1%s", btype.c_str())].getObject(),  vG[Form("2r1%ssys", btype.c_str())].getObject(), Form("PA1S%s", stype.c_str()));
	readyPlot(vG[Form("2r2%s", btype.c_str())].getObject(),  vG[Form("2r2%ssys", btype.c_str())].getObject(), Form("CA2S%s", stype.c_str()));
	readyPlot(vG[Form("2r3%s", btype.c_str())].getObject(),  vG[Form("2r3%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));
	readyPlot(vG[Form("2r23%s", btype.c_str())].getObject(),  vG[Form("2r23%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));
	readyPlot(vG[Form("3r1%s", btype.c_str())].getObject(),  vG[Form("3r1%ssys", btype.c_str())].getObject(), Form("PA1S%s", stype.c_str()));
	readyPlot(vG[Form("3r2%s", btype.c_str())].getObject(),  vG[Form("3r2%ssys", btype.c_str())].getObject(), Form("CA2S%s", stype.c_str()));
	readyPlot(vG[Form("3r3%s", btype.c_str())].getObject(),  vG[Form("3r3%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));
	readyPlot(vG[Form("3r23%s", btype.c_str())].getObject(),  vG[Form("3r23%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));
	readyPlot(vG[Form("4r1%s", btype.c_str())].getObject(),  vG[Form("4r1%ssys", btype.c_str())].getObject(), Form("PA1S%s", stype.c_str()));
	readyPlot(vG[Form("4r2%s", btype.c_str())].getObject(),  vG[Form("4r2%ssys", btype.c_str())].getObject(), Form("CA2S%s", stype.c_str()));
	readyPlot(vG[Form("4r3%s", btype.c_str())].getObject(),  vG[Form("4r3%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));
	readyPlot(vG[Form("4r23%s", btype.c_str())].getObject(),  vG[Form("4r23%ssys", btype.c_str())].getObject(), Form("CA3S%s", stype.c_str()));

	gStyle->SetEndErrorSize(0);


	TCanvas* c1 =new TCanvas("c1", "" , 800, 720);
	c1->cd();
	vG[Form("0r1%ssys", btype.c_str())].getObject()->Draw("A5");
	vG[Form("0r2%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("0r3%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("0r1%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("0r2%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("0r3%s", btype.c_str())].getObject()->Draw("PE");

	vG[Form("1r1%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("1r2%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("1r3%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("1r1%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("1r2%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("1r3%s", btype.c_str())].getObject()->Draw("PE");

	vG[Form("2r1%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("2r2%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("2r3%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("2r1%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("2r2%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("2r3%s", btype.c_str())].getObject()->Draw("PE");

	vG[Form("3r1%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("3r2%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("3r3%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("3r1%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("3r2%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("3r3%s", btype.c_str())].getObject()->Draw("PE");

	vG[Form("4r1%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("4r2%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("4r3%ssys", btype.c_str())].getObject()->Draw("5");
	vG[Form("4r1%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("4r2%s", btype.c_str())].getObject()->Draw("PE");
	vG[Form("4r3%s", btype.c_str())].getObject()->Draw("PE");

	CMS_lumi_square((TPad*) c1->GetPad(0), 1030, 33, 1);
	c1->Draw();
	c1->SaveAs("../checkout/tscol/AUX/testtest.pdf");


	TCanvas* c2 =new TCanvas("c2", "" , 900, 800);
	c2->cd();


	vG[Form("0r1%s", btype.c_str())] / vG[Form("0r1%s", btype.c_str())];
	vG[Form("0r1%ssys", btype.c_str())] / vG[Form("0r1%ssys", btype.c_str())];
	readyPlot(vG[Form("0r1%s", btype.c_str())].getDerivedObject(),  vG[Form("0r1%ssys", btype.c_str())].getDerivedObject(), Form("PA1S%s", stype.c_str())); 

	vG[Form("1r1%s", btype.c_str())] / vG[Form("0r1%s", btype.c_str())];
	vG[Form("1r1%ssys", btype.c_str())] / vG[Form("0r1%ssys", btype.c_str())];
	readyPlot(vG[Form("1r1%s", btype.c_str())].getDerivedObject(),  vG[Form("1r1%ssys", btype.c_str())].getDerivedObject(), Form("AA1S%s", stype.c_str())); 

	vG[Form("2r1%s", btype.c_str())] / vG[Form("0r1%s", btype.c_str())];
	vG[Form("2r1%ssys", btype.c_str())] / vG[Form("0r1%ssys", btype.c_str())];
	readyPlot(vG[Form("2r1%s", btype.c_str())].getDerivedObject(),  vG[Form("2r1%ssys", btype.c_str())].getDerivedObject(), Form("A2A1S%s", stype.c_str())); 

	vG[Form("0r2%s", btype.c_str())] / vG[Form("0r2%s", btype.c_str())];
	vG[Form("0r2%ssys", btype.c_str())] / vG[Form("0r2%ssys", btype.c_str())];
	readyPlot(vG[Form("0r2%s", btype.c_str())].getDerivedObject(),  vG[Form("0r2%ssys", btype.c_str())].getDerivedObject(), Form("CA2S%s", stype.c_str())); 

	vG[Form("1r2%s", btype.c_str())] / vG[Form("0r2%s", btype.c_str())];
	vG[Form("1r2%ssys", btype.c_str())] / vG[Form("0r2%ssys", btype.c_str())];
	readyPlot(vG[Form("1r2%s", btype.c_str())].getDerivedObject(),  vG[Form("1r2%ssys", btype.c_str())].getDerivedObject(), Form("AA2S%s", stype.c_str())); 

	vG[Form("2r2%s", btype.c_str())] / vG[Form("0r2%s", btype.c_str())];
	vG[Form("2r2%ssys", btype.c_str())] / vG[Form("0r2%ssys", btype.c_str())];
	readyPlot(vG[Form("2r2%s", btype.c_str())].getDerivedObject(),  vG[Form("2r2%ssys", btype.c_str())].getDerivedObject(), Form("A2A2S%s", stype.c_str())); 

	vG[Form("0r3%s", btype.c_str())] / vG[Form("0r3%s", btype.c_str())];
	vG[Form("0r3%ssys", btype.c_str())] / vG[Form("0r3%ssys", btype.c_str())];
	readyPlot(vG[Form("0r3%s", btype.c_str())].getDerivedObject(),  vG[Form("0r3%ssys", btype.c_str())].getDerivedObject(), Form("CA3S%s", stype.c_str())); 

	vG[Form("1r3%s", btype.c_str())] / vG[Form("0r3%s", btype.c_str())];
	vG[Form("1r3%ssys", btype.c_str())] / vG[Form("0r3%ssys", btype.c_str())];
	readyPlot(vG[Form("1r3%s", btype.c_str())].getDerivedObject(),  vG[Form("1r3%ssys", btype.c_str())].getDerivedObject(), Form("AA3S%s", stype.c_str())); 

	vG[Form("2r3%s", btype.c_str())] / vG[Form("0r3%s", btype.c_str())];
	vG[Form("2r3%ssys", btype.c_str())] / vG[Form("0r3%ssys", btype.c_str())];
	readyPlot(vG[Form("2r3%s", btype.c_str())].getDerivedObject(),  vG[Form("2r3%ssys", btype.c_str())].getDerivedObject(), Form("A2A3S%s", stype.c_str())); 

	globalOffSetY(0.4, vG[Form("0r1%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(0.4, vG[Form("0r1%s", btype.c_str())].getDerivedObject());

	globalOffSetY(0.4, vG[Form("1r1%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(0.4, vG[Form("1r1%s", btype.c_str())].getDerivedObject());

	globalOffSetY(0.4, vG[Form("2r1%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(0.4, vG[Form("2r1%s", btype.c_str())].getDerivedObject());

	globalOffSetY(-0.0, vG[Form("0r2%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.0, vG[Form("0r2%s", btype.c_str())].getDerivedObject());

	globalOffSetY(-0.0, vG[Form("1r2%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.0, vG[Form("1r2%s", btype.c_str())].getDerivedObject());

	globalOffSetY(-0.0, vG[Form("2r2%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.0, vG[Form("2r2%s", btype.c_str())].getDerivedObject());

	globalOffSetY(-0.5, vG[Form("0r3%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.5, vG[Form("0r3%s", btype.c_str())].getDerivedObject());

	globalOffSetY(-0.5, vG[Form("1r3%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.5, vG[Form("1r3%s", btype.c_str())].getDerivedObject());

	globalOffSetY(-0.5, vG[Form("2r3%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.5, vG[Form("2r3%s", btype.c_str())].getDerivedObject());

	vG[Form("0r1%ssys", btype.c_str())].getDerivedObject()->GetYaxis()->SetTitle("Relative uncertainty (tick = 10\%)");
	vG[Form("0r1%ssys", btype.c_str())].getDerivedObject()->GetYaxis()->SetRangeUser(-0.2, 2);
	vG[Form("0r1%ssys", btype.c_str())].getDerivedObject()->GetYaxis()->SetLabelSize(0);
	vG[Form("0r1%ssys", btype.c_str())].getDerivedObject()->GetXaxis()->SetLimits(-2, 35);
	vG[Form("0r1%ssys", btype.c_str())].getDerivedObject()->GetXaxis()->SetRangeUser(-2, 35);
	vG[Form("0r1%ssys", btype.c_str())].getDerivedObject()->GetXaxis()->SetTitle("p_{T} (GeV)");
	vG[Form("0r1%ssys", btype.c_str())].getDerivedObject()->Draw("A5");
	vG[Form("0r1%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("1r1%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("1r1%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("2r1%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("2r1%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("0r2%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("0r2%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("1r2%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("1r2%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("2r2%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("2r2%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("0r3%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("0r3%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("1r3%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("1r3%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("2r3%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("2r3%s", btype.c_str())].getDerivedObject()->Draw("PE");

	TLegend* leg= new TLegend(0.35, 0.12, 0.88, 0.22, ""); 
	TLegend* leg2= new TLegend(0.35, 0.12, 0.88, 0.22, ""); 
	leg->SetBorderSize(0);
	leg2->SetBorderSize(0);
	leg2->SetFillStyle(0);
	leg->SetFillStyle(0);
	leg->SetNColumns(3);
	leg2->SetNColumns(3);
	leg->SetTextSize(0.021);
	leg2->SetTextSize(0.021);
	leg->SetTextFont(42);
	leg2->SetTextFont(42);

	leg2->AddEntry(vG[Form("0r1%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(1S), Run2 2015", "f");
	leg2->AddEntry(vG[Form("1r1%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(1S), 4.5 nb^{-1}", "f");
	leg2->AddEntry(vG[Form("2r1%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(1S), 7.2 nb^{-1}", "f");
	leg2->AddEntry(vG[Form("0r2%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(2S), Run2 2018", "f");
	leg2->AddEntry(vG[Form("1r2%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(2S), 4.5 nb^{-1}", "f");
	leg2->AddEntry(vG[Form("2r2%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(2S), 7.2 nb^{-1}", "f");
	leg2->AddEntry(vG[Form("0r3%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(3S), Run2 2018", "f");
	leg2->AddEntry(vG[Form("1r3%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(3S), 4.5 nb^{-1}", "f");
	leg2->AddEntry(vG[Form("2r3%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(3S), 7.2 nb^{-1}", "f");
	leg->AddEntry(vG[Form("0r1%s", btype.c_str())].getDerivedObject(), "#Upsilon(1S), Run2 2015", "lpe");
	leg->AddEntry(vG[Form("1r1%s", btype.c_str())].getDerivedObject(), "#Upsilon(1S), 4.5 nb^{-1}", "lpe");
	leg->AddEntry(vG[Form("2r1%s", btype.c_str())].getDerivedObject(), "#Upsilon(1S), 7.2 nb^{-1}", "lpe");
	leg->AddEntry(vG[Form("0r2%s", btype.c_str())].getDerivedObject(), "#Upsilon(2S), Run2 2018", "lpe");
	leg->AddEntry(vG[Form("1r2%s", btype.c_str())].getDerivedObject(), "#Upsilon(2S), 4.5 nb^{-1}", "lpe");
	leg->AddEntry(vG[Form("2r2%s", btype.c_str())].getDerivedObject(), "#Upsilon(2S), 7.2 nb^{-1}", "lpe");
	leg->AddEntry(vG[Form("0r3%s", btype.c_str())].getDerivedObject(), "#Upsilon(3S), Run2 2018", "lpe");
	leg->AddEntry(vG[Form("1r3%s", btype.c_str())].getDerivedObject(), "#Upsilon(3S), 4.5 nb^{-1}", "lpe");
	leg->AddEntry(vG[Form("2r3%s", btype.c_str())].getDerivedObject(), "#Upsilon(3S), 7.2 nb^{-1}", "lpe");

	leg->Draw();
	leg2->Draw("same");

    TLine* lineone = new TLine();
    lineone->SetLineStyle(kDashed);
    lineone->SetLineWidth(1);
	lineone->SetLineColorAlpha(kBlack, 0.3);
    TLine* c1_line1 = lineone->DrawLine(-2, 1.4, 35, 1.4);
    TLine* c1_line2 = lineone->DrawLine(-2, 1, 35, 1);
    TLine* c1_line3 = lineone->DrawLine(-2, 0.5, 35, 0.5);
	

	CMS_lumi_square((TPad*) c2->GetPad(0), 1030, 33, 1);

	c2->SaveAs("../checkout/tscol/AUX/testtest2.pdf");


	TCanvas* c3 =new TCanvas("c3", "" , 900, 800);
	c3->cd();

	vG[Form("0r23%s", btype.c_str())] / vG[Form("0r23%s", btype.c_str())];
	vG[Form("0r23%ssys", btype.c_str())] / vG[Form("0r23%ssys", btype.c_str())];
	readyPlot(vG[Form("0r23%s", btype.c_str())].getDerivedObject(),  vG[Form("0r23%ssys", btype.c_str())].getDerivedObject(), Form("CA3S%s", stype.c_str())); 

	vG[Form("1r23%s", btype.c_str())] / vG[Form("0r23%s", btype.c_str())];
	vG[Form("1r23%ssys", btype.c_str())] / vG[Form("0r23%ssys", btype.c_str())];
	readyPlot(vG[Form("1r23%s", btype.c_str())].getDerivedObject(),  vG[Form("1r23%ssys", btype.c_str())].getDerivedObject(), Form("AA3S%s", stype.c_str())); 

	vG[Form("2r23%s", btype.c_str())] / vG[Form("0r23%s", btype.c_str())];
	vG[Form("2r23%ssys", btype.c_str())] / vG[Form("0r23%ssys", btype.c_str())];
	readyPlot(vG[Form("2r23%s", btype.c_str())].getDerivedObject(),  vG[Form("2r23%ssys", btype.c_str())].getDerivedObject(), Form("A2A3S%s", stype.c_str())); 

	globalOffSetY(-0.0, vG[Form("0r23%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.0, vG[Form("0r23%s", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.0, vG[Form("1r23%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.0, vG[Form("1r23%s", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.0, vG[Form("2r23%ssys", btype.c_str())].getDerivedObject());
	globalOffSetY(-0.0, vG[Form("2r23%s", btype.c_str())].getDerivedObject());

	vG[Form("0r23%ssys", btype.c_str())].getDerivedObject()->GetYaxis()->SetTitle("Relative uncertainty (tick = 10\%)");
	vG[Form("0r23%ssys", btype.c_str())].getDerivedObject()->GetYaxis()->SetRangeUser(-0.2, 2.2);
	vG[Form("0r23%ssys", btype.c_str())].getDerivedObject()->GetYaxis()->SetLabelSize(0);
	vG[Form("0r23%ssys", btype.c_str())].getDerivedObject()->GetXaxis()->SetLimits(-2, 35);
	vG[Form("0r23%ssys", btype.c_str())].getDerivedObject()->GetXaxis()->SetRangeUser(-2, 35);
	vG[Form("0r23%ssys", btype.c_str())].getDerivedObject()->GetXaxis()->SetTitle("p_{T} (GeV)");
	vG[Form("0r23%ssys", btype.c_str())].getDerivedObject()->Draw("A5");
	vG[Form("0r23%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("2r23%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("2r23%s", btype.c_str())].getDerivedObject()->Draw("PE");

	TLegend* leg3= new TLegend(0.52, 0.12, 0.87, 0.35, ""); 
	TLegend* leg4= new TLegend(0.52, 0.12, 0.87, 0.35, ""); 
	leg3->SetBorderSize(0);
	leg3->SetFillStyle(0);
	leg3->SetNColumns(1);
	leg3->SetTextSize(0.021);
	leg3->SetTextFont(42);
	leg4->SetBorderSize(0);
	leg4->SetFillStyle(0);
	leg4->SetNColumns(1);
	leg4->SetTextSize(0.021);
	leg4->SetTextFont(42);

	leg3->AddEntry(vG[Form("0r23%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), Run2 2018", "f");
	leg3->AddEntry(vG[Form("2r23%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), 7.2 nb^{-1}", "f");
	leg4->AddEntry(vG[Form("0r23%s", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), Run2 2018", "lpe");
	leg4->AddEntry(vG[Form("2r23%s", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), 7.2 nb^{-1}", "lpe");

	leg3->Draw();
	leg4->Draw();

    lineone->SetLineStyle(kDashed);
    lineone->SetLineWidth(1);
	lineone->SetLineColorAlpha(kBlack, 0.3);
    lineone->DrawLine(-2, 1.0, 35, 1.0);

	CMS_lumi_square((TPad*) c3->GetPad(0), 1030, 33, 1);
	c3->SaveAs("../checkout/tscol/AUX/testtest3.pdf");


	TCanvas* c4 =new TCanvas("c4", "" , 900, 800);
	c4->cd();

	vG[Form("0r23%ssys", btype.c_str())].getDerivedObject()->Draw("A5");
	vG[Form("0r23%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("1r23%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("1r23%s", btype.c_str())].getDerivedObject()->Draw("PE");

	vG[Form("2r23%ssys", btype.c_str())].getDerivedObject()->Draw("5");
	vG[Form("2r23%s", btype.c_str())].getDerivedObject()->Draw("PE");

	leg3->Clear();
	leg4->Clear();
	leg3->SetBorderSize(0);
	leg3->SetFillStyle(0);
	leg3->SetNColumns(1);
	leg3->SetTextSize(0.021);
	leg3->SetTextFont(42);
	leg4->SetBorderSize(0);
	leg4->SetFillStyle(0);
	leg4->SetNColumns(1);
	leg4->SetTextSize(0.021);
	leg4->SetTextFont(42);

	leg3->AddEntry(vG[Form("0r23%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), Run2 2018", "f");
	leg3->AddEntry(vG[Form("1r23%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), 4.5 nb^{-1}", "f");
	leg3->AddEntry(vG[Form("2r23%ssys", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), 7.2 nb^{-1}", "f");
	leg4->AddEntry(vG[Form("0r23%s", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), Run2 2018", "lpe");
	leg4->AddEntry(vG[Form("1r23%s", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), 4.5 nb^{-1}", "lpe");
	leg4->AddEntry(vG[Form("2r23%s", btype.c_str())].getDerivedObject(), "#Upsilon(3S)/#Upsilon(2S), 7.2 nb^{-1}", "lpe");

	leg3->Draw();
	leg4->Draw();

    lineone->SetLineStyle(kDashed);
    lineone->SetLineWidth(1);
	lineone->SetLineColorAlpha(kBlack, 0.3);
    lineone->DrawLine(-2, 1.0, 35, 1.0);

	CMS_lumi_square((TPad*) c4->GetPad(0), 1030, 33, 1);
	c4->SaveAs("../checkout/tscol/AUX/testtest4.pdf");

};
