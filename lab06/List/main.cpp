// main.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "List.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <string>

int main()
{
	{
		std::list<int> l;
		std::list<int> r;
		l = r;
	}
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");
		l.push_back("0-=");

		//auto it = l.rbegin();
		//++it;
		//++it;

		//l.insert(it, "123");

		//for (auto it = l.begin(); it != l.end(); it++)
		//{
		//	std::cout << *it << "\n";
		//}

	/*	for (auto it = l.rbegin(); it != l.rend(); ++it)
		{
			std::cout << *it << "\n";
		}*/

		//for (auto const& item : l)
		//{
		//	std::cout << item << "\n";
		//}
		//
		std::cout << "\n";
		//std::list<int> l({ 1, 2, 3 });
		CList<std::string> l2;
		CList<std::string> l3;
		auto it = l2.cbegin();

		for (auto it = l.begin(); it != l.end(); ++it)
		{
			std::cout << *it << "\n";
		}
		
		for (auto it = l.rbegin(); it != l.rend(); ++it)
		{
			std::cout << *it << "\n";
		}


		//l2.clear()
		//l2.clear();
		//l2.push_back("123");
		//std::copy(l.begin(), l.end(), std::back_insert_iterator<CList<std::string>>(l2));
		//std::copy(l2.begin(), l2.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

	/*	std::copy(l.begin(), l1.end(),
			std::back_insert_iterator<CList<T> >(m_childs));*/
		std::cout << "\n";

		//std::copy(l.rbegin(), l.rend(), std::ostream_iterator<std::string>(std::cout, "\n"));
	}
	//CList<int> list;

	//auto it = list.begin();
	////it++;

	//CList<std::string> l;
	//l.push_back("123");
	//l.push_back("456");
	//l.push_back("789");
	//l.push_back("0-=");

	//for (auto it = l.begin(); it != l.end(); it++)
	//{
	//	std::cout << *it << std::endl;
	//}
	//{
	//	auto it = l.end();
	//}
	//{
	//	//CList<int> l;
	//	CList<int> l;

	//	for (int i = 0; i < 10; ++i)
	//	{
	//		//l.push_back(i);
	//		l.push_back(i);
	//	}

	//	//std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, "\n"));
	//}
	//{
	//	CList<int> l({ 1, 2, 3, 4, 5, 6 });
	//	auto it = l.begin();

	//	//l.insert(it, { 123, 123, 123, 123 });
	//	//l.empty();
	//	std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, "\n"));
	//}
	//{
	//	CList<std::string> li;
	//	li.push_back("123");
	//	li.push_back("456");
	//	li.push_back("789");
	//	li.push_front("0");

	//	for (auto const& item : li)
	//	{
	//		std::cout << item << std::endl;
	//	}

	//	li.empty();
	//	li.size();

	//	std::cout << std::endl;
	//	auto it = li.insert(li.begin(), "hello world");
	//	std::cout << "it data: " << *it << std::endl;

	//	++it;
	//	it = it = li.insert(li.begin(), "$");
	//	std::cout << "it: data: " << *it << std::endl;

	//	std::cout << "\n\n'";
	//	li.Clear();
	//	it = li.begin();
	//	//it = li.end();
	///*	for (auto it = li.begin(); it != li.end(); ++it)
	//	{
	//		std::cout << *it << std::endl;
	//	}*/

	//	//for (auto const& item : li)
	//	//{
	//		//std::cout << item << std::endl;
	//	//}
	//}
	//{
	//	CList<int> l;
	//	
	//	l.begin();
	//	l.push_front(9);
	//	l.insert(l.end(), 3);
	//	//l.insert(l.begin(), 3);
	//	//l.insert(l.end(), 1);
	//	/*l.insert(l.begin(), 2);
	//	l.insert(l.begin(), 3);
	//	l.insert(l.begin(), 4);*/
	//	
	//}
	// 
	//{
	//	CList<int> l;
	//	l.push_back(1);
	//	l.push_back(2);
	//	l.push_back(3);
	//	l.push_back(4);

	//	//for (auto it = l.rbegin(); it != l.rend(); ++it)
	//	//{
	//	//	std::cout << *it << std::endl;
	//	//}	
	//
	//	{
	//		CList<int> l;
	//		for (auto it = l.begin(); it != l.end(); ++it)
	//		{
	//			std::cout << *it << std::endl;
	//		}
	//		for (auto it = l.rbegin(); it != l.rend(); ++it)
	//		{
	//		std::cout << *it << std::endl;
	//		}
	//	}
	//}
	{
	/*	CList<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);

		auto it = l.rbegin();*/
	}

	return 0;
}
