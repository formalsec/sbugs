from __future__ import annotations
import yaml

def read_yaml(file : str) -> dict:
    with open(file, "r") as fd:
        return yaml.safe_load(fd)
