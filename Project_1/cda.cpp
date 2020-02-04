#include<cstdlib>

#define MIN_CAPACITY 1 //array will never go below this capacity
#define MULTIPLIER 2 //capacity of array is doubled when 100%, halved when 25% used
#define INSERTION_THRESHOLD 68 //quicksort insertion-sort threshold

using namespace std;
 
template <class data_type>
class CDA
{
    private:
        bool ordered;
        int size;  //size of the data
        int capacity;  //capacity of the data
        int front_index;
        int index_offset;
        data_type* data;  //pointer to data data
        data_type spam;
        void resize(int mode);
        data_type quickselect(int left, int right, int k);
        void quicksort(int left, int right);
        void insertionsort(int left, int right);
        int partition(int left, int right, int part);
        void swap(int left, int right);
        void median(int left, int right);
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
        bool operator==(const CDA &a2);
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
    capacity = MIN_CAPACITY;
    size = 0;
    front_index = 0;
    index_offset = 1;
    ordered = false;
    data = new data_type[capacity];
}

// constructor
template <class data_type>
CDA<data_type>::CDA(int cap) {
    capacity = cap;
    size = cap;
    front_index = 0;
    index_offset = 1;
    ordered = false;
    data = new data_type[capacity];
    for(int i = 0;i<capacity;i++){
        data[i] = 0;
    }
}

// copy constructor
template <class data_type>
CDA<data_type>::CDA(const CDA &a2) {
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
    delete [] data;
}

// *******member functions*******
template <class data_type>
void CDA<data_type>::AddEnd(data_type value) {
    //check if data is already full
    if(size >= capacity) {
        resize(1);
    }
    //     8        0       1
    data[(size-index_offset+1)%capacity] = value;
    size++;
    SetOrdered();
}

template <class data_type>
void CDA<data_type>::AddFront(data_type value) { 
    if(size >= capacity) {
        resize(1);
    }
    front_index = capacity - index_offset;
    data[front_index % capacity] = value;
    size++;

    index_offset++;
    SetOrdered();
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
    //performs a deep copy of the class object
    if(this == &a2)
        return;
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
}

template <class data_type>
bool CDA<data_type>::operator==(const CDA &a2) {
    //checks if the address is the same, only works for objt == objt
    if(this == &a2)
        return true;
    //check all values related to the class now
    if(ordered != a2.ordered)
        return false;
    if(size != a2.size)
        return false;
    if(front_index !=a2.front_index)
        return false;
    if(index_offset!=a2.index_offset)
        return false;
    return true;
}

template <class data_type>
void CDA<data_type>::DelEnd() {
    if(size == 0)
        return;
    data[(size - index_offset) % capacity] = 0;
    size--;

    if(size == capacity/4){
        resize(0);
    }
    return;
}

template <class data_type>
void CDA<data_type>::DelFront() {
    if(size == 0)
        return;
    data[front_index] = 0;
    front_index  = (front_index + 1) % capacity;
    index_offset --;
    size --;

    if(size == capacity/4){
        resize(0);
    }
    return;
}

template <class data_type>
int CDA<data_type>::Length() {
    return size;
}

template <class data_type>
int CDA<data_type>::Capacity() {
    return capacity;
}

template <class data_type>
void CDA<data_type>::Clear() {
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
    return ordered;
}

template <class data_type>
int CDA<data_type>::SetOrdered() {
    ordered = true;
    for(int i = 0; i< size - 1; i++){
        if((*this)[i]>(*this)[i+1]){
            ordered = false;
            return -1;
        }
    }
    return 1;
}

template <class data_type>
data_type CDA<data_type>::Select(int choice) { 
    if(ordered == true){
        return (*this)[choice - 1];
    }
    else{
        //quickselect is going to mess up the order, so make a 'backup' before
        data_type *new_data;
        new_data = new data_type[capacity];      
        for (int i = 0; i<capacity;i++){
            new_data[i] = data[i];
        }
        data_type answer = quickselect(0, size - 1, choice);
        data = new_data;
        return answer;
    }
}

