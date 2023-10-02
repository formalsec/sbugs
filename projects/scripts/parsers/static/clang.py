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


def parse(file, project, bugs):


    lines = read_file(file)

    # find vulnerability summary
    bugs = re.findall(
        '(?P<filename>[/\.\w-]+):(?P<lineno>\d+):\d+:\swarning:.+\[(?P<bug_type>[\w\.]+)\]',
        lines
    )
    if not bugs:
        return 0

    base = os.path.splitext(os.path.basename(file))[0]
    for b in bugs:
        bug = {
            'bug_type'  : b[2],
            'line'      : b[1],
            'procedure' : 'unknown',
            'file'      : b[0]
        }

        if report not in bugs[project].keys():
            bugs[project][report] = []
        bugs[project][report].append(bug)

    return

if __name__ == '__main__':

    bugs = {}
    path = '/../../outputs/static/clang'
    projects = os.listdir(path)
    projects = filter(lambda x: os.path.isdir(f'{path}/{x}'), projects)
    
    for p in projects:

        bugs[p] = {}   
        students = os.listdir(f'{path}/{p}')
        
        for s in students:
            report = f'{path}/{p}/{s}/report.txt'
            print(report)
            parse(report, p, bugs)

        if len(bugs[p].keys()) == 0:
            del bugs[p]
    
    output_file = f'{path}/report.json'
    output_json(bugs, output_file)