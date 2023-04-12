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


def clean_report(report):
    patterns = ['\'.*\'{0,1}', r'\(.*\){0,1}']
    for p in patterns:
        report = re.sub(p, '', report)
    return report.strip()


def parse(file):

    lines = read_file(file)

    bugs = []
    for line in lines:
        try:
            if line.startswith('uno: /home'):

                filename = line.split(':')[1].split('/')[-1]
                bug_line = line.split(':')[2].strip()
                report = line.split(':')[3].split(',')[1]
                report = clean_report(report)

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

    #parse('/home/fmarques/sbugs/projects/outputs/uno/iaed_p1/241/report.txt')

    uno = '/home/fmarques/sbugs/projects/outputs/uno'
    projects = os.listdir(uno)
    
    for p in projects:
        students = os.listdir(f'{uno}/{p}')
        for s in students:
            report = f'{uno}/{p}/{s}/report.txt'
            print(report)
            parse(report)
           
