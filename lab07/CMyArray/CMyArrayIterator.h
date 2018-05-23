#pragma once

#include <iterator>

template <typename T>
class CMyArray;

template <typename T>
class CMyArrayIterator
{
	friend CMyArray<T>;

public:
	using value_type = T;
	using reference = T&;
	using pointer = T*;
	using iterator_category = std::random_access_iterator_tag;
	using self_type = CMyArrayIterator;
	using difference_type = std::ptrdiff_t;

	CMyArrayIterator(pointer pointer);
	reference operator*();
	pointer operator->();
	self_type operator++();
	self_type operator++(int);
	self_type operator--();
	self_type operator--(int);

	bool operator==(self_type const& rhs);
	bool operator!=(self_type const& rhs);
	bool operator<(self_type const& rhs);
	bool operator>=(self_type const& rhs);
	bool operator>(self_type const& rhs);
	bool operator<=(self_type const& rhs);

	value_type operator[](size_t index)const;

	self_type& operator+=(size_t offset);
	self_type& operator-=(size_t offset);
	self_type& operator+(difference_type offset) const;
	self_type& operator-(difference_type offset) const;
	difference_type operator-(self_type const& rhs) const;

private:
	pointer m_pointer;
};

template<typename T>
CMyArrayIterator<T>& operator+(std::ptrdiff_t& offset, const CMyArrayIterator<T>& rhs);

template<typename T>
CMyArrayIterator<T>::CMyArrayIterator(pointer pointer)
	: m_pointer(pointer)
{
}

template<typename T>
typename CMyArrayIterator<T>::reference CMyArrayIterator<T>::operator*()
{
	return *m_pointer;
}

template<typename T>
typename CMyArrayIterator<T>::pointer CMyArrayIterator<T>::operator->()
{
	return m_pointer;
}

template<typename T>
typename CMyArrayIterator<T>::self_type CMyArrayIterator<T>::operator++()
{
	self_type prev = *this;

	m_pointer++;

	return prev;
}

template<typename T>
typename CMyArrayIterator<T>::self_type CMyArrayIterator<T>::operator++(int)
{
	m_pointer++;

	return *this;
}

template<typename T>
typename CMyArrayIterator<T>::self_type CMyArrayIterator<T>::operator--()
{
	self_type prev = *this;

	m_pointer--;

	return prev;
}

template<typename T>
typename CMyArrayIterator<T>::self_type CMyArrayIterator<T>::operator--(int)
{
	m_pointer--;
	return *this;
}

template<typename T>
bool CMyArrayIterator<T>::operator==(self_type const& rhs)
{
	return m_pointer == rhs.m_pointer;
}

template<typename T>
bool CMyArrayIterator<T>::operator!=(self_type const& rhs)
{
	return m_pointer != rhs.m_pointer;
}

template<typename T>
bool CMyArrayIterator<T>::operator<(self_type const& rhs)
{
	return m_pointer < rhs.m_pointer;
}

template<typename T>
bool CMyArrayIterator<T>::operator>=(self_type const& rhs)
{
	return !(*this < rhs);
}

template<typename T>
bool CMyArrayIterator<T>::operator>(self_type const& rhs)
{
	return rhs.m_pointer < m_pointer;
}

template<typename T>
bool CMyArrayIterator<T>::operator<=(self_type const& rhs)
{
	return !(*this > rhs);
}

template<typename T>
typename CMyArrayIterator<T>::value_type CMyArrayIterator<T>::operator[](size_t index)const
{
	return m_pointer[index];
}

template<typename T>
typename CMyArrayIterator<T>::self_type& CMyArrayIterator<T>::operator+=(size_t offset)
{
	m_pointer = m_pointer + offset;

	return *this;
}

template<typename T>
typename CMyArrayIterator<T>::self_type& CMyArrayIterator<T>::operator-=(size_t offset)
{
	m_pointer = m_pointer - offset;

	return *this;
}

template<typename T>
typename CMyArrayIterator<T>::self_type& CMyArrayIterator<T>::operator+(difference_type offset) const
{
	self_type tmp = *this;

	return (tmp += offset);
}

template<typename T>
typename CMyArrayIterator<T>::self_type& CMyArrayIterator<T>::operator-(difference_type offset) const
{
	self_type tmp = *this;

	return (tmp -= offset);
}

template<typename T>
typename CMyArrayIterator<T>::difference_type CMyArrayIterator<T>::operator-(self_type const& rhs) const
{
	return m_pointer - rhs.m_pointer;
}

template<typename T>
CMyArrayIterator<T>& operator+(std::ptrdiff_t& offset, const CMyArrayIterator<T>& rhs)
{
	CMyArrayIterator<T> tmp = rhs;

	return tmp + offset;
}