#!/bin/bash
#void makeRooDataSet(bool isMC, bool fAccW, bool fEffW, int state, string Str = "OniaSkim_TirgS0")
#root -l -b -q 'makeRooDataSet.C(false, false, false, 2, "OniaSkim_TrigS13")'
#root -l -b -q 'makeRooDataSet.C(false, false, false, 2, "OniaSkim_TrigS2")'
#root -l -b -q 'makeRooDataSet.C(true, false, false, 2, "OniaSkim_TrigS13")'
#root -l -b -q 'makeRooDataSet.C(true, false, false, 2, "OniaSkim_TrigS1")'
#root -l -b -q 'makeRooDataSet.C(true, false, false, 2, "OniaSkim_TrigS2")'
root -l -b -q 'makeRooDataSet.C(false, false, false, 2, "OniaSkim_TrigS1_PDty1_Switch1")'
root -l -b -q 'makeRooDataSet.C(false, false, false, 2, "OniaSkim_TrigS1_PDty1")'
