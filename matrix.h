#ifndef MATRIX_H
#define MATRIX_H

#include "variable.h"
#include <iostream>

class Matrix : public Variable{
private:
	int rows;
	int cols;
	double** values;
	double** memAllocate(int rows, int cols);
	void memDelete(double** mem, int rows);
public:
	enum fillType{zero, one, random, identity};
	Matrix(int rows, int cols, std::string name = "");
	Matrix(int rows, int cols, fillType ft, std::string name = "");
	Matrix(int rows, int cols, double** array, std::string name = "");
	Matrix(int rows, int cols, float** array, std::string name);
	Matrix(Matrix const& other);
	Matrix& operator=(Matrix const& rhs);
	~Matrix();

	inline int getRows() const {return rows;}
	inline int getCols() const {return cols;}
	inline double getValue(int row, int col) const {return values[row][col];}
	inline void setValue(int row, int col, double value) {values[row][col] = value;}
	static Matrix rand(int rows, int cols);
	static Matrix eye(int rows, int cols);
	static Matrix zeroes(int rows, int cols);
	static Matrix ones(int rows, int cols);
	Matrix& fill(fillType ft); //in-place
	Matrix& fillValue(double value); //in-place
	Matrix& fillPart(int row, int col, Matrix const& fillMatrix); //in-place

	/* Matrix operations */
	Matrix add(Matrix const& rhs) const;
	Matrix sub(Matrix const& rhs) const;
	Matrix mul(Matrix const& rhs) const;
	Matrix rightDiv(Matrix const& rhs) const;
	Matrix inverse() const;
	Matrix transpose() const;
	Matrix getMinor(int row, int col) const;
	Matrix elemMul(double scalar) const;
	Matrix elemPow(double exponent) const;
	double determinant() const;
	Matrix& swapRows(int row1, int row2); //in-place
	Matrix sin();
	Matrix cos();
	Matrix tan();
	Matrix asin();
	Matrix acos();
	Matrix atan();
	Matrix log();
	Matrix log10();
	Matrix pow(double exponent);
	Matrix sqrt();

	/* Overloaded operators for Matrix operations */
	Matrix operator+(Matrix const& rhs) const;
	Matrix operator-(Matrix const& rhs) const;
	Matrix operator*(Matrix const& rhs) const;
	Matrix operator*(double scalar) const;
	friend Matrix operator*(double lhs_scalar, Matrix const& rhs_matrix);
	Matrix operator/(Matrix const& rhs) const;

	std::string getString() const;
	friend std::ostream& operator<<(std::ostream& out, Matrix const& matrix);
};

#endif //MATRIX_H
