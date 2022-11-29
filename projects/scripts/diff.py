#!/usr/bin/python3
import sys

def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]
    libc = argv[0]
    project = argv[1]

    with open(libc, "r") as f1, open(project, "r") as f2:
        libc_functions = f1.readlines()
        project_functions = f2.readlines()

    print(len(list(filter(lambda f : f in libc_functions, project_functions))))


    return 0

if __name__ == "__main__":
    sys.exit(main())
