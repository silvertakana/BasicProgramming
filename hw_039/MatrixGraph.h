#pragma once
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <map>
class MatrixGraph
{
public:
	std::vector<std::vector<bool>> matrix;
	std::map<int, bool> visited;
	MatrixGraph(int count)
	{
		matrix.resize(count);
		for (int i = 0; i < count; i++)
		{
			matrix[i].resize(count);
			for (int j = 0; j < count; j++)
			{
				matrix[i][j] = false;
			}
		}
	}
	void AddEdge(int from, int to)
	{
		matrix[from - 1][to - 1] = true;
		matrix[to - 1][from - 1] = true;
	}
	void RemoveEdge(int from, int to)
	{
		matrix[from - 1][to - 1] = false;
		matrix[to - 1][from - 1] = false;
	}
	void AddOneWayEdge(int from, int to)
	{
		matrix[from - 1][to - 1] = true;
	}
	void RemoveOneWayEdge(int from, int to)
	{
		matrix[from - 1][to - 1] = false;
	}
	std::pair<std::vector<int>, std::vector<int>> BFS(int start)
	{
		std::vector<int> dist, prev;
		dist = std::vector<int>(matrix.size(), -1);
		prev = std::vector<int>(matrix.size(), -1);
		dist[start - 1] = 0;
		std::vector<bool> visited(matrix.size(), false);
		std::queue<int> q;
		q.push(start - 1);
		do
		{
			int current = q.front();
			q.pop();
			std::cout << current+1 << " ";
			visited[current] = true;
			for (int i = 0; i < matrix.size(); i++)
			{
				if (matrix[current][i] && !visited[i] && std::find(q._Get_container().begin(), q._Get_container().end(), i) == q._Get_container().end())
				{
					dist[i] = dist[current] + 1;
					prev[i] = current;
					q.push(i);
				}
			}
		}
		while (!q.empty());
		return { prev, dist };
	}
	std::pair<std::vector<int>, int> PathFind(int start, int end)
	{
		auto PathFindData = BFS(start);
		int dist = PathFindData.second[end - 1];
		std::vector<int> path;
		if (dist == -1)
		{
			return { path, dist };
		}
		int current = end - 1;
		path.push_back(current + 1);
		while (current != start - 1)
		{
			current = PathFindData.first[current];
			path.emplace(path.begin(), current + 1);
		}
		return { path, dist };
	}
	void DFS(int start)
	{
		if (visited[start]) return;
		visited[start] = true;
		for (size_t i = 1; i <= matrix.size(); i++)
		{
			if (matrix[start-1][i-1]) DFS(i);
		}
		std::cout << start << " ";
	}
};

void MatrixGraphDemo()
{
	MatrixGraph myGraph(10);
	myGraph.AddEdge(1, 2);
	myGraph.AddEdge(1, 4);
	myGraph.AddEdge(1, 7);
	myGraph.AddEdge(2, 3);
	myGraph.AddEdge(2, 4);
	myGraph.AddEdge(2, 6);
	myGraph.AddEdge(3, 4);
	myGraph.AddEdge(3, 5);
	myGraph.AddEdge(3, 9);
	myGraph.AddEdge(3,10);
	myGraph.AddEdge(4, 5);
	myGraph.AddEdge(4, 8);
	myGraph.AddEdge(7, 8);
	myGraph.DFS(2);
	std::cout << std::endl;

	//auto [Path, Dist] = myGraph.PathFind(7, 9);
	//std::cout << std::endl;
	//for (auto& i : Path)
	//{
	//	std::cout << i << " ";
	//}
	//std::cout << "\ndistance: " << Dist << std::endl;
}