from os import system

system("g++ -o brute_forcer brute_forcer.cpp")
system("g++ -o hyperbola_trick hyperbola_trick.cpp")

for i in range(1, 10000):
    with open("tester.in", "w+") as f:
        f.write(str(i))
    
    system("./brute_forcer >\"tester_brute_forcer.out\" <\"tester.in\"")
    system("./hyperbola_trick >\"tester_fast.out\" <\"tester.in\"")
    
    with open("tester_brute_forcer.out", "r+") as brute_f, open("tester_fast.out", "r+") as fast_f:
        if(brute_f.read() != fast_f.read()):
            print(f"{i} FAILED")
            exit(0)