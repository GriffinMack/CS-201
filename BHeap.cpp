#include "CDA.cpp"
#include <cstdlib>

using namespace std;

template <class keytype, class valuetype>
class BHeap
{
public:
    struct Node
    {
        //data about a node(value and key represent two seperate data entries ex. CWID and Name)
        valuetype value;
        keytype key;
        int degree;

        Node *child;
        Node *sibling;
        Node *parent;
    };
    CDA<Node *> heap;

private:
    Node *newNode(keytype k, valuetype v)
    {
        //creates a new Node
        Node *temp = new Node();
        temp->key = k;
        temp->value = v;
        temp->degree = 0;

        temp->child = NULL;
        temp->sibling = NULL;
        temp->parent = NULL;

        return temp;
    }

    Node *mergeNodes(Node *n1, Node *n2)
    {
        //make sure that n1 is always smaller
        if (n1->key > n2->key)
        {
            Node *temp = n1;
            n1 = n2;
            n2 = temp;
        }

        //make the larger tree a child of the smaller tree
        n2->parent = n1;
        n2->sibling = n1->child;
        n1->child = n2;
        n1->degree++;

        //n1 now contains both nodes
        return n1;
    }

    void insertTreeIntoHeap(Node *tree)
    {
        // creating a new heap
        CDA<Node *> temp;
        // inserting Binomial Tree into heap
        temp.AddEnd(tree);

        // perform union operation to insert Binomial Tree in original heap
        temp = unionBinomialHeap(heap, temp);

        temp = adjust(temp);

        heap = temp;
    }

    CDA<Node *> unionBinomialHeap(CDA<Node *> l1, CDA<Node *> l2)
    {
        //combines two binomial heaps into a new one
        CDA<Node *> _new;
        int it = 0;
        int ot = 0;
        while (it != l1.Length() && ot != l2.Length())
        {
            // if l1->degree <= l2->degree
            if (l1[it]->degree <= l2[ot]->degree)
            {
                _new.AddEnd(l1[it]);
                it++;
            }
            // if l1->degree > l2->degree
            else
            {
                _new.AddEnd(l2[ot]);
                ot++;
            }
        }

        // if there remains some elements in l1
        // binomial heap
        while (it != l1.Length())
        {
            _new.AddEnd(l1[it]);
            it++;
        }

        // if there remains some elements in l2
        // binomial heap
        while (ot != l2.Length())
        {
            _new.AddEnd(l2[ot]);
            ot++;
        }
        return _new;
    }

    CDA<Node *> adjust(CDA<Node *> _heap)
    {
        //adjusts heap to be valid
        //check if the heap is empty or has just one tree (A)
        if (_heap.Length() <= 1)
        {
            return _heap;
        }
        int prev_x = 0;
        int x = 0; //smallest order trees are at the end
        int next_x = 1;

        while (next_x <= _heap.Length() - 1)
        {
            //check if the orders of x and next-x are not the same(CASE 1)
            if (_heap[x]->degree != _heap[next_x]->degree)
            {
                // cout << "degrees not the same, moving on.." << endl;
            }
            else
            {
                if (next_x + 1 <= _heap.Length() - 1 && _heap[next_x + 1]->degree == _heap[x]->degree)
                {               //CASE 2
                    prev_x = x; //only if case 2 happens
                }
                else
                {                                                     //CASE 3 and 4
                    Node *temp = mergeNodes(_heap[x], _heap[next_x]); //creates a node of the next order
                    _heap = del(_heap, x);
                    _heap[x] = temp;
                    x--;
                    next_x--;
                }
            }
            x++;
            next_x++;
        }

        return _heap;
    }
    CDA<Node *> del(CDA<Node *> array, int i)
    {
        //deletes index i from the array
        if (i == 0)
        {
            array.DelFront();
        }
        else
        {
            for (int j = i; j < array.Length() - 1; j++)
            {
                array[j] = array[j + 1];
            }
            array.DelEnd();
        }
        return array;
    }
    Node *findMin()
    {
        //finds the minimum root in the heap
        Node *min = heap[0];
        for (int i = 1; i < heap.Length(); i++)
        {
            if (heap[i]->key < min->key)
                min = heap[i];
        }
        return min;
    }
    CDA<Node *> removeMinFromTree(Node *min)
    {
        //removes the minimum node from the tree and returns the tree
        CDA<Node *> new_heap;
        Node *temp = min->child;
        Node *lo;

        while (temp)
        {
            lo = temp;
            temp = temp->sibling;
            lo->sibling = NULL;
            new_heap.AddFront(lo);
        }
        return new_heap;
    }
    void printTree(Node *h)
    {
        //prints a tree
        while (h)
        {
            cout << h->key << " ";
            printTree(h->child);
            h = h->sibling;
        }
    }

