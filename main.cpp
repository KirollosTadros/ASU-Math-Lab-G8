#include <iostream>
#include <string>

using namespace std;
string find_div(string s);

int main()
{
string s="3*5/2+8/5-5/8.8*9+3/2";
cout<<find_div(s)<<endl;
    }




    string find_div(string s){
    int flag=0;
    string final_str = s;
    for(int i=0;s[i]!='\0';i++){
int before,after;
if(s[i]=='/'){
flag=1;
for(int j=i+1;j<s.length();j++){
if(s[j]=='*'||s[j]=='-'||s[j]=='+'||s[j]=='^'||s[j]=='/'){
after=j-1;
break;
}
else
after=s.length()-1;
}
for(int k=i-1;k>0;k--){
if(s[k]=='*'||s[k]=='-'||s[k]=='+'||s[k]=='^'||s[k]=='/'){
before=k+1;
break;
}
}

string after_str=s.substr(i+1,after-i);
string before_str=s.substr(before,i-before);


float result = stof(before_str)/stof(after_str);
string result_str=to_string(result);
 final_str= s.substr(0,before)+result_str+s.substr(after+1,s.length()-after);


}
}
if(flag==1){
final_str=find_div(final_str);
}


return final_str;
}
