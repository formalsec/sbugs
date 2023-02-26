#!/usr/bin/env python3
from __future__ import annotations
import os
import json
import yaml
import texttable
import latextable


def parse_json(file : str) -> dict:
    with open(file, "r") as f:
        return json.load(f)


def parse_yaml(file : str) -> dict:
    with open(file, "r") as f:
        return yaml.safe_load(f)


def json_to_string(object : dict) -> str:
    return json.dumps(object, indent=4)

def json_to_file(object : dict, file : str) -> None:
    with open(file, "w") as fd:
        json.dump(object, fd)


def error_to_cwe():
    cwesPath = os.path.abspath("../../cwe-mapping.yml")
    cwes = parse_yaml(cwesPath)
    cwesMap = {}
    for cwe in cwes:
        for error in cwes[cwe]:
            cwesMap[error] = cwe
    return cwesMap


def flatten_json(d : dict) -> list[str]:
    cwesMap = error_to_cwe()
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
    ds = []
    for p, bug_types in d.items():
        for t, bugs in bug_types.items():
            for b in bugs:
                l = "{}:{}:{}".format(
                    p,
                    b["line"],
                    b["file"]
                )
                ds.append(l)
    ds = list(set(ds))

    res = []
    for location in ds:
        l1 = location.split(":")
        project = dataset[l1[0]]
        cwe = ""
        for t, bs in project.items():
            for loc in bs:
                if (loc["line"] == l1[1]
                        and loc["file"] == l1[2]):
                    cwe = t
        if cwe == "":
            continue

        res.append("{}:{}:{}:{}".format(l1[0], cwe, l1[1], l1[2]))
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

def pp_cwe(code):
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
    return cwes[code]

def count_cwes(d, cwe_mapper):
    result = {}
    for _, bug_types in d.items():
        for t, bugs in bug_types.items():
            cwe = cwe_mapper[t]
            if not (cwe in result):
                result[cwe] = 0
            result[cwe] += len(bugs)
    return result

def get(m, k):
    try:
        return m[k]
    except:
        return 0

def to_latex(table : list, col_size : int):
    table_str = texttable.Texttable()
    table_str.set_cols_align(["c"] + ["r"] * (col_size - 1))
    table_str.add_rows(table)
    return latextable.draw_latex(table_str)

def table():
    cwes_map = error_to_cwe()
    # Dataset
    dataset = parse_json("../../results/dataset-gt1-extended.json")
    dataset_cwes = count_cwes(dataset, cwes_map)
    # Fuzzers
    fuse_cwes = count_cwes(parse_json("../../results/FuSeBMC.json"), cwes_map)
    kluz_cwes = count_cwes(parse_json("../../results/libkluzzer.json"), cwes_map)
    veri_cwes = count_cwes(parse_json("../../results/verifuzz.json"), cwes_map)
    # Symbolic
    klee_cwes = count_cwes(parse_json("../../results/KLEE.json"), cwes_map)
    symb_cwes = count_cwes(parse_json("../../results/symbiotic.json"), cwes_map)
    cpac_cwes = count_cwes(parse_json("../../results/CPAchecker.json"), cwes_map)
    # Static
    clang = parse_json("../../results/clang.json")
    infer = parse_json("../../results/infer.json")
    pulse = parse_json("../../results/pulse.json")
    cobra = parse_json("../../results/cobra/cobra.json")
    cppch = parse_json("../../results/cppcheck/cppcheck.json")
    flawf = parse_json("../../results/flawfinder/flawfinder.json")
    frama = parse_json("../../results/framaC/framaC.json")
    uno   = parse_json("../../results/uno/uno.json")
    clang_tp = inflate_json(flatten_json_static(clang, dataset))
    json_to_file(clang_tp, "clang.json")
    clang_cwes = count_cwes(clang_tp, cwes_map)
    infer_tp = inflate_json(flatten_json_static(infer, dataset))
    json_to_file(infer_tp, "infer.json")
    infer_cwes = count_cwes(infer_tp, cwes_map)
    pulse_tp = inflate_json(flatten_json_static(pulse, dataset))
    json_to_file(pulse_tp, "pulse.json")
    pulse_cwes = count_cwes(pulse_tp, cwes_map)
    cobra_tp = inflate_json(flatten_json_static(cobra, dataset))
    json_to_file(cobra_tp, "cobra.json")
    cobra_cwes = count_cwes(cobra_tp, cwes_map)
    cppch_tp = inflate_json(flatten_json_static(cppch, dataset))
    json_to_file(cppch_tp, "cppch.json")
    cppch_cwes = count_cwes(cppch_tp, cwes_map)
    flawf_tp = inflate_json(flatten_json_static(flawf, dataset))
    json_to_file(flawf_tp, "flawf.json")
    flawf_cwes = count_cwes(flawf_tp, cwes_map)
    frama_tp = inflate_json(flatten_json_static(frama, dataset))
    json_to_file(frama_tp, "frama.json")
    frama_cwes = count_cwes(frama_tp, cwes_map)
    uno_tp = inflate_json(flatten_json_static(uno, dataset))
    json_to_file(uno_tp, "uno.json")
    uno_cwes = count_cwes(uno_tp, cwes_map)
    static_tools = [
        ("clang", clang_cwes),
        ("infer", infer_cwes),
        ("pulse", pulse_cwes),
        ("cobra", cobra_cwes),
        ("cppchecker", cppch_cwes),
        ("flawfinder", flawf_cwes),
        ("framaC", frama_cwes),
        ("uno", uno_cwes),
    ]
    static_tools.sort(reverse=True,key=lambda p: sum(p[1].values()))
    print(static_tools[0:3])
    static = list(map(lambda p: p[1], static_tools))

    tools = ([fuse_cwes, kluz_cwes, veri_cwes, klee_cwes, symb_cwes, cpac_cwes] 
             + static[0:3])

    order = [
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
    rows = [["Scope", "FuSeBMC", "libkluzzer", "VeriFuzz", "KLEE", "Symbiotic",
            "CPAchecker", "FramaC", "Cobra", "Clang"]]
    for cwe in order:
        row = [pp_cwe(cwe)]
        for t in tools:
            n = get(t, cwe)
            row.append(f"{n} ({round((n/dataset_cwes[cwe]) * 100, 1)})")
        rows.append(row)
    DT = sum(dataset_cwes.values())
    total = ["Dataset"]
    for t in tools:
        T = sum(t.values())
        total.append(f"{T} ({round((T/DT) * 100, 1)})")
    rows.append(total)
    # print table
    print(to_latex(rows, len(tools) + 1))

table()
