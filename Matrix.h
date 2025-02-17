#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix {
public:
	int rows, cols;
	std::vector<std::vector<int>> data;

	Matrix(int r, int c) : rows(r), cols(c) {
		data.resize(rows, std::vector<int>(cols, 0));
	}
};

Matrix mulMatrix(Matrix m1, Matrix m2);

#endif