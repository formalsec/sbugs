#!/bin/bash

export PROJ_ROOT=/home/fmarques/sbugs/projects/alunos

export OUTDIR_ROOT=${PROJ_ROOT}/../output/FuSeBMC

export EDITIONS="asa_1819_p1 
          asa_1819_p2 
          asa_1920_p1 
          asa_1920_p2 
          asa_2021_p1 
          asa_2021_p2 
          asa_2122_p1 
          asa_2122_p2 
          iaed_p1 
          iaed_p2"

export MEMOUT=1
export TIMEOUT=900

benchmark_proj() {
  e=$1

  edition=${PROJ_ROOT}/$e
  for p in $(ls "$edition")
  do
    project=$edition/$p
    (! test -d $project || test $p = "symbolic") && continue

    OUTPUT_DIR=$OUTDIR_ROOT/$e/$p
    test -e $OUTPUT_DIR || mkdir -p $OUTPUT_DIR

    SOURCES="$project"/preprocessed/harness.c
    echo "Running $e/$p..."
    test -e $OUTPUT_DIR/report.txt && continue
    ulimit -m 4000000
    (time timeout 890 ./fusebmc.py -a 64 -p properties/coverage-branches.prp -o "$OUTPUT_DIR" -s incr "$SOURCES" > $OUTPUT_DIR/report.txt 2>&1) &> $OUTPUT_DIR/time.txt
  done
}

main() {
  test -e $OUTDIR_ROOT || mkdir -p $OUTDIR_ROOT
  parallel -j 10 benchmark_proj ::: $EDITIONS
}

export -f benchmark_proj

main $@
