/**********************************************************************  Filename:  stl_numr.cpp  Chapter:   7      Templates Generic Programming and STL  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************/#include <iostream>#include <numeric>using namespace std;//Use of mutating copy and reverse//Vector accumulation and innerproductint main(){   double v1[3] = { 1.0, 2.5, 4.6 },          v2[3] = { 1.0, 2.0, -3.5 };   double sum, inner_p;   sum = accumulate(v1, v1 + 3, 0.0);   inner_p = inner_product(v1, v1 + 3, v2, 0.0);   cout << "sum = " << sum        << ",product = " << inner_p << endl;   int look; cin >> look;}