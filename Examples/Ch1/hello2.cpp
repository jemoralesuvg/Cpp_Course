/**********************************************************************  Filename:  hello2.cpp  Chapter:   1      Overview of C++ and Object Oriented Programming  Compiler:  Borland C++     Version 5.01      Summer 1998  C++ for C Programmers, Edition 3     By Ira Pohl********************************************************************/#include <iostream>      //IO library#include <string>using namespace std;inline void pr_message(string s = "Hello world!"){ cout << s << endl; }int main(){   pr_message();   pr_message("Laura Pohl");   pr_message("It is dinner time.");   int look; cin >> look;}