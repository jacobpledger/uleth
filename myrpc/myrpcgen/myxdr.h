#ifndef MYXDR_H
#define MYXDR_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;

void my_xdr_int(void* i, void* s);
void my_xdr_float(void* f, void* s);
void my_xdr_char(void* c, void* s);
int my_xdr_int(const char* a);
string my_xdr_int(int i);
float my_xdr_float(const char* a);
string my_xdr_float(float f);
char my_xdr_char(char c);

#endif
