#!/bin/bash

#MassYieldFit(const string fname = "", const Double_t ptMin = 0, const Double_t ptMax = 30, const Double_t rapMin = -2    .4, const Double_t rapMax = 2.4, const TString MupT = "4", const string Trig = "", int cBinLow=0, int cBinHigh = 180)

#root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "3p5", 1, 180)'
#root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "3p5", 2, 180)'
#root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "3p5", 13, 180)'
#root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "4", 1, 180)'
#root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "4", 2, 180)'
#root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "4", 13, 180)'

#root -l -b -q 'MassYieldFit.C(0, 6, -2.4, 2.4, "3p5", 1, 180)'
#root -l -b -q 'MassYieldFit.C(0, 6, -2.4, 2.4, "3p5", 2, 180)'
#root -l -b -q 'MassYieldFit.C(0, 6, -2.4, 2.4, "3p5", 13, 180)'
#root -l -b -q 'MassYieldFit.C(0, 6, -2.4, 2.4, "4", 1, 180)'
#root -l -b -q 'MassYieldFit.C(0, 6, -2.4, 2.4, "4", 2, 180)'
#root -l -b -q 'MassYieldFit.C(0, 6, -2.4, 2.4, "4", 13, 180)'
#
#root -l -b -q 'MassYieldFit.C(6, 50, -2.4, 2.4, "3p5", 1, 180)'
#root -l -b -q 'MassYieldFit.C(6, 50, -2.4, 2.4, "3p5", 1, 180)'
#root -l -b -q 'MassYieldFit.C(6, 50, -2.4, 2.4, "3p5", 2, 180)'
#root -l -b -q 'MassYieldFit.C(6, 50, -2.4, 2.4, "3p5", 13, 180)'
#root -l -b -q 'MassYieldFit.C(6, 50, -2.4, 2.4, "4", 1, 180)'
#root -l -b -q 'MassYieldFit.C(6, 50, -2.4, 2.4, "4", 2, 180)'
#root -l -b -q 'MassYieldFit.C(6, 50, -2.4, 2.4, "4", 13, 180)'

#S1= DBMUOS40100 -> 0~86 : UpsTrig, 87~ : DBMUOS40100
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 87, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S1", 0, 86)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 87, 180)' &  2>/dev/null
wait %% 2>/dev/null 
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S1", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S1", 87, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S1", 0, 86)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "3p5", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "3p5", "S13", 87, 180)' &  2>/dev/null
wait %% 2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S1", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S1", 87, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S1", 0, 86)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "3p5", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "3p5", "S13", 87, 180)' &  2>/dev/null
wait %% 2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "4", "S1", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "4", "S1", 87, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 50, -2.4, 2.4, "4", "S1", 0, 86)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 0, 180)' &  2>/dev/null 
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 87, 180)' &  2>/dev/null
wait %% 2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "4", "S1", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "4", "S1", 87, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 10, 50, -2.4, 2.4, "4", "S1", 0, 86)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "4", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "4", "S13", 87, 180)' &  2>/dev/null
wait %% 2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "4", "S1", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "4", "S1", 87, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS1_Switch1.root", 0, 10, -2.4, 2.4, "4", "S1", 0, 86)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "4", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "4", "S13", 87, 180)' &  2>/dev/null
wait %% 2>/dev/null
#S2= DBMU50100 -> 0~106 : UpsTrig, 107~ : DBMU50100
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S2", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S2", 107, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "3p5", "S2", 0, 106)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "3p5", "S13", 107, 180)' &  2>/dev/null
wait %% 2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S2", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S2", 107, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "3p5", "S2", 0, 106)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "3p5", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "3p5", "S13", 107, 180)' &  2>/dev/null
wait %% 2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S2", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S2", 107, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "3p5", "S2", 0, 106)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "3p5", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "3p5", "S13", 107, 180)' &  2>/dev/null
wait %% 2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "4", "S2", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "4", "S2", 107, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 50, -2.4, 2.4, "4", "S2", 0, 106)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 50, -2.4, 2.4, "4", "S13", 107, 180)' &  2>/dev/null
wait %% 2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "4", "S2", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "4", "S2", 107, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 10, 50, -2.4, 2.4, "4", "S2", 0, 106)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "4", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 10, 50, -2.4, 2.4, "4", "S13", 107, 180)' &  2>/dev/null
wait %% 2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "4", "S2", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "4", "S2", 107, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS2_Switch1.root", 0, 10, -2.4, 2.4, "4", "S2", 0, 106)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "4", "S13", 0, 180)' &  2>/dev/null
root -l -b -q 'MassYieldFit.C("OniaRooDataSet_OniaSkim_TrigS13.root", 0, 10, -2.4, 2.4, "4", "S13", 107, 180)' &  2>/dev/null
wait %% 2>/dev/null
