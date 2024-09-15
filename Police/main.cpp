#pragma warning (disable: 4236)
#include<iostream>
#include<string>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>
#include<fstream>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{1, "Ремень безопасности"},
	{2, "Парковка в неположенном месте"},
	{3, "Пересечение сплошной"},
	{4, "Превышение скорости"},
	{5, "Отсутствие водительского удостоверения"},
	{6, "Отсутствие права управления автомобилем"},
	{7, "Отсутствие страховки"},
	{8, "Проезд на красный"},
	{9, "Выезд на встречную полосу"},
	{10, "Дрифт на перекрестке"},
	{11, "Езда в нетрезвом состоянии"},
	{12, "Оскорбление офицера"},
	{13, "Внесение изменений в конструкцию автомобиля"},
	{14, "Перевозка негабаритного груза"},
	{15, "Превышение максимальной нагрузки на ось"},
	{16, "Перевозка ребенка без кресла"}
};

class Crime
{
	//std::string license_plate;
	int id;
	std::string place;
	std::string time;
public:
	/*const std::string& get_license_plate()const
	{
		return license_plate;
	}*/
	int get_violation_id()const
	{
		return id;
	}
	const std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::string& get_time()const
	{
		return time;
	}
	/*void set_license_plate(const std::string& license_plate)
	{
		this->license_plate = license_plate;
	}*/
	void set_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		this->time = time;
	}

	//constructors
	Crime
	(
		int violation_id, 
		const std::string& place, 
		const std::string& time
	)
	{
		set_violation_id(violation_id);
		set_place(place);
		set_time(time); 
#ifdef DEBUG
			cout << "CrimeConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Crime()
	{
#ifdef DEBUG
		cout << "CrimeDestructor:\t" << this << endl;
#endif // DEBUG
	}
};

//std::ostream& operator<<(std::ostream& os, const Crime& obj)
//{
//	return os << obj.get_time() << ":\t" << obj.get_place() << " - " << obj.get_violation();
//}

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << "Time: " << obj.get_time() << "\t Place: " << obj.get_place() << " - Violation №" << obj.get_violation_id() << " " << obj.get_violation();
}

void Save(std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<Crime>>::iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		fout << "Plate: " << map_it->first << ":\n";
		for (std::list<Crime>::iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			fout << "\t" << *it << endl;
		}
		fout << delimiter << endl;
	}
	fout.close();
}

bool If_plates(std::string& str)
{
	for (int i = 0; i < str.size(); ++i)
	{		
		if (str[i] == 'P')
		{
			if (str[i + 1] == 'l')
			{
				if (str[i + 2] == 'a')
				{
					if (str[i + 3] == 't')
					{
						if (str[i + 4] == 'e')
						{							
							if (str[i + 5] == ':')
							{
								return true;
							}							
						}
					}
				}
			}
		}
	}
	return false;
}

bool If_time(std::string& str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == 'T')
		{
			if (str[i + 1] == 'i')
			{
				if (str[i + 2] == 'm')
				{
					if (str[i + 3] == 'e')
					{
						if (str[i + 4] == ':')
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

int Sym_position(std::string& str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == '-')return i;
	}
	return 0;
}

int Id_return(std::string& str)
{
	if (str == "1 ")return 1;
	if (str == "2 ")return 2;
	if (str == "3 ")return 3;
	if (str == "4 ")return 4;
	if (str == "5 ")return 5;
	if (str == "6 ")return 6;
	if (str == "7 ")return 7;
	if (str == "8 ")return 8;
	if (str == "9 ")return 9;
	if (str == "10")return 10;
	if (str == "11")return 11;
	if (str == "12")return 12;
	if (str == "13")return 13;
	if (str == "14")return 14;
	if (str == "15")return 15;
	if (str == "16")return 16;	
	return 0;
}

void Load(std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	int sw = 0;
	std::string Plates;
	std::string Time;
	std::string Place;
	std::string Violation;
	int id = 0;

	std::ifstream fin(filename);
	if (fin.is_open())
	{
		auto mapItr = base.rbegin();

		while (!fin.eof())
		{
			std::string buffer;
			std::getline(fin, buffer);			
			
			++sw;

			if (If_plates(buffer))
			{
				Plates = buffer.substr(7, 6);
				sw = 0;
			}			
			
			if (If_time(buffer))
			{
				Time = buffer.substr(6, 17);
				Place = buffer.substr(31, Sym_position(buffer) - 32);
				Violation = buffer.substr(Sym_position(buffer) + 13, 2);				
				id = Id_return(Violation);				
			}

			if (sw == 1)
			{				
				base.insert(std::pair<std::string, std::list<Crime>>(Plates, { Crime(id, Place, Time) }));				
			}			

			if (sw > 1 && If_time(buffer))
			{
				mapItr->second.push_back(Crime(id, Place, Time));
			}			
		}		

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

	//Crime crime(1, "ул. Ленина", "18:10 1.09.2024");
	//cout << crime << endl;

	std::map<std::string, std::list<Crime>> base =
	{
		//{"a777bb", {Crime(1, "ул. Ленина", "18:10 01.09.2024"), Crime(2,"пл. Свободы", "12:25 20.08.2024")}},
		//{"a000bb", {Crime(6, "ул. Космонавтов", "17:50 01.08.2024"), Crime(8,"ул. Космонавтов", "17:45 01.08.2024")}},
		//{"a001аа", {Crime(10, "ул. Пролетарская", "21:50 01.08.2024"), Crime(9,"ул. Пролетарская", "21:50 01.08.2024"), Crime(11,"ул. Пролетарская", "21:50 01.08.2024"), Crime(12,"ул. Пролетарская", "22:05 01.08.2024")}},
	};

    Load(base, "FILE.txt");
		
	cout << delimiter << endl;
	for (
		std::map<std::string, std::list<Crime>>::iterator map_it = base.begin();
		map_it != base.end();
		++map_it
		)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}

	//Save(base, "FILE.txt");
}