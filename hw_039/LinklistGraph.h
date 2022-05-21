#pragma once
#include <vector>
#include <iostream>
#include <stack>
#include <queue>

class LLGraph
{
public:
	struct Node
	{
		int data;
		std::vector<Node*> adjs;
		Node(const int& Data)
			:data(Data)
		{}
		Node* AddAdj(Node* other)
		{
			adjs.push_back(other);
			return this;
		}
		Node* AddAdj(LLGraph& graph, const int& other)
		{
			return AddAdj(graph.GetNode(other));
		}
		void DFS()
		{
			if (Explored) return;
			Explored = true;
			for (auto& i : adjs)
			{
				i->DFS();
			}
			std::cout << data << " ";
		}
	private:
		bool Explored = false;
		int time = 0;
	};
	std::pair<std::vector<int>, std::vector<int>> BFS(const int& target)
	{
		std::vector<Node*> BFSWillExplore, BFSExplored;

		std::vector<int> dist, prev;
		dist = std::vector<int>(nodes.size(), -1);
		prev = std::vector<int>(nodes.size(), -1);
		dist[target - 1] = 0;

		Node* crntNode = GetNode(target);
		if (crntNode == nullptr)
			return { prev, dist };
		BFSWillExplore.push_back(crntNode);
		do
		{
			crntNode = BFSWillExplore.back();
			BFSWillExplore.pop_back();
			std::cout << crntNode->data << " ";
			BFSExplored.push_back(crntNode);
			for (auto& i : crntNode->adjs)
			{

				if (std::find(BFSWillExplore.begin(), BFSWillExplore.end(), i) == BFSWillExplore.end() and
					std::find(BFSExplored.begin(), BFSExplored.end(), i) == BFSExplored.end())
				{
					dist[i->data - 1] = dist[crntNode->data - 1] + 1;
					prev[i->data - 1] = crntNode->data;
					BFSWillExplore.emplace(BFSWillExplore.begin(), i);
				}
			}
		}
		while (!BFSWillExplore.empty());
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
			current = PathFindData.first[current] - 1;
			path.emplace(path.begin(), current + 1);
		}
		return { path, dist };
	}
	void DFS(const int& target)
	{
		GetNode(target)->DFS();
	}
	std::vector<Node*> nodes;
	size_t AddNode(Node* node)
	{
		nodes.push_back(node);
		return nodes.size() - 1;
	}
	Node* GetNode(const int& target)
	{
		for (auto node : nodes)
		{
			if (node->data == target)
			{
				return node;
			}
		}
		return nullptr;
	}
};

void LLGraphDemo()
{

	LLGraph myGraph;
	for (size_t i = 0; i < 10; i++)
	{
		myGraph.AddNode(new LLGraph::Node { (int)i + 1 });
	}
	myGraph.GetNode(1)->AddAdj(myGraph, 2)->AddAdj(myGraph, 4)->AddAdj(myGraph, 7);
	myGraph.GetNode(2)->AddAdj(myGraph, 1)->AddAdj(myGraph, 3)->AddAdj(myGraph, 4)->AddAdj(myGraph, 6);
	myGraph.GetNode(3)->AddAdj(myGraph, 2)->AddAdj(myGraph, 4)->AddAdj(myGraph, 5)->AddAdj(myGraph, 9)->AddAdj(myGraph, 10);
	myGraph.GetNode(4)->AddAdj(myGraph, 1)->AddAdj(myGraph, 2)->AddAdj(myGraph, 3)->AddAdj(myGraph, 5)->AddAdj(myGraph, 8);
	myGraph.GetNode(5)->AddAdj(myGraph, 3)->AddAdj(myGraph, 4);
	myGraph.GetNode(6)->AddAdj(myGraph, 2);
	myGraph.GetNode(7)->AddAdj(myGraph, 1)->AddAdj(myGraph, 8);
	myGraph.GetNode(8)->AddAdj(myGraph, 4)->AddAdj(myGraph, 7);
	myGraph.GetNode(9)->AddAdj(myGraph, 3);
	myGraph.GetNode(10)->AddAdj(myGraph, 3);
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