#!/bin/bash
#	1.QQVtxProb  2.QQdca  3.ctau(2D)  4.ctau(3D)  5.cosalpha(2D)  6.cosalpha(3D)
#   100019111111 : Blind nom, 2*** Unblind, *N0019*** : Quat N
function TRAINERCheck {
#	DATASET=\"testBlind_Quat1.root"\
	root -l -b -q "BDTClassifier_BLIND_BDTCOMB_postApprov.C(300519011111, "$OPT", "$DATPREP", true, \"OutputSkim_isMC0_m614_v211025_ForBLIND.root\" )" 2>&1| tee BDT"$TS".log
#	root -l -b -q "BDTClassifier_BLIND_BDTCOMB_NOM_comment.C(130019111111, "$OPT", "$DATPREP", true, \"testBlind_Quat3.root\")" 2>&1| tee BDT"$TS".log
#	echo $DATAPREP >> ./.past_source/_BDTClassifier_BLIND_BDTCOMB_$TS.old
#	echo $OPT >> ./.past_source/_BDTClassifier_BLIND_BDTCOMB_$TS.old
#	root -l -b -q "BDTNominalProcess.cxx(140019111111, 140019111111, 0, {{0,30}}, \"testBlind_Quat4.root\")"
#	root -l -b -q "BDTNominalProcess.cxx(300019011111, 300019011111, 0, {{0,30}})"
#	root -l -b -q "BDTNominalProcess.cxx(100119111111, 112019111111, 0, {{0,30}}, \"testBlind_Quat4.root\")"
#	root -l -b -q "BDTNominalProcess.cxx(112019111111, 212019111111, 0, {{0,30}}, \"test220217.root\")"
	root -l -b -q "BDTNominalProcess.cxx(300519011111, 400519011111, 0, {{0,30}}, \"test220217.root\")"
#	root -l -b -q 'BDTNominalProcess.cxx(100219110101, 0, {{0,4}})'
}
TS=300519011111 #FROM 40
DATPREP=""\"SplitSeed=100:SplitMode=Random:NormMode=None:Correlations=False:!V\"""
OPT=""\"\!H:\!V:NTrees=350:MaxDepth=3:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.1:UseBaggedBoost=True:SeparationType=GiniIndex:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:DoBoostMonitor:VarTransform=G+D\"""
#OPT=""\"\!H:\!V:NTrees=700:MaxDepth=5:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.1:UseBaggedBoost=True:SeparationType=GiniIndex:PruneMethod=CostComplexity:PruneStrength=1:PruningValFraction=0.3:UseRandomisedTrees=False:BaggedSampleFraction=0.4:nCuts=200:DoBoostMonitor:VarTransform=G+D+G\"""
TRAINERCheck

