#include "SinglyLinkedList.h"
struct PolynomialElem
{
	int  coeff, pow;
};
typedef ST::SLL<PolynomialElem> Polynomial;
Polynomial operator+(Polynomial p1,const Polynomial& p2)
{
	p1.join(p2);
	size_t index;
	for (auto& i : p1)
	{
		index = 0;
		bool lastOK = true;
		for (auto& j : p1)
		{
			if (!lastOK)
			{
				lastOK = true;
				p1.pop(index-1);
				index--;
			}
			if (&i != &j && i.pow == j.pow)
			{
				i.coeff += j.coeff;
				lastOK = false;
			}
			index++;
		}
		if (!lastOK)
		{
			lastOK = true;
			p1.pop(index - 1);
		}
	}
	return p1;
}
int main() {
	Polynomial p1{ {2,2},{3,1},{2,0} };
	Polynomial p2{ {3,2},{-5,1},{-1,0} };
	Polynomial p3 = p1 + p2;
	//expected output: 5x^2 - 2x + 1
	for (auto& i : p3)
	{
		std::cout << i.coeff<< "x^"<<i.pow<<" + ";
	}
	std::cout << 0 << "\n";
}