#!/usr/bin/env pypy3.9

"""Local testing tool for the problem "Scales".

Run one of the following commands, where the part after "--" is how you might
run your program normally in a non-interactive task:

    ./interactive_runner.py ./local_judge.py input.txt -- ./my_solution
    ./interactive_runner.py ./local_judge.py input.txt -- my_solution.exe
    ./interactive_runner.py ./local_judge.py input.txt -- python3 my_solution.py

where input.txt is a valid input file.

Notice that in the first and second, there would usually be a compilation step
before running, which you should run in your usual way before using this tool.

The testing tool also accepts arguments such as -v; run

    ./local_judge.py --help

for more information.

To use arguments with the interactive runner, simply pass the arguments to the
judge command, e.g.,

    ./interactive_runner.py ./local_judge.py input.txt -v 1 -- ./my_solution
"""

from fractions import Fraction as Frac
from sys import stderr

def interact_scales(cases, user, *, verbose=0, wrong=Exception):

    if verbose:
        print(f"Starting interaction with {len(cases)} cases.", file=stderr)

    print(len(cases), file=user, flush=True)

    for caseno, ordering in enumerate(cases, 1):
        if verbose >= 2:
            print(f"[Case {caseno}] Starting a new case with order:", *ordering, file=stderr)

        weight_of = {coin: weight for weight, coin in enumerate(ordering)}
        coinset = {*range(1, 6 + 1)}
        assert coinset == {*weight_of}

        def get_lightest(a, b, c):
            if not (len({a, b, c}) == 3 and {a, b, c} <= coinset): raise wrong("Invalid weighing")
            return min(a, b, c, key=weight_of.get)

        def get_heaviest(a, b, c):
            if not (len({a, b, c}) == 3 and {a, b, c} <= coinset): raise wrong("Invalid weighing")
            return max(a, b, c, key=weight_of.get)

        def get_median(a, b, c):
            if not (len({a, b, c}) == 3 and {a, b, c} <= coinset): raise wrong("Invalid weighing")
            a, b, c = sorted((a, b, c), key=weight_of.get)
            return b

        def get_next_lightest(a, b, c, d):
            if not (len({a, b, c, d}) == 4 and {a, b, c, d} <= coinset): raise wrong("Invalid weighing")
            remain = [a, b, c]
            remain = [coin for coin in remain if weight_of[coin] > weight_of[d]] or remain
            return min(remain, key=weight_of.get)

        weighing_count = 0
        while True:
            [setting] = user.read.token().space
            if setting == 'answer':
                [predicted_ordering] = user.read.ints(6, 1, 6).eoln
                break
            elif setting == 'getLightest':
                weighing_count += 1
                [(a, b, c)] = user.read.ints(3, 1, 6).eoln
                print(get_lightest(a, b, c), file=user, flush=True)
            elif setting == 'getHeaviest':
                weighing_count += 1
                [(a, b, c)] = user.read.ints(3, 1, 6).eoln
                print(get_heaviest(a, b, c), file=user, flush=True)
            elif setting == 'getMedian':
                weighing_count += 1
                [(a, b, c)] = user.read.ints(3, 1, 6).eoln
                print(get_median(a, b, c), file=user, flush=True)
            elif setting == 'getNextLightest':
                weighing_count += 1
                [(a, b, c, d)] = user.read.ints(4, 1, 6).eoln
                print(get_next_lightest(a, b, c, d), file=user, flush=True)
            else:
                raise wrong(f"Invalid output")

        print((1 if caseno < len(cases) else 0), file=user, flush=True)

        yield ordering, predicted_ordering, weighing_count

        if verbose >= 2:
            print(f"[Case {caseno}] Performed {weighing_count} weighings.", file=stderr)


