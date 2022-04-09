#include <iostream>
#include <xhash>
#include <array>
#include <format>
#include <string>
template<class T, size_t TableSize>
struct HashTableLink
{
	std::hash<T> basicHasher {};
	T* table[TableSize];
	size_t hash(const T& data, size_t offset = 0)
	{
		return basicHasher(data) + offset;
	}
	size_t Insert(const T& data)
	{
		for (size_t i = 0; i < TableSize; i++)
		{
			auto j = hash(data, i) % TableSize;
			if (table[j] == nullptr)
			{
				table[j] = new T(data);
				return j;
			}
		}
		throw std::overflow_error("overflow hash table");
	}
	size_t Search(const T& data)
	{
		for (size_t i = 0; i < TableSize; i++)
		{
			auto j = hash(data, i) % TableSize;
			if (table[j] != nullptr and *table[j] == data)
			{
				return j;
			}
		}
		return -1;
	}
	size_t Delete(const T& data)
	{
		auto index = Search(data);
		table[index] = nullptr;
		return index;
	}
};
template<class T, size_t TableSize>
struct HashTableOpenAdress
{
	std::hash<T> basicHasher {};
	T* table[TableSize];
	size_t hash(const T& data,  size_t offset = 0)
	{
		
		return basicHasher(data) + offset;
	}
	size_t Insert(const T& data)
	{
		for (size_t i = 0; i < TableSize; i++)
		{
			auto j = hash(data, i) % TableSize;
			if (table[j] == nullptr)
			{
				table[j] = new T(data);
				return j;
			}
		}
		throw std::overflow_error("overflow hash table");
	}
	size_t Search(const T& data)
	{
		for (size_t i = 0; i < TableSize; i++)
		{
			auto j = hash(data, i) % TableSize;
			if (table[j] != nullptr and *table[j] == data)
			{
				return j;
			}
		}
		return -1;
	}
	size_t Delete(const T& data)
	{
		auto index = Search(data);
		if(index!=-1) table[index] = nullptr;
		return index;
	}
};
struct Account
{
	const char* name;
	const char* password;
	bool operator==(const Account& account)
	{
		return name == account.name and password == account.password;
	}
};
namespace std
{
	template<>
	struct hash<Account>
	{
		uint64_t operator()(const Account& account) { return std::hash<std::string>()(std::string(account.name)); };
	};
}
int main()
{
	Account inputs[]{
		{"james", "qwerty123"},
		{"lol", "mitlun"},
		{"what", "why"},
		{"tit", "epic123"},
		{"mitis solun", "truefact"},
	};
	const auto size = sizeof(inputs) / sizeof(Account);
	HashTableOpenAdress<Account, size> myHashTable{};
	for (size_t i = 0; i < size; i++)
	{
		myHashTable.Insert(inputs[i]);
	}
	auto index = myHashTable.Search({"lol", "mitlun"});
	auto account = index != -1 ? *myHashTable.table[index] : Account{"unfound", "null"};
	std::cout << std::format("index: {0}, name: {1}, password: {2}\n", index, account.name, account.password);
	myHashTable.Delete({ "james", "qwerty123" });
	index = myHashTable.Search({ "james", "qwerty123" });
	account = index != -1 ? *myHashTable.table[index] : Account { "unfound", "null" };
	std::cout << std::format("index: {0}, name: {1}, password: {2}\n", index, account.name, account.password);
}