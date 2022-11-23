#!/usr/bin/env python3
from __future__ import annotations
from __future__ import print_function

import os
import sys
import json
import itertools

import common

from collections import OrderedDict

def main(argv : list[str]) -> int:
    if len(argv) < 3:
        return 1

    report_path = argv[0]
    dataset_vulns = argv[1]
    project = argv[2]

    dataset = common.parse_json(dataset_vulns)
    if project not in dataset:
        return 1

    bugs = OrderedDict()
    for bug_type, vulns in dataset[project].items():
        bugs[bug_type] = len(vulns)

    common.output_json(bugs, report_path)

    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
