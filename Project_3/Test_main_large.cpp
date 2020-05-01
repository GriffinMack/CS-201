#include <iostream>
#include <chrono>
#include "Heap.cpp"
#include "BHeap.cpp"

using namespace std;
using namespace chrono;

bool LARGE_HEAP_PRINT = false;
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();
void test12();
void test13();
void test14();
void test15();

template <typename keytype, typename valuetype>
void foo(Heap<keytype,valuetype> x) 
{
	cout << "Entering foo..." << endl;
	cout << "Printing copied heap:" << endl;
	x.printKey();
    cout << "Extracting min: " << x.extractMin() << endl;
	cout << "Printing modified heap: " << endl;
	x.printKey();
	cout << "Exiting foo..." << endl << endl;
}

template <typename keytype, typename valuetype>
void foo1(BHeap<keytype,valuetype> x)
{
	cout << "Entering foo..." << endl;
	cout << "Printing copied heap:" << endl;
	x.printKey();
    cout << "Extracting min: " << x.extractMin() << endl;
	cout << "Printing modified heap: " << endl;
	x.printKey();
	cout << "Exiting foo..." << endl << endl;
}

int main(int argc, char **argv)
{
    if(argc < 2){
        cout << "use: ./phase2 #" << endl;
        return 0;
    }
	int testToRun = atoi(argv[1]);
    cout << "-------TESTS BEGIN-------" << endl << endl;
	auto start = steady_clock::now();
	switch (testToRun){
		case 1:
			test1();
			break;
		case 2:
			test2();
			break;
		case 3:
			test3();
			break;
		case 4:
			test4();
			break;
		case 5:
			test5();
			break;
		case 6:
			test6();
			break;
		case 7:
			test7();
			break;
		case 8:
			test8();
			break;
		case 9:
			test9();
			break;
		case 10:
			test10();
			break;
		case 11:
			test11();
			break;
		case 12:
			test12();
			break;
		case 13:
			test13();
			break;
		case 14:
			test14();
			break;
		case 15:
			test15();
			break;
	}
	auto end = steady_clock::now();
    cout << endl << "-------TESTS OVER-------" << endl;
	cout << endl << "Completed in " << duration_cast<microseconds>(end-start).count() << " µs" << endl;
    cout << endl << "you can also try: ./phase2 # > debug.out" << endl;
}

void test1()
{
	cout << "testing default contructors for Binary Heap..." << endl;
    Heap<int,int> T1;
	Heap<double,double> T2;
	Heap<int,double> T3;
	Heap<double,int> T4;
	Heap<string,string> T5;
	Heap<string,int> T6;
	Heap<int,string> T7;
	Heap<string,double> T8;
	Heap<double,string> T9;
	Heap<long,long> T10;
	cout << "test passed..." << endl;
}

void test2()
{
	const int size = 10;
	int k[size];
	int v[size];
	cout << "Building Binary Heap via default constructor" << endl;
	Heap<int,int> T1;
	for(int i=size-1; i>=0; i--){
		T1.insert(i,i);
	}
	cout << "success..." << endl;
	cout << "Building Binary Heap via alternate constructor" << endl;
	int j = 9;
	for(int i=0; i<size; i++){
		k[i] = j-i;
		v[i] = j-i;
	}
	Heap<int,int> T2(k,v,size);
	cout << "success..." << endl << endl;

	cout << "Printing Keys for both Heaps..." << endl;
	cout << "T1: "; T1.printKey();
	cout << "T2: "; T2.printKey(); cout << endl;

	cout << "Testing minimum for T1" << endl;
	cout << T1.peekKey() << endl;
	cout << T1.peekValue() << endl;
	cout << "Exctracting min..." << endl;
	cout << T1.extractMin() << endl;
	cout << "Printing key..." << endl;
	T1.printKey(); cout << endl;

	cout << "Testing minimum for T2" << endl;
	cout << T2.peekKey() << endl;
	cout << T2.peekValue() << endl;
	cout << "Exctracting min..." << endl;
	cout << T2.extractMin() << endl;
	cout << "Printing key..." << endl;
	T2.printKey();
}

void test3()
{
	cout << "Creating Binary Heap from default contructor..." << endl;
    const int size = 10;
	Heap<int,int> T1;
	for(int i=size-1; i>=0; i--){
		T1.insert(i,i);
	}
	cout << "Printing original heap:" << endl;
	T1.printKey(); cout << endl;
	cout << "Testing copy constructor..." << endl;
	foo(T1);
	cout << "Printing original heap:" << endl;
	T1.printKey();
	
	Heap<int,int> T2;
	cout << endl << "Testing copy assignment operator..." << endl;
	T2 = T1;
	cout << "Printing copied heap:" << endl;
	T2.printKey();
	cout << "Extracting min: " << T2.extractMin() << endl;
	cout << "Printing modified heap:" << endl;
	T2.printKey();
	cout << endl << "Printing original heap:" << endl;
	T1.printKey();
}
	
