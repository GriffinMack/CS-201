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
*/
using namespace std;

template <class keytype, class valuetype>
class RBTree
{
public:
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
        int size;

        //constructor for the Node(called when inserting)
        Node()
        {
            parent = NULL;
            leftChild = NULL;
            rightChild = NULL;

            color = RED;
            size = 1;
        }
    };

    //Tree variables
    Node *root; //points to the root node of the Tree
    Node *nil;
    int current_size; //keeps track of the current size of the Tree

    //private member functions
    void _insertFixup(Node *new_node);
    void _leftRotate(Node *node);
    void _rightRotate(Node *node);
    void _transplant(Node *root, Node *root_child);
    void _removeFixup(Node *);
    void _displayTree(Node *node);
    void _preorderWalk(Node *node);
    void _inorderWalk(Node *node);
    void _postorderWalk(Node *node);
    Node *_select(Node *node, int pos)
    {
        int rank = node->leftChild->size + 1;
        if (rank == pos)
            return node;
        else if (pos < rank)
            return _select(node->leftChild, pos);
        else
            return _select(node->rightChild, pos - rank);
    }
    Node *_minimum(Node *current_node)
    {
        while (current_node->leftChild != nil)
            current_node = current_node->leftChild;
        return current_node;
    }
    Node *_maximum(Node *current_node)
    {
        while (current_node->rightChild != nil)
            current_node = current_node->rightChild;
        return current_node;
    }
    Node *_search(keytype k)
    {
        /*returns the NODE with the key k*/
        Node *current_node = root;
        while (current_node != nil && k != current_node->key)
        {
            if (k < current_node->key)
                current_node = current_node->leftChild;
            else
                current_node = current_node->rightChild;
        }
        return current_node; //returns nil if not found
    }
    Node *_successor(Node *current_node)
    {
        /*returns the NODE successor of the current_node*/
        if (current_node->rightChild != nil)
            return _minimum(current_node->rightChild);
        Node *parent = current_node->parent;
        while (parent != nil && current_node == parent->rightChild)
        {
            current_node = parent;
            parent = parent->parent;
        }
        return parent;
    }
    Node *_predecessor(Node *current_node)
    {
        /*returns the NODE predecessor of the current_node*/
        if (current_node->leftChild != nil)
            return _maximum(current_node->leftChild);
        Node *parent = current_node->parent;
        while (parent != nil && current_node == parent->leftChild)
        {
            current_node = parent;
            parent = parent->parent;
        }
        return parent;
    }

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
    nil->size = 0;
    current_size = 0;
    root = nil; //begin with pointing to an empty tree
}

