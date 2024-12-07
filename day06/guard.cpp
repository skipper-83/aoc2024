#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

enum direction
{
	N,
	E,
	S,
	W
};

void applyDirection(std::pair<int,int>& guard, enum direction dir)
{
	switch (dir)
	{
	case N:
		guard.second--;
		break;
	case E:
		guard.first++;
		break;
	case S:
		guard.second++;
		break;
	case W:
		guard.first--;
		break;
	default:
		break;
	}
}

enum direction turn(enum direction dir)
{
	switch (dir)
	{
	case N:
		return E;
	case E:
		return S;
	case S:
		return W;
	case W:
		return N;
	}
}

void walk(std::vector<std::string> &map, std::pair<int, int> guard, enum direction dir)
{
	if (guard.first > map[0].size() || guard.first < 0 || guard.second > map.size() || guard.second < 0)
		return ;
	std::pair<int, int> lookAhead = guard;
	if (map[guard.second][guard.first] != 'X')
		map[guard.second][guard.first] = 'X';
	applyDirection(lookAhead, dir);
	if (map[lookAhead.second][lookAhead.first] == '#')
		dir = turn(dir);
	applyDirection(guard, dir);
	walk(map, guard, dir);
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

	std::vector<std::string> map;
	std::string line;
	std::pair<int, int> guard;
	int x = 0, y = 0;
	while (std::getline(file, line))
	{
		map.push_back(line);
		auto loc = std::find(line.begin(), line.end(), '^');
		if (loc != line.end())
		{
			x = std::distance(line.begin(), loc);
			guard = {x, y};
		}
		++y;
	}
	for (int y = 0; y < map.size(); ++y)
	{
		for (int x = 0; x < map[y].size(); ++x)
		{
			if (x == guard.first && y == guard.second)
				std::cout << "!";
			else
				std::cout << map[y][x];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	 walk(map, guard, N);
	int count = 0;
	for (int y = 0; y < map.size(); ++y)
	{
		for (int x = 0; x < map[y].size(); ++x)
		{
				std::cout << map[y][x];
				if (map[y][x] == 'X')
					++count;
		}
		std::cout << std::endl;
	}

	// for
	std::cout << "hash: " << count << std::endl;
}