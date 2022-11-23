#!/bin/bash

export PARSER=scripts/parsers/asan.py

parse_reports() {
  local REPORTS=$1  
  test -z "$REPORTS" && return 1

  for REPORT in $REPORTS; do
    ./$PARSER $REPORT
  done

  return 0
}

concat_jsons() {
  local OUTPUT=$1
  local REPORTS=$2
  test -z "$REPORTS" && return 1

  ./scripts/utils/concat.py $OUTPUT $REPORTS
  return $?
}

generate_report() {
  TOOL=$1
  OUTPUT_ROOT=$2
  EDITION=$3
  PROJECT=$4

  PROJ_PATH="$OUTPUT_ROOT/$EDITION/$PROJECT"

  printf "[$EDITION/$PROJECT] Parsing reports...\n"
  TOOL_REPORTS=$(find $PROJ_PATH -type f -name "*.err")
  test -z "$TOOL_REPORTS" && TOOL_REPORTS=$(find $PROJ_PATH -type f -name "report.txt")
  parse_reports "$TOOL_REPORTS" || return 0

  printf "[$EDITION/$PROJECT] Generating project report...\n"
  REPORT_PATH="$PROJ_PATH/report.json"
  test -e "$REPORT_PATH" && return 0

  JSON_REPORTS=$(find $PROJ_PATH -type f -name "*.json")
  concat_jsons "$REPORT_PATH" "$JSON_REPORTS"

  printf "[$EDITION/$PROJECT] Done.\n"
  return 0
}

# Main loop
main() {
  TOOL=$1
  JOBS=$2
  test -z $TOOL && (printf "[ERROR] No tool provided!\n" \
                    && return 1)
  test -z $JOBS && JOBS=4

  OUTPUT_ROOT="outputs/$TOOL-asan"
  test -e $OUTPUT_ROOT \
    || (printf "[ERROR] \"$OUTPUT_ROOT\" not found!\n" \
    && return 1)

  for EDITION in $(ls $OUTPUT_ROOT); do

    printf "[$EDITION] Building project reports...\n"
    PROJECTS=$(ls $OUTPUT_ROOT/$EDITION)
    parallel -j $JOBS generate_report $TOOL $OUTPUT_ROOT $EDITION ::: $PROJECTS

    printf "[$EDITION] Generating vulnerability statistics...\n"
    PROJECT_REPORTS=$(find "$OUTPUT_ROOT/$EDITION/" -type f -name "report.json")
    ./scripts/utils/aggregate.py "results/$TOOL.json" $EDITION $PROJECT_REPORTS

  done

  (test -e "outputs/$TOOL" \
    && ./scripts/utils/times.py "outputs/$TOOL" > "results/$TOOL-times.json") \
    || print "[ERROR] \"outputs/$TOOL\" not found!\n"
}

export -f main generate_report parse_reports concat_jsons

main $@
