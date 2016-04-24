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


#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "EquationParser.h"

using namespace std;

int EquationParser::power(int a,int b){
if(a == 0)
return 0;
if(b == 0)
return 1;
int temp=a;
for(int i=1;i<b;i++)
temp *=a;
return temp;
}

vector<int> EquationParser::evaluate(string equation, vector<string> variables){
   mintermNum = power(2,(int)variables.size());
   return parse(preparse(equation,variables));
}

string EquationParser::preparse(string equation, vector<string> variables){
   char newVariable='a';
   while(variables.size() > charVariableList.size()){
      bool inUse=false;
      for(int i=0; i < (int)variables.size(); i++){
	 if(variables[i].length() == 1)
	    if(newVariable == variables[i].at(0))
	       inUse=true;
      }
      if(!inUse)
	 charVariableList.push_back(newVariable);
      newVariable++;
   }
   for(int i=0; i < (int)variables.size(); i++){
      size_t found=std::string::npos;
      do{
	 found = equation.find(variables[i]);
	 if(found!=std::string::npos){
	    equation.replace(found, variables[i].size(), (size_t)1, charVariableList[i]);
	 }
      }while(found!=std::string::npos);
   }
   return equation;
}

vector<int> EquationParser::parse(string equation){
   vector<vector<int> > minterms;
   vector<int> finalMinterms;
   int bracketStart=0;
   int bracketEnd=0;
   vector<int> isNot;
   vector<int> star;
   vector<int> plus;
   vector<int> hat;
   minterms.push_back(finalMinterms);
   int bracketNum=0;

   for(int i=0;i<(int)equation.size();i++){
      switch(equation.at(i)){
	case '(':
	   if(!minterms.back().empty())
	     minterms.push_back(finalMinterms);
	   for(int j=i;j<(int)equation.size();j++){
	      if(equation.at(j) == '('){
		if(bracketStart==0)
		   bracketStart=j;
		   bracketNum++;
		}
	      if(equation.at(j) == ')'){
		   bracketNum--;
		   if(bracketNum == 0){
			bracketEnd = j;
			minterms.back()=parse(equation.substr(bracketStart+1,bracketEnd-bracketStart-1));
			i=j;
			break;
		   }
	      }
	   }
	   break;
	case '\'':
	   if(!minterms.back().empty())
	     minterms.push_back(finalMinterms);	 
	   isNot.push_back((int)minterms.size()-2);
	   break;
	case '^':
	   if(!minterms.back().empty())
	     minterms.push_back(finalMinterms);	 
	   hat.push_back((int)minterms.size()-2);
	   break;
	case '*':
	   if(!minterms.back().empty())
	     minterms.push_back(finalMinterms);	 
	   star.push_back((int)minterms.size()-2);
	   break;
	case '+':
	   if(!minterms.back().empty())
	     minterms.push_back(finalMinterms);	 
	   plus.push_back((int)minterms.size()-2);
	   break;
	default:
           int temp=0;
	   int half=0;
	   bool powered=false;
	   for(int j=0;j<(int)charVariableList.size();j++)
	      if(equation.at(i) == charVariableList[j]){
		 half=power(2,j+1);
		 powered=true;
	      }
	   if(!powered)
	      cerr << "oops";
	   while(temp<mintermNum){
		for(int j=temp;j<temp+(mintermNum/half);j++)
			minterms.back().push_back(0);
		temp += mintermNum/half;
		for(int j=temp;j<temp+(mintermNum/half);j++)
			minterms.back().push_back(1);
		temp += mintermNum/half;
	   }
      }
   }
   while((int)isNot.size()>0){
	for(int i=0;i<mintermNum;i++){
	if(minterms[isNot.back()][i] == 0)
		minterms[isNot.back()][i] =1;
	else
		minterms[isNot.back()][i] =0;
	}
	isNot.pop_back();
   }
   while((int)star.size()>0){
	for(int i=0;i<mintermNum;i++){
	if(minterms[star.back()][i] == 1 && minterms[star.back()+1][i] == 1)
		minterms[star.back()][i] =1;
	else
		minterms[star.back()][i] =0;
	}
	minterms.erase(minterms.begin()+star.back()+1);
		for(int j=0;j<(int)hat.size();j++)
		if(hat[j]>star.back())
			hat[j]--;
		for(int j=0;j<(int)star.size();j++)
		if(star[j]>star.back())
			star[j]--;
		for(int j=0;j<(int)plus.size();j++)
		if(plus[j]>star.back())
			plus[j]--;
	
	star.pop_back();
   }
   while((int)hat.size()>0){
	for(int i=0;i<mintermNum;i++){
	if((minterms[hat.back()][i] == 1 && minterms[hat.back()+1][i] == 0) || (minterms[hat.back()][i] == 0 && 
minterms[hat.back()+1][i] == 1))
		minterms[hat.back()][i] =1;
	else
		minterms[hat.back()][i] =0;
	}
	minterms.erase(minterms.begin()+hat.back()+1);
		for(int j=0;j<(int)hat.size();j++)
		if(hat[j]>hat.back())
			hat[j]--;
		for(int j=0;j<(int)star.size();j++)
		if(star[j]>hat.back())
			star[j]--;
		for(int j=0;j<(int)plus.size();j++)
		if(plus[j]>hat.back())
			plus[j]--;
	
	hat.pop_back();
   }

   while((int)plus.size()>0){
	for(int i=0;i<mintermNum;i++){
	if(minterms[plus.back()][i] == 1 || minterms[plus.back()+1][i] == 1)
		minterms[plus.back()][i] =1;
	else
		minterms[plus.back()][i] =0;
	}
	minterms.erase(minterms.begin()+plus.back()+1);
		for(int j=0;j<(int)hat.size();j++)
		if(hat[j]>plus.back())
			hat[j]--;
		for(int j=0;j<(int)star.size();j++)
		if(star[j]>plus.back())
			star[j]--;
		for(int j=0;j<(int)plus.size();j++)
		if(plus[j]>plus.back())
			plus[j]--;
	
	plus.pop_back();
   }
   return minterms[0];
}

