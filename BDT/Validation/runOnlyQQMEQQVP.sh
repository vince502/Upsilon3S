#!/bin/bash
root -l -b -q 'BDTClassifier_BLIND_onlyQQMEQQVP.C'
root -l -b -q 'BDTNominalProcess.cxx(8100000003,0)'
root -l -b -q 'BDT_trainVariable_Mass_Distribution.C(8100000003,1)'
cd /home/vince402/Upsilon3S
root -l -b -q 'doConstraintFit_VALI.cxx(1312,8100000003)'
cd /home/vince402/Upsilon3S/BDT/Validation
oot -l -b -q 'BDTNominalProcess.cxx(8100000003,1)'

cd /home/vince402/Upsilon3S/Macros
./runYIeldRatio.sh 8100000003 1 1
./runYIeldRatio.sh 8100000003 3 1
./runYIeldRatio.sh 8100000003 2 2
./runYIeldRatio.sh 8100000003 1 3
./runYIeldRatio.sh 8100000003 3 3
#
#cd Macros
#root -l -b -q 'DrawYield.C(8100000001)'
