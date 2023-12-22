#include <bits/stdc++.h>
#include <optional>

using namespace std;

#define int int16_t

const int kSize = 16;

class Vertex {
public:
    enum class Directions {
        Up, Down, Left, Right
    };
    size_t matr[16];
    explicit Vertex(size_t a) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                matr[i * 4 + j] = a & 15ull;
                a >>= 4;
            }
        }
    }

    int FindZero() {
        int x;
        for (int i = 0; i < kSize; ++i) {
            if (matr[i] == 15) {
                x = i;
                break;
            }
        }
        return x;
    }

    std::optional<Vertex> GoUp() {
        int index = FindZero();
        if (index / 4 == 3) {
            return std::nullopt;
        }
        Vertex temp = *this;
        swap(temp.matr[index], temp.matr[index + 4]);
        return { temp };
    }

    std::optional<Vertex> GoDown() {
        int index = FindZero();
        if (index / 4 == 0) {
            return std::nullopt;
        }
        Vertex temp = *this;
        swap(temp.matr[index], temp.matr[index - 4]);
        return { temp };
    }

    std::optional<Vertex> GoLeft() {
        int index = FindZero();
        if (index % 4 == 3) {
            return std::nullopt;
        }
        Vertex temp = *this;
        swap(temp.matr[index], temp.matr[index + 1]);
        return { temp };
    }

    std::optional<Vertex> GoRight() {
        int index = FindZero();
        if (index % 4 == 0) {
            return std::nullopt;
        }
        Vertex temp = *this;
        swap(temp.matr[index], temp.matr[index - 1]);
        return { temp };
    }


    size_t Heuristic() {
        size_t res = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (matr[i * 4 + j] == 15) {
                    continue;
                }
                int usual_x = (matr[i * 4 + j]) / 4;
                int usual_y = (matr[i * 4 + j]) % 4;
                res += abs(i - usual_x) + abs(j - usual_y);
            }
        }
        for (int line = 0; line < 4; ++line) {
            for (int l = 0; l < 3; ++l) {
                for (int r = l + 1; r < 4; ++r) {
                    if (matr[line * 4 + l] / 4 == line && matr[line * 4 + r] / 4 == line &&
                        matr[line * 4 + l] > matr[line * 4 + r] &&
                        ((matr[line * 4 + l] | matr[line * 4 + r]) ^ 15)) {
                        res += 2;
                    }
                }
            }
        }
        for (int row = 0; row < 4; ++row) {
            for (int l = 0; l < 3; ++l) {
                for (int r = l + 1; r < 4; ++r) {
                    if (matr[l * 4 + row] % 4 == row && matr[r + row % 4] % 4 == row &&
                        matr[l * 4 + row] > matr[r * 4 + row] &&
                        ((matr[l * 4 + row] | matr[r * 4 + row]) ^ 15)) {
                        res += 2;
                    }
                }
            }
        }
        return (res * 895) / 800;
    }

    vector<pair<size_t, Directions>> FindNext() {
        vector<pair<size_t, Directions>> ans;
        std::optional<Vertex> up_ans = GoUp();
        if (up_ans != nullopt) {
            ans.push_back(make_pair(up_ans.value().to_int(), Directions::Up));
        }

        std::optional<Vertex> down_ans = GoDown();
        if (down_ans != nullopt) {
            ans.push_back(make_pair(down_ans.value().to_int(), Directions::Down));
        }

        std::optional<Vertex> left_ans = GoLeft();
        if (left_ans != nullopt) {
            ans.push_back(make_pair(left_ans.value().to_int(), Directions::Left));
        }

        std::optional<Vertex> right_ans = GoRight();
        if (right_ans != nullopt) {
            ans.push_back(make_pair(right_ans.value().to_int(), Directions::Right));
        }

        return ans;
    }

    size_t to_int() {
        size_t res = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                res |= matr[i * 4 + j] * 1ull << (i * 4 + j) * 4;
            }
        }
        return res;
    }
};

bool Check(vector<size_t>& start) {
    int inv = 0;
    for (int i = 0; i < 16; ++i)
        if (start[i] != 15)
            for (int j = 0; j < i; ++j)
                if (start[j] > start[i] && start[j] != 15)
                    ++inv;
    for (int i = 0; i < 16; ++i)
        if (start[i] == 15)
            inv += 1 + i / 4;

    return inv % 2 == 0;
}

void AStar(size_t start, size_t end, unordered_map<size_t, size_t>& g,
    unordered_map<size_t, size_t>& parents) {
    priority_queue<pair<size_t, size_t>, std::vector<pair<size_t, size_t>>, greater<>> q;
    g.insert(pair<size_t, size_t>(start, 0));
    q.push({ Vertex(start).Heuristic(), start });
    while (!q.empty()) {
        size_t tmp = q.top().second;
        q.pop();
        if (tmp == end) {
            return;
        }
        vector<pair<size_t, Vertex::Directions>> next_direcitons = Vertex(tmp).FindNext();
        size_t dist = g[tmp];
        for (auto v : next_direcitons) {
            size_t next_weight = dist + 1;
            if (g.find(v.first) == g.end() || next_weight < g[v.first]) {
                parents[v.first] = tmp;
                g[v.first] = next_weight;
                q.push({ next_weight + Vertex(v.first).Heuristic(), v.first });
            }
        }
    }
}

void PrintAns(size_t start, size_t end,
    unordered_map<size_t, size_t>& parents) {
    vector<Vertex::Directions> ans;
    size_t tmp = end;
    while (tmp != start) {
        size_t prev = parents[tmp];
        vector<pair<size_t, Vertex::Directions>> next_direcitons = Vertex(tmp).FindNext();
        for (auto v : next_direcitons) {
            if (v.first == prev) {
                ans.push_back(v.second);
                break;
            }
        }
        tmp = prev;
    }
    cout << ans.size() << '\n';
    std::reverse(ans.begin(), ans.end());
    for (size_t i = 0; i < ans.size(); ++i) {
        if (ans[i] == Vertex::Directions::Up) {
            cout << 'D';
        }
        else if (ans[i] == Vertex::Directions::Down) {
            cout << 'U';
        }
        else if (ans[i] == Vertex::Directions::Left) {
            cout << 'R';
        }
        else if (ans[i] == Vertex::Directions::Right) {
            cout << 'L';
        }
    }
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    vector<size_t> matrix(kSize);
    size_t start = 0;
    for (size_t i = 0; i < kSize; ++i) {
        cin >> matrix[i];
        if (matrix[i] == 0) matrix[i] = 15;
        else --matrix[i];
        start |= matrix[i] << i * 4;
    }
    if (!Check(matrix)) {
        cout << -1;
        return 0;
    }
    size_t end = 0xfedcba9876543210ull;
    unordered_map<size_t, size_t> g;
    unordered_map<size_t, size_t> parents;
    g.reserve(1000000);
    parents.reserve(1000000);
    AStar(start, end, g, parents);
    PrintAns(start, end, parents);
    return 0;
}