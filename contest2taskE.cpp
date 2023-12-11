#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

#define SPACE ' '
#define NEW_LINE '\n'

size_t timer = 0;
size_t INF = 1e9;

void dfs(const std::vector<std::vector<std::pair<size_t, size_t>>>& graph, std::vector<bool>& used, std::vector<size_t>& ret,
	std::vector<size_t>& tin, std::vector<size_t>& tout, std::vector<size_t>& parents, std::set<size_t>& bridges, size_t s, size_t parent = -1) {
	parents[s] = parent;
	tin[s] = timer++;
	ret[s] = tin[s];
	used[s] = true;
	for (auto to : graph[s]) {
		if (to.first == parent) {
			continue;
		}
		if (used[to.first]) {
			ret[s] = std::min(ret[s], tin[to.first]);
		}
		else {
			dfs(graph, used, ret, tin, tout, parents, bridges, to.first, s);
			ret[s] = std::min(ret[s], ret[to.first]);
			if (ret[to.first] == tin[to.first]) {
				bridges.insert(to.second);
			}
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	size_t n, m;
	std::cin >> n >> m;
	std::vector<bool> used(n + 1, false);
	std::vector<std::vector<std::pair<size_t, size_t>>> graph(n + 1);
	std::vector<size_t> tin(n + 1, 0);
	std::vector<size_t> tout(n + 1, 0);
	std::vector<size_t> ret(n + 1, INF);
	std::vector<size_t> parents(n + 1, 0);
	std::set<size_t> bridges;
	for (size_t i = 1; i <= m; i++) {
		size_t first, second;
		std::cin >> first >> second;
		graph[first].push_back(std::make_pair(second, i));
		graph[second].push_back(std::make_pair(first, i));
	}
	for (size_t i = 1; i <= n; i++) {
		if (!used[i]) {
			dfs(graph, used, ret, tin, tout, parents, bridges, i);
		}
	}
	std::cout << bridges.size() << NEW_LINE;
	for (auto bridge : bridges) {
		std::cout << bridge << SPACE;
	}
}