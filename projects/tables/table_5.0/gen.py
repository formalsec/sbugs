#!/usr/bin/python3
import os
import sys
import json
import latextable
import statistics

from texttable import Texttable

def get_times_total(tool : str) -> list:
    with open(f"{tool}-times.json", "r") as fd:
        times = json.load(fd)
    time_list = []
    for _, students in times.items():
        time_list += list(map(lambda t: t[1], students.items()))
    time_list = list(filter(lambda t: t != 0.0, time_list))
    return [
        min(time_list),
        max(time_list),
        round(statistics.mean(time_list),2),
        round(statistics.stdev(time_list),2),
        round(sum(time_list), 2)
    ]

proj_map = {
    "iaed_p1" : 0,
    "iaed_p2" : 1,
    "asa_1819_p1" : 2,
    "asa_1819_p2" : 3,
    "asa_1920_p1" : 4,
    "asa_1920_p2" : 5,
    "asa_2021_p1" : 6,
    "asa_2021_p2" : 7,
    "asa_2122_p1" : 8,
    "asa_2122_p2" : 9
}

def get_times_project(tool : str, col_size : int) -> dict:
    with open(f"{tool}-times.json", "r") as fd:
        times = json.load(fd)
    time_list = [0 for _ in range(col_size)]
    for proj, students in times.items():
        proj_total = sum(map(lambda t : t[1], students.items()))
        time_list[proj_map[proj]] = proj_total
    time_list[-1] = sum(time_list[:-1])
    return time_list

def fill_row(tool : str, row : int, table : list, times : list) -> None:
    table[row][0] = tool
    for i in range(len(times)):
        table[row][i + 1] = times[i]

def to_latex(table : list, col_size : int) -> None:
    table_str = Texttable()
    table_str.set_cols_align(["c"] + ["r"] * (col_size - 1))
    table_str.add_rows(table)
    return latextable.draw_latex(table_str)


def gen_total(col_size : int, row_size : int):
    table = [[ 0 for _ in range(col_size) ] for _ in range(row_size)]

    fill_row("libkluzzer", 0, table, get_times_total("libkluzzer"))
    fill_row("CPAchecker", 1, table, get_times_total("CPAchecker"))
    fill_row("symbiotic" , 2, table, get_times_total("symbiotic"))
    fill_row("FuSeBMC"   , 3, table, get_times_total("FuSeBMC"))
    table[4][0] = "KLEE"
    fill_row("verifuzz"  , 5, table, get_times_total("verifuzz"))
    fill_row("clang"     , 6, table, get_times_total("clang"))
    fill_row("pulse"     , 7, table, get_times_total("pulse"))
    fill_row("infer"     , 8, table, get_times_total("infer"))

    table.insert(0, ["Tool", "Min", "Max", "Mean", "St. Dev", "Total"])
    return table

def gen_project(col_size : int, row_size : int):
    table = [[0 for _ in range(col_size)] for _ in range(row_size)]

    fill_row("libkluzzer", 0, table, get_times_project("libkluzzer", col_size-1))
    fill_row("CPAchecker", 1, table, get_times_project("CPAchecker", col_size-1))
    fill_row("symbiotic" , 2, table, get_times_project("symbiotic" , col_size-1))
    fill_row("FuSeBMC"   , 3, table, get_times_project("FuSeBMC"   , col_size-1))
    fill_row("KLEE"      , 4, table, get_times_project("KLEE"      , col_size-1))
    fill_row("verifuzz"  , 5, table, get_times_project("verifuzz"  , col_size-1))
    fill_row("clang"     , 6, table, get_times_project("clang"     , col_size-1))
    fill_row("pulse"     , 7, table, get_times_project("pulse"     , col_size-1))
    fill_row("infer"     , 8, table, get_times_project("infer"     , col_size-1))

    table.insert(0, ["Tool", "PA1", "PA2", "PA3", "PA4", "PA5", "PA6", "PA7", "PA8", "PA9", "PA10", "Total"])
    return table

def main(argv=None) -> int:
    if argv is None:
        argv=sys.argv[1:]

    table5_total = gen_total(6, 9)
    with open("tbl5.0_total.tex", "w") as fd:
        fd.write(to_latex(table5_total, 6))

    table5_project = gen_project(12, 9)
    with open("tbl5.0_project.tex", "w") as fd:
        fd.write(to_latex(table5_project, 12))
    return 0

if __name__ == "__main__":
    sys.exit(main())
