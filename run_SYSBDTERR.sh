#!/bin/bash

step=$1
root -l -b -q 'doConstraintFit_SYSBDTERR.cxx(-1, '$step')'
root -l -b -q 'doConstraintFit_SYSBDTERR.cxx( 1, '$step')'
