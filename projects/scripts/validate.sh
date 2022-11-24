#!/bin/bash

JOBS=10
CONF=testcov
SCRIPT=scripts/val_testsuite.sh
TOOLS=CPAchecker

for t in $TOOLS; do
  for c in $(ls configs/*$CONF.sh); do
    sed -i "s/TOOL=[a-zA-Z]*/TOOL=$t/g" $c
    ln -sf $c config.sh
    ./$SCRIPT $JOBS
  done
done
