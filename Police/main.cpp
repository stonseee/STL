﻿#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4236)
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>

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
	tm time;
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
	const std::string get_time()const
	{
		//std::string result = asctime(&time);
		//result.pop_back();
		//return result;
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e.%m.%Y", &time);
		return formatted;
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
		char* time_buffer = new char[time.size() + 1] {};
		strcpy(time_buffer, time.c_str());
		
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);
		delete[] time_buffer;

		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900;
		//this->time = time;
	}

	//constructors
	Crime
	(
		int violation_id, 
		const std::string& place, 
		const std::string& time
	)
	{
		this->time = {};
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

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << ":\t" << obj.get_place() << " - " << obj.get_violation();
}

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string filename);

void main()
{
	setlocale(LC_ALL, "");

	//Crime crime(1, "ул. Ленина", "18:10 1.09.2024");
	//cout << crime << endl;

	std::map<std::string, std::list<Crime>> base =
	{
		{"a777bb", {Crime(1, "ул. Ленина", "18:10 1.09.2024"), Crime(2,"пл. Свободы", "12:25 20.08.2024")}},
		{"a000bb", {Crime(6, "ул. Космонавтов", "17:50 1.08.2024"), Crime(8,"ул. Космонавтов", "17:45 01.08.2024")}},
		{"a001аа", {Crime(10, "ул. Пролетарская", "21:50 1.08.2024"), Crime(9,"ул. Пролетарская", "21:50 1.08.2024"), Crime(11,"ул. Пролетарская", "21:50 1.08.2024"), Crime(12,"ул. Пролетарская", "22:05 1.08.2024")}},
	};    
		
	print(base);
	save(base, "base.txt");
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	cout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
		map_it != base.end();
		++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
}

void save(const std::map<std::string, std::list<Crime>>& base, const std::string filename)
{
	std::ofstream fout(filename);
	fout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
		map_it != base.end();
		++map_it)
	{
		fout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			fout << "\t" << *it << endl;
		}
		fout << delimiter << endl;
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}