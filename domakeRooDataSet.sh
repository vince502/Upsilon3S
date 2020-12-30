#!/bin/bash
setroot
root -l -b -q 'makeRooDataSet.C(true, false, false, 1, "L1DoubleMuOpen50100")'
root -l -b -q 'makeRooDataSet.C(true, false, false, 1, "Ups")'
