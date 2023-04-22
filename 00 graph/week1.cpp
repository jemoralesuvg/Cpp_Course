//****************************************************************************
// *  Author: José Eduardo Morales
// *  Date: march 9 2023
// *  This code is the week 1 assignment of a conversion of a C code to C++
// ***************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

// constant size for vector
const int N = 40;

// this function takes a vector d, its size n and saves the sum in p
inline void sum(int &p, int n, const vector <int> d)
{
    p = 0;
    for (int i = 0; i < n; ++i)
        p = p + d[i];
}
// main code 
int main()
{
    int accum = 0;

    //create data vector of size N
    vector<int> data; 
    data.resize(N);
    //initial values for the data array, ordered 0 to N (ie 0,1,2,..,N)
    for (int i = 0; i < N; ++i)
        data[i] = i;
    //total sum function
    sum(accum, N, data);

    cout << "sum is " << accum << endl;

    return 0;
}