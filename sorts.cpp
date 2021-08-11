#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// merge sort
// this merge doesn't use a left and right array, but a single merge array
void merge(int seq[], int helperArr[], int start, int mid, int end){
    for (int i=start; i<end+1; i++){
        helperArr[i] = seq[i];
    }
    int left = start;
    int right = mid+1;
    int idx = left;
    
    while ((left<=mid) && (right<=end)){
        if (helperArr[left] <= helperArr[right]){
            seq[idx] = helperArr[left];
            left++;
        }
        else {
            seq[idx] = helperArr[right];
            right++;
        }
        idx++;
    }

    // copying remaining elements on the left
    // we don't need to do this for the right the remainder on the right is already in seq
    int remaining = mid - left;
    for (int i=0; i<=remaining; i++){
        seq[idx+i] = helperArr[left+i];
    }
}

// recurses on left and right halves until they are of size 1. then, it merges them together
void mergeSort(int seq[], int start, int end){
    if (start<end){
        // this helper array stores both the halves we are trying to merge
        // from start...mid is the "left array", and from mid+1...end is the "right array"
        int* helperArr = new int[end-start+1];
        int mid = (start+end)/2; 
        mergeSort(seq, start, mid);
        mergeSort(seq, mid+1, end);
        merge(seq, helperArr, start, mid, end);
    }
}

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// partitions an array around the median
int partition(int seq[], int start, int end){
    int partitionIndex = (start+end)/2;
    int partitionVal = seq[partitionIndex];

    // while the start index doesn't overpass the end index
    while(start<end){
        // lookign for the first element on the left side of the partition that's on the wrong side
        while (seq[start]<partitionVal) {
            start++;
        }
        // looking for the first element on the right side of the partition that's on the wrong side
        while(seq[end]>partitionVal){
            end--;
        }
        // swaps the left and right so they'll be on the side
        swap(seq[start], seq[end]);
    }
    return start; // returns start as the partition index since this will be where partitionVal is
} 

// quicksort sorts an array around a parititon
void quickSort(int seq[], int start, int end){
    // we partition the array around an index, and then sort the other sides
    if (start<end){
        int partitionIdx = partition(seq, start, end); 
        quickSort(seq, start, partitionIdx-1);
        quickSort(seq, partitionIdx+1, end);
    }
}

int getMax(int intArr[], int size){
    if (size > 0) {
      int currMax = intArr[0];  
      for (int i=1; i<size; i++){
          if (intArr[i]>currMax)
            currMax = intArr[i];
      }
      return currMax;
    }
    return -1;
}

// keeps a hash table of keys 1-10, and counts how many values' places are between 1-10
void countingSort(int intArr[], int size, int exp){
    int countsArr[10];
    int val, digit;
    for (int i=0; i<10; i++){
        countsArr[i] = 0;
    }

    // storing counts. for example, 828 with exp 10 would lead to an increment of countsArr[2]
    for (int i=0; i<size; i++){
        val = intArr[i];
        digit = (val/exp)%10;
        countsArr[digit]++;
    }

    // aggregating the sums
    for (int i=1; i<10; i++){
        countsArr[i] = countsArr[i]+countsArr[i-1];
    }

    int output[size];

    // using the aggregated sums for array indexing to store into an output arrays
    for (int i=size-1; i>=0; i--){
        val = intArr[i];
        digit = (val/exp)%10;
        output[countsArr[digit]-1] = val;
        countsArr[digit]--;
    }
}

// sorts integers using decimal places - sorts by 1s, then 10s, then 100s, etc
void radixSort(int intArr[], int size){
    int max = getMax(intArr, size);
    int exp = 1;

    // going until maximum place. ex. if max is 270, we only want exp to go to 100
    while(max/exp>0){
        countingSort(intArr, size, exp); // sort for that individual decimal place
        exp *= 10; // go to the next place
    }
}
int main() { 
    int arr[7] = {5, 6, 3, 0, 2, 1, 4};
    quickSort(arr, 0, 6);
    for (int i=0; i<7; i++){
        cout << arr[i] << ' ';
    }
    cout << endl;

    int intArr[8] = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(intArr, 8);
    for (int i=0; i<8; i++){
        cout << intArr[i] << ' ';
    }
    return 0;
}
// quick sort
// radix sort
// iterative binary search