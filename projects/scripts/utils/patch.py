#!/usr/bin/env python3
from __future__ import annotations

import re
import os
import sys
from difflib import SequenceMatcher

import utils

def diff(str1 : str, str2 : str) -> float:
    return SequenceMatcher(None, str1, str2).ratio()

def patch(v : dict) -> int:
    lineno = int(v["line"])
    filename = v["file"]

    if not ("preprocessed" in filename):
        return 1

    with open(filename, "r") as fd:
        line = str(lineno) + ":" + fd.readlines()[lineno - 1].strip()

    original = os.path.join(os.path.dirname(filename), "..",
                            os.path.basename(filename))
    with open(original, "r") as fd:
        lines = fd.readlines()

    lines = list(map(lambda p: str(p[0] + 1) + ":" + p[1], enumerate(lines)))

    diffs = list(map(lambda l : diff(l, line), lines))
    max_element = max(diffs)
    v["n_line"] = diffs.index(max_element) + 1

    return 0

def main(argv : list[str]=None) -> int:
    if argv is None:
        argv = sys.argv[1:]

    bad, good = 0, 0
    d = utils.parse_json(argv[0])
    for k, vs in d.items():
        for v in vs:
            patch(v)

    return 0

if __name__ == "__main__":
    sys.exit(main())
