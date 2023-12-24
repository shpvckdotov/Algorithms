#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void longest_matching_subsequences_filling(const std::string& first, const std::string& second,
	std::vector<size_t>& first_string_len, std::vector<size_t>& second_string_len,
	std::vector<std::vector<bool>>& longest_matching_subsequences)
	{
	for (size_t i = 0; i < first.size(); i++) {
		second_string_len.assign(second.size() + 1, 0);
		for (size_t j = 0; j < second.size(); j++) {
			if (first[i] == second[j]) {
				second_string_len[j + 1] = first_string_len[j] + 1;
			}
			else {
				if (second_string_len[j] >= first_string_len[j + 1]) {
					second_string_len[j + 1] = second_string_len[j];
				}
				else {
					second_string_len[j + 1] = first_string_len[j + 1];
					longest_matching_subsequences[i + 1][j + 1] = 1;
				}
			}
		}
		first_string_len = second_string_len;
	}
}

void answer_building(const std::string& first, const std::string& second,
	const std::vector<std::vector<bool>>& longest_matching_subsequences,
	std::vector<size_t>& first_string_indexes, std::vector<size_t>& second_string_indexes) {
	int iteration_on_first_string = first.size() - 1;
	int iteration_on_second_string = second.size() - 1;
	while (iteration_on_first_string >= 0 && iteration_on_second_string >= 0) {
		if (first[iteration_on_first_string] == second[iteration_on_second_string]) {
			first_string_indexes.push_back(iteration_on_first_string + 1);
			second_string_indexes.push_back(iteration_on_second_string + 1);
			i--;
			iteration_on_second_string--;
			continue;
		}
		else {
			if (longest_matching_subsequences[iteration_on_first_string + 1][iteration_on_second_string + 1]) {
				iteration_on_first_string--;
			}
			else {
				iteration_on_second_string--;
			}
		}
	}
}

void answer_printing(std::vector<size_t>& first_string_indexes,std::vector<size_t>& second_string_indexes) {
	std::reverse(first_string_indexes.begin(), first_string_indexes.end());
	std::reverse(second_string_indexes.begin(), second_string_indexes.end());
	std::cout << second_string_indexes.size() << std::endl;
	for (const auto& item : first_string_indexes) {
		std::cout << item << ' ';
	}
	std::cout << std::endl;
	for (const auto& item : second_string_indexes) {
		std::cout << item << ' ';
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::string first, second;
	std::vector<size_t> first_string_len, second_string_len;
	std::vector<size_t> first_string_indexes, second_string_indexes;
	std::cin >> first >> second;
	std::vector<std::vector<bool>> longest_matching_subsequences(first.size() + 1, std::vector<bool>(second.size() + 1, false));
	first_string_len.resize(second.size() + 1);
	longest_matching_subsequences_filling(first, second, first_string_len, second_string_len, longest_matching_subsequences);
	answer_building(first, second, longest_matching_subsequences, first_string_indexes, second_string_indexes);
	answer_printing(first_string_indexes, second_string_indexes);
}