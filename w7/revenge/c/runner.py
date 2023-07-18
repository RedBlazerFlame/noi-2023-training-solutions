from os import system

for i in ["08", "13", "14", "15", "16", "17", "18", "19", "20"]:
    system(f"pypy3 solver2.py <\"circuit_inputs/input_{i}.txt\" >\"outs/output_{i}.txt\"")
    print(f"{i} done")