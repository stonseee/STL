#include<iostream>
#include<array>
#include<vector>
#include<list>
#include<iterator>
#include<string>
#include<map>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;

void symbol_check(std::string& str)
{	
	int ctr = str.size();
	for (int i = 0; i < str.size(); ++i)
	{			
		cout << "str[] " << str[i] << endl;
		if (str[i] == ';' || str[i] == ':')
		{
			--ctr;
			for (int j = i; j < str.size(); ++j)
			{
				str[j] = str[j + 1];
			}
		}		
	}
	str.resize(ctr);
	for (int i = 0; i < str.size(); ++i)
	{		
		if (str[i] == ';' || str[i] == ':')
		{
			symbol_check(str);
		}		
	}
}

void print(std::map<std::string, std::vector<std::string>>& database)
{
	for (std::map<std::string, std::vector<std::string>>::iterator mapItr = database.begin(); mapItr != database.end(); ++mapItr)
	{
		cout << (*mapItr).first << ":  ";
		for (std::vector<std::string>::iterator vecItr = mapItr->second.begin(); vecItr != mapItr->second.end(); ++vecItr)
		{
			cout << *vecItr;
			if (*vecItr == mapItr->second.back())cout << ";";
			else cout << ", ";
		}
		cout << endl;
	}
}

void print_personal(std::map<std::string, std::vector<std::string>>& database)
{
	std::string insertBufferPlates;
	cout << "Insert PLATES: ";
	cin >> insertBufferPlates;	
	int sw = 0;
		
	for (std::map<std::string, std::vector<std::string>>::iterator mapItr = database.begin(); mapItr != database.end(); ++mapItr)
	{
		if ((*mapItr).first == insertBufferPlates)
		{
			cout << (*mapItr).first << ":  ";
			for (std::vector<std::string>::iterator vecItr = mapItr->second.begin(); vecItr != mapItr->second.end(); ++vecItr)
			{
				cout << *vecItr;
				if (*vecItr == mapItr->second.back())cout << ";";
				else cout << ", ";
			}
			++sw;			
		}		
	}
	
	if(sw == 0)cout << "No vehicle found!!" << endl;
}

void add(std::map<std::string, std::vector<std::string>>& database)
{
	std::string insertBufferPlates;
	std::string insertBufferFelony;
	cout << "Insert PLATES: ";
	cin >> insertBufferPlates;
	symbol_check(insertBufferPlates);
    cout << "Insert FELONY: ";
	cin >> insertBufferFelony;	
	symbol_check(insertBufferFelony);
	int sw = 0;
	
	for (std::map<std::string, std::vector<std::string>>::iterator mapItr = database.begin(); mapItr != database.end(); ++mapItr)
	{
		if ((*mapItr).first == insertBufferPlates)
		{
			mapItr->second.push_back(insertBufferFelony);
			++sw;
		}		
	}	

	if (sw == 0)database.insert(std::pair<std::string, std::vector<std::string>>(insertBufferPlates, { insertBufferFelony }));
}

void save(std::map<std::string, std::vector<std::string>>& database, const std::string& filename)
{
	std::ofstream fout(filename);	
	for (std::map<std::string, std::vector<std::string>>::iterator mapItr = database.begin(); mapItr != database.end(); ++mapItr)
	{
		fout << (*mapItr).first << ":  ";
		for (std::vector<std::string>::iterator vecItr = mapItr->second.begin(); vecItr != mapItr->second.end(); ++vecItr)
		{
			fout << *vecItr;
			if (*vecItr == mapItr->second.back())fout << ";";
			else fout << ", ";
		}
		fout << endl;
	}
	fout.close();	
}

void load(std::map<std::string, std::vector<std::string>>& database, const std::string& filename, int& n)
{	
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		n = 0;
		while (!fin.eof())
		{
			std::string buffer;
			std::getline(fin, buffer);
			//if (NotAppropriateType(buffer))continue;
			n++;
		}
		cout << "Количество записей в файле: " << n << endl;

		//group = new Human * [n] {};

		cout << "Позиция курсора на чтение: " << fin.tellg() << endl;
		fin.clear();
		fin.seekg(0);
		cout << "Позиция курсора на чтение: " << fin.tellg() << endl;

		/*for (int i = 0; i < n; i++)
		{
			std::string type;
			fin >> type;
			if (NotAppropriateType(type))continue;
			group[i] = HumanFactory(type);
			if (group[i])fin >> *group[i];
		}*/

		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
	//return group;	
}

void main()
{
	setlocale(LC_ALL, "");

	std::map<std::string, std::vector<std::string>> database =
	{
		std::pair<std::string, std::vector<std::string>>("LWYRUP", {"Speeding"}),
		std::pair<std::string, std::vector<std::string>>("THE CAPN", {"Too low", "Too slow"}),
		std::pair<std::string, std::vector<std::string>>("o000o199", {"Эксгибиционизм", "Туз червей"})
	};

	//add(database);	
	//print_personal(database);	
	//print(database);
	//save(database, "FILE.txt");
	
	
}