#include "matrix.h"
#include <cstdlib> 	//rand()
#include <ctime>	//rand()
#include <cstddef> 	//nullptr
#include <iostream>
#include <sstream>
#include <cmath>


double** Matrix::memAllocate(int rows, int cols){
	/*
	 * allocates memory for 2D array (rows x cols)
	 * of doubles
	 */
	double** tmp = new double*[rows];
	for(int i=0; i<rows; ++i){
		tmp[i] = new double[cols];
	}
	return tmp;
}

void Matrix::memDelete(double** mem, int rows){
	/*
	 * deletes memory allocated using Matrix::memAllocate()
	 */
	for(int i=0; i<rows; ++i){
		delete[] mem[i];
	}
	delete[] mem;
}


Matrix::Matrix(int rows, int cols, std::string name)
: Variable(name, Variable::matrix), rows(rows), cols(cols) {
	values = memAllocate(rows, cols);
}

Matrix::Matrix(int rows, int cols, fillType ft, std::string name)
: Variable(name, Variable::matrix), rows(rows), cols(cols) {
	values = memAllocate(rows, cols);
	fill(ft);
}

Matrix::Matrix(int rows, int cols, double** array, std::string name)
: Variable(name, Variable::matrix), rows(rows), cols(cols) {
	values = memAllocate(rows, cols);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			values[i][j] = array[i][j];
		}
	}
}

Matrix::Matrix(int rows, int cols, float** array, std::string name)
: Variable(name, Variable::matrix), rows(rows), cols(cols) {
    values = memAllocate(rows, cols);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			values[i][j] = array[i][j];
		}
	}
}

Matrix::Matrix(Matrix const& other) : Matrix(other.rows, other.cols) {
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			values[i][j] = other.values[i][j];
		}
	}
}

Matrix& Matrix::operator=(Matrix const& rhs){
	/*
	 * deep copies the rhs (right-hand side) matrix
	 * to lhs matrix
	 * Returns: lhs matrix
	 */
	//check if already same dimensions, to speed
	//up the copy process
	if(rows == rhs.rows && cols == rhs.cols){
		for(int i=0; i<rows; ++i){
			for(int j=0; j<cols; ++j){
				values[i][j] = rhs.values[i][j];
			}
		}
	}else{
		memDelete(values, rows);
		rows = rhs.rows;
		cols = rhs.cols;
		values = memAllocate(rows, cols);
		for(int i=0; i<rows; ++i){
			for(int j=0; j<cols; ++j){
				values[i][j] = rhs.values[i][j];
			}
		}
	}
	return *this;
}

Matrix::~Matrix(){
	memDelete(values, rows);
}

Matrix Matrix::rand(int rows, int cols) {
	double** mat = new double*[rows];
	for(int i = 0; i < rows; i++){
		mat[i] = new double[cols];
	}
	srand(time(0));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			mat[i][j] = std::rand() % 6;
		}
	}
	Matrix C(rows, cols, mat);
	return C;
}

Matrix Matrix::zeroes(int rows, int cols) {
	double** mat = new double*[rows];
	for(int i = 0; i < rows; i++){
		mat[i] = new double[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			mat[i][j] = 0;
		}
	}
	Matrix C(rows, cols, mat);
	return C;
}

Matrix Matrix::eye(int rows, int columns) {
	int size = rows;
	Matrix mat(size, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) {
				mat.setValue(i, j, 1);
			} else {
				mat.setValue(i, j, 0);
			}
		}
	}
	return mat;
}

Matrix Matrix::ones(int rows, int columns) {
	int size = rows;
	Matrix mat(size, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat.setValue(i, j, 1);
		}
	}
	return mat;
}

Matrix& Matrix::fill(fillType ft){
	/*
	 * Fills the matrix with values according
	 * to the given Matrix::fillType
	 */
	switch(ft){
	case(zero):
		*this = Matrix::zeroes(rows, cols);
	break;
	case(one):
		*this = Matrix::ones(rows, cols);
	break;
	case(identity):
		*this = Matrix::eye(rows, cols);
	break;
	case(random):
		*this = Matrix::rand(rows, cols);
	break;
	}
	return *this;
}

Matrix& Matrix::fillValue(double value){
	/*
	 * fills the matrix with the given (value)
	 */
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			values[i][j] = value;
		}
	}
	return *this;
}

