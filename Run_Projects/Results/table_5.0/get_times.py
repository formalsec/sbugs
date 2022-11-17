#!/usr/bin/python3
import re
import os
import sys
import glob
import json

SH_REGEX=r"(?P<min>\d+):(?P<sec>\d+)\.(?P<msec>\d+)"
BASH_REGEX=r"real\s+(?P<min>\d+)m(?P<sec>\d+).(?P<msec>\d+)"

def parse_time(t : str) -> float:
    with open(t, "r") as fd:
        data = fd.read()
    match = re.search(BASH_REGEX, data)
    if match:
        return (
            float(match.group('min')) * 60
            + float(match.group('sec'))
            + (float(match.group('msec')) / 100.0)
        )
    return 0.0

def main(argv=None) -> int:
    if argv is None:
        argv=sys.argv[1:]

    if len(argv) != 1:
        return 1

    base_dir = argv[0]
    time_path = os.path.join(base_dir, "**", "**", "time.txt")
    times = {}
    for time in glob.glob(time_path):
        student = os.path.basename(os.path.dirname(time))
        project = os.path.basename(os.path.dirname(os.path.dirname(time)))
        if project not in times:
            times[project] = {}
        t = parse_time(time)
        times[project][student] = round(t, 2)

    print(json.dumps(times, indent=4))
    return 0

if __name__ == "__main__":
    sys.exit(main())
