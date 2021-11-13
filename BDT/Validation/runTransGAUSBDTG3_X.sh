#!/bin/bash
#cd Macros
#root -l -b -q 'DrawYield.C(8000000014$1)'
function part1 {
root -l -b -q "BDTClassifier_BLIND_BDTG3_$1.C"
root -l -b -q "BDTNominalProcess.cxx(800000014$1,0, {{0,30}})"
#root -l -b -q "BDT_trainVariable_Mass_Distribution.C(800000014$1,1)"
}
function part2 {
cd /home/vince402/Upsilon3S
root -l -b -q "doConstraintFit_VALI.cxx(1311,800000014$1,3)"
cd /home/vince402/Upsilon3S/BDT/Validation
root -l -b -q "BDTNominalProcess.cxx(800000014$1,1, {{0,30}})"
#
#cd /home/vince402/Upsilon3S/Macros
#./runYIeldRatio.sh 8000000011 1 1
#./runYIeldRatio.sh 8000000011 3 1
#./runYIeldRatio.sh 8000000011 2 2
#./runYIeldRatio.sh 8000000011 1 3
./runYIeldRatio.sh 800000014$1 3 3
}
#
#cd Macros
#root -l -b -q "DrawYield.C(8100000001)"

for i in {1..7}
do
	part1 $i
done
for i in {1..7}
do
	part2 $i
done
