#include <vector>
#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char** file)
{
	if (file[1] == nullptr)
	{
		std::cout << "Invalid Argument Entered.";
		std::cin.ignore();
		return 1;
	}

	char *fileName = file[1];
	auto delimiter = '|';
	std::vector< std::vector<std::string> > data;
	csvReader(fileName, delimiter, data);

	for (auto Line = 0; Line < data.size(); Line++)
	{
		std::cout << "Line " << Line << " -->";
		for (size_t field = 0; field < data[Line].size(); field++)
		{
			std::cout << " " << data[Line][field];
		}
		std::cout << std::endl;
	}
	std::cin.ignore();
	return 0;
}