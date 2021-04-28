#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "util.h"
using namespace std;

class Item
{
	string name, installer, remover, sequenceNumber, description;
public:
	Item() {}
	Item(vector<string>& line)
	{
		switch (line.size())
		{
		case 5:
			description = line[4];
		case 4:
			if (validSequenceNumber(line[3]))
				sequenceNumber = line[3];
			else
				throw string("bad sequence number name -->") + line[3] = "<--";
		case 3:
			if (validItemName(line[2]))
				remover = line[2];
			else
				throw string("bad fail Item name -->") + line[2] = "<--";
		case 2:
			if (validItemName(line[1]))
				installer = line[1];
			else
		case 1:
			if (validItemName(line[0]))
				name = line[0];
			else
				throw string("bad item name task-->") + line[2] = "<--";
			break;
		default:
			throw string("bad line, found ") + to_string(line.size()) + " fields, expected 1, 2, 3, or 4";
		}
	}

	void print()
	{
		cout << "name/installer/remover/sequenceNumber/description = "
			<< "/" << name
			<< "/" << installer
			<< "/" << remover
			<< "/" << sequenceNumber
			<< "/" << description
			<< "/" << "/n";
	}

	void graph(fstream& dotfile) 
	{
		cout << "yes";

		dotfile << '"' << "Item: " << name << '"'
			<< " ->"
			<< '"' << "installer" << installer << '"'
			<< "[color=green]\n";
		dotfile << '"' << "Item: " << name << '"'
			<< " ->"
			<< '"' << "Remover: " << remover << '"'
			<< " [color=red]\n";
	}
};

class ItemManager
{
	vector<Item> ItemList;
public:
	ItemManager() {}

	ItemManager(vector <vector<string>> & csvItemData)
	{
		for (auto line : csvItemData)
			try
			{
				ItemList.push_back( move(Item(line)) );
			}
			catch (const string& e)
			{
				std::cout << "Problem: " << e << "\n";
			}
	}


	void print()
	{
		for (auto& t : ItemList)
		{
			t.print();
		}
	}

	void graph(string& filename) 
	{
		cout << "item cpp graph";

		string dotFilename = filename + ".gv";
		fstream dotfile(dotFilename, ios::out | ios::trunc);
		if (dotfile.is_open()) {
			dotfile << "digraph tsakgraph{\n";
			for (auto& t : ItemList)
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
			auto fileexist = [](string file) { fstream f(file, ios::in);
			return f.is_open();
			};
			if (fileexist(e))
			{
				dot = move(e);
				break;
			}
		}
	}
};

///Debugging purposes
/*
int main(int argc, char* file[])
{
	/*
	if (argc != 3)
	{
		cerr << "Usage: " << file[0] << " Item-csv-file Item-csv-seperator-character\n";
		cin.ignore();
		return 1;
	}
	*/
/*

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
	// csvPrint(csvItemData);

	ItemManager im( data );
	im.print();
	im.graph(fileName);



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

*/