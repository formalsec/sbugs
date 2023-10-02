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


def parse(file, project, bugs):

    lines = read_file(file)

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
            
            if cwe not in bugs[project].keys():
                bugs[project][cwe] = []
            bugs[project][cwe].append(bug)

        except IndexError:
            print(line)
            sys.exit()

    return

if __name__ == '__main__':

    bugs = {}
    path = '/../../outputs/static/flawfinder'
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
           
