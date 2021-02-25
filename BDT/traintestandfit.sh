#!/bin/bash

# training to fitting process. Currently works for ID1, MoreVar0, IDonly1.

if [ $# -eq 0 ] 
then
	runTMVA=1
	runFit=0
fi

if [ $# -ne 0 ]
then
	if [ $# -g 3 ] | [ $# -l 2 ]
	  then
	  echo "need two or three numbers"
	fi

runTMVA=$1
runFit=$2
userts=$3
fi
if [ $runTMVA -eq 1 ]
then
	root -l -b -q 'BDTClassifier.C(true,false,true)'
	ts=$(<timestamp.tmp)
	export timestamp=$ts
	root -l -b -q 'BDTClassifierApplication.C('$timestamp',0)'
	root -l -b -q 'BDTClassifierApplication.C('$timestamp',1)'
fi
if [ $runFit -eq 1 ]
then
	if [ $# -eq 2 ]
	  then
	ts=$(<timestamp.tmp)
	fi
	if [ $# -eq 3 ]
	then
	ts=$userts
	fi
	export timestamp=$ts
	echo $ts >> timestamp.old
	root -l -b -q 'makeRooDataset_fromBDT.C('$timestamp')'
	cd ..
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.2, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
wait && 2</dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.2, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
wait && 2</dev/null

#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,-1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
#wait && 2</dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.02,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
wait && 2</dev/null

#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,-1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#wait && 2</dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.05,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
wait && 2</dev/null

#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,-1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#wait && 2</dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.1,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 1, 1})' &  2>/dev/null
#echo "" > timestamp.tmp
fi
