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
    for line in lines[1:]:
        try:
            
            comma_split = line.split(',')
            filename = comma_split[0].split('/')[-1]
            bug_line = comma_split[1]
            cwe = re.search('(?P<cwe>CWE-\d+)', line)[0]

            bug = {
                'bug_type'  : cwe,
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

    #parse('/home/fmarques/sbugs/projects/outputs/flawfinder/asa_1819_p2/al060/report.txt')

    flawfinder = '/home/fmarques/sbugs/projects/outputs/flawfinder'
    projects = os.listdir(flawfinder)
    
    for p in projects:
        students = os.listdir(f'{flawfinder}/{p}')
        for s in students:
            report = f'{flawfinder}/{p}/{s}/report.txt'
            print(report)
            parse(report)
           