bool EquationParser::isValid(string equation, vector<string> variables){
   return isValid(preparse(equation,variables),equation,variables);
}

bool EquationParser::isValid(string check, string equation, vector<string> variables){
   bool validVariable=false;
   int operatorNum=0;
   int variableNum=0;
   int bracketNum=0;
   char newVariable='A';
   vector<char> newVariableList;
   for(int j=0; j < (int)variables.size(); j++)
      for(int i=j+1; i < (int)variables.size(); i++)
	 if(variables[j] == variables[i]){
	    errorMessage = "Input error 01: Cannot have 2 variables with the same name";
	    return false;
	 }   
   while(variables.size() > newVariableList.size()){
      bool inUse=false;
      for(int i=0; i < (int)variables.size(); i++){
	 if(variables[i].length() == 1)
	    if(newVariable == variables[i].at(0))
	       inUse=true;
      }
      if(!inUse)
	 newVariableList.push_back(newVariable);
      newVariable++;
   }
   for(int i=0; i < (int)variables.size(); i++){
      size_t found;
      do{
	 found = equation.find(variables[i]);
	 if(found!=std::string::npos){
	    equation.replace(found, variables[i].size(), (size_t)1, newVariableList[i]);
	 }
      }while(found!=std::string::npos);
   }
   for(int i=0;i<(int)check.size();i++)
      for(int j=0;j < (int)newVariableList.size();j++)
	 if(check.at(i) == newVariableList[j]){
	    errorMessage = "Input error 02: Invalid variable name";
	    return false;
	 }

   for(int i=0;i<(int)equation.size();i++){
      switch(equation.at(i)){
	case ' ':
           equation.erase(equation.begin()+i);
	   i--;
	   break;
	case '(':
	   bracketNum++;
	   break;
	case ')':
	   bracketNum--;
	   if(i!=0)
	      if(equation.at(i-1) == '+' || equation.at(i-1) == '*' || equation.at(i-1) == '^'){
		errorMessage = "Input error 03: Invalid positioning of the ) character";
		return false;
	      }
	   if(bracketNum < 0){
	      errorMessage = "Input error 04: Invalid positioning of the ) character";
	      return false;
	   }
	   break;
	case '\'':
	   if(i==0){
	      errorMessage = "Input error 05: Invalid positioning of the ' character";
	      return false;
	   }
	   else
	      if(equation.at(i-1) == '+' || equation.at(i-1) == '*' || equation.at(i-1) == '^' || equation.at(i-1) == '\'' || equation.at(i-1) == '('){
		errorMessage = "Input error 06: Invalid positioning of the ' character";
		return false;
	      }
	   break;
	case '*':
	   operatorNum++;
	   if(operatorNum > variableNum){
	      errorMessage = "Inout Error 07: Invalid positioning of the * character";
	      return false;
	   }
	   break;
	case '+':
	   operatorNum++;
	   if(operatorNum > variableNum){
	      errorMessage = "Input error 08: Invalid positioning of the + character";
	      return false;
	   }
	   break;
	case '^':
	   operatorNum++;
	   if(operatorNum > variableNum){
	      errorMessage = "Input error 09: Invalid positioning of the ^ character";
	      return false;
	   }
	   break;
	default:
	   for(int j=0;j < (int)newVariableList.size();j++)
	      if(equation.at(i) == newVariableList[j])
		 validVariable = true;
	   if(!validVariable){
	      errorMessage = "Input error 10: Invalid variable name";
	      return false;
	   }
	   if(operatorNum < variableNum){
	      errorMessage = "Input error 11: Invalid variable positioning";
	      return false;
	   }
	   variableNum++;
	   validVariable = false;
      }
   }
   if(operatorNum == variableNum){
      errorMessage = "Input error 12: Cannot end with an operator +,*,or ^";
      return false;
   }
   if(bracketNum != 0){
      errorMessage = "Input error 13: Invalid bracketing";
      return false;
   }
   return true;
}

string EquationParser::getErrorMessage(){
   return errorMessage;
}
