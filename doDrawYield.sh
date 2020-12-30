#!/bin/bash
#DrawYieldHist(const double ptCut = 3.5, int cBinLow = 0, int cBinHigh = 180, in    t Trig = "S1", bool trigSwitch = true)

#root -l -b -q 'DrawYieldHist.C(3.5, 0, 180, "S1", true)'
#root -l -b -q 'DrawYieldHist.C(3.5, 80, 180, "S1", true)'
#root -l -b -q 'DrawYieldHist.C(3.5, 0, 80, "S1", true)'
#root -l -b -q 'DrawYieldHist.C(3.5, 0, 180, "S2", true)'
#root -l -b -q 'DrawYieldHist.C(3.5, 100, 180, "S2", true)'
#root -l -b -q 'DrawYieldHist.C(3.5, 0, 100, "S2", true)'
#
#root -l -b -q 'DrawYieldHist.C(3.5, 80, 180, "S1", false)'
#root -l -b -q 'DrawYieldHist.C(3.5, 100, 180, "S2", false)'
root -l -b -q 'DrawYieldHist.C(3.5, 0, 180, "S13", false)'
root -l -b -q 'DrawYieldHist.C(3.5, 0, 100, "S13", false)'
root -l -b -q 'DrawYieldHist.C(3.5, 0, 80, "S13", false)'
root -l -b -q 'DrawYieldHist.C(3.5, 80, 180, "S13", false)'
root -l -b -q 'DrawYieldHist.C(3.5, 100, 180, "S13", false)'

#root -l -b -q 'DrawYieldHist.C(4, 0, 180, "S1", true)'
#root -l -b -q 'DrawYieldHist.C(4, 80, 180, "S1", true)'
#root -l -b -q 'DrawYieldHist.C(4, 0, 80, "S1", true)'
#root -l -b -q 'DrawYieldHist.C(4, 0, 180, "S2", true)'
#root -l -b -q 'DrawYieldHist.C(4, 100, 180, "S2", true)'
#root -l -b -q 'DrawYieldHist.C(4, 0, 100, "S2", true)'
#
#root -l -b -q 'DrawYieldHist.C(4, 80, 180, "S1", false)'
#root -l -b -q 'DrawYieldHist.C(4, 100, 180, "S2", false)'
root -l -b -q 'DrawYieldHist.C(4, 0, 180, "S13", false)'
root -l -b -q 'DrawYieldHist.C(4, 0, 100, "S13", false)'
root -l -b -q 'DrawYieldHist.C(4, 0, 80, "S13", false)'
root -l -b -q 'DrawYieldHist.C(4, 80, 180, "S13", false)'
root -l -b -q 'DrawYieldHist.C(4, 100, 180, "S13", false)'
