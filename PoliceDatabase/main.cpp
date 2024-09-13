#include<iostream>
#include<array>
#include<vector>
#include<list>
#include<iterator>
#include<string>
#include<map>
using std::cin;
using std::cout;
using std::endl;

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
    cout << "Insert FELONY: ";
	cin >> insertBufferFelony;	

	for (std::map<std::string, std::vector<std::string>>::iterator mapItr = database.begin(); mapItr != database.end(); ++mapItr)
	{
		if ((*mapItr).first == insertBufferPlates)
		{
			mapItr->second.push_back(insertBufferFelony);
		}
		else
		{
			database.insert(std::pair<std::string, std::vector<std::string>>(insertBufferPlates, { insertBufferFelony }));
		}
	}	
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
}