#include <string>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
std::vector<size_t> SearchStringRabinKalp(const std::string &pattern, const std::string &txt)
{
	std::vector<size_t> positions; // positions where pattern occurs in text
	const size_t q = 11;		   // A prime number
	const size_t base = 256;	   // Input alphabet base (256 in our case)
	size_t m = pattern.size();	   // Size of pattern
	size_t n = txt.size();		   // Size of text
	size_t i, j;				   // Indices for for-loop
	size_t p = 0;				   // Hash value of pattern
	size_t t = 0;				   // Hash value of current window of text
	size_t h = 1;				   // Hash value of pattern shifted by h

	// The value of h would be same for a fixed pattern.
	// h = pow(base, m-1) % q
	for (i = 0; i < m - 1; i++)
		h = (h * base) % q;

	// Calculate the hash value of pattern and first window of text
	for (i = 0; i < m; i++)
	{
		p = (base * p + pattern[i]) % q;
		t = (base * t + txt[i]) % q;
	}

	// Slide the pattern over text one by one
	for (i = 0; i <= n - m; i++)
	{
		// Check the hash values of current window of text and pattern.
		// If the hash values match then only check for characters on by one
		if (p == t)
		{
			/* Check for characters one by one */
			for (j = 0; j < m; j++)
			{
				if (pattern[j] != txt[i + j])
					break;
			}

			// if p == t and pat[0...m-1] = txt[i, i+1, ...i+m-1]
			if (j == m)
				positions.push_back(i); // record the current window position
		}

		// Calculate hash value for next window of text: Remove leading digit, add trailing digit
		if (i < n - m)
		{
			t = (base * (t - txt[i] * h) + txt[i + m]) % q;

			// We might get negative value of t, converting it to positive
			if (t < 0)
				t = (t + q);
		}
	}

	return positions;
}

int main()
{
	std::string txt = "ABDCB";
	std::string pattern = "DC";

	std::vector<size_t> positions = SearchStringRabinKalp(pattern, txt);
	for (auto &i : positions)
	{
		std::cout << i << "\t" << txt.substr(i, pattern.size()) << std::endl;
	}
}