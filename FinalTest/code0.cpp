#include <iostream>
#include <string>
#include <vector>

template <class T>
void promt(std::string text, T& input){
	std::cout << text;
	std::cin >> input;
}
int main(){
	size_t arraySize;
	promt("Enter array size: ", arraySize);
	std::cout << "enter array elements: " << std::endl;
	std::vector<int> array(arraySize);
	for (size_t i = 0; i < arraySize; i++)
	{
		int element;
		promt("", element);
		array[i] = element;
	}
	std::cout << "array: " << std::endl;
	for (size_t i = 0; i < arraySize; i++)
	{
		std::cout << array[i] << " ";
	}
	std::cout << "\nresult: " << std::endl;
	int multiple = 1;
	for (size_t i = 0; i < arraySize; i++)
	{
		multiple = multiple * array[i];
	}
	for (size_t j = 0; j < arraySize; j++)
	{
		int result = multiple;
		result /= array[j];
		std::cout << result << " ";
	}
}