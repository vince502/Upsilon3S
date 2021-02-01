#!/bin/bash

# training to fitting process. Currently works for ID1, MoreVar0, IDonly1.

root -l -b -q 'BDTClassifier.C(true,false,true)'
ts=$(<timestamp.tmp)
export timestamp=$ts
echo $ts >> timestamp.old
root -l -b -q 'makeRooDataset_fromBDT.C("./BDTResult/BDTresultY3S_'$timestamp'_IDv1_MoreVar0.root")'
cd ..
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
wait && 2</dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
wait && 2</dev/null

root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,-1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
wait && 2</dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
wait && 2</dev/null

root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,-1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
wait && 2</dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
wait && 2</dev/null

root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,-1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
wait && 2</dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 50, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
echo "" > timestamp.tmp
