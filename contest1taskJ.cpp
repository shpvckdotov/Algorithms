#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

void dp_filling(const std::string& first, const std::string& second,
	std::vector<size_t>& first_string_len, std::vector<size_t>& second_string_len,
	std::vector<std::vector<bool>>& dp)
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
					dp[i + 1][j + 1] = 1;
				}
			}
		}
		first_string_len = second_string_len;
	}
}

void answer_building(const std::string& first, const std::string& second,
	const std::vector<std::vector<bool>>& dp,
	std::vector<size_t>& first_string_indexes, std::vector<size_t>& second_string_indexes) {
	int i = first.size() - 1;
	int j = second.size() - 1;
	while (i >= 0 && j >= 0) {
		if (first[i] == second[j]) {
			first_string_indexes.push_back(i + 1);
			second_string_indexes.push_back(j + 1);
			i--;
			j--;
			continue;
		}
		else {
			if (dp[i + 1][j + 1]) {
				i--;
			}
			else {
				j--;
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
	std::vector<std::vector<bool>> dp(first.size() + 1, std::vector<bool>(second.size() + 1, false));
	first_string_len.resize(second.size() + 1);
	dp_filling(first, second, first_string_len, second_string_len, dp);
	answer_building(first, second, dp, first_string_indexes, second_string_indexes);
	answer_printing(first_string_indexes, second_string_indexes);
}