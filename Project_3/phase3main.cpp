#include <iostream>
using namespace std;
#include "Heap.cpp"
#include "BHeap.cpp"

int main()
{
	int v[100000];
	int k[100000];

	Heap<int, int> T1;

	//Should output  1 2 4 3 6 5 8 10 7 9

	for (int i = 0; i < 100000; i++)
	{
		v[i] = i;
		k[i] = i;
		T1.insert(i, i);
	}

	T1.printKey();

	Heap<int, int> T2(k, v, 100000);
	T2.printKey();
	// // Should output 1 2 5 4 3 9 6 10 7 8

	// cout << T2.peekValue() << endl;
	// //Should output K

	// cout << T1.extractMin() << endl;
	// //Should output 1

	// T2.printKey();
	// //Should output 2 3 5 4 8 9 6 10 7

	// BHeap<string, int> X(v, k, 10), Y;

	// X.printKey();
	// //Should output
	// //B1
	// //J K
	// //
	// //B3
	// //A E H I F C D B

	// cout << X.extractMin() << endl;
	// //Should output A

	// X.printKey(); //Should output
	// //B0
	// //B
	// //
	// //B3
	// //C E H I F J K D

	// Y.insert("M", 100);
	// Y.insert("O", 101);
	// Y.insert("G", 102);
	// Y.insert("N", 103);
	// Y.insert("L", 104);

	// Y.printKey();
	// //Should output
	// //B0
	// //L
	// //
	// //B2
	// //G M O N

	// Y.merge(X);
	// cout << Y.peekKey() << endl;
	// //Should output B

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
