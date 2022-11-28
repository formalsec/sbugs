#!/bin/bash

export KLEE_ROOT=/home/fmarques/klee
export PROJ_ROOT=/home/fmarques/sbugs/projects/alunos

export OUTDIR_ROOT=${PROJ_ROOT}/../outputs/klee

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

export MEMOU
export TIMEOUT=900

preprocess() {
  local src=$1
  local benchmark=$2
  local sources=$(ls $src/preprocessed/*.c)
  test -e $benchmark || $CC -E $sources > $benchmark
  return $?
}

benchmark_proj() {
  e=$1

  edition=${PROJ_ROOT}/$e
  for p in $(ls "$edition")
  do
    project=$edition/$p
    (test $p = "Makefile" || test $p = "symbolic") && continue

    output_dir=$OUTDIR_ROOT/$e/$p
    test -e $output_dir || mkdir -p $output_dir

    benchmark="$project/preprocessed/$p.c"
    preprocess $project $benchmark || continue

    echo "Running $e/$p..."
    test -e $output_dir/stdout.txt && continue
    ulimit -f 1048576
    (time \
      $KLEE_ROOT/bin/klee \
        --property-file=/home/fmarques/sbugs/projects/properties/coverage-branches.prp \
        --max-memory=4000000000 \
        --max-cputime-hard=900 \
        -32 \
        $benchmark > $output_dir/stdout.txt 2>&1
    ) &> $output_dir/time.txt
  done
}

main() {
  test -e $OUTDIR_ROOT || mkdir -p $OUTDIR_ROOT
  parallel -j 8 benchmark_proj ::: $EDITIONS
}

export -f benchmark_proj

main $@
