#!/bin/bash

run="ConstraintFit_VALI.cxx(1314, 8000000004, 3,0.0 )"
dir=/home/vince402/Upsilon3S
outfile=$run_`date`
subfile=subfile_$outfile
root=`which root`

cat > $subfile << EOF
Executable   = $root
Arguments    = $dir/$2 $3 $4 $5 $6 $7 $8 $9

Initialdir   = $dir
Log          = $outfile.log
Error        = $outfile.err
Output       = $outfile.out
#Input        = WHEN_YOU_HAVE_INPUT_FILES

Universe     = vanilla
GetEnv       = True
Request_cpus = 1
Notification = Always
Requirements = machine == "kunpl17"
#Notify_user  = CHANGE_THIS_TO_YOUR_EMAIL

Queue
EOF


condor_submit $subfile
rm $subfile

