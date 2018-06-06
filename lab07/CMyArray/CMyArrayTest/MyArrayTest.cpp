#include "stdafx.h"
#include "TestUtility.h"

using namespace TestUtility;

SCENARIO("CMyArray")
{
	GIVEN("CmyArray test")
	{
		CMyArray<std::string> arrString;
		CMyArray<double> arrDouble;

		WHEN("Initially CMyArray of std::string and double")
		{
			THEN("allow get size")
			{
				REQUIRE(arrString.GetSize() == 0);
				REQUIRE(arrDouble.GetSize() == 0);
			}

			THEN("size is equal '0' and capacity is equal '0'")
			{
				VerifyArraySizeAndCapacity(arrString, 0, 0);
			}

			THEN("allow append new item")
			{
				arrString.Append("123");
				arrString.Append("456");
				arrDouble.Append(1);
				arrDouble.Append(2);
				arrDouble.Append(3);
				VerifyArraySizeAndCapacity(arrString, 2, 2);
				VerifyArraySizeAndCapacity(arrDouble, 4, 3);
				REQUIRE(IsEqual(arrString, std::vector<std::string>({ "123", "456" })));
			}

			AND_WHEN("reserve definite size and capacity")
			{
				CMyArray<std::string> arr(5);

				THEN("size and capacity is equal a reserved size number")
				{
					VerifyArraySizeAndCapacity(arr, 5, 5);
				}
			}

			AND_WHEN("allows you to construct an array from another array")
			{
				CMyArray<std::string> lhs;
				lhs.Append("123");
				lhs.Append("456");

				CMyArray<std::string> rhs(lhs);

				THEN("array is equal")
				{
					REQUIRE(IsEqual(lhs, rhs));
				}
			}

			THEN("allow to resize size")
			{
				WHEN("new size < CMyArray size")
				{
					CMyArray<double> arr;
					arr.Append(1);
					arr.Append(2);
					arr.Append(3);
					arr.Append(4);

					arr.Resize(1);

					THEN("element from newEnd to oldEnd are deleted")
					{
						AND_THEN("new CMyArray size is equal a transferred to Resize() number and new capacity is equal a previous capacity")
						{
							VerifyArraySizeAndCapacity(arr, 4, 1);
						}
					}
				}

				WHEN("new size > CMyArray size")
				{
					CMyArray<double> arr;

					arr.Resize(4);

					THEN("new CMyArray size is equal new size and new capacity is equal a new size")
					{
						VerifyArraySizeAndCapacity(arr, 4, 4);

						AND_THEN("The elements inserted at the end of the array must be initialized with a default value for the type")
						{
							REQUIRE(IsEqual(arr, CMyArray<double>(4)));
						}
					}
				}	
				WHEN("new size < CMyArray size")
				{
					CMyArray<double> arr;
					for (double i = 0; i < 10; ++i)
					{
						arr.Append(i);
					}

					arr.Resize(4);

					THEN("new CMyArray size is equal new size and new capacity is equal a new size")
					{
						VerifyArraySizeAndCapacity(arr, 16, 4);
					}
				}
			}

			THEN("allow to resize capacity")
			{
				WHEN("array capacity is equal 0")
				{
					AND_WHEN("new capacity is equal 0")
					{
						CMyArray<double> arr;
						arr.ResizeCapacity(0);

						THEN("capacity and size after resize is equal a 0")
						{
							REQUIRE(arr.GetCapacity() == 0);
						}
					}

					AND_WHEN("new capacity is more 0")
					{
						CMyArray<double> arr;
						arr.ResizeCapacity(2);

						THEN("capacity after resize is equal a new capacity and size is equal 0")
						{
							VerifyArraySizeAndCapacity(arr, 2, 0);
						}
					}
				}

				WHEN("array size is more than 0")
				{
					AND_WHEN("new capacity is equal 0")
					{
						CMyArray<double> arr;
						arr.ResizeCapacity(0);

						THEN("capacity and size after resize is equal a 0")
						{
							REQUIRE(arr.GetCapacity() == 0);
						}
					}

					AND_WHEN("new capacity is more than pervious capacity")
					{
						CMyArray<double> arr;
						arr.Append(1);
						arr.Append(2);
						arr.ResizeCapacity(2);

						THEN("capacity after resize is equal a new capacity and size is equal old capacity")
						{
							VerifyArraySizeAndCapacity(arr, 4, 2);
						}
					}
				}
			}
		}

		WHEN("operator []")
		{
			AND_WHEN("CMyArray is empty")
			{
				CMyArray<double> arr;

				THEN("throw 'std::out_of_range' exception")
				{
					REQUIRE_THROWS_AS(arr[2], std::out_of_range);
				}
			}

			AND_WHEN("index >= CMyArray size")
			{
				CMyArray<double> arr;

				THEN("throw 'std::out_of_range' exception")
				{
					REQUIRE_THROWS_AS(arr[2], std::out_of_range);
				}
			}
			AND_WHEN("index is less than CMyArray size")
			{
				CMyArray<double> arr;

				arr.Append(1.0);
				arr.Append(2.0);
				
				THEN("allow change value")
				{
					arr[1] = 9999.0;
					REQUIRE(IsEqual(arr, std::vector<double>({ 1.0, 9999.0 })));
				}
			}
		}

		WHEN("const operator '[]'")
		{
			AND_WHEN("CMyArray is empty")
			{
				const CMyArray<double> arr;

				THEN("throw 'std::out_of_range' exception")
				{
					REQUIRE_THROWS_AS(arr[2], std::out_of_range);
				}
			}

			AND_WHEN("index >= CMyArray size")
			{
				const CMyArray<double> arr;

				THEN("throw 'std::out_of_range' exception")
				{
					REQUIRE_THROWS_AS(arr[2], std::out_of_range);
				}
			}

			AND_WHEN("index is less than CMyArray size")
			{
				CMyArray<double> arr1;
				arr1.Append(1.0);
				arr1.Append(2.0);
				arr1.Append(3.0);
				arr1.Append(4.0);
				arr1.Append(5.0);

				const CMyArray<double> arr2(arr1);

				THEN("allow change value")
				{
					double number = arr2[1];
					
					REQUIRE(IsEqual(number, 2.0));
				}
			}

			AND_WHEN("index >= array size")
			{
				CMyArray<double> arr;
				arr.Append(1.0);
				arr.Append(2.0);
				arr.Append(3.0);

				THEN("throw out_of_range")
				{
					REQUIRE_THROWS_AS(arr[12], std::out_of_range);
				}
			}
		}

		WHEN("operator =")
		{
			CMyArray<int> rhs;
			rhs.Append(1);
			rhs.Append(2);

			AND_WHEN("self-assignment")
			{
				size_t prevSize = rhs.GetSize();
				size_t prevCapacity = rhs.GetCapacity();

				rhs = rhs;

				THEN("data, size and capacity is equal a previous")
				{
					VerifyArraySizeAndCapacity(rhs, prevCapacity, prevSize);
					REQUIRE(IsEqual(rhs, std::vector<int>({ 1, 2 })));
				}
			}

			AND_WHEN("two array have one value type")
			{
				CMyArray<int> lhs;
				lhs.Append(7);
				lhs.Append(8);
				lhs.Append(9);

				lhs = rhs;

				THEN("data, size and capacity is equal a previous")
				{
					VerifyArraySizeAndCapacity(rhs, 2, 2);
					REQUIRE(IsEqual(rhs, std::vector<int>({ 1, 2 })));
				}
			}
		}

		WHEN("method Clear()")
		{
			CMyArray<int> arr;
			arr.Append(1);
			arr.Append(2);
			arr.Append(3);
			arr.Append(4);

			size_t prevCapacity = arr.GetCapacity();

			arr.Clear();

			THEN("CMyArray size is equal zero")
			{
				VerifyArraySizeAndCapacity(arr, prevCapacity, 0);
				size_t size = arr.GetSize();
				std::stringstream strm;

				for (size_t i = 0; i < size; ++i)
				{
					strm << arr[i];
					if (i != size)
					{
						strm << ",";
					}
				}

				REQUIRE(strm.str().empty());
			}
		}
	}
}

