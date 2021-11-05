#include <iostream>
#include <array>
static size_t counter;
const size_t n = 8;
void PrintBoard(std::array<size_t, n> board)
{
	counter++;
	char black = 178, white = 176;
	for (size_t j = 0; j < n; j++)
	{
		for (size_t i = 0; i < n; i++)
		{
			if (board[j] == i)
				std::cout << "QU";
			else
				for (size_t k = 0; k < 2; k++)
				{
					std::cout << (((i + j + 1) % 2) == 0 ? white : black);
				}
		}
		std::cout << "\n";

	}
	std::cout << "\n";
}

void backtrack(std::array<size_t, n> board, size_t lineOn = 0)
{
	// show board
	if (lineOn == n)
	{
		PrintBoard(board);
		return;
	}

	for (size_t x = 0; x < n; x++)
	{
		size_t checkX = 0, checkY = 0;
		bool isAvailable = true;
		for (size_t i = 0; i < lineOn; i++)
		{
			if (board[i] != (size_t)-1)
			{
				checkX = board[i];
				checkY = i;

				if (x == checkX || abs((int)(x - checkX)) == abs((int)(lineOn - checkY)))
				{
					isAvailable = false;
					break;
				}
			}
			checkY++;
			continue;
		}
		if (isAvailable)
		{
			auto b2 = board;
			b2[lineOn] = x;
			backtrack(b2, lineOn + 1);
		}
	}
}
int main()
{
	std::array<size_t, n> board;
	board.fill(-1);

	backtrack(board);
	std::cout << "there are " << counter << " possible alternitive universe";
}