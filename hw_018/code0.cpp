#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <initializer_list>
#include <map>
#include <cmath>
#include <cstring>
#include <algorithm>

namespace ST
{
	namespace Tree
	{
		template <class T>
		struct Node
		{
			T data;
			Node *left = nullptr, *right = nullptr;
			void preOrder(void (*f)(T &, Node &))
			{
				f(data, *this);
				if (this->left)
					this->left->preOrder(f);
				if (this->right)
					this->right->preOrder(f);
			}
		};
	}
	template <class T>
	class HuffCode
	{
	private:
		struct QueueNode
		{
			Tree::Node<T> *node;
			size_t weight;
			// get depth of the tree
			size_t depth()
			{
				size_t depth = 0;
				QueueNode *temp = this;
				while (temp->node->left != nullptr)
				{
					temp = temp->node->left;
					depth++;
				}
				return depth;
			}
		};

	public:
		Tree::Node<T> *tree;
		HuffCode(T arr[], const size_t &size)
		{
			GenerateTree(arr, size);
		}
		HuffCode(std::initializer_list<T> input)
		{
			GenerateTree(input.begin(), input.size());
		}

		void GenerateTree(T arr[], const size_t &size)
		{
			// get the frequency of each element
			std::map<T, int> freq;
			for (size_t i = 0; i < size; i++)
			{
				freq[arr[i]]++;
			}
			// create a priority queue
			QueueNode *priorityQueue = new QueueNode[freq.size()];
			// put the elements in the queue
			{
				size_t i = 0;
				for (const auto &j : freq)
				{
					priorityQueue[i].node = new Tree::Node<T>{j.first};
					priorityQueue[i].weight = j.second;
					i++;
				}
			}

			// sort the queue
			std::sort(priorityQueue, priorityQueue + freq.size(), [](QueueNode &a, QueueNode &b)
						 { return a.weight < b.weight; });
			// create the tree
			while (priorityQueue[1].node != nullptr)
			{
				// create a new node
				Tree::Node<T> *newNode = new Tree::Node<T>;
				// get the two nodes with the lowest weight
				newNode->data = '\0';
				newNode->left = priorityQueue[0].node;
				newNode->right = priorityQueue[1].node;

				size_t total_weight = priorityQueue[0].weight + priorityQueue[1].weight;

				// remove the two nodes from the queue
				priorityQueue[0].node = nullptr;
				priorityQueue[1].node = nullptr;
				// insert the new node into the queue
				for (size_t i = 0; i < freq.size(); i++)
				{
					// find the position of the new node
					if (priorityQueue[i].node == nullptr)
					{
						// insert the new node
						priorityQueue[i].node = newNode;
						priorityQueue[i].weight = total_weight;
						break;
					}
				}

				// sort the queue
				std::sort(priorityQueue, priorityQueue + freq.size(), [](QueueNode &a, QueueNode &b)
							 {
								 if (a.node && b.node)
									 return a.weight < b.weight;
								 else if (!a.node)
									 return false;
								 else if (!b.node)
									 return true;
								 else return false; });
			}
			// set the root of the tree
			tree = priorityQueue[0].node;
			delete[] priorityQueue;
		}
		void GenerateTree(std::initializer_list<T> input)
		{
			GenerateTree(input.begin(), input.size());
		}
		// find objects in the tree
		std::pair<int, size_t> Find(const T &obj)
		{
			auto res = m_Find(obj);
			return {res.first, res.second.second};
		}
		std::pair<void *, size_t> encode(const std::string &input)
		{

			auto setBit = [](void *data, size_t index, bool on) -> void
			{
				uint8_t *charData = (uint8_t *)data;
				size_t bytes = index / 8;
				if (on)
					charData[bytes] |= (1 << (index - bytes * 8));
				else
					charData[bytes] &= ~(uint8_t)(1 << (index - bytes * 8));
			};

			// a look up table for each character in the input string
			std::map<char, std::pair<int, size_t>> dict;
			// find the code for each character and put it in dict
			{
				for (const auto &i : input)
				{
					if (dict.find(i) == dict.end())
					{
						dict[i] = Find(i);
					}
				}
			}

			// memory needed to store the input string
			size_t memoryCount = 0;
			for (const auto &i : input)
			{
				// calcualte memory in bits
				memoryCount += dict[i].second;
			}
			// result of the encoded string
			void *code = malloc(ceil(memoryCount / 8.f));
			// the current index in which each character code is being append into the final code
			size_t currentIndex = 0;
			for (const auto &i : input)
			{
				auto bitres = (std::bitset<32>)dict[i].first;
				for (size_t j = 0; j < dict[i].second; j++)
				{
					setBit(code, currentIndex, bitres[j]);
					currentIndex++;
				}
			}
			return {code, memoryCount};
		}
		std::string decode(void *code, size_t size)
		{
			auto getBit = [](void *data, size_t index) -> bool
			{
				uint8_t *charData = (uint8_t *)data;
				size_t bytes = index / 8;
				return (1 << (index - bytes * 8)) & charData[bytes];
			};
			std::stringstream output;
			Tree::Node<T> *currentNode = tree;
			for (size_t i = 0; i < size; i++)
			{
				if (getBit(code, i))
				{
					currentNode = currentNode->right;
				}
				else
				{
					currentNode = currentNode->left;
				}
				if (!currentNode->left && !currentNode->right)
				{
					output << currentNode->data;
					currentNode = tree;
				}
			}

			return output.str();
		}

	private:
		std::pair<int, std::pair<bool, size_t>> m_Find(const T &obj, Tree::Node<T> *node = nullptr, size_t digitToWrite = 0)
		{
			if (!node)
				node = tree;
			int code = 0;
			size_t size = 0;
			bool found = false;
			if (node->right != nullptr && node->right->data == obj)
			{
				code |= 1 << digitToWrite;
				found = true;
				size = 1;
			}
			else if (node->left != nullptr && node->left->data == obj)
			{
				found = true;
				size = 1;
			}
			else
			{
				if (node->left != nullptr)
				{
					auto res = m_Find(obj, node->left, digitToWrite + 1);
					found = res.second.first;

					if (found)
					{
						size = 1 + res.second.second;
						code |= res.first;

						return {code, {found, size}};
					}
				}
				if (node->right != nullptr)
				{
					auto res = m_Find(obj, node->right, digitToWrite + 1);
					found = res.second.first;
					if (found)
					{
						size = 1 + res.second.second;
						code |= res.first;
						code |= 1 << digitToWrite;

						return {code, {found, size}};
					}
				}
			}

			return {code, {found, size}};
		}
	};
}

bool getBit(void *data, size_t index)
{
	uint8_t *charData = (uint8_t *)data;
	size_t bytes = index / 8;
	return (1 << (index - bytes * 8)) & charData[bytes];
}
void setBit(void *data, size_t index, bool on)
{
	uint8_t *charData = (uint8_t *)data;
	size_t bytes = index / 8;
	if (on)
		charData[bytes] |= (1 << (index - bytes * 8));
	else
		charData[bytes] &= ~(uint8_t)(1 << (index - bytes * 8));
}
int main()
{
	char input[] = "CAU TRUC DU LIEU VA GIAI THUAT";
	ST::HuffCode<char> a = {input, strlen(input)};

	auto [code, size] = a.encode("CAU TRUC DU LIEU VA GIAI THUAT");
	for (size_t i = 0; i < size; i++)
	{
		std::cout << getBit(code, i);
	}
	std::cout << std::endl
				 << a.decode(code, size) << std::endl;
	std::cout << strlen(input) * 5 - size << " saved bits";
	free(code);
}