#!/bin/bash
root -l -b -q 'BDTClassifier_BLIND_transGAUS.C'
root -l -b -q 'BDTNominalProcess.cxx(8000000010,0)'
root -l -b -q 'BDT_trainVariable_Mass_Distribution.C(8000000010,1)'
cd /home/vince402/Upsilon3S
root -l -b -q 'doConstraintFit_VALI.cxx(1312,8000000010)'
cd /home/vince402/Upsilon3S/Macros 
./runYieldRatioComp_afterTrain.sh 8000000010

#
#cd Macros
#root -l -b -q 'DrawYield.C(8000000010)'
