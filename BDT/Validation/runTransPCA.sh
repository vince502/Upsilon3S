#!/bin/bash
root -l -b -q 'BDTClassifier_BLIND_transPCA.C'
root -l -b -q 'BDTNominalProcess.cxx(8000000003,0)'
root -l -b -q 'BDT_trainVariable_Mass_Distribution.C(8000000003,1)'
#cd /home/vince402/Upsilon3S
#root -l -b -q 'doConstraintFit_VALI.cxx(1312,8000000003)'
#
#cd Macros
#root -l -b -q 'DrawYield.C(8000000003)'
