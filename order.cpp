#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "util.h"
#include "order.h"
using namespace std;

class Order
{
private:
	string customer, product;
	vector <string> itemList;

public:
	Order() {}
	Order(vector<string>&line)
	{
		if (validCustomerName(line[0]))
		{
			customer = line[0];
		}
		else
		{
			throw string("bad customer name -->");
		}

		for (size_t i = 2; i < line.size(); i++)
		{
			if (validItemName(line[i]))
			{
				itemList.push_back(move(line[i]));
			}
			else
			{
				throw string("bad item name -->") + line[i] + "<--";
			}
		}
	}

	void print()
	{
		cout << "/customer/product/item/item2 = "
			<< "/" << customer
			<< "/" << product;

		for (auto& e : itemList)
		{
			cout << "/" << e;
		}
		cout << "/\n";
	}

	void graph(fstream& dotfile)
	{
		for (auto e : itemList )
		dotfile << '"' << customer << "\n" << product << '"'
			<< "->"
			<< '"' << e       
			<< "[color=blue]\n";
	}
};

class OrderManager
{
	vector<Order> orderList;

public:
	OrderManager() {}
	OrderManager(vector <vector<string>>& csvData)
	{
		for (auto& line : csvData)
		{
			try
			{
				orderList.push_back(Order(line));
			}
			catch (const string& e)
			{
				std::cout << "Problem: " << e << "\n";
			}
		}
	}

	void print()
	{
		for (auto& t : orderList)
		{
			t.print();
		}
	}

	void graph(string& filename)
	{
		string dotFilename = filename + ".gv";
		fstream dotfile(dotFilename, ios::out | ios::trunc);
		if (dotfile.is_open()) {
			dotfile << "digraph tsakgraph{\n";
			for (auto& t : orderList)
				t.graph(dotfile);
			dotfile << "}\n";
			dotfile.close();
		}

		vector<string> dotLocations
		{
			"usr/bin/dot",
			"/usr/local/bin/dot"
			"c:/\"Program Files (x86)\"/Graphviz2.38/bin/dot.exe"
		};

		string dot;

		for (auto& e : dotLocations)
		{
			auto fileexist = [](string file)
			{
				fstream f(file, ios::in);
				return f.is_open();
			}

				if (fileexist(e))
				{
					dot = move(e);
					break;
				}
		}
	}
}

int main(int argc, char* file[])
{		
	if (file[1] == nullptr)
	{
		std::cout << "Invalid Argument Entered.";
		std::cin.ignore();
		return 1;
	}

	string fileName = string(file[1]);
	auto delimiter = '|'; 
	std::vector < std::vector<std::string> > data;
	csvReader(fileName, delimiter, data);
	OrderManager om(data);

	om.print();
	om.graph(fileName);

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
	