// compile with g++ hashTable.cpp -std=c++11
#include <iostream>
#include <stdexcept>
using namespace std;

// Queue implemented as circulary array
class Queue{
    private:
        int rear;
        int front;
        int* queue;
        int size;
    public:
        Queue(int queueSize=5);
        ~Queue(){delete [] queue;} // destructor to delete dynamically allocated array
        int dequeue();
        void enqueue(int value);
        int peek();
        bool isEmpty();
        bool isFull();
};

/**
 * Creates an instance of the Queue class
 * Begins with front and rear as -1.
 * 
 * @param queueSize Size of queue, which defaults to 5.
 */
Queue::Queue(int queueSize=5){
    size = queueSize;
    queue = new int[size];
    front = -1;
    rear = front;
}

/**
 * Adds an element to the queue, by adding at rear.
 * Throws error if queue is full. If queue is empty, front is set to 0. 
 * Increments rear using (rear+1)%size for circular behavior.
 * 
 * @param value Value of element to be added.
 */
void Queue::enqueue(int value){
    if (this->isFull()){
        throw length_error("Queue is full!");
    }
    if (this->isEmpty()){
        front = 0; 
    }

    rear = (rear+1)%(size);
    queue[rear] = value; 
}

/**
 * Dequeues an element from the queue, by removing the front.
 * Throws error if queue is empty. If there's only one element in the queue, front and rear goes back to -1.
 * Otherwise, increments front using (front+1)%size for circular behavior.
 * 
 * @return Value of element that was dequeued.
 */
int Queue::dequeue(){
    if (this->isEmpty()){
        throw length_error("Queue is empty!");
    }
    int valueToReturn = queue[front];
    if (front==rear){
        front = -1;
        rear = front;
    }
    else{
        front = (front+1)%size;
    }
    return valueToReturn;
}

/**
 * See value of front element in queue.
 * 
 * @return Value of element in the front of the queue.
 */
int Queue::peek(){
    if (this->isEmpty()){
        throw length_error("Queue is empty!");
    }
    return queue[front];
}

/**
 * Check if queue is empty, by seeing if front is -1.
 * 
 * @return True if queue is empty, otherwise false.
 */
bool Queue::isEmpty(){
    return(front==-1);
}

/**
 * Check if queue is full, by seeing if rear is right behind front.
 * 
 * @return True if queue is full, otherwise false.
 */
bool Queue::isFull(){
    return((rear+1)%size==front);
}

// Driver
int main() {
    Queue myQueue = Queue(3);
    myQueue.enqueue(1);
    myQueue.enqueue(2);

    cout << "Front of queue: " << myQueue.peek() << endl;

    myQueue.enqueue(3);

    if (myQueue.isFull()){
        cout << "Queue is now full!!" << endl;
    }

    int val = myQueue.dequeue();
    cout << "New front of queue: " << myQueue.peek() << endl;

    myQueue.enqueue(4);
    if (myQueue.isFull()){
        cout << "Queue is now full!!" << endl;
    }
    myQueue.dequeue();
    myQueue.dequeue();
    cout << "New front of queue: " << myQueue.peek() << endl;
    myQueue.dequeue();

    if(myQueue.isEmpty()){
        cout << "Queue is now empty!!" << endl;
    }

    myQueue.enqueue(0);
    myQueue.enqueue(1);
    cout << "New front of queue: " << myQueue.peek() << endl;
    return 0;
}