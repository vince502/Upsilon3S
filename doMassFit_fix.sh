#!/bin/bash

#MassYieldFit(const string fname = "", const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2    .4, const Double_t rapMax = 2.4, const TString MupT = "4", const string Trig = "", int cBinLow=0, int cBinHigh = 180, Double_t params[/*sigma1S_1, alpha, n , frac, Erfmean, Erfsigma, Erfp0*/])
#0-10, 10-50, 0-50 GeV DiMu Pt cut
##S1= DBMUOS40100 -> 0~86 : UpsTrig, 87~ : DBMUOS40100
#---------------------------------------------------------------------------------0-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 120, 180, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 0, 180, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 1.52, 4.3, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null 
##---------------------------------------------------------------------------------10-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S1", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "3p5", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
##---------------------------------------------------------------------------------0-10--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S1", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "3p5", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
##---------------------------------------------------------------------------------0-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "4", "S1", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "4", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "4", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null 
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
##---------------------------------------------------------------------------------10-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "4", "S1", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "4", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "4", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "4", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##---------------------------------------------------------------------------------0-10--------------------------------------------------------------------------------#
#wait %% 2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "4", "S1", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "4", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "4", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "4", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
#
##MassYieldFit(const string fname = "", const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2    .4, const Double_t rapMax = 2.4, const TString MupT = "4", const string Trig = "", int cBinLow=0, int cBinHigh = 180, Double_t params[/*sigma1S_1, alpha, n , frac, Erfmean, Erfsigma, Erfp0*/])
###S2= DBMU50100 -> 0~109 : UpsTrig, 110~ : DBMU50100
##---------------------------------------------------------------------------------0-50--------------------------------------------------------------------------------#
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##wait %% 2>/dev/null
##---------------------------------------------------------------------------------10-50--------------------------------------------------------------------------------#
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "3p5", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##wait %% 2>/dev/null
##---------------------------------------------------------------------------------0-10--------------------------------------------------------------------------------#
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "3p5", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##wait %% 2>/dev/null
##---------------------------------------------------------------------------------0-50--------------------------------------------------------------------------------#
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "4", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "4", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "4", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##wait %% 2>/dev/null
##---------------------------------------------------------------------------------10-50--------------------------------------------------------------------------------#
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "4", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "4", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "4", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "4", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##wait %% 2>/dev/null
##---------------------------------------------------------------------------------0-10--------------------------------------------------------------------------------#
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "4", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "4", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "4", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
##wait %% 2>/dev/null
#
##MassYieldFit(const string fname = "", const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2    .4, const Double_t rapMax = 2.4, const TString MupT = "4", const string Trig = "", int cBinLow=0, int cBinHigh = 180, Double_t params[/*sigma1S_1, alpha, n , frac, Erfmean, Erfsigma, Erfp0*/])
#
##0-6, 6-50, 0-50 GeV DiMu Pt cut
#
##S1= DBMUOS40100 -> 0~89 : UpsTrig, 90~ : DBMUOS40100
##---------------------------------------------------------------------------------0-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 0, 180, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 8, 1.3, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 90, 180, (Double_t[]) {0.05, 1.58, 3.68, 0.6, 5, 4, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 1.0, 0.5, 7.5, 3, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 4.0, 0.5, 7.5, 5, 8})' &  2>/dev/null
#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 60, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 10, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 20, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 40, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 90, 180, (Double_t[]) {0.05, 5.5, 4.0, 0.5, 6, 5, 12})' &  2>/dev/null
#wait %% 2>/dev/null 
#---------------------------------------------------------------------------------6-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 6, 50, -2.4, 2.4, "3p5", "S1", 0, 180, (Double_t[]) {0.05, 1.717, 2.27, 0.5, 7, 2, 6})' &  2>/dev/null  #FIXED!
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 6, 50, -2.4, 2.4, "3p5", "S1", 90, 180, (Double_t[]) {0.05, 1.0, 4.0, 0.6, 5, 2, 3})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 6, 50, -2.4, 2.4, "3p5", "S1", 0, 89, (Double_t[]) {0.05, 4.0, 3.0, 0.5, 6, 4, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 1.521, 4.18, 0.5, 7, 1, 3})' &  2>/dev/null #FIXED!
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "3p5", "S13", 10, 60, (Double_t[]) {0.12, 1.519, 4.21, 0.5, 8, 2, 8})' &  2>/dev/null #FIXED!
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "3p5", "S13", 10, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "3p5", "S13", 20, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "3p5", "S13", 40, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "3p5", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 8, 5, 7})' &  2>/dev/null
#wait %% 2>/dev/null
#---------------------------------------------------------------------------------0-6--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 6, -2.4, 2.4, "3p5", "S1", 0, 180, (Double_t[]) {0.05, 1.321, 22., 0.5, 5, 6, 2})' &  2>/dev/null #FIXED!
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 6, -2.4, 2.4, "3p5", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 6, -2.4, 2.4, "3p5", "S1", 0, 89, (Double_t[]) {0.05, 6.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.11, 1.5243, 4.414, 0.47, 8.1, 0.9, 7})' &  2>/dev/null #FIXED!
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "3p5", "S13", 0, 60, (Double_t[]) {0.12, 1.5243, 4.414, 0.51, 7.8, 1.02, 5.1})' &  2>/dev/null #FIXED!
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "3p5", "S13", 10, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "3p5", "S13", 20, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "3p5", "S13", 40, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "3p5", "S13", 90, 180, (Double_t[]) {0.05, 5.0, 2.0, 0.5, 7, 5, 5})' &  2>/dev/null
#wait %% 2>/dev/null
#---------------------------------------------------------------------------------0-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "4", "S1", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "4", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "4", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 2, 5})' &  2>/dev/null 
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 10, 60, (Double_t[]) {0.12, 1.519, 4.21, 0.5, 8, 2, 8})' &  2>/dev/null #FIXED!
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 10, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 20, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 40, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 2, 1})' &  2>/dev/null
#wait %% 2>/dev/null
#---------------------------------------------------------------------------------6-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 6, 50, -2.4, 2.4, "4", "S1", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 6, 50, -2.4, 2.4, "4", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 6, 50, -2.4, 2.4, "4", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 10, 60, (Double_t[]) {0.12, 1.519, 4.21, 0.5, 8, 2, 8})' &  2>/dev/null #FIXED!
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 10, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 20, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 40, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 5, 1})' &  2>/dev/null
#wait %% 2>/dev/null
#---------------------------------------------------------------------------------0-6--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 6, -2.4, 2.4, "4", "S1", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 6, -2.4, 2.4, "4", "S1", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 6, -2.4, 2.4, "4", "S1", 0, 89, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 2})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 10, 60, (Double_t[]) {0.12, 1.519, 4.21, 0.5, 8, 2, 8})' &  2>/dev/null #FIXED!
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "4", "S13", 10, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "4", "S13", 20, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "4", "S13", 40, 89, (Double_t[]) {0.12, 1.518, 4.31, 0.5, 9, 1, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "4", "S13", 90, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 2, 1})' &  2>/dev/null
#wait %% 2>/dev/null

