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
        Node *left;
        Node *right;

        //data about the node(value and key represent two seperate data entries ex. CWID and Name)
        bool color;
        valuetype value;
        keytype key;
        int size;

        //constructor for the Node(called when inserting)
        Node()
        {
            parent = NULL;
            left = NULL;
            right = NULL;

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
    void _preorderWalk(Node *node);
    void _inorderWalk(Node *node);
    void _postorderWalk(Node *node, bool print);
    void _postorderDelete(Node *node);
    bool _nodeEquality(Node *node1, Node *node2)
    {
        //checks if two nodes have identical values
        if (node1->value != node2->value)
            return false;
        if (node1->key != node2->key)
            return false;
        if (node1->color != node2->color)
            return false;
        if (node1->size != node2->size)
            return false;
        return true;
    }
    bool _treeEquality(Node *new_tree_root, Node *old_tree_nil, Node *old_tree_root)
    {
        //checks equality of every node in the tree
        if (old_tree_root == old_tree_nil) //there is no root in the old tree
        {
            return _nodeEquality(new_tree_root, old_tree_root); //nil == nil?
        }
        if (_nodeEquality(new_tree_root, old_tree_root) == false)
            return false;
        _treeEquality(new_tree_root->left, old_tree_nil, old_tree_root->left);
        _treeEquality(new_tree_root->right, old_tree_nil, old_tree_root->right);
        return true;
    }
    Node *_copyNode(Node *node_to_copy)
    {
        //returns a deep copy of a node pointer(doesnt copy left,right,or parent)
        Node *x = new Node();
        x->value = node_to_copy->value;
        x->key = node_to_copy->key;
        x->color = node_to_copy->color;
        x->size = node_to_copy->size;
        return x;
    }

    Node *_copyTree(Node *old_tree_root, Node *old_tree_nil, Node *new_tree_parent)
    {
        //given an old tree root, an old tree's nil, and a new tree's parent,
        //will create a deep copy of the tree
        if (old_tree_root == old_tree_nil) //there is no root in the old tree
        {
            return nil;
        }
        Node *new_tree_root = _copyNode(old_tree_root);

        new_tree_root->parent = new_tree_parent;
        new_tree_root->left = _copyTree(old_tree_root->left, old_tree_nil, new_tree_root);
        new_tree_root->right = _copyTree(old_tree_root->right, old_tree_nil, new_tree_root);
        if (new_tree_root->parent == nil)
        {
            root = new_tree_root;
        }
        return new_tree_root;
    }
    Node *_select(Node *node, int pos)
    {
        int rank = node->left->size + 1;
        if (rank == pos)
            return node;
        else if (pos < rank)
            return _select(node->left, pos);
        else
            return _select(node->right, pos - rank);
    }
    Node *_minimum(Node *current_node)
    {
        while (current_node->left != nil)
            current_node = current_node->left;
        return current_node;
    }
    Node *_maximum(Node *current_node)
    {
        while (current_node->right != nil)
            current_node = current_node->right;
        return current_node;
    }
    Node *ra(keytype k, int size_change = 0)
    {
        /*returns the NODE with the key k*/
        Node *current_node = root;
        while (current_node != nil && k != current_node->key)
        {
            current_node->size = current_node->size + size_change;
            if (k < current_node->key)
                current_node = current_node->left;
            else
                current_node = current_node->right;
        }
        if (current_node == nil)
            return nullptr;
        return current_node; //returns nil if not found
    }
    Node *_successor(Node *current_node)
    {
        /*returns the NODE successor of the current_node*/
        if (current_node->right != nil)
            return _minimum(current_node->right);
        Node *parent = current_node->parent;
        while (parent != nil && current_node == parent->right)
        {
            current_node = parent;
            parent = parent->parent;
        }
        return parent;
    }
    Node *_predecessor(Node *current_node)
    {
        /*returns the NODE predecessor of the current_node*/
        if (current_node->left != nil)
            return _maximum(current_node->left);
        Node *parent = current_node->parent;
        while (parent != nil && current_node == parent->left)
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
    //copy constructor
    RBTree(RBTree &old_tree);
    // destructor
    ~RBTree();
    //overloaded operators
    void operator=(const RBTree &old_tree);
    bool operator==(const RBTree &old_tree);

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

// copy constructor
template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(RBTree &old_tree)
{
    nil = new Node();
    nil->color = BLACK;
    nil->size = 0;
    current_size = old_tree.current_size;
    root = nil; //begin with pointing to an empty tree
    _copyTree(old_tree.root, old_tree.nil, nil);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::operator=(const RBTree &old_tree)
{
    if (this == &old_tree) //T = T
    {
        return;
    }
    current_size = old_tree.current_size;
    root = nil; //begin with pointing to an empty tree
    _copyTree(old_tree.root, old_tree.nil, nil);
}

template <class keytype, class valuetype>
bool RBTree<keytype, valuetype>::operator==(const RBTree &old_tree)
{
    //checks if the address is the same, only works for objt == objt
    if (this == &old_tree)
        return true;
    //check all values related to the class now
    return _treeEquality(root, old_tree.nil, old_tree.root);
    return true;
}

// destructor
template <class keytype, class valuetype>
RBTree<keytype, valuetype>::~RBTree()
{
    _postorderDelete(root);
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
                current_node = current_node->left;
            }
            else
            {
                current_node = current_node->right;
            }
        }
        current_node = last_node;        //cleaning up the current node
        new_node->parent = current_node; //setting the parent node of new node
        if (new_node->key < current_node->key)
        {
            current_node->left = new_node;
        }
        else
        {
            current_node->right = new_node;
        }
    }
    new_node->left = nil;
    new_node->right = nil;
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
        if (new_node->parent == new_node->parent->parent->left)
        {                                            //checking if parent of new node is left or right child
            uncle = new_node->parent->parent->right; //brother of new node's parent
            if (uncle->color == RED)
            { //parent and uncle are both red (CASE 1)
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            else
            {
                if (new_node == new_node->parent->right)
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
            uncle = new_node->parent->parent->left;
            if (uncle->color == RED)
            {
                new_node->parent->color = BLACK;
                uncle->color = BLACK;
                new_node->parent->parent->color = RED;
                new_node = new_node->parent->parent;
            }
            else
            {
                if (new_node == new_node->parent->left)
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
    Node *y = node->right;
    node->right = y->left;
    if (y->left != nil)
    {
        y->left->parent = node;
    }
    y->parent = node->parent;
    if (node->parent == nil)
    {
        root = y;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
    {
        node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
    //update size after the rotations
    y->size = node->size;
    node->size = node->left->size + node->right->size + 1;
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
    Node *x = node->left;
    node->left = x->right;
    if (x->right != nil)
    {
        x->right->parent = node;
    }
    x->parent = node->parent;
    if (node->parent == nil)
    {
        root = x;
    }
    else if (node == node->parent->right)
    {
        node->parent->right = x;
    }
    else
    {
        node->parent->left = x;
    }
    x->right = node;
    node->parent = x;
    //update size after the rotations
    x->size = node->size;
    node->size = node->right->size + node->left->size + 1;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_transplant(Node *u, Node *root_child)
{
    /*replaces the subtree rooted at 'root' with the subtree rooted at 'root_child'
      outputs:
              u's parent is now v's parent
              u's parent has v as a child (which child depends on the situation)
    */
    if (u->parent == nil) //root is the root node in the tree
        root = root_child;
    else if (u == u->parent->left) //root is a left child
        u->parent->left = root_child;
    else //root is a right child
        u->parent->right = root_child;
    root_child->parent = u->parent; //update the parent of 'root_child' to be 'root' parent
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
    Node *z = _search(k, -1); //obtain a pointer to the node with key k
    Node *x = NULL;
    if (z == nullptr)
        return 0;
    current_size--; //the node exists so it will be removed
    Node *y = z;
    bool original_y_color = y->color; //keep track of color before any changes
    if (z->left == nil)               //node to delete has no left child
    {
        x = z->right;
        _transplant(z, x); //replace node to delete by its right child(could be nil)
    }
    else if (z->right == nil) //node to delete has a left child but no right child
    {
        x = z->left;
        _transplant(z, x);
    }
    else //node to delete has two children
    {
        y = _minimum(z->right); //find the y of the node to delete
        original_y_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else
        {
            _transplant(y, x);
            y->right = z->right;
            y->right->parent = y;
        }
        _transplant(z, y);
        y->left = z->left; //y has been moved into node to deletes spot
        y->left->parent = y;
        y->color = z->color;
    }
    if (original_y_color == BLACK) //some violations might of been introduced
        _removeFixup(x);
    return 1;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_removeFixup(Node *x)
{
    /*Three problems may of come up in removing a node:
        1. If successor had been the root and a red child of successor becomes the new root, 
            we have violated property 2
        2. If both node to delete's child and y to delete's child's parent are red, 
            then we have violated property 4
        3. Moving successor within the tree causes any path that contained successor to have one
            fewer black node, violating property 5
    */
    Node *w = NULL;
    while (x != root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (w->color == RED)
            { //case 1
                w->color = BLACK;
                x->parent->color = RED;
                _leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK)
            { //case 2
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    _rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                _leftRotate(x->parent);
                x = root;
            }
        }
        else //same as the 'if' with left and right switched
        {
            w = x->parent->left;
            if (w->color == RED)
            { //case 1
                w->color = BLACK;
                x->parent->color = RED;
                _rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK)
            { //case 2
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    _leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                _rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
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
    Node *z = _search(k);
    if (z == nullptr)
        return 0;
    int r = z->left->size + 1;
    Node *y = z;
    while (y != root)
    {
        if (y == y->parent->right)
            r = r + y->parent->left->size + 1;
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
    if (_search(k) == nullptr)
        return nullptr;
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
    if (_successor(_search(k)) == nil)
        return nullptr;
    return &_successor(_search(k))->key;
}

template <class keytype, class valuetype>
keytype *RBTree<keytype, valuetype>::predecessor(keytype k)
{
    if (_predecessor(_search(k)) == nil)
        return nullptr;
    return &_predecessor(_search(k))->key;
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
    _postorderWalk(root, 1);
    cout << endl;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_preorderWalk(Node *node)
{
    if (node != nil)
    {
        cout << node->key << " ";
        _preorderWalk(node->left);
        _preorderWalk(node->right);
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_inorderWalk(Node *node)
{
    if (node != nil)
    {
        _inorderWalk(node->left);
        cout << node->key << " ";
        _inorderWalk(node->right);
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_postorderWalk(Node *node, bool print)
{
    if (node != nil)
    {
        _postorderWalk(node->left, print);
        _postorderWalk(node->right, print);
        if (print == 1)
            cout << node->key << " ";
    }
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::_postorderDelete(Node *node)
{
    if (node != nil)
    {
        _postorderWalk(node->left, 0);
        _postorderWalk(node->right, 0);
        delete (node);
    }
}
