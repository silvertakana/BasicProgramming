#include<iostream>
#include<math.h>
int main(){
	std::cout << "n>>" << std::endl;
	int n;
	std::cin >> n;
	
	if(n < 2){
		std::cout << "n is not a prime number" << std::endl;
		return 0;
	}

	for (size_t i = 2; i <= sqrt(n); i++)
	{
		if(fmod(n,i) == 0){
			std::cout << "n is not a prime number"<<std::endl;
			return 0;
		}
	}
	std::cout << "n is a prime number"<<std::endl;
	return 0;
}