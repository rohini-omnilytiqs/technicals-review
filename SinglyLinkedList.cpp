#include <iostream>
#include <stdexcept>
using namespace std;

struct Node {
    Node* next; // reference to next node
    int data;
};

// This is a singly linked list class with a head and tail node 
class SinglyLinkedList{ 
    private:
        Node* head; // reference to head node of list
        Node* tail; // reference to tail node of list
    public:
        SinglyLinkedList();
        ~SinglyLinkedList();
        void pushFront(int value); // O(1)
        int popFront(); // O(1)
        void pushBack(int value); // O(1)
        int popBack(); // O(n)
        void print(); // O(n)
        int size(); // O(n)
        bool isEmpty(); // O(1)
        int front(); // O(1)
        int back(); // O(1)
        void insertAtIndex(int index, int value); // O(n)
        void deleteValue(int value); // O(n)
        void eraseAtIndex(int index); // O(n)
        void reverse(); // O(n)
        void weave(); // O(n)
};

/**
 * Constructs an object of type SinglyLinked List by setting head and tail to NULL.
 */
SinglyLinkedList::SinglyLinkedList() {
    head = NULL;
    tail = NULL;
}

/**
 * Destroys an object of type SinglyLinkedList by deallocating nodes.
 */
SinglyLinkedList::~SinglyLinkedList(){
    Node* runner = head;
    while(runner!=NULL){
        Node* temp = runner;
        runner = runner->next;
        delete temp;
    }
}

/**
 * Add a node to the front of a linked list.
 *
 * @param value Value of node to add.
 */
void SinglyLinkedList::pushFront(int value){
    Node* nodeToAdd = new Node; 
    nodeToAdd->data = value;
    if(head == NULL) {
        head = nodeToAdd;
        tail = nodeToAdd;
        nodeToAdd->next = NULL;
    }
    else {
        nodeToAdd->next = head;
        head = nodeToAdd;
    }
}

/**
 * Removes first node in linked list.
 *
 * @return Value of node removed.
 */
int SinglyLinkedList::popFront(){
    if(head==NULL){
        throw length_error("List is empty!");
    }
    else {
        Node* temp = head;
        int value = temp->data;
        head = temp->next;
        delete temp;
        return value;
    }
}

/**
 * Adds node to back of linked list.
 *
 * @param value Value to of node to add.
 */
void SinglyLinkedList::pushBack(int value){
    Node* nodeToAdd = new Node;
    nodeToAdd->data = value;
    nodeToAdd->next = NULL;
    if (tail==NULL) {
        head = nodeToAdd;
        tail = nodeToAdd;
    }
    else {
        tail->next = nodeToAdd;
        tail = nodeToAdd;
    }

}

/**
 * Remove last node of linked list.
 * 
 * @return Value of node removed.
 */
int SinglyLinkedList::popBack(){
    Node* nextToLast = head;
    while(nextToLast->next!=tail){
        nextToLast = nextToLast->next;
    }
    if(tail==NULL){
        throw length_error("List is empty!");
    }
    else { 
        Node* temp = tail;
        int value = temp->data;
        tail = nextToLast;
        tail->next = NULL;
        return value;
        delete temp;
    }
}

/**
 * Print value of nodes in linked list.
 *
 */
void SinglyLinkedList::print() {
    Node* runner;
    runner = head;
    while(runner != NULL) {
        cout << runner->data << " ";
        runner = runner->next;
    }
    cout << endl;
}

/**
 * Find number of nodes in linked list.
 *
 * @return Size of linked list.
 */
int SinglyLinkedList::size(){
    Node* runner = head;
    int counter = 0;
    while(runner != NULL){
        counter++;
        runner = runner->next;
    }
    return counter;
}

/**
 * Check if linked list is empty.
 *
 * @return True if list is empty, otherwise false.
 */
bool SinglyLinkedList::isEmpty(){
    return(head==NULL);
}

/**
 * Gets value of node at front of linked list.
 *
 * @return Value of node at front of linked list.
 */
