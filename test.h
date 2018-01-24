#ifndef TEST_H
#define TEST_H

#include "matrix.h"

namespace test{

void print(Matrix const& matrix, char const* label);
void print(double value, char const* label);
void test_matrix();
void test_variable();
}

#endif //TEST_H
