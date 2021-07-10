// all tree traversals (recursive and iterative)
// all O(n) time and O(n) space

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

struct TreeNode* newNode(int value){
    struct TreeNode* newNode = new struct TreeNode; 
    newNode->right = NULL; 
    newNode->left = NULL;
    newNode->value = value;
    return newNode;
}

// preorder follows curr->left->right
void preOrderTraversal(struct TreeNode* root, vector<int> &traversal){
    traversal.push_back(root->value); 
    if (root->left != NULL)
        preOrderTraversal(root->left, traversal);
    if (root->right != NULL) 
        preOrderTraversal(root->right, traversal);
}

vector<int> iterPreOrderTraversal(struct TreeNode* root){
    vector<int> traversal;
    stack<struct TreeNode*> nodes; // substitutes recursion
    vector<struct TreeNode*> visited; // keeping track of nodes already visited so we don't explore them again

    struct TreeNode* runner = root;
    nodes.push(runner);
    while(!nodes.empty()){
        runner = nodes.top();
        if (find(visited.begin(), visited.end(), runner) == visited.end())
            traversal.push_back(runner->value);
        visited.push_back(runner);

        if((runner->left != NULL) && (find(visited.begin(), visited.end(), runner->left) == visited.end()))
            nodes.push(runner->left);
        else if ((runner->right != NULL) && (find(visited.begin(), visited.end(), runner->right) == visited.end()))
            nodes.push(runner->right);
        else {
            nodes.pop();
        }
    }
    return traversal;
}

// inorder follows left->curr->right
void inOrderTraversal(struct TreeNode* root, vector<int> &traversal){
    if (root->left != NULL)
        inOrderTraversal(root->left, traversal);
    traversal.push_back(root->value);
    if (root->right != NULL)
        inOrderTraversal(root->right, traversal);
}

vector<int> iterInOrderTraversal(struct TreeNode* root){
    vector<int> traversal;
    stack<struct TreeNode*> nodes;
    vector<struct TreeNode*> visited;

    struct TreeNode* runner = root;
    nodes.push(runner);
    while(!nodes.empty()){
        runner = nodes.top();
        if((runner->left!=NULL) && (find(visited.begin(), visited.end(), runner->left) == visited.end())){
            nodes.push(runner->left);
        }
        else if (find(visited.begin(), visited.end(), runner) == visited.end()){
            traversal.push_back(runner->value);
            visited.push_back(runner);
            nodes.pop();

            if((runner->right!=NULL) && (find(visited.begin(), visited.end(), runner->right) == visited.end())){
                nodes.push(runner->right);
            }
        }
    }
    return traversal;
}
// postorder follows left->right->curr
void postOrderTraversal(struct TreeNode* root, vector<int>& traversal){
    if (root->left != NULL)
        postOrderTraversal(root->left, traversal);
    if (root->right != NULL)
        postOrderTraversal(root->right, traversal);
    traversal.push_back(root->value);
}

vector<int> iterPostOrderTraversal(struct TreeNode* root){
    vector<int> traversal;
    stack<struct TreeNode*> nodes;
    vector<struct TreeNode*> visited;

    struct TreeNode* runner = root;
    nodes.push(runner);
    while(!nodes.empty()){
        runner = nodes.top();
        if((runner->left != NULL) && (find(visited.begin(), visited.end(), runner->left) == visited.end()))
            nodes.push(runner->left);
        else if ((runner->right != NULL)&& (find(visited.begin(), visited.end(), runner->right) == visited.end()))
            nodes.push(runner->right);
        else {
            nodes.pop();
            traversal.push_back(runner->value);
            visited.push_back(runner);
        }
    }
    return traversal;
}

int main() { 
    struct TreeNode* leaf1;
    struct TreeNode* leaf2;
    struct TreeNode* leaf3;
    struct TreeNode* leaf4;
    struct TreeNode* mid1;
    struct TreeNode* mid2;
    struct TreeNode* root;

    leaf1 = newNode(4);
    leaf2 = newNode(5);
    leaf3 = newNode(1);
    leaf4 = newNode(9);

    mid1 = newNode(12);
    mid1->left = leaf1;
    mid1->right = leaf2;

    mid2 = newNode(0);
    mid2->left = leaf3;
    mid2->right = leaf4;

    root = newNode(100);
    root->left = mid1;
    root->right = mid2;

    vector<int> traversal;
    vector<int> iterTraversal;

    // recursive and iterative preorder
    preOrderTraversal(root, traversal);
    iterTraversal = iterPreOrderTraversal(root);
    vector<int>::iterator it; 
    for (it=traversal.begin(); it != traversal.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
    for (it=iterTraversal.begin(); it != iterTraversal.end(); ++it){
        cout << *it << " ";
    }
    cout << endl << endl;

    traversal.clear();

    // recursive and iterative inorder
    inOrderTraversal(root, traversal);
    for (it=traversal.begin(); it != traversal.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    traversal.clear();
    iterTraversal = iterInOrderTraversal(root);
    for (it=iterTraversal.begin(); it != iterTraversal.end(); ++it){
        cout << *it << " ";
    }
    cout << endl << endl;

    traversal.clear();

    // recursive and iterative postorder
    postOrderTraversal(root, traversal);
    for (it=traversal.begin(); it != traversal.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
    traversal.clear();
    iterTraversal = iterPostOrderTraversal(root);
    for (it=iterTraversal.begin(); it != iterTraversal.end(); ++it){
        cout << *it << " ";
    }
    return 0;
}