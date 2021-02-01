#!/bin/bash


#void getAcceptance(double ptLow = 0, double ptHigh=30, double yLow=0, double yHigh=2.4, double SiMuPtCut=4)
root -l -b -q 'getAcceptance.C(0,  6, 0, 2.4, 4  )' &
root -l -b -q 'getAcceptance.C(0,  6, 0, 2.4, 3.5)' &
root -l -b -q 'getAcceptance.C(6, 50, 0, 2.4, 4  )' &
root -l -b -q 'getAcceptance.C(6, 50, 0, 2.4, 3.5)' &
root -l -b -q 'getAcceptance.C(0, 50, 0, 2.4, 4  )' &
root -l -b -q 'getAcceptance.C(0, 50, 0, 2.4, 3.5)' &
