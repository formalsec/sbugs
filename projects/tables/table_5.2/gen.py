#!/usr/bin/python3
import os
import sys
import json
import latextable
import statistics

from texttable import Texttable

def get_coverage(tool : str) -> list:
    cov_file = os.path.join("results", f"{tool}-cov.json")
    with open(cov_file, "r") as fd:
        coverage = json.load(fd)
    cov_list = []
    for _, students in coverage.items():
        cov_list += list(map(lambda t: t[1], students.items()))
    return [
        min(cov_list),
        max(cov_list),
        round(statistics.mean(cov_list),3),
        round(statistics.stdev(cov_list),3),
        round(sum(cov_list), 3)
    ]

def fill_row(tool : str, row : int, table : list, times : list) -> None:
    table[row][0] = tool
    for i in range(len(times)):
        table[row][i + 1] = times[i]

def to_latex(table : list, col_size : int) -> None:
    table_str = Texttable()
    table_str.set_cols_align(["c"] + ["r"] * (col_size - 1))
    table_str.add_rows(table)
    return latextable.draw_latex(table_str)

def generate(col_size : int, row_size : int):
    table = [[ 0 for _ in range(col_size) ] for _ in range(row_size)]

    fill_row("libkluzzer", 0, table, get_coverage("libkluzzer"))
    fill_row("CPAchecker", 1, table, get_coverage("CPAchecker"))
    fill_row("symbiotic" , 2, table, get_coverage("symbiotic"))
    fill_row("FuSeBMC"   , 3, table, get_coverage("FuSeBMC"))
    table[4][0] = "KLEE"
    fill_row("verifuzz"  , 5, table, get_coverage("verifuzz"))

    table.insert(0, ["Tool", "Min", "Max", "Mean", "St. Dev", "Total"])
    return table

def main(argv=None) -> int:
    if argv is None:
        argv=sys.argv[1:]

    table5_total = generate(6, 6)
    output_file = os.path.join("tables", "tables_5.2", "tbl5.2_coverage.tex")
    with open(output_file, "w") as fd:
        fd.write(to_latex(table5_total, 6))
    return 0

if __name__ == "__main__":
    sys.exit(main())
