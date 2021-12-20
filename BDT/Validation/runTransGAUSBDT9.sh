#!/bin/bash
#cd Macros
#root -l -b -q 'DrawYield.C(80000000020)'
root -l -b -q "BDTClassifier_BLIND_BDT9.C" 2>&1| tee BDT9.log
root -l -b -q "BDTNominalProcess.cxx(8000000020,0, {{0,30}})"
#root -l -b -q "BDT_trainVariable_Mass_Distribution.C(8000000020,1)"
cd /home/vince402/Upsilon3S
root -l -b -q "doConstraintFit_VALI_v3.cxx(1311,8000000020,3)"
#cd /home/vince402/Upsilon3S/BDT/Validation
#root -l -b -q "BDTNominalProcess.cxx(8000000020,1, {{0,30}})"
#
cd /home/vince402/Upsilon3S/Macros
#./runYIeldRatio.sh 8000000011 1 1
#./runYIeldRatio.sh 8000000011 3 1
#./runYIeldRatio.sh 8000000011 2 2
#./runYIeldRatio.sh 8000000020 1 3
#./runYIeldRatio.sh 8000000020 2 3
#./runYIeldRatio.sh 8000000020 3 3
#
#cd Macros
#root -l -b -q "DrawYield.C(8100000001)"
