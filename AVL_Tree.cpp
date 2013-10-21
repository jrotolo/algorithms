//=====================================
//    Implementation of AVL Tree
//    Time Complexity : O(logn)
//=====================================

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct node
{
    int key;
    int size;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
};

int max(int a, int b);

int height(struct node *N)
{
    if (N == NULL) return 0;
    return N->height;
}

int size(struct node* node)
{
    if (node == NULL) return 0;
    else return(size(node->left) + 1 + size(node->right));
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

//-----------------------------------------------------------------
// Creates a new Node
//-----------------------------------------------------------------
struct node* newNode(int key)
{
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->height = 1;
    node->size = 1;
    return(node);
}

//-----------------------------------------------------------------
// Does a right rotation on subtree rooted with y
//-----------------------------------------------------------------
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Do rotation
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    y->size = size(y);
    x->size =size(x);

    return x;
}

//-----------------------------------------------------------------
// Does a left rotation on subtree rooted with x
//-----------------------------------------------------------------
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Do rotation
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    x->size = size(x);
    y->size = size(y);

    return y;
}

//-----------------------------------------------------------------
// Returns the balance factor of node N
//-----------------------------------------------------------------
int getBalanceFactor(struct node *N)
{
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

//-----------------------------------------------------------------
// Returns the smallest node of AVL tree
//-----------------------------------------------------------------
struct node *minNode(struct node* node)
{
    struct node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

//-----------------------------------------------------------------
// Returns the biggest node of AVL tree
//-----------------------------------------------------------------
struct node *maxNode(struct node* node)
{
    struct node* current = node;
    while (current->right != NULL)
        current = current->right;
    return current;
}

//-----------------------------------------------------------------
// Insert a new node into the tree and restores the AVL property.
//-----------------------------------------------------------------
struct node* insert(struct node* node, int key)
{
    // Perform BST insertion
    if (node == NULL) return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    // Update the height of inserted ancestor node
    node->height = max(height(node->left), height(node->right))+1;
    node->size = size(node);

    // Get the balance factor of the ancestor node
    int balance = getBalanceFactor(node);

    // If node is unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//-----------------------------------------------------------------
// Delete a node from AVL tree and restore AVL property.
//-----------------------------------------------------------------
struct node* deleteNode(struct node* root, int key)
{
    // 1 PERFORM BST DELETE
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        // One child case/No child case
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) { temp = root; root = NULL; }
            else *root = *temp;     // One child case

            free(temp);
        }
        else
        {
            // Two child case
            struct node *temp = minNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    //Single node case
    if (root == NULL) return root;

    // 2 UPDATE HEIGHT
    root->height = max(height(root->left), height(root->right))+1;
    root->size = size(root);

    // 3 GET BALANCE FACTOR
    int balance = getBalanceFactor(root);

    // 4 BALANCE AVL TREE FOR ALL CASES

    // Left Left Case
    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && getBalanceFactor(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalanceFactor(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

//-----------------------------------------------------------------
// Search for node with given key in AVL tree.
//-----------------------------------------------------------------
bool search(struct node* root, int key)
{
    if (root == NULL) return false;

    if (root->key == key) return true;
    else if (key < root->key)
        search(root->left, key);
    else if (key > root->key)
        search(root->right, key);
}

//-----------------------------------------------------------------
// Returns successor of element x i.e. element with the smallest key
// greater than that of element x.
//-----------------------------------------------------------------
struct node* successor(struct node* nodeX)
{
    struct node *nodeY = nodeX->parent;

    if (nodeX->right != NULL)
        return(minNode(nodeX->right));

    while (nodeY != NULL && nodeX == nodeY->right)
    {
        nodeX = nodeY;
        nodeY = nodeY->parent;
    }
    return nodeY;
}

//-----------------------------------------------------------------
// Returns predecessor of element x i.e. element with the largest
// key smaller than that of element x.
//-----------------------------------------------------------------
struct node* predecessor(struct node* nodeX)
{
    if (nodeX->left != NULL)
        return(maxNode(nodeX->left));
    struct node* nodeY = nodeX->parent;

    while (nodeY != NULL && nodeX == nodeY->left)
    {
        nodeX = nodeY; nodeY = nodeY->parent;
    }
    return nodeY;
}

//-----------------------------------------------------------------
// Performs a preorder traversal on the tree.
//-----------------------------------------------------------------
void preOrderTraversal(struct node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

//-----------------------------------------------------------------
// Performs a inorder traversal on the tree.
//-----------------------------------------------------------------
void inOrderTraversal(struct node *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        printf("%d ", root->key);
        inOrderTraversal(root->right);
    }
}

//-----------------------------------------------------------------
// Returns the rank/position of element i in the linear order
// deteremined by inorder traversal of the tree
// WARNING: NOT WORKING FOR ALL INPUTS....
//-----------------------------------------------------------------
int rank(struct node *x, int i)
{
    if (x == NULL) return 0;
    if (i < x->key) return rank(x->left, i);
    if (i == x->key) return (x->left->size+1);
    // Problem may be in this return statement..
    return ((x->left->size+1)+(rank(x->right, i)));
}

//-----------------------------------------------------------------
// Returns the element containing the ith smallest key in a tree
// WARNIING: NOT WORKING FOR ALL INPUTS...
//-----------------------------------------------------------------
int select(struct node *x, int i)
{
    if (x == NULL) return 0;
    if (x->left->size >= i)
        return select(x->left, i);
    if (x->left->size+1 == i)
        return x->key;
    return select(x->right, i-1-(x->left->size));
}

int main()
{
    bool found = false;
    struct node *root = NULL;
    string line;
    ifstream inputFile("AVLtree-input.txt");

    // Reading input file
    inputFile.open("AVLtree-input", ifstream::in);
    if (inputFile.is_open())
    {
        while (getline(inputFile, line))
            cout << line << endl;
        inputFile.close();
    }
    else cout << "Unable to open file" << endl;

    // Construct Tree
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 10);
    root = insert(root, 0);
    root = insert(root, 6);
    root = insert(root, 11);
    root = insert(root, -1);
    root = insert(root, 1);
    root = insert(root, 2);

    printf("Pre order traversal of AVL tree is \n");
    preOrderTraversal(root);
    printf("\nIn order traversal of AVL tree is \n");
    inOrderTraversal(root);

    /* AVL Tree after inserts

                  9
                 / \
                1   10
               / \    \
              0   5    11
             /   / \
            -1  2   6

    */

    root = deleteNode(root, 10);
    printf("\nPre order traversal after deletion \n");
    preOrderTraversal(root);

    /* AVL Tree after deletion

                  1
                 / \
                0   9
               /   / \
             -1   5   11
                 / \
                2   6

    */

    printf("\n");
    found = search(root, 7);
    printf("Search for 7 = ");
    printf(found ? "Number found!" : "Number not found!");

    printf("\n");
    found = search(root, 11);
    printf("Search for 11 = ");
    printf(found ? "Number found!" : "Number not found!");

    printf("%d", rank(root, 0));
    printf("%d", rank(root, 1));
    // NOT WORKING..... printf("%d", rank(root, 2));


    printf("\n%d\n", select(root, 2));
    printf("\n%d\n", select(root, 3));





    return 0;
}
