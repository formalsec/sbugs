#!/bin/bash

# Available config variables
export CC=clang
export PROJS_DIR=alunos
export OUTPUT_DIR=output-infer

# overwrites configuration variables
. ./config.sh

export PROJS=$(find $PROJS_DIR -type d)

function analyse_project() {
  local prj=$1
  local cwd=`pwd`

  sources=$(find $prj -type f -name "*.c")
  [ -z $sources ]  && return

  local output=$cwd/$OUTPUT_DIR/$prj
  local output_t=$cwd/output-times/$prj
  test -e $output_t || mkdir -p $output_t
  printf "Analysing $prj...\n"
  /usr/bin/time -o $output_t/time.txt infer run -o $output -- $CC -c $sources

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
