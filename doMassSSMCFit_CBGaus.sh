#!/bin/bash

#root -l -b -q 'MassYieldSingleStateMCFit.C("OniaRooDataSet_OniaSkim_TrigS1_MC.root" ,0, 50, -2.4, 2.4, "3p5", "L1DoubleMuOpenOS40100", 180, 1)'
#root -l -b -q 'MassYieldSingleStateMCFit.C("OniaRooDataSet_OniaSkim_TrigS2_MC.root", 0, 50, -2.4, 2.4, "3p5", "L1DoubleMuOpen50100", 180, 1)'
#root -l -b -q 'MassYieldSingleStateMCFit.C("OniaRooDataSet_OniaSkim_TrigS13_MC.root",0, 50, -2.4, 2.4, "3p5", "UpsilonTrig", 180, 1)'
#root -l -b -q 'MassYieldSingleStateMCFit.C("OniaRooDataSet_OniaSkim_TrigS1_MC.root" ,0, 50, -2.4, 2.4, "4", "L1DoubleMuOpenOS40100", 180, 1)'
#root -l -b -q 'MassYieldSingleStateMCFit.C("OniaRooDataSet_OniaSkim_TrigS2_MC.root", 0, 50, -2.4, 2.4, "4", "L1DoubleMuOpen50100", 180, 1)'
#root -l -b -q 'MassYieldSingleStateMCFit.C("OniaRooDataSet_OniaSkim_TrigS13_MC.root",0, 50, -2.4, 2.4, "4", "UpsilonTrig", 180, 1)'

#root -l -b -q 'MassYieldSingleStateMCFit.C("OniaRooDataSet_L1DoubleMuOpenOS40100Trig_isMC1_HFNom_201222.root" ,0, 50, -2.4, 2.4, "3p5", "L1DoubleMuOpenOS40100", 180, 3)'
#root -l -b -q 'MassYieldSingleStateMCFit.C("OniaRooDataSet_L1DoubleMuOpenOS40100Trig_isMC1_HFNom_201222.root" ,0, 50, -2.4, 2.4, "4", "L1DoubleMuOpenOS40100", 180, 3)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(0, 6, -2.4, 2.4, "3p5", 1, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(0, 6, -2.4, 2.4, "3p5", 2, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(0, 6, -2.4, 2.4, "3p5", 13, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(0, 6, -2.4, 2.4, "4", 1, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(0, 6, -2.4, 2.4, "4", 2, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(0, 6, -2.4, 2.4, "4", 13, 180)'
#
#root -l -b -q 'MassYieldSingleStateMCFit.C(6, 50, -2.4, 2.4, "3p5", 1, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(6, 50, -2.4, 2.4, "3p5", 1, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(6, 50, -2.4, 2.4, "3p5", 2, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(6, 50, -2.4, 2.4, "3p5", 13, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(6, 50, -2.4, 2.4, "4", 1, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(6, 50, -2.4, 2.4, "4", 2, 180)'
#root -l -b -q 'MassYieldSingleStateMCFit.C(6, 50, -2.4, 2.4, "4", 13, 180)'

#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS1_MC.root", "OniaRooDataSet_L1DoubleMuOpenOS40100Trig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "4", "L1DoubleMuOpenOS40100", 180, 1, true)'
#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS2_MC.root", "OniaRooDataSet_L1DoubleMuOpen50100Trig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "4", "L1DoubleMuOpen50100", 180, 1, true)'
root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS13_MC.root", "OniaRooDataSet_UpsTrig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "3p5", "Ups", 180, 1, true)' &
root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS1_MC.root", "OniaRooDataSet_L1DoubleMuOpenOS40100Trig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "3p5", "L1DoubleMuOpenOS40100", 180, 1, true)'
#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS2_MC.root", "OniaRooDataSet_L1DoubleMuOpen50100Trig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "3p5", "L1DoubleMuOpen50100", 180, 1, true)'
#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS13_MC.root", "OniaRooDataSet_UpsTrig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "3p5", "Ups", 180, 1, true)'
#
#
#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS1_MC.root", "OniaRooDataSet_L1DoubleMuOpenOS40100Trig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "4", "L1DoubleMuOpenOS40100", 180, 3, false)'
#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS2_MC.root", "OniaRooDataSet_L1DoubleMuOpen50100Trig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "4", "L1DoubleMuOpen50100", 180, 3, false)'
#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS13_MC.root", "OniaRooDataSet_UpsTrig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "4", "Ups", 180, 3, false)'
#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS1_MC.root", "OniaRooDataSet_L1DoubleMuOpenOS40100Trig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "3p5", "L1DoubleMuOpenOS40100", 180, 3, false)'
#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS2_MC.root", "OniaRooDataSet_L1DoubleMuOpen50100Trig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "3p5", "L1DoubleMuOpen50100", 180, 3, false)'
#root -l -b -q 'MassYieldFit_CBGaus_MC.C("OniaRooDataSet_OniaSkim_TrigS13_MC.root", "OniaRooDataSet_UpsTrig_isMC1_HFNom_201222.root", 0, 50, -2.4, 2.4, "3p5", "Ups", 180, 3, false)'
