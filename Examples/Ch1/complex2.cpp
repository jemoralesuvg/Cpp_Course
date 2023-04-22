/**********************************************************************  Filename:  complex2.cpp  Chapter:   1      Overview of C++ and Object Oriented Programming  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************/#include <iostream>      //IO library#include <string>        //string typeusing namespace std; //An elementary implementation of type complexclass complex {public:                   //universal access to interface   //constructor   complex(double r=0, double im=0): real(r), imaginary(im) { }   //destructor   ~complex() { cout << "destructor called on "; print(); }   void re_assign(double r) { real = r; }   void im_assign(double im) { imaginary = im; }   void print() const      { cout << "(" << real << ","             << imaginary << "i)" << endl; }   void  print(string var_name) const      { cout << var_name << " = "; print(); }   friend complex operator+(complex, complex);private:                  //restricted access to implementation   double real, imaginary;};//overload +complex operator+(complex x, complex y){   complex t;   t.real = x.real + y.real;   t.imaginary = x.imaginary + y.imaginary;   return t;}//Test of the class complexint main(){   complex  x(5.5, 1.0), y, z;   complex w(1.5,2);   w.print("w");             //print: w = (1.5,2i)   w.print();                //print: (1.5,2i)   x.print("x");   y.re_assign(4.2);   y.im_assign(6.0);   z = x + y;                 //uses operator+()   x.print("x");   y.print("y");   z.print("z");   int look; cin >> look;}