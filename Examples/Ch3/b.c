/**********************************************************************  Filename:  b.c  Chapter:   3      Functions Pointers and Arrays  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************///  file A.cstatic int  foo(int i){   return (i * 3);}int  goo(int i){   return (i * foo(i));}