Matrix& Matrix::fillPart(int row, int col, Matrix const& fillMatrix){
	/*
	 * Fills part of the matrix, starting at row and col, with
	 * another fillMatrix
	 * Returns itself
	 */
	//TODO implement the function
}


/*
 * Matrix operations
 */

Matrix Matrix::add(Matrix const& rhs) const{
	/*
	 * adds matrix to rhs and returns result as
	 * a new matrix
	 */
	Matrix result(rows, cols);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			result.values[i][j] = values[i][j] + rhs.values[i][j];
		}
	}
	return result;
}

Matrix Matrix::sub(Matrix const& rhs) const{
	/*
	 * subtracts rhs matrix from *this and returns
	 * result as a new matrix
	 */
	Matrix result(rows, cols);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			result.values[i][j] = values[i][j] - rhs.values[i][j];
		}
	}
	return result;
}

Matrix Matrix::mul(Matrix const& rhs) const{
	Matrix result(rows, rhs.cols, zero);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<rhs.cols; ++j){
			for(int k=0; k<rhs.rows; ++k){
				result.values[i][j] += values[i][k] * rhs.values[k][j];
			}
		}
	}
	return result;
}

Matrix Matrix::rightDiv(Matrix const& rhs) const{
	/*
	 * calculates the "Right division",
	 * (see matlab's definition of right-division)
	 */
	return this->mul(rhs.inverse());
}

Matrix Matrix::inverse() const{
	/*
	 * gets the inverse of the matrix
	 */

	//get matrix of cofactors,
	//actually not exactly the matrix of cofactors,
	//because it's multiplied by 1/determinant
	//for performance
	double d = determinant();
	try{
		if(d == 0){
			throw "Error: Cannot get inverse (determinant equals zero)";
		}
	}
	catch(const char* error_msg){
		throw;
	}
	d = 1/d;
	int sign;
	Matrix cofactors(rows, cols);
	for(int i=0; i<rows; i++){
		for(int j=0; j<cols; j++){
			sign = ((i+1+j+1) % 2 == 0) ? 1 : -1;
			cofactors.values[i][j] =  d * sign * getMinor(i+1, j+1).determinant();
		}
	}
	return cofactors.transpose();
}

Matrix Matrix::transpose() const{
	Matrix result(cols, rows);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			result.values[j][i] = values[i][j];
		}
	}
	return result;
}

Matrix Matrix::getMinor(int row, int col) const{
	/*
	 * get the minor matrix, by removing the
	 * given row and col,
	 * Note: row and col start from 1
	 */
	Matrix result(rows-1, cols-1);
	int source_i, source_j;
	for(int i=0; i<rows-1; ++i){
		source_i = (i >= row-1) ? i+1 : i;
		for(int j=0; j<cols-1; ++j){
			source_j = (j >= col-1) ? j+1 : j;
			result.values[i][j] = values[source_i][source_j];
		}
	}
	return result;
}

Matrix Matrix::elemMul(double scalar) const{
	/*
	 * element-wise multiplication,
	 * Returns a new matrix where each element
	 * is multiplied by the given scalar
	 */
	Matrix result(*this);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			result.values[i][j] *= scalar;
		}
	}
	return result;
}

Matrix Matrix::elemPow(double exponent) const{
	/*
	 * element-wise power,
	 * Returns a new matrix where each element
	 * is the element to the power of the
	 * given (exponent)
	 */
	//TODO implement the function
}

double Matrix::determinant() const{
	/*
	 * calcluate determinant using Gauss elimination
	 */
	if(cols == 2){
		return values[0][0] * values[1][1] - values[0][1] * values[1][0];
	}else if(cols == 1){
		return values[0][0];
	}else{
		//copy the matrix because it will be modified
		Matrix d(*this);
		int sign = 1;
		double multiplier;
		//for each column except last one...
		for(int j=0; j<cols-1; j++){
			//for all elements below the diagonal
			for(int i=j+1; i<rows; i++){
				if(d.values[j][j] == 0){
					//can't use zero as pivot element,
					//find the first non-zero element in same column
					int row_index = 0; //the row we're looking for can't be zero (row_index >= 2)
					for(int r=i; r<rows; r++){
						if(d.values[r][j] != 0){
							row_index = r;
							break;
						}
					}
					if(row_index){
						d.swapRows(j+1, row_index+1);
						//change sign for every row swap
						sign *= -1;
					}else{
						//didn't found a non-zero element,
						//determinant is zero
						return 0;
					}
				}
				multiplier = d.values[i][j] / d.values[j][j];
				//for all elements in the row of the current element
				for(int k=0; k<cols; k++){
					d.values[i][k] = d.values[i][k] - d.values[j][k] * multiplier;
				}
			}
		}
		//determinant = (-1)^number_of_swaps * product of diagonal elements
		double result = 1;
		for(int i=0; i<rows; i++){
			result *= d.values[i][i];
		}
		return sign * result;
	}
}

