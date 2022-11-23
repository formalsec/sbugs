#!/usr/bin/env python3
import sys
import json
import functools

def merge(dict_1 : dict, dict_2 : dict) -> dict:
    dict_3 = {**dict_1, **dict_2}
    for key, val in dict_3.items():
        if key in dict_1 and key in dict_2:
            dict_3[key] += dict_1[key]
    return dict_3

def parse_json(file : str) -> dict:
    with open(file, 'r') as f:
        return json.load(f)

def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]

    output_file = argv[0]
    jsons = list(map(parse_json, argv[1:]))
    final = functools.reduce(merge, jsons, {})

    with open(output_file, 'w') as f:
        json.dump(final, f, indent=4)


if __name__ == '__main__':
    sys.exit(main())
