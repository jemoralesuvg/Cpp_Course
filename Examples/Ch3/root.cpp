/**********************************************************************  Filename:  root.cpp  Chapter:   3      Functions Pointers and Arrays  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************/#include <iostream>#include <assert>//using namespace std;double f(double x){   return (x*x + 1.0/x);}void plot(double fcn(double), double x0, double incr, int n){   for (int i = 0; i < n; ++i){      cout << " x :" << x0           << "   f(x) : " << fcn(x0) << endl;      x0 += incr;   }}int main(){   cout << "mapping function x*x + 1.0/x " << endl;   plot(f, 0.01, 0.01, 100);   int look; cin >> look;}