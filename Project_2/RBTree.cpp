#include <cstdlib>

#define RED true
#define BLACK false
/*
Properties:
1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.
using namespace std;
*/
template <class keytype, class valuetype>
class RBTree
{
    struct Node
    {
        /*Each node of the tree now contains the attributes:
            color, key, value, left, right, and parent
    */
        //pointers to other nodes
        Node *parent;
        Node *leftChild;
        Node *rightChild;

        //data about the node(value and key represent two seperate data entries ex. CWID and Name)
        bool color;
        valuetype value;
        keytype key;

        //constructor for the Node(called when inserting)
        Node()
        {
            parent = NULL;
            leftChild = NULL;
            rightChild = NULL;

            color = RED;
        }
    };

private:
    //Tree variables
    Node *root; //points to the root node of the Tree
    Node *nil;
    int current_size; //keeps track of the current size of the Tree

    //private member functions
    void _insertFixup(Node *new_node);
    void _leftRotate(Node *node);
    void _rightRotate(Node *node);
    void _displayTree(Node *p);

public:
    // default constructor
    RBTree();
    // argument constructor
    RBTree(keytype k[], valuetype V[], int size);
    // destructor
    ~RBTree();

    void insert(keytype k, valuetype v);
    int remove(keytype k);
    int rank(keytype k);
    int size();
    valuetype *search(keytype k);
    keytype select(int pos);
    keytype *successor(keytype k);
    keytype *predecessor(keytype k);

    //traversals
    void preorder();
    void inorder();
    void postorder();
    void displayTree();
};

// default constructor
template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree()
{
    nil = new Node();
    nil->color = BLACK;
    root = nil; //begin with pointing to an empty tree
}

// argument constructor
template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype V[], int size)
{
    nil = new Node();
    nil->color = BLACK;
    root = nil; //begin with pointing to an empty tree
    for (int i = 0; i < size; i++)
    {
        insert(k[i], V[i]);
    }
}

// destructor
template <class keytype, class valuetype>
RBTree<keytype, valuetype>::~RBTree()
{
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::insert(keytype k, valuetype v)
{
    /*  inputs:
            -k (node.key)
            -v (node.key)
    description:
            -create a new node with the data given and insert into
                the tree. Remember to make any changes to the tree that
                this insert may cause
    output:
            -size of tree increased
            -new node inserted
            -tree follows all rules for RBT's
    */
    current_size++;
    Node *new_node = new Node();
    new_node->value = v;
    new_node->key = k;
    Node *current_node = root;
    Node *last_node = nil; //one node behind the current node
    if (root == nil)
    {
        root = new_node;
        new_node->parent = nil;
    }
    else
    {
        while (current_node != nil)
        {
            last_node = current_node;
            if (new_node->key < current_node->key)
            {
                current_node = current_node->leftChild;
            }
            else
            {
                current_node = current_node->rightChild;
            }
        }
        current_node = last_node;        //cleaning up the current node
        new_node->parent = current_node; //setting the parent node of new node
        if (new_node->key < current_node->key)
        {
            current_node->leftChild = new_node;
        }
        else
        {
            current_node->rightChild = new_node;
        }
    }
    new_node->leftChild = nil;
    new_node->rightChild = nil;
    _insertFixup(new_node);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_insertFixup(Node *new_node)
{
    /*violated properties
        property 2:which requires the root to be black
        property 4:which says that a red node cannot have a red child.
    */
    Node* uncle = NULL;
    while(new_node->parent->color == RED){
        if(new_node->parent == new_node->parent->parent->leftChild){ //checking if parent of new node is left or right child
            uncle = new_node->parent->parent->rightChild;  //brother of new node's parent
            if(uncle->color == RED){  //parent and uncle are both red (CASE 1)
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            else{
                if(new_node == new_node->parent->rightChild){ //uncle is black, parent is red, new_node is to the right(CASE 2)
                    new_node = new_node->parent;
                    _leftRotate(new_node);
                }
                new_node->parent->color = BLACK;              //uncle is black, parent is red, new_node is to the left(CASE 3)
                new_node->parent->parent->color = RED;
                _rightRotate(new_node->parent->parent);
            }
        }
        else{
            uncle = new_node->parent->parent->leftChild;
            if(uncle->color == RED){
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            else{
                if(new_node == new_node->parent->leftChild){
                    new_node = new_node->parent;
                    _rightRotate(new_node);
                }
                new_node->parent->color = BLACK;
                new_node->parent->parent->color = RED;
                _leftRotate(new_node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_leftRotate(Node *node)
{
    /*When we do a left rotation on a node x, 
      we assume that its right child y is not T:nil
        x                   y
      /   \               /   \
    a       y    ---->  x       c
          /   \       /   \
        b      c    a       b

    */
   Node* y = node->rightChild;
   node->rightChild = y->leftChild;
   if(y->leftChild != nil){
       y->leftChild->parent = node;
   }
   y->parent = node->parent;
   if(node->parent == nil){
       root = y;
   }
   else if(node==node->parent->leftChild){
       node->parent->leftChild = y;
   }
   else{
       node->parent->rightChild = y;
   }
   y->leftChild = node;
   node->parent = y;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_rightRotate(Node *node)
{
    /*When we do a left rotation on a node y, 
      we assume that its right child x is not T:nil
        x                   y
      /   \               /   \
    a       y    <----  x       c
          /   \       /   \
        b      c    a       b

    */
   Node* x = node->leftChild;
   node->leftChild = x->rightChild;
   if(x->rightChild != nil){
       x->rightChild->parent = node;
   }
   x->parent = node->parent;
   if(node->parent == nil){
       root = x;
   }
   else if(node==node->parent->rightChild){
       node->parent->rightChild = x;
   }
   else{
       node->parent->leftChild = x;
   }
   x->rightChild = node;
   node->parent = x;

}
// template <class keytype, class valuetype>
// int remove(keytype k);

// template <class keytype, class valuetype>
// int rank(keytype k);

// template <class keytype, class valuetype>
// int size();

// template <class keytype, class valuetype>
// valuetype *search(keytype k);

// template <class keytype, class valuetype>
// keytype select(int pos);

// template <class keytype, class valuetype>
// keytype *successor(keytype k);

// template <class keytype, class valuetype>
// keytype *predecessor(keytype k);

// //tree traversal algorithms
// template <class keytype, class valuetype>
// void preorder();
// template <class keytype, class valuetype>
// void inorder();
// template <class keytype, class valuetype>
// void postorder();
template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::displayTree()
{
    _displayTree(root);

}
template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_displayTree(Node *p)
{
     if(root==nil)
     {
          cout<<"\nEmpty Tree.";
          return ;
     }
     if(p!=nil)
     {
                cout<<"\n\t NODE: ";
                cout<<"\n Key: "<<p->key;
                cout<<"\n Colour: ";
    if(p->color==false)
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=nil)
                       cout<<"\n Parent: "<<p->parent->key;
                else
                       cout<<"\n There is no parent of the node.  ";
                if(p->rightChild!=nil)
                       cout<<"\n Right Child: "<<p->rightChild->key;
                else
                       cout<<"\n There is no right child of the node.  ";
                if(p->leftChild!=nil)
                       cout<<"\n Left Child: "<<p->leftChild->key;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;
    if(p->leftChild)
    {
                 cout<<"\n\nLeft:\n";
     _displayTree(p->leftChild);
    }
    /*else
     cout<<"\nNo Left Child.\n";*/
    if(p->rightChild)
    {
     cout<<"\n\nRight:\n";
                 _displayTree(p->rightChild);
    }
    /*else
     cout<<"\nNo Right Child.\n"*/
     }
}