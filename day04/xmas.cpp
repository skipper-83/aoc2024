#include <iostream>
#include <fstream>
#include <vector>

std::string pattern = "XMAS";
enum direction { NORTH, EAST, SOUTH, WEST, NW, NE, SW, SE };

void direction(size_t *x, size_t *y, enum direction dir)
{
	switch (dir)
	{
		case NORTH:
			*y -= 1;
			break;
		case EAST:
			*x += 1;
			break;
		case SOUTH:
			*y += 1;
			break;
		case WEST:
			*x -= 1;
			break;
		case NW:
			*x -= 1;
			*y -= 1;
			break;
		case NE:
			*x += 1;
			*y -= 1;
			break;
		case SW:
			*x -= 1;
			*y += 1;
			break;
		case SE:
			*x += 1;
			*y += 1;
			break;
		default:
			break;
	}
}

bool xmas(std::vector<std::string> map, size_t x, size_t y, int pos, enum direction dir)
{
	// std::cout << "x: " << x << " y: " << y << " pos: " << pos << " dir: " << dir << std::endl;
	if (pos == pattern.size())
		return true;
	direction(&x, &y, dir);
	// std::cout << "after dir x: " << x << " y: " << y << " pos: " << pos << " dir: " << dir << std::endl;
	if (x >= map[0].size() || y >= map.size())
		return false;
	// std::cout << "pattern[" << pos << "]: " << pattern[pos] << " map[" << y << "][" << x << "]: " << map[y][x] << std::endl;
	if (map[y][x] == pattern[pos])
	{
		if (xmas(map, x, y, pos + 1, dir))
			return true;
	}
	return false;
}

char getChar(std::vector<std::string> map, size_t x, size_t y, enum direction dir)
{
	direction(&x, &y, dir);
	if (y >= map.size() || x >= map[0].size())
		return ' ';
	return map[y][x];
}

bool crossMas(std::vector<std::string> map, size_t x, size_t y)
{
	std::string surroundings = {getChar(map, x, y, NW) , getChar(map, x, y, NE) ,
								getChar(map, x, y, SW) ,  getChar(map, x, y, SE)};
	if(std::count(surroundings.begin(), surroundings.end(), 'M') == 2
	&& std::count(surroundings.begin(), surroundings.end(), 'S') == 2)
	{
		if (surroundings[0] != surroundings[3])
			return true;
	}
	return false;
}

int main(int ac, char** av)
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
	std::vector<std::string> map;
	std::string line;
	int count = 0;
	int crossCount = 0;
	while (std::getline(file, line))
	{
		map.push_back(line);
	}
	std::cout << "Map size: " << map.size() << std::endl;
	std::cout << "Top line: " << map[0] << std::endl;
	for (size_t y = 0; y < map.size(); ++y)
	{
		// std::cout << map[y] << std::endl;
		for(size_t x = 0; x < map[y].size(); ++x)
		{
			if (map[y][x] == pattern[0])
			{
				// std::cout << "Found at: " << x << " " << y << std::endl;
				for (int dir = 0; dir < 8; ++dir)
				{
					// std::cout << "dirring" << std::endl;
					if (xmas(map, x, y, 1, (enum direction)dir))
					{
						std::cout << "Found at: " << x << " " << y << std::endl;
						++count;
					}
				}
			}
			if (map[y][x] == 'A')
			{
				if (crossMas(map, x, y))
				{
					std::cout << "Cross at: " << x << " " << y << std::endl;
					++crossCount;
				}
			}
		}
	}
	std::cout << "Count: " << count << std::endl;
	std::cout << "Cross Count: " << crossCount << std::endl;

}