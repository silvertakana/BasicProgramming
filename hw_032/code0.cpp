	#include <string>
#include <iostream>
#include <vector>

std::vector<size_t> SearchStringNaive(const std::string &text, const std::string &findingText)
{
	size_t i, j;
	std::vector<size_t> allIndex;
	for (i = 0; i < text.size(); i++)
	{
		for (j = 0; j < findingText.size() && text[i + j] == findingText[j]; j++)
			;
		if (j >= findingText.size())
			allIndex.push_back(i);
	}
	return allIndex;
}

std::vector<size_t> SearchStringRabinKalp(const std::string &text, const std::string &findingText)
{
	size_t p = 0, m = findingText.size(), n = text.size();
	for (size_t i = 0; i < m; i++)
		p = (UCHAR_MAX + 1) * p + findingText[i];

	std::cout << p << "\n";
	std::vector<size_t> t;
	size_t maxPow = std::pow(UCHAR_MAX + 1, m - 1);

	t.push_back(0);
	for (size_t i = 0; i < m; i++)
		t[0] = (UCHAR_MAX + 1) * t[0] + text[i];
	for (size_t s = 1; s <= n - m; s++)
	{
		t.push_back(0);
		t[s] = (UCHAR_MAX + 1) * (t[s - 1] - maxPow * text[s - 1]) + text[s + m - 1];
	}
	std::vector<size_t> positions;
	for (size_t i = 0; i < t.size(); i++)
	{
		if (p == t[i])
		{
			std::cout << t[i] << "\n";
			positions.push_back(i);
		}
	}
	return positions;
}

int main()
{
	std::string text = "Computer programming is the process of performing a particular computation, usually by designing/building an executable computer program. Programming involves tasks such as analysis, generating algorithms, profiling algorithms' accuracy and resource consumption, and the implementation of algorithms.";
	std::string findingText = "programming";
	auto allIndex = SearchStringRabinKalp(text, findingText);
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