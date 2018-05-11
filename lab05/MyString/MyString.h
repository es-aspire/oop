#pragma once
#include "MyIterator.h"
#include "MyReverseIterator.h"

#if __cplusplus >= 201103L || (__cplusplus < 200000 && __cplusplus > 199711L)
#define CPLUSPLUS_ELEVENT_SUPPORTED
#endif

class CMyString
{
public:
	using Iterator = CMyIterator<char>;
	using ConstIterator = CMyIterator<const char>;
	using ReverseIterator = CMyReverseIterator<char>;
	using ConstReverseIterator = CMyReverseIterator<const char>;

	CMyString();
	CMyString(const char* pString);
	CMyString(const char* pString, size_t length);

#ifndef CPLUSPLUS_ELEVEN_SUPPORTED
	CMyString(CMyString&& other);
	CMyString& operator=(CMyString&& other);
#endif // !CPLUSPLUS_ELEVEN_SUPPORTED

	CMyString(CMyString const& other);
	CMyString(std::string const& stlString);
	~CMyString();

	size_t GetLength() const;
	const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	void Clear();

	CMyString const operator+(CMyString const& rhs);
	CMyString const operator+=(CMyString const& rhs);

	CMyString& operator=(CMyString const& other);

	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	Iterator begin();
	Iterator end();

	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();

	ConstReverseIterator crbegin() const;
	ConstReverseIterator crend() const;

private:
	using CharsPtr = std::unique_ptr<char[]>;

	CharsPtr m_pChars;
	size_t m_length = 0;
};

CMyString const operator+(std::string const& lhs, CMyString const& rhs);
CMyString const operator+(const char* lhs, CMyString const& rhs);

bool operator==(const CMyString& lhs, const CMyString& rhs);
bool operator!=(const CMyString& lhs, const CMyString& rhs);
bool operator<(const CMyString& lhs, const CMyString& rhs);
bool operator>=(const CMyString& lhs, const CMyString& rhs);
bool operator>(const CMyString& lhs, const CMyString& rhs);
bool operator<=(const CMyString& lhs, const CMyString& rhs);

std::istream& operator>>(std::istream& input, CMyString& resultStr);
std::ostream& operator<<(std::ostream& output, CMyString const& str);
