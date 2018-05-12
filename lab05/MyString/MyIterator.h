#pragma once

class CMyString;

template <typename ValueType>
class CMyIterator
{
	friend CMyString;

public:
	typedef ValueType value_type;
	typedef ValueType& reference;
	typedef ValueType* pointer;
	typedef std::random_access_iterator_tag iterator_category;
	typedef ptrdiff_t difference_type;
	typedef CMyIterator<ValueType> self_type;

	CMyIterator(pointer pointer)
		: m_pointer(pointer)
	{	
	}

	reference operator*()
	{
		return *m_pointer;
	}

	pointer operator->()
	{
		return m_pointer;
	}

	self_type operator++()
	{
		self_type prev = *this;
		
		m_pointer++;

		return prev;
	}

	self_type operator++(int)
	{
		m_pointer++;

		return *this;
	}

	self_type operator--()
	{
		self_type prev = *this;

		m_pointer--;

		return prev;
	}

	self_type operator--(int)
	{
		m_pointer--;
		return *this;
	}

	bool operator==(self_type const& rhs)
	{
		return m_pointer == rhs.m_pointer;
	}

	bool operator!=(self_type const& rhs)
	{
		return m_pointer != rhs.m_pointer;
	}

	bool operator<(self_type const& rhs)
	{
		return m_pointer < rhs.m_pointer;
	}

	bool operator>=(self_type const& rhs)
	{
		return !(*this < rhs);
	}

	bool operator>(self_type const& rhs)
	{
		return rhs.m_pointer < m_pointer;
	}

	bool operator<=(self_type const& rhs)
	{
		return !(*this > rhs);
	}

	value_type operator[](size_t index)const
	{
		return m_pointer[index];
	}

	self_type& operator+=(size_t offset)
	{
		m_pointer = m_pointer + offset;

		return *this;
	}

	self_type& operator-=(size_t offset)
	{
		m_pointer = m_pointer - offset;

		return *this;
	}

	self_type& operator+(difference_type offset) const
	{	
		self_type tmp = *this;

		return (tmp += offset);
	}

	self_type& operator-(difference_type offset) const
	{
		self_type tmp = *this;
	
		return (tmp -= offset);
	}

	difference_type operator-(self_type const& rhs) const
	{
		return m_pointer - rhs.m_pointer;
	}

private:
	pointer m_pointer;
};

template<typename ValueType>
CMyIterator<ValueType>& operator+(std::ptrdiff_t& offset, const CMyIterator<ValueType>& rhs)
{
	CMyIterator<ValueType> tmp = rhs;

	return tmp + offset;
}
