from __future__ import annotations
import os
from pprint import pprint
from tabulate import tabulate
import json
import yaml


def parse_json(file : str) -> dict:
    with open(file, "r") as f:
        return json.load(f)


def parse_yaml(file : str) -> dict:
    with open(file, "r") as f:
        return yaml.safe_load(f)


def json_to_string(object : dict) -> str:
    return json.dumps(object, indent=4)


def create_latex_table(table):
    print(tabulate(table, tablefmt="latex_raw"))


def getErrorToCweMap():
    cwesPath = os.path.abspath("../../cwe-mapping.yml")
    cwes = parse_yaml(cwesPath)
    cwesMap = {}
    for cwe in cwes:
        for error in cwes[cwe]:
            cwesMap[error] = cwe
    return cwesMap


def flatten_json(d : dict) -> list[str]:
    cwesMap = getErrorToCweMap()
    res = []
    for p, bug_types in d.items():
        for t, bugs in bug_types.items():
            for location in bugs:
                l = "{}:{}:{}:{}".format(
                    p,
                    cwesMap[t],
                    location["line"],
                    location["file"]
                )
                res.append(l)
    return res


def flatten_json_static(d : dict, dataset: dict) -> list[str]:
    cwesMap = getErrorToCweMap()

    ds = []
    for p, bugs in d.items():
        for location in bugs:
            l = "{}:{}:{}".format(
                p,
                location["line"],
                location["file"]
            )
            ds.append(l)
    ds = list(set(ds))

    res = []
    for p, bugs in d.items():
        for location in bugs:
            l1 = "{}:{}:{}".format(
                p,
                location["line"],
                location["file"]
            )

            cwe = ""
            if l1 in ds:
                project = dataset[p]
                for t, bs in project.items():
                    for loc in bs:
                        if loc["line"] == location["line"] and loc["file"] == location["file"]:
                            cwe = t

            l2 = "{}:{}:{}:{}".format(
                    p,
                    cwesMap[cwe],
                    location["line"],
                    location["file"]
                )
            res.append(l2)
    return res


def inflate_json(l : list) -> dict:
    result = {}
    for v in l:
        bug = v.split(":")
        project = bug[0]
        bug_type = bug[1]
        bug_line = bug[2]
        bug_file = bug[3]
        if project not in result:
            result[project] = {}
        if bug_type not in result[project]:
            result[project][bug_type] = []
        result[project][bug_type].append(
            dict(line=bug_line, file=bug_file)
        )
    return result

def mapCWECodetoReadableCWE(cweCode):
    cwes = {
        "cwe-120_classic-bo": "CWE-120",
        "cwe-121_stack-overflow": "CWE-121",
        "cwe-122_heap-overflow": "CWE-122",
        "cwe-124_buffer-underflow": "CWE-124",
        "cwe-125_out-of-bounds-read": "CWE-125",
        "cwe-401_memory-leak": "CWE-401",
        "cwe-415_bad-free": "CWE-415",
        "cwe-416_use-after-free": "CWE-416",
        "cwe-789_alloc-too-big": "CWE-789",
        "cwe-369_devide-zero": "CWE-369",
        "cwe-563_deadstore": "CWE-563",
        "cwe-1325_bad-seq-mem-alloc": "CWE-1325",
        "cwe-562_return-stack-address": "CWE-562",
        "cwe-758_undef-behaviour": "CWE-758",
        "cwe-628_call-bad-args": "CWE-628",
        "cwe-457_use-uinitialised-variable": "CWE-457",
        "cwe-476_nullptr-dereference": "CWE-476",
        "cwe-other": "Other CWE"
    }
    return cwes[cweCode]


def cweToDescription(cweCode):
    cwes = {
        "cwe-120_classic-bo": "Classic Buffer-Overflow",
        "cwe-121_stack-overflow": "Stack Overflow",
        "cwe-122_heap-overflow": "Heap Overflow",
        "cwe-124_buffer-underflow": "Buffer-Underflow",
        "cwe-125_out-of-bounds-read": "Out-of-bounds Read",
        "cwe-401_memory-leak": "Memory Leak",
        "cwe-415_bad-free": "Bad Free",
        "cwe-416_use-after-free": "Use After Free",
        "cwe-789_alloc-too-big": "Alloc Too Big",
        "cwe-369_devide-zero": "Divide by Zero",
        "cwe-563_deadstore": "Dead Store",
        "cwe-1325_bad-seq-mem-alloc": "Bad Memory Alloc",
        "cwe-562_return-stack-address": "Return Stack Address",
        "cwe-758_undef-behaviour": "Undefined Behaviour",
        "cwe-628_call-bad-args": "Call Bad Args",
        "cwe-457_use-uinitialised-variable": "Use Uninitialised Variable",
        "cwe-476_nullptr-dereference": "Null Pointer Dereference",
        "cwe-other": "-"
    }
    return cwes[cweCode]


