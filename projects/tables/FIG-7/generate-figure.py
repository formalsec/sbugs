import os
import json
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.colors import ColorConverter

DEBUG=False

font = {'size'   : 22}
matplotlib.rc('font', **font)
matplotlib.rcParams['axes.spines.right'] = False
matplotlib.rcParams['axes.spines.top'] = False

def parse_json(file : str) -> dict:
    with open(file, "r") as f:
        return json.load(f)


def json_to_string(object : dict) -> str:
    return json.dumps(object, indent=4)


def keep_only_jsons(file):
    filename_array = file.split('.')
    return len(filename_array) > 1 and filename_array[1] == 'json'


def getNumbers_symb(filePath):
    rawNumbers = parse_json(filePath)

    results = 0
    for p in rawNumbers:
        project = rawNumbers[p]
        # print(f"Project {p}")
        for error in project:
            results += len(project[error])
    return results


def getNumbersDict_symb(jsonFiles):
    results = {}
    for file in jsonFiles:
        name = os.path.basename(file).split('.')[0]
        # print(f"Checking {name}")
        results[name] = getNumbers_symb(file)
    return results


def getNumbers_static(filePath):
    rawNumbers = parse_json(filePath)

    results = 0
    for p in rawNumbers:
        project = rawNumbers[p]
        results += len(project)

    return results


def getNumbersDict_static(jsonFiles):
    results = {}
    for file in jsonFiles:
        name = os.path.basename(file).split('.')[0]
        # print(f"Checking {name}")
        results[name] = getNumbers_static(file)
    return results


def global_score_method_plot_2(A_scores, B_scores):
    A = np.array([A_scores[method] for method in A_scores])
    B = np.array([B_scores[method] for method in B_scores])

    total = A+B
    proportion_A = np.true_divide(A, total) * 100
    proportion_B = np.true_divide(B, total) * 100

    #add colors
    # colors = ['#3dae55', '#f09d00', '#9858bb', '#e34d34']
    ccv = ColorConverter()
    colors_base = ['#3dae55', '#e34d34']
    colors = [ np.array(ccv.to_rgba(c, 0.8)) for c in colors_base]

    x_ticks = [
        "Fuzzer",
        "Symbolic",
        "Static"
    ]

    # The position of the bars on the x-axis
    r = range(len(x_ticks))
    barWidth = 0.85

    def place_value_label(X, proportion_X, before_X=[]):
        for i in range(len(X)):
            if X[i] < 45:
                continue

            if len(before_X) > 0:
                y = before_X[i] + (proportion_X[i]/2) - 0.5
            else:
                y = (proportion_X[i]/2) - 0.5

            if y <= 0:
                y = 1

            x = i
            if X[i] < 75:
                x = i
            plt.annotate(str(X[i]), xy=(x,y), fontsize=20, fontweight="bold", color="white", ha='center', va='center')

    #plot bars
    # plt.figure(figsize=(8.5,7))
    plt.figure(figsize=(9,5))
    ax1 = plt.bar(r, proportion_A, color=colors[0], width=barWidth, label='True Positives')
    ax2 = plt.bar(r, proportion_B, color=colors[1], bottom=proportion_A, width=barWidth, label='False Negatives')

    place_value_label(A, proportion_A)
    place_value_label(B, proportion_B, proportion_A)

    for i in range(len(A)):
        tp = A[i]
        fn = B[i]

        tpr = (float(tp) / float(tp + fn))*100

        plt.annotate(f"{tpr:.1f}%", xy=(i, 105), fontsize=20, color="black", ha='center', va='center')

    #plt.legend(bbox_to_anchor=(0.01, 1.09), loc='upper left', ncol=4, frameon=False)
    # plt.legend(bbox_to_anchor=(0.05, 1.15), loc='upper left', ncol=2, frameon=False)
    plt.legend(bbox_to_anchor=(0.5, 1.3), loc="upper center", ncol=2, frameon=False)
    plt.xticks(r, x_ticks) #, rotation=65)
    plt.ylabel(f"% of Vulnerabilities\nin Dataset")
    plt.tight_layout()
    # plt.show()
    plt.savefig("tools-recall-global-method-update.pdf", bbox_inches='tight')


filesDir = os.path.abspath(".")
jsonTPFiles = list(map(lambda p: os.path.join(filesDir, p), ["fuzzer-tp-new.json", "symbolic-tp-new.json"]))
tpNumbers = getNumbersDict_symb(jsonTPFiles)
jsonTPFiles = list(map(lambda p: os.path.join(filesDir, p), ["static-tp.json"]))
tpNumbers["static-tp"] = getNumbersDict_static(jsonTPFiles)["static-tp"]
print(tpNumbers)


jsonFNFiles = list(map(lambda p: os.path.join(filesDir, p), ["fuzzer-fn4.json", "symbolic-fn3.json"]))
fnNumbers = getNumbersDict_symb(jsonFNFiles)
jsonFNFiles = list(map(lambda p: os.path.join(filesDir, p), ["static-fn2.json"]))
fnNumbers["static-fn2"] = getNumbersDict_static(jsonFNFiles)["static-fn2"]
print(fnNumbers)

global_score_method_plot_2(tpNumbers, fnNumbers)