template <class data_type>
void CDA<data_type>::InsertionSort() { 
    insertionsort(0, size);
}

template <class data_type>
void CDA<data_type>::QuickSort() { 
    quicksort(0, size-1);
    ordered = true;
    index_offset = 1;
    front_index = 0;
}

template <class data_type>
void CDA<data_type>::CountingSort(int max_size) { 
    data_type *new_data2;

    new_data2 = new data_type[capacity];

    int Count_Array[max_size + 1];
    for(int i = 0;i<max_size + 1;i++){
        Count_Array[i] = 0;
    }
    for(int i = 0;i<size;i++){
        Count_Array[(*this)[i]]++;
    }
    for(int i = 1;i<max_size + 1;i++){
        Count_Array[i] = Count_Array[i] + Count_Array[i-1];
    }
    for(int i = 0;i<size;i++){
        new_data2[Count_Array[(*this)[i]]-1] = (*this)[i];
        --Count_Array[(*this)[i]];
    }
    ordered = true;
    index_offset = 1;
    front_index = 0;
    data = new_data2;
}

template <class data_type>
int CDA<data_type>::Search(data_type value) {
    if(ordered == true){
        int first = 0;
        int last = size;
        while(first <= last){
            int middle_element = first + (last - first)/2;
            if(value == (*this)[middle_element]){
                return middle_element;
            }
            else if(value > (*this)[middle_element]){
                first = middle_element + 1;
            }
            else{
                last = middle_element - 1;
            }    
        }
    }
    else{
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
    }
}

template <class data_type>
void CDA<data_type>::display_array() {
    // method used for testing, displays current "back end" array
    cout<<"offset: "<<index_offset<<" size: "<<size<<" capacity: "<<capacity<<" current data array: ";
    for(int i = 0;i<capacity;i++){
        cout<<" "<<data[i]<<" ";
    }
    cout<<endl;
}

template <class data_type>
data_type CDA<data_type>::quickselect(int left, int right, int k) {
    //i want the k smallest element 
    // 1 3 5 7 9
    // k=2--->3
    int random = rand()%(right-left + 1) + left;
    int part = partition(left, right, random);

    if(k == part)
        return data[k];
    else if(k < part)
        return quickselect(left, part - 1,k);
    else
        return quickselect(part+1, right, k);
}

template <class data_type>
void CDA<data_type>::quicksort(int left, int right) {
    if(left < right){
        median(left,right);
        int part = partition(left, right, right);
        quicksort(left, part - 1);
        quicksort(part + 1, right);
    }
    return;
}

template <class data_type>
int CDA<data_type>::partition(int left, int right, int part){ 
    data_type pivot = data[right];
    int i = left;

    for(int j = left;j < right;j++){
        if(data[j]<pivot){
            swap(i,j);
            i++;
        }
    }
    swap(i,right);
    return(i);
}

template <class data_type>
void CDA<data_type>::median(int left, int right) { 
	int mid = (left+right)/2;
    if(data[right] < data[left])
        swap(left, right);
    if(data[mid] < data[left])
        swap(left, mid);
    if(data[right] < data[mid])
        swap(mid, right);
    //so now we know the middle value is in the middle
    //now move the middle value to the end and do a normal quick sort
    swap(mid, right);
}

template <class data_type>
void CDA<data_type>::swap(int left, int right) {
    //takes in left and right INDEX, and swaps their VALUES 
    data_type tmp;

    tmp = data[left];
    data[left] = data[right];
    data[right] = tmp;
}

template <class data_type>
void CDA<data_type>::insertionsort(int left, int right) {
    int left_index = left;
    data_type key;
    for(int i = left_index + 1; i < right; i++ ){
        key = (*this)[i];
        left_index = i - 1;
        while(left_index >= 0 && (*this)[left_index] > key)
        {
            (*this)[left_index + 1] = (*this)[left_index];
            left_index = left_index - 1;
        }
        (*this)[left_index + 1] = key;
    }
    ordered = true;
}
