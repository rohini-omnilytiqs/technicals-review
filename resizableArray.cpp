#include <stdexcept>
#include <iostream>
#include <string.h>
using namespace std;

// Resizable array class; can use stl class vector though
class ResizableArray {
    private:
        int size;
        int* arr;
        int elementCount;

    public:
        ResizableArray(){
            size = 10;
            arr = new int[size];
            elementCount = 0;
        };
        ~ResizableArray(){delete [] arr;}
        void insert(int value);
        void removeValueAtIndex(int index);
        void print();
};

/**
 * Inserts item into resizable array.
 * Size of array doubles if an element needs to be added to a full array. 
 * 
 * @param value Value to insert.
 */
void ResizableArray::insert(int value) {
    elementCount += 1;
    if (elementCount > size) {

        // int* temp = new int[size];
        // for (int i=0; i<size; i++) {
        //     temp[i] = arr[i];
        // }
        // delete [] arr;

        // arr = new int[size * 2];
        // for (int i=0; i<size; i++) {
        //     arr[i] = temp[i];
        // }
        // delete [] temp;

        int* newArr = new int[size*2];
        memcpy(newArr, arr, size * sizeof(int)); // copies memory from pointer to dest, pointer to source, num bytes
        delete [] arr;
        arr = newArr;

        arr[elementCount-1] = value;
    }
    else {
        arr[elementCount-1] = value;
    }
    size += 1;
}

/**
 * Removes item from resizable array by index.
 * 
 * @param index Index of value to remove.
 */
void ResizableArray::removeValueAtIndex(int index) {
    if ((index > elementCount) || (index == elementCount)) { 
        throw invalid_argument("Array is not large enough to remove this index");
    }
    else { 
        for (int i=index; i<size-1; i++) {
            arr[i] = arr[i+1];
        }
        elementCount -= 1;
        size -= 1;
    }
}

/**
 * Prints resizable array.
 */
void ResizableArray::print() {
    for (int i=0; i<elementCount; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Driver
int main() { 
    ResizableArray myResizableArray = ResizableArray();

    for (int i=0; i<10; i++){
        myResizableArray.insert(i);
    }
    myResizableArray.print();
    myResizableArray.insert(11);
    myResizableArray.print();
    myResizableArray.removeValueAtIndex(4);
    myResizableArray.print();
}
