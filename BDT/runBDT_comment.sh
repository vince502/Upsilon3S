#!/bin/bash
#	1.QQVtxProb  2.QQdca  3.ctau(2D)  4.ctau(3D)  5.cosalpha(2D)  6.cosalpha(3D)
function TRAINERCheck {
	root -l -b -q "BDTClassifier_BLIND_BDTCOMB_NOM_comment.C(100019111111, "$OPT", "$DATPREP", true)" 2>&1| tee BDT"$TS".log
	root -l -b -q 'BDTNominalProcess.cxx(100019111111, 0, {{0,30}})'
	root -l -b -q 'BDTNominalProcess.cxx(100019111111, 0, {{0,4}})'
}
TS=90019111111 #FROM 40
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:Correlations=False:!V\"""
OPT=""\"\!H:\!V:NTrees=350:MaxDepth=3:MinNodeSize=10%:BoostType=Grad:Shrinkage=0.1:AdaBoostBeta=0.4:UseBaggedBoost=True:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:DoBoostMonitor:VarTransform=G+D\"""
TRAINERCheck

