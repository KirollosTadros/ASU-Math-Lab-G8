#include "matrix.h"
#include <cstdlib> 	//rand()
#include <ctime>	//rand()
#include <cstddef> 	//nullptr
#include <iostream>
#include <sstream>
#include <cmath>


double** Matrix::memAllocate(int rows/**< [in] number of rows */, int cols/**< [in] number of columns */){
	/**
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
	/**
	 * deletes memory allocated using Matrix::memAllocate()
	 */
	for(int i=0; i<rows; ++i){
		delete[] mem[i];
	}
	delete[] mem;
}


Matrix::Matrix(int rows/**< [in] number of rows */, int cols/**< [in] number of columns */, std::string name/**< [in] name of matrix */)
: Variable(name, Variable::matrix), rows(rows), cols(cols) {
	values = memAllocate(rows, cols);
}

Matrix::Matrix(int rows/**< [in] number of rows */, int cols/**< [in] number of columns */, fillType ft/**<[in] fill Type*/, std::string name/**< [in] name of matrix */)
: Variable(name, Variable::matrix), rows(rows), cols(cols) {
	values = memAllocate(rows, cols);
	fill(ft);
}

Matrix::Matrix(int rows/**< [in] number of rows */, int cols/**< [in] number of columns */, double** array/**< [in] array to be copied*/, std::string name/**< [in] name of matrix */)
: Variable(name, Variable::matrix), rows(rows), cols(cols) {
	values = memAllocate(rows, cols);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			values[i][j] = array[i][j];
		}
	}
}

Matrix::Matrix(int rows/**< [in] number of rows */, int cols/**< [in] number of columns */, float** array/**< [in] array to be copied*/, std::string name/**< [in] name of matrix */)
: Variable(name, Variable::matrix), rows(rows), cols(cols) {
    values = memAllocate(rows, cols);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			values[i][j] = array[i][j];
		}
	}
}

Matrix::Matrix(Matrix const& other /**<[in] Matrix to be copied*/) : Matrix(other.rows, other.cols) {
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			values[i][j] = other.values[i][j];
		}
	}
}

Matrix& Matrix::operator=(Matrix const& rhs){
	/**
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

Matrix Matrix::rand(int rows /**<[in] number of rows*/, int cols/**<[in] number of columns*/) {
	/**Creates a Matrix of random numbers*/
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
	return C;///\return a Matrix
}

Matrix Matrix::zeroes(int rows/**<[in] number of rows*/, int cols/**<[in] number of columns*/) {
	/**Creates a Matrix of zeros*/
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
	return C;///\return a Matrix
}

Matrix Matrix::eye(int rows/**<[in] number of rows*/, int columns/**<[in] number of columns*/) {
	/**Creates a Matrix of ones on the main diagonal and zeros elsewhere*/
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
	return mat;///\return a Matrix
}

Matrix Matrix::ones(int rows/**<[in] number of rows*/, int columns/**<[in] number of columns*/) {
	/**Creates a Matrix of ones*/
	int size = rows;
	Matrix mat(size, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat.setValue(i, j, 1);
		}
	}
	return mat;///\return a Matrix
}

Matrix& Matrix::fill(fillType ft){
	/**
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
	return *this;///\return a Matrix
}

Matrix& Matrix::fillValue(double value /**<[in] value to fill matrix with*/){
	/**
	 * fills the matrix with the given (value)
	 */
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			values[i][j] = value;
		}
	}
	return *this;///\return a Matrix
}

Matrix& Matrix::fillPart(int row, int col, Matrix const& fillMatrix){
	/**
	 * Fills part of the matrix, starting at row and col, with
	 * another fillMatrix
	 * Returns itself
	 */
	//TODO implement the function
}



Matrix Matrix::add(Matrix const& rhs /**<[in] Matrix to be added*/) const{
	/**adds Matrices together*/
	Matrix result(rows, cols);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			result.values[i][j] = values[i][j] + rhs.values[i][j];
		}
	}
	return result;///\return a new Matrix
}

