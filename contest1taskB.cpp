#include <iostream>
#include <vector>

#define _MOD_ 1000003
#define _MATRIX_SIZE_ 5
#define _DEGREE_CONST_ 2
#define _BASE_MATRIX_ { {1,1,1,1,1}, {1,0,0,0,0}, {0,1,0,0,0}, {0,0,1,0,0}, {0,0,0,1,0} }
#define _BASE_VECTOR_ {8,4,2,1,1}

std::vector <std::vector<size_t>> multiply_matrix(std::vector <std::vector<size_t>> left_matrix, std::vector <std::vector<size_t>> right_matrix) {
	std::vector <std::vector<size_t>> matrix(_MATRIX_SIZE_,std::vector<size_t>(_MATRIX_SIZE_,0));
	for (int i = 0; i < _MATRIX_SIZE_; i++) {
		for (int j = 0; j < _MATRIX_SIZE_; j++) {
			for (int t = 0; t < _MATRIX_SIZE_; t++) {
				matrix[i][j] += left_matrix[i][t] % _MOD_ * right_matrix[t][j] % _MOD_;
			}
		}
	}
	return matrix;
}

size_t pow_matrix(size_t degree,const std::vector<size_t>& base_vector) {
	std::vector <std::vector<size_t>> base = _BASE_MATRIX_;
	std::vector <std::vector<size_t>> matrix_mult = _BASE_MATRIX_;
	while (degree) {
		if (degree % _DEGREE_CONST_ == 0) {
			degree /= _DEGREE_CONST_;
			base = multiply_matrix(base, base);
		}
		else {
			degree--;
			matrix_mult = multiply_matrix(matrix_mult, base);
		}
	}
	size_t ways_count = 0;
	size_t matrix_iteration = 0;
	while (matrix_iteration < _MATRIX_SIZE_) {
		ways_count += (matrix_mult[1][matrix_iteration] * base_vector[matrix_iteration]) % _MOD_;
		matrix_iteration++;
	}
	return ways_count;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	size_t n, position;
	std::vector<size_t> base_vector = _BASE_VECTOR_;
	std::cin >> n;
	if (n < _MATRIX_SIZE_) {
		std::cout << base_vector[_MATRIX_SIZE_ - n];
		return 0;
	}
	std::cout << pow_matrix(n - _MATRIX_SIZE_, base_vector) % _MOD_;
}