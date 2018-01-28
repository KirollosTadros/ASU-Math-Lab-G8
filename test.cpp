#include "test.h"
#include "variable.h"
#include "matrix.h"
#include "number.h"
#include "parser.h"
#include <iostream>
#include <vector>

namespace test{
using namespace std;

void print(Matrix const& matrix, char const* label){
	cout << label << matrix << endl << endl;
}
void print(double value, char const* label){
	cout << label << value << endl << endl;
}

void test_matrix(){
	Matrix zero(3, 3, Matrix::zero);
	Matrix one(2, 2, Matrix::one);
	Matrix rnd(2, 4, Matrix::random);
	Matrix eye(3, 3, Matrix::identity);
	cout << zero << endl << endl;
	cout << one  << endl << endl;
	cout << rnd  << endl << endl;
	cout << eye  << endl << endl;

	print(Matrix(3, 2).fillValue(0.1), "Testing fillValue()");

	Matrix a(2, 3);
	for(int i=0; i<a.getRows(); ++i){
		for(int j=0; j<a.getCols(); ++j){
			a.setValue(i, j, i*a.getRows()+i+j+1);
		}
	}
	print(a, "a (testing setValue()");

	Matrix b(a);
	print(b, "b(a) (testing copy constructor)");

	Matrix c = a;
	print(c, "c = a (testing assignment operator)");
	cout << "c has " << c.getRows() << " row(s) and ";
	cout << c.getCols() << " col(s)" << endl << endl;

	print(a+b, "a+b = ");
	print(a-b, "a-b = ");
	print(a.transpose(), "a.transpose() = ");
	print(a*10, "a*10 = ");
	print(100*a, "100*a = ");

	Matrix x(3, 3);
	double list[][3] = {
		{3,  5,  6},
		{6, -9, 11},
		{1,  9, .5}
	};
	for(int i=0; i<x.getRows(); ++i){
		for(int j=0; j<x.getCols(); ++j){
			x.setValue(i, j, list[i][j]);
		}
	}

	Matrix y(3, 3);
	for(int i=0; i<y.getRows(); ++i){
		for(int j=0; j<y.getCols(); ++j){
			y.setValue(i, j, i*y.getRows()+j+1);
		}
	}
	print(x, "x = ");
	print(y, "y = ");

	print(eye*x, "eye * x = ");
	print(x*eye, "x * eye = ");

	print(x*x, "x * x = ");
	print(x*y, "x * y = ");

	print(x.determinant(), "det(x) = ");
	print(y.determinant(), "det(y) = ");

//	print(y.minor(1, 1), "y.minor(1, 1) = ");


	try{
		print(x/x, "x/x = ");
	}
	catch(const char* msg){
		cout << msg << endl;
	}

	print(y/x, "y/x = ");

	try{
		print(x/y, "x/y = ");
	}
	catch(const char* msg){
		cout << "Error in x/y:" << endl;
		cout << msg << endl << endl;
	}

	print(x.swapRows(1, 2), "x.swapRows(1, 2) = "); //swapping modifies the matrix


	Matrix z(3, 3);
	double list2[][3] = {
			{0, 1, 3},
			{0, 0, 9},
			{3, 6, 6}
	};
	for(int i=0; i<z.getRows(); ++i){
		for(int j=0; j<z.getCols(); ++j){
			z.setValue(i, j, list2[i][j]);
		}
	}
	print(z, "z = ");
	print(z.determinant(), "det(z) (testing swapping of rows in determinant) = ");
}

void test_variable(){
	using namespace std;

	//direct
	Matrix a(3, 3, Matrix::identity, "A");
	Number x(520, "x");
	cout << a << endl;
	cout << x << endl;

	//polymorphism
	Variable* v1 = new Matrix(2, 2, Matrix::identity, "B");
	Variable* v2 = new Number(630, "y");
	cout << *v1 << endl;
	cout << *v2 << endl;
	Matrix* m = (Matrix*) v1;
	cout << *m + *m << endl; //note: result has no name, gets a default name (var1)
	cout << *m * 0.5 << endl;
	delete v1;
	delete v2;

	//polymorphism with vector
	typedef vector<Variable*> VariableList;
	VariableList storage;
	storage.push_back(new Matrix(3, 4, Matrix::random, "C"));
	cout << *storage[0] << endl;
	delete storage[0];
}

void test_parser(){
	using namespace std;
	/*
	 * Adding variables
	 */

	Parser parser;

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
}

}
