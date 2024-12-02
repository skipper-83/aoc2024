#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
	std::vector<int> list1, list2;
	int a, b, sum = 0;
	while (file >> a >> b)
	{
		list1.push_back(a);
		list2.push_back(b);
	}
	
	file.close();
	std::sort(list1.begin(), list1.end());
	std::sort(list2.begin(), list2.end());
	for (size_t i = 0; i < list1.size(); i++)
	{
		std::cout << "diff: " << list1[i] << " - " << list2[i] << " = " << std::abs(list1[i] - list2[i]) << std::endl;
		sum += std::abs(list1[i] - list2[i]);
	}
	std::cout << "Sum: " << sum << std::endl;
	
}