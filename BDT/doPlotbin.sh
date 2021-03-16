#!/bin/bash
#04 49 912 1230
#PlotYieldtoEffandSignifbin.C(long ts, double ylim, double ptlow, double pthigh, int cbinlow, int cbinhigh)
root -l -b -q 'PlotYieldtoEffandSignifbin.C(1614848550, 2.4, 0., 4., 0, 180)'&
#root -l -b -q 'PlotYieldtoEffandSignifbin.C(1614848550, 2.4, 4., 9., 0, 180)'
#root -l -b -q 'PlotYieldtoEffandSignifbin.C(1614848550, 2.4, 9., 12., 0, 180)'&
#root -l -b -q 'PlotYieldtoEffandSignifbin.C(1614848550, 2.4, 12., 30., 0, 180)'
