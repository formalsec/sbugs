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


def parse(file, project, bugs):

    lines = read_file(file)

    # find vulnerability summary
    bug_report = re.findall(
        '(?P<filename>[/\.\w-]+):(?P<lineno>\d+):\d+:\swarning:\s+(?P<bug_type>[\w\.\s]+):',
        lines
    )

    for b in bug_report:
        bug = {
            'bug_type'  : b[2],
            'line'      : int(b[1]),
            'procedure' : 'unknown',
            'file'      : b[0].split('/')[-1]
        }
    
        if b[2] not in bugs[project].keys():
            bugs[project][b[2]] = []
        bugs[project][b[2]].append(bug)
        
    return

if __name__ == '__main__':

    bugs = {}
    path = '/../../outputs/static/cppcheck'
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

