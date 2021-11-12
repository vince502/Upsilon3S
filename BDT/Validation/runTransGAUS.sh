#!/bin/bash
#root -l -b -q 'BDTClassifier_BLIND_transGAUS.C'
#root -l -b -q 'BDTNominalProcess.cxx(8000000010,0)'
#root -l -b -q 'BDT_trainVariable_Mass_Distribution.C(8000000010,1)'
#cd /home/vince402/Upsilon3S
#root -l -b -q 'doConstraintFit_VALI.cxx(1312,8000000010)'
#cd /home/vince402/Upsilon3S/Macros 
./runYieldRatioComp_afterTrain.sh 8000000010 3 3
./runYieldRatioComp_afterTrain.sh 8000000010 2 2
./runYieldRatioComp_afterTrain.sh 8000000010 1 1
#root -l -b -q 'BDTNominalProcess.cxx(8000000010,1)'

#
#cd Macros
#root -l -b -q 'DrawYield.C(8000000010)'

#!/bin/bash
#root -l -b -q 'BDTClassifier_BLIND_transGAUSBDTG.C'
#root -l -b -q 'BDTNominalProcess.cxx(8000000011,0)'
#root -l -b -q 'BDT_trainVariable_Mass_Distribution.C(8000000011,1)'
cd /home/vince402/Upsilon3S
root -l -b -q 'doConstraintFit_VALI.cxx(1200,8000000011)'
#cd /home/vince402/Upsilon3S/BDT/Validation
#root -l -b -q 'BDTNominalProcess.cxx(8000000011,1)'
#
#cd /home/vince402/Upsilon3S/Macros
#./runYIeldRatio.sh 8000000011 1 1
#./runYIeldRatio.sh 8000000011 3 1
#./runYIeldRatio.sh 8000000011 2 2
#./runYIeldRatio.sh 8000000011 1 3
#./runYIeldRatio.sh 8000000011 3 3
#
#cd Macros
#root -l -b -q 'DrawYield.C(8100000001)'
