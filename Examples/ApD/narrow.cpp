/**********************************************************************  Filename:  narrow.cpp  Chapter:   E      Appendix E - Input/Output  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************/#include <iostream>class B {public:   int i;protected:   int  p;};class D: public B {public:    int l;private:    int k;public:   B::p;};main(){   cout << "hi " << endl;   B a;   D d;   a.i = 3;   cin >> d.i;}