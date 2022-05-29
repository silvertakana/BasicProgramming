#include <iostream>
#include <vector>
#include <map>

template<class T>
class Graph
{
public:
	std::map<T, std::map<T, float>> nodes;
	void AddEdge(T a, T b, float w)
	{
		nodes[a][b] = w;
		nodes[b][a] = w;
	}
	size_t countEdge()
	{
		size_t count = 0;
		for (auto& node : nodes)
		{
			count += node.second.size();
		}
		return count / 2;
	}
	std::pair<T, T> minEdge()
	{
		float min = std::numeric_limits<float>::max();
		T a, b;
		for (auto& node : nodes)
		{
			for (auto& edge : node.second)
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
	bool haveCycle(T start, T prev, std::vector<T> visited)
	{
		visited.push_back(start);
		for (auto& edge : nodes[start])
		{
			if (edge.first == prev)
			{
				continue;
			}
			if (std::find(visited.begin(), visited.end(), edge.first) != visited.end())
			{
				return true;
			}
			if (haveCycle(edge.first, start, visited))
			{
				return true;
			}
		}
		return false;
	}
	Graph Kruskal()
	{
		Graph copy = *this;
		Graph frame;
		size_t nodesSize = nodes.size();
		while (frame.countEdge() < nodesSize - 1 and copy.countEdge() > 0)
		{
			auto edge = copy.minEdge();
			copy.removeEdge(edge.first, edge.second);
			frame.AddEdge(edge.first, edge.second, 1);
			if(frame.haveCycle(edge.first, edge.first, std::vector<T>()))
			{
				frame.removeEdge(edge.first, edge.second);
			}
		}
		if( frame.countEdge() < nodesSize - 1) throw std::runtime_error("Graph not connected");
		return frame;
	}
};

int main()
{
	Graph<char> g;
	g.AddEdge('a', 'b', 2.f);
	g.AddEdge('a', 'c', 7.f);
	g.AddEdge('a', 'd', 2.f);
	g.AddEdge('b', 'c', 4.f);
	g.AddEdge('b', 'd', 5.f);
	g.AddEdge('b', 'e', 3.f);
	g.AddEdge('e', 'c', 1.f);
	g.AddEdge('e', 'd', 4.f);
	g.AddEdge('e', 'f', 4.f);
	g.AddEdge('f', 'c', 1.f);
	g.AddEdge('f', 'g', 7.f);
	g.AddEdge('c', 'g', 5.f);

	auto frame = g.Kruskal();
}