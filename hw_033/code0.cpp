#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
std::unordered_map<size_t, size_t> ComputePrefix(const std::string &P)
{
	const auto m = P.size();
	std::unordered_map<size_t, size_t> mapValue;
	size_t k = 0;
	mapValue[0] = 0;
	for (size_t q = 1; q < m; q++)
	{
		while (k > 0 and P[k + 1] != P[q])
			k = mapValue[k];

		if (P[k + 1] == P[q])
			k++;
		mapValue[q] = k;
	}
	return mapValue;
}
std::vector<size_t> KMP_Matcher(const std::string &P, const std::string &T)
{
	std::vector<size_t> positions;
	const auto m = P.size(), n = T.size();

	const std::unordered_map<size_t, size_t> mapValue = ComputePrefix(P);
	size_t q = -1;

	for (size_t i = 0; i < n; i++)
	{
		while (q > -1 and P[q + 1] != T[i])
			q = mapValue.at(q);

		if (P[q + 1] == T[i])
			q++;
		if (q == m - 1)
		{
			positions.emplace_back(i);
			q = mapValue.at(q);
		}
	}
	return positions;
}
int main()
{
	std::string text = "abababaca";
	std::string findingText = "aba";
	auto allIndex = KMP_Matcher(findingText, text);
	for (size_t j = 0; j < allIndex.size(); j++)
	{
		for (size_t i = 0; i < findingText.size(); i++)
		{
			std::cout << text[allIndex[j] + i];
		}
		std::cout << "\n"
				  << allIndex[j] << "\n";
	}
}