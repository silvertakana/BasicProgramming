#include <iostream>
#include <vector>
#include <cmath>
std::vector<int> boymoreMatcher(std::string P, std::string T)
{
	int s = 0;
	int m = P.size(); // length of pattern
	int n = T.size(); // length of text
	std::vector<int> result;
	
	while (s <= n - m)
	{
		int j = m - 1;
		while (j >= 0 && P[j] == T[s + j])
			--j;
		if (j < 0)
		{
			result.push_back(s);
			s++;
		}
		else
			s += std::max(1, int(j - P.find_last_of(T[j+s])));
	}
	return result;
}
int main()
{
	std::string text = "BACABCBAABA";
	std::string pattern = "ACBAB";

	std::vector<int> result = boymoreMatcher(pattern, text);
	for (auto& i : result)
	{
		std::cout << i << "\t"<< text.substr(i, pattern.size()) << "\n";
	}
}