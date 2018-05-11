#include "stdafx.h"
#include "MyString.h"

#ifdef _DEBUG
#include <cassert>
#endif // _DEBUG


CMyString::CMyString()
	: CMyString("")
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_pChars = std::make_unique<char[]>(length + 1);
	_memccpy(m_pChars.get(), (pString + '\0'), 0, length);
	m_length = length;
}

CMyString::CMyString(CMyString const& other)
	: CMyString(other.GetStringData(), other.m_length)
{
}

#ifndef CPLUSPLUS_ELEVEN_SUPPORTED
CMyString::CMyString(CMyString&& other)
	: m_pChars(other.m_pChars.get())
	, m_length(other.m_length)
{
	other.Clear();
}

CMyString& CMyString::operator=(CMyString&& other)
{
	if (this != std::addressof(other))
	{
		std::swap(m_pChars, other.m_pChars);
		std::swap(m_length, other.m_length);
		other.Clear();
	}

	return *this;
}
#endif // CPLUSPLUS_ELEVEN_SUPPORTED

CMyString::CMyString(std::string const& stlString)
	: CMyString(stlString.c_str(), stlString.length())
{
}

CMyString::~CMyString()
{
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char* CMyString::GetStringData() const
{
	return (m_length == 0) ? "\0" : m_pChars.get();
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		return CMyString();
	}

	if (start + length > m_length)
	{
		return CMyString(&m_pChars[start], m_length - start);
	}

	return CMyString(&m_pChars[start], length);
}

void CMyString::Clear()
{
	m_pChars.reset();
	m_length = 0;
}

CMyString const CMyString::operator+(CMyString const& rhs)
{
	std::unique_ptr<char[]> result;
	result = std::make_unique<char[]>(m_length + rhs.m_length + 1);

	_memccpy(result.get(), m_pChars.get(), 0, m_length);
	_memccpy(result.get() + m_length, rhs.GetStringData(), 0, rhs.m_length);

	return CMyString(result.get(), m_length + rhs.m_length);
}

CMyString const CMyString::operator+=(CMyString const& rhs)
{
	*this = *this + rhs;

	return *this;
}

CMyString& CMyString::operator=(CMyString const& other)
{
	if (this != std::addressof(other))
	{
		CMyString tmp(other);
		std::swap(m_pChars, tmp.m_pChars);
		std::swap(m_length, tmp.m_length);
	}

	return *this;
}

const char& CMyString::operator[](size_t index) const
{
#ifdef _DEBUG
	assert(index < m_length);
#endif // _DEBUG

	return m_pChars[index];
}

char& CMyString::operator[](size_t index)
{
#ifdef _DEBUG
	assert(index < m_length);
#endif // _DEBUG
	return m_pChars[index];
}

CMyString::Iterator CMyString::begin()
{
	return Iterator(m_pChars.get());
}

CMyString::Iterator CMyString::end()
{
	return Iterator(m_pChars.get() + m_length);
}

CMyString::ConstIterator CMyString::cbegin() const
{
	return ConstIterator(m_pChars.get());
}

CMyString::ConstIterator CMyString::cend() const
{
	return ConstIterator(m_pChars.get() + m_length);
}

CMyString::ReverseIterator CMyString::rbegin()
{
	return ReverseIterator(m_pChars.get() + m_length - 1);
}

CMyString::ReverseIterator CMyString::rend()
{
	return ReverseIterator(m_pChars.get() - 1);
}

CMyString::ConstReverseIterator CMyString::crbegin() const
{
	return ConstReverseIterator(m_pChars.get() + m_length - 1);
}

CMyString::ConstReverseIterator CMyString::crend() const
{
	return ConstReverseIterator(m_pChars.get() - 1);
}

CMyString const operator+(std::string const& lhs, CMyString const& rhs)
{
	return CMyString(lhs) + rhs;
}

CMyString const operator+(const char* lhs, CMyString const& rhs)
{
	return CMyString(lhs) + rhs;
}

bool operator==(const CMyString& lhs, const CMyString& rhs)
{
	if (lhs.GetLength() != rhs.GetLength())
	{
		return false;
	}

	return strcmp(lhs.GetStringData(), rhs.GetStringData()) == 0;
}

bool operator!=(const CMyString& lhs, const CMyString& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const CMyString& lhs, const CMyString& rhs)
{
	return lhs.GetLength() < rhs.GetLength() || strcmp(lhs.GetStringData(), rhs.GetStringData()) < 0;
}

bool operator>=(const CMyString& lhs, const CMyString& rhs)
{
	return !(lhs < rhs);
}

bool operator>(const CMyString& lhs, const CMyString& rhs)
{
	return (rhs < lhs);
}

bool operator<=(const CMyString& lhs, const CMyString& rhs)
{
	return !(rhs < lhs);
}

std::istream& operator>>(std::istream& input, CMyString& resultStr)
{
	std::string readedStr;

	input >> readedStr;

	resultStr = readedStr;

	return input;
}

std::ostream& operator<<(std::ostream& output, CMyString const& str)
{
	output << str.GetStringData();

	return output;
}
