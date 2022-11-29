#!/usr/bin/python3
import os
import sys
import glob
import json
import common

def parse_coverage(f : str) -> float:
    report = common.parse_json(f)
    if len(report) == 0:
        return 0.0
    return max(list(map(lambda t: t["Coverage (accumulated)"], report)))

def main(argv=None) -> int:
    if argv is None:
        argv=sys.argv[1:]

    if len(argv) != 1:
        return 1

    base_dir = argv[0]
    results_path = os.path.join(base_dir, "**", "**", "results.json")
    coverage = {}
    for report in glob.glob(results_path):
        student = os.path.basename(os.path.dirname(report))
        project = os.path.basename(os.path.dirname(os.path.dirname(report)))
        if project not in coverage:
            coverage[project] = {}
        coverage[project][student] = parse_coverage(report)

    print(json.dumps(coverage, indent=4))
    return 0

if __name__ == "__main__":
    sys.exit(main())
