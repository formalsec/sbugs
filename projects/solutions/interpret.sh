#!/bin/bash

function run_wasp() {
  e=$1
  i=$2

  OUTPUT=../outputs/testsuite/sym_calls/$e
  test -e $OUTPUT || mkdir -p $OUTPUT

  BASE=$(basename $i)
  test -e $OUTPUT/${BASE%.in}.out && return
  timeout 30s \
    wasp $e/wasp.wat -e '(invoke "__original_main")' \
      < $i \
      > $OUTPUT/${BASE%.in}.out
}

export -f run_wasp


EDITIONS="asa_1819_p1 asa_1819_p2 asa_1920_p1 asa_1920_p2 asa_2021_p2 asa_2122_p1 asa_2122_p2"
for e in $EDITIONS; do
  echo "Starting \"$e\""
  export INPUTS=$(ls ../inputs/$e/*.in)
  parallel -j 8 run_wasp $e ::: $INPUTS
done
