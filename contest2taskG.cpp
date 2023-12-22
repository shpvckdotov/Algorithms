#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <pair>
#include <optional>

#define MATRIX_SIZE 16
#define DESK_CONST 4
#define ON_DESK_POSITION_MASK 15ull
#define ROTATE_VERTICAL 4
#define ROTATE_HORIZONTAL 1
#define FIRST_HEURISTIC_CONST 800
#define SECOND_HEURISTIC_CONST 895
#define DESK_POSITION_CONST 15
#define SIZE_OF_DESK 16
#define END_CONST 0xfedcba9876543210ull
#define POSITION 15
#define RESERVE_CONST 1000000
#define LEFT 'L'
#define RIGHT 'R'
#define DOWN 'D'
#define UP 'U'
#define UNACHIEVABLE -1


class Vertex {
public:
    enum class Directions {
        Up, Down, Left, Right
    };
    size_t desk_position[16];
    explicit Vertex(size_t vertex) {
        for (int16_t i = 0; i < DESK_CONST; ++i) {
            for (int16_t j = 0; j < DESK_CONST; ++j) {
                desk_position[i * DESK_CONST + j] = vertex & ON_DESK_POSITION_MASK;
                vertex >>= DESK_CONST;
            }
        }
    }

    int16_t FindZero() {
        int16_t x;
        for (int16_t i = 0; i < MATRIX_SIZE; ++i) {
            if (desk_position[i] == DESK_POSITION_CONST) {
                x = i;
                break;
            }
        }
        return x;
    }

    std::optional<Vertex> GoUp() {
        int16_t index = FindZero();
        if (index / DESK_CONST == 3) {
            return std::nullopt;
        }
        Vertex temp = *this;
        std::swap(temp.desk_position[index], temp.desk_position[index + ROTATE_VERTICAL]);
        return { temp };
    }

    std::optional<Vertex> GoDown() {
        int16_t index = FindZero();
        if (index / DESK_CONST == 0) {
            return std::nullopt;
        }
        Vertex temp = *this;
        std::swap(temp.desk_position[index], temp.desk_position[index - ROTATE_VERTICAL]);
        return { temp };
    }

    std::optional<Vertex> GoLeft() {
        int16_t index = FindZero();
        if (index % DESK_CONST == 3) {
            return std::nullopt;
        }
        Vertex temp = *this;
        std::swap(temp.desk_position[index], temp.desk_position[index + ROTATE_HORIZONTAL]);
        return { temp };
    }

    std::optional<Vertex> GoRight() {
        int16_t index = FindZero();
        if (index % DESK_CONST == 0) {
            return std::nullopt;
        }
        Vertex temp = *this;
        std::swap(temp.desk_position[index], temp.desk_position[index - ROTATE_HORIZONTAL]);
        return { temp };
    }


    size_t Heuristic() {
        size_t res = 0;
        for (int16_t i = 0; i < DESK_CONST; ++i) {
            for (int16_t j = 0; j < DESK_CONST; ++j) {
                if (desk_position[i * DESK_CONST + j] == DESK_POSITION_CONST) {
                    continue;
                }
                int16_t usual_x = (desk_position[i * DESK_CONST + j]) / DESK_CONST;
                int16_t usual_y = (desk_position[i * DESK_CONST + j]) % DESK_CONST;
                res += abs(i - usual_x) + abs(j - usual_y);
            }
        }
        for (int16_t line = 0; line < DESK_CONST; ++line) {
            for (int16_t l = 0; l < 3; ++l) {
                for (int16_t r = l + 1; r < DESK_CONST; ++r) {
                    if (desk_position[line * DESK_CONST + l] / 4 == line && desk_position[line * DESK_CONST + r] / DESK_CONST == line &&
                        desk_position[line * DESK_CONST + l] > desk_position[line * DESK_CONST + r] &&
                        ((desk_position[line * DESK_CONST + l] | desk_position[line * DESK_CONST + r]) ^ ON_DESK_POSITION_MASK)) {
                        res += 2;
                    }
                }
            }
        }
        for (int16_t row = 0; row < DESK_CONST; ++row) {
            for (int16_t l = 0; l < 3; ++l) {
                for (int16_t r = l + 1; r < DESK_CONST; ++r) {
                    if (desk_position[l * DESK_CONST + row] % 4 == row && desk_position[r + row % DESK_CONST] % DESK_CONST == row &&
                        desk_position[l * DESK_CONST + row] > desk_position[r * DESK_CONST + row] &&
                        ((desk_position[l * DESK_CONST + row] | desk_position[r * DESK_CONST + row]) ^ ON_DESK_POSITION_MASK)) {
                        res += 2;
                    }
                }
            }
        }
        return (res * SECOND_HEURISTIC_CONST) / FIRST_HEURISTIC_CONST;
    }

