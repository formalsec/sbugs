#!/usr/bin/env python3
from __future__ import annotations

import os
import sys
import yaml
import json
import common

def flatten_json(d : dict) -> list[str]:
    res = []
    for p, bug_types in d.items():
        for t, bugs in bug_types.items():
            for location in bugs:
                l = "{}:{}:{}:{}".format(
                    p,
                    t,
                    location["line"],
                    location["file"]
                )
                res.append(l)
    return res

def inflate_json(l : list) -> dict:
    result = {}
    for v in l:
        bug = v.split(":")
        project = bug[0]
        bug_type = bug[1]
        bug_line = bug[2]
        bug_file = bug[3]
        if project not in result:
            result[project] = {}
        if bug_type not in result[project]:
            result[project][bug_type] = []
        result[project][bug_type].append(
            dict(line=bug_line, file=bug_file)
        )
    return result

def main(argv : list[str]=None) -> int:
    if argv is None:
        argv = sys.argv[1:]

    if len(argv) < 3:
        print("Usage: json_set.py <op> <json_a> <json_b>")
        return 1

    op = argv[0]
    a = common.parse_json(argv[1])
    b = common.parse_json(argv[2])

    a_set = set(flatten_json(a))
    b_set = set(flatten_json(b))

    result = {}
    if "intersec" == op:
        result = inflate_json(list(a_set & b_set))
    elif "diff" == op:
        result = inflate_json(list(a_set - b_set))
    elif "union" == op:
        result = inflate_json(list(a_set.union(b_set)))
    else:
        return 1

    print(common.json_to_string(result))

    return 0

if __name__ == "__main__":
    sys.exit(main())
