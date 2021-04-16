#!/bin/bash

ts=$1
root -l -b -q 'BDTClassifierApplication.C('$ts',0)'
root -l -b -q 'BDTClassifierApplication.C('$ts',1)'
root -l -b -q 'makeRooDataset_fromBDT.C('$ts',true, 0)'
root -l -b -q 'makeRooDataset_fromBDT.C('$ts',true, 1)'
echo $ts
