#!/bin/bash

root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "3p5", 1, 180)'
root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "3p5", 2, 180)'
root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "4", 1, 180)'
root -l -b -q 'MassYieldFit.C(0, 50, -2.4, 2.4, "4", 2, 180)'
