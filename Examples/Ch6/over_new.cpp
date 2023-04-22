/**********************************************************************  Filename:  over_new.cpp  Chapter:   6      Operator Overloading and Conversions  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************/#include <iostream>#include <assert>#include <new>//using namespace std;//overloaded new as found in <new.h>void* operator new(size_t size, void* ptr){ return ptr; }char*  buf1 = new char[1000];      //in place of free storechar*  buf2 = new char[1000];class object {               //needs only a few bytespublic:   char a;   char b;};// This program will use new to get memory from buf1 or buf2int main(){   strcpy(buf1, "ABCDEFGHIJK");    // init memory so we can see alloc   strcpy(buf2, "1234567890");   object *p = new(buf1) object;   //allocate at buf1   object *q = new(buf2) object;   //allocate at buf2   object *r = new(buf2 + sizeof(object)) object;   cout << "p points at " << p -> a << p -> b << endl;   cout << "q points at " << q -> a << q -> b << endl;   cout << "r points at " << r -> a << r -> b << endl;   int look; cin >> look;}