#include "parser.h"
#include <vector>
#include <string>
#include <cstddef>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "number.h"
#include "matrix.h"
#include <fstream>

using namespace std;

Parser::~Parser(){
	if(!varList.empty()){
		for(auto it=varList.begin(); it!=varList.end(); ++it){
			delete *it;
		}
	}
}

void Parser::addVar(Variable* var){
	varList.push_back(var);
}

Variable* Parser::findVar(std::string varName) const{
	if(varList.empty()){
		return nullptr;
	}
	for(std::vector<Variable*>::const_iterator it=varList.begin(); it!=varList.end(); ++it){
		Variable* var = *it;
		if(var->getName() == varName){
			return var;
		}
	}
	return nullptr;
}

void Parser::printVars() const{
	for(auto it=varList.begin(); it!=varList.end(); ++it){
		Variable* var = *it;
		switch(var->getType()){
		case Variable::number:
			std::cout << *(Number*) var << std::endl;
			break;
		case Variable::matrix:
			std::cout << *(Matrix*) var << std::endl;
			break;
		}
	}
}

void Parser::parse(std::string s){
string temp,str;

int pos=0;
string temp_new;
int len=s.length();
while(1){
if(s.find('\n')!=-1)
{
 pos=pos+s.find('\n')+1;
 }
 else if(s.find('\n')==-1){
 pos=pos+s.find('\0')+1;
 }

if(pos>=len)
break;
temp=s.substr(0,s.find('\n'));
s=s.substr(s.find('\n')+1,s.length());



if(temp.find("rand")!=-1){
temp=removeSpaces(temp);
string rows,cols;
rows=temp.substr(temp.find('(')+1,temp.find(',')-temp.find('(')-1);
cols=temp.substr(temp.find(',')+1,temp.find(')')-temp.find(',')-1);
Variable* A=new Matrix (stoi(rows),stoi(cols),Matrix::random,temp.substr(0,temp.find("=")));
cout<<*A<<endl;

}
else if(temp.find("zero")!=-1){
temp=removeSpaces(temp);
string rows,cols;
rows=temp.substr(temp.find('(')+1,temp.find(',')-temp.find('(')-1);
cols=temp.substr(temp.find(',')+1,temp.find(')')-temp.find(',')-1);
Variable* A=new Matrix (stoi(rows),stoi(cols),Matrix::zero,temp.substr(0,temp.find("=")));
cout<<*A<<endl;

}
else if(temp.find("one")!=-1){
temp=removeSpaces(temp);
string rows,cols;
rows=temp.substr(temp.find('(')+1,temp.find(',')-temp.find('(')-1);
cols=temp.substr(temp.find(',')+1,temp.find(')')-temp.find(',')-1);
Variable* A=new Matrix  (stoi(rows),stoi(cols),Matrix::one,temp.substr(0,temp.find("=")));
cout<<*A<<endl;

}

else if(temp.find("eye")!=-1){
temp=removeSpaces(temp);
string rows,cols;
rows=temp.substr(temp.find('(')+1,temp.find(',')-temp.find('(')-1);
cols=temp.substr(temp.find(',')+1,temp.find(')')-temp.find(',')-1);
Variable* A=new Matrix  (stoi(rows),stoi(cols),Matrix::identity,temp.substr(0,temp.find("=")));
cout<<*A<<endl;

}

else if(temp.find("eye")==-1&&temp.find("rand")==-1&&temp.find("one")==-1&&temp.find("zero")==-1){
string new_temp=temp.substr(temp.find('=')+1,temp.length());
//cout<<new_temp<<endl;
int count=0;
for (int i=0;i<new_temp.length();i++){
if(new_temp[i]=='[')
count++;
}
if(count>1){
Variable* A= new Matrix (3,3,Matrix::identity,temp.substr(0,temp.find("=")-1));

cout<<*A<<endl;
}
else if(count==1){
//call old parser
}
for(int i=0;i<new_temp.length();i++){
if(isalpha(new_temp[i])){
string find=new_temp.substr(i,1);


Variable*  result = findVar(find);

	//if result is nullptr, then variable with this
	//name does not exist
	if(result != nullptr){
		cout <<"name "<< new_temp[i] << endl;
		cout << *result << endl;
	}
}

}

}
}
}

