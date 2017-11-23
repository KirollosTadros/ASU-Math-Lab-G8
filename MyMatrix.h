#pragma once

class MyMatrix{

	int rows;
	float **Matrix;

  public:
  int cols;
	MyMatrix();
	MyMatrix(int rows, int cols);
	MyMatrix(float **Matrix, int rows, int cols);
	~MyMatrix();

	// void make(float **Mat, int x, int y);
	void empty();

	float **getMatrix();

	int getCols();
	int getRows();

	MyMatrix operator+(MyMatrix &b);
	MyMatrix operator-(MyMatrix &b);
	MyMatrix operator*(MyMatrix &b);
	MyMatrix operator--();

	MyMatrix(const MyMatrix &other);
	MyMatrix operator=(const MyMatrix &other);
	MyMatrix get_minor_matrix(int row, int col);
	MyMatrix elemMul(float elem);
	MyMatrix elemDiv(float elem);
	MyMatrix inverse();
	float det();
	MyMatrix right_divide(MyMatrix &rhs);
	MyMatrix operator/(MyMatrix &rhs);
	void print();
};


