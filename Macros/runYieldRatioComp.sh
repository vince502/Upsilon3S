#!/bin/bash
#cd /home/vince402/Upsilon3S #BDT/Validation
#root -l -b -q 'doConstraintFit_VALI.cxx(1312, 8000000004)'
#cd /home/vince402/Upsilon3S/Macros #BDT/Validation
#root -l -b -q 'DrawYield_Ratio.C(8000000004)'
cd /home/vince402/Upsilon3S #BDT/Validation
root -l -b -q 'doConstraintFit_VALI.cxx(1312, 8000000007)'
cd /home/vince402/Upsilon3S/Macros #BDT/Validation
root -l -b -q 'DrawYield_Ratio.C(8000000007)'