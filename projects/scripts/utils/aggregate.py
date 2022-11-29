#!/usr/bin/env python3
from __future__ import annotations
from __future__ import print_function

import os
import sys
import json
import itertools

import common

def main(argv : list[str]) -> int:
    if len(argv) < 2:
        return 1

    report_path = argv[0]
    project = argv[1]
    jsons = list(itertools.chain.from_iterable(map(common.parse_json, argv[2:])))

    bugs = {}
    if os.path.exists(report_path):
        bugs = common.parse_json(report_path)

    aux = {}
    for bug in jsons:
        bug_type = bug["bug_type"]
        if not (bug_type in aux):
            aux[bug_type] = []
        aux[bug_type].append(bug)

    bugs[project] = aux

    common.output_json(bugs, report_path)

    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