    void copyTree(Node *old_tree, Node *new_tree_parent)
    {
        //copy given tree into current tree
        Node *sibling = NULL;
        while (old_tree)
        {
            Node *temp = newNode(old_tree->key, old_tree->value);
            temp->key = old_tree->key;
            temp->value = old_tree->value;
            temp->degree = old_tree->degree;
            if (new_tree_parent == NULL)
                heap.AddEnd(temp);

            temp->parent = new_tree_parent;
            if (new_tree_parent && sibling == NULL)
                new_tree_parent->child = temp;
            if (sibling)
            {
                sibling->sibling = temp;
                sibling = NULL;
            }
            copyTree(old_tree->child, temp);
            old_tree = old_tree->sibling;
            sibling = temp;
        }
    }

public:
    BHeap();
    BHeap(keytype k[], valuetype V[], int size);
    BHeap(BHeap &old_tree);
    void operator=(BHeap &a2);
    bool operator==(const BHeap &a2);
    ~BHeap();

    valuetype peekValue();
    keytype peekKey();
    keytype extractMin();
    void insert(keytype k, valuetype v);
    void merge(BHeap<keytype, valuetype> &H2);
    void printKey();
};

// default constructor
template <class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap()
{
    //nothing really needs to be done here
}

// argument constructor
template <class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap(keytype k[], valuetype v[], int size)
{
    for (int i = 0; i < size; i++)
    {
        insert(k[i], v[i]);
    }
}
//copy constructor
template <class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap(BHeap &heap2)
{
    for (int i = 0; i < heap2.heap.Length(); i++)
    {
        //for each root in the heap, copy all values
        copyTree(heap2.heap[i], NULL);
    }
}

template <class keytype, class valuetype>
void BHeap<keytype, valuetype>::operator=(BHeap &heap2)
{
    if (this == &heap2)
        return;
    for (int i = 0; i < heap.Length() + 1; i++)
    {
        //clear the current heap
        heap.DelEnd();
    }
    for (int i = 0; i < heap2.heap.Length(); i++)
    {
        //for each root in the heap, copy all values
        copyTree(heap2.heap[i], NULL);
    }
}

template <class keytype, class valuetype>
bool BHeap<keytype, valuetype>::operator==(const BHeap &heap2)
{
    //check if EVERY element of heap == heap2
    if (this == &heap2)
        return true;
}

// destructor
template <class keytype, class valuetype>
BHeap<keytype, valuetype>::~BHeap()
{
}

template <class keytype, class valuetype>
valuetype BHeap<keytype, valuetype>::peekValue()
{
    //return the minimum key's value without touching the heap
    return findMin()->value;
}

template <class keytype, class valuetype>
keytype BHeap<keytype, valuetype>::peekKey()
{
    //return the minimum key without touching the heap
    return findMin()->key;
}

template <class keytype, class valuetype>
keytype BHeap<keytype, valuetype>::extractMin()
{
    //return the minimum key and remove the key from the heap
    Node *min = findMin();
    CDA<Node *> new_heap;
    CDA<Node *> lo;
    for (int i = 0; i < heap.Length(); i++)
    {
        if (heap[i] != min)
        {
            new_heap.AddEnd(heap[i]);
        }
    }
    lo = removeMinFromTree(min);
    new_heap = unionBinomialHeap(new_heap, lo);
    new_heap = adjust(new_heap);

    heap = new_heap;
    return min->key;
}

template <class keytype, class valuetype>
void BHeap<keytype, valuetype>::insert(keytype k, valuetype v)
{
    //create a tree with the key and value pair
    Node *tree = newNode(k, v);

    //insert the tree node (which is a tree of order 0) into the heap
    insertTreeIntoHeap(tree);
}
template <class keytype, class valuetype>
void BHeap<keytype, valuetype>::merge(BHeap<keytype, valuetype> &H2)
{
    //merges input H2 into the heap
    heap = unionBinomialHeap(heap, H2.heap);
    heap = adjust(heap);
}
template <class keytype, class valuetype>
void BHeap<keytype, valuetype>::printKey()
{
    //prints the current array's keys
    for (int i = 0; i < heap.Length(); i++)
    {
        cout << "B" << heap[i]->degree << endl;
        printTree(heap[i]);
        cout << endl
             << endl;
    }
}
