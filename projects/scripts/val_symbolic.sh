#!/bin/bash

# Available config variables
export CC=gcc
export TIMEOUT=30s
export TESTS_DIR=inputs
export PROJS_DIR=alunos
export OUTPUT_DIR=output

# overwrites configuration variables
. ./config.sh

export PROJS=$(ls -d $PROJS_DIR/*)

function compile() {
  local src=$1
  local bin=$2
  sources=$(ls $src/*.c)
  test -e $bin || \
    $CC -O1 -g -fsanitize=address -fno-omit-frame-pointer $sources -o $bin \
    > /dev/null 2>&1
  return $?
}

function run_test() {
  local bin=$1
  local t=$2

  local dir=$(basename $(dirname $bin))
  local out_dir=$OUTS_DIR/$dir
  test -e $out_dir || mkdir -p $out_dir

  local name=$(basename $t)
  ulimit -f 1024
  timeout $TIMEOUT $bin < $t > /dev/null 2> $out_dir/${name%.in}.err
  return $?
}

function benchmark_proj() {
  local prj=$1

  (test $(basename $prj) = "symbolic") && return 1

  test -d "$TESTS_DIR/$(basename $prj)" || return 1
  local TESTS=$(find $TESTS_DIR/$(basename $prj)/ -type f -name "*.scanf")

  local bin=$prj/run
  printf "Compiling $bin...\n"
  compile $prj $bin || return 1

  printf "Running inputs for $bin...\n"
  for t in $TESTS; do run_test $bin $t; done && return 0
}

function main() {
  local jobs=$1
  # Set-up environment
  test -e $OUTS_DIR || mkdir -p $OUTS_DIR
  # Parallel run
  parallel -j $jobs benchmark_proj ::: $PROJS
}

export -f benchmark_proj compile run_test
main $@
