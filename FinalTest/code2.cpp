#include <iostream>
#include <string>
#include <vector>
#include <map>

void removeIsland(std::vector<std::string> &landMap, int x, int y)
{
	if (x < 0 || x >= landMap.size() || y < 0 || y >= landMap[x].size())
	{
		return;
	}
	if (landMap[x][y] == '0')
	{
		return;
	}
	landMap[x][y] = '0';
	removeIsland(landMap, x - 1, y);
	removeIsland(landMap, x + 1, y);
	removeIsland(landMap, x, y - 1);
	removeIsland(landMap, x, y + 1);
}

int countIsland(std::vector<std::string> landMap)
{
	int islandCount = 0;
	for (int x = 0; x < landMap.size(); x++)
	{
		for (int y = 0; y < landMap[x].size(); y++)
		{
			if (landMap[x][y] == '1')
			{
				islandCount++;
				removeIsland(landMap, x, y);
			}
		}
	}
	return islandCount;
}

int main()
{
	// std::vector<std::string> landMap {
	//	"11110",
	//	"11010",
	//	"00000",
	//	"11000",
	// };
	std::vector<std::string> landMap{
		"11000",
		"11000",
		"00100",
		"00011",
	};

	std::cout << countIsland(landMap);
}