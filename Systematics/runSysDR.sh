#!/bin/bash

root -l -b -q BDTVariDRUnc.cxx
root -l -b -q SigParVariDRUnc.cxx
root -l -b -q SigPdfVariDRUnc.cxx
root -l -b -q BkgVariDRUnc.cxx
#root -l -b -q TNPUnc.cxx
#root -l -b -q DPTVariUnc.cxx
root -l -b -q CENTVariDRUnc.cxx
#root -l -b -q ACCVariUnc.cxx
root -l -b -q systematic_ups_DR.cxx
