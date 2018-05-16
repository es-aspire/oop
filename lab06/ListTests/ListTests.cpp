#include "stdafx.h"
#include "../List/List.h"
#include <string>
#include <sstream>

TEST_CASE("push value")
{
	SECTION("allow push back elements")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");

		std::stringstream strm;
		for (auto const& item : l)
		{
			strm << item;
		}

		REQUIRE(strm.str() == "123456789");
	}

	SECTION("allow push front elements")
	{
		CList<std::string> l;
		l.push_front("123");
		l.push_front("456");
		l.push_front("789");

		std::stringstream strm;
		for (auto const& item : l)
		{
			strm << item;
		}

		REQUIRE(strm.str() == "789456123");
	}

	SECTION("allow to get front value")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");

		REQUIRE(l.front() == "123");
	}	
	
	SECTION("allow to get back value")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");

		REQUIRE(l.back() == "789");
	}

	SECTION("allow to get const front value")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");

		REQUIRE(l.front() == "123");
	}	

	SECTION("allow get size")
	{
		CList<std::string> l;
		l.push_front("123");
		l.push_front("456");
		l.push_front("789");

		REQUIRE(l.size() == 3);
	}	

	SECTION("allows you to find the empty list")
	{
		SECTION("when list empty (size is equal 0), method empty() return true")
		{
			CList<std::string> l;
			REQUIRE(l.size() == 0);
			REQUIRE(l.empty());
		}

		SECTION("when list not empty (size is not equal 0), method empty() return true")
		{
			CList<std::string> l;
			l.push_front("123");
			l.push_front("456");
			l.push_front("789");
			
			REQUIRE(l.size() == 3);
			REQUIRE_FALSE(l.empty());
		}
	}

	SECTION("allows to clear list")
	{
		CList<std::string> l;
		l.push_front("123");
		l.push_front("456");
		l.push_front("789");
		l.clear();
	}

	SECTION("allow insert element to iterator position")
	{
		CList<std::string> l;
		l.push_front("789");
		l.push_front("456");
		l.push_front("123");
		l.push_front("123");

		SECTION("to front")
		{
			l.insert(l.begin(), "HELLO");
			
			std::stringstream strm;
			for (auto const& item : l)
			{
				strm << item;
			}

			REQUIRE(strm.str() == "HELLO123123456789");
		}
		
		SECTION("to back")
		{
			l.insert(l.end(), "HELLO");
			
			std::stringstream strm;
			for (auto const& item : l)
			{
				strm << item;
			}

			REQUIRE(strm.str() == "123123456789HELLO");
		}

		SECTION("when iterator position > begin() && iterator position < end()")
		{
			auto it = l.begin();
			++it;
			++it;
			it++;
			--it;
			it--;
			++it;
			++it;
			l.insert(it, "HELLO");
			
			std::stringstream strm;
			for (auto const& item : l)
			{
				strm << item;
			}

			REQUIRE(strm.str() == "123123456HELLO789");
		}
	}
}


SCENARIO("iterator")
{
	SECTION("operator '->'")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");
		
	}

	SECTION("range base for")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");

		std::stringstream strm;
		for (auto const& item : l)
		{
			strm << item;
		}

		REQUIRE(strm.str() == "123456789");
	}

	SECTION("iterator(begin(), end())")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");
		
		std::stringstream strm;

		for (auto it = l.begin(); it != l.end(); ++it)
		{
			strm << *it;
		}

		REQUIRE(strm.str() == "123456789");
	}

	SECTION("iterator(cbegin(), cend())")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");
		
		std::stringstream strm;

		for (auto it = l.cbegin(); it != l.cend(); ++it)
		{
			strm << *it;
		}

		REQUIRE(strm.str() == "123456789");
	}	
	
	SECTION("iterator(rbegin(), rend())")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");
		
		std::stringstream strm;

		for (auto it = l.rbegin(); it != l.rend(); ++it)
		{
			strm << *it;
		}

		REQUIRE(strm.str() == "789456123");
	}

	SECTION("iterator(crbegin(), crend())")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");
		
		std::stringstream strm;

		for (auto it = l.crbegin(); it != l.crend(); ++it)
		{
			strm << *it;
		}

		REQUIRE(strm.str() == "789456123");
	}

	SECTION("std::copy")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("456");
		l.push_back("789");

		SECTION("copy with std::ostream_iterator")
		{
			std::ostringstream os1;
			std::copy(l.rbegin(), l.rend(), std::ostream_iterator<std::string>(os1));
			REQUIRE(os1.str() == "789456123");	
			
			std::ostringstream os2;
			std::copy(l.crbegin(), l.crend(), std::ostream_iterator<std::string>(os2));
			REQUIRE(os2.str() == "789456123");
		}
	}

	SECTION("std::count")
	{
		CList<std::string> l;
		l.push_back("123");
		l.push_back("7894");
		l.push_back("HELLO WORLD");
		l.push_back("456");
		l.push_back("456");
		l.push_back("456");

		std::string s("HELLO WORLD");

		int count = std::count(l.begin(), l.end(), "456");
		REQUIRE(count == 3);
	}
}