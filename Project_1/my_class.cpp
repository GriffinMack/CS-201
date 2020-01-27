#include<iostream>
#include <string>

#define MIN_CAPACITY 1
#define MULTIPLIER 2

using namespace std;
 
template <class data_type>
class CDA
{
    private:
        bool ordered;
        int size;  //size of the array
        int capacity;  //capacity of the array
        int* data;  //pointer to array data

    public:
        // default constructor
        CDA();
        // constructor
        CDA(int);
        // destructor
        ~CDA();

        // methods
        data_type Data(data_type);
        //data_type& operator[](int);
        void AddEnd(data_type);
        void AddFront(data_type);
        void DelEnd();
        void DelFront();
        int Length();
        int Capacity();
        int Clear();
        bool Ordered();
        int SetOrdered();
        data_type Select(int);
        void InsertionSort();
        void QuickSort();
        void CountingSort(int);
        int Search(data_type);
};
// default constructor
template <class data_type>
CDA<data_type>::CDA() {
    cout<<"Constructor, allocating."<<endl;
    capacity = MIN_CAPACITY;
    size = 0;
    data = (data_type*)malloc(capacity * sizeof(data));
}
// constructor
template <class data_type>
CDA<data_type>::CDA(int size) {
    cout<<"Constructor, allocating."<<endl;
    capacity = size;
    size = size;
    data = (data_type*)malloc(capacity * sizeof(data));
}
// destructor
template <class data_type>
CDA<data_type>::~CDA() {
    cout<<"Destructor, unallocating"<<endl;
    free(data);
}

// *******member functions*******
template <class data_type>
void CDA<data_type>::AddEnd(data_type) {
    cout<<"Adding value to end"<<endl;
    if(size>=)
    return;       
}

template <class data_type>
void CDA<data_type>::AddFront(data_type) { 
    cout<<"Adding value to front"<<endl;
    return;       
}

template <class data_type>
void CDA<data_type>::DelEnd() {    
    cout<<"Deleting value from end"<<endl;
    return;
}

template <class data_type>
void CDA<data_type>::DelFront() {
    cout<<"Deleting value from front"<<endl;
    return;
}

template <class data_type>
int CDA<data_type>::Length() {
    cout<<"Displaying length"<<endl;
    return size;
}

template <class data_type>
int CDA<data_type>::Capacity() {
    cout<<"Displaying capacity"<<endl;
    return capacity;
}

template <class data_type>
int CDA<data_type>::Clear() {
    cout<<"erasing array"<<endl;
    return 1;
}

template <class data_type>
bool CDA<data_type>::Ordered() {
    cout<<"displaying ordered status"<<endl;
    return false;
}

template <class data_type>
int CDA<data_type>::SetOrdered() {
    cout<<"checking if array is ordered"<<endl;
    return 1;
}

template <class data_type>
data_type CDA<data_type>::Select(int choice) { 
    cout<<"returning kth smallest element in array"<<endl;
    return;       
}

template <class data_type>
void CDA<data_type>::InsertionSort() { 
    cout<<"sorting array using Insertion Sort"<<endl;
    return;       
}

template <class data_type>
void CDA<data_type>::QuickSort() { 
    cout<<"sorting array using Quick Sort"<<endl;
    return;       
}

template <class data_type>
void CDA<data_type>::CountingSort(int size) { 
    cout<<"sorting array using CountingSort"<<endl;
    return;       
}

template <class data_type>
int CDA<data_type>::Search(data_type) { 
    cout<<"searching for desired element"<<endl;
    return 1;       
}

int main() 
{
    CDA <int> objt(400);

    cout<<objt.Length()<<endl;
    cout<<objt.Capacity()<<endl;

    return 0;
}



