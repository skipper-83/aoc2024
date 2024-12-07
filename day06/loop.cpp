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

void printMap(std::vector<std::string> &map)
{
	std::cout << "\nSize: " << map[0].size() << " " << map.size() << "\n";
	for(auto it = map.begin(); it != map.end(); it++)
		std::cout << *it << std::endl;
}

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

char dirChar(enum direction dir)
{
	switch(dir)
	{
		case N:
			return '^';
		case E:
			return '>';
		case S:
			return 'v';
		case W:
			return '<';
	}
}
bool doTurn(std::vector<std::string > &map, std::pair<int, int> &guard, enum direction &dir)
{
	enum direction newDir = dir;
	std::pair<int, int> lookAhead = guard;
	applyDirection(lookAhead, dir);
	for (int i = 0; i < 4; ++i){
		if (lookAhead.first >= map[0].size() || lookAhead.first < 0 || lookAhead.second >= map.size() || lookAhead.second < 0)
		{
			dir = newDir;
			return true;
		}
		if (map[lookAhead.second][lookAhead.first] == '#')
		{
			newDir = turn(newDir);
		}else
		{
			dir = newDir;
			return true;
		}
		lookAhead = guard;
		applyDirection(lookAhead, newDir);
	}
	return false;
}

bool loopCheck(std::vector<std::string> &map, std::pair<int, int> startPos, std::pair<int, int> newGuard, enum direction dir, bool firstCall, int &count)
{
	if (newGuard.first >= map[0].size() || newGuard.first < 0 || newGuard.second >= map.size() || newGuard.second < 0)
		return false;
	if (!doTurn(map, newGuard, dir))
		return true;
	if (!firstCall && map[newGuard.second][newGuard.first] == dirChar(dir))
		return true;
	map[newGuard.second][newGuard.first] = dirChar(dir);
	++count;
	applyDirection(newGuard, dir);
	return loopCheck(map, startPos, newGuard, dir, false, count);
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

	std::vector<std::string> map, checkMap;
	std::string line;
	std::pair<int, int> guard;
	int x = 0, y = 0, count = 0;
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
	checkMap = map;
	int steps = 0;
	for (int y = 0; y < map.size(); ++y)
	{
		for (int x = 0; x < map[0].size(); ++x)
		{
			if (map[y][x] != '#' && map[y][x] != '^')
			{
				checkMap = map;
				checkMap[y][x] = '#';
				if (loopCheck(checkMap, guard, guard, N, true, steps))
					++count;
				steps = 0;
			}
		}
	}
	std::cout << "looping obstacles: " << count << std::endl;
}