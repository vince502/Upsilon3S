#!/bin/bash


#cd Macros
#root -l -b -q 'DrawYield.C(80000000027)'
function TRAINER {
#	root -l -b -q "BDTClassifier_BLIND_BDT.C("$TS", "$OPT", "$DATPREP")" 2>&1| tee BDT"$TS".log
	root -l -b -q "BDTNominalProcess.cxx(9999999999,0, {{12,15}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,1, {{0,3}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,1, {{3,6}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,1, {{6,9}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,0, {{0,50}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,0, {{15,50}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,0, {{0,30}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,1, {{0,30}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,0, {{0,4}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,0, {{4,9}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,0, {{9,15}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,1, {{9,15}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,1, {{15,30}})"
#	root -l -b -q "BDTNominalProcess.cxx(9999999999,0, {{15,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,4}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{4,9}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{9,12}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,50}})"
}
TS=9000000052 #FROM 40
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:!V\"""
OPT=""\"\!H:\!V:NTrees=300:MaxDepth=2:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.7:UseBaggedBoost=True:SeparationType=CrossEntropy:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D\"""
#TRAINER
#./runBDTFit.sh ############CHECK THE CONSEQUENCES!###############

function TRAINER2 {
	root -l -b -q "BDTClassifier_BLIND_BDTCOMB.C("$TS", "$OPT", "$DATPREP")" 2>&1| tee BDT"$TS".log
	root -l -b -q "BDTNominalProcess.cxx(10000000001,1, {{0,3}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000001,1, {{3,6}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000001,1, {{6,9}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000001,0, {{9,15}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000001,1, {{9,15}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000001,0, {{15,30}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000001,0, {{0,30}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000001,1, {{0,30}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000001,0, {{0,4}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000001,0, {{4,9}})"


#	root -l -b -q "BDTNominalProcess.cxx(10000000000,0, {{12,30}})"
#	root -l -b -q "BDTNominalProcess.cxx(10000000000,0, {{12,50}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,4}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{4,9}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{9,12}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,50}})"
}
TS=9000000053 #FROM 40
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:!V\"""
OPT=""\"\!H:\!V:NTrees=300:MaxDepth=2:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.7:UseBaggedBoost=True:SeparationType=CrossEntropy:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D\"""
#TRAINER2
#./runBDTFit.sh ############CHECK THE CONSEQUENCES!###############

function TRAINER3 {
#	root -l -b -q "BDTClassifier_BLIND_BDTCOMB.C("$TS", "$OPT", "$DATPREP")" 2>&1| tee BDT"$TS".log
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,1, {{0,3}})"
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,1, {{3,6}})"
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,1, {{6,9}})"
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,0, {{9,15}})"
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,1, {{9,15}})"
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,0, {{15,30}})"
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,0, {{0,30}})"
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,1, {{0,30}})"
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,0, {{0,4}})"
#	root -l -b -q "BDTNominalProcess.cxx(11000000000,0, {{4,9}})"

	root -l -b -q "BDTNominalProcess.cxx(11000000000,1, {{15,30}})"

#	root -l -b -q "BDTNominalProcess.cxx(10000000000,0, {{12,30}})"
#	root -l -b -q "BDTNominalProcess.cxx(10000000000,0, {{12,50}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,4}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{4,9}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{9,12}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,50}})"
}
TS=9000000054 #FROM 40
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:!V\"""
OPT=""\"\!H:\!V:NTrees=300:MaxDepth=2:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.7:UseBaggedBoost=True:SeparationType=CrossEntropy:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D\"""
#TRAINER3
#./runBDTFit.sh ############CHECK THE CONSEQUENCES!###############

function TRAINER4 {
#	root -l -b -q "BDTClassifier_BLIND_BDTCOMB.C(10000000025, "$OPT", "$DATPREP", false)" 2>&1| tee BDT"$TS".log
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{0,30}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{0,3}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{0,4}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{3,6}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{6,9}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{9,15}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{9,15}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{15,30}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{0,30}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{4,9}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{15,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {10,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,4}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{4,9}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{9,12}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,50}})"
}
TS=90000001151 #FROM 40
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:Correlations=False:!V\"""
OPT=""\"\!H:\!V:NTrees=300:MaxDepth=2:MinNodeSize=5%:BoostType=AdaBoost:AdaBoostBeta=0.6:Shrinkage=0.1:UseBaggedGrad=True:SeparationType=CrossEntropy:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:DoBoostMonitor:VarTransform=G+D\"""
#TRAINER4
#UseFisherCuts=True:UseExclusiveVars=True:DoPreselection=True: :

#cd ../
#root -l -b -q 'doConstraintFit_NOM_combv2tmp.cxx(111, 10000000025)'  2>&1 | tee fitlog_v2tmp.log
#./runBDTFit.sh ############CHECK THE CONSEQUENCES!###############

#NOMINAL ( 10000000016 ) -- DO NOT CHANGE !
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:!V\"""
OPT=""\"\!H:\!V:NTrees=300:MaxDepth=2:MinNodeSize=5%:BoostType=Grad:AdaBoostBeta=0.7:UseBaggedBoost=True:SeparationType=CrossEntropy:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:CreateMVAPdfs:DoBoostMonitor:VarTransform=G+D+G+D\"""
#TRAINER3
#./runBDTFit.sh ############CHECK THE CONSEQUENCES!###############

function TRAINERNOM {
#	root -l -b -q "BDTClassifier_BLIND_BDTCOMB_NOM.C(10000000016, "$OPT", "$DATPREP", false)" 2>&1| tee BDT"$TS".log
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{0,30}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{0,3}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{0,4}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{3,6}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{6,9}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{9,15}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{9,15}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{15,30}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{0,30}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{4,9}})"
	root -l -b -q "BDTNominalProcess.cxx(10000000016,0, {{15,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {10,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,4}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{4,9}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{9,12}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,50}})"
}
TS=90000009999 #FROM 40
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:Correlations=False:!V\"""
OPT=""\"\!H:\!V:NTrees=350:MaxDepth=3:MinNodeSize=10%:BoostType=Grad:Shrinkage=0.1:AdaBoostBeta=0.4:UseBaggedBoost=True:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:DoBoostMonitor:VarTransform=G+D\"""
#TRAINERNOM

function TRAINERNOMCENT {
	root -l -b -q "BDTClassifier_BLIND_BDTCOMB_NOM_CENT.C(100000000161, "$OPT", "$DATPREP", false)" 2>&1| tee BDT"$TS".log
#	root -l -b -q "BDTNominalProcess.cxx(100000000161,0, {{0,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {10,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{0,4}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{4,9}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{9,12}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,30}})"
##	root -l -b -q "BDTNominalProcess.cxx("$TS",0, {{12,50}})"
}
TS=90000009998 #FROM 40
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:Correlations=False:!V\"""
OPT=""\"\!H:\!V:NTrees=350:MaxDepth=3:MinNodeSize=10%:BoostType=Grad:Shrinkage=0.1:AdaBoostBeta=0.4:UseBaggedBoost=True:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:DoBoostMonitor:VarTransform=G+D\"""
TRAINERNOMCENT
