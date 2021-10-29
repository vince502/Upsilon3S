#!/bin/bash
root -l -b -q 'BDTClassifier_BLIND_NOM.C'
root -l -b -q 'BDTNominalProcess.cxx(8000000001,0)'
cd /home/vince402/Upsilon3S
root -l -b -q 'doConstraintFit_VALI.cxx(1312,8000000001)'

cd Macros
root -l -b -q 'DrawYield.C(8000000001)'
