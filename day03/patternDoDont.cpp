#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>

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
	std::stringstream fileBuf;
	fileBuf << file.rdbuf();
	std::string fileStr = fileBuf.str();
	std::string doDontString;
	size_t dontPos = 0, doPos = 0;

std::cout << "fileStr: " << fileStr << std::endl;
	while ((dontPos = fileStr.find("don't()")) != std::string::npos)
	{
		doPos = fileStr.find("do()");
		if (doPos < dontPos)
			doPos = fileStr.find("do()", dontPos);
		fileStr.erase(dontPos, doPos - dontPos + 4);
		std::cout << "fileStrLoop: " << fileStr << std::endl;
	}
	// doDontString += fileStr;
	std::cout << "dodont:" << fileStr << std::endl;
	
	std::regex levelRegex(R"(mul\((\d{1,3}),(\d{1,3})\))");

	std::sregex_iterator begin(fileStr.begin(), fileStr.end(), levelRegex);
	std::sregex_iterator end;
	int a,b,sum=0;

	for (auto it = begin; it != end; ++it)
	{
		std::smatch match = *it;
		a = std::stoi(match[1].str());
		b = std::stoi(match[2].str());
		std::cout << match[1].str() << " " << match[2].str() << std::endl;
		sum += a * b;
		// std::cout << it->str() << "a: " << a << " b: " << b << std::endl;
	}
	std::cout << "Sum: " << sum << std::endl;

}