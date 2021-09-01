#!/bin/bash


#void getAcceptance(double ptLow = 0, double ptHigh=30, double yLow=0, double yHigh=2.4, double SiMuPtCut=4)
#root -l -b -q 'getAcceptance.C(0,  6, 0, 2.4, 4  )' &
#root -l -b -q 'getAcceptance.C(0,  6, 0, 2.4, 3.5)' &
#root -l -b -q 'getAcceptance.C(6, 50, 0, 2.4, 4  )' &
#root -l -b -q 'getAcceptance.C(6, 50, 0, 2.4, 3.5)' &
#root -l -b -q 'getAcceptance.C(0, 50, 0, 2.4, 4  )' &
#root -l -b -q 'getAcceptance.C(0, 50, 0, 2.4, 3.5)' &

#root -l -b -q 'getAcceptance.C(0 , 30, -2.4, 2.4, 3.5, true, 1, 1)' &
root -l -b -q 'getAcceptance.C(6 , 30, -2.4, 2.4, 3.5,true,1,1)' &
root -l -b -q 'getAcceptance.C(0 , 6 , -2.4, 2.4, 3.5,true,1,1)' &
root -l -b -q 'getAcceptance.C(0 , 4 , -2.4, 2.4, 3.5,true,1,1)' 
root -l -b -q 'getAcceptance.C(4 , 9 , -2.4, 2.4, 3.5,true,1,1)' &
root -l -b -q 'getAcceptance.C(9 , 12, -2.4, 2.4, 3.5,true,1,1)' &
root -l -b -q 'getAcceptance.C(9, 30, -2.4, 2.4, 3.5,true,1,1)' 

#root -l -b -q 'getAcceptance.C(0 , 30, -1.2, 1.2, 3.5,true,1,1)' 
#root -l -b -q 'getAcceptance.C(6 , 30, -1.2, 1.2, 3.5,true,1,1)' &
#root -l -b -q 'getAcceptance.C(0 , 6 , -1.2, 1.2, 3.5,true,1,1)' &
#root -l -b -q 'getAcceptance.C(0 , 4 , -1.2, 1.2, 3.5,true,1,1)' 
#root -l -b -q 'getAcceptance.C(4 , 9 , -1.2, 1.2, 3.5,true,1,1)' &
#root -l -b -q 'getAcceptance.C(9 , 12, -1.2, 1.2, 3.5,true,1,1)' &
#root -l -b -q 'getAcceptance.C(9, 30, -1.2, 1.2, 3.5,true,1,1)' &

root -l -b -q 'getAcceptance.C(0 , 30, -2.4, 2.4, 3.5,true,2,1)' &
root -l -b -q 'getAcceptance.C(6 , 30, -2.4, 2.4, 3.5,true,2,1)' &
root -l -b -q 'getAcceptance.C(0 , 6 , -2.4, 2.4, 3.5,true,2,1)' &
root -l -b -q 'getAcceptance.C(0 , 4 , -2.4, 2.4, 3.5,true,2,1)' 
root -l -b -q 'getAcceptance.C(4 , 9 , -2.4, 2.4, 3.5,true,2,1)' &
root -l -b -q 'getAcceptance.C(9 , 12, -2.4, 2.4, 3.5,true,2,1)' &
root -l -b -q 'getAcceptance.C(9, 30, -2.4, 2.4, 3.5,true,2,1)' 

#root -l -b -q 'getAcceptance.C(0 , 30, -1.2, 1.2, 3.5,true,2,1)' 
#root -l -b -q 'getAcceptance.C(6 , 30, -1.2, 1.2, 3.5,true,2,1)' &
#root -l -b -q 'getAcceptance.C(0 , 6 , -1.2, 1.2, 3.5,true,2,1)' &
#root -l -b -q 'getAcceptance.C(0 , 4 , -1.2, 1.2, 3.5,true,2,1)' 
#root -l -b -q 'getAcceptance.C(4 , 9 , -1.2, 1.2, 3.5,true,2,1)' &
#root -l -b -q 'getAcceptance.C(9 , 12, -1.2, 1.2, 3.5,true,2,1)' &
#root -l -b -q 'getAcceptance.C(9, 30, -1.2, 1.2, 3.5,true,2,1)' &

root -l -b -q 'getAcceptance.C(0 , 30, -2.4, 2.4, 3.5,true,3,1)' &
root -l -b -q 'getAcceptance.C(6 , 30, -2.4, 2.4, 3.5,true,3,1)' &
root -l -b -q 'getAcceptance.C(0 , 6 , -2.4, 2.4, 3.5,true,3,1)' &
root -l -b -q 'getAcceptance.C(0 , 4 , -2.4, 2.4, 3.5,true,3,1)' 
root -l -b -q 'getAcceptance.C(4 , 9 , -2.4, 2.4, 3.5,true,3,1)' &
root -l -b -q 'getAcceptance.C(9 , 12, -2.4, 2.4, 3.5,true,3,1)' &
root -l -b -q 'getAcceptance.C(9, 30, -2.4, 2.4, 3.5,true,3,1)' 

#root -l -b -q 'getAcceptance.C(0 , 30, -1.2, 1.2, 3.5,true,3,1)' 
#root -l -b -q 'getAcceptance.C(6 , 30, -1.2, 1.2, 3.5,true,3,1)' &
#root -l -b -q 'getAcceptance.C(0 , 6 , -1.2, 1.2, 3.5,true,3,1)' &
#root -l -b -q 'getAcceptance.C(0 , 4 , -1.2, 1.2, 3.5,true,3,1)' 
#root -l -b -q 'getAcceptance.C(4 , 9 , -1.2, 1.2, 3.5,true,3,1)' &
#root -l -b -q 'getAcceptance.C(9 , 12, -1.2, 1.2, 3.5,true,3,1)' &
#root -l -b -q 'getAcceptance.C(9, 30, -1.2, 1.2, 3.5,true,3,1)' &

