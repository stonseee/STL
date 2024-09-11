#include<iostream>
#include<array>
#include<vector>
#include<list>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------\n"

//#define STL_ARRAY
//#define STL_VECTOR
//#define VECTOR_FLEXABILITY
//#define LIST_FLEXABILITY

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


}

template<typename T>void vector_info(const std::vector<T>& vec)
{
	cout << "Size:     " << vec.size() << endl;
	cout << "Capacity: " << vec.capacity() << endl;
	cout << "MaxSize:  " << vec.max_size() << endl;
}
