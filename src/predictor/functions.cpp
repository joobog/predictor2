/*
 * =====================================================================================
 *
 *       Filename:  function.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/08/2015 12:16:22 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "functions.hpp"
#include <cassert>

void print_message(FILE* target, const char* str) {
//	fprintf(target, "%s", str);
	printf("%s", str);
}

void print_warning(FILE* target, const char* str) {
//	fprintf(target, "%s", str);
	printf("%s", str);
}

void print_error(FILE* target, const char* str) {
//	fprintf(target, "%s", str);
	printf("%s", str);
}

std::vector<double> convert(const shogun::SGVector<float64_t>& sg_vector) {
	using namespace std;
	using namespace shogun;

	vector<double> v(sg_vector.size());
	
	for (size_t i = 0; i < sg_vector.size(); ++i) {
		v[i] = sg_vector[i];
	}

	return move(v);
}

shogun::SGVector<float64_t> convert(const std::vector<double>& v) {
	using namespace std;
	using namespace shogun;
	
	SGVector<float64_t> sg_vector(v.size());

	for (size_t i = 0; i < v.size(); ++i) {
		sg_vector[i] = v[i];
	}
	return move(sg_vector);
}



std::vector<std::vector<double>> convert(const shogun::SGMatrix<float64_t>& sg_matrix) {
	using namespace std;
	using namespace shogun;

	const index_t cols = sg_matrix.num_cols;
	const index_t rows = sg_matrix.num_rows;;

	vector<vector<double>> matrix;

	for (index_t col = 0; col < cols; ++col) {
		vector<double> v;
	
		for (index_t row = 0; row < rows; ++row) {
			v[row] = sg_matrix.matrix[row * cols + row];
		}
		matrix.push_back(v);
	}

	return move(matrix);
}

shogun::SGMatrix<float64_t> convert(const std::vector<std::vector<double>>& matrix) {
	using namespace std;
	using namespace shogun;
		
	const size_t cols = matrix.size();
	const size_t rows = matrix[0].size();

	SGMatrix<float64_t> sg_matrix(rows, cols);

	for (size_t col = 0; col < cols; ++col) {
		for (size_t row = 0; row < rows; ++row) {
			sg_matrix.matrix[row * cols + row] = matrix[row][col];
		}
	}

	return move(sg_matrix);
}


/**
 * @brief In-place matrix normalization
 *
 * @param matrix
 */
void normalize(shogun::SGMatrix<float64_t>& matrix) {
	using namespace shogun;
	using namespace std;

	const index_t nrows = matrix.num_rows;
	const index_t ncols = matrix.num_cols;

	vector<float64_t> max_values(nrows);

	// find max values
	for (index_t row = 0; row < nrows; ++row){
		SGVector<float64_t> sg_vector = matrix.get_row_vector(row);
		max_values[row]	= CMath::max(sg_vector.vector, sg_vector.vlen);
	}

	// normalize	
	for (index_t col = 0; col < ncols; ++col) {
		for (index_t row = 0; row < nrows; ++row){
			matrix.matrix[col * nrows + row] = matrix.matrix[col * nrows + row] / max_values[row];
		}
	}
}

std::ostream& operator<< (std::ostream& os, const shogun::SGMatrix<float64_t>& matrix) {
	using namespace shogun;
	using namespace std;

	const int32_t nrows = matrix.num_rows;
	const int32_t ncols = matrix.num_cols;

	for (int32_t ncol = 0; ncol < ncols ; ++ncol) {
		for (int32_t nrow = 0; nrow < nrows ;  ++nrow) {
			cout << matrix.matrix[ncol * nrows + nrow] << " ";
		}
		cout << endl;
	}
	return os;
}

std::ostream& operator<< (std::ostream& os, const shogun::SGVector<float64_t>& vector) {
	using namespace shogun;
	using namespace std;

	for (int32_t i = 0; i < vector.size(); i++) {
		cout << vector[i] << " ";
	}
	cout << endl;
	return os;
}
