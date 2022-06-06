#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <format>

template <class T>
class Graph
{
public:
	std::map<T, std::map<T, float>> nodes;
	void AddEdge(T a, T b, float w)
	{
		nodes[b];
		// nodes[b][a] = w;
		nodes[a][b] = w;
	}
	size_t countEdge()
	{
		size_t count = 0;
		for (auto &node : nodes)
		{
			count += node.second.size();
		}
		return count / 2;
	}
	std::pair<T, T> minEdge()
	{
		float min = std::numeric_limits<float>::max();
		T a, b;
		for (auto &node : nodes)
		{
			for (auto &edge : node.second)
			{
				if (edge.second < min)
				{
					min = edge.second;
					a = node.first;
					b = edge.first;
				}
			}
		}
		return std::make_pair(a, b);
	}
	void removeEdge(T a, T b)
	{
		nodes[a].erase(b);
		nodes[b].erase(a);
	}
	std::pair<std::map<T, float>, std::map<T, T>> Dijkstra(T start)
	{
		removeUnreachable();
		std::map<T, float> dist;
		std::map<T, T> prev;
		std::vector<T> checked;
		checked.reserve(nodes.size());
		for (auto &node : nodes)
		{
			dist[node.first] = std::numeric_limits<float>::max();
			prev[node.first] = node.first;
		}
		dist[start] = 0;
		while (checked.size() != nodes.size())
		{
			// find a node with min distance from starting node
			T min = dist.begin()->first;
			for (auto &node : dist)
			{
				if (checked.end() == std::find(checked.begin(), checked.end(), node.first))
				{
					if (dist[node.first] < dist[min] || checked.end() != std::find(checked.begin(), checked.end(), min))
					{
						min = node.first;
					}
				}
			}

			checked.push_back(min);

			for (auto &edge : nodes[min])
			{
				if (dist[edge.first] > dist[min] + edge.second)
				{
					dist[edge.first] = dist[min] + edge.second;
					prev[edge.first] = min;
					// if (!nodes.contains(edge.first)) dist[edge.first] == INFINITY;
				}
			}
		}
		return std::make_pair(dist, prev);
	}
	static void printPath(std::pair<std::map<T, float>, std::map<T, T>> directionMap, T end)
	{
		auto &[dist, prev] = directionMap;
		// extract path
		std::vector<T> path;
		T cur = end;
		if (!dist.contains(cur))
		{
			std::cout << "No path found";
			return;
		}
		while (dist[cur] != 0.f)
		{
			path.push_back(cur);
			cur = prev[cur];
			if (cur != '\0')
				cur = prev[cur];
			else
				return;
		}
		path.push_back(cur);
		std::reverse(path.begin(), path.end());
		// print path
		for (auto &i : path)
		{
			std::cout << i << " ";
		}
	}
	void removeUnreachable()
	{
		std::set<T> pointedTo;
		for (auto &i : nodes)
		{
			for (auto &j : i.second)
			{
				pointedTo.insert(j.first);
			}
		}
		auto copy = nodes;
		for (auto &i : nodes)
		{
			if (!pointedTo.contains(i.first))
			{
				copy.erase(i.first);
			}
		}
		nodes = copy;
	}
	void pathFind(T start, T end)
	{
		removeUnreachable();
		std::map<T, float> dist;
		std::map<T, T> prev;
		std::vector<T> checked;
		checked.reserve(nodes.size());
		for (auto &node : nodes)
		{
			dist[node.first] = INFINITY;
			prev[node.first] = node.first;
		}
		dist[start] = 0;
		while (true)
		{
			// find a node with min distance from starting node
			T min = dist.begin()->first;
			for (auto &node : dist)
			{
				if (checked.end() == std::find(checked.begin(), checked.end(), node.first))
				{
					if (dist[node.first] < dist[min] || checked.end() != std::find(checked.begin(), checked.end(), min))
					{
						min = node.first;
					}
				}
			}

			checked.push_back(min);

			for (auto &edge : nodes[min])
			{
				if (dist[edge.first] > dist[min] + edge.second)
				{
					dist[edge.first] = dist[min] + edge.second;
					prev[edge.first] = min;
					// if (!nodes.contains(edge.first)) dist[edge.first] == INFINITY;
				}
			}
			if (min == end)
			{
				break;
			}
		}
		// ------PRINT PATH------
		printPath(std::make_pair(dist, prev), end);
	}
	void pathFindAll()
	{
		for (auto &j : nodes)
		{
			char start = j.first;
			auto [dist, prev] = Dijkstra(start);
			for (auto &i : nodes)
			{
				char end = i.first;
				std::cout << std::format("\n{0} - {1} : {2} = ", start, end, dist.contains(end) ? dist[end] : -1);
				printPath(std::make_pair(dist, prev), end);
			}
			std::cout << std::endl;
		}
	}
};

int main()
{
	Graph<char> g;
	// g.AddEdge('a', 'b', 2.f);
	// g.AddEdge('a', 'c', 7.f);
	// g.AddEdge('a', 'd', 2.f);
	// g.AddEdge('b', 'c', 4.f);
	// g.AddEdge('b', 'd', 5.f);
	// g.AddEdge('b', 'e', 3.f);
	// g.AddEdge('e', 'c', 1.f);
	// g.AddEdge('e', 'd', 4.f);
	// g.AddEdge('e', 'f', 4.f);
	// g.AddEdge('f', 'c', 1.f);
	// g.AddEdge('f', 'g', 7.f);
	// g.AddEdge('c', 'g', 5.f);

	g.AddEdge('a', 'c', 1.f);
	g.AddEdge('b', 'a', 3.f);
	g.AddEdge('b', 'c', 5.f);
	g.AddEdge('c', 'd', 2.f);
	g.AddEdge('c', 'e', 4.f);
	g.AddEdge('d', 'a', 5.f);

	// std::cout << "path from b to g: ";
	// g.pathFind('b', 'f');

	// std::cout << "\npath for all nodes:\n";

	// g.pathFindAll();

	char start = 'c';
	auto copy = g;
	auto [dist, prev] = copy.Dijkstra(start);
	for (auto &i : g.nodes)
	{
		char end = i.first;
		std::cout << std::format("\n{0} - {1} : {2} = ", start, end, dist.contains(end) ? dist[end] : INFINITY);
		Graph<char>::printPath(std::make_pair(dist, prev), end);
	}
	std::cout << std::endl;
}