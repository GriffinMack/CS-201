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
        int front_index;
        int index_offset;
        data_type* data;  //pointer to array data
        data_type spam;
        void resize(int mode);
        void display_array();

    public:
        // default constructor
        CDA();
        // constructor
        CDA(int);
        //copy constructor
        CDA(const CDA &a2);
        // destructor
        ~CDA();

        // methods
        data_type Data(data_type);
        data_type& operator[](int index);
        void operator=(const CDA &a2);
        void AddEnd(data_type);
        void AddFront(data_type);
        void DelEnd();
        void DelFront();
        int Length();
        int Capacity();
        void Clear();
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
    front_index = 0;
    index_offset = 1;
    ordered = false;
    data = new data_type[capacity];

    //for testing purposes, fill all elements with 0
    for(int i = 0;i<capacity;i++){
        data[i] = 0;
    }
}
// constructor
template <class data_type>
CDA<data_type>::CDA(int cap) {
    cout<<"Constructor, allocating."<<endl;
    capacity = cap;
    size = cap;
    front_index = 0;
    index_offset = 1;
    ordered = false;
    data = new data_type[capacity];

    //for testing purposes, fill all elements with 0
    for(int i = 0;i<capacity;i++){
        data[i] = 0;
    }
}

// copy constructor
template <class data_type>
CDA<data_type>::CDA(const CDA &a2) {
    cout<<"Copy Constructor, Copying."<<endl;
    ordered = a2.ordered;
    size = a2.size;
    capacity = a2.capacity;
    front_index = a2.front_index;
    index_offset = a2.index_offset;

    data = new data_type[capacity];
    for(int i = 0;i<capacity;i++){
        data[i] = a2.data[i];
    }
}
// destructor
template <class data_type>
CDA<data_type>::~CDA() {
    cout<<"Destructor, unallocating"<<endl;
    delete [] data;
}

// *******member functions*******
template <class data_type>
void CDA<data_type>::AddEnd(data_type value) {
    cout<<"Adding value to end"<<endl;
    //check if array is already full
    if(size >= capacity) {
        resize(1);
    }
    data[size-index_offset+1] = value;
    size++;
    display_array();     
}

template <class data_type>
void CDA<data_type>::AddFront(data_type value) { 
    cout<<"Adding value to front"<<endl;
    if(size >= capacity) {
        resize(1);
    }
    front_index = capacity - index_offset;
    data[front_index] = value;
    size++;

    index_offset++;
    display_array();      
}

template <class data_type>
data_type& CDA<data_type>::operator[](int value) {
    if(value < capacity){
        return data[(capacity + (value + 1 - index_offset))% capacity];
    }
    return spam;
    
}
template <class data_type>
void CDA<data_type>::operator=(const CDA &a2) {
    cout<<"Copy Constructor, Copying."<<endl;
    ordered = a2.ordered;
    size = a2.size;
    capacity = a2.capacity;
    front_index = a2.front_index;
    index_offset = a2.index_offset;

    data = new data_type[capacity];
    *data = *a2.data;
    for(int i = 0;i<capacity;i++){
        data[i] = a2.data[i];
    }
    
    // //for testing purposes, fill all elements with 0
    // for(int i = 0;i<capacity;i++){
    //     data[i] = value.data[i];
    // }
    // return 
}

template <class data_type>
void CDA<data_type>::DelEnd() {    
    cout<<"Deleting value from end"<<endl;
    data[size - index_offset] = 0;
    size--;
    display_array();

    if(size == capacity/4){
        resize(0);
    }
    return;
}

template <class data_type>
void CDA<data_type>::DelFront() {
    cout<<"Deleting value from front"<<endl;
    data[front_index] = 0;
    front_index  = (front_index + 1) % capacity;
    index_offset --;
    size --;
    display_array();

    if(size == capacity/4){
        resize(0);
    }

    return;
}

template <class data_type>
int CDA<data_type>::Length() {
    cout<<"Displaying length "<<front_index <<endl;
    return size;
}

template <class data_type>
int CDA<data_type>::Capacity() {
    cout<<"Displaying capacity"<<endl;
    return capacity;
}

template <class data_type>
void CDA<data_type>::Clear() {
    cout<<"erasing array"<<endl;
    ordered = false;
    size = 0;
    capacity = 1;
    front_index = 0;
    index_offset = 1;
    delete [] data;
    data = new data_type[capacity];

}

template <class data_type>
bool CDA<data_type>::Ordered() {
    cout<<"displaying ordered status"<<endl;
    return ordered;
}

