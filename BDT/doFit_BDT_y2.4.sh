#/bin/bash
ts=$1
ts=1614848550
export timestamp=$ts
	cd ..
if [ $2 -eq 1 ]
  then 
  plow=0;phigh=4;
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, -0.3, -0.1 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.2, 5, 5, 0.95, 8, 2, 8})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, -1., -0.2 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.2, 3.2, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.14, 3, 6, 0.9, 8, 1.4, 5})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, -0.2, -0.1 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.3, 1.2, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.14, 3, 6, 0.95, 8, 2.0, 7})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, -0.1, 0.05 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.05, 1.8, 3.0, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.14, 3, 6, 0.95, 8, 2.0, 7})' &  2>/dev/null
#
root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.05, 0.2 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 0.9, 1.0, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 5, 7, 0.95, 8, 2.0, 7})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.2, 0.4 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.03, 1.5, 1.5, 0.15, 0.5, 0.5, 0.1}, (Double_t[]) {0.14, 3, 6, 0.95, 8, 2.0, 7})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0.4, 1.0 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 0.5, 0.3, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.24, 6, 20, 0.85, 8, 2.0, 7})' &  2>/dev/null
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", 0, 180, 0.01, 0., 0.1 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.3, 5, 10, 0.95, 8, 10, 10})' &  2>/dev/null
fi

if [ $2 -eq  0 ]
  then
  for i in "-1.0 -0.3" "-0.3 -0.1" "-0.1 0.0" "0.0 0.1" "0.1 1.0" "-0.1 1.0" "-0.3 0.0" "0.0 1.0" "-0.3 0.1"
    do bdt=( $i )
      bl=${bdt[0]}; bh=${bdt[1]}
      for j in "0 40" "40 100" "100 180"
	do cent=( $j )
	  cl=${cent[0]}; ch=${cent[1]}
	for k in "0 6" "6 30" "0 30"
	  do pt=( $k )
	    pl=${pt[0]}; ph=${pt[1]}
root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$pl', '$ph', -2.4, 2.4, "3p5", "S13", '$cl', '$ch', 0.01, '$bl', '$bh' , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 5, 8, 0.95, 9, 2, 8})' &  2>/dev/null
        done
      done
    wait && 2</dev/null
      for j in "0 180"
	do cent=( $j )
	  cl=${cent[0]}; ch=${cent[1]}
	for k in "0 6" "6 30" "0 30" "0 4" "4 9" "9 12" "12 30"
	  do pt=( $k )
	    pl=${pt[0]}; ph=${pt[1]}
root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$pl', '$ph', -2.4, 2.4, "3p5", "S13", '$cl', '$ch', 0.01, '$bl', '$bh' , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 5, 8, 0.95, 9, 2, 8})' &  2>/dev/null
        done
      done
  wait && 2</dev/null
  done

fi

if [ $2 -eq 3 ]
  then
  root -l -b -q 'DrawTemp.C('$ts', 1.2, -0.3,-0.1, 0.01, "3p5", "S13", "freefit")'
  root -l -b -q 'DrawTemp.C('$ts', 1.2, -0.1, 0.0, 0.01, "3p5", "S13",  "freefit")'
  root -l -b -q 'DrawTemp.C('$ts', 1.2, 0.0, 0.2, 0.01, "3p5", "S13",  "freefit")'
  root -l -b -q 'DrawTemp.C('$ts', 1.2, 0.2, 1.0, 0.01, "3p5", "S13",  "freefit")'
fi
