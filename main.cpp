#include "variable.h"
#include "matrix.h"
#include "number.h"
#include "parser.h"
#include "reader.h"
#include <iostream>

#include "test.h" //remove on delivery

using namespace std;

int main(int argc, char* argv[]){

	Parser parser;

	/*
	 * Adding variables
	 */

	//adding a number variable called x
	parser.addVar(new Number(500, "x"));

	//adding a number variable called y
	parser.addVar(new Number(-3, "y"));

	//adding a matrix variable called A
	Variable* some_variable = new Matrix(3, 3, "A");

	//cast (Variable*) to (Matrix*) to use matrix methods
	Matrix* tmp = (Matrix*) some_variable;

	//fill matrix with sequential numbers
	for(int i=0; i<tmp->getRows(); ++i){
		for(int j=0; j<tmp->getCols(); ++j){
			tmp->setValue(i, j, i*3+j+1);
		}
	}
	parser.addVar(tmp);


	/*
	 * Reading variables
	 */

	//get variable y from vector
	Variable* result = parser.findVar("y");

	//if result is nullptr, then variable with this
	//name does not exist
	if(result != nullptr){
		cout << "The number is:" << endl;
		cout << *result << endl;
	}

	//get variable A from vector
	result = parser.findVar("A");
	//check if not null
	if(result){
		//get transpose of matrix,
		//we know type of A is matrix,
		//we have to cast it first
		Matrix* t = (Matrix*) result;
		*t = t->transpose(); //note the *

		//print
		cout << "The transpose of matrix is:" << endl;
		cout << *t << endl << endl;	//again: note the *
		cout << "Multipling matrix by 0.1:" << endl;
		cout << *t * 0.1 << endl;
	}


	//print all saved variables
	cout << endl;
	cout << "All variables:" << endl;
	parser.printVars();


    return 0;
}
