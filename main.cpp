#include <iostream>
#include <fstream>
#include <string>
#include "MyMatrix.h"
using namespace std;
void matrixName(string path);
MyMatrix findMatrix (char c, string path);
string removeSpaces(string input);
int findResult(char c);
int findWhere(char c);
int n=100;
char* name;
MyMatrix* A;
int main(int argc, char* argv[])
{

	//handle wrong command line arguments
	//usage: ./matrix <filename>
	//example: ./matrix bigexample.m
	/*if(argc < 2){
		cout << "Wrong number of arguments" << endl;
		cout << "Usage: matrix <filename>" << endl;
		return 1;
	}*/

	ifstream files;
	/*try{
		files.open(argv[1]);
	}
	catch(...){
		cout << "Error opening file" << endl;
		return 1;
	*/

string path ="example1.m";
	name = new char[n];
matrixName(path);                       //Finds matrices names from file and adds them to name array

	A= new MyMatrix[5*n];




for(int i=0;i<n;i++){
A[i]=findMatrix(name[i],path);         //finds the matrices of the names found from the previous function
}





string file;
int flag=0;
ifstream myfile;
myfile.open(path);
while(!myfile.eof()){

getline(myfile,file);

for(int i=0;file[i]!='\0';i++){

if(file[i]=='=')
{


string s=removeSpaces(file);                    //finds the line that caontains equal and [ which is a operation not matrix
int pos=s.find("=");
if(s[pos+1]!='[')
{
cout<<file<<endl;

if(s.length()==4){                              //special case for the equal operator
A[findResult(s[0])]=A[findWhere(s[2])];
cout<<name[findResult(s[0])]<<"="<<endl;
A[findResult(s[0])].print();

}

if(s.length()>7){                               //special case for the the ./ oerator for number greater the 9
float div=stof(s.substr(s.find("=")+1,s.find(",")-s.find("=")));

A[findResult(s[0])]=A[findWhere(s[s.find("/")+1])].elemDiv(div);
cout<<name[findResult(s[0])]<<"="<<endl;
A[findResult(s[0])].print();

}

switch(s[3])                    //all operator cases
{


 case '+' : {


int r=findResult(s[0]);


A[r]=A[findWhere(s[2])]+A[findWhere(s[4])];
cout<<name[findResult(s[0])]<<"="<<endl;
A[r].print();

 } break;


 case '-' : {


 A[findResult(s[0])]=A[findWhere(s[2])]-A[findWhere(s[4])];
cout<<name[findResult(s[0])]<<"="<<endl;
A[findResult(s[0])].print();} break;


 case '*' : {
 A[findResult(s[0])]=A[findWhere(s[2])]*A[findWhere(s[4])];
cout<<name[findResult(s[0])]<<"="<<endl;
A[findResult(s[0])].print();

 } break;


 case '/' : {


 A[findResult(s[0])]=A[findWhere(s[2])]/A[findWhere(s[4])];
cout<<name[findResult(s[0])]<<"="<<endl;
A[findResult(s[0])].print();

 } break;



 case '.' : {
 A[findResult(s[0])]=A[findWhere(s[5])].elemDiv((float)(s[2]-'0'));
cout<<name[findResult(s[0])]<<"="<<endl;
A[findResult(s[0])].print();


 } break;



 case '\'' : {
 A[findResult(s[0])]=--A[findWhere(s[2])];
cout<<name[findResult(s[0])]<<"="<<endl;
A[findResult(s[0])].print();

 } break;


}

}

}
}


}
myfile.close();
delete[] A;
delete[] name;
}

void matrixName(string path)
{


	ifstream myfile;
	string file;

	myfile.open(path);
	n=0;

	while(!myfile.eof()){
	getline(myfile,file);
	for(int i=0;file[i]!='\0';i++){
	if(file[i]=='='){
	string s=removeSpaces(file);
	int pos=s.find("=");
	if(s[pos+1]=='['){                  //if = si followed by [ after removing spaces then it is a mtrix we need to stor its name
	n++;

	name[n-1]=s[0];

	}
	}
	}



	}

	myfile.close();


}



MyMatrix findMatrix (char c, string path){

string file;
	int matrixFlag=0;

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

                    //findinf first row
			for(int i=0;file[i]!='\0';i++){
				if(file[i]=='[')

				{


				if(file.length()==1)
				{
				myfile>>file;
				matrix[0][0]==stof(file);
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


				myflag=1;


				matrix[0][n]=stof(file.substr(0,file.length()-1));

				}
				}
				if(myflag!=1){



				matrix[0][n]=stof(file);





				n++;
				}

				else
				{
				cols=n+1;


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
int nrows=1;
int thflag=0;

int ncols=0;
while(myfile>>file)
{


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

}



for(int i=0;file[i]!='\0';i++){

if(file[i]==']')
{
rows=++nrows;                           //rows counted

thflag=1;

}
}

nrows++;
ncols=-1;


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



MyMatrix A (matrix,rows,cols);
return A;
for (int i=0;i<cols;i++)
delete[] matrix[i];
delete[] matrix;

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

int findResult (char c){                            //finds the position of the result matrix in the array and if doesn't exit creat one
int myFlag=0;
for(int i=0;i<n;i++){

 if(c==name[i]){
 return i;
 myFlag=1;
 break;
 }

 }
 if(myFlag!=1){
 n++;
 name[n-1]=c;
 return n-1;
 }
}


int findWhere(char c){                          //find position of given matrix in array

for(int i=0;i<n;i++){
if(name[i]==c)
return i;
}


}
