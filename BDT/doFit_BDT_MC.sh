#!/bin/bash

ts=$1
export timestamp=$ts
	cd ..
root -l -b -q 'MassYieldFit_BDT_MC.C('$timestamp',"", "OniaRooDataset_BDT'$timestamp'_OniaSkim_TrigS13_BDT_MC.root", 0, 30, -2.4, 2.4, "3p5", "S13", 180, 3, false, 0.01, 0.2 ,1.)' &  2>/dev/null
