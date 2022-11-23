#!/bin/bash

TOOL=
SCRIPT=scripts/val_random.sh

for conf in $(ls configs/*$TOOL.sh); do
  ln -sf $conf config.sh
  ./$SCRIPT 10
done
