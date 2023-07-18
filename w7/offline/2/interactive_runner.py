#!/usr/bin/env pypy3.9

"""Makes two processes interact.

This code can be run as python2 or python3 in most systems.

This is a small program that runs two processes, connecting the stdin of each
one to the stdout of the other. It doesn't perform a lot of checking, so many
errors may be caught internally by Python (e.g., if your command line has
incorrect syntax) or not caught at all (e.g., if the judge or solution hangs).

Run this as:

    python interactive_runner.py <cmd_line_judge> -- <cmd_line_solution>

For example, if you have a testing_tool.py in python3 to use as judge -- like
one downloaded from a problem statement -- and you would run your solution
in a standalone using one of the following:

    python3 my_solution.py
    ./my_solution
    java Solution
    my_solution.exe

Then you could run the judge and solution together, using this, as:

    python interactive_runner.py python3 testing_tool.py -- python3 my_solution.py
    python interactive_runner.py python3 testing_tool.py -- ./my_solution
    python interactive_runner.py python3 testing_tool.py -- java solution
    python interactive_runner.py python3 testing_tool.py -- my_solution.exe

Notice that the solution in cases 2, 3 and 4 would usually have a compilation
step before running, which you should run in your usual way before using this
tool.

This is only intended as a convenient tool to help contestants test solutions
locally. In particular, it is not identical to the implementation on our
server, which is more complex.

The standard streams are handled the following way:

- judge's stdin is connected to the solution's stdout;
- judge's stdout is connected to the solution's stdin;
- stderrs of both judge and solution are piped to standard error stream, with
  lines prepended by "judge: " and "  sol: " respectively (note, no
  synchronization is done so it's possible for the messages from both programs
  to overlap with each other).
"""

from __future__ import print_function
import sys
from subprocess import PIPE, Popen
from threading import Thread

class SubprocessThread(Thread):
    def __init__(self, args, stdin=PIPE, stdout=PIPE, stderr_prefix=None):
        super(SubprocessThread, self).__init__()
        self.stderr_prefix = stderr_prefix
        self.popen = Popen(args, stdin=stdin, stdout=stdout, stderr=PIPE)

    def run(self):
        try:
            self.pipe_to_stderr(self.popen.stderr)
            self.return_code = self.popen.wait()
            self.error_msg = None
        except (SystemError, OSError):
            self.return_code = -1
            self.error_msg = "The process crashed or produced too much output."

    # Reads bytes from the stream and writes them to sys.stderr prepending
    # lines with self.stderr_prefix. We are not reading by lines to guard
    # against the case when EOL is never found in the stream.
    def pipe_to_stderr(self, stream):
        new_line = True
        while True:
            chunk = stream.readline(1024)
            if not chunk:
                return
            chunk = chunk.decode("UTF-8")
            if new_line and self.stderr_prefix:
                chunk = self.stderr_prefix + chunk
                new_line = False
            sys.stderr.write(chunk)
            if chunk.endswith("\n"):
                new_line = True
            sys.stderr.flush()


if sys.argv.count("--") != 1:
    raise Exception(
        "There should be exactly one instance of '--' in the command line.")
sep_index = sys.argv.index("--")
judge_args = sys.argv[1:sep_index]
solut_args = sys.argv[sep_index + 1:]

t_solut = SubprocessThread(
        solut_args,
        stderr_prefix="  sol: ")
t_judge = SubprocessThread(
        judge_args,
        stdin=t_solut.popen.stdout,
        stdout=t_solut.popen.stdin,
        stderr_prefix="judge: ")
t_solut.start()
t_judge.start()
t_solut.join()
t_judge.join()

# Print an empty line to handle the case when stderr doesn't print EOL.
print()
print(   "Judge return code:", t_judge.return_code)
if t_judge.error_msg: print("Judge error message:", t_judge.error_msg)

print("Solution return code:", t_solut.return_code)
if t_solut.error_msg: print("Solution error message:", t_solut.error_msg)

if t_solut.return_code:
    print("A solution finishing with exit code other than 0 (without exceeding "
          "time or memory limits) would be interpreted as a Runtime Error "
          "in the system.")
    raise Exception(t_solut.return_code)
elif t_judge.return_code:
    print("A solution finishing with exit code 0 (without exceeding time or "
          "memory limits) and a judge finishing with exit code other than 0 "
          "would be interpreted as a Wrong Answer in the system.")
    raise Exception(t_judge.return_code)
else:
    print("A solution and judge both finishing with exit code 0 (without "
          "exceeding time or memory limits) would be interpreted as Correct "
          "in the system.")