template <class data_type>
int CDA<data_type>::SetOrdered() {
    cout<<"checking if array is ordered"<<endl;
    ordered = true;
    for(int i = 0; i< capacity - 1 && ordered == true; i++){
        if((*this)[i]>(*this)[i+1]){
            ordered = false;
            return -1;
        }
    }
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
void CDA<data_type>::CountingSort(int max_size) { 
    cout<<"sorting array using CountingSort"<<endl;
    //data[] array to sort
    int Count_Array[max_size];

    //initialize counting array to 0
    for (int i = 0;i<max_size;i++){
        Count_Array[i] = 0;
    }


    return;
}

template <class data_type>
int CDA<data_type>::Search(data_type value) { 
    if(ordered == true){
        cout<<"searching using binary search"<<endl;
        int first = 0;
        int last = capacity - 1;
        while(first <= last){
            // Compare value with the middle element.
            int middle_element = first + (last - first)/2;
            if(value == (*this)[middle_element]){
                // If value matches with middle element, we return the mid index.
                return middle_element;
            }
            // Else If value is greater than the mid element, then value can only lie in right half subarray after the mid element. So we recur for right half.
            else if(value > (*this)[middle_element]){
                first = middle_element + 1;
            }
            // Else (value is smaller) recur for the left half.
            else{
                last = middle_element - 1;
            }    
        }
    }
    else{
        cout<<"searching linearly for: "<< value<<endl;
        for(int i = 0; i< capacity;i++){
            if((*this)[i] == value){
                return i;
            }
        }
    }
    return -1;       
}

template <class data_type>
void CDA<data_type>::resize(int mode) { 
    if (mode == 0){
        data_type *new_data;
        int new_capacity = capacity / MULTIPLIER;
        new_data = new data_type[new_capacity];        

        for (int i = 0; i<new_capacity;i++){
            new_data[i] = (*this)[i];
        }

        capacity = new_capacity;
        data = new_data;
        front_index = 0;
        index_offset = 1;
        display_array();

    }
    if (mode == 1){
        data_type *new_data;
        int new_capacity = capacity * MULTIPLIER;
        new_data = new data_type[new_capacity];

        for (int i = 0; i<capacity;i++){
            new_data[i] = (*this)[i];
        }

        capacity = new_capacity;
        data = new_data;
        front_index = 0;
        index_offset = 1;
        display_array();
    }
}

template <class data_type>
void CDA<data_type>::display_array() { 
    cout<<"front_index:"<<front_index<<" index offset:"<<index_offset<<" size:"<<size<<" capacity:"<<capacity<<endl;
    for(int i = 0;i<capacity;i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
}


int main() 
{
    CDA <int> objt;


    
    objt.AddEnd(1);
    objt.AddEnd(2);
    objt.AddEnd(3);
    objt.AddEnd(4);
    objt.AddEnd(5);
    objt.AddEnd(6);
    objt.AddEnd(7);
    objt.AddEnd(8);

    CDA <int> objt2;

    objt2 = objt;

    //TODO: == EQUAL OPERATOR
    if(objt2 == objt){
        cout<<"here"<<endl;
    }


    //     objt.AddEnd(5);
    //     objt.AddFront(6);
    //     objt.AddFront(7);
    //     objt.AddFront(8);
    //     objt.AddFront(9);

    //     // for(int i = 1;i<15;i++){
    //     //     objt.AddFront(i);
    //     // }

    // cout<<objt.Length()<<endl;
    // cout<<objt.Capacity()<<endl;
    // cout<<objt.Ordered()<<endl;

    // CDA <int> objt2 = objt;

    // cout<<objt2.Length()<<endl;
    // cout<<objt2.Capacity()<<endl;
    // cout<<objt2.Ordered()<<endl;

    // objt.AddEnd(1);
    // objt.AddEnd(2);
    // objt.AddEnd(3);
    // objt.AddEnd(4);

    // objt.AddEnd(5);
    // objt.AddFront(6);
    // objt.AddFront(7);
    // objt.AddFront(8);
    // objt.AddFront(9);
    // objt.DelEnd();
    // objt.DelEnd();
    // objt.DelEnd();
    // objt.DelEnd();
    // objt.DelEnd();
    // objt.DelEnd();
    // objt.DelEnd();
    // objt.DelEnd();
    // objt.AddFront(5);
    // objt.AddFront(6);
    // objt.AddFront(7);
    // objt.AddEnd(8);
    // objt.AddFront(9);
    // objt.DelFront();

    cout<<objt.SetOrdered()<<endl;
    cout<<objt.Search(1)<<endl;



    objt.Clear();
    return 0;
}



