#!/bin/bash

dataset="../../results/dataset-gt1-extended.json"

tool_files=("FuSeBMC.json" "libkluzzer.json" "verifuzz.json" "clang.json" "infer.json" "pulse.json" "CPAchecker.json" "KLEE.json" "symbiotic.json")
fuzzers=("FuSeBMC.json" "verifuzz.json" "libkluzzer.json")
symbolics=("CPAchecker.json" "KLEE.json" "symbiotic.json")

test -e false-negatives || mkdir false-negatives
# False Negatives Fuzzers
for i in ${!fuzzers[@]}; do
  fuzzer=${fuzzers[$i]}
  ../../scripts/utils/json_set.py diff \
    ../../results/dataset-gt1-extended.json \
    ../../results/$fuzzer > false-negatives/$fuzzer
done
# False Negatives Fuzzers
for i in ${!symbolics[@]}; do
  symbolic=${symbolics[$i]}
  ../../scripts/utils/json_set.py diff \
    ../../results/dataset-gt1-extended.json \
    ../../results/$symbolic> false-negatives/$symbolic
done
# Fuzzer unions
test -e unions || mkdir unions
../../scripts/utils/json_set.py union \
  ../../results/FuSeBMC.json \
  ../../results/verifuzz.json > unions/FuSe-veri.json
../../scripts/utils/json_set.py union \
  unions/FuSe-veri.json \
  ../../results/libkluzzer.json > unions/fuzzer.json
# Fuzzers False Negativs
../../scripts/utils/json_set.py diff \
  ../../results/dataset-gt1-extended.json \
  unions/fuzzer.json > fuzzer-fn.json
# Symbolic Union
../../scripts/utils/json_set.py union \
  ../../results/CPAchecker.json \
  ../../results/KLEE.json > unions/CPA-KLEE.json
../../scripts/utils/json_set.py union \
  unions/CPA-KLEE.json \
  ../../results/symbiotic.json > unions/symbolic.json
# Symbolic False Negativs
../../scripts/utils/json_set.py diff \
  ../../results/dataset-gt1-extended.json \
  unions/symbolic.json > sym-fn.json
# Total Fns
../../scripts/utils/json_set.py diff \
  ../../results/dataset-gt1-extended.json \
  ../../results/dataset-gt0.json > total-fn.json
