import sys
import resource
import subprocess

class Executor:
    def __init__(
            self,
            tool,
            args,
            time_limit=900,           # hard time limit
            memory_limit=15*1024*1024 # hard memory limit
    ):
        self.tool = tool
        self.args = args
        self.time_limit = time_limit
        self.memory_limit = memory_limit

    @staticmethod
    def memory_limit(soft, hard):
        resource.setrlimit(resource.RLIMIT_AS, (soft, hard))
