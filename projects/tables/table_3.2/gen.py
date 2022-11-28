#!/usr/bin/python3
import os
import sys
import json
import yaml
import latextable
import statistics

from texttable import Texttable

PROJECT_ROOT = os.path.join("..", "..")

def read_json(filename : str) -> dict:
    with open(filename, "r") as fd:
        return json.load(fd)

def read_yaml(filename : str) -> dict:
    with open(filename, "r") as fd:
        return yaml.safe_load(fd)


def to_latex(table : list, col_size : int) -> None:
    table_str = Texttable()
    table_str.set_cols_align(["c"] + ["r"] * (col_size - 1))
    table_str.add_rows(table)
    return latextable.draw_latex(table_str)

def get_label(cats : dict, sub_lbl : str) -> str:
    for lbl, sub_lbls in cats.items():
        if sub_lbl == lbl:
            return lbl
        if sub_lbl in sub_lbls:
            return lbl
    return ""

def gen_table(n_rows: int, n_cols : int, gt_0 : str, gt_1 : str):
    dgt_0 = read_json(gt_0)
    dgt_1 = read_json(gt_1)

    categories = read_yaml(os.path.join(PROJECT_ROOT, "cwe-mapping.yml"))

    col_map = {
        "iaed_p1"     : (1, 2),
        "iaed_p2"     : (3, 4),
        "asa_1819_p1" : (5, 6),
        "asa_1819_p2" : (7, 8),
        "asa_1920_p1" : (9, 10),
        "asa_1920_p2" : (11, 12),
        "asa_2021_p1" : (13, 14),
        "asa_2021_p2" : (15, 16),
        "asa_2122_p1" : (17, 18),
        "asa_2122_p2" : (19, 20),
    }

    row_label = {
        "cwe-121_stack-overflow"      : "CWE-121",
        "cwe-122_heap-overflow"       : "CWE-122",
        "cwe-124_buffer-underflow"    : "CWE-124",
        "cwe-401_memory-leak"         : "CWE-401",
        "cwe-415_bad-free"            : "CWE-415",
        "cwe-416_use-after-free"      : "CWE-416",
        "cwe-476_nullptr-dereference" : "CWE-476",
        "cwe-789_alloc-too-big"       : "CWE-789",
        "cwe-other"                   : "Other CWE"
    }

    row_map = {
        "cwe-121_stack-overflow"      : 0,
        "cwe-122_heap-overflow"       : 1,
        "cwe-124_buffer-underflow"    : 2,
        "cwe-401_memory-leak"         : 3,
        "cwe-415_bad-free"            : 4,
        "cwe-416_use-after-free"      : 5,
        "cwe-476_nullptr-dereference" : 6,
        "cwe-789_alloc-too-big"       : 7,
        "cwe-other"                   : 8
    }

    bugs_0 = {}
    for proj, vulns in dgt_0.items():
        if proj not in bugs_0:
            bugs_0[proj] = {}
        for bug_type, bugs in vulns.items():
            if bug_type not in bugs_0[proj]:
                bugs_0[proj][bug_type] = 0
            bugs_0[proj][bug_type] += len(bugs)

    bugs_1 = {}
    for proj, vulns in dgt_1.items():
        if proj not in bugs_1:
            bugs_1[proj] = {}
        for bug_type, bugs in vulns.items():
            if bug_type not in bugs_1[proj]:
                bugs_1[proj][bug_type] = 0
            bugs_1[proj][bug_type] += len(bugs)


    table = [[0 for _ in range(n_cols)] for _ in range(n_rows)]
    for proj, counts in bugs_0.items():
        for bug_type, cnt in counts.items():
            lbl = get_label(categories, bug_type)
            if table[row_map[lbl]][0] == 0:
                table[row_map[lbl]][0] = row_label[lbl]
            table[row_map[lbl]][col_map[proj][0]] += cnt

    for proj, counts in bugs_1.items():
        for bug_type, cnt in counts.items():
            lbl = get_label(categories, bug_type)
            table[row_map[lbl]][col_map[proj][1]] += cnt

    # Sums
    for i in range(n_rows):
        table[i][21] = sum([table[i][j] for j in range(1, 21, 2)])
        table[i][22] = sum([table[i][j] for j in range(2, 21, 2)])

    table[n_rows - 1][0] = "Total"
    for j in range(1, n_cols):
        for i in range(n_rows - 1):
            table[n_rows - 1][j] += table[i][j]

    # Add headers to table
    header1 = ["Scope"] + ["\\multicol{2}{c}{\\bf PA" + str(i) + "}" for i in range(1, 11)] + [""] * 12
    header2 = [""] + ["GT0", "GT1"] * 11
    table.insert(0, header1)
    table.insert(1, header2)

    return table

def main(argv=None) -> int:
    if argv is None:
        argv=sys.argv[1:]

    n_rows, n_cols = 10, 23
    gt_0 = os.path.join(PROJECT_ROOT, "results", "dataset-gt0.json")
    gt_1 = os.path.join(PROJECT_ROOT, "results", "dataset-gt1-extended.json")

    table = gen_table(n_rows, n_cols, gt_0, gt_1)
    table_str = to_latex(table, n_cols)
    with open("tbl3.2_gt.tex", "w") as fd:
        fd.write(table_str)

    return 0

if __name__ == "__main__":
    sys.exit(main())
