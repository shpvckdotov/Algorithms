#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

#define WHITE_VERTEX "WHITE"
#define BLACK_VERTEX "BLACK"
#define GREY_VERTEX "GREY"
#define NEW_LINE '\n'

long long INF = 1e9;

void first_dfs(const std::vector<std::vector<long long>>& graph, long long s, std::vector<std::string>& color,
	std::vector<long long>& parents, std::vector<long long>& top_sort, long long parent = -1) {
	color[s] = GREY_VERTEX;
	parents[s] = parent;
	for (auto to : graph[s]) {
		if (color[to] != WHITE_VERTEX) {
			continue;
		}
		else {
			first_dfs(graph, to, color, parents, top_sort, s);
		}
	}
	top_sort.push_back(s);
	color[s] = BLACK_VERTEX;
}
void second_dfs(const std::vector<std::vector<long long>>& graph, long long s, std::vector<long long>& colors,
	std::vector<long long>& parents, const long long& counter) {
	colors[s] = counter;
	for (auto to : graph[s]) {
		if (colors[to] != -1) {
			continue;
		}
		else {
			second_dfs(graph, to, colors, parents, counter);
		}
	}
}


void graphs_initiation(std::vector<std::vector<long long>>& graph, std::vector<std::vector<long long>>& graph_reverse) {
	for (long long i = 1; i <= m; i++) {
		long long first, second;
		std::cin >> first >> second;
		graph[first].push_back(second);
		graph_reverse[second].push_back(first);
	}
}

void strong_connectivity_components(const std::vector<std::vector<long long>>& graph, const std::vector<std::vector<long long>>& graph_reverse, std::vector<std::string>& color,
	std::vector<long long>& parents, std::vector<long long>& top_sort, long long counter) {
	for (long long i = 1; i <= n; i++) {
		if (color[i] == WHITE_VERTEX) {
			first_dfs(graph, i, color, parents, top_sort);
		}
	}
	for (long long i = 1; i <= top_sort.size(); i++) {
		long long v = top_sort[n - i];
		if (colors[v] == -1) {
			second_dfs(graph_reverse, v, colors, parents, counter++);
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	long long n, m;
	std::cin >> n >> m;
	std::vector<std::vector<long long>> graph(n + 1), graph_reverse(n + 1);
	std::vector<std::string> color(n + 1, WHITE_VERTEX);
	std::vector<long long> parents(n + 1), top_sort, colors;
	long long counter = 0;
	colors.assign(n + 1, -1);
	graphs_initiation(graph, graph_reverse);
	strong_connectivity_components(graph, graph_reverse, color, parents, top_sort, counter)
	std::cout << counter << '\n';
	for (int i = 1; i < colors.size(); i++) {
		std::cout << colors[i] + 1 << ' ';
	}
}