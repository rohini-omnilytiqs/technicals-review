// a binary search tree has a node's left descendants being smaller than it, and its right descendants being larger
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct TreeNode {
    int value; 
    struct TreeNode* left;
    struct TreeNode* right;
};

class BinarySearchTree {
    private:
        TreeNode* root;
        struct TreeNode* newNode(int value);
        void preOrderHelper(struct TreeNode* node);
        void inOrderHelper(struct TreeNode* node);
        void postOrderHelper(struct TreeNode* node);

    public:
        BinarySearchTree() {root = NULL;};
        ~BinarySearchTree() {destroyRecursive(root);};
        void destroyRecursive(struct TreeNode* node);
        void insert(int value); // O(log n)
        void remove(int value); // O(log n)
        struct TreeNode* find(int value); // O(log n)
        void preOrderTraversal(); // O(n)
        void inOrderTraversal(); // O(n)
        void postOrderTraversal(); // O(n)
};

// helper function to allocate a new node
struct TreeNode* BinarySearchTree::newNode(int value){
    struct TreeNode* newNode = new struct TreeNode;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// helper function for destructor
void BinarySearchTree::destroyRecursive(struct TreeNode* node){
    if (node!=NULL) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

// new nodes are always added as leaves
// perform a binary search to find which node to add a leaf to
void BinarySearchTree::insert(int value){
    struct TreeNode* nodeToAdd = newNode(value);

    if (root == NULL) {
        root = nodeToAdd;
        return;
    }

    struct TreeNode* runner = root;
    bool inserted = false;

    while (!inserted){
        if (value < runner->value) {
            if (runner->left == NULL){
                runner->left = nodeToAdd;
                inserted = true;
            }
            else {
                runner = runner->left;
            }
        }    
        else if (value > runner->value){
            if (runner->right == NULL){
                runner->right = nodeToAdd;
                inserted = true;
            }
            else {
                runner = runner->right;
            }
        }
        else {
            cout << "Duplicate value" << endl;
            return;
        }    
    }
}

// finds a node using binary search
struct TreeNode* BinarySearchTree::find(int value) {
    struct TreeNode* runner = root;
    while (runner != NULL){
        if (value > runner->value){
            runner = runner->right;
        }
        else if (value < runner->value){
            runner = runner->left;
        }
        else {
            return runner;
        }
    }
    return NULL;
}

// removes a node by first finding it 
// at a high level, to remove a node, take the largest of its smaller children (i.e left, and then as far right as possible) and use
// then change the node's value to that. then delete that child. 
// there are multiple edge cases:
    // 1. node doesn't exist
    // 2. node has no children, in which case it is just deleted. 
    // 3. node doesn't have any smaller children (i.e. nothing on its left). In that case, we replace it with the child on the right.
// from there, we go left once, and go as far right as possible, and use that child.
void BinarySearchTree::remove(int value) {
    struct TreeNode* node = find(value);
    if (node == NULL){
        return;
    }

    if (node->left == NULL){
        if (node->right == NULL){
            delete node;
        }
        else {
            struct TreeNode* temp = node->right;
            node->value = node->right->value;
            node->left = node->right->left;
            node->right = node->right->right;
            delete temp;
        }
    }

    else{
        struct TreeNode* runner = node->left;
        if (runner->right != NULL){
            while (runner->right->right != NULL){
                runner = runner->right;
            }
            struct TreeNode* temp = runner->right;
            node->value = temp->value;
            runner->right = temp->left;
            delete temp; 
        }
        else {
            node->value = runner->value;
            node->left = runner->left;
            delete runner;
        }
            
    }
}
// preorder follows curr->left->right
void BinarySearchTree::preOrderTraversal(){
    preOrderHelper(root);
}

void BinarySearchTree::preOrderHelper(struct TreeNode* node){
    cout << node->value << " ";
    if (node->left != NULL)
        preOrderHelper(node->left);
    if (node->right != NULL) 
        preOrderHelper(node->right);
}


// inorder follows left->curr->right
void BinarySearchTree::inOrderTraversal(){
    inOrderHelper(root);
}
void BinarySearchTree::inOrderHelper(struct TreeNode* node){
    if (node->left != NULL)
        inOrderHelper(node->left);
    cout << node->value << " ";
    if (node->right != NULL)
        inOrderHelper(node->right);
}

// postorder follows left->right->curr
void BinarySearchTree::postOrderTraversal(){
    postOrderHelper(root);
}

void BinarySearchTree::postOrderHelper(struct TreeNode* node){
    if (node->left != NULL)
        postOrderHelper(node->left);
    if (node->right != NULL)
        postOrderHelper(node->right);
    cout << node->value << " ";
}

int main() {
    BinarySearchTree myTree = BinarySearchTree();
    myTree.insert(5);
    myTree.insert(3);
    myTree.insert(8);
    myTree.insert(1);
    myTree.insert(4);
    myTree.insert(0);
    myTree.insert(2);
    myTree.insert(7);
    myTree.insert(9);
    myTree.insert(6);
    myTree.insert(10);

    myTree.inOrderTraversal();
    cout << endl;
    struct TreeNode* node = myTree.find(6);
    cout << node->value << endl;

    myTree.remove(5);
    myTree.inOrderTraversal();
    cout << endl;

    return 0;
}