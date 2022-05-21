#pragma once
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <map>
class ELGraph
{
public:
	std::vector<int> ev1;
	std::vector<int> ev2;
	std::map<int, bool> visited;
	void InsertEdge(int v1, int v2)
	{
		ev1.push_back(v1);
		ev2.push_back(v2);
	}
	std::pair<std::vector<int>, std::vector<int>> BFS(int start)
	{
		std::vector<bool> visited(ev1.size(), false);
		std::vector<int> dist, prev;
		dist = std::vector<int>(ev1.size(), 0);
		prev = std::vector<int>(ev1.size(), -1);
		std::queue<int> q;
		q.push(start);
		visited[start] = true;
		while (!q.empty())
		{
			int v = q.front();
			q.pop();
			std::cout << v << " ";
			for (int i = 0; i < ev1.size(); i++)
			{
				if (ev1[i] == v && !visited[ev2[i]])
				{
					dist[ev2[i]] = dist[v] + 1;
					prev[ev2[i]] = v;
					q.push(ev2[i]);
					visited[ev2[i]] = true;
				}
				else if (ev2[i] == v && !visited[ev1[i]])
				{
					dist[ev1[i]] = dist[v] + 1;
					prev[ev1[i]] = v;
					q.push(ev1[i]);
					visited[ev1[i]] = true;
				}
			}
		}
		return std::make_pair(prev, dist);
	}
	void DFS(int start)
	{
		if (visited[start]) return;
		visited[start] = true;
		std::map<int, int> children;
		for (int i = 0; i < ev1.size(); i++)
		{
			if (ev1[i] == start)
			{
				children[ev2[i]] = NULL;
			}
			else if (ev2[i] == start)
			{
				children[ev1[i]] = NULL;
			}
		}
		for (auto& i : children)
		{
			DFS(i.first);
		}
		std::cout << start << " ";
	}
	std::pair<std::vector<int>, int> PathFind(int start, int end)
	{
		auto PathFindData = BFS(start);
		int dist = PathFindData.second[end];
		std::vector<int> path;
		if (dist == 0)
		{
			return { path, dist };
		}
		int current = end;
		path.push_back(current);
		while (current != start)
		{
			current = PathFindData.first[current];
			path.emplace(path.begin(), current);
		}
		return { path, dist };
	}
};
void ELGraphDemo()
{
	ELGraph g;
	g.InsertEdge(1, 2);
	g.InsertEdge(1, 4);
	g.InsertEdge(1, 7);
	g.InsertEdge(2, 3);
	g.InsertEdge(2, 4);
	g.InsertEdge(2, 6);
	g.InsertEdge(3, 4);
	g.InsertEdge(3, 5);
	g.InsertEdge(3, 9);
	g.InsertEdge(3, 10);
	g.InsertEdge(4, 5);
	g.InsertEdge(4, 8);
	g.InsertEdge(7, 8);
	g.BFS(2);
	std::cout << std::endl;

	//auto [Path, Dist] = g.PathFind(7, 9);
	//std::cout << std::endl;
	//for (auto& i : Path)
	//{
	//	std::cout << i << " ";
	//}
	//std::cout << "\ndistance: " << Dist << std::endl;
}