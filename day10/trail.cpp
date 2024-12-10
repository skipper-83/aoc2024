#include <iostream>
#include <fstream>
#include <vector>

// typedef struct s_position
// {
// 	int x;
// 	int y;
// } position;

typedef struct s_gridPoint
{
	int value;
	bool visited = false;
} gridPoint;

void printMap(std::vector<std::vector<gridPoint>> &grid)
{
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			std::cout << grid[i][j].value;
		}
		std::cout << std::endl;
	}
}

int trail(std::vector<std::vector<gridPoint>> &grid, int y, int x, int current)
{
	if (y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size())
		return 0;

	int total = 0;
	if (grid[y][x].value == 9 && current == 9)
	{
		// comment these two lines to get the total number of trails for part 2
		if (grid[y][x].visited)
			return 0;
		// end of comment
		grid[y][x].visited = true;
		return 1;
	}
	if (grid[y][x].value != current)
	{
		return 0;
	}

	total += trail(grid, y + 1, x, current + 1);
	total += trail(grid, y - 1, x, current + 1);
	total += trail(grid, y, x + 1, current + 1);
	total += trail(grid, y, x - 1, current + 1);
	return total;
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Usage: " << av[0] << " <file>" << std::endl;
		return 1;
	}
	std::ifstream file(av[1]);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << av[1] << std::endl;
		return 1;
	}
	std::vector<std::vector<gridPoint>> grid;
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<gridPoint> row;
		gridPoint point;
		for (int i = 0; i < line.size(); i++)
		{
			point.value = line[i] - '0';
			row.push_back(point);
		}
		grid.push_back(row);
	}
	printMap(grid);
	std::cout << "size: " << grid.size() << " " << grid[0].size() << std::endl;
	int trails = 0, total = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j].value == 0)
			{
				std::vector<std::vector<gridPoint>> copy = grid;
				if ((trails = trail(copy, i, j, 0)))
				{
					total += trails;
					trails = 0;
				}
			}
		}
	}
	std::cout << "Total trails: " << total << std::endl;
}