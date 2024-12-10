#include <iostream>
#include <fstream>
#include <map>
#include <vector>

typedef struct s_gridPoint
{
	int x;
	int y;
	char c;
	bool antiNode = false;
	bool node = false;
} t_gridPoint;

void calculateAntiNodes(std::vector<std::vector<t_gridPoint>> &map, std::vector<t_gridPoint> &similarNodes, t_gridPoint &nodeToCheck)
{
	for (auto it = similarNodes.begin(); it != similarNodes.end(); it++)
	{
		if ((*it).x == nodeToCheck.x && (*it).y == nodeToCheck.y) // Skip the node we are checking
			continue;
		int distanceX = (*it).x - nodeToCheck.x;
		int distanceY = (*it).y - nodeToCheck.y;
		int deltaX = distanceX * 2;
		int deltaY = distanceY * 2;
		int antiNodeX = nodeToCheck.x + deltaX;
		int antiNodeY = nodeToCheck.y + deltaY;
		if (antiNodeX >= 0 && antiNodeX < map[0].size() && antiNodeY >= 0 && antiNodeY < map.size())
		{
			std::cout << "Antinode for [" << nodeToCheck.c << "] at " << antiNodeY << " " << antiNodeX << std::endl;
			map[antiNodeY][antiNodeX].antiNode = true;
		}
	}
}

void calculatePart2AntiNodes(std::vector<std::vector<t_gridPoint>> &map, std::vector<t_gridPoint> &similarNodes, t_gridPoint &nodeToCheck)
{
	for (auto it = similarNodes.begin(); it != similarNodes.end(); it++)
	{
		if ((*it).x == nodeToCheck.x && (*it).y == nodeToCheck.y) // Skip the node we are checking
			continue;
		int distanceX = (*it).x - nodeToCheck.x;
		int distanceY = (*it).y - nodeToCheck.y;
		int deltaX = 0, deltaY = 0;
		while (true)
		{
			int antiNodeX = nodeToCheck.x + deltaX;
			int antiNodeY = nodeToCheck.y + deltaY;
			if (antiNodeX < 0 || antiNodeX >= map[0].size() || antiNodeY < 0 || antiNodeY >= map.size())
				break;
			map[antiNodeY][antiNodeX].antiNode = true;
			deltaX += distanceX;
			deltaY += distanceY;
		}
		deltaX = 0, deltaY = 0;
		while (true)
		{
			int antiNodeX = nodeToCheck.x + deltaX;
			int antiNodeY = nodeToCheck.y + deltaY;
			if (antiNodeX < 0 || antiNodeX >= map[0].size() || antiNodeY < 0 || antiNodeY >= map.size())
				break;
			map[antiNodeY][antiNodeX].antiNode = true;
			deltaX -= distanceX;
			deltaY -= distanceY;
		}
	}
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
	std::vector<std::vector<t_gridPoint>> map, part2Map;
	std::map<char, std::vector<t_gridPoint>> nodes;
	std::string line;
	while (std::getline(file, line))
	{
		std::vector<t_gridPoint> row;
		for (int i = 0; i < line.size(); i++)
		{
			t_gridPoint point;
			point.x = i;
			point.y = map.size();
			point.c = line[i];
			row.push_back(point);
			if (line[i] != '.')
			{
				row[i].node = true;
				if (nodes.find(line[i]) == nodes.end())
				{
					std::vector<t_gridPoint> node;
					nodes[line[i]] = node;
				}
				nodes[line[i]].push_back(row[i]);
			}
		}
		map.push_back(row);
	}
	part2Map = map;
	for (auto it = nodes.begin(); it != nodes.end(); it++)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
		{
			std::cout << it->first << ": " << it2->x << " " << it2->y << std::endl;
			calculateAntiNodes(map, it->second, *it2);
			calculatePart2AntiNodes(part2Map, it->second, *it2);
		}
	}
	int count = 0, part2Count = 0;
	for (auto it = map.begin(); it != map.end(); it++)
	{
		for (auto it2 = it->begin(); it2 != it->end(); it2++)
		{
			if (it2->antiNode)
			{
				if (it2->node)
					std::cout << "!";
				else
					std::cout << "#";
				++count;
			}
			else
				std::cout << it2->c;
		}
		std::cout << std::endl;
	}
	for (auto it = part2Map.begin(); it != part2Map.end(); it++)
	{
		for (auto it2 = it->begin(); it2 != it->end(); it2++)
		{
			if (it2->antiNode)
			{
				if (it2->node)
					std::cout << "!";
				else
					std::cout << "#";
				++part2Count;
			}
			else
				std::cout << it2->c;
		}
		std::cout << std::endl;
	}

	std::cout << "Antennas: " << count << std::endl;
	std::cout << "Part 2 antennas: " << part2Count << std::endl;
}
