from os import system

for i in range(5):
    system(f"pypy3 i.py <\"in/input_{i}.txt\" >\"out/output_{i}.txt\"")