SCENARIO("CMyArray get data")
{
	CMyArray<int> arr;
	arr.Append(1);
	arr.Append(2);
	arr.Append(3);
	arr.Append(4);

	SECTION("allow get array of pointers")
	{
		int* data = arr.Data();
		
		for (size_t i = 0; i < arr.GetSize(); ++i)
		{
			REQUIRE(data[i] == arr[i]);
		}
	}

	const CMyArray<int> constArr = arr;

	SECTION("allow get const array of pointers")
	{
		const int* data = constArr.Data();

		for (size_t i = 0; i < arr.GetSize(); ++i)
		{
			REQUIRE(data[i] == constArr[i]);
		}
	}

	SECTION("arr not empty")
	{
		SECTION("allow get Front() element")
		{
			REQUIRE(arr.Front() == 1);
		}

		SECTION("allow get Front() const element")
		{
			REQUIRE(constArr.Front() == 1);
		}

		SECTION("allow get Back() element")
		{
			REQUIRE(arr.Back() == 4);
		}

		SECTION("allow get Back() const element")
		{
			CHECK(constArr.Back() == 4);
		}
	}
	
	SECTION("array empty")
	{
		CMyArray<int> emptyArray;
		CMyArray<int> constEmptyArray = emptyArray;

		SECTION("throw std::out_of_range when get Front() element")
		{
			REQUIRE_THROWS_WITH(emptyArray.Front(), "CMyArray is empty");
		}

		SECTION("throw std::out_of_range when get Front() const element")
		{
			REQUIRE_THROWS_WITH(constEmptyArray.Front(), "CMyArray is empty");
		}

		SECTION("throw std::out_of_range when get Back() element")
		{
			REQUIRE_THROWS_WITH(emptyArray.Back(), "CMyArray is empty");
		}

		SECTION("throw std::out_of_range when get Back() const element")
		{
			REQUIRE_THROWS_WITH(constEmptyArray.Front(), "CMyArray is empty");
		}
	}
}

