#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include "matrix.h"
#include "reader.h"
#include "parser.h"

using namespace std;
string find_op(string s,char c);
string find_brackets (string s);
string removeSpaces(string input);
string solve_trig (string s);
string find_inside (int pos , string s);
void matrixName(string path);
Matrix findMatrix (char c, string path);


int main()
{
string s="(1.2 + 3.4 - 5.6)/(2.1*3.2 + 4.6) - 12.1*3.1 + (1.2 + 5.2)^(4/(3.2+5.6))";
//cout<<find_brackets(removeSpaces(s))<<endl;
cout<<find_brackets(solve_trig(removeSpaces(s)))<<endl;
Reader R;
Parser P;
P.parse(R.readFile());


    }




    string find_op(string s,char c){
    int flag=0,sign_flag=0;
    string final_str = s;
    string before_str,after_str;
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
default: int x=5; break;
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
    case '^':final_str=find_op(final_str,'/');
    case '/':final_str=find_op(final_str,'*');
    case '*':final_str=find_op(final_str,'-');
    case '-':final_str=find_op(final_str,'+');
    break;
}

}
return final_str;

}


string find_brackets(string s){
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

string removeSpaces(string input)                   //remove spaces from the string
{
  int length = input.length();
  for (int i = 0; input[i]!='\0'; i++) {
     if(input[i] == ' ')
        input.erase(i, 1);
  }
  return input;
}

string solve_trig (string s){
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

string find_inside (int pos , string s){
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



