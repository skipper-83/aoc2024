#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

typedef struct s_calc
{
	long long result;
	std::vector<long> parts;
	std::string ops;
	bool valid = false;
	bool partTwoValid = false;
} t_calc;

void makeCalc(t_calc &calc, int idx, std::string trace)
{
	if (idx == calc.parts.size() - 1)
	{
		t_calc concattedCalc = calc;
		long result = concattedCalc.parts[0];
		long partTwoResult = concattedCalc.parts[0];
		for (int i = 1; i < concattedCalc.parts.size(); i++)
		{
			if (trace[i - 1] == '+')
			{
				result += concattedCalc.parts[i];
				partTwoResult += concattedCalc.parts[i];
			}
			else if (trace[i - 1] == '*')
			{
				result *= concattedCalc.parts[i];
				partTwoResult *= concattedCalc.parts[i];
				}
			else if (trace[i - 1] == '|')
				partTwoResult = std::stoll(std::to_string(partTwoResult) + std::to_string(concattedCalc.parts[i]));
		}
		if (result == calc.result)
		{
			calc.ops = trace;
			calc.valid = true;
		}
		if (partTwoResult == calc.result)
		{
			calc.partTwoValid = true;
		}
		return ;
	}
	makeCalc(calc, idx + 1, trace + "+" );
	makeCalc(calc, idx + 1, trace + "*");
	makeCalc(calc, idx + 1, trace + "|");
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
	std::vector<t_calc> calcs;
	while(std::getline(file, line))
	{
		t_calc calc;
		int a;
		std::replace(line.begin(), line.end(), ':', ' ');
		std::stringstream ss(line);
		ss >> calc.result;
		while (ss >> a)
			calc.parts.push_back(a);
		calcs.push_back(calc);
	}
	long long result = 0, partTwoResult = 0;
	for (auto it = calcs.begin(); it != calcs.end(); it++)
	{
		makeCalc(*it, 0, "");
		if (it->valid)
			result += it->result;
		if (it->partTwoValid)
			partTwoResult += it->result;
	}
	std::cout << "result: " << result << std::endl;
	std::cout << "partTwoResult: " << partTwoResult << std::endl;
	
}