void test4()
{
	cout << "Creating Binary Heap from secondary constructor..." << endl;
	const int size = 10;
	int k[size];
	int v[size];
	int j = 9;
	for(int i=0; i<size; i++){
		k[i] = j-i;
		v[i] = j-i;
	}
	Heap<int,int> T2(k,v,size);
	cout << "Printing original heap:" << endl;
	T2.printKey(); cout << endl;
	cout << "Testing copy constructor..." << endl;
	foo(T2);
	cout << "Printing original heap:" << endl;
	T2.printKey();
	
	Heap<int,int> T1;
	cout << endl << "Testing copy assignment operator..." << endl;
	T1 = T2;
	cout << "Printing copied heap:" << endl;
	T1.printKey();
	cout << "Extracting min: " << T1.extractMin() << endl;
	cout << "Printing modified heap:" << endl;
	T1.printKey();
	cout << endl << "Printing original heap:" << endl;
	T2.printKey();
}

void test5()
{
	cout << "creating big Binary Heap using default contructor..." << endl;
	const int size = 1000;
	Heap<int,int> T1;
	for(int i=size-1; i>=0; i--){
		T1.insert(i,i);
	}
	if(LARGE_HEAP_PRINT){
		cout << "success! printing tree..." << endl;
		T1.printKey(); cout << endl;
	}
	cout << "removing everything..." << endl << endl;
	int key = 0;
	for(int i=0; i<size; i++){
		key = T1.extractMin();
		if(key != i){
			cout << "Error: i=" << i << " but key=" << key << endl;
		}
		if(size <= 10){
			T1.printKey();
		}
	}
	cout << "success!" << endl;
}

void test6()
{
	cout << "creating big Binary Heap using secondary contructor..." << endl;
	const int size = 1000;
	int k[size];
	int v[size];
	for(int i=0; i < size; i++){
		k[i] = size-(i+1);
		v[i] = size-(i+1);
	}
	Heap<int,int> T1(k,v,size);
	if(LARGE_HEAP_PRINT){
		cout << "success! printing tree..." << endl;
		T1.printKey();
	}
	cout << "removing everything..." << endl << endl;
	int key = 0;
	for(int i=0; i<size; i++){
		key = T1.extractMin();
		if(key != i){
			cout << "Error: i=" << i << " but key=" << key << endl;
		}
		if(size <= 10){
			T1.printKey();
		}
	}
	cout << endl << "success!" << endl;
}

//Bionomial Heap

void test7()
{
	cout << "testing default contructors for Binomial Heap..." << endl;
    BHeap<int,int> T1;
	BHeap<double,double> T2;
	BHeap<int,double> T3;
	BHeap<double,int> T4;
	BHeap<string,string> T5;
	BHeap<string,int> T6;
	BHeap<int,string> T7;
	BHeap<string,double> T8;
	BHeap<double,string> T9;
	BHeap<long,long> T10;
	cout << "test passed..." << endl;
}

void test8()
{
	const int size = 10;
	int k[size];
	int v[size];
	cout << "Building Binomial Heap via default constructor" << endl;
	BHeap<int,int> T1;
	for(int i=size-1; i>=0; i--){
		T1.insert(i,i);
	}
	cout << "success..." << endl;
	cout << "Building Binomial Heap via alternate constructor" << endl;
	int j = 9;
	for(int i=0; i<size; i++){
		k[i] = j-i;
		v[i] = j-i;
	}
	BHeap<int,int> T2(k,v,size);
	cout << "success..." << endl << endl;
	cout << "Printing Keys for both Heaps..." << endl;
	cout << "Default:" << endl;
	T1.printKey();
	cout << endl;
	cout << "Alternate:" << endl;
	T2.printKey();

	cout << "Testing minimum on default BHeap" << endl;
	cout << "key: " << T1.peekKey() << endl;
	cout << "value: " << T1.peekValue() << endl;
	cout << "Exctracting min..." << endl;
	cout << T1.extractMin() << endl;
	cout << "Printing key..." << endl;
	T1.printKey();

	cout << "Testing minimum on alternate BHeap" << endl;
	cout << "key: " << T2.peekKey() << endl;
	cout << "value: " << T2.peekValue() << endl;
	cout << "Exctracting min..." << endl;
	cout << T2.extractMin() << endl;
	cout << "Printing key..." << endl;
	T2.printKey();
}

