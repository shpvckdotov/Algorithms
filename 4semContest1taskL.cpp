#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

void manacher_odd(std::vector<long long>& count_of_palindroms_odd, const std::string& string) {
    size_t string_size = string.size();
    long long left = 0, right = -1;
    for (long long iteration_on_string = 0; iteration_on_string < string_size; iteration_on_string++) {
        long long palindroms_count = iteration_on_string > right ? 1 : std::min(count_of_palindroms_odd[left + right - iteration_on_string],
                                                                                                        right - iteration_on_string + 1);
        while (iteration_on_string + palindroms_count < string_size && iteration_on_string - palindroms_count >= 0 
                && string[iteration_on_string + palindroms_count] == string[iteration_on_string - palindroms_count]) {
            palindroms_count++;
        }
        count_of_palindroms_odd[iteration_on_string] = palindroms_count;
        if (iteration_on_string + palindroms_count - 1 > right) {
            left = iteration_on_string - palindroms_count + 1;
            right = iteration_on_string + palindroms_count - 1;
        }
    }
}

void manacher_even(std::vector<long long>& count_of_palindroms_even, const std::string& string) {
    auto string_size = string.size();
    long long left = 0, right = -1;
    for (long long iteration_on_string = 0; iteration_on_string < string_size; iteration_on_string++) {
        long long palindroms_count = iteration_on_string > right ? 0 : std::min(count_of_palindroms_even[left + right - iteration_on_string + 1],
            right - iteration_on_string + 1);
        while (iteration_on_string + palindroms_count < string_size && iteration_on_string - palindroms_count - 1 >= 0
            && string[iteration_on_string + palindroms_count] == string[iteration_on_string - palindroms_count - 1]) {
            palindroms_count++;
        }
        count_of_palindroms_even[iteration_on_string] = palindroms_count;
        if (iteration_on_string + palindroms_count - 1 > right) {
            left = iteration_on_string - palindroms_count;
            right = iteration_on_string + palindroms_count - 1;
        }
    }
}

long long palindroms_count(const std::string& string, std::vector<long long>& count_of_palindroms_odd,
    std::vector<long long>& count_of_palindroms_even) {
    long long palindroms_count = 0;
    size_t string_size = string.size();
    manacher_even(count_of_palindroms_even, string);
    manacher_odd(count_of_palindroms_odd, string);
    for (auto count_on_symbol : count_of_palindroms_even) {
        palindroms_count += count_on_symbol;
    }
    for (auto count_on_symbol : count_of_palindroms_odd) {
        palindroms_count += count_on_symbol;
    }
    return palindroms_count;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
    std::string string;
    std::cin >> string;
    std::vector<long long> count_of_palindroms_odd(string.size(), 1);
    std::vector<long long> count_of_palindroms_even(string.size(), 0);
    std::cout << palindroms_count(string, count_of_palindroms_odd, count_of_palindroms_even) - string.size();
    return 0;
}