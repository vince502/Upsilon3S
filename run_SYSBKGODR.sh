#!/bin/bash

step=$1
#root -l -b -q 'doConstraintFit_SYSBKGODR.cxx(1, '$step')'
#root -l -b -q 'doConstraintFit_SYSBKGODR.cxx(3, '$step')'
root -l -b -q 'doConstraintFit_SYSBKGODR.cxx(4, '$step')'
root -l -b -q 'doConstraintFit_SYSBKGODR.cxx(5, '$step')'
root -l -b -q 'doConstraintFit_SYSBKGODR.cxx(6, '$step')'
