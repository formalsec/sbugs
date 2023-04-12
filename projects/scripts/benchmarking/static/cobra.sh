#!/bin/bash

# Available config variables
export CC=clang
export PROJS_DIR=../../../alunos
export OUTS_DIR=../../../outputs/static/cobra


function analyse_project() {
  local PRJ=$1
  local CWD=`pwd`

  SOURCES=$(find $PRJ -type f -name "*.c")
  test -z "$SOURCES" && return 1

  local TARGET=$(echo $PRJ | cut -f 5,6 -d "/" )
  local OUTPUT=$OUTS_DIR/$TARGET

  printf "Analysing $TARGET...\n"

  test -e $OUTPUT || mkdir -p $OUTPUT

  /usr/bin/time -o $OUTPUT/time.txt cobra -f cwe.cobra $PRJ/*.c > /dev/null 2>&1; cat *_.txt >> $OUTPUT/report.txt 2>&1; rm -f _*.txt
  # cleanup
  for FILE in $SOURCES; do
    OBJECT="$(basename ${FILE%.c}.o)"
    test -e $OBJECT && rm $OBJECT
  done
  return 0
}

function main() {

  for PROJ in $(ls -d $PROJS_DIR/* | grep _); do
    
    #printf "Analysing $PROJ...\n"
    
    local PROJS=$(ls -d $PROJ/* | grep -v symbolic)
    local jobs=$1
    # Set-up environment
    test -e $OUTS_DIR || mkdir -p $OUTS_DIR

    # Parallel run
    parallel -j $jobs analyse_project ::: $PROJS

  done
}

#MUST BE RUN SINGLE THREADED
export -f analyse_project
main 1
