#!/usr/bin/env python3
from __future__ import annotations
from __future__ import print_function

import os
import re
import sys
import json
import functools

def parse_json(file : str) -> dict:
    with open(file, "r") as f:
        return json.load(f)

def output_json(object : list, filename : str) -> None:
    with open(filename, 'w') as fd:
        json.dump(object, fd, indent=4)

def append_witness(object, witness) -> None:
    if not (type(object["witness"]) is list):
        object["witness"] = [object["witness"]]
    object["witness"].append(witness)

def main(argv : list[str]) -> int:
    if len(argv) < 1:
        print("Please provide a file to parse!", file=sys.stderr)
        return 1

    report_path = argv[0]
    jsons = list(map(parse_json, argv[1:]))
    final = []
    for r1 in jsons:
        append = True
        for r2 in final:
            if r1["line"] == r2["line"] and r1["bug_type"] == r2["bug_type"]:
                append_witness(r2, r1["witness"])
                append = False
        if append:
            final.append(r1)

    output_json(final, report_path)
    return 0

if __name__ == '__main__':
    argv = sys.argv[1:]
    sys.exit(main(argv))