    vector<pair<size_t, Directions>> FindNext() {
        std::vector<pair<size_t, Directions>> ans;
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
        for (int16_t i = 0; i < DESK_CONST; ++i) {
            for (int16_t j = 0; j < DESK_CONST; ++j) {
                res |= desk_position[i * DESK_CONST + j] * 1ull << (i * DESK_CONST + j) * DESK_CONST;
            }
        }
        return res;
    }
};

bool Check(vector<size_t>& start) {
    int16_t inv = 0;
    for (int16_t i = 0; i < SIZE_OF_DESK; ++i)
        if (start[i] != POSITION)
            for (int16_t j = 0; j < i; ++j)
                if (start[j] > start[i] && start[j] != POSITION)
                    ++inv;
    for (int16_t i = 0; i < SIZE_OF_DESK; ++i)
        if (start[i] == POSITION)
            inv += 1 + i / DESK_CONST;

    return inv % 2 == 0;
}

void AStar(size_t start, size_t end, unordered_map<size_t, size_t>& function_for_heuristic,
    std::unordered_map<size_t, size_t>& parents) {
    std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, greater<>> binary_heap_for_Astar;
    function_for_heuristic.insert(pair<size_t, size_t>(start, 0));
    binary_heap_for_Astar.push({ Vertex(start).Heuristic(), start });
    while (!binary_heap_for_Astar.empty()) {
        size_t tmp = binary_heap_for_Astar.top().second;
        binary_heap_for_Astar.pop();
        if (tmp == end) {
            return;
        }
        std::vector<pair<size_t, Vertex::Directions>> next_direcitons = Vertex(tmp).FindNext();
        size_t dist = function_for_heuristic[tmp];
        for (auto directions : next_direcitons) {
            size_t next_weight = dist + 1;
            if (function_for_heuristic.find(directions.first) == function_for_heuristic.end() || next_weight < function_for_heuristic[directions.first]) {
                parents[directions.first] = tmp;
                function_for_heuristic[directions.first] = next_weight;
                binary_heap_for_Astar.push({ next_weight + Vertex(directions.first).Heuristic(), directions.first });
            }
        }
    }
}

void PrintAns(size_t start, size_t end,
    std::unordered_map<size_t, size_t>& parents) {
    std::vector<Vertex::Directions> ans;
    size_t tmp = end;
    while (tmp != start) {
        size_t prev = parents[tmp];
        std::vector<pair<size_t, Vertex::Directions>> next_direcitons = Vertex(tmp).FindNext();
        for (auto directions : next_direcitons) {
            if (directions.first == prev) {
                ans.push_back(directions.second);
                break;
            }
        }
        tmp = prev;
    }
    std::cout << ans.size() << '\n';
    std::reverse(ans.begin(), ans.end());
    for (size_t i = 0; i < ans.size(); ++i) {
        if (ans[i] == Vertex::Directions::Up) {
            std::cout << DOWN;
        }
        else if (ans[i] == Vertex::Directions::Down) {
            std::cout << UP;
        }
        else if (ans[i] == Vertex::Directions::Left) {
            std::cout << RIGHT;
        }
        else if (ans[i] == Vertex::Directions::Right) {
            std::cout << LEFT;
        }
    }
}

signed main() {
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
    std::vector<size_t> matrix(MATRIX_SIZE);
    size_t start = 0;
    for (size_t i = 0; i < MATRIX_SIZE; ++i) {
        cin >> matrix[i];
        if (matrix[i] == 0) matrix[i] = POSITION;
        else --matrix[i];
        start |= matrix[i] << i * DESK_CONST;
    }
    if (!Check(matrix)) {
        cout << UNACHIEVABLE;
        return 0;
    }
    size_t end = END_CONST;
    std::unordered_map<size_t, size_t> function_for_heuristic;
    std::unordered_map<size_t, size_t> parents;
    function_for_heuristic.reserve(RESERVE_CONST);
    parents.reserve(RESERVE_CONST);
    AStar(start, end, function_for_heuristic, parents);
    PrintAns(start, end, parents);
    return 0;
}