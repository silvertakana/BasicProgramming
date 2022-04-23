#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
std::vector<size_t> preComputeLPS(const std::string &pat)
{
	std::vector<size_t> LPS; // length of longest prefix suffix
	LPS.resize(pat.size());	 // size of LPS array must be equal to size of pattern
	size_t len = 0;			 // length of the previous longest prefix suffix
	LPS[0] = 0;				 // no proper prefix or suffix possible for a single character string
	for (size_t i = 1; i < pat.size(); ++i)
	{
		if (pat[i] == pat[len])
		{
			LPS[i] = ++len;
		}
		else
		{
			if (len != 0)
			{
				len = LPS[len - 1];
				--i;
			}
		}
	}
	return LPS;
}
std::vector<size_t> KMPSearch(const std::string &pat, const std::string &txt)
{
	std::vector<size_t> positions; // all positions of matching pattern in txt
	size_t m = pat.size(); // size of pattern
	size_t n = txt.size(); // size of text

	std::vector<size_t> LPS = preComputeLPS(pat); // precompute the length of longest prefix suffix

	size_t i = 0; // index for T[]
	size_t j = 0; // index for P[]
	while (i < n)
	{
		if (pat[j] == txt[i])
		{
			++i;
			++j;
		}
		if (j == m)
		{
			positions.push_back(i - j);
			j = LPS[j - 1];
		}
		else if (i < n && pat[j] != txt[i])
		{
			if (j != 0)
				j = LPS[j - 1];
			else
				++i;
		}
	}
	return positions;
}
int main()
{
	std::string txt = "Computer programming is the process of performing a particular computation, usually by designing/building an executable computer program. Programming involves tasks such as analysis, generating algorithms, profiling algorithms' accuracy and resource consumption, and the implementation of algorithms.";
	std::string pattern = "rogr";

	std::vector<size_t> positions = KMPSearch(pattern, txt);
	for (size_t i = 0; i < positions.size(); ++i)
		std::cout << positions[i] << "\t" << txt.substr(positions[i], pattern.size()) << '\n';
}