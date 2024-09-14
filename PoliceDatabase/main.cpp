#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include<map>
#include<fstream>
using std::cin;
using std::cout;
using std::endl;

void pop_front(std::string& str)
{
	std::string buffer;
	buffer.resize(str.size() - 1);
	for (int i = 0; i < str.size() - 1; ++i)
	{
		buffer[i] = str[i + 1];			
	}
	str = buffer;
}

void symbol_check(std::string& str)
{	
	int ctr = str.size();
	for (int i = 0; i < str.size(); ++i)
	{					
		if (str[i] == ';' || str[i] == ':' || str[i] == ',')
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
		if (str[i] == ';' || str[i] == ':' || str[i] == ',')
		{
			symbol_check(str);
		}		
	}
}

void print(std::map<std::string, std::vector<std::string>>& database)
{
	for (std::map<std::string, std::vector<std::string>>::reverse_iterator mapItr = database.rbegin(); mapItr != database.rend(); ++mapItr)
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

void print_personal(std::map<std::string, std::vector<std::string>>& database, std::string& insertBufferPlates)
{	
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
	
	cout << endl;
	if(sw == 0)cout << "No vehicle found!!" << endl;
}

void add(std::map<std::string, std::vector<std::string>>& database, std::string insertBufferPlates, std::string insertBufferFelony)
{
	symbol_check(insertBufferPlates);	
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
	for (std::map<std::string, std::vector<std::string>>::reverse_iterator mapItr = database.rbegin(); mapItr != database.rend(); ++mapItr)
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

void load(std::map<std::string, std::vector<std::string>>& database, const std::string& filename)
{	
	int ctr = 0;
	int oldCtr = 0;
	int felonyCtr = 1;
	std::string insertPlates;
	std::string insertFelony;	
	std::ifstream fin(filename);
	if (fin.is_open())
	{		
		while (!fin.eof())
		{
			std::string buffer;
			std::getline(fin, buffer);

			for (int i = 0; i < buffer.size(); ++i)
			{
				if (buffer[i] == ':')ctr = i + 1;
				if (buffer[i] == ',')felonyCtr++;
			}
			
			insertPlates = buffer;
			insertPlates.resize(ctr);			
			symbol_check(insertPlates);			
				
			for (int i = 0; i < ctr; ++i)
			{
				pop_front(buffer);
			}

			ctr = 0;

			for (int i = buffer.size() - 1; i >= 0; --i)
			{				
				if (buffer[i] == ',' || buffer[i] == ';') ctr = i + 1;
			}

			insertFelony = buffer;
			insertFelony.resize(ctr);
			symbol_check(insertFelony);				
			add(database, insertPlates, insertFelony);			

			for (int i = 0; i < ctr; ++i)
			{
				pop_front(buffer);						
			}
			
			--felonyCtr;
			
			while (felonyCtr > 0)
			{
				for (int i = buffer.size() - 1; i >= 0; --i)
				{
					if (buffer[i] == ',' || buffer[i] == ';') ctr = i + 1;
				}

				insertFelony = buffer;
				insertFelony.resize(ctr);
			    
				for (int i = 0; i < ctr; ++i)
				{
					pop_front(buffer);
				}

			    symbol_check(insertFelony);	
				add(database, insertPlates, insertFelony);				
				--felonyCtr;
			}

			ctr = 0;
			felonyCtr = 1;
		}			

		database.erase("");

		fin.clear();
		fin.seekg(0);		
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}	
}

void main()
{
	setlocale(LC_ALL, "");

	std::map<std::string, std::vector<std::string>> database =
	{
		//std::pair<std::string, std::vector<std::string>>("THE CAPN", {"Too low", "Too slow", "Too high"}),
		//std::pair<std::string, std::vector<std::string>>("LWYRUP", {"Breaking the law"}),
		//std::pair<std::string, std::vector<std::string>>("09Q SBN", {"Meth manufacturing", "Exhibitionism"})
	};	
	
	std::string input;
	std::string plates;
	std::string felony;		
	std::string piece;		

	while (input != "exit")
	{
		cout << "Insert command" << endl;
		cout << "- \"print\" to read database memory" << endl;
		cout << "- \"personal\" to get specific information" << endl;
		cout << "- \"add\" to set felony information" << endl;
		cout << "- \"save\" to save data changes" << endl;
		cout << "- \"load\" to upload data file" << endl;
		cout << "- \"exit\" to get out" << endl;
		cin >> input;

		if (input == "print")
		{
			cout << "----------------------------------------------" << endl;
			print(database);
			cout << "----------------------------------------------" << endl;
		}

		if (input == "personal")
		{
			cout << "Input PLATES: "; cin >> plates; getline(cin, piece);
			plates += piece;
			cout << "----------------------------------------------" << endl;			
			print_personal(database, plates);
			cout << "----------------------------------------------" << endl;
		}

		if (input == "add")
		{
			cout << "Input PLATES: "; cin >> plates; getline(cin, piece);
			plates += piece;			
			cout << "Input FELONY TYPE: "; cin >> felony; getline(cin, piece);
			felony += piece;
			cout << "----------------------------------------------" << endl;
			add(database, plates, felony);	
			symbol_check(plates);
			print_personal(database, plates);
			cout << "----------------------------------------------" << endl;
		}

		if (input == "save")
		{
			cout << "----------------------------------------------" << endl;
			save(database, "FILE.txt");
			database.clear();
			load(database, "FILE.txt");
			cout << "----------------------------------------------" << endl;
		}

		if (input == "load")
		{
			cout << "----------------------------------------------" << endl;
			database.clear();
			load(database, "FILE.txt");
			print(database);
			cout << "----------------------------------------------" << endl;
		}
	}	
}