int SinglyLinkedList::front(){
    if (head==NULL){
        throw length_error("List is empty!");
    }
    else {
        return head->data;
    }
}

/**
 * Returns value of node at end of linked list.
 * 
 * @return Value of node at end of linked list.
 */
int SinglyLinkedList::back(){
    if (tail==NULL){
        throw length_error("List is empty!");
    }
    else {
        return tail->data;
    }
}

/**
 * Insert a node into the linked list by index.
 *
 * @param index Index to add node at.
 * @param value Value of node to add.
 */
void SinglyLinkedList::insertAtIndex(int index, int value){
    if((head==NULL) && (value !=0)){
        throw length_error("List is empty!");
    }
    if(head==NULL){
        this->pushFront(value);
        return;
    }
    if(index>=this->size()){
        throw length_error("List is not long enough!");
    }
    if(index==this->size()-1){
        this->pushBack(value);
        return;
    }
    Node* beforeIndex = head;
    for(int i=0; i<index; i++){
        beforeIndex = beforeIndex->next;
    }

    Node* afterIndex = beforeIndex->next;
    Node* nodeToAdd = new Node;
    nodeToAdd->data = value;

    beforeIndex->next = nodeToAdd;
    nodeToAdd->next = afterIndex;
}

/**
 * Delete node in linked list by value.
 *
 * @param value Value of node to remove.
 */
void SinglyLinkedList::deleteValue(int value){
    if (this->isEmpty()){
        throw length_error("List is empty!");
    }
    Node* runner = head;
    bool valueFound = false;
    while((runner->next!=NULL) && (!valueFound)){
        if(runner->next->data == value){
            Node* temp = runner->next;
            runner->next = temp->next;
            delete temp;
            valueFound = true;
        }
        runner = runner->next;
    }
    if (!valueFound){
        throw invalid_argument("Value not in list!");
    }
}

/**
 * Delete node of linked list by index.
 *
 * @param index Index of node to delete.
 */
void SinglyLinkedList::eraseAtIndex(int index){
    if(head==NULL){
        throw length_error("List is empty!");
    }
    if(index>=this->size()){
        throw length_error("List is not long enough!");
    }
    if(index==this->size()-1){
        this->popBack();
        return;
    }

    Node* runner = head;
    for(int i=0; i<index-1; i++){
        runner = runner->next;
    }
    Node* temp = runner->next;
    runner->next = temp->next;
    delete temp;
}

/**
 * Reverse order of nodes of linked list in place.
 */
void SinglyLinkedList::reverse(){
    Node* prev=NULL; 
    Node* current=head;
    Node* after=NULL;

    if (head == NULL){
        return;
    }
 
    while (current != NULL) {
        after = current->next;
        current->next = prev;
        prev = current;
        current = after;
        }
        head = prev;
}

/**
 * Weave first and second half of even-length linked list in place.
 * Ex. 1 3 5 2 4 6 -> 1 2 3 4 5 6
 */
void SinglyLinkedList::weave(){
    Node* firstHalf = head;
    Node* secondHalf = head;

    int midIndex = this->size()/2;
    for (int i=0; i<midIndex; i++){
        secondHalf = secondHalf->next; }
    while(secondHalf!= NULL){
        Node* temp1 = firstHalf->next;
        Node* temp2 = NULL;
        if (secondHalf->next != NULL){
            temp2 = secondHalf->next;
            secondHalf->next = firstHalf->next;
        }

        firstHalf->next = secondHalf;
        firstHalf = temp1;
        secondHalf = temp2;
    }
}


int main() {
    SinglyLinkedList myLinkedList = SinglyLinkedList();
    myLinkedList.pushBack(1);
    myLinkedList.pushBack(3);
    myLinkedList.pushBack(5);
    myLinkedList.pushBack(2);
    myLinkedList.pushBack(4);
    myLinkedList.pushBack(6);
    myLinkedList.print();

    // Weaving technique example
    myLinkedList.weave();
    myLinkedList.print();
    return 0;
}