#MassYieldFit(const string fname = "", const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2    .4, const Double_t rapMax = 2.4, const TString MupT = "4", const string Trig = "", int cBinLow=0, int cBinHigh = 180, Double_t params[/*sigma1S_1, alpha, n , frac, Erfmean, Erfsigma, Erfp0*/])

#S2= DBMU50100 -> 0~109 : UpsTrig, 110~ : DBMU50100

#---------------------------------------------------------------------------------0-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S2", 0, 180, (Double_t[]) {0.12, 1.541, 4.2, 0.49, 7.0, 1.2, 8})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2.root", 0, 50, -2.4, 2.4, "3p5", "S2", 0, 180, (Double_t[]) {0.05, 1.541, 4.2, 0.5, 5, 2, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S2", 110, 180, (Double_t[]) {0.12, 1.541, 4.2, 0.44, 7.6, 1.01, 6})' #&  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
#---------------------------------------------------------------------------------6-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 6, 50, -2.4, 2.4, "3p5", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 6, 50, -2.4, 2.4, "3p5", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 6, 50, -2.4, 2.4, "3p5", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "3p5", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
#---------------------------------------------------------------------------------0-6--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 6, -2.4, 2.4, "3p5", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 6, -2.4, 2.4, "3p5", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 6, -2.4, 2.4, "3p5", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "3p5", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
#---------------------------------------------------------------------------------0-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "4", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "4", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "4", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
#---------------------------------------------------------------------------------6-50--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 6, 50, -2.4, 2.4, "4", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 6, 50, -2.4, 2.4, "4", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 6, 50, -2.4, 2.4, "4", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 50, -2.4, 2.4, "4", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
#---------------------------------------------------------------------------------0-6--------------------------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 6, -2.4, 2.4, "4", "S2", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 6, -2.4, 2.4, "4", "S2", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 6, -2.4, 2.4, "4", "S2", 0, 109, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "4", "S13", 0, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "4", "S13", 110, 180, (Double_t[]) {0.05, 2.0, 2.0, 0.5, 5, 1, 1})' &  2>/dev/null
#wait %% 2>/dev/null
#MassYieldFit(const string fname = "", const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2    .4, const Double_t rapMax = 2.4, const TString MupT = "4", const string Trig = "", int cBinLow=0, int cBinHigh = 180, Double_t params[/*sigma1S_1, alpha, n , frac, Erfmean, Erfsigma, Erfp0*/])
#-----------------------------------for 0-6-30GeV Fit-------------------------------------------------------------#
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 30, -2.4, 2.4, "3p5", "S1", 0, 180, (Double_t[]) {0.12, 1.515, 5.3, 0.5, 6.5, 1.2, 7})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 6, -2.4, 2.4, "3p5", "S1", 0, 180, (Double_t[]) {0.12, 1.321, 22, 0.5, 7, 1.2, 4})' &  2>/dev/null
root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 6, 30, -2.4, 2.4, "3p5", "S1", 0, 180, (Double_t[]) {0.11, 1.62, 4.1, 0.5, 6.6, 1.4, 2})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.12, 1.75, 1.9, 0.5, 7, 1.1, 6})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 6, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.12, 1.4226, 9.2, 0.5, 7, 1.2, 5})' &  2>/dev/null
root -l -b -q 'MassYieldFit_fix.C("OniaRooDataSet_OniaSkim_TrigS13.root", 6, 30, -2.4, 2.4, "3p5", "S13", 0, 180, (Double_t[]) {0.11, 1.4465, 6.676, 0.5, 6.6, 1.5, 2})' &  2>/dev/null
