#!/usr/bin/python3
import os
import sys

import common

def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]

    json = common.parse_json(argv[0])
    for prj, vulns in json.items():
        for _, bugs in vulns.items():
            for bug in bugs:
                file = bug["file"]
                n_file = os.path.join(
                    prj,
                    os.path.basename(os.path.dirname(file)),
                    os.path.basename(file)
                )
                bug["file"] = n_file
    common.output_json(json, argv[0])

    return 0

if __name__ == "__main__":
    sys.exit(main())
