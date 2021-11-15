#!/bin/bash
TS=8000000028
#cd Macros
#root -l -b -q 'DrawYield.C(80000000028)'
root -l -b -q "BDTClassifier_BLIND_BDT17.C" 2>&1| tee BDT17.log
root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,30}})"
#root -l -b -q "BDT_trainVariable_Mass_Distribution.C("$TS",1)"
cd /home/vince402/Upsilon3S
root -l -b -q "doConstraintFit_VALI_v3.cxx(1311,"$TS",3)"
cd /home/vince402/Upsilon3S/BDT/Validation
root -l -b -q "BDTNominalProcess.cxx("$TS",1, {{0,30}})"
cd /home/vince402/Upsilon3S
root -l -b -q "doConstraintFit_VALI_v3.cxx(1311,"$TS",2)"
#cd /home/vince402/Upsilon3S/BDT/Validation
#root -l -b -q "BDTNominalProcess.cxx("$TS",1, {{0,30}})"
#
cd /home/vince402/Upsilon3S/Macros
./runYIeldRatio.sh "$TS" 1 3
./runYIeldRatio.sh "$TS" 2 3
./runYIeldRatio.sh "$TS" 3 3
./runYIeldRatio.sh "$TS" 1 2
./runYIeldRatio.sh "$TS" 2 2
./runYIeldRatio.sh "$TS" 3 2
root -l -b -q "DrawMass2.cxx("$TS", 1)"
root -l -b -q "DrawMass2.cxx("$TS", 2)"
root -l -b -q "DrawMass2.cxx("$TS", 3)"

tar -zcvf result_$TS.tar.gz ./FullMassBDT/FullMassBDTCompare_fullmass_m614_"$TS"_1.C ./FullMassBDT/FullMassBDTCompare_fullmass_m614_"$TS"_2.C ./FullMassBDT/FullMassBDTCompare_fullmass_m614_"$TS"_3.C BDTCorYield_plots_"$TS".root
mv result_"$TS".tar.gz /home/vince402/Upsilon3S/BDT/Validation
#
#cd Macros
#root -l -b -q "DrawYield.C(8100000001)"

