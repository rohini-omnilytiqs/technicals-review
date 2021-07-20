#include <iostream>
using namespace std;

// Gets the bit in num at index i (counting from smallest to largest)
bool getBit(int num, int i){
    unsigned int shiftedFlag = (1<<i);
    return (num & shiftedFlag) != 0;
}

// Sets the i-th bit of num to 1 (counting from smallest to largest)
void setBit(int &num, int i){
    unsigned int shiftedFlag = (1<<i);
    num = num | shiftedFlag;
}

// Clears the i-th bit of num (sets to 0) (counting from smallest to largest)
void clearBit(int &num, int i){
    unsigned int shiftedFlag = (1<<i);
    num = num & ~shiftedFlag;
}

// Updates the i-th bit of num to be 1 or 0, depending on bool flag
// Does this by first clearing the bit and then or-ing with the value
void updateBit(int &num, int i, bool bitIsOne){
    unsigned int value = bitIsOne ? 1 : 0;
    unsigned int mask = ~(1<<i);
    num = ((num & mask) | (value << i));
}

int main(){
    int num = 0xb6;
    if (getBit(num, 6)) cout << "Bit is set!" << endl;
    else cout << "Bit isn't set!" << endl;

    setBit(num, 6);
    if (getBit(num, 6)) cout << "Bit is set!" << endl;
    else cout << "Bit isn't set!" << endl;

    if (getBit(num, 5)) cout << "Bit is set!" << endl;
    else cout << "Bit isn't set!" << endl;

    clearBit(num, 5);
    if (getBit(num, 5)) cout << "Bit is set!" << endl;
    else cout << "Bit isn't set!" << endl;

    updateBit(num, 5, true);
    if (getBit(num, 5)) cout << "Bit is set!" << endl;
    else cout << "Bit isn't set!" << endl;
    return 0;
}