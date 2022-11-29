#!/bin/bash

JOBS=10
CONF=testcov
SCRIPT=scripts/val_testsuite.sh
TOOLS=verifuzz

# Allow passwordless commits
eval $(ssh-agent)
ssh-add ~/.ssh/github

for t in $TOOLS; do
  for c in $(ls configs/*$CONF.sh); do
    sed -i "s/TOOL=[a-zA-Z]*/TOOL=$t/g" $c
    ln -sf $c config.sh
    ./$SCRIPT $JOBS
  done
  cd outputs/$t-testcov \
    && zip -r $t-testcov.zip * \
    && mv $t-testcov.zip .. \
    && find -type d -name "test-suite" | xargs rm -rf \
    && find -type f -name "a.out" | xargs rm \
    && find -type f -name "*.log" | xargs rm \
    && find -type f -name "harness.c" | xargs rm \
    && git add . \
    && git commit -m "$t-cov" \
    && git push
  cd ../..
done

# generate coverage reports
for c in $(ls -d outputs/*testcov); do
  output_file="$(basename $c).json"
  ./scripts/utils/coverage.py $c > results/$output_file
done

# generate tables
./tables/table_5.2/gen.py
