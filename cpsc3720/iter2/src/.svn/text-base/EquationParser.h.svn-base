/****************************************************************************
This file is part of KMapper.

KMapper is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
KMapper is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with KMapper.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef EQUATIONPARSER_H
#define EQUATIONPARSER_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class EquationParser
{
private:

   int mintermNum;
   vector<char> charVariableList;
string errorMessage;
int power(int a,int b);
vector<int> parse(string equation);
string preparse(string equation, vector<string> variables); 
bool isValid(string check,string equation, vector<string> variables); 

public:

EquationParser(){
   mintermNum=0;
}

bool isValid(string equation, vector<string> variables); 

vector<int> evaluate(string equation, vector<string> variables); 

string getErrorMessage();

};

#endif
