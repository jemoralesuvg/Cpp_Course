/**********************************************************************  Filename:  dyn_ar~1.cpp  Chapter:   3      Functions Pointers and Arrays  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************/#include <iostream>#include <assert>//Use of new to dynamically allocate an array//assumes older style return of 0 for allocation errorint main(){   int*  data;   int   size;   cout << "\nEnter array size: ";   cin >> size;   assert(size > 0);   data = new int[size];        //allocate an array of ints   assert(data != 0);           //data != 0 allocation succeeds   for (int j = 0; j < size; ++j)      cout << (data[j] = j) << '\t';   cout << "\n\n";   delete[] data;               //deallocate an array   int look; cin >> look;}