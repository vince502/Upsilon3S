#!/bin/bash

#void SkimTree_Event(int nevt=-1, bool isMC = true, int kTrigSel = kTrigUps, int hiHFBinEdge = 0, int PDtype = 1) 
root -l -b -q 'SkimTree_Event.C(-1, true, 1, 0, 1)' 
root -l -b -q 'SkimTree_Event.C(-1, true, 2, 0, 1)' 
root -l -b -q 'SkimTree_Event.C(-1, true, 10, 0, 1)' 
