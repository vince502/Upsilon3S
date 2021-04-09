#/bin/bash
ts=$1
ts=1614932252
export timestamp=$ts
	cd ..
if [ $2 -eq 1 ]
  then 
  plow=0;phigh=6;
  clow=100;chigh=180;
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -1.2, 1.2, "3p5", "S13", '$clow', '$chigh', 0.01, -0.3, -0.1 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.2, 5, 5, 0.95, 8, 2, 8})' &  2>/dev/null

# BDT  - 1.0   ~  - 0.2
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -1.2, 1.2, "3p5", "S13", '$clow', '$chigh', 0.01, -1., -0.2 , (Double_t[]) {0.15, 2.84, 3.18, 0.56, 8.0, 1.1, 7.13}, (Double_t[]) {0.01, 1.8, 2.4, 0.15, 0.5, 0.5, 0.1}, (Double_t[]) {0.19, 4, 4, 0.8, 9, 2.1, 9})' &  2>/dev/null

# BDT  - 0.2   ~  - 0.1
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -1.2, 1.2, "3p5", "S13", '$clow', '$chigh', 0.01, -0.2, -0.1 , (Double_t[]) {0.13, 1.64, 2.63, 0.56, 8.0, 1.8, 7.13}, (Double_t[]) {0.01, 1.4, 2.2, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 2, 3.3, 0.95, 9, 3.5, 9})' &  2>/dev/null

# BDT  - 0.1   ~  0.05
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -1.2, 1.2, "3p5", "S13", '$clow', '$chigh', 0.01, -0.1, 0.05 , (Double_t[]) {0.13, 1.43, 2.48, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.02, 1.4, 2.10, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.20, 4, 4.7, 0.90, 9, 4.0, 10})' &  2>/dev/null

# BDT  0.05   ~   0.2
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -1.2, 1.2, "3p5", "S13", '$clow', '$chigh', 0.01, 0.05, 0.2 , (Double_t[]) {0.13, 1.74, 2.38, 0.51, 6.0, 4.8, 8.13}, (Double_t[]) {0.01, 1.4, 2.1, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.21, 2.2, 4.1, 0.95, 9, 9.0, 9.})' &  2>/dev/null

# BDT   0.2   ~   1.0
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -1.2, 1.2, "3p5", "S13", '$clow', '$chigh', 0.01, 0.2, 1.0 , (Double_t[]) {0.21, 1.64, 2.58, 0.5, 7.0, 1.1, 7.13}, (Double_t[]) {0.02, 1.3, 2.1, 0.10, 0.5, 0.9, 0.1}, (Double_t[]) {0.25, 1.6, 3.4, 0.95, 9, 3.0, 9})' &  2>/dev/null

#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -1.2, 1.2, "3p5", "S13", '$clow', '$chigh', 0.01, 0., 0.1 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.3, 5, 10, 0.95, 8, 10, 10})' &  2>/dev/null
wait && 2</dev/null
cd ./BDT
root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', 1.2, '$plow'., '$phigh', '$clow', '$chigh', false)'
root -l -b -q 'plotresult.C('$ts', 1.2, '$plow', '$phigh', '$clow', '$chigh',0.01, "3p5","S13", "freefit")'
fi

if [ $2 -eq  0 ]
  then
  for i in "-1.0 -0.3" "-0.3 -0.1" "-0.1 0.0" "0.0 0.1" "0.1 1.0" "-0.1 1.0" "-0.3 0.0" "0.0 1.0" "-0.3 0.1"
    do bdt=( $i )
      bl=${bdt[0]}; bh=${bdt[1]}
#      for j in "0 40" "40 100" "100 180"
#	do cent=( $j )
#	  cl=${cent[0]}; ch=${cent[1]}
#	for k in "0 6" "6 30" "0 30"
#	  do pt=( $k )
#	    pl=${pt[0]}; ph=${pt[1]}
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$pl', '$ph', -1.2, 1.2, "3p5", "S13", '$cl', '$ch', 0.01, '$bl', '$bh' , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 5, 8, 0.95, 9, 2, 8})' &  2>/dev/null
#        done
#      done
    wait && 2</dev/null
      for j in "0 180"
	do cent=( $j )
	  cl=${cent[0]}; ch=${cent[1]}
	for k in "0 6" "6 30" "0 30" "0 4" "4 9" "9 12" "12 30"
	  do pt=( $k )
	    pl=${pt[0]}; ph=${pt[1]}
root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$pl', '$ph', -1.2, 1.2, "3p5", "S13", '$cl', '$ch', 0.01, '$bl', '$bh' , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 5, 8, 0.95, 9, 2, 8})' &  2>/dev/null
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