void test9()
{
	cout << "Creating Binomal Heap via default contructor..." << endl;
	const int size = 10;
	BHeap<int,int> T1;
	for(int i=size; i>=1; i--){
		T1.insert(i,i);
	}
	cout << "Printing original heap:" << endl;
	T1.printKey();
	cout << "Testing copy constructor..." << endl;
	foo1(T1);
	cout << "Printing original heap:" << endl;
	T1.printKey();
	
	BHeap<int,int> T2;
	cout << endl << "Testing copy assignment operator..." << endl;
	T2 = T1;
	cout << "Extracting min: " << T2.extractMin() << endl;
	cout << "Printing modified heap:" << endl;
	T2.printKey();
	cout << "Printing original heap:" << endl;
	T1.printKey();
}

void test10()
{
	cout << "Creating Binomial Heap from secondary constructor..." << endl;
	const int size = 10;
	int k[size];
	int v[size];
	int j = 9;
	for(int i=0; i<size; i++){
		k[i] = j-i;
		v[i] = j-i;
	}
	BHeap<int,int> T2(k,v,size);
	cout << "Printing original heap:" << endl;
	T2.printKey();
	cout << "Testing copy constructor..." << endl;
	foo1(T2);
	cout << "Printing original heap:" << endl;
	T2.printKey();
	
	BHeap<int,int> T1;
	cout << endl << "Testing copy assignment operator..." << endl;
	T1 = T2;
	cout << "Extracting min: " << T1.extractMin() << endl;
	cout << "Printing modified heap:" << endl;
	T1.printKey();
	cout << "Printing original heap:" << endl;
	T2.printKey();
}

void test11()
{
	cout << "creating big Binomal Heap using default contructor..." << endl;
	const int size = 1000;
	BHeap<int,int> T1;
	for(int i=size-1; i>=0; i--){
		T1.insert(i,i);
	}
	if(LARGE_HEAP_PRINT){
		cout << "success! printing tree..." << endl;
		T1.printKey(); cout << endl;
	}
	cout << "removing everything..." << endl << endl;
	int key = 0;
	for(int i=0; i<size; i++){
		key = T1.extractMin();
		if(key != i){
			cout << "Error: i=" << i << " but key=" << key << endl;
		}
		if(size <= 10){
			T1.printKey();
		}
	}
	cout << "success!" << endl;
}

void test12()
{
	cout << "creating big Binomial Heap using secondary contructor..." << endl;
	const int size = 1000;
	int k[size];
	int v[size];
	for(int i=0; i < size; i++){
		k[i] = size-(i+1);
		v[i] = size-(i+1);
	}
	BHeap<int,int> T1(k,v,size);
	if(LARGE_HEAP_PRINT){
		cout << "success! printing tree..." << endl;
		T1.printKey();
	}
	cout << "removing everything..." << endl << endl;
	int key = 0;
	for(int i=0; i<size; i++){
		key = T1.extractMin();
		if(key != i){
			cout << "Error: i=" << i << " but key=" << key << endl;
		}
		if(size <= 10){
			T1.printKey();
		}
	}
	cout << endl << "success!" << endl;
}

void test13()
{
	cout << "creating Binomal Heap using default contructor..." << endl;
	const int size = 10;
	BHeap<int,int> T1;
	for(int i=0; i<size; i++){
		T1.insert(i,i);
	}
	cout << "success! Printing Heap:" << endl;
	T1.printKey(); cout << endl;

	cout << "creating Binomial Heap using secondary contructor..." << endl;
	int k[size];
	int v[size];
	for(int i=size; i < size*2; i++){
		k[i-size] = i;
		v[i-size] = i;
	}
	BHeap<int,int> T2(k,v,size);
	cout << "success! Printing Heap:" << endl;
	T2.printKey(); cout << endl;
	
	cout << "merging heaps..." << endl;
	T1.merge(T2);
	cout << "success! Printing Heap:" << endl;
	T1.printKey();

	cout << "Testing copy constructor..." << endl;
	foo1(T1);
	cout << "Printing original heap:" << endl;
	T1.printKey();
	
	cout << endl << "Testing copy assignment operator..." << endl;
	T2 = T1;
	cout << "Printing copied heap:" << endl;
	T2.printKey();
	cout << "Extracting min: " << T2.extractMin() << endl;
	cout << "Printing modified heap:" << endl;
	T2.printKey();
	cout << endl << "Printing original heap:" << endl;
	T1.printKey();
}

