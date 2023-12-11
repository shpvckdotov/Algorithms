#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

#define INF 1e9
#define BASE_FOR_PAIR { -1, -1 }

void min_sum(std::vector<std::vector<std::pair<int, int>>>& pred, std::vector<std::vector<int>>& dp,
    std::vector<std::vector<int>> mid_distances, const std::vector<int>& houses, int n, int m){
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int mid = houses[(l + r) >> 1];
            for (int u = l; u <= r; u++) {
                mid_distances[l][r] += abs(houses[u] - mid);
            }
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= n; j++) {
            for (int r = j + 1; r <= n; r++) {
                if (dp[i + 1][r] > dp[i][j] + mid_distances[j + 1][r]) {
                    dp[i + 1][r] = dp[i][j] + mid_distances[j + 1][r];
                    pred[i + 1][r] = { j, r };
                }
            }
        }
    }
}

void answer_building(const std::vector<std::vector<std::pair<int, int>>>& pred,const std::vector<int>& houses, std::vector<int>& ans, int n, int m) {
    int i = m;
    int j = n;
    while (i != 0) {
        int l = pred[i][j].first;
        int r = pred[i][j].second;
        int u = (l + r) / 2;
        if ((l + r) % 2) {
            u++;
        }
        ans.push_back(houses[u]);
        j = l;
        i--;
    }
    reverse(ans.begin(), ans.end());
}

int main(){
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> pred(m + 1, std::vector<std::pair<int, int>>(n + 1, BASE_FOR_PAIR));
    std::vector<std::vector<int>> mid_distances(n + 1, std::vector<int>(n + 1));
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, INF));
    std::vector<int> houses(1);
    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        houses.push_back(x);
    }
    min_sum(pred, dp, mid_distances, houses, n, m);
    std::cout << dp[m][n] << '\n';
    answer_building(pred,houses,ans,n,m);
    for (auto houses : ans) {
        std::cout << houses << ' ';
    }
}