from __future__ import annotations
from __future__ import print_function

import json
import yaml

def parse_json(file : str) -> dict:
    with open(file, "r") as f:
        return json.load(f)

def parse_yaml(file : str) -> dict:
    with open(file, "r") as f:
        return yaml.safe_load(f)

def output_json(object : dict, filename : str) -> None:
    with open(filename, "w") as f:
        json.dump(object, f, indent=4)

def json_to_string(object : dict) -> str:
    return json.dumps(object, indent=4)
