#include <iostream>
#include <chrono>
using namespace std;

int main() {
    auto t1t1 = chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000000; i++) {
        int a[10000];
    }
    auto t1t2 = chrono::high_resolution_clock::now();

    auto t2t1 = chrono::high_resolution_clock::now();
    for(int i = 0; i < 1000000; i++) {
        int* a = new int[10000];
        delete[] a;
    }
    auto t2t2 = chrono::high_resolution_clock::now();
    
    cout << "Stack: " << chrono::duration_cast<chrono::microseconds>(t1t2 - t1t1).count() << " ms" << endl;
    cout << "Heap: " << chrono::duration_cast<chrono::microseconds>(t2t2 - t2t1).count() << " ms" << endl;
    
    return 0;
}