#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

void applyRules(std::vector<int> &page, std::vector<std::pair<int, int>> rules, int level, int *sum)
{
	bool valid = true;
	int swap;
	std::cout << "Applying rules: " << level << " ";
	for (auto rule = rules.begin(); rule != rules.end(); rule++)
	{
		std::vector<int>::iterator firstRule = std::find(page.begin(), page.end(), rule->first);
		std::vector<int>::iterator secondRule = std::find(page.begin(), page.end(), rule->second);
		if (firstRule != page.end() && secondRule != page.end())
		{
			if (secondRule < firstRule)
			{
				swap = *firstRule;
				*firstRule = *secondRule;
				*secondRule = swap;
				valid = false;
				break;
			}
		}
	}
	if (!valid)
		applyRules(page, rules, ++level, sum);
	if (valid)
	{
		std::cout << "Valid page: " << level << " ";
		for (auto it2 = page.begin(); it2 != page.end(); it2++)
			std::cout << *it2 << " ";
		std::cout << std::endl;
		*sum += page[page.size() / 2];
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

	std::string line;
	std::vector<std::pair<int, int>> rules;
	std::vector<std::vector<int>> pages, wrongPages;
	int a, b, sum = 0, wrongSum;
	while (std::getline(file, line) && !line.empty())
	{
		std::replace(line.begin(), line.end(), '|', ' ');
		std::stringstream ss(line);
		ss >> a >> b;
		// std::cout << a << " " << b << std::endl;
		rules.push_back(std::make_pair(a, b));
	}
	while (std::getline(file, line))
	{
		std::replace(line.begin(), line.end(), ',', ' ');
		std::stringstream ss(line);
		std::vector<int> page;
		while (ss >> a)
			page.push_back(a);
		pages.push_back(page);
	}
	// for (auto it = pages.begin(); it != pages.end(); it++)
	// {
	// 	for (auto it2 = it->begin(); it2 != it->end(); it2++)
	// 		std::cout << *it2 << " ";
	// 	std::cout << std::endl;
	// }
	for (auto it = pages.begin(); it != pages.end(); it++)
	{
		bool valid = true;
		for (auto rule = rules.begin(); rule != rules.end(); rule++)
		{
			std::vector<int>::iterator firstRule = std::find(it->begin(), it->end(), rule->first);
			std::vector<int>::iterator secondRule = std::find(it->begin(), it->end(), rule->second);
			if (firstRule != it->end() && secondRule != it->end())
			{
				// std::cout << "found: " << rule->first << " " << rule->second << std::endl;
				// std::cout << "Applying rule: " << rule->first << " " << rule->second << "to page:";
				if (secondRule < firstRule)
				{
					// std::cout << "Transgression! : "  << rule->first << " " << rule->second << std::endl;
					// std::cout << "Transgression!\n";
					wrongPages.push_back(*it);
					valid = false;
					break;
				}
				else
				{
					// std::cout << "Valid!\n" ;
				}
			}
		}
		if (valid)
			// {
			// std::cout << "Valid page: ";
			// for (auto it2 = it->begin(); it2 != it->end(); it2++)
			// std::cout << *it2 << " ";
			// std::cout << "lengt: " << it->size() << " half: " << it->size() / 2 << std::endl;
			// std::cout << (*it)[it->size() / 2] << std::endl;
			// std::cout << std::endl;
			sum += (*it)[it->size() / 2];
		// }else
		// {
		// 	std::cout << "Invalid page: ";
		// 	for (auto it2 = it->begin(); it2 != it->end(); it2++)
		// 		std::cout << *it2 << " ";
		// 	std::cout << std::endl << std::endl;
		// }
		// std::vector<int>::iterator firstRule = std::find(it->begin(), it->end(), rules[0].first);
		// std::vector<int>::iterator secondRule = std::find(it->begin(), it->end(), rules[0].second);
	}
	for (auto it = wrongPages.begin(); it != wrongPages.end(); it++)
	{
		for (auto it2 = it->begin(); it2 != it->end(); it2++)
			std::cout << *it2 << " ";
		std::cout << std::endl;
	}
	for (auto it = wrongPages.begin(); it != wrongPages.end(); it++)
	{
		applyRules(*it, rules, 0, &wrongSum);
	}
	std::cout << "Sum: " << sum << std::endl;
	std::cout << "Wrong sum: " << wrongSum << std::endl;
}