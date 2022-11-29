from __future__ import annotations
import os
import json
import yaml
from collections import Counter
import matplotlib
import matplotlib.pyplot as plt
from matplotlib_venn import *
import matplotlib.patches as mpatches
from matplotlib.colors import ColorConverter
import pandas as pd
import numpy as np
from pprint import pprint
from tabulate import tabulate

#plt.style.use('seaborn')
font = {'size'   : 22}
matplotlib.rc('font', **font)
matplotlib.rcParams['axes.spines.right'] = False
matplotlib.rcParams['axes.spines.top'] = False


def json_to_string(object : dict) -> str:
    return json.dumps(object, indent=4)


def parse_json(file : str) -> dict:
    with open(file, "r") as f:
        return json.load(f)


def parse_yaml(file : str) -> dict:
    with open(file, "r") as f:
        return yaml.safe_load(f)


def getErrorToCweMap():
    cwesPath = os.path.abspath("../files/cwe.yml")
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


def inflate_bug(bug_str : str) -> dict:
    result = {}
    bug = bug_str.split(":")
    project = bug[0]
    bug_type = bug[1]
    bug_line = bug[2]
    bug_file = bug[3]
    result["project"] = project
    result["bug_type"] = bug_type
    result["line"] = bug_line
    result["file"] = bug_file
    return result


def check_bug_in_tool_results(bug, fuzzer, symbolic, static):
    project = bug["project"]
    bug_type = bug["bug_type"]
    line = bug["line"]
    file = bug["file"]

    l = "{}:{}:{}:{}".format(project, bug_type, line, file)

    result = [0, 0, 0]
    if l in fuzzer:
        result[0] = 1

    if l in symbolic:
        result[1] = 1

    if l in static:
        result[2] = 1

    return result


def get_score_three_tools_venn(cwe, dataset, fuzzer, symbolic, static):

    # {'001': 10, '100': 20, '010': 21, '110': 13, '011': 14}
    sets = Counter()
    sets['100'] = 0
    sets['010'] = 0
    sets['001'] = 0
    sets['110'] = 0
    sets['011'] = 0
    sets['101'] = 0
    sets['111'] = 0

    num_results = 0
    for b in dataset:
        bug = inflate_bug(b)
        bug_cwe = bug["bug_type"]
        if cwe == bug_cwe:
            num_results += 1
            methods_used = check_bug_in_tool_results(bug, fuzzer, symbolic, static)
            sum_methods = sum(methods_used)

            if sum_methods == 0:
                continue
            if sum_methods == 1:
                if methods_used[0] == 1:
                    # Fuzzer Only
                    sets['100'] = sets['100'] + 1
                elif methods_used[1] == 1:
                    # Symbolic Only
                    sets['010'] = sets['010'] + 1
                else:
                    # Static Only
                    sets['001'] = sets['001'] + 1
            else:
                combination_key = ''.join(map(lambda i: str(i), methods_used))
                sets[combination_key] = sets[combination_key] + 1

    return sets


def plot_venn_scores(sets_list, labels, anchor_box, outfile):
    # font = {'size': 14}
    # matplotlib.rc('font', **font)
    # matplotlib.rcParams['axes.spines.right'] = False
    # matplotlib.rcParams['axes.spines.top'] = False

    LINES = 2
    COLUMNS = 4
    SUBPLOTS = len(sets_list)

    venn_fontsize = 8
    venn_title_fontsize = 8
    legend_fontsize = 8

    ccv = ColorConverter()
    mcta_patch = mpatches.Patch(color=np.array(ccv.to_rgba('r', 0.4)), label=labels[0])
    cfpm_patch = mpatches.Patch(color=np.array(ccv.to_rgba('g', 0.4)), label=labels[1])
    pism_patch = mpatches.Patch(color=np.array(ccv.to_rgba('b', 0.4)), label=labels[2])

    figure, axes = plt.subplots(1, SUBPLOTS, figsize=(10, 4), squeeze=True)

    sets_id = 0
    # for line in range(LINES):
    #     for column in range(COLUMNS):

    for sp in range(SUBPLOTS):
        ax = axes[sp]
        cwe = sets_list[sets_id][0]
        sets = sets_list[sets_id][1]
        ax.set_title(cwe).set_fontsize(venn_title_fontsize)

        v = venn3(subsets=sets, ax=ax)

        for text in v.set_labels:
            text.set_visible(False)

        for text in v.subset_labels:
            if text:
                text.set_fontsize(venn_fontsize)
        sets_id += 1

    plt.legend(handles=[mcta_patch, cfpm_patch, pism_patch], ncol=len(labels), bbox_to_anchor=anchor_box, fontsize=legend_fontsize, frameon=False)
    # plt.show()
    # plt.savefig("cwe_venn.png", bbox_inches='tight')
    plt.savefig(outfile, bbox_inches='tight')


def venn_categories(cwes, cwes_list, dataset, fuzzer, symbolic, static):
    sets_list_three = []
    for cwe in cwes_list:
        scores = get_score_three_tools_venn(cwe, dataset, fuzzer, symbolic, static)
        if sum(scores.values()) > 0:
            sets_list_three.append((cwes[cwe], scores))

    labels=['Fuzzer', 'Symbolic', 'Static']
    plot_venn_scores(sets_list_three, labels, (-1.65, 0), "venn_categories_vf_update.pdf")


def venn_best_tools_different_cats(cwes, cwes_list, dataset, fuzzer, symbolic, static):
    sets_list_three = []
    for cwe in cwes_list:
        scores = get_score_three_tools_venn(cwe, dataset, fuzzer, symbolic, static)
        if sum(scores.values()) > 0:
            sets_list_three.append((cwes[cwe], scores))

    labels=['FuSeBMC', 'CPAChecker', 'CLang']
    plot_venn_scores(sets_list_three, labels, (-1.5, 0), "venn_best_tools_cats_vf_update.pdf")


