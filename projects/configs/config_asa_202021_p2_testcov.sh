#!/bin/bash

# C compiler
export CC=gcc
# Execution time limit
export TIMEOUT=30s
# Input directory
export TOOL=verifuzz
export TESTS_DIR=outputs/$TOOL/asa_2021_p2
# Student projects
export PROJS_DIR=alunos/asa_2021_p2
# Ouputs
export OUTS_DIR=outputs/$TOOL-testcov/asa_2021_p2
