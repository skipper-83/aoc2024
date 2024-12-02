#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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
	std::vector<std::vector<int>> levels;
	std::vector<int> level;
	std::string line;
	int safeLevels = 0;
	while (std::getline(file, line))

	{
		std::stringstream ss(line);
		int n;
		while (ss >> n)
		{
			level.push_back(n);
		}
		levels.push_back(level);
		level.clear();
	}
	int count = 0;
	for (auto it : levels)
	{
		bool danger = false;
		bool descending = false;
		std::cout << count++ << ": (" << it.size() << ") ";
		for (int i = 0; i < it.size() - 1; ++i)
		{
			if (i == 0 && it[i] > it[i + 1])
				descending = true;
			std::cout << std::abs(it[i] - it[i + 1]) << " ";
			if (std::abs(it[i] - it[i + 1]) > 3 || std::abs(it[i] - it[i + 1]) < 1)
				danger = true;
			if (i > 0 && descending && it[i] < it[i + 1])
				danger = true;
			if (i > 0 && !descending && it[i] > it[i + 1])
				danger = true;
			if (danger)
				break;
		}
		if (!danger)
			safeLevels++;
		std::cout << "level: ";
		for (auto i : it)
			std::cout << i << " ";
		 std::cout << " danger: " << danger << std::endl;
	}
	std::cout << "Safe levels: " << safeLevels << std::endl;
}