string Parser::find_op(string s,char c){         //this function makes all operations calculations
    int flag=0,sign_flag=0;
    string final_str = s;
    string before_str,after_str;                    //the string before and after the operation
    float result;
    int before,after;

    for(int i=1;s[i]!='\0';i++){
if(s[i]==c&&s[i-1]!='+'&&s[i-1]!='-'&&s[i-1]!='*'&&s[i-1]!='/'&&s[i-1]!='^'){
flag=1;
if(s[i+1]=='-'){
sign_flag=1;
}
if (sign_flag==1){
for(int j=i+2;j<s.length();j++){

if(s[j]=='*'||s[j]=='-'||s[j]=='+'||s[j]=='^'||s[j]=='/'){
after=j-1;
break;
}
else
after=s.length()-1;
}

}
else
for(int j=i+1;j<s.length();j++){

if(s[j]=='*'||s[j]=='-'||s[j]=='+'||s[j]=='^'||s[j]=='/'){
after=j-1;
break;
}
else
after=s.length()-1;
}
if(i-1 == 0)
before = 0;
else
for(int k=i-1;k>0;k--){

if(s[k]=='*'||s[k]=='-'||s[k]=='+'||s[k]=='^'||s[k]=='/'){
before=k+1;
break;
}
else
before=0;
}
if(sign_flag==1){
after_str="-"+s.substr(i+2,after-i-1);
before_str=s.substr(before,i-before);
}
else{
 after_str=s.substr(i+1,after-i);
before_str=s.substr(before,i-before);
}

switch (c){
case '^': {result = pow(stof(before_str),stof(after_str)); break;}
case '/': {result = stof(before_str)/stof(after_str); break;}
case'*': {result = stof(before_str)*stof(after_str); break;}
case '-' :{result = stof(before_str)-stof(after_str); break;}
case '+' :{result = stof(before_str)+stof(after_str); break;}
default:
	break;
}
string result_str=to_string(result);
 final_str= s.substr(0,before)+result_str+s.substr(after+1,s.length()-after);
break;

}
}
if(flag==1){
final_str=find_op(final_str,c);
}
else{
switch(c)
{
    case '^':final_str=find_op(final_str,'/'); break;
    case '/':final_str=find_op(final_str,'*'); break;
    case '*':final_str=find_op(final_str,'-'); break;
    case '-':final_str=find_op(final_str,'+'); break;
}

}
return final_str;

}

string Parser::find_brackets(string s){            //this function gets the string between to brackets and sends it to inf_op to calculate it and return it back
string final_str=s,to_rec;
int starts,ends;
int flag=0;
for(int i=0;i<s.length();i++){
if(s[i]=='('){
flag=1;
for (int j=i+1;j<s.length();j++){
if(s[j]==')'){
final_str= s.substr(i+1,j-i-1);
ends=j;
break;
}
}
if( final_str.find('(')!=-1){
continue;
}
if(flag==1){
starts=i;
break;
}
}
}
if(flag==1){

to_rec= s.substr(0,starts)+find_op(final_str,'^')+s.substr(ends+1,s.length()-ends);


to_rec = find_brackets(to_rec);

}
else{
to_rec = find_op(s,'^');
}


return to_rec;
}

string Parser::removeSpaces(string input)                   //remove spaces from the string
{
  //int length = input.length();
  for (int i = 0; input[i]!='\0'; i++) {
     if(input[i] == ' ')
        input.erase(i, 1);
  }
  return input;
}