def print_table(fuzzer_cwes, sym_cwes, static_cwes, global_cwes):
    table = []

    header_1 = ["\multirow{2}{*}{\makecell{CWE}}", "\multirow{2}{*}{\makecell{Description}}", "\multicolumn{4}{c}{\makecell{Undetected}}", "\multirow{2}{*}{\makecell{Total\\\\Vulnerabilities}}"]
    header_2 = ["", "", "Fuzzer (\%)", "Symbolic (\%)",  "Static (\%)", "Global (\%)", ""]
    table.append(header_1)
    table.append(header_2)

    for cwe in global_cwes:
        fuzzer_str = f"{fuzzer_cwes[cwe][0]} ({(fuzzer_cwes[cwe][0]/fuzzer_cwes[cwe][1])*100:.0f}\%)"
        sym_str = f"{sym_cwes[cwe][0]} ({(sym_cwes[cwe][0]/sym_cwes[cwe][1])*100:.0f}\%)"
        static_str = f"{static_cwes[cwe][0]} ({(static_cwes[cwe][0]/static_cwes[cwe][1])*100:.0f}\%)"
        global_str = f"{global_cwes[cwe][0]} ({(global_cwes[cwe][0]/global_cwes[cwe][1])*100:.0f}\%)"
        table.append([mapCWECodetoReadableCWE(cwe), cweToDescription(cwe), fuzzer_str, sym_str, static_str, global_str, global_cwes[cwe][1]])

    create_latex_table(table)

def make_table_symb_static():
    # fuzzer_sym = set(flatten_json(parse_json("all-fn-5.json")))
    fuzzer = set(flatten_json(parse_json("fuzzer-fn.json")))
    sym = set(flatten_json(parse_json("sym-fn.json")))
    # fuzzer_sym = fuzzer & sym
    static = set(flatten_json_static(parse_json("static-fn-2.json"), parse_json("../../results/dataset-gt1-extended.json")))
    # all_tools = inflate_json(list(fuzzer_sym & static))
    all_tools = inflate_json(list(fuzzer & sym & static))
    # print(json_to_string(all))

    cwes_symb = [
        "cwe-121_stack-overflow",
        "cwe-122_heap-overflow",
        "cwe-124_buffer-underflow",
        "cwe-401_memory-leak",
        "cwe-415_bad-free",
        "cwe-416_use-after-free",
        "cwe-476_nullptr-dereference",
        "cwe-789_alloc-too-big",
        "cwe-other",
        ]

    cwesMap = getErrorToCweMap()
    dataset = parse_json("../../results/dataset-gt1-extended.json")
    dataset_cwes = {}
    for p, bug_types in dataset.items():
        for t, bugs in bug_types.items():
            cwe = cwesMap[t]
            if cwe in dataset_cwes:
                dataset_cwes[cwe] = dataset_cwes[cwe] + len(bugs)
            else:
                dataset_cwes[cwe] = len(bugs)

    global_cwes = {}
    for p, bug_types in all_tools.items():
        for t, bugs in bug_types.items():
            if t in global_cwes:
                global_cwes[t][0] = global_cwes[t][0] + len(bugs)
            else:
                global_cwes[t] = [ len(bugs), dataset_cwes[t] ]

    fuzzer_cwes = {}
    for p, bug_types in inflate_json(fuzzer).items():
        for t, bugs in bug_types.items():
            if t in fuzzer_cwes:
                fuzzer_cwes[t][0] = fuzzer_cwes[t][0] + len(bugs)
            else:
                fuzzer_cwes[t] = [ len(bugs), dataset_cwes[t] ]

    sym_cwes = {}
    for p, bug_types in inflate_json(sym).items():
        for t, bugs in bug_types.items():
            if t in sym_cwes:
                sym_cwes[t][0] = sym_cwes[t][0] + len(bugs)
            else:
                sym_cwes[t] = [ len(bugs), dataset_cwes[t] ]


    static_cwes = {}
    for p, bug_types in inflate_json(static).items():
        for t, bugs in bug_types.items():
            if t in static_cwes:
                static_cwes[t][0] = static_cwes[t][0] + len(bugs)
            else:
                static_cwes[t] = [ len(bugs), dataset_cwes[t] ]

    # print(json_to_string(dataset_cwes)-gt0)
    # print(json_to_string(cwes))

    print_table(fuzzer_cwes, sym_cwes, static_cwes, global_cwes)


make_table_symb_static()
