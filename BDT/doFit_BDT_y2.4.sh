#/bin/bash
ts=$1
ts=1618564208 #1618557840 #1618557150 #1618557109 #1618557066 #1618555164 #1618553605 # #1618505174 #1618506795 #1618491012 #1618494295#1618036602 #1614848550
export timestamp=$ts
	cd ..
if [ $2 -eq 1 ]
  then 
  plow=0;phigh=30;
  clow=0;chigh=180;
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.01, -0.3, -0.1 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.2, 5, 5, 0.95, 8, 2, 8})' &  2>/dev/null

# BDT  - 1.0   ~  - 0.2
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.01, -1., -0.2 , (Double_t[]) {0.13, 1.74, 2.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.4, 2.1, 0.15, 0.5, 0.5, 0.1}, (Double_t[]) {0.24, 4, 7., 0.9, 9, 5, 9})' &  2>/dev/null

# BDT  - 0.2   ~  - 0.1
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.01, -0.2, -0.1 , (Double_t[]) {0.13, 1.54, 2.68, 0.56, 6.0, 6.8, 5.13}, (Double_t[]) {0.01, 1.2, 2.5, 0.05, 4.5, 0.3, 0.1}, (Double_t[]) {0.34, 4, 5, 0.95, 9.1, 8.0, 9})' &  2>/dev/null

# BDT  - 0.1   ~  0.05
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.01, -0.1, 0.05 , (Double_t[]) {0.18, 1.54, 4.68, 0.56, 7.0, 0.8, 7.13}, (Double_t[]) {0.05, 1.1, 2.10, 0.05, 0.5, 0.1, 0.1}, (Double_t[]) {0.25, 4, 4.0, 0.95, 9.1, 8.5, 10})' &  2>/dev/null

# BDT  0.05   ~   0.2  -0.2  ~   0.05
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.01, -0.2, 0.05 , (Double_t[]) {0.16, 1.74, 1.88, 0.56, 9.0, 4.1, 3.73}, (Double_t[]) {0.01, 1.4, 1.8, 0.05, 0.5, 0.1, 0.1}, (Double_t[]) {0.21, 3, 3.0, 0.95, 9.1, 7.0, 7.})' &  2>/dev/null

# BDT   0.2   ~   1.0  0.05  ~   1.0
#root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.01, 0.05, 1.0 , (Double_t[]) {0.13, 1.74, 2.18, 0.56, 7.0, 1.1, 3.13}, (Double_t[]) {0.01, 1.15, 1.0, 0.05, 0.5, 0.5, 0.1}, (Double_t[]) {0.24, 10.1, 10.5, 0.95, 9.1, 10.0, 20})' &  2>/dev/null
# BDT   0.2   ~   1.0  0.2  ~   1.0
root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.01, 0.2, 1.0 , (Double_t[]) {0.13, 1.74, 2.18, 0.56, 7.0, 1.1, 3.13}, (Double_t[]) {0.01, 1.15, 1.0, 0.05, 0.5, 0.5, 0.1}, (Double_t[]) {0.24, 1.9, 3.9, 0.95, 9.4, 2.0, 20})' &  2>/dev/null

root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.01, 0.3, 1.0 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.5, 1.5, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.3, 5, 10, 0.95, 8, 10, 10})' &  2>/dev/null
root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", '$plow', '$phigh', -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.00, 0.2, 1.0 , (Double_t[]) {0.13, 1.74, 2.18, 0.56, 7.0, 1.1, 3.13}, (Double_t[]) {0.01, 1.15, 1.0, 0.05, 0.5, 0.5, 0.1}, (Double_t[]) {0.41, 1.9, 3.9, 0.95, 7.4, 2.0, 4})' &  2>/dev/null

root -l -b -q 'MassYieldFit_BDT.C("./BDT/roodatasets/OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT.root", 0, 30, -2.4, 2.4, "3p5", "S13", '$clow', '$chigh', 0.00, 0.3, 1.0 , (Double_t[]) {0.13, 1.54, 3.68, 0.56, 5.0, 1.8, 3.13}, (Double_t[]) {0.01, 1.1, 1.1, 0.15, 0.5, 0.1, 0.1}, (Double_t[]) {0.4, 2, 4, 0.95, 7.4, 2, 4})' &  2>/dev/null
wait && 2</dev/null
cd ./BDT
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', 2.4, '$plow'., '$phigh', '$clow', '$chigh', false)'
#root -l -b -q 'plotresult.C('$ts', 2.4, '$plow', '$phigh', '$clow', '$chigh',0.01, "3p5","S13", "freefit", 3)'
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
