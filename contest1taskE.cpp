#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#define INF 1e9
#define BASE_FOR_PAIR { -1, -1 }

void min_sum(std::vector<std::vector<std::pair<int, int>>>& previous, std::vector<std::vector<int>>& distances,
    std::vector<std::vector<int>> mid_distances, const std::vector<int>& houses, int n, int m){
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int mid = houses[(l + r) >> 1];
            for (int u = l; u <= r; u++) {
                mid_distances[l][r] += abs(houses[u] - mid);
            }
        }
    }
    distances[0][0] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int r = j + 1; r <= n; r++) {
                if (distances[i + 1][r] > distances[i][j] + mid_distances[j + 1][r]) {
                    distances[i + 1][r] = distances[i][j] + mid_distances[j + 1][r];
                    previous[i + 1][r] = { j, r };
                }
            }
        }
    }
}

void answer_building(const std::vector<std::vector<std::pair<int, int>>>& previous, const std::vector<int>& houses, std::vector<int>& influence_points, int n, int m) {
    int influence_points_iteration = m;
    int houses_iteration = n;
    while (i != 0) {
        int left = previous[i][j].first;
        int right = previous[i][j].second;
        int mid = (left + right) / 2;
        if ((left + right) % 2) {
            mid++;
        }
        influence_points.push_back(houses[u]);
        houses_iteration = l;
        influence_points_iteration--;
    }
    reverse(influence_points.begin(), influence_points.end());
}

void houses_initiation(std::vector<int>& houses) {
    for (int i = 0; i < n; i++) {
        int house;
        std::cin >> house;
        houses.push_back(house);
    }
}

void answer_printing(const std::vector<std::vector<int>>& distances, const std::vector<int>& influence_points) {
    std::cout << distances[m][n] << '\n';
    for (auto houses : influence_points) {
        std::cout << houses << ' ';
    }
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> previous(m + 1, std::vector<std::pair<int, int>>(n + 1, BASE_FOR_PAIR));
    std::vector<std::vector<int>> mid_distances(n + 1, std::vector<int>(n + 1));
    std::vector<std::vector<int>> distances(m + 1, std::vector<int>(n + 1, INF));
    std::vector<int> houses(1), influence_points;
    houses_initiation(houeses);
    min_sum(previous, distances, mid_distances, houses, n, m);
    answer_building(previous, houses, influence_points, n, m);
    answer_printing(distances, influence_points);
}