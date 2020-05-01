#include <iostream>
using namespace std;
#include "Heap.cpp"
#include "BHeap.cpp"

int main()
{
    string v[10] = {"A", "B", "C", "D", "E", "F", "H", "I", "J", "K"};
    int k[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    BHeap<string, int> X(v, k, 10), Y;

    X.printKey();
    // //Should output
    // //B1
    // //J K
    // //
    // //B3
    // //A E H I F C D B

    cout << X.extractMin() << endl;
    // //Should output A

    X.printKey();
    // //Should output
    // //B0
    // //B
    // //
    // //B3
    // //C E H I F J K D
    cout << "____________ " << endl;
    Y = X;
    Y.printKey();

    // Y.insert("M", 100);
    // Y.insert("O", 101);
    // Y.insert("G", 102);
    // Y.insert("N", 103);
    // Y.insert("L", 104);

    // Y.printKey();
    // // //Should output
    // // //B0
    // // //L
    // // //
    // // //B2
    // // //G M O N

    // Y.merge(X);
    // cout << Y.peekKey() << endl;
    // // //Should output B

    // Y.printKey();
    // //Should output
    // //B1
    // //B L
    // //
    // //B2
    // //G M O N
    // //
    // //B3
    // //C E H I F J K D

    // return 0;
}
