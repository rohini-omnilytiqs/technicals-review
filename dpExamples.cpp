// 2 implementations of longest increasing subsequence
#include <iostream> 
#include <vector> 
using namespace std;

int max(int a, int b){
    if (a>=b) return a;
    return b;
}

// recursion helper
// LIS(i, j, seq) denotes the LIS of seq starting with value i from indices j...n
int LISHelper(int lastValue, int startIndex, vector<int> sequence){
    if (startIndex == sequence.size()){
        return 0;
    }
    int currValue = sequence[startIndex];
    if (lastValue < currValue) {
        return max(1+LISHelper(currValue, startIndex+1, sequence), LISHelper(lastValue,startIndex+1, sequence));
    }
    return LISHelper(lastValue, startIndex+1, sequence);
}

// recursive
// -1000 acts as a sentinel
int LISRecursive(vector<int> sequence){
    return LISHelper(-1000, 0, sequence);
}

// iterative
// memo[i][j] denotes the LIS starting with sequence[i] from indicies j...n 
int LISDP(vector<int> sequence){
    sequence.insert(sequence.begin(), -1000); // inserting the sentinel
    int n = sequence.size(); // size is n, so the last index is n-1
    int memo[n][n+1];

    for (int i=0; i<n; i++){
        memo[i][n]=0;
    }

    for(int j=n-1;j>=0;j--){
        for(int i=0; i<n; i++){
            if((sequence[i]<sequence[j]))
                memo[i][j] = max(1+memo[j][j+1], memo[i][j+1]);
            else
                memo[i][j] = memo[i][j+1];  
        }
    }
    return memo[0][1];
}

int main(){
    vector<int> seq = {6, 1, 2, 4, 9, 8, 6, 7};
    cout << LISRecursive(seq) << endl;
    cout << LISDP(seq) << endl;
    return 0;
}