//#include "stdafx.h"
#include "MyMatrix.h"
#include <iostream>
#include <iomanip>
using namespace std;

void debug(const char* msg){
//	cout << msg << endl;
}
void debug2(const char* msg){
	// cout << msg << endl;
}


MyMatrix::MyMatrix(){
	rows = -1;
	cols = -1;
	Matrix = 0;
	debug("Empty constructor called");
};
MyMatrix::MyMatrix(int rows, int cols){
	this->rows = rows;
	this->cols = cols;
	float **mat = new float*[rows];
	for(int i=0; i<rows; i++){
		mat[i] = new float[cols];
	}
	this->Matrix = mat;
}
MyMatrix::MyMatrix(float **Matrix, int rows, int cols)
{
	//allocate memory for MyMatrix,
	//and fill with values from Matrix argument
	float **mat = new float*[rows];
	for(int i=0; i<rows; i++){
		mat[i] = new float[cols];
	}
	this->Matrix = mat;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			this->Matrix[i][j] = Matrix[i][j];
		}
	}
	this->rows = rows;
	this->cols = cols;
	debug("constr done");
}
MyMatrix::~MyMatrix()
{
	
	for(int i=0;i<rows;i++){
		delete[] Matrix[i];
	}
	delete[] Matrix;
	debug("destr done");
	
}
// void MyMatrix::make(float **Mat, int x, int y)
// { //Function that creates the Matrix
	// rows = x;
	// cols = y;
	// Matrix = Mat;
// }
void MyMatrix::empty()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Matrix[i][j] = 0;
		}
	}
}

float **MyMatrix::getMatrix()
{ //Returns the Matrix pointer
	return Matrix;
}

int MyMatrix::getCols()
{ //Return Number of Rows
	return cols;
}

int MyMatrix::getRows()
{ //Return Number of Rows
	return rows;
}

MyMatrix MyMatrix::operator+(MyMatrix &b){

	float **c = new float *[this->rows];
	for (int i = 0; i < this->rows; ++i)
		c[i] = new float[this->cols];


	if (this->rows != b.getRows() || this->cols != b.getCols())
	{
	}

	float **A = this->Matrix;
	float **B = b.getMatrix();
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			c[i][j] = A[i][j] + B[i][j];
		}
	}

	MyMatrix C(c, this->rows, this->cols);
	//free allocated memory
	for(int i=0; i<rows; i++){
		delete [] c[i];
	}
	delete[] c;
	return C;
}

MyMatrix MyMatrix::operator-(MyMatrix &b){

	float **c = new float *[this->rows];
	for (int i = 0; i < this->rows; ++i)
		c[i] = new float[this->cols];

	if (this->rows != b.getRows() || this->cols != b.getCols())
	{
	}

	float **A = this->Matrix;
	float **B = b.getMatrix();
	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < this->cols; j++)
		{
			c[i][j] = A[i][j] - B[i][j];
		}
	}

	MyMatrix C(c, this->rows, this->cols);
	//free allocated memory
	for(int i=0; i<rows; i++){
		delete [] c[i];
	}
	delete[] c;
	return C;
}

MyMatrix MyMatrix::operator*(MyMatrix &b){

	float **c = new float *[this->rows];
	for (int i = 0; i < this->rows; ++i)
		c[i] = new float[b.cols];

	for (int i = 0; i < this->rows; i++)
	{
		for (int j = 0; j < b.cols; j++)
		{
			c[i][j] = 0;
		}
	}

	float **A = this->Matrix;
	float **B = b.getMatrix();

	for (int i = 0; i < (this->rows); i++) // result row
	{
		for (int g = 0; g < b.cols; g++) // second matrix and result coloumn
		{
			for (int j = 0; j < b.rows; j++) // first and second matrix coloumn and row (browsize or acolsize must be equal whatever)
			{
				c[i][g] = c[i][g] + (A[i][j] * B[j][g]);
			}
		}
	}
	
	//C.empty();
	MyMatrix C(c, this->rows, b.cols);
	//free allocated memory
	for(int i=0; i<rows; i++){
		delete [] c[i];
	}
	delete[] c;
	return C;
}

MyMatrix MyMatrix::operator--(){
	debug("started --");
	float **A = this->Matrix;
	float **B = new float*[cols];
	for(int i=0; i<cols; i++){
		B[i] = new float[rows];
	}
	for (int i = 0; i < this->rows; i++){
		for (int j = 0; j < this->cols; j++){
			B[i][j] = A[j][i];
		}
	}
	MyMatrix C = MyMatrix(B, this->cols, this->rows);
	//free allocated memory
	for(int i=0; i<rows; i++){
		delete [] B[i];
	}
	delete[] B;
	return C;
}

MyMatrix MyMatrix::elemMul(float elem){
	MyMatrix result(Matrix, rows, cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			result.Matrix[i][j] *= elem;
		}
	}
	return result;
}

MyMatrix MyMatrix::elemDiv(float elem){
	//todo check division by zero
	MyMatrix result(Matrix, rows, cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			result.Matrix[i][j] = elem / result.Matrix[i][j];
		}
	}
	return result;
}