// argument constructor
template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype V[], int size)
{
    nil = new Node();
    nil->color = BLACK;
    nil->size = 0;
    current_size = 0;
    root = nil; //begin with pointing to an empty tree
    for (int i = 0; i < size; i++)
        insert(k[i], V[i]);
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
            current_node->size++; //increase the size for each node traversed
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
    Node *uncle = NULL;
    while (new_node->parent->color == RED)
    {
        if (new_node->parent == new_node->parent->parent->leftChild)
        {                                                 //checking if parent of new node is left or right child
            uncle = new_node->parent->parent->rightChild; //brother of new node's parent
            if (uncle->color == RED)
            { //parent and uncle are both red (CASE 1)
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            else
            {
                if (new_node == new_node->parent->rightChild)
                { //uncle is black, parent is red, new_node is to the right(CASE 2)
                    new_node = new_node->parent;
                    _leftRotate(new_node);
                }
                new_node->parent->color = BLACK; //uncle is black, parent is red, new_node is to the left(CASE 3)
                new_node->parent->parent->color = RED;
                _rightRotate(new_node->parent->parent);
            }
        }
        else
        {
            uncle = new_node->parent->parent->leftChild;
            if (uncle->color == RED)
            {
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            else
            {
                if (new_node == new_node->parent->leftChild)
                {
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
    Node *y = node->rightChild;
    node->rightChild = y->leftChild;
    if (y->leftChild != nil)
    {
        y->leftChild->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nil)
    {
        root = y;
    }
    else if (node == node->parent->leftChild)
    {
        node->parent->leftChild = y;
    }
    else
    {
        node->parent->rightChild = y;
    }
    y->leftChild = node;
    node->parent = y;
    //update size after the rotations
    y->size = node->size;
    node->size = node->leftChild->size + node->rightChild->size + 1;
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
    Node *x = node->leftChild;
    node->leftChild = x->rightChild;
    if (x->rightChild != nil)
    {
        x->rightChild->parent = node;
    }
    x->parent = node->parent;
    if (node->parent == nil)
    {
        root = x;
    }
    else if (node == node->parent->rightChild)
    {
        node->parent->rightChild = x;
    }
    else
    {
        node->parent->leftChild = x;
    }
    x->rightChild = node;
    node->parent = x;
    //update size after the rotations
    x->size = node->size;
    node->size = node->rightChild->size + node->leftChild->size + 1;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_transplant(Node *root, Node *root_child)
{
    /*replaces the subtree rooted at 'root' with the subtree rooted at 'root_child'
      outputs:
              u's parent is now v's parent
              u's parent has v as a child (which child depends on the situation)
    */
    if (root->parent == nil) //root is the root node in the tree
        root = root_child;
    else if (root == root->parent->left) //root is a left child
        root->parent->left = root_child;
    else //root is a right child
        root->parent->right = root_child;
    root_child->parent = root->parent; //update the parent of 'root_child' to be 'root' parent
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::remove(keytype k)
{
    /* 4 cases to think about:
            1. node to delete has no left child
                -handles when node to delete has no children, and when node to delete 
                 has one child to the right
                -replaces node to delete by its right child(could be nil)
            2. node to delete has 1 child and it is to the left
                -replaces node to delete by its left child
            3. node to delete has two children, and the successor 'successor'
               is the right child of the node to delete
                -replaces the node to delete by the successor node, and we leave 
                 the successor node's right subtree alone
            4. node to delete has two children, and the successor 'successor'
               is inside the right child of the node to delete, but not the child
                -replace the successor node by its own right child
                -replace the node to delete by the successor node
    */
    Node *node_to_delete = _search(k); //obtain a pointer to the node with key k
    Node *node_to_delete_child = NULL;
    if (node_to_delete == nil)
        return 0;

    Node *successor = node_to_delete;
    bool original_successor_color = successor->color; //keep track of color before any changes
    if (node_to_delete->leftChild == nil)             //node to delete has no left child
    {
        node_to_delete_child = node_to_delete->rightChild;
        _transplant(node_to_delete, node_to_delete_child); //replace node to delete by its right child(could be nil)
    }
    else if (node_to_delete->rightChild == nil) //node to delete has a left child but no right child
    {
        node_to_delete_child = node_to_delete->leftChild;
        _transplant(node_to_delete, node_to_delete_child);
    }
    else //node to delete has two children
    {
        successor = _minimum(node_to_delete->rightChild); //find the successor of the node to delete
        original_successor_color = successor->color;
        node_to_delete_child = successor->rightChild;
        if (successor->parent == node_to_delete)
            node_to_delete_child->parent = successor;
        else
        {
            _transplant(successor, node_to_delete_child);
            successor->rightChild = node_to_delete->rightChild;
            successor->rightChild->parent = successor;
        }
        _transplant(node_to_delete, successor);
        successor->leftChild = node_to_delete->leftChild; //successor has been moved into node to deletes spot
        successor->leftChild->parent = successor;
        successor->color = node_to_delete->color;
    }
    //if (original_successor_color == BLACK)  //some violations might of been introduced
    //_removeFixup(node_to_delete_child);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_removeFixup(Node *node_to_delete_child)
{
    /*Three problems may of come up in removing a node:
        1. If successor had been the root and a red child of successor becomes the new root, 
            we have violated property 2
        2. If both node to delete's child and node to delete's child's parent are red, 
            then we have violated property 4
        3. Moving successor within the tree causes any path that contained successor to have one
            fewer black node, violating property 5
    */
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::rank(keytype k)
{
    /* given a key, find the node with that key and return its rank
       in the tree (order in an in-order walk)
       returns:
                0 if not found
                1 if smallest item
    */
    Node *node_to_delete = _search(k);
    if (node_to_delete == nil)
        return 0;
    int r = node_to_delete->leftChild->size + 1;
    Node *y = node_to_delete;
    while (y != root)
    {
        if (y == y->parent->rightChild)
            r = r + y->parent->leftChild->size + 1;
        y = y->parent;
    }
    return r;
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::size()
{
    return current_size;
}

template <class keytype, class valuetype>
valuetype *RBTree<keytype, valuetype>::search(keytype k)
{
    return &_search(k)->value;
}

template <class keytype, class valuetype>
keytype RBTree<keytype, valuetype>::select(int pos)
{
    /*given a position in the tree, find its key*/
    return _select(root, pos)->key;
}

template <class keytype, class valuetype>
keytype *RBTree<keytype, valuetype>::successor(keytype k)
{
    return &_successor(_search(k))->key;
}

template <class keytype, class valuetype>
keytype *RBTree<keytype, valuetype>::predecessor(keytype k)
{
    return &_successor(_search(k))->key;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::preorder()
{
    _preorderWalk(root);
    cout << endl;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::inorder()
{
    _inorderWalk(root);
    cout << endl;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::postorder()
{
    _postorderWalk(root);
    cout << endl;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_preorderWalk(Node *node)
{
    if (node != nil)
    {
        cout << node->key << " ";
        _preorderWalk(node->leftChild);
        _preorderWalk(node->rightChild);
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_inorderWalk(Node *node)
{
    if (node != nil)
    {
        _inorderWalk(node->leftChild);
        cout << node->key << " ";
        _inorderWalk(node->rightChild);
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_postorderWalk(Node *node)
{
    if (node != nil)
    {
        _postorderWalk(node->leftChild);
        _postorderWalk(node->rightChild);
        cout << node->key << " ";
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::displayTree()
{
    _displayTree(root);
}
template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_displayTree(Node *p)
{
    if (root == nil)
    {
        cout << "\nEmpty Tree.";
        return;
    }
    if (p != nil)
    {
        cout << "\n\t NODE: ";
        cout << "\n Key: " << p->key;
        cout << "\n Colour: ";
        if (p->color == false)
            cout << "Black";
        else
            cout << "Red";
        if (p->parent != nil)
            cout << "\n Parent: " << p->parent->key;
        else
            cout << "\n There is no parent of the node.  ";
        if (p->size)
            cout << "\n Size: " << p->size;
        else
            cout << "\n There is no size of the node.  ";
        if (p->rightChild != nil)
            cout << "\n Right Child: " << p->rightChild->key;
        else
            cout << "\n There is no right child of the node.  ";
        if (p->leftChild != nil)
            cout << "\n Left Child: " << p->leftChild->key;
        else
            cout << "\n There is no left child of the node.  ";
        cout << endl;
        if (p->leftChild)
        {
            cout << "\n\nLeft:\n";
            _displayTree(p->leftChild);
        }
        /*else
     cout<<"\nNo Left Child.\n";*/
        if (p->rightChild)
        {
            cout << "\n\nRight:\n";
            _displayTree(p->rightChild);
        }
        /*else
     cout<<"\nNo Right Child.\n"*/
    }
}