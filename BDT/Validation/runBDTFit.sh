#!/bin/bash


#cd Macros
#root -l -b -q 'DrawYield.C(80000000027)'
function TRAINER {
	root -l -b -q "BDTClassifier_BLIND_BDT.C("$TS", "$OPT", "$DATPREP")" 2>&1| tee BDT"$TS".log
	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,30}})"
}
function ONECYCLE {
#root -l -b -q "BDT_trainVariable_Mass_Distribution.C("$TS",1)"
cd /home/vince402/Upsilon3S
root -l -b -q "doConstraintFit_VALI_v3.cxx(1311,"$TS",3)" 2>&1 | tee Fitresult.log
#root -l -b -q "doConstraintFit_VALI_v3.cxx(1311,"$TS",2)" 2>&1 | tee Fitresult2.log
#root -l -b -q "doConstraintFit_VALI_v3.cxx(1311,"$TS",1)"
cd /home/vince402/Upsilon3S/BDT/Validation
#root -l -b -q "BDTNominalProcess.cxx("$TS",1, {{0,30}})"
#cd /home/vince402/Upsilon3S
#root -l -b -q "doConstraintFit_VALI_v3.cxx(13113,"$TS",2)"
#root -l -b -q "BDTNominalProcess.cxx("$TS",1, {{0,30}})"
#
cd /home/vince402/Upsilon3S/Macros
#./runYIeldRatio.sh "$TS" 1 3
#./runYIeldRatio.sh "$TS" 2 3
#./runYIeldRatio.sh "$TS" 3 3
#./runYIeldRatio.sh "$TS" 1 2
#./runYIeldRatio.sh "$TS" 2 2
#./runYIeldRatio.sh "$TS" 3 2
#root -l -b -q "DrawMass2.cxx("$TS", 1)"
#root -l -b -q "DrawMass2.cxx("$TS", 2)"
#root -l -b -q "DrawMass2.cxx("$TS", 3)"
#
#tar -zcvf result_"$TS".tar.gz  /home/vince402/Upsilon3S/BDT/Validation/../.past_source/_BDTClassifier_BLIND_BDT_"$TS".old ./FullMassBDT/FullMassBDTCompare_fullmass_m614_"$TS"_1.C ./FullMassBDT/FullMassBDTCompare_fullmass_m614_"$TS"_2.C ./FullMassBDT/FullMassBDTCompare_fullmass_m614_"$TS"_3.C BDTCorYield_plots_"$TS".root
#mv result_"$TS".tar.gz /home/vince402/Upsilon3S/BDT/Validation
}
function ONECYCLE2 {
#root -l -b -q "BDT_trainVariable_Mass_Distribution.C("$TS",1)"
cd /home/vince402/Upsilon3S
root -l -b -q "doConstraintFit_VALI_v3.cxx(1312,"$TS",3)" 2>&1 | tee Fitresult.log
root -l -b -q "doConstraintFit_VALI_v3.cxx(1312,"$TS",2)" 2>&1 | tee Fitresult2.log
#root -l -b -q "doConstraintFit_VALI_v3.cxx(1311,"$TS",1)"
cd /home/vince402/Upsilon3S/BDT/Validation
#root -l -b -q "BDTNominalProcess.cxx("$TS",1, {{0,30}})"
#cd /home/vince402/Upsilon3S
#root -l -b -q "doConstraintFit_VALI_v3.cxx(13113,"$TS",2)"
#root -l -b -q "BDTNominalProcess.cxx("$TS",1, {{0,30}})"
#
cd /home/vince402/Upsilon3S/Macros
#./runYIeldRatio.sh "$TS" 1 3
#./runYIeldRatio.sh "$TS" 2 3
#./runYIeldRatio.sh "$TS" 3 3
#./runYIeldRatio.sh "$TS" 1 2
#./runYIeldRatio.sh "$TS" 2 2
#./runYIeldRatio.sh "$TS" 3 2
#root -l -b -q "DrawMass2.cxx("$TS", 1)"
#root -l -b -q "DrawMass2.cxx("$TS", 2)"
#root -l -b -q "DrawMass2.cxx("$TS", 3)"
#
#tar -zcvf result_"$TS".tar.gz  /home/vince402/Upsilon3S/BDT/Validation/../.past_source/_BDTClassifier_BLIND_BDT_"$TS".old ./FullMassBDT/FullMassBDTCompare_fullmass_m614_"$TS"_1.C ./FullMassBDT/FullMassBDTCompare_fullmass_m614_"$TS"_2.C ./FullMassBDT/FullMassBDTCompare_fullmass_m614_"$TS"_3.C BDTCorYield_plots_"$TS".root
#mv result_"$TS".tar.gz /home/vince402/Upsilon3S/BDT/Validation
}
#TS=8200000002
#DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
#OPT=""\"\!H:\!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.6:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TRAINER &
#TS=8200000003
#DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
#OPT=""\"\!H:\!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.6:SeparationType=GiniIndexWithLaplace:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TRAINER &
#TS=8200000004
#DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
#OPT=""\"\!H:\!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.6:SeparationType=MisClassificationError:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TRAINER &
#TS=8200000005
#DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
#OPT=""\"\!H:\!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.6:SeparationType=SDivSqrtSPlusB:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TRAINER
#wait
#TS=8200000006
#DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
#OPT=""\"\!H:\!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TS=8200000011
#DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
#OPT=""\"\!H:\!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=GiniIndexWithLaplace:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TRAINER &
##
#TS=8200000012
#DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
#OPT=""\"\!H:\!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.3:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TRAINER &
#TS=8200000013
#DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
#OPT=""\"\!H:\!V:NTrees=700:MaxDepth=3:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.4:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TRAINER &
#TS=8200000010
#DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
#OPT=""\"\!H:\!V:NTrees=500:MaxDepth=3:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TRAINER
TS=8200000015
DATPREP=""\"SplitSeed=100:nTrain_Signal=50000:nTest_Signal=50000:SplitMode=Alternate:NormMode=None:!V\"""
OPT=""\"\!H:\!V:NTrees=1000:MaxDepth=3:MinNodeSize=5%:BoostType=Grad:UseBaggedBoost=True:AdaBoostBeta=0.4:SeparationType=CrossEntropy:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=-1:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D+G\"""
#TRAINER

#TS=8200000006
#ONECYCLE
#TS=8200000008
#ONECYCLE
#TS=8200000009
#ONECYCLE
#TS=8200000010
#ONECYCLE
#TS=8200000011
#ONECYCLE
#TS=8200000018
#ONECYCLE
TS=8000000037
#ONECYCLE2
#TS=8000000042
#ONECYCLE
TS=$1
ONECYCLE
#
#cd Macros
#root -l -b -q "DrawYield.C(8100000001)"

