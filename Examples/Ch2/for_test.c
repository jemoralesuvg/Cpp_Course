/**********************************************************************  Filename:  for_test.c  Chapter:   2      Native Types and Statements  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************/#include <iostream>#include <string>using namespace std;int main(){   int i = 0, sum = 0;   while (i <= 10) {      sum += i;      ++i;   }   cout << "\nSum for i "<< i << " is " << sum << endl;}