#!/bin/bash
#DATA
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigL1DBOS40100, 0, 1, false)' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigL1DBOS40100, 0, 2, false )' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigL1DB50100, 0, 1, false )' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigL1DB50100, 0, 2, false )' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigUps, 0, 1, false )' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigUps, 0, 2, false )' 

#FOR DATA TRIGGER SWITCH
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigL1DBOS40100, 0, 1, true )' & 
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigL1DBOS40100, 0, 2, true )' & 
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigL1DB50100, 0, 1, true )' &
#root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigL1DB50100, 0, 2, true )' 
root -l -b -q 'SkimTree_Event_MT.C(-1, false, kTrigUps, 0, 1, false )' 

#MC (NEED UPDATE)
#root -l -b -q 'SkimTree_Event_MT.C(-1, true, kTrigL1DBOS40100, 0, 1)' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, true, kTrigL1DBOS40100, 0, 2)' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, true, kTrigL1DB50100, 0, 1)' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, true, kTrigL1DB50100, 0, 2)' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, true, kTrigUps, 0, 1)' 
#root -l -b -q 'SkimTree_Event_MT.C(-1, true, kTrigUps, 0, 2)' 