def venn_best_tools(cwes, cwes_list, dataset, tool1, tool2, tool3, labels):
    sets_list_three = []
    for cwe in cwes_list:
        scores = get_score_three_tools_venn(cwe, dataset, tool1, tool2, tool3)
        if sum(scores.values()) > 0:
            sets_list_three.append((cwes[cwe], scores))

    plot_venn_scores(sets_list_three, labels, (-1.5, 0), "venn_best_tools_vf_update.pdf")


def get_score_global_venn(dataset, fuzzer, symbolic, static):

    # {'001': 10, '100': 20, '010': 21, '110': 13, '011': 14}
    sets = Counter()
    sets['100'] = 0
    sets['010'] = 0
    sets['001'] = 0
    sets['110'] = 0
    sets['011'] = 0
    sets['101'] = 0
    sets['111'] = 0

    num_results = 0
    for b in dataset:
        bug = inflate_bug(b)

        num_results += 1
        methods_used = check_bug_in_tool_results(bug, fuzzer, symbolic, static)
        sum_methods = sum(methods_used)

        if sum_methods == 0:
            continue
        if sum_methods == 1:
            if methods_used[0] == 1:
                # Fuzzer Only
                sets['100'] = sets['100'] + 1
            elif methods_used[1] == 1:
                # Symbolic Only
                sets['010'] = sets['010'] + 1
            else:
                # Static Only
                sets['001'] = sets['001'] + 1
        else:
            combination_key = ''.join(map(lambda i: str(i), methods_used))
            sets[combination_key] = sets[combination_key] + 1

    return sets


def venn_global(dataset, fuzzer, symbolic, static):
    # font = {'size': 14}
    # matplotlib.rc('font', **font)
    # matplotlib.rcParams['axes.spines.right'] = False
    # matplotlib.rcParams['axes.spines.top'] = False
    venn_fontsize = 8
    venn_title_fontsize = 8
    legend_fontsize = 8

    labels=['Fuzzer', 'Symbolic', 'Static']

    ccv = ColorConverter()
    mcta_patch = mpatches.Patch(color=np.array(ccv.to_rgba('r', 0.4)), label=labels[0])
    cfpm_patch = mpatches.Patch(color=np.array(ccv.to_rgba('g', 0.4)), label=labels[1])
    pism_patch = mpatches.Patch(color=np.array(ccv.to_rgba('b', 0.4)), label=labels[2])

    fig, ax = plt.subplots(figsize=(10, 4))

    sets = get_score_global_venn(dataset, fuzzer, symbolic, static)

    v = venn3(subsets=sets, ax=ax)

    for text in v.set_labels:
        text.set_visible(False)

    for text in v.subset_labels:
        if text:
            text.set_fontsize(venn_fontsize)

    plt.legend(handles=[mcta_patch, cfpm_patch, pism_patch], ncol=len(labels), bbox_to_anchor=(1, 0), fontsize=legend_fontsize, frameon=False)
    # plt.show()
    plt.savefig("venn_global_update.pdf", bbox_inches='tight')


def main():
    cwes = {
        "cwe-121_stack-overflow": "CWE-121",
        "cwe-122_heap-overflow": "CWE-122",
        "cwe-124_buffer-underflow": "CWE-124",
        "cwe-401_memory-leak": "CWE-401",
        "cwe-415_bad-free": "CWE-415",
        "cwe-416_use-after-free": "CWE-416",
        "cwe-476_nullptr-dereference": "CWE-476",
        "cwe-789_alloc-too-big": "CWE-789",
        "cwe-120_classic-bo": "CWE-120",
        "cwe-125_out-of-bounds-read": "CWE-125",
        "cwe-369_devide-zero": "CWE-369",
        "cwe-563_deadstore": "CWE-563",
        "cwe-1325_bad-seq-mem-alloc": "CWE-1325",
        "cwe-562_return-stack-address": "CWE-562",
        "cwe-758_undef-behaviour": "CWE-758",
        "cwe-628_call-bad-args": "CWE-628",
        "cwe-457_use-uinitialised-variable": "CWE-457",
        "cwe-other": "Other CWE"
    }
    cwes_list = list(cwes.keys())[:8]

    dataset = set(flatten_json(parse_json("../files/dataset3.json")))
    fuzzer = set(flatten_json(parse_json("fuzzer-tp-new.json")))
    symbolic = set(flatten_json(parse_json("symbolic-tp-new.json")))
    static = set(flatten_json_static(parse_json("static-tp.json"), parse_json("../files/dataset3.json")))
    venn_categories(cwes, cwes_list, dataset, fuzzer, symbolic, static)

    fusebmc = set(flatten_json(parse_json("../files/true-positives/fuzzer-FuSeBMC.json")))
    cpachecker = set(flatten_json(parse_json("../files/true-positives/symbolic-CPAchecker.json")))
    clang = set(flatten_json_static(parse_json("../TAB-6/static_files/true-positives/static-clang.json"), parse_json("../files/dataset3.json")))
    venn_best_tools_different_cats(cwes, cwes_list, dataset, fusebmc, cpachecker, clang)

    labels=['CPAChecker', 'FuSeBMC', 'Symbiotic']
    symbiotic = set(flatten_json(parse_json("../files/true-positives/symbolic-symbiotic.json")))
    venn_best_tools(cwes, cwes_list, dataset, cpachecker, fusebmc, symbiotic, labels)

    venn_global(dataset, fuzzer, symbolic, static)

if __name__ == "__main__":
    main()