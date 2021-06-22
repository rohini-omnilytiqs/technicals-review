#include <iostream> 
using namespace std;

struct Node{
    Node* next;
    int data;
};

// This is a stack class implemented with a linked list.
// It can also be done with an array, keeping track of the last element.
class Stack{
    private:
        Node* top; // top of the stack is the head of the linked list
    public:
        Stack();
        ~Stack();
        void push(int value);
        int pop();
        int peek();
        bool isEmpty();
};

/**
 * Constructs an object of type Stack by setting top to NULL.
 */
Stack::Stack(){
    top = NULL;
}

/**
 * Destructs an object of type Stack by deallocating nodes.
 */
Stack::~Stack(){
    while(top!=NULL){
        Node* temp = top;
        top = top->next;
        delete temp;
    }
}

/**
 * Add an element to the stack, by adding it as the new top. 
 * 
 * @param value: Value to add to stack.
 */
void Stack::push(int value){
    Node* newNode = new Node; 
    newNode->data = value;
    if (top==NULL){
        newNode->next = NULL;
    }
    else{
        newNode->next = top;
    }
    top = newNode;
}

/**
 * Remove top of the stack. 
 * 
 * @return Value of the node that was removed.
 */
int Stack::pop(){
    int valueToReturn = top->data;
    Node* temp = top;
    top = top->next;
    delete temp;
    return valueToReturn;
}

/**
 * Return value of top of the stack.
 * 
 * @return Value of node at the top of the stack.
 */
int Stack::peek(){
    return top->data;
}

/**
 * Checks if stack has any elements.
 * 
 * @return True if no elements are in the stack, otherwise false.
 */
bool Stack::isEmpty(){
    return (top==NULL);
}

// Driver
int main(){
    Stack myStack = Stack();
    if (myStack.isEmpty()){
        cout << "Stack is currently empty" << endl;
    }

    myStack.push(4);
    myStack.push(9);
    myStack.push(10);
    cout << "Top of stack: " << myStack.peek() << endl;

    myStack.pop();
    myStack.pop();
    cout << "New top of stack: " << myStack.peek() << endl;

    return 0;
}

