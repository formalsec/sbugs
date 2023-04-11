from __future__ import annotations

import os
import sys
import glob
import argparse

from facts import _info
from facts import utils

def get_parser():
    parser = argparse.ArgumentParser(
        prog=_info.__NAME__,
        formatter_class=argparse.ArgumentDefaultsHelpFormatter
    )

    parser.add_argument(
        "--version",
        "-v",
        action="version",
        version=_info.__VERSION__
    )

    parser.add_argument(
        "--jobs",
        "-j",
        dest="jobs",
        action="store",
        type=int,
        default=1
    )

    parser.add_argument("benchmarks")

    return parser

def parse(argv):
    parser = get_parser()
    args = parser.parse_args(argv)
    return args

def main(argv=None) -> int:
    if argv is None:
        argv = sys.argv[1:]

    args = parse(argv)

    with open(args.benchmarks, "r") as fd:
        benchmarks = fd.readlines()

    for projects in benchmarks:
        configs = glob.glob(projects.strip())
        for config in configs:
            conf = utils.read_yaml(config)

    return 0
