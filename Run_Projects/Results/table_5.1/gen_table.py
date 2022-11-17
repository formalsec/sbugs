#!/usr/bin/python3
import os
import sys
import json
import latextable
import statistics

from texttable import Texttable

testsuites = {
    "CPAchecker" : 0,
    "FuSeBMC" : 0,
    "KLEE" : 0,
    "libkluzzer" : 0,
    "symbiotic" : 0,
    "verifuzz" : 0,
}

def get_row(tool : str) -> list:
    vulns_detected = 1
    testsuite_size = testsuites[tool]
    with open(os.path.join("..", tool + ".json"), "r") as fd:
        data = json.load(fd)
    vuln_lst = []
    for i in data.values():
        for bug_type, vulns in i.items():
            vuln_lst += list(map(lambda v: v["file"] + v["line"] + bug_type, vulns))
    vulns_detected = len(set(vuln_lst))
    return [vulns_detected, testsuite_size, (vulns_detected/testsuite_size)*100]

def fill_row(tool : str, row : int, table : list, times : list) -> None:
    table[row][0] = tool
    for i in range(len(times)):
        table[row][i + 1] = times[i]

def to_latex(table : list, col_size : int) -> None:
    table_str = Texttable()
    table_str.set_cols_align(["c"] + ["r"] * (col_size - 1))
    table_str.add_rows(table)
    return latextable.draw_latex(table_str)

def gen_efficiency_table(row_size : int, col_size : int):
    table = [[0 for _ in range(col_size)] for _ in range(row_size)]

    fill_row("libkluzzer", 0, table, get_row("libkluzzer"))
    fill_row("CPAchecker", 1, table, get_row("CPAchecker"))
    fill_row("symbiotic" , 2, table, get_row("symbiotic"))
    fill_row("FuSeBMC"   , 3, table, get_row("FuSeBMC"))
    fill_row("KLEE"      , 4, table, get_row("KLEE"))
    fill_row("verifuzz"  , 5, table, get_row("verifuzz"))

    table.insert(0, ["Tool", "Detected", "Test Suite", "Efficiency"])
    return table

def main(argv=None) -> int:
    if argv is None:
        argv=sys.argv[1:]

    with open("testsuites.json", "r") as fd:
        data = json.load(fd)
    for tool, count in data.items():
        testsuites[tool] = count

    efficiency = gen_efficiency_table(6, 4)
    with open("tbl5.1_efficiency.tex", "w") as fd:
        fd.write(to_latex(efficiency, 4))

    return 0

if __name__ == "__main__":
    sys.exit(main())
