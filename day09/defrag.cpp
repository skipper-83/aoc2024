#include <iostream>
#include <fstream>
#include <vector>
// void printHdd(std::vector<block> &hdd);

typedef struct s_block
{
	long long size;
	long long fileId;
	bool moved = false;
} block;




void printHdd(std::vector<block> &hdd)
{
	for (int i = 0; i < hdd.size(); i++)
	{
		if (hdd[i].fileId == -1)
		{
			for (int x = 0; x < hdd[i].size; x++)
			{
				std::cout << ".";
			}
		}
		else
		{
			for (int x = 0; x < hdd[i].size; x++)
			{
				std::cout << hdd[i].fileId;
			}
		}
	}
	std::cout << std::endl;
}

long long checkSum(std::vector<block> &hdd)
{
	long long sum = 0;
	int pos = 0;
	for (int i = 0; i < hdd.size(); i++)
	{
		if (hdd[i].fileId == -1)
		{
			for (int x = 0; x < hdd[i].size; x++)
			{
				++pos;
			}
		}
		else
		{
			for (int x = 0; x < hdd[i].size; x++)
			{
				sum += hdd[i].fileId * pos;
				++pos;
			}
		}
	}
	return sum;
}

void defrag(std::vector<block> &hdd)
{
	for (int i = hdd.size() - 1; i >= 0; i--)
	{
		if (hdd[i].fileId == 0)
			return;
		if (hdd[i].fileId == -1 || hdd[i].moved)
			continue;
		for (int j = 0; j < hdd.size(); j++)
		{
			if (hdd[j].fileId == -1 && hdd[j].size >= hdd[i].size)
			{
				if (j >= i)
					break;
				if (hdd[j].size > hdd[i].size)
				{
					block newBlock;
					newBlock.fileId  = -1;
					newBlock.size = hdd[j].size - hdd[i].size;
					hdd.insert(hdd.begin() + j + 1, newBlock);
					i = i + 1;
					hdd[j].size = hdd[i].size;
				}
				hdd[j].fileId = hdd[i].fileId;
				hdd[j].moved = true;
				hdd[i].fileId = -1;
				break;
			}
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
	int a, b;
	std::string hddString, line;
	std::vector<block> hdd;
	std::getline(file, line);
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == '0')
			continue;
		block newBlock;
		if (i % 2 == 0)
		{
			newBlock.fileId = i / 2;
			newBlock.size = line[i] - '0';
		}
		else
		{
			newBlock.fileId = -1;
			newBlock.size = line[i] - '0';
		}
		hdd.push_back(newBlock);
	}
	printHdd(hdd);
	defrag(hdd);
	std::cout << std::endl << std::endl;
	printHdd(hdd);
	std::cout << "Checksum: " << checkSum(hdd) << std::endl;
}