void test14()
{
	const int size = 10000; //The size of the array (o...n) inclusive
	const int moveBy = 7; 	//determines the space between inserts E.g [0,3,6,9,12]
	Heap<int,int> T1;
	cout << "Attempting to break Binary Heap..." << endl << endl;
	cout << "Inserting using default constructor..." << endl;
	for(int i=0; i<moveBy; i++){
		for(int j=i; j<=size; j = j+moveBy){
			T1.insert(j,j);
		}
	}
	if(LARGE_HEAP_PRINT){
		cout << "printing heap..." << endl;
		T1.printKey(); cout << endl;
	}
	
	cout << "Removing all minimums..." << endl;
	int key;
	for(int i=0; i<=size; i++){
		key = T1.extractMin();
		if(key != i){
			cout << "Error: i=" << i << " but key=" << key << endl;
		}
		if(size <= 10){
			T1.printKey();
		}
	}
	cout << "passed..." << endl << endl;

	cout << "Inserting using secondary constructor..." << endl;
	int k[size+1];
	int v[size+1];
	int l = 0;
	for(int i=0; i<moveBy; i++){
		for(int j=i; j<=size; j = j+moveBy){
			k[l] = j;
			v[l] = j;
			l++;
		}
	}
	Heap<int,int> T2(k,v,size+1);
	if(LARGE_HEAP_PRINT){
		cout << "printing heap..." << endl;
		T2.printKey(); cout << endl;
	}

	cout << "removing all minimums..." << endl;
	for(int i=0; i<=size; i++){
		key = T2.extractMin();
		if(key != i){
			cout << "Error: i=" << i << " but key=" << key << endl;
		}
		if(size <= 10){
			T2.printKey();
		}
	}
	cout << "passed..." << endl << endl;

	cout << "Inserting nodes again..." << endl;
	for(int i=0; i<moveBy; i++){
		for(int j=i; j<=size; j = j+moveBy){
			T1.insert(j,j);
		}
	}
	for(int i=0; i<moveBy; i++){
		for(int j=i; j<=size; j = j+moveBy){
			T2.insert(j,j);
		}
	}
	cout << "Success!" << endl;
	if(LARGE_HEAP_PRINT){
		cout << "printing heaps..." << endl;
		cout << "T1:" << endl; T1.printKey(); cout << endl;
		cout << "T2:" << endl; T2.printKey(); cout << endl;
	}
}

void test15()
{
	const int size = 10000; //The size of the array (o...n) inclusive
	const int moveBy = 13; 	//determines the space between inserts E.g [0,3,6,9,12]
	BHeap<int,int> T1;
	cout << "Attempting to break Binomial Heap..." << endl << endl;
	cout << "Inserting using default constructor..." << endl;
	for(int i=0; i<moveBy; i++){
		for(int j=i; j<size; j = j+moveBy){
			T1.insert(j,j);
		}
	}
	if(LARGE_HEAP_PRINT){	
		cout << "printing heap..." << endl;
		T1.printKey(); cout << endl;
	}
	
	cout << "removing all minimums..." << endl;
	int key;
	for(int i=0; i<size; i++){
		key = T1.extractMin();
		if(key != i){
			cout << "Error: i=" << i << " but key=" << key << endl;
		}
		if(size <= 10){
			//cout << "Tree:" << endl; T1.printKey();
		}
	}
	cout << "passed..." << endl << endl;
	
	cout << "Inserting using secondary constructor..." << endl;
	int k[size+1];
	int v[size+1];
	int l = 0;
	for(int i=size; i<moveBy+size; i++){
		for(int j=i; j<=size*2; j = j+moveBy){
			k[l] = j;
			v[l] = j;
			l++;
		}
	}
	BHeap<int,int> T2(k,v,size+1);
	if(LARGE_HEAP_PRINT){
		cout << "printing heap..." << endl;
		T2.printKey(); cout << endl;
	}

	cout << "removing all minimums..." << endl;
	for(int i=size; i<=size*2; i++){
		key = T2.extractMin();
		if(key != i){
			cout << "Error: i=" << i << " but key=" << key << endl;
		}
		if(size <= 10){
			T2.printKey();
		}
	}
	cout << "passed..." << endl << endl;

	cout << "Rebuilding heaps using insert..." << endl;
	for(int i=0; i<moveBy; i++){
		for(int j=i; j<size; j = j+moveBy){
			T1.insert(j,j);
		}
	}
	for(int i=size; i<moveBy+size; i++){
		for(int j=i; j<=size*2; j = j+moveBy){
			T2.insert(j,j);
		}
	}
	cout << "success!" << endl << endl;

	cout << "Merging both heaps..." << endl;
	T1.merge(T2);
	cout << "Success!" << endl << endl;
	if(LARGE_HEAP_PRINT){
		cout << "Printing union:" << endl;
		T1.printKey(); cout << endl;
	}

	cout << "Removing all minimums..." << endl;
	for(int i=0; i<=size*2; i++){
		key = T1.extractMin();
		if(key != i){
			cout << "Error: i=" << i << " but key=" << key << endl;
		}
		if(size <= 10){
			T1.printKey();
		}
	}
	cout << "passed..." << endl;
}