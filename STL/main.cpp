#include<iostream>
#include<array>
#include<vector>
#include<list>
#include<iterator>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------\n"

//#define STL_ARRAY
//#define STL_VECTOR
//#define VECTOR_FLEXABILITY
//#define LIST_FLEXABILITY
#define STL_LIST

template<typename T>void vector_info(const std::vector<T>& vec);

void main()
{
	setlocale(LC_ALL, "");
	
#ifdef STL_ARRAY
	
	const int N = 5;
	std::array<int, N> arr = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

#endif // STL_ARRAY

#ifdef STL_VECTOR

	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };		
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}	
	cout << endl;
	vector_info(vec);
	vec.push_back(55);
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec.at(i) << tab;
	}
	cout << endl;
	vector_info(vec);
	vec.reserve(24);
	vec.shrink_to_fit();
	vec.resize(8);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	vector_info(vec);

	vec.insert(vec.begin() + 4, { 111, 222, 333 });
	for (int i : vec)cout << i << tab; cout << endl;

	int index;
	int count;
	int value;
	cout << "index "; cin >> index;
	cout << "count "; cin >> count;
	cout << "value "; cin >> value;

	//vec.insert(vec.begin() + index, value);
	vec.insert(vec.begin() + index, count, value);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);

	cout << "index "; cin >> index;
	cout << "count "; cin >> count;
	vec.erase(vec.begin() + index, vec.begin() + index + count);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);

#endif // STL_VECTOR	

#ifdef VECTOR_FLEXABILITY
	std::vector<int> vec = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;

	std::vector<int>::iterator it;
	it = vec.begin();
	++it;
	//vec.insert(it, 99);            //работает
	vec.insert(vec.begin() + 2, 99); //работает
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;

	vec.erase(vec.begin() + 2);      //работает
	//vec.erase(it + 2);             //не работает
	//vec.erase(it);                    //не работает
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;
#endif // VECTOR_FLEXABILITY

#ifdef LIST_FLEXABILITY
	std::list<int> list = { 3, 5, 8, 13, 21 };	
	std::list<int>::iterator it;

	it = list.begin();
	++it;

	//list.insert(list.begin() + 2, 99); //не работает
	//list.insert(list.begin(), 99);     //работает
	list.insert(it, 99);                 //работает

	++it;
	list.erase(it);                      //работает
	//list.erase(list.begin());          //работает
	//list.erase(list.begin() + 3);      //не работает

	int n = list.size();
	for (int i = 0; i < n; i++)
	{
		cout << list.front() << tab;
		list.pop_front();
	}
	cout << endl;


#endif // LIST_FLEXABILITY

#ifdef STL_LIST
	std::list<int> list = { 3, 5, 8, 13, 21 };
	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)cout << *it << tab; cout << endl;

	cout << list.front() << endl;
	cout << list.back() << endl;
	list.push_front(2);
	list.push_back(34);
	list.emplace_front(1);
	for (int i : list)cout << i << tab; cout << endl;

	int index;
	int value;
	do
	{
		cout << "index "; cin >> index;
		if (index >= list.size())cout << "error: out of range" << endl;
	} while (index >= list.size());
	cout << "value "; cin >> value;

	std::list<int>::iterator position;
	position = list.begin();

	//for (int i = 0; i < index; i++)	position++;
	std::advance(position, index);
	list.insert(position, value);
	for (int i : list)cout << i << tab; cout << endl;
#endif // STL_LIST


}

template<typename T>void vector_info(const std::vector<T>& vec)
{
	cout << "Size:     " << vec.size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
	cout << "MaxSize:  " << vec.max_size() << endl;
}
