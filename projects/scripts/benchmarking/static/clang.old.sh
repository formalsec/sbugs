#!/bin/bash

# Available config variables
export CC=clang
export PROJS_DIR=alunos
export OUTS_DIR=output/clang

# overwrites configuration variables
. ./config.sh

export PROJS=$(ls -d $PROJS_DIR/*)

function analyse_project() {
  local PRJ=$1
  local CWD=`pwd`

  SOURCES=$(find $PRJ -type f -name "*.c")
  test -z "$SOURCES" && return 1

  local OUTPUT=$CWD/$OUTS_DIR/$PRJ
  test -e $OUTPUT || mkdir -p $OUTPUT
  printf "Analysing $PRJ...\n"
  /usr/bin/time -o $OUTPUT/time.txt scan-build-14 -o $OUTPUT -enable-checker security.insecureAPI.strcpy $CC -c $SOURCES > $OUTPUT/report.txt 2>&1
  # cleanup
  for FILE in $SOURCES; do
    OBJECT="$(basename ${FILE%.c}.o)"
    test -e $OBJECT && rm $OBJECT
  done
  return 0
}

function main() {
  local jobs=$1
  # Set-up environment
  test -e $OUTPUT_DIR || mkdir -p $OUTPUT_DIR
  # Parallel run
  parallel -j $jobs analyse_project ::: $PROJS
}

export -f analyse_project
main $@
