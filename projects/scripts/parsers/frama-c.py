#!/usr/bin/env python3
from __future__ import print_function
from __future__ import annotations

import os
import json

def read_file(filename : str) -> str:
    lines = []
    with open(filename, 'r') as f:
        lines = f.readlines()
    return lines

def output_json(object : list[dict], filename : str):
    with open(filename, 'w') as fd:
        json.dump(object, fd, indent=4)


def parse(file):

    lines = read_file(file)

    bugs = []
    idx = 0
    for line in lines:
        
        if '[eva:alarm]' in line:
            bug_line = line.split()[1].split(':')[1]
            filename = line.split()[1].split(':')[0].split('/')[-1]
            report = lines[idx+1].split('.')[0]

            bug = {
                'bug_type'  : report,
                'line'      : int(bug_line),
                'procedure' : 'unknown',
                'file'      : filename
            }
            bugs.append(bug)

        idx += 1
   
   
    if not bugs:
        return

    output_file = os.path.dirname(file) +'/report.json'
    output_json(bugs, output_file)

    return

if __name__ == '__main__':

    framaC = '/home/fmarques/sbugs/projects/outputs/framaC'
    projects = os.listdir(framaC)

    for p in projects:
        if os.path.isdir(f'{framaC}/{p}'):
            students = os.listdir(f'{framaC}/{p}')
            for s in students:
                report = f'{framaC}/{p}/{s}/output.txt'
                parse(report)
