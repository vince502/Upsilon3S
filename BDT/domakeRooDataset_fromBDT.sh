#!/bin/bash

#root -l -b -q 'makeRooDataset_fromBDT.C(long ts,bool isMC )'

if [ $2 -eq 0 ]
  then
  root -l -b -q 'makeRooDataset_fromBDT.C( '$1', false)'
fi

if [ $2 -eq 1 ]
  then 
  root -l -b -q 'makeRooDataset_fromBDT.C('$1', true)'
  fi
