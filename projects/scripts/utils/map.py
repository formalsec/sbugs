#!/usr/bin/env python3
import sys
import json
import functools

def parse_json(file : str) -> dict:
    with open(file, 'r') as f:
        return json.load(f)

def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]

    a = parse_json(argv[0])
    b = parse_json(argv[1])

    for e, types in b.items():
        for t, vulns in types.items():
            for v1 in vulns:
                for v2 in a[e][t]:
                    if (v1["line"] == v2["line"]
                            and v1["file"] == v2["file"]):
                        v1["witness"] = v2["witness"]
    print(json.dumps(b, indent=4))


if __name__ == '__main__':
    sys.exit(main())
