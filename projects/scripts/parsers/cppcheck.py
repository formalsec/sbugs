#!/usr/bin/env python3
from __future__ import print_function
from __future__ import annotations

import os
import re
import json

def read_file(filename : str) -> str:
    lines = []
    with open(filename, 'r') as f:
        lines = f.read()
    return lines

def output_json(object : list[dict], filename : str):
    with open(filename, 'w') as fd:
        json.dump(object, fd, indent=4)


def parse(file):

    lines = read_file(file)

    # find vulnerability summary
    bugs = re.findall(
        '(?P<filename>[/\.\w-]+):(?P<lineno>\d+):\d+:\swarning:\s+(?P<bug_type>[\w\.\s]+):',
        lines
    )

    if not bugs:
        return

    n_bugs = []
    for b in bugs:
        bug = {
            'bug_type'  : b[2],
            'line'      : int(b[1]),
            'procedure' : 'unknown',
            'file'      : b[0].split('/')[-1]
        }
        n_bugs.append(bug)

    output_file = file.split('.')[0] + '.json'
    print(output_file)
    output_json(n_bugs, output_file)

    return

if __name__ == '__main__':

    cppcheck = '/home/fmarques/sbugs/projects/outputs/cppcheck'
    projects = os.listdir(cppcheck)
    
    for p in projects:
        if os.path.isdir(f'{cppcheck}/{p}'):
            students = os.listdir(f'{cppcheck}/{p}')
            for s in students:
                report = f'{cppcheck}/{p}/{s}/report.txt'
                parse(report)
