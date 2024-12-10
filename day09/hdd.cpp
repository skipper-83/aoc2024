#include <iostream>
#include <fstream>
#include <vector>
void printHdd(std::vector<long long> &hdd);

bool isDefragged(std::vector<long long> &hdd)
{
	size_t firstFilled = hdd.size() - 1;
	while (hdd[firstFilled] == -1)
	{
		firstFilled--;
	}
	while(hdd[firstFilled] != -1)
	{
		firstFilled--;
		if (firstFilled == 0)
			return true;
	}
	return false;
}

void defrag(std::vector<long long> &hdd)
{
	bool allDone = true;
	for (int i = hdd.size() - 1; i >= 0; i--)
	{
		if (hdd[i] == -1)
			continue;
		for (int j = 0; j < hdd.size(); j++)
		{
			if (hdd[j] == -1)
			{
				hdd[j] = hdd[i];
				hdd[i] = -1;
				break;

			}
		}
		if (isDefragged(hdd))
			return;
	}
}

void printHdd(std::vector<long long> &hdd)
{
	for (int i = 0; i < hdd.size(); i++)
	{
		if (hdd[i] == -1)
			std::cout << ".";
		else
			std::cout << hdd[i];
	}
	std::cout << std::endl;
}

long long checkSum(std::vector<long long> &hdd)
{
	long long sum = 0;
	for (long long i = 0; i < hdd.size(); i++)
	{
		if (hdd[i] == -1)
			continue;
		sum += hdd[i] * i;
	}
	return sum;
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
	int a, b;
	std::string hddString, line;
	std::vector<long long> hdd;
	std::getline(file, line);
	for (int i = 0; i < line.size(); i++)
	{
		if (i % 2 == 0)
		{
			for (int x = 0; x < line[i] - '0'; x++)
			{
				if (line[i])
					hdd.push_back(i / 2);
			}
		}
		else
		{
			for (int x = 0; x < line[i] - '0'; x++)
			{
				hdd.push_back(-1);
			}
		}
	}
	printHdd(hdd);
	defrag(hdd);
	std::cout << std::endl << std::endl;
	printHdd(hdd);
	std::cout << "Checksum: " << checkSum(hdd) << std::endl;
}