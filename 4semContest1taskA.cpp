#include <iostream>
#include <vector>
#include <string>

#define SEPARATOR "#"
#define OFFSET 2

void prefix_function(const std::string& pi_string, std::vector<size_t>& pi) {
	size_t pi_string_size = pi_string.size();
	for (size_t prefix_position = 1; prefix_position < pi_string_size; prefix_position++) {
		size_t pref_suff_matches = pi[prefix_position - 1];
		while (pref_suff_matches > 0 && pi_string[prefix_position] != pi_string[pref_suff_matches]){
			pref_suff_matches = pi[pref_suff_matches - 1];
		}
		if (pi_string[prefix_position] == pi_string[pref_suff_matches]) {
			pref_suff_matches++;
		}
		pi[prefix_position] = pref_suff_matches;
	}
}

void answer_counting(const std::string& string, const std::string& pattern) {
	std::string pi_string = pattern + SEPARATOR + string;
	size_t pi_string_size = pi_string.size();
	size_t pattern_size = pattern.size();
	std::vector<size_t> pi(pi_string_size);
	prefix_function(pi_string, pi);
	for (int position = pattern_size; position < pi_string_size; position++) {
		if (pi[position] == pattern_size) {
			std::cout << position - OFFSET * pattern_size << '\n';
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::string string, pattern;
	std::cin >> string >> pattern;
	answer_counting(string, pattern);
}