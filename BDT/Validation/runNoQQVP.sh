#!/bin/bash
#root -l -b -q 'BDTClassifier_BLIND_noQQVP.C'
#root -l -b -q 'BDTNominalProcess.cxx(8000000004,0)'
#root -l -b -q 'BDT_trainVariable_Mass_Distribution.C(8000000004,1)'
cd /home/vince402/Upsilon3S
root -l -b -q 'doConstraintFit_VALI.cxx(1314,8000000004,33, 0.2)'
root -l -b -q 'doConstraintFit_VALI.cxx(1314,8000000004,11, 0.2)'
root -l -b -q 'doConstraintFit_VALI.cxx(1314,8000000004,33, 0.1)'
root -l -b -q 'doConstraintFit_VALI.cxx(1314,8000000004,11, 0.1)'


#
#cd Macros
#root -l -b -q 'DrawYield.C(8000000003)'
