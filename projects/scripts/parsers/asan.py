#!/usr/bin/env python3
from __future__ import annotations
from __future__ import print_function

import os
import re
import sys
import json

def read_file(filename : str) -> str:
    lines = []
    with open(filename, 'r') as f:
        lines = f.read()
    return lines

def output_json(object : dict, filename : str):
    with open(filename, 'w') as fd:
        json.dump(object, fd, indent=4)

def main(argv : list[str]) -> int:
    if len(argv) < 1:
        print('Please provide a file to parse!', file=sys.stderr)
        return 1

    file = argv[0]
    lines = read_file(file)

    # find vulnerability summary
    memory_error = "SUMMARY: \w+: (?P<bug_type>[\w-]+) (?P<filename>[/\.\w-]+):(?P<lineno>\d+) \w+ (?P<function>[\w-]+)"
    memory_leaks = "#1 \w+ in (?P<function>[\w-]+) (?P<filename>[/\.\w-]+):(?P<lineno>\d+)"

    bug_type = ""
    m = re.search(memory_error, lines)
    if m:
        bug_type = m.group('bug_type')
    elif re.search("detected memory leaks", lines):
        m = re.search(memory_leaks, lines)
        if not m:
            return 1
        bug_type = 'memory-leak'
    else:
        return 1

    basename = os.path.basename(m.group('filename'))
    dirname = os.path.join(
        os.path.basename(os.path.dirname(os.path.dirname(file))),
        os.path.basename(os.path.dirname(file))
    )

    base = os.path.splitext(os.path.basename(file))[0]
    bug = {
            'bug_type'  : bug_type,
            'line'      : m.group('lineno'),
            'procedure' : m.group('function'),
            'file'      : os.path.join(dirname, basename),
            'witness'   : base + '.in'
        }

    output_file = os.path.splitext(file)[0] + '.json'
    output_json(bug, output_file)

    return 0

if __name__ == '__main__':
    argv = sys.argv[1:]
    sys.exit(main(argv))
