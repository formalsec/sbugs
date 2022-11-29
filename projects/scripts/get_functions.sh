#!/bin/bash

PROJECTS="asa_1819_p1 asa_1819_p2 asa_1920_p1 asa_1920_p2 asa_2021_p1 asa_2021_p2 asa_2122_p1 asa_2122_p2 iaed_p1 iaed_p2"

for PROJ in $PROJECTS; do
  for i in $(find -type f -wholename "./$PROJ/*.c"); do
    test -e "$PROJ.functions" || \
      clang -Wno-everything -c -Xclang -ast-dump $i | grep "DeclRefExpr" | grep "Function" | awk -F\'  '{ print $4 }' >> "$PROJ.functions"
  done
done
