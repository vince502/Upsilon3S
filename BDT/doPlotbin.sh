#!/bin/bash
#04 49 912 1230
#PlotYieldtoEffandSignifbin.C(long ts, double ylim, double ptlow, double pthigh, int cbinlow, int cbinhigh)
#root -l -b -q 'PlotYieldtoEffandSignifbin.C(1614848550, 2.4, 0., 30., 0, 180, false, 5)'
#
#ylim=1.2;ts=1614932252;
#ylim=2.4;ts=1614848550;
#FOR BLIND
#ylim=1.2;ts=1617964901;
#ylim=2.4;ts=1617963007;
#FOR OTHER VARIABLES
#ylim=2.4;ts=1618036602;
#INCLUDED COS_ALPHA
#ylim=2.4;ts=1618491012;
#ALL VAR
ylim=2.4;ts=1618505174;
numbin=3;

#root -l -b -q 'plotresult.C('$ts', '$ylim', 0,30, 0, 180,0.01, "3p5","S13", "freefit")'

root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 0., 30., 0, 180, false, '$numbin')'&

#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 0., 4., 0, 180, false, '$numbin')'
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 4., 9., 0, 180, false, '$numbin')'&
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 9., 12., 0, 180, false, '$numbin')'
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 12., 30., 0, 180, false, '$numbin')'&
#
#
#
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 0., 6. , 0  , 180, false, '$numbin')'
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 6., 30., 0  , 180, false, '$numbin')'&
#
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 0., 6. , 0  , 40 , false, '$numbin')'
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 6., 30., 0  , 40 , false, '$numbin')'&
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 0., 30., 0  , 40 , false, '$numbin')'
#
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 0., 6. , 40 , 100, false, '$numbin')'&
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 6., 30., 40 , 100, false, '$numbin')'
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 0., 30., 40 , 100, false, '$numbin')'&
#
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 0., 6. , 100, 180, false, '$numbin')'
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 6., 30., 100, 180, false, '$numbin')'&
#root -l -b -q 'PlotYieldtoEffandSignifbin.C('$ts', '$ylim', 0., 30., 100, 180, false, '$numbin')'

#root -l -b -q 'plotresult.C('$ts', '$ylim', 0, 4, 0, 180,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim', 4, 9, 0, 180,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim', 9,12, 0, 180,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim',12,30, 0, 180,0.01, "3p5","S13", "freefit")'

#root -l -b -q 'plotresult.C('$ts', '$ylim', 0, 6 , 0  , 180,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim', 6, 30, 0  , 180,0.01, "3p5","S13", "freefit")'
                                                              
#root -l -b -q 'plotresult.C('$ts', '$ylim', 0, 6 , 0  , 40 ,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim', 6, 30, 0  , 40 ,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim', 0, 30, 0  , 40 ,0.01, "3p5","S13", "freefit")'
                                                              
#root -l -b -q 'plotresult.C('$ts', '$ylim', 0, 6 , 40 , 100,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim', 6, 30, 40 , 100,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim', 0, 30, 40 , 100,0.01, "3p5","S13", "freefit")'
                                                              
#root -l -b -q 'plotresult.C('$ts', '$ylim', 0, 6 , 100, 180,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim', 6, 30, 100, 180,0.01, "3p5","S13", "freefit")'
#root -l -b -q 'plotresult.C('$ts', '$ylim', 0, 30, 100, 180,0.01, "3p5","S13", "freefit")'
