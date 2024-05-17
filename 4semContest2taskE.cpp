#include <complex>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <math.h>

#define ROUND_CONST 0.5

const double PI = acos(-1);

void fast_fourier_transform(std::vector<std::complex<double>>& first_polynomial, bool invert_polynomial) {
	int first_polynomial_size = (int)first_polynomial.size();
	if (first_polynomial_size == 1) {
		return;
	}
	std::vector<std::complex<double>> polynomial_even(first_polynomial_size / 2), polynomial_odd(first_polynomial_size / 2);
	for (int i = 0, j = 0; i < first_polynomial_size; i += 2, j++) {
		polynomial_even[j] = first_polynomial[i];
		polynomial_odd[j] = first_polynomial[i + 1];
	}
	fast_fourier_transform(polynomial_even, invert_polynomial);
	fast_fourier_transform(polynomial_odd, invert_polynomial);
	double ang = 2 * PI / first_polynomial_size * (invert_polynomial ? -1 : 1);
	std::complex<double> point(1), point_degreed(cos(ang), sin(ang));
	for (int i = 0; i < first_polynomial_size / 2; i++) {
		first_polynomial[i] = polynomial_even[i] + point * polynomial_odd[i];
		first_polynomial[i + first_polynomial_size / 2] = polynomial_even[i] - point * polynomial_odd[i];
		if (invert_polynomial) {
			first_polynomial[i] /= 2, first_polynomial[i + first_polynomial_size / 2] /= 2;
		}
		point *= point_degreed;
	}
}

void multipy_two_polynomials(const std::vector<int>& first_polynomial, const std::vector<int>& second_polynomial, std::vector<int>& res) {
	std::vector<std::complex<double>> fourier_transformed_first_polynomial(first_polynomial.begin(), first_polynomial.end()), fourier_transformed_second_polynomial(second_polynomial.begin(), second_polynomial.end());
	size_t first_polynomial_size = 1;
	while (first_polynomial_size < std::max(first_polynomial.size(), second_polynomial.size())) {
		first_polynomial_size <<= 1;
	}
	first_polynomial_size <<= 1;
	fourier_transformed_first_polynomial.resize(first_polynomial_size), fourier_transformed_second_polynomial.resize(first_polynomial_size);
	fast_fourier_transform(fourier_transformed_first_polynomial, false), fast_fourier_transform(fourier_transformed_second_polynomial, false);
	for (size_t i = 0; i < first_polynomial_size; i++) {
		fourier_transformed_first_polynomial[i] *= fourier_transformed_second_polynomial[i];
	}
	fast_fourier_transform(fourier_transformed_first_polynomial, true);
	res.resize(first_polynomial_size);
	for (size_t i = 0; i < first_polynomial_size; i++) {
		auto real_part = real(fourier_transformed_first_polynomial[i]);
		if (real_part >= 0) {
			res[i] = int(real_part + ROUND_CONST);
		}
		else {
			res[i] = int(real_part - ROUND_CONST);
		}
	}
}

void enter_polynomial(std::vector<int>& first_polynomial, int polynomial_size) {
	for (int i = 0; i < polynomial_size + 1; i++) {
		std::cin >> first_polynomial[i];
	}
}

void generalize_polynomials(std::vector<int>& first_polynomial, std::vector<int>& second_polynomial,
							int first_polynomial_size, int second_polynomial_size) {
	if (first_polynomial_size > second_polynomial_size) {
		second_polynomial.resize(first_polynomial_size + 1);
	}
	else {
		first_polynomial.resize(second_polynomial_size + 1);
	}
}


void print_answer(size_t first_polynomial_size, size_t second_polynomial_size, const std::vector<int>& multiply_result) {
	std::cout << second_polynomial_size + first_polynomial_size << ' ';
	for (int i = 0; i < second_polynomial_size + first_polynomial_size + 1; i++) {
		std::cout << multiply_result[i] << ' ';
	}
}

int main() {
	size_t first_polynomial_size, second_polynomial_size;
	std::cin >> first_polynomial_size;
	std::vector<int> first_polynomial(first_polynomial_size + 1);
	enter_polynomial(first_polynomial, first_polynomial_size);
	std::cin >> second_polynomial_size;
	std::vector<int> second_polynomial(second_polynomial_size + 1);
	enter_polynomial(second_polynomial, second_polynomial_size);
	generalize_polynomials(first_polynomial, second_polynomial, first_polynomial_size, second_polynomial_size);
	std::vector<int> multiply_result;
	multipy_two_polynomials(first_polynomial, second_polynomial, multiply_result);
	print_answer( first_polynomial_size, second_polynomial_size, multiply_result);
}