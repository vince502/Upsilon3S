#/bin/bash
ts=$1
export timestamp=$ts
	cd ..
if [ $2 -eq 1 ]
  then 
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-1., (Double_t[]) {0.10, 1.36, 3.68, 0.345, 7.4, 6.1, 1.33})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.2, (Double_t[]) {0.05, 1.58, 3.68, 0.56, 6, 3, 1.2})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.56, 5, 3, 1.1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 6, 3.6, 1.1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 5, 1.1})' &  2>/dev/null
wait && 2</dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 6, 4, 1.2})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -1.2, 1.2, "3p5", "S13", 0, 180, 0.01, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.7, 6.3, 6, 2.1})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.2, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 6, 5, 1.12})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT_fix.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
wait && 2</dev/null
fi

if [ $2 -eq  0 ]
  then
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-1., -0.3, (Double_t[]) {0.13, 1.54, 3.68, 0.66, 4.4, 10, 1.43})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.3, 0.1, (Double_t[]) {0.13, 1.54, 3.68, 0.66, 4.4, 5.8, 1.23})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.3, -0.1, (Double_t[]) {0.13, 1.54, 3.68, 0.56, 3.0, 2.8, 1.13})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -1.2, 1.2, "3p5", "S13", 0, 180, 0.01, 0.1, 1.0, (Double_t[]) {0.13, 1.54, 3.68, 0.56, 3.0, 2.8, 1.13})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0., 0.2, (Double_t[]) {0.13, 1.54, 3.68, 0.56, 3.0, 1.8, 1.13})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0.2, 1., (Double_t[]) {0.13, 1.54, 3.68, 0.56, 3.0, 3.8, 1.33})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.1, 1., (Double_t[]) {0.13, 1.54, 3.68, 0.66, 7.4, 6.8, 1.13})' &  2>/dev/null
fi

if [ $2 -eq 3 ]
  then
  #root -l -b -q 'DrawTemp.C('$ts', -1, -0.3, 0.01, "3p5", "S13", "freefit")'
  #root -l -b -q 'DrawTemp.C('$ts', -0.3, 0.1, 0.01, "3p5", "S13", "freefit")'
  root -l -b -q 'DrawTemp.C('$ts', 0.1, 1.0, 0.01, "3p5", "S13", "DatafixtoMC")'
fi
