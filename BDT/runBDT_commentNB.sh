#!/bin/bash
#	1.QQVtxProb  2.QQdca  3.ctau(2D)  4.ctau(3D)  5.cosalpha(2D)  6.cosalpha(3D)
function TRAINERCheck {
#	root -l -b -q "BDTClassifier_BLIND_BDTCOMB_NOM_commentNB.C(400019111111, "$OPT", "$DATPREP", false)" 2>&1| tee BDT"$TS".log
	root -l -b -q "BDTNominalProcessNB.cxx(400019111111,0, {{0,30}}, 400019111111)"
	root -l -b -q "BDTNominalProcessNB.cxx(400019111111,0, {{0,4}}, 400019111111)"
	root -l -b -q "BDTNominalProcessNB.cxx(400019111111,0, {{4,9}}, 400019111111)"
	root -l -b -q "BDTNominalProcessNB.cxx(400019111111,0, {{9,15}}, 400019111111)"
	root -l -b -q "BDTNominalProcessNB.cxx(400019111111,0, {{15,30}}, 400019111111)"
	root -l -b -q "BDTNominalProcessNB.cxx(400019111111,0, {{0,3}}, 400019111111)"
	root -l -b -q "BDTNominalProcessNB.cxx(400019111111,0, {{3,6}}, 400019111111)"
	root -l -b -q "BDTNominalProcessNB.cxx(400019111111,0, {{6,9}}, 400019111111)"
#	root -l -b -q "BDTNominalProcess.cxx(20000000011,0, {{0,30}})"
#	root -l -b -q "BDTNominalProcessNB.cxx(20000000002,0, {{0,30}})"
#	root -l -b -q "BDTNominalProcessNB.cxx(20000000004,0, {{0,30}})"
#	root -l -b -q "BDTNominalProcessNB.cxx(20000000000,0, {{0,3}})"
#	root -l -b -q "BDTNominalProcessNB.cxx(20000000000,0, {{3,6}})"
#	root -l -b -q "BDTNominalProcessNB.cxx(20000000000,0, {{6,9}})"
#	root -l -b -q "BDTNominalProcessNB.cxx(20000000000,0, {{0,4}})"
#	root -l -b -q "BDTNominalProcessNB.cxx(20000000000,0, {{4,9}})"
#	root -l -b -q "BDTNominalProcessNB.cxx(20000000000,0, {{9,15}})"
#	root -l -b -q "BDTNominalProcessNB.cxx(20000000000,0, {{15,30}})"
}
TS=90019111111 #FROM 40
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:Correlations=False:!V\"""
OPT=""\"\!H:\!V:NTrees=350:MaxDepth=3:MinNodeSize=10%:BoostType=Grad:Shrinkage=0.1:AdaBoostBeta=0.4:UseBaggedBoost=True:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:DoBoostMonitor:VarTransform=G+D\"""
TRAINERCheck