string Parser::solve_trig (string s){          //this function solve all trig functions and return the string back after solving the functions
string trig;
string final_str=s;
int pos,flag=0;
if(s.find("sin")!=-1){
flag=1;
pos=s.find("sin");
trig=to_string(sin(stof(find_inside(pos,s))));
}
else if(s.find("cos")!=-1){
flag=1;
int pos=s.find("cos");
trig=to_string(cos(stof(find_inside(pos,s))));
}
else if(s.find("tan")!=-1){
flag=1;
int pos=s.find("tan");
trig=to_string(tan(stof(find_inside(pos,s))));
}

if(flag==1){
final_str=s.substr(0,pos)+trig+s.substr(s.find(')',pos)+1,s.length()-s.find(')',pos));
final_str=solve_trig(final_str);
}
return final_str;
}

string Parser::find_inside (int pos , string s){
string trig;
int strt,en;
for(int i=pos;s[i]!='\0';i++){
if(s[i]=='('){
strt=i;
break;
}
}
for(int j=strt;s[j]!='\0';j++){
if(s[j]==')')
{
en=j;
break;

}
}
trig=s.substr(strt+1,en-strt-1);
return trig;
}

Matrix findMatrix (char c, string path){

string file;
	int matrixFlag=0;
	int firstflag=0;

	int rows=1000, cols=1000;
float** matrix= new float* [rows];
	for(int i = 0; i < rows; ++i)
    matrix[i] = new float[cols];


		ifstream myfile;
		int flag=0,myflag=0;
		myfile.open(path);

		while(myfile>>file){

		for(int i=0;file[i]!='\0';i++)
		{

		if(file[i]==c)                  //finding matrix of sent char
		{
		matrixFlag=1;
		while(myfile>>file){

                    //finding first row
			for(int i=0;file[i]!='\0';i++){
				if(file[i]=='[')

				{


				if(file.length()==1)
				{
				myfile>>file;
				matrix[0][0]=stof(file);
				flag=1;

				}
				else{


				flag=1;

				matrix[0][0]=stof(file.substr(1));
				}


                int n=1;
                while(myfile>>file){



				for(int j=0;file[j]!='\0';j++){
				if(file[j]==';')
				{

				if(file.length()==1)
				myflag=2;
				else{
				if(file[0]==';'){
				matrix [1][0]=stof(file.substr(1));
				firstflag=1;
				}

				myflag=1;


				matrix[0][n]=stof(file.substr(0,file.length()-1));
				}

				}
				}
				if(myflag==0){



				matrix[0][n]=stof(file);


				n++;
				}

				else if(myflag==1)
				{
				cols=n+1;


				break;
				}
				if(myflag==2){
				cols=n;
				break;
				}
				}
				}
			}
			if(flag==1)
			{

			break;
			}

		}

		//first row found and start fidning other rows
int nrows=1+firstflag;
int thflag=0;


int ncols=0;
while(myfile>>file)
{
int semiflag=0;

matrix[nrows][ncols]=stof(file);


if(ncols==cols-1)                   //the last element in each row is stuck to ; we need to remove it
{

if(file[file.length()-1]==';'||file[file.length()-1]==']'){
if(file[file.length()-2]==']'){
matrix[nrows][ncols]=stof(file.substr(0,file.length()-2));
}
else
matrix[nrows][ncols]=stof(file.substr(0,file.length()-1));

}
else
{
matrix[nrows][ncols]=stof(file);
myfile>>file;
if(file[1]!='\0'){
matrix[nrows+1][0]=stof(file.substr(1));
nrows++;
ncols=0;
semiflag=1;
}

}



for(int i=0;file[i]!='\0';i++){

if(file[i]==']')
{
rows=++nrows;                           //rows counted

thflag=1;

}
}
if(semiflag!=1){
nrows++;
ncols=-1;
}


}
ncols++;

if(thflag==1)
break;
}
}

}


if(matrixFlag==1){

break;
}
}

myfile.close();


/*Matrix A (rows,cols,(double**)matrix,c);
return A;
for (int i=0;i<cols;i++)
delete[] matrix[i];
delete[] matrix;*/

}


