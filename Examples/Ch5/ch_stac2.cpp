/**********************************************************************  Filename:  ch_stac2.cpp  Chapter:   5      Constructors and Destructors  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************/#include <iostream>//using namespace std;#include "ch_stac2.h"const int N = 5;//count the number of c�s found in sint cnt_char(char c, ch_stack s){   int  count = 0;   while (!s.empty()) //done when empty      count += (c == s.pop()); //found a c   return count;}int main(){   ch_stack  data;            //creates s[100]   ch_stack  d[N];            //creates N 100 element ch_stacks   ch_stack  w(4, "ABCD");    //w.s[0]='A'...w.s[3]='D'   ch_stack  x(10, "ABCDABC");   ch_stack  y(x);   char   str[40] = { "My name is Don Knuth!" };   int    i = 0;   cout << str << endl;   while (str[i] && !data.full())      data.push(str[i++]);   data.print();   w.print();   x.print();   y.print();   cout << "\nThere are " << cnt_char('C', x) << " C's in the above" << endl;   int look; cin >> look;}