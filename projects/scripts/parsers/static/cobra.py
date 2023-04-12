#!/usr/bin/env python3
from __future__ import print_function
from __future__ import annotations

import os
import json
import re
import sys


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
    report = None
    for line in lines:
        try:
            if line.startswith('==='):
                report = line.replace('===','')
                report = report.strip()
                continue

            if re.match('\d+:', line) and report:

                bug_line = line.split(':')[2].split('..')[0]
                filename = line.split(':')[1].split('/')[-1]

                bug = {
                    'bug_type'  : report,
                    'line'      : int(bug_line),
                    'procedure' : 'unknown',
                    'file'      : filename
                }
                bugs.append(bug)
        
        except IndexError:
            print(line)
            sys.exit()

    if not bugs:
        return

    output_file = os.path.dirname(file) +'/report.json'
    output_json(bugs, output_file)

    return

if __name__ == '__main__':

    #parse('/home/fmarques/sbugs/projects/outputs/cobra/asa_1819_p1/al001/report.txt')

    cobra = '/home/fmarques/sbugs/projects/outputs/cobra'
    projects = os.listdir(cobra)
    
    for p in projects:
        students = os.listdir(f'{cobra}/{p}')
        for s in students:
            report = f'{cobra}/{p}/{s}/report.txt'
            print(report)
            parse(report)
            