MyMatrix MyMatrix::inverse(){
	//todo check if matrix can be inverted
	//get matrix of cofactors
	float d = this->det();
	// cout << "got determinant of whole matrix" << endl << endl; //todo remove det
	try{
		if(d <= 0){
			throw -1;
		}
	}
	catch(...){
		throw;
	}
	int sign;
	//actually not a cofactors matrix
	//because it's multiplied by 1/determinant
	//for performance
	MyMatrix cofactors(rows, cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			sign = ((i+1+j+1) % 2 == 0) ? 1 : -1;
			//cout << "Getting cofactor of element: " << i << ", " << j << endl; //todo remove det
			cofactors.Matrix[i][j] =  d * sign * this->get_minor_matrix(i+1,j+1).det();
		}
	}
	cofactors = --cofactors; //transpose
	return cofactors;
}

MyMatrix::MyMatrix(const MyMatrix &other){
	debug("copy constr called");
	rows = other.rows;
	cols = other.cols;
	float** x = new float*[rows];
	for(int i=0; i<rows; i++){
		x[i] = new float[cols];
	}
	Matrix = x;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			Matrix[i][j] = other.Matrix[i][j];
		}
	}
}

MyMatrix MyMatrix::operator=(const MyMatrix &rhs){
	debug("(=) operator called");
	//clean old matrix
	//if it was previously initialized
	if(Matrix){
		for(int i=0; i<rows; i++){
			delete [] Matrix[i];
		}
		delete [] Matrix;
	}
	//copy rhs MyMatrix
	rows = rhs.rows;
	cols = rhs.cols;
	float** x = new float*[rows];
	for(int i=0; i<rows; i++){
		x[i] = new float[cols];
	}
	Matrix = x;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			Matrix[i][j] = rhs.Matrix[i][j];
		}
	}
	//return
	return *this;
}

MyMatrix MyMatrix::get_minor_matrix(int row, int col){
	//return a matrix that is the same
	//as the calling matrix, but with its
	//'row' and 'col' removed
	MyMatrix result(Matrix, rows-1, cols-1);
	int source_i, source_j;
	for(int i=0; i<rows-1; i++){
		source_i = (i>=row-1) ? i+1 : i;
		for(int j=0; j<cols-1; j++){
			source_j = (j>=col-1) ? j+1 : j;
			result.Matrix[i][j] = Matrix[source_i][source_j];
		}
	}
	return result;
}

MyMatrix MyMatrix::right_divide(MyMatrix &rhs){
	debug("right_divide called");
	MyMatrix b = rhs.inverse();
	return *this * b;
}

MyMatrix MyMatrix::operator/(MyMatrix &rhs){
	debug("operator (/) called");
	MyMatrix inv = rhs.inverse();
	return *this * inv;
}

void MyMatrix::print(){
	cout << endl;
	cout<<"["<<endl;
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			cout<< Matrix[i][j]<<" ";

		}
			cout <<";"<< endl<<endl;

	}
	cout<<"]"<<endl;

	cout << endl;
}

float MyMatrix::det(){
	//calcluate determinant using Gauss elimination
	//todo: handle non-square matrices
	if(cols == 2){
		return Matrix[0][0] * Matrix[1][1] - Matrix[0][1] * Matrix[1][0];
	}else if(cols == 1){
		return Matrix[0][0];
	}else{
		//copy the matrix because it will be modified
		MyMatrix d(Matrix, rows, cols);
		int sign = 1;
		float multiplier;
		//for each column except last one...
		for(int j=0; j<cols-1; j++){
			//for all elements below the diagonal
			for(int i=j+1; i<rows; i++){
				if(d.Matrix[j][j] == 0){
					//can't use zero as pivot element
					//find the first non-zero element in same column
					int row_index = 0; //the row we're looking for can't be zero (row_index >= 2)
					for(int r=i; r<rows; r++){
						if(d.Matrix[r][j] != 0){
							row_index = r;
							break;
						}
					}
					if(row_index){
						d.swapRows(j, row_index);
						//change sign for every row swap
						sign *= -1;
					}else{
						//didn't found a non-zero element,
						//determinant is zero
						return 0;
					}
				}
				multiplier = d.Matrix[i][j] / d.Matrix[j][j];
				//for all elements in the row of the current element
				for(int k=0; k<cols; k++){
					d.Matrix[i][k] = d.Matrix[i][k] - d.Matrix[j][k] * multiplier;
				}
			}
		}
		//determinant = (-1)^number_of_swaps * product of diagonal elements
		float result = 1;
		for(int i=0; i<rows; i++){
			result *= d.Matrix[i][i];
		}
		return sign * result;
	}
}

void MyMatrix::swapRows(int row1, int row2){
	//swap row1 with row2
	//todo: check arguments are in range
	float tmp;
	for(int j=0; j<cols; j++){
		tmp = Matrix[row1][j];
		Matrix[row1][j] = Matrix[row2][j];
		Matrix[row2][j] = tmp;
	}
}
