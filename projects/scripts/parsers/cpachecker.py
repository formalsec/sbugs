#!/usr/bin/env python3
from __future__ import annotations
from __future__ import print_function

import os
import re
import sys
import json

def read_file(filename : str) -> list[str]:
    lines = []
    with open(filename, 'r') as f:
        lines = f.read()
    return lines

def output_json(object : list[dict], filename : str):
    with open(filename, 'w') as fd:
        json.dump(object, fd, indent=4)

def main(argv : list[str]) -> int:
    if len(argv) < 1:
        print('Please provide a file to parse!', file=sys.stderr)
        return -1

    file = argv[0]
    lines = read_file(file)

    # find vulnerability summary
    filename = re.search(
        'Parsing CFA from file\(s\) \"(?P<filename>[/\.\w_-]+)',
        lines
    )
    bug = re.search(
        'Verification result: (?P<result>\w+). \w+ \w+ \((?P<bug_type>[\w-]+): [\w\s]* line (?P<lineno>\d+)\)',#'(?P<filename>[/\.\w-]+):(?P<lineno>\d+):\d+:\swarning:.+\[(?P<bug_type>[\w\.]+)\]',
        lines
    )
    if not bug:
        return 0

    base = os.path.splitext(os.path.basename(file))[0]
    n_bug = {
        'bug_type'  : bug.group('bug_type'),
        'line'      : bug.group('lineno'),
        'procedure' : 'unknown',
        'file'      : filename.group('filename')
    }

    output_file = os.path.splitext(file)[0] + '.json'
    output_json([n_bug], output_file)

    return 0

if __name__ == '__main__':
    argv = sys.argv[1:]
    sys.exit(main(argv))
