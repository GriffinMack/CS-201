#include "CDA.cpp"
#include <cstdlib>

//each item inserted has a key and a value
//  key - determines spot in the heap
//  value - value that the key holds
using namespace std;

template <class keytype, class valuetype>
class Heap
{
private:
    void buildHeap(keytype k[], valuetype v[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            //create a node with the key and value pair
            Node *node = new Node();
            node->key = k[i];
            node->value = v[i];

            //add node to the CDA
            storage.AddEnd(node);
            currentSize++;
        }
        for (int i = (size - 1) / 2; i >= 0; i--)
        {
            maxHeapify(i, size - 1);
        }
    }

    void maxHeapify(int i, int size)
    {
        int left = (2 * i) + 1;
        int right = (2 * i) + 2;
        int largest = 0;

        if (left <= size && storage[left]->key > storage[i]->key)
        {
            largest = left;
        }
        else
            largest = i;
        if (right <= size && storage[right]->key > storage[largest]->key)
        {
            largest = right;
        }
        if (largest != i)
        {
            exchange(i, largest);
            maxHeapify(largest, size);
        }
    }

    void exchange(int i, int j)
    {
        //exchanges node* stored at i for j and vice versa
        Node *temp = storage[i];
        storage[i] = storage[j];
        storage[j] = temp;
    }

    void printArray()
    {
        //prints the current array's keys
        for (int i = 0; i < currentSize; i++)
        {
            cout << storage[i]->key << " ";
        }
        cout << endl;
    }

public:
    struct Node
    {
        //data about the node(value and key represent two seperate data entries ex. CWID and Name)
        valuetype value;
        keytype key;

        //constructor for the Node(called when inserting)
        Node()
        {
            value = "0";
            key = 0;
        }
    };

    CDA<Node *> storage;
    int currentSize;
    // default constructor
    Heap();
    // argument constructor
    Heap(keytype k[], valuetype V[], int size);
    ~Heap();

    valuetype peekValue();
    keytype peekKey();
    keytype extractMin();
    void insert(keytype k, valuetype v);
    void printKey();
};

// default constructor
template <class keytype, class valuetype>
Heap<keytype, valuetype>::Heap()
{
}

// argument constructor
template <class keytype, class valuetype>
Heap<keytype, valuetype>::Heap(keytype k[], valuetype v[], int size)
{
    currentSize = 0;
    buildHeap(k, v, size);
}

// destructor
template <class keytype, class valuetype>
Heap<keytype, valuetype>::~Heap()
{
}

template <class keytype, class valuetype>
valuetype Heap<keytype, valuetype>::peekValue()
{
}

template <class keytype, class valuetype>
keytype Heap<keytype, valuetype>::peekKey()
{
}

template <class keytype, class valuetype>
keytype Heap<keytype, valuetype>::extractMin()
{
}

template <class keytype, class valuetype>
void Heap<keytype, valuetype>::insert(keytype k, valuetype v)
{
}

template <class keytype, class valuetype>
void Heap<keytype, valuetype>::printKey()
{
}