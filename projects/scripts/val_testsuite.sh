#!/bin/bash

# Available config variables
export CC=gcc
export TIMEOUT=30s
export TESTS_DIR=test-suite
export PROJS_DIR=alunos
export OUTS_DIR=output

# overwrites configuration variables
. ./config.sh

export PROJS=$(ls -d $PROJS_DIR/*)

function gen_testsuite() {
  local proj=$1
  local testsuite=$2

  local xmls=$(find $TESTS_DIR/$proj/test-suite -type f -name "*.xml" )
  test -z "$xmls" && return 1

  printf "Found test-suite! Compressing to $testsuite...\n"
  zip $testsuite $xmls 2>&1 > /dev/null
  return 0
}

function preprocess() {
  local src=$1
  local harness=$2
  local sources=$(ls $src/preprocessed/*.c)
  test -e $harness || $CC -E $sources > $harness
  return $?
}

function validate_testsuite() {
  local testsuite=$1
  local harness=$2
  local output_dir=$3

  /home/fmarques/test-suite-validator/bin/testcov \
    --memlimit 6GB \
    --timelimit-per-run 3 \
    --no-plots \
    --reduction BY_ORDER \
    --reduction-output test-suite \
    --test-suite $testsuite \
    --output $output_dir \
    --goal properties/coverage-branches.prp \
    $harness

  return 0
}

function validate() {
  local proj_path=$1

  local proj=$(basename $proj_path)
  (test $proj = "symbolic" || test $proj = "Makefile") && return 1

  printf "$TESTS_DIR/$proj\n"
  test -d "$TESTS_DIR/$proj" || return 1

  local testsuite="$TESTS_DIR/$proj/test-suite.zip"
  gen_testsuite $proj $testsuite || return 1

  printf "Preprocessing $proj_path sources...\n"
  local harness="$proj_path/preprocessed/$proj.c"
  preprocess $proj_path $harness || return 1

  printf "validating $testsuite...\n"
  local output_dir="$OUTS_DIR/$proj"
  validate_testsuite $testsuite $harness $output_dir
}

function main() {
  local jobs=1
  # Set-up environment
  test -e $OUTS_DIR || mkdir -p $OUTS_DIR
  # Parallel run
  parallel -j $jobs validate ::: $PROJS
}

export -f validate validate_testsuite preprocess gen_testsuite
main $@
