#!/usr/bin/env python3
from __future__ import annotations
from __future__ import print_function

import os
import sys
import yaml
import json
import pathlib

from collections import OrderedDict

script = pathlib.Path(__file__).resolve()
module_dir = script.parent.parent.absolute()

sys.path.insert(0, str(module_dir))

from scripts import utils

def get_key(type : str, map : dict) -> str:
    for key, data in map.items():
        if type == key or type in (data if data else []):
            return key
    return type

def main(argv : list[str]) -> int:
    if len(argv) < 3:
        print("Usage: compress.py <json_file> <map_file> <output_file>")
        return 1

    if not os.path.exists(argv[0]):
        return 1

    json_file = utils.parse_json(argv[0])
    vuln_file = utils.parse_yaml(argv[1])
    output_file = argv[2]

    # Compress new dict with generic keys from vuln_file
    n_json = OrderedDict()
    for key, data in json_file.items():
        n_key = get_key(key, vuln_file)
        if not (n_key in n_json):
            n_json[n_key] = 0
        n_json[n_key] += data

    utils.output_json(n_json, output_file)
    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
