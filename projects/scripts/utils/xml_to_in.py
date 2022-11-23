#!/usr/bin/env python3
import sys
import xml.etree.ElementTree as ET

def repair_file(file):
    with open(file, 'r') as fd:
        lines = fd.readlines()
    if len(lines) < 1:
        return False
    lines[-1] = '</testcase>'
    with open(file, 'w') as fd:
        fd.writelines(lines)
    try:
        ET.parse(file).getroot()
        return True
    except:
        return False

def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]

    if len(argv) != 2:
        return 1

    input_file = argv[0]
    output_file = argv[1]

    try:
        root = ET.parse(input_file).getroot()
    except ET.ParseError:
        if not repair_file(input_file):
            return 1
        root = ET.parse(input_file).getroot()

    if root.tag != 'testcase':
        return 1

    with open(output_file, 'w') as f:
        for inpt in root.iter('input'):
            f.write(inpt.text + '\n')
        f.close()

    return 0

if __name__ == '__main__':
    sys.exit(main())
