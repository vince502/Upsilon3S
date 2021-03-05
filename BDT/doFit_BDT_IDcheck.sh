#/bin/bash
ts=$1
export timestamp=$ts
	cd ..
root -l -b -q '_BDTFIT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_IDcheck.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-1., (Double_t[]) {0.05, 1.58, 3.68, 0.3, 8., 4., 1.3})' &  2>/dev/null
#root -l -b -q '_BDTFIT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_IDcheck.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.2, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 7, 4, 1.1})' &  2>/dev/null
#root -l -b -q '_BDTFIT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_IDcheck.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 4, 5, 1.2})' &  2>/dev/null
#root -l -b -q '_BDTFIT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_IDcheck.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,-0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5.5, 4, 1.1})' &  2>/dev/null
#root -l -b -q '_BDTFIT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_IDcheck.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0.0, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 5, 1.1})' &  2>/dev/null
#wait && 2</dev/_BDTFIT
#root -l -b -q '_BDTFIT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_IDcheck.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.02, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 3, 4, 1.2})' &  2>/dev/null
#root -l -b -q '_BDTFIT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_IDcheck.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.1, (Double_t[]) {0.05, 1.58, 3.68, 0.7, 6.3, 6, 2.1})' &  2>/dev/null
#root -l -b -q '_BDTFIT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_IDcheck.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.2, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 5.9, 1.2})' &  2>/dev/null
#root -l -b -q '_BDTFIT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_IDcheck.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01,0.3, (Double_t[]) {0.05, 1.58, 3.68, 0.5, 5, 4, 1})' &  2>/dev/null
wait && 2</dev/null