Matrix Matrix::sub(Matrix const& rhs/**<[in] Matrix to be subtracted*/) const{
	/**subtractes Matrices together*/
	Matrix result(rows, cols);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			result.values[i][j] = values[i][j] - rhs.values[i][j];
		}
	}
	return result;///\return a new Matrix
}

Matrix Matrix::mul(Matrix const& rhs/**<[in] Matrix to be multiplied*/) const{
	/**multiplies Matrices together*/
	Matrix result(rows, rhs.cols, zero);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<rhs.cols; ++j){
			for(int k=0; k<rhs.rows; ++k){
				result.values[i][j] += values[i][k] * rhs.values[k][j];
			}
		}
	}
	return result;///\return a new Matrix
}

Matrix Matrix::rightDiv(Matrix const& rhs/**<[in] Matrix to be right divided*/) const{
	/** calculates the "Right-division", see <a href="https://www.mathworks.com/">Matlab</a>'s definition of <a href="https://www.mathworks.com/help/matlab/ref/rdivide.html">Right array division</a> */
	return this->mul(rhs.inverse());///\return a new Matrix
}

Matrix Matrix::inverse() const{
	/** Calculates the inverse of the matrix*/

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
	return cofactors.transpose();///\return an inversed Matrix
}

Matrix Matrix::transpose() const{
	Matrix result(cols, rows);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			result.values[j][i] = values[i][j];
		}
	}
	return result;///\return the transposed Matrix
}

Matrix Matrix::getMinor(int row /**<[in] number of rows to be removed*/, int col/**<[in] number of columns to be removed*/) const{
	/**get the minor matrix,
	 * __Note: row and col start from 1__
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

Matrix Matrix::elemMul(double scalar/**<[in]number to be multiplied with*/) const{
	/**element-wise multiplication with a constant number*/
	Matrix result(*this);
	for(int i=0; i<rows; ++i){
		for(int j=0; j<cols; ++j){
			result.values[i][j] *= scalar;
		}
	}
	return result;///\return a new Matrix
}

Matrix Matrix::elemPow(double exponent) const{
	/**element-wise exponenial with a constant number*/
	//TODO implement the function
}

double Matrix::determinant() const{
	/**Calcluate determinant using __Gauss elimination__*/
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
		return sign * result;///\return a double-type number
	}
}

Matrix& Matrix::swapRows(int row1/**<[in] first row*/, int row2/**<[in] second row to be swapped with the first*/){
	/** swaps row1 with row2 within the matrix,__Note: row1 and row2 starts from 1__*/
	double tmp;
	row1 -= 1;
	row2 -= 1;
	for(int j=0; j<cols; j++){
		tmp = values[row1][j];
		values[row1][j] = values[row2][j];
		values[row2][j] = tmp;
	}
	return *this;///\return the same Matrix after modification
}


Matrix Matrix::sin() {
	/**element-wise sine function*/
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

	return C;///\return a new Matrix
}

Matrix Matrix::cos() {
	/**element-wise cosine function*/
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
	return C;///\return a new Matrix
}

Matrix Matrix::tan() {
	/**element-wise tangent function*/
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
	return C;///\return a new Matrix
}

Matrix Matrix::asin() {
	/**element-wise arcsine function*/
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
	return C;///\return a new Matrix
}

Matrix Matrix::acos() {
	/**element-wise arccosine function*/
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
	return C;///\return a new Matrix
}

Matrix Matrix::atan() {
	/**element-wise arctangent function*/
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
	return C;///\return a new Matrix
}

Matrix Matrix::log() {
	/**element-wise logarithm function*/
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
	return C;///\return a new Matrix
}

Matrix Matrix::log10() {
	/**element-wise logarithm with the base of 10 function*/
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
	return C;///\return a new Matrix
}

Matrix Matrix::pow(double exponent) {
	/**element-wise exponenial with a constant number*/
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
	return C;///\return a new Matrix
}

Matrix Matrix::sqrt() {
	/**element-wise square-root function*/
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
	return C;///\return a new Matrix
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
	/**print the Matrix*/
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
	return ss.str();///\return a string
}

std::ostream& operator<<(std::ostream& out, Matrix const& matrix){
	out << matrix.getString();
	return out;
}


