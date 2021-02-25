#!/bin/bash


if [ $# -ne 12 ]
  then 

  echo "unmatching variable numbers, setting default"
  pl="0.0"; ph="30.0"; yl="0.0"; yh="2.4"; cl="0"; ch="180"; tnp="false"; wei="false"; sw="false"; ktrig="kTrigUps"; ts="1613554344"; bdt_ts="0.2";
fi
if [ $# -eq 2 ]
  then
  ts=$1; bdt_ts=$2
  echo "using timestamp $1, bdt threshold $2"
fi

if [ $# -eq 12 ]
  then
  pl=$1; ph=$2; yl=$3; yh=$4; cl=$5; ch=$6; tnp=$7; wei=$8; sw=$9; ktrig=$10; ts=$11; bdt_ts=$12;
fi


root -l -b -q '../../Efficiency/getEfficiencyBDT.C('$pl', '$ph' , '$yl', '$yh', '$cl','$ch','$tnp', '$wei', '$ts','$bdt_ts')'
root -l -b -q '../../Efficiency/getEfficiency.C('$pl', '$ph' , '$yl', '$yh', '$cl','$ch','$tnp','$wei', '$sw','$ktrig')'

root -l -b -q 'openEffhist.C('$pl', '$ph','$yl','$yh','$cl','$ch','$tnp','$sw','$sw','$ktrig','$ts','$bdt_ts')'

