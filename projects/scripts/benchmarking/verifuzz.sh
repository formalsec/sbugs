#!/bin/bash

export PROJ_ROOT=/home/fmarques/sbugs/projects/alunos

export OUTDIR_ROOT=${PROJ_ROOT}/../output/verifuzz

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

    output_dir=$OUTDIR_ROOT/$e/$p
    test -e $output_dir || mkdir -p $output_dir

    sources=$(ls "$project"/preprocessed/*.c)
    echo "Running $e/$p..."
    test -e $output_dir/report.txt && continue
    (! test -e "$project"/preprocessed/harness.c) && gcc -E $sources > "$project"/preprocessed/harness.c
    ulimit -m 4000000 -f 1048576
    (time \
      timeout 900 \
      ./scripts/verifuzz.py \
        --bit 64 \
        --testcomp \
        --testsuite $output_dir \
        --propertyFile ../FuSeBMC/properties/coverage-branches.prp \
        "$project"/preprocessed/harness.c \
        > $output_dir/report.txt 2>&1
    ) &> $output_dir/time.txt
  done
}

main() {
  test -e $OUTDIR_ROOT || mkdir -p $OUTDIR_ROOT
  parallel -j 1 benchmark_proj ::: $EDITIONS
}

export -f benchmark_proj

main $@
