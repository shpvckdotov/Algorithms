#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

size_t timer = 0;
size_t INF = 1e9;

void dfs(const std::vector<std::vector<std::pair<size_t, size_t>>>& graph, std::vector<bool>& used_vertexes, std::vector<size_t>& tree_return_time,
	std::vector<size_t>& vertex_enter_time, std::vector<size_t>& vertex_time_out, std::vector<size_t>& parents, std::set<size_t>& bridges, size_t s, size_t parent = -1) {
	parents[s] = parent;
	vertex_enter_time[s] = timer++;
	tree_return_time[s] = vertex_enter_time[s];
	used_vertexes[s] = true;
	for (auto to : graph[s]) {
		if (to.first == parent) {
			continue;
		}
		if (used_vertexes[to.first]) {
			tree_return_time[s] = std::min(tree_return_time[s], vertex_enter_time[to.first]);
		}
		else {
			dfs(graph, used_vertexes, tree_return_time, vertex_enter_time, vertex_time_out, parents, bridges, to.first, s);
			tree_return_time[s] = std::min(tree_return_time[s], tree_return_time[to.first]);
			if (tree_return_time[to.first] == vertex_enter_time[to.first]) {
				bridges.insert(to.second);
			}
		}
	}
}

void graph_initiation(std::vector<std::vector<std::pair<size_t, size_t>>>& graph) {
	for (size_t i = 1; i <= m; i++) {
		size_t first, second;
		std::cin >> first >> second;
		graph[first].push_back(std::make_pair(second, i));
		graph[second].push_back(std::make_pair(first, i));
	}
}

void answer_building(const std::vector<std::vector<std::pair<size_t, size_t>>>& graph, std::vector<bool>& used_vertexes, std::vector<size_t>& tree_return_time,
	std::vector<size_t>& vertex_enter_time, std::vector<size_t>& vertex_time_out, std::vector<size_t>& parents, std::set<size_t>& bridges, size_t s, size_t parent = -1) {
	for (size_t vertex = 1; vertex <= n; vertex++) {
		if (!used_vertexes[vertex]) {
			dfs(graph, used_vertexes, tree_return_time, vertex_enter_time, vertex_time_out, parents, bridges, i);
		}
	}
}

void answer_printing(const std::set<size_t>& bridges;) {
	std::cout << bridges.size() << '\n';
	for (auto bridge : bridges) {
		std::cout << bridge << ' ';
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	size_t n, m;
	std::cin >> n >> m;
	std::vector<bool> used_vertexes(n + 1, false);
	std::vector<std::vector<std::pair<size_t, size_t>>> graph(n + 1);
	std::vector<size_t> vertex_enter_time(n + 1, 0), vertex_time_out(n + 1, 0), tree_return_time(n + 1, INF), std::vector<size_t> parents(n + 1, 0);
	std::set<size_t> bridges;
	graph_initiation(graph);
	answer_building(graph, used_vertexes, tree_return_time, vertex_enter_time, vertex_time_out, parents, bridges, i);
	answer_printing(bridges);
}