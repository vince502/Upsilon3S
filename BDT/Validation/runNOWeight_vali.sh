#!/bin/bash
root -l -b -q 'BDTClassifier_BLIND_noWeight.C'
root -l -b -q 'BDTNominalProcess.cxx(8000000002,0)'
cd /home/vince402/Upsilon3S
root -l -b -q 'doConstraintFit_VALI.cxx(1312,8000000002)'

cd Macros
root -l -b -q 'DrawYield.C(8000000002)'