Matrix& Matrix::swapRows(int row1, int row2){
	/*
	 * swaps row1 with row2 of the matrix in-place,
	 * i.e. it modifies the matrix itself,
	 * Note: row1 and row2 starts from 1
	 * Returns itself
	 */
	double tmp;
	row1 -= 1;
	row2 -= 1;
	for(int j=0; j<cols; j++){
		tmp = values[row1][j];
		values[row1][j] = values[row2][j];
		values[row2][j] = tmp;
	}
	return *this;
}


Matrix Matrix::sin() {

	//allocate temp 2d array
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::sin(getValue(i, j));
		}
	}
	Matrix C(this->rows, this->cols, c);

	//delete temp 2d array
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;

	return C;
}

Matrix Matrix::cos() {
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::cos(getValue(i, j));
		}
	}
	Matrix C(this->rows, this->cols, c);
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;
	return C;
}

Matrix Matrix::tan() {
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::tan(getValue(i, j));
		}
	}
	Matrix C(this->rows, this->cols, c);
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;
	return C;
}

Matrix Matrix::asin() {
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::asin(getValue(i, j));
		}
	}
	Matrix C(this->rows, this->cols, c);
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;
	return C;
}

Matrix Matrix::acos() {
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::acos(getValue(i, j));
		}
	}
	Matrix C(this->rows, this->cols, c);
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;
	return C;
}

Matrix Matrix::atan() {
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::atan(getValue(i, j));
		}
	}
	Matrix C(this->rows, this->cols, c);
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;
	return C;
}

Matrix Matrix::log() {
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::log(getValue(i, j));
		}
	}
	Matrix C(this->rows, this->cols, c);
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;
	return C;
}

Matrix Matrix::log10() {
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::log10(getValue(i, j));
		}
	}
	Matrix C(this->rows, this->cols, c);
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;
	return C;
}

Matrix Matrix::pow(double exponent) {
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::pow(getValue(i, j), exponent);
		}
	}
	Matrix C(this->rows, this->cols, c);
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;
	return C;
}

Matrix Matrix::sqrt() {
	double **c = new double *[this->rows];
	for (int i = 0; i < this->rows; i++) {
		c[i] = new double[this->cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			c[i][j] = std::sqrt(getValue(i, j));
		}
	}
	Matrix C(this->rows, this->cols, c);
	for (int i = 0; i < rows; i++) {
		delete[] c[i];
	}
	delete[] c;
	return C;
}



/*
 * Overloaded operators for Matrix operations
 */


Matrix Matrix::operator+(Matrix const& rhs) const{
	return add(rhs);
}

Matrix Matrix::operator-(Matrix const& rhs) const{
	return sub(rhs);
}

Matrix Matrix::operator*(Matrix const& rhs) const{
	return mul(rhs);
}

Matrix Matrix::operator*(double scalar) const{
	return elemMul(scalar);
}

Matrix operator*(double lhs_scalar, Matrix const& rhs_matrix){
	return rhs_matrix.elemMul(lhs_scalar);
}

Matrix Matrix::operator/(Matrix const& rhs) const{
	return rightDiv(rhs);
}



std::string Matrix::getString() const{
	std::ostringstream ss;
	ss << name << " = ";
	ss << "[" << std::endl;
	for(int i=0; i<rows; ++i){
		if(i != 0) {ss << std::endl;}
		for(int j=0; j<cols; ++j){
			if(j != 0) {ss << " ";}
			ss << values[i][j];
		}
		ss << ";";
	}
	ss << std::endl << "]";
	return ss.str();
}

std::ostream& operator<<(std::ostream& out, Matrix const& matrix){
	out << matrix.getString();
	return out;
}


