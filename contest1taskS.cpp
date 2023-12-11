#include <iostream>
#include <vector>

bool bit(size_t i, size_t mask) {
    return ((1 << i) & mask) != 0;
}

bool compare_masks(size_t mask1, size_t mask2, size_t m) {
    for (size_t i = 1; i < m; ++i) {
        if (bit(i, mask1) && bit(i, mask2) && bit(i - 1, mask1) && bit(i - 1, mask2)) {
            return false;
        }
        if (!bit(i, mask1) && !bit(i, mask2) && !bit(i - 1, mask1) && !bit(i - 1, mask2)) {
            return false;
        }
    }
    return true;
}

size_t generate_ans(std::vector<std::vector<size_t>>& cnt_profiles, size_t length, size_t num_of_masks) {
    size_t ans = 0;
    for (size_t i = 0; i < num_of_masks; i++) {
        ans += cnt_profiles[length - 1][i];
    }
    return ans;
}

void bool_table_generator(std::vector<std::vector<bool>>& bool_table, size_t num_of_masks, size_t width) {
    for (size_t i = 0; i < num_of_masks; i++) {
        for (size_t j = 0; j < num_of_masks; j++) {
            bool_table[i][j] = compare_masks(i, j, width);
        }
    }
}

void count_profiles(const std::vector<std::vector<bool>>& bool_table, std::vector<std::vector<size_t>>& cnt_profiles, size_t length, size_t num_of_masks) {
    for (size_t i = 1; i < length; i++) {
        for (size_t mask1 = 0; mask1 < num_of_masks; mask1++) {
            for (size_t mask2 = 0; mask2 < num_of_masks; mask2++) {
                cnt_profiles[i][mask1] += cnt_profiles[i - 1][mask2] * (size_t)(bool_table[mask1][mask2]);
            }
        }
    }
}

int main() {
    size_t length;
    size_t width;
    size_t mod;
    std::cin >> length >> width >> mod;
    if (length < width) {
        std::swap(length, width);
    }
    size_t num_of_masks = (1 << width);
    std::vector<std::vector<bool>> bool_table(num_of_masks, std::vector<bool>(num_of_masks));
    bool_table_generator(bool_table, num_of_masks, width);
    std::vector<std::vector<size_t>> cnt_profiles(length, std::vector<size_t>(num_of_masks));
    for (size_t i = 0; i < num_of_masks; ++i) {
        cnt_profiles[0][i] = 1;
    }
    count_profiles(bool_table, cnt_profiles, length, num_of_masks);
    std::cout << generate_ans(cnt_profiles, length, num_of_masks) % mod ;
}