### @@ rem {
def main():
    from collections import deque
    from itertools import islice
    from random import Random, getrandbits
    from sys import stdin, stdout, exit as sysexit

    class Wrong(Exception):
        pass

    class InteractorException(Exception):
        pass

    class ChainRead:
        def __init__(self, stream):
            self._s = stream
            self._r = deque()
            super().__init__()

        def __iter__(self):
            while self._r:
                yield self._r.popleft()

        def __call__(self): return list(self)

        def ints(self, *a, **kw):
            self._r.append(self._s.read_ints(*a, **kw)); return self

        def int(self, *a, **kw):
            self._r.append(self._s.read_int(*a, **kw)); return self

        def token(self, *a, **kw):
            self._r.append(self._s.read_token(*a, **kw)); return self

        @property
        def space(self):
            self._s.read_space(); return self

        @property
        def eoln(self):
            self._s.read_eoln(); return self

    class Stream:
        def __init__(self, reader, writer):
            self.reader = reader
            self.writer = writer
            self.read = ChainRead(self)
            self.pieces = deque()
            super().__init__()

        def read_int(self, a, b):
            piece = self.next_piece()
            try:
                res = int(piece)
            except ValueError:
                raise Wrong(f"Expected an int in [{a}, {b}], got {piece!r}")
            if not (a <= res <= b):
                raise Wrong(f"{res} not in [{a}, {b}]")
            return res

        def read_token(self):
            return self.next_piece()

        def read_ints(self, n, a, b):
            res = []
            for i in range(n):
                if i: self.read_space()
                res.append(self.read_int(a, b))
            return res

        def read_space(self):
            self.expect(' ')

        def read_eoln(self):
            self.expect('\n')

        def expect(self, expec):
            got = self.next_piece()
            if expec != got:
                raise Wrong(f"Expected {expec!r}, got {got!r}")

        def next_piece(self):
            if not self.pieces:
                line = self.reader.readline()
                endl = line.endswith('\n')
                if endl: line = line[:-1]
                for v in line.split(' '):
                    self.pieces.append(v)
                    self.pieces.append(' ')
                # discard last space
                self.pieces.pop()
                if endl: self.pieces.append('\n')

            if not self.pieces:
                raise Wrong("No more output")

            return self.pieces.popleft()

        def write(self, *args, **kwargs): self.writer.write(*args, **kwargs)
        def flush(self, *args, **kwargs): self.writer.flush(*args, **kwargs)

    def get_cases(input_file, *, verbose=0):
        with open(input_file) as inputf:
            t = int(inputf.readline())
            if t <= 0:
                raise InteractorException(f"Invalid number of test cases {t}")
            cases = []
            for caseno in range(t):
                ordering = [*map(int, inputf.readline().split())]
                if sorted(ordering) != [*range(1, 6+1)]:
                    raise InteractorException(f"Invalid ordering {ordering}")
                cases.append(ordering)
            return cases

    from argparse import ArgumentParser

    parser = ArgumentParser(description="Local testing judge for 'Scales'")
    parser.add_argument('input_file', nargs='?', help='input file to read')
    parser.add_argument('-v', '--verbose', type=int, help='Verbosity level (default: %(default)s)', default=0)

    args = parser.parse_args()

    try:
        cases = get_cases(args.input_file, verbose=args.verbose)
        counts = []
        for ordering, predicted_ordering, ct in interact_scales(
                cases,
                Stream(stdin, stdout),
                wrong=Wrong,
                verbose=args.verbose,
            ):
            print("The contestant's output is:", *predicted_ordering, file=stderr)
            counts.append(ct)
    except Wrong as exc:
        [message] = exc.args
        print("The answer is incorrect:", message, file=stderr)
        sysexit(1)
    except InteractorException:
        raise
    except Exception as exc:
        raise InteractorException(
                "The interactor issued an error! "
                "Please contact the admins. (Also save the script's output and send them to the admins.)") from exc
    else:
        print(
            f"The solution spent performed a maximum of {max(counts)} weighings "
            f"and a total of {sum(counts)} weighings.", file=stderr)
    finally:
        # end the test cases
        print(0)


if __name__ == '__main__':
    main()

### @@ }