SCENARIO("CMyArray iterator")
{
	CMyArray<int> arr;
	arr.Append(1);
	arr.Append(2);
	arr.Append(3);
	arr.Append(4);

	SECTION("operator ==")
	{
		bool isOk = arr.Begin() == arr.Begin();
		REQUIRE(isOk);

		isOk = arr.Begin() == arr.End();
		REQUIRE_FALSE(isOk);
	}
	
	SECTION("operator !=")
	{
		bool isOk = arr.Begin() != arr.End();
		REQUIRE(isOk);

		isOk = arr.Begin() != arr.Begin();
		REQUIRE_FALSE(isOk);
	}
	
	SECTION("operator <")
	{
		bool isOk = arr.Begin() < arr.End();
		REQUIRE(isOk);

		isOk = arr.Begin() < arr.Begin();
		REQUIRE_FALSE(isOk);

		isOk = arr.End() < arr.Begin();
		REQUIRE_FALSE(isOk);
	}

	SECTION("operator <=")
	{
		bool isOk = arr.Begin() <= arr.End();
		REQUIRE(isOk);

		isOk = arr.Begin() <= arr.Begin();
		REQUIRE(isOk);

		isOk = arr.End() <= arr.Begin();
		REQUIRE_FALSE(isOk);
	}	

	SECTION("operator <")
	{
		bool isOk = arr.Begin() > arr.End();
		REQUIRE_FALSE(isOk);

		isOk = arr.Begin() > arr.Begin();
		REQUIRE_FALSE(isOk);

		isOk = arr.End() > arr.Begin();
		REQUIRE(isOk);
	}

	SECTION("operator <=")
	{
		bool isOk = arr.Begin() >= arr.End();
		REQUIRE_FALSE(isOk);

		isOk = arr.Begin() >= arr.Begin();
		REQUIRE(isOk);

		isOk = arr.End() >= arr.Begin();
		REQUIRE(isOk);
	}	

	SECTION("prefix operator '++'")
	{
		auto it = arr.Begin();
		++it;
		REQUIRE(*it == 2);
	}
		
	SECTION("postfix operator '++'")
	{
		auto it = arr.Begin();
		it++;
		REQUIRE(*it == 2);
	}	
	
	SECTION("prefix operator '--'")
	{
		auto it = arr.End();
		--it;
		REQUIRE(*it == 4);
	}
		
	SECTION("postfix operator '--'")
	{
		auto it = arr.End();
		it--;
		REQUIRE(*it == 4);
	}
	
	SECTION("operator '+='")
	{
		auto it = arr.Begin();
		it += 1;
		REQUIRE(*it == 2);
	}	
	
	SECTION("operator '-='")
	{
		auto it = arr.End();
		it -= 2;
		REQUIRE(*it == 3);
	}

	SECTION("binary operator '-'")
	{
		std::ptrdiff_t diff = arr.End() - arr.Begin();
		REQUIRE(diff == static_cast<std::ptrdiff_t>(arr.GetSize()));
	}	

	SECTION("allow iterator from Begin() to End()")
	{
		std::stringstream strm;

		for (auto it = arr.Begin(); it != arr.End(); ++it)
		{
			strm << *it << ",";
		}

		REQUIRE(strm.str() == "1,2,3,4,");
	}
	
	SECTION("allow iterator from CBegin() to CEnd()")
	{
		std::stringstream strm;

		for (auto it = arr.CBegin(); it != arr.CEnd(); ++it)
		{
			strm << *it << ",";
		}

		REQUIRE(strm.str() == "1,2,3,4,");
	}
	
	SECTION("allow iterator from RBegin() to REnd()")
	{
		std::stringstream strm;

		for (auto it = arr.RBegin(); it != arr.REnd(); ++it)
		{
			strm << *it;

			if (it != arr.REnd() - 1)
			{
				strm << ",";
			}
		}

		REQUIRE(strm.str() == "4,3,2,1");
	}

	SECTION("allow iterator from CRBegin() to CREnd()")
	{
		std::stringstream strm;

		for (auto it = arr.CRBegin(); it != arr.CREnd(); ++it)
		{
			strm << *it;

			if (it != arr.CREnd() - 1)
			{
				strm << ",";
			}
		}

		REQUIRE(strm.str() == "4,3,2